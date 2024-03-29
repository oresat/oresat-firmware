/**
 * @file    ax5043.c
 * @brief   AX5043 Radio.
 *
 * @addtogroup AX5043
 * @{
 */
#include <string.h>
#include "ch.h"
#include "hal.h"
#include "ax5043.h"
#include "radio.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/**
 * @brief   ChibiOS Event masks for AX5043.
 */
#define AX5043_EVENT_IRQ                    EVENT_MASK(0)
#define AX5043_EVENT_TERMINATE              EVENT_MASK(1)

/**
 * @brief   ChibiOS Event masks for AX5043.
 */
#define AX5043_FIFO_SIZE                    256U

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/
typedef union __attribute__((packed)) {
    struct {
        union {
            uint16_t    reg;
            uint16_t    status;
        };
        uint8_t         data[AX5043_FIFO_SIZE];
    };
    uint8_t             buf[AX5043_FIFO_SIZE + sizeof(uint16_t)];
} spibuf_t;

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

#if (AX5043_USE_SPI) || defined(__DOXYGEN__)
/**
 * @brief   Perform a long (16-bit address) exchange with AX5043 using SPI.
 * @note    Can be called with NULL values for txbuf and/or rxbuf.
 * @note    A maximum of 256 bytes can be transferred at a time using this function.
 * @pre     The SPI interface must be initialized, the driver started, and the device selected.
 *
 * @param[in]   spip        SPI Configuration
 * @param[in]   reg         Register address
 * @param[in]   write       Indicates Read/Write bit
 * @param[in]   txbuf       Buffer to send data from
 * @param[out]  rxbuf       Buffer to return data in
 * @param[in]   n           Number of bytes to exchange
 *
 * @return                  AX5043 status bits
 * @notapi
 */
ax5043_status_t ax5043SPIExchange(SPIDriver *spip, uint16_t reg, bool write, const void *txbuf, void *rxbuf, size_t n) {
    spibuf_t sendbuf;
    spibuf_t recvbuf;

    /* Ensure we don't exceed 256 bytes of data */
    n = (n < AX5043_FIFO_SIZE ? n : AX5043_FIFO_SIZE);

    /* Set the register address to perform the transaction with */
    sendbuf.reg = __REVSH((reg & 0x0FFFU) | 0x7000U | (write << 15));

    /* Copy the TX data to the sending buffer */
    if (txbuf != NULL) {
        memcpy(sendbuf.data, txbuf, n);
    } else {
        memset(sendbuf.data, 0, n);
    }

    /* Perform the exchange */
    /* We always receive because we need the status bits */
    spiExchange(spip, n + sizeof(uint16_t), sendbuf.buf, recvbuf.buf);

    /* Copy the RX data to provided buffer */
    if (rxbuf != NULL) {
        memcpy(rxbuf, recvbuf.data, n);
    }

    return __REVSH(recvbuf.status);
}
#endif /* AX5043_USE_SPI */

/**
 * @brief   Interrupt handler for AX5043 IRQ signals.
 *
 * @param[in]   arg         Pointer to the @p AX5043Driver object
 *
 * @notapi
 */
void ax5043IRQHandler(void *arg) {
    AX5043Driver *devp = arg;

    osalDbgCheck(devp != NULL && devp->irq_worker != NULL);

    chSysLockFromISR();
    chEvtSignalI(devp->irq_worker, AX5043_EVENT_IRQ);
    chSysUnlockFromISR();
}

/**
 * @brief   Interrupt worker thread for AX5043 IRQ signals.
 * @details Broadcasts IRQ signals and handles error conditions.
 *
 * @param[in]   arg         Pointer to the @p AX5043Driver object
 *
 * @notapi
 */
THD_FUNCTION(irq_worker, arg) {
    AX5043Driver *devp = arg;
    eventmask_t irq = 0;

    osalDbgCheck(devp != NULL);

    ax5043WriteU16(devp, AX5043_REG_IRQMASK, 0x0000U);

    while (!chThdShouldTerminateX()) {
        chEvtWaitAny(AX5043_EVENT_IRQ | AX5043_EVENT_TERMINATE);

        /* Retrieve the pending interrupt requests */
        irq = ax5043ReadU16(devp, AX5043_REG_IRQREQUEST);

        /* Signal waiting thread with pending interrupts */
        chEvtBroadcastFlags(&devp->irq_event, irq);
    }
    chThdExit(MSG_OK);
}

/**
 * @brief   Waits for the specified interrupts to occur
 *
 * @return  Event mask
 * @notapi
 */
eventmask_t ax5043WaitIRQ(AX5043Driver *devp, uint16_t irq, sysinterval_t timeout) {
    event_listener_t el;
    eventmask_t event;
    uint16_t regval;

    osalDbgCheck(devp != NULL && devp->config != NULL);

    /* Register on the interrupt with the specified IRQ signals */
    chEvtRegisterMaskWithFlags(&devp->irq_event, &el, AX5043_EVENT_IRQ, irq);

    /* Enable the interrupt source */
    regval = ax5043ReadU16(devp, AX5043_REG_IRQMASK);
    regval |= irq;
    ax5043WriteU16(devp, AX5043_REG_IRQMASK, regval);

    /* Wait for the interrupt to occur */
    event = chEvtWaitAnyTimeout(AX5043_EVENT_IRQ | AX5043_EVENT_TERMINATE, timeout);

    /* Retrieve interrupt request value and unregister from interrupt */
    regval = chEvtGetAndClearFlags(&el);
    chEvtUnregister(&devp->irq_event, &el);

    /* Disable the interrupt */
    regval &= ~irq;
    ax5043WriteU16(devp, AX5043_REG_IRQMASK, regval);
    return event;
}

/**
 * @brief   RX worker thread for handling AX5043 receive data.
 *
 * @param[in]   arg         Pointer to the @p AX5043Driver object
 *
 * @notapi
 */
THD_FUNCTION(rx_worker, arg) {
    AX5043Driver *devp = arg;
    objects_fifo_t *fifo = devp->config->fifo;
    fb_t *fb = NULL;
    uint8_t buf[AX5043_FIFO_SIZE];
    ax5043_rx_chunk_t *chunkp = (ax5043_rx_chunk_t*)buf;
    uint8_t header;
    size_t length, data_len;
    uint8_t *pos;

    osalDbgCheck(devp != NULL);

    while (!chThdShouldTerminateX()) {

        /* Wait for FIFO data */
        if (ax5043WaitIRQ(devp, AX5043_IRQ_FIFONOTEMPTY, TIME_INFINITE) & AX5043_EVENT_TERMINATE) {
            continue;
        }

        /* Get chunk header from FIFO */
        ax5043Exchange(devp, AX5043_REG_FIFODATA, false, NULL, &header, 1);

        /* Determine chunk length */
        length = _FLD2VAL(AX5043_FIFOCHUNK_SIZE, header);
        if (length == AX5043_CHUNKSIZE_VAR) {
            ax5043Exchange(devp, AX5043_REG_FIFODATA, false, NULL, &length, 1);
        }

        /* Get chunk */
        ax5043Exchange(devp, AX5043_REG_FIFODATA, false, NULL, buf, length);

        /* Process chunk */
        switch (_FLD2VAL(AX5043_FIFOCHUNK_CMD, header)) {
        case AX5043_CHUNKCMD_DATA:
            data_len = length - sizeof(ax5043_chunk_data_t);
            /* TODO: Handle error flags */
            /* Start of new packet */
            if (chunkp->data.flags & AX5043_CHUNK_DATARX_PKTSTART) {
                /* Acquire frame buffer object if needed */
                if (fb != NULL) {
                    fb_free(fb, fifo);
                    fb = NULL;
                }
                while (fb == NULL) {
                    fb = fb_alloc(FB_MAX_LEN, fifo);
                }
                fb->phy_rx = devp;
                fb->phy_arg = (void*)devp->config->phy_arg;
            }

            osalDbgAssert(fb != NULL, "rx_worker(), NULL frame buffer object");
            pos = fb_put(fb, data_len);
            if (pos != NULL) {
                /* Copy packet data */
                memcpy(pos, chunkp->data.data, data_len);
            } else {
                /* Length exceeds maximum frame buffer length, abort receive */
                uint8_t reg = ax5043ReadU8(devp, AX5043_REG_FRAMING);
                reg |= AX5043_FRAMING_FABORT;
                ax5043WriteU8(devp, AX5043_REG_FRAMING, reg);
                fb_free(fb, fifo);
                fb = NULL;
            }

            /* End of packet */
            if (chunkp->data.flags & AX5043_CHUNK_DATARX_PKTEND) {
                if (fb != NULL) {
                    pdu_send(fb, fifo);
                    fb = NULL;
                }
            }
            break;
        case AX5043_CHUNKCMD_TIMER:
            devp->timer = __REV(chunkp->timer.timer << 8);
            break;
        case AX5043_CHUNKCMD_RSSI:
            devp->rssi = chunkp->rssi.rssi;
            break;
        case AX5043_CHUNKCMD_FREQOFFS:
            devp->freq_off = __REV(chunkp->freqoffs.freqoffs << 8);
            break;
        case AX5043_CHUNKCMD_RFFREQOFFS:
            devp->rf_freq_off = __REV(chunkp->rffreqoffs.rffreqoffs << 8);
            break;
        case AX5043_CHUNKCMD_DATARATE:
            devp->datarate = __REV(chunkp->datarate.datarate << 8);
            break;
        case AX5043_CHUNKCMD_ANTRSSI:
            if (length == 2) {
                devp->ant0rssi = chunkp->antrssi2.rssi;
                devp->bgndnoise = chunkp->antrssi2.bgndnoise;
            } else if (length == 3) {
                devp->ant0rssi = chunkp->antrssi3.ant0rssi;
                devp->ant1rssi = chunkp->antrssi3.ant1rssi;
                devp->bgndnoise = chunkp->antrssi3.bgndnoise;
            }
            break;
        default:
            break;
        }
    }

    if (fb != NULL) {
        fb_free(fb, fifo);
        fb = NULL;
    }
    chThdExit(MSG_OK);
}

/**
 * @brief   Sets powermode register of AX5043.
 *
 * @param[in]   devp        Pointer to the @p AX5043Driver object.
 * @param[in]   pwrmode     Power mode register value.
 *
 * @return                  Most significant status bits (S14...S8)
 * @notapi
 */
ax5043_status_t ax5043SetPWRMode(AX5043Driver *devp, uint8_t pwrmode) {
    uint8_t regval = 0;

    osalDbgCheck(devp != NULL && devp->config != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043SetPWRMode(), invalid state");

    ax5043Exchange(devp, AX5043_REG_PWRMODE, false, NULL, &regval, 1);
    regval &= ~AX5043_PWRMODE;
    regval |= _VAL2FLD(AX5043_PWRMODE, pwrmode);
    return ax5043Exchange(devp, AX5043_REG_PWRMODE, true, &regval, NULL, 1);
}

/**
 * @brief   Resets the AX5043 device into POWERDOWN state.
 *
 * @param[in]  devp         Pointer to the @p AX5043Driver object.
 *
 * @return                  AX5043 status bits
 * @notapi
 */
ax5043_status_t ax5043Reset(AX5043Driver *devp) {
    ax5043_status_t status = 0;
    uint8_t regval = 0;

    osalDbgCheck(devp != NULL && devp->config != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043Reset(), invalid state");

    devp->error = AX5043_ERR_NOERROR;

    /* Reset the chip through powermode register */
    regval = AX5043_PWRMODE_RESET;
    ax5043WriteU8(devp, AX5043_REG_PWRMODE, regval);

    /* Write to PWRMODE: XOEN, REFEN and POWERDOWN mode. Clear RST bit.
       Page 33 in programming manual */
    regval = AX5043_PWRMODE_REFEN | AX5043_PWRMODE_XOEN | AX5043_PWRMODE_POWERDOWN;
    ax5043WriteU8(devp, AX5043_REG_PWRMODE, regval);

    /* Verify functionality with SCRATCH register */
    regval = 0xAA;
    ax5043Exchange(devp, AX5043_REG_SCRATCH, true, &regval, NULL, 1);
    regval = 0x55;
    status = ax5043Exchange(devp, AX5043_REG_SCRATCH, true, &regval, &regval, 1);
    if (regval != 0xAA) {
        devp->error = AX5043_ERR_NOT_CONNECTED;
        devp->state = AX5043_STOP;
        return status;
    }
    status = ax5043Exchange(devp, AX5043_REG_SCRATCH, true, NULL, &regval, 1);
    if (regval != 0x55) {
        devp->error = AX5043_ERR_NOT_CONNECTED;
        devp->state = AX5043_STOP;
        return status;
    }

    devp->state = AX5043_RESET;
    return status;
}

/**
 * @brief   Sets RFDIV related registers.
 *
 * @param[in]   freq        Frequency
 *
 * @notapi
 */
void ax5043SetRFDIV(AX5043Driver *devp, uint32_t freq) {
    osalDbgCheck(devp != NULL && devp->config != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043SetRFDIV(), invalid state");
    osalDbgAssert((freq >= AX5043_RFDIV_DIV1_MIN && freq <= AX5043_RFDIV_DIV1_MAX) ||
                  (freq >= AX5043_RFDIV_DIV2_MIN && freq <= AX5043_RFDIV_DIV2_MAX),
                  "ax5043SetRFDIV(), frequency out of bounds");

    uint8_t pllvcodiv = ax5043ReadU8(devp, AX5043_REG_PLLVCODIV);
    if (freq >= AX5043_RFDIV_DIV1_MIN && freq <= AX5043_RFDIV_DIV1_MAX) {
        pllvcodiv &= ~AX5043_PLLVCODIV_RFDIV;
    } else {
        pllvcodiv |= AX5043_PLLVCODIV_RFDIV;
    }
    ax5043WriteU8(devp, AX5043_REG_PLLVCODIV, pllvcodiv);
    ax5043WriteU8(devp, AX5043_REG_0xF34, (pllvcodiv & AX5043_PLLVCODIV_RFDIV ? AX5043_0xF34_RFDIV : AX5043_0xF34_NORFDIV));
}

/*===========================================================================*/
/* Interface implementation.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Initializes an instance of AX5043Driver object.
 *
 * @param[out]  devp        Pointer to the @p AX5043Driver object
 *
 * @init
 */
void ax5043ObjectInit(AX5043Driver *devp) {
    devp->config = NULL;

    chMtxObjectInit(&devp->tx_lock);

    devp->irq_worker = NULL;
    chEvtObjectInit(&devp->irq_event);

    devp->rx_worker = NULL;

    devp->preamble = NULL;
    devp->postamble = NULL;

    devp->state = AX5043_STOP;
}

/**
 * @brief   Configures and activates the AX5043 Radio Driver.
 *
 * @param[in]   devp        Pointer to the @p AX5043Driver object
 * @param[in]   config      Pointer to the @p AX5043Config object
 *
 * @api
 */
void ax5043Start(AX5043Driver *devp, const AX5043Config *config) {
    osalDbgCheck((devp != NULL) && (config != NULL));
    osalDbgAssert((devp->state != AX5043_UNINIT),
            "ax5043Start(), invalid state");

    devp->config = config;
    devp->error = AX5043_ERR_NOERROR;
    devp->profile = config->profile;
    devp->preamble = config->preamble;
    devp->preamble_len = config->preamble_len;
    devp->postamble = config->postamble;
    devp->postamble_len = config->postamble_len;

    devp->vcora = 0;
    devp->vcorb = 0;
    devp->timer = 0;
    devp->datarate = 0;
    devp->freq_off = 0;
    devp->rf_freq_off = 0;
    devp->rssi = 0;
    devp->ant0rssi = 0;
    devp->ant1rssi = 0;
    devp->bgndnoise = 0;

#if AX5043_USE_SPI
#if AX5043_SHARED_SPI
    spiAcquireBus(config->spip);
#endif /* AX5043_SHARED_SPI */

    /* Start the SPI interface for the device */
    spiStart(config->spip, config->spicfg);

#if AX5043_SHARED_SPI
    spiReleaseBus(config->spip);
#endif /* AX5043_SHARED_SPI */
#endif /* AX5043_USE_SPI */

    /* Reset device into POWERDOWN state */
    devp->status = ax5043Reset(devp);
    if (devp->error != AX5043_ERR_NOERROR) {
        return;
    }

    /* Register interrupt handler for device and start worker */
    if (devp->irq_worker == NULL) {
        devp->irq_worker = chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(0x400), "ax5043_irq_worker", HIGHPRIO, irq_worker, devp);
        palSetLineCallback(config->irq, ax5043IRQHandler, devp);
        palEnableLineEvent(config->irq, PAL_EVENT_MODE_RISING_EDGE);
    }

    /* Transition to ready state */
    devp->state = AX5043_READY;

    /* Apply initial profile provided by user */
    if (config->profile) {
        ax5043SetProfile(devp, config->profile);
    }

}

/**
 * @brief   Deactivates the AX5043 Radio Driver.
 *
 * @param[in]   devp        Pointer to the @p AX5043Driver object
 *
 * @api
 */
void ax5043Stop(AX5043Driver *devp) {
    osalDbgCheck(devp != NULL && devp->config != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT),
            "ax5043Stop(), invalid state");

    if (devp->state != AX5043_STOP) {
        /* Power down device */
        ax5043SetPWRMode(devp, AX5043_PWRMODE_POWERDOWN);

        /* Disable the interrupt handler and worker thread */
        palDisableLineEvent(devp->config->irq);
        palSetLineCallback(devp->config->irq, NULL, NULL);
        chThdTerminate(devp->irq_worker);
        chEvtSignal(devp->irq_worker, AX5043_EVENT_TERMINATE);
        chThdWait(devp->irq_worker);
        devp->irq_worker = NULL;

#if AX5043_USE_SPI
#if AX5043_SHARED_SPI
        spiAcquireBus(devp->config->spip);
        spiStart(devp->config->spip, devp->config->spicfg);
#endif /* AX5043_SHARED_SPI */

        /* Stop the SPI interface for the device */
        spiStop(devp->config->spip);

#if AX5043_SHARED_SPI
        spiReleaseBus(devp->config->spip);
#endif /* AX5043_SHARED_SPI */
#endif /* AX5043_USE_SPI */
    }

    /* Transition to stop state */
    devp->state = AX5043_STOP;
}

/**
 * @brief   Puts AX5043 into idle mode.
 *
 * @param[in]  devp         Pointer to the @p AX5043Driver object.
 *
 * @api
 */
void ax5043Idle(AX5043Driver *devp) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert(((devp->state == AX5043_READY) ||
                   (devp->state == AX5043_RX) ||
                   (devp->state == AX5043_WOR) ||
                   (devp->state == AX5043_TX)), "ax5043Idle(), invalid state");

    if (devp->state != AX5043_READY) {
        devp->error = AX5043_ERR_NOERROR;

        if (devp->rx_worker) {
            chThdTerminate(devp->rx_worker);
            chEvtSignal(devp->rx_worker, AX5043_EVENT_TERMINATE);
            chThdWait(devp->rx_worker);
            devp->rx_worker = NULL;
        }

        ax5043SetPWRMode(devp, AX5043_PWRMODE_POWERDOWN);

        devp->state = AX5043_READY;
    }
}

/**
 * @brief   Puts AX5043 into receive or wake-on-radio mode.
 *
 * @param[in]  devp         Pointer to the @p AX5043Driver object.
 * @param[in]  chan_b       Use channel B if true.
 * @param[in]  wor          Enable Wake-On-Radio mode.
 *
 * @api
 */
void ax5043RX(AX5043Driver *devp, bool chan_b, bool wor) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert(((devp->state == AX5043_READY) ||
                   (devp->state == AX5043_RX) ||
                   (devp->state == AX5043_WOR) ||
                   (devp->state == AX5043_TX)), "ax5043RX(), invalid state");

    bool cur_chan = ax5043ReadU8(devp, AX5043_REG_PLLLOOP) & AX5043_PLLLOOP_FREQSEL;

    if ((!wor && devp->state != AX5043_RX) || (wor && devp->state != AX5043_WOR) || chan_b != cur_chan) {
        devp->error = AX5043_ERR_NOERROR;

        /* Enter idle state first */
        ax5043Idle(devp);

        /* Set the channel */
        uint32_t freq;
        uint8_t pllloop = ax5043ReadU8(devp, AX5043_REG_PLLLOOP);
        if (chan_b) {
            freq = AX5043_REG_TO_FREQ(ax5043ReadU32(devp, AX5043_REG_FREQB), devp->config->xtal_freq);
            pllloop |= AX5043_PLLLOOP_FREQSEL;
        } else {
            freq = AX5043_REG_TO_FREQ(ax5043ReadU32(devp, AX5043_REG_FREQA), devp->config->xtal_freq);
            pllloop &= ~AX5043_PLLLOOP_FREQSEL;
        }
        ax5043WriteU8(devp, AX5043_REG_PLLLOOP, pllloop);
        ax5043SetRFDIV(devp, freq);

        /* Activate synthesizer to lock PLL */
        ax5043SetPWRMode(devp, AX5043_PWRMODE_RX_SYNTH);
        chThdSleepMicroseconds(1);
        if (!(ax5043GetStatus(devp) & AX5043_STATUS_PLL_LOCK)) {
            ax5043SetPWRMode(devp, AX5043_PWRMODE_POWERDOWN);
            devp->error = AX5043_ERR_LOCKLOST;
            return;
        }
        /* Clear FIFO and set threshold */
        ax5043WriteU8(devp, AX5043_REG_FIFOSTAT, AX5043_FIFOCMD_CLEAR_FIFODAT);
        ax5043WriteU16(devp, AX5043_REG_FIFOTHRESH, 0);

        /* Activate RX or WOR */
        if (wor) {
            ax5043SetPWRMode(devp, AX5043_PWRMODE_RX_WOR);
            devp->state = AX5043_WOR;
        } else {
            ax5043SetPWRMode(devp, AX5043_PWRMODE_RX_FULL);
            devp->state = AX5043_RX;
        }

        /* Start the FIFO worker */
        devp->rx_worker = chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(0x400), "ax5043_rx_worker", HIGHPRIO-1, rx_worker, devp);
    }
}

/**
 * @brief   Puts AX5043 into transmit mode and transmits a packet.
 *
 * @param[in]  devp         Pointer to the @p AX5043Driver object.
 * @param[in]  buf          Transmit buffer.
 * @param[in]  len          Initial length provided in the buffer.
 * @param[in]  total_len    Total length of data to be transmitted.
 * @param[in]  tx_cb        Optional transmit buffer fill callback.
 * @param[in]  tx_cb_arg    Optional transmit buffer fill callback argument.
 * @param[in]  chan_b       Use channel B if true.
 *
 * @api
 */
void ax5043TX(AX5043Driver *devp, const ax5043_profile_t *profile, const void *buf, size_t len, size_t total_len, ax5043_tx_cb_t tx_cb, void *tx_cb_arg, bool chan_b) {
    const ax5043_profile_t *prev_profile;
    ax5043_state_t prev_state;
    bool prev_chan;

    osalDbgCheck(devp != NULL && buf != NULL);
    osalDbgAssert(((devp->state == AX5043_READY) ||
                   (devp->state == AX5043_RX) ||
                   (devp->state == AX5043_WOR) ||
                   (devp->state == AX5043_TX)), "ax5043TX(), invalid state");
    osalDbgAssert(total_len != 0, "ax5043TX(), invalid total length");
    osalDbgAssert(tx_cb != NULL || len == total_len,
            "ax5043TX(), no callback when len != total_len");

    chMtxLock(&devp->tx_lock);
    devp->error = AX5043_ERR_NOERROR;

    /* Record previous state and enter idle state */
    prev_state = devp->state;
    prev_chan = ax5043ReadU8(devp, AX5043_REG_PLLLOOP) & AX5043_PLLLOOP_FREQSEL;
    ax5043Idle(devp);

    /* Set TX profile */
    if (profile != NULL) {
        prev_profile = ax5043GetProfile(devp);
        ax5043SetProfile(devp, profile);
    }

    /* Set Frequency Selection */
    uint32_t freq;
    uint8_t pllloop = ax5043ReadU8(devp, AX5043_REG_PLLLOOP);
    if (chan_b) {
        freq = AX5043_REG_TO_FREQ(ax5043ReadU32(devp, AX5043_REG_FREQB), devp->config->xtal_freq);
        pllloop |= AX5043_PLLLOOP_FREQSEL;
    } else {
        freq = AX5043_REG_TO_FREQ(ax5043ReadU32(devp, AX5043_REG_FREQA), devp->config->xtal_freq);
        pllloop &= ~AX5043_PLLLOOP_FREQSEL;
    }
    ax5043WriteU8(devp, AX5043_REG_PLLLOOP, pllloop);
    ax5043SetRFDIV(devp, freq);

    /* Activate synthesizer to lock PLL */
    /* TODO: Can we base this on an interrupt instead of a delay? */
    ax5043SetPWRMode(devp, AX5043_PWRMODE_TX_SYNTH);
    chThdSleepMicroseconds(1);
    if (!(ax5043GetStatus(devp) & AX5043_STATUS_PLL_LOCK)) {
        ax5043SetPWRMode(devp, AX5043_PWRMODE_POWERDOWN);
        devp->error = AX5043_ERR_LOCKLOST;
        return;
    }
    /* Clear FIFO */
    ax5043WriteU8(devp, AX5043_REG_FIFOSTAT, AX5043_FIFOCMD_CLEAR_FIFODAT);

    /* Activate TX */
    ax5043SetPWRMode(devp, AX5043_PWRMODE_TX_FULL);
    devp->state = AX5043_TX;

    /* Write preamble if provided */
    if (devp->preamble) {
        ax5043WriteU16(devp, AX5043_REG_FIFOTHRESH, devp->preamble_len);
        ax5043WaitIRQ(devp, AX5043_IRQ_FIFOTHRFREE, TIME_INFINITE);

        /* Write preamble to FIFO */
        ax5043Exchange(devp, AX5043_REG_FIFODATA, true, devp->preamble, NULL, devp->preamble_len);
        ax5043WriteU8(devp, AX5043_REG_FIFOSTAT, AX5043_FIFOCMD_COMMIT);
    }

    size_t transferred = 0;
    size_t offset = 0;
    ax5043WriteU16(devp, AX5043_REG_FIFOTHRESH, AX5043_FIFO_WRITE_LEN);
    while (transferred < total_len) {
        ax5043_chunk_data_tx_t data;
        size_t write_len;

        /* Refill buffer if needed */
        if (len == 0 && tx_cb) {
            len = tx_cb(tx_cb_arg);
            offset = 0;
            osalDbgAssert(len != 0,
                    "ax5043TX(), callback returned zero length");
            osalDbgAssert(transferred + len <= total_len,
                    "ax5043TX(), callback returned length exceeding total length");
        }

        /* Determine length of data chunk write */
        write_len = AX5043_FIFO_WRITE_LEN - sizeof(data);
        if (len < write_len) {
            write_len = len;
        }

        /* Prepare chunk */
        data.header = AX5043_CHUNKCMD_DATA | _VAL2FLD(AX5043_FIFOCHUNK_SIZE, AX5043_CHUNKSIZE_VAR);
        data.length = write_len + 1;
        data.flags = 0;
        if (transferred == 0) {
            data.flags |= AX5043_CHUNK_DATATX_PKTSTART;
        }
        if (transferred + write_len == total_len) {
            data.flags |= AX5043_CHUNK_DATATX_PKTEND;
        }

        /* Once there's enough free space, write the data chunk and commit */
        ax5043WaitIRQ(devp, AX5043_IRQ_FIFOTHRFREE, TIME_INFINITE);
        ax5043Exchange(devp, AX5043_REG_FIFODATA, true, (uint8_t*)(&data), NULL, sizeof(data));
        ax5043Exchange(devp, AX5043_REG_FIFODATA, true, &((uint8_t*)buf)[offset], NULL, write_len);
        ax5043WriteU8(devp, AX5043_REG_FIFOSTAT, AX5043_FIFOCMD_COMMIT);

        len -= write_len;
        offset += write_len;
        transferred += write_len;
    }

    /* Write postamble if provided */
    if (devp->postamble) {
        ax5043WriteU16(devp, AX5043_REG_FIFOTHRESH, devp->postamble_len);
        ax5043WaitIRQ(devp, AX5043_IRQ_FIFOTHRFREE, TIME_INFINITE);

        /* Write postamble to FIFO */
        ax5043Exchange(devp, AX5043_REG_FIFODATA, true, devp->postamble, NULL, devp->postamble_len);
        ax5043WriteU8(devp, AX5043_REG_FIFOSTAT, AX5043_FIFOCMD_COMMIT);
    }

    ax5043WriteU16(devp, AX5043_REG_RADIOEVENTMASK, AX5043_RADIOEVENT_DONE);
    ax5043WaitIRQ(devp, AX5043_IRQ_RADIOCTRL, TIME_INFINITE);
    ax5043WriteU16(devp, AX5043_REG_RADIOEVENTMASK, 0x0000U);
    ax5043ReadU16(devp, AX5043_REG_RADIOEVENTREQ);

    /* Return to original state */
    if (profile != NULL) {
        ax5043SetProfile(devp, prev_profile);
    }
    switch (prev_state) {
    case AX5043_RX:
        ax5043RX(devp, prev_chan, false);
        break;
    case AX5043_WOR:
        ax5043RX(devp, prev_chan, true);
        break;
    case AX5043_READY:
    default:
        ax5043Idle(devp);
    }
    chMtxUnlock(&devp->tx_lock);
}

/**
 * @brief   Puts AX5043 into raw transmit mode.
 *
 * @param[in]  devp         Pointer to the @p AX5043Driver object.
 * @param[in]  buf          Transmit FIFO buffer.
 * @param[in]  len          Initial length provided in the buffer.
 * @param[in]  total_len    Total length of data to be transmitted.
 * @param[in]  tx_cb        Optional transmit buffer fill callback.
 * @param[in]  tx_cb_arg    Optional transmit buffer fill callback argument.
 * @param[in]  chan_b       Use channel B if true.
 *
 * @api
 */
void ax5043TXRaw(AX5043Driver *devp, const ax5043_profile_t *profile, const void *buf, size_t len, size_t total_len, ax5043_tx_cb_t tx_cb, void *tx_cb_arg, bool chan_b) {
    const ax5043_profile_t *prev_profile;
    ax5043_state_t prev_state;
    bool prev_chan;

    osalDbgCheck(devp != NULL && buf != NULL);
    osalDbgAssert(((devp->state == AX5043_READY) ||
                   (devp->state == AX5043_RX) ||
                   (devp->state == AX5043_WOR) ||
                   (devp->state == AX5043_TX)), "ax5043TXRaw(), invalid state");
    osalDbgAssert(total_len != 0, "ax5043TXRaw(), invalid total length");
    osalDbgAssert(tx_cb != NULL || len == total_len,
            "ax5043TXRaw(), no callback when len != total_len");

    chMtxLock(&devp->tx_lock);
    devp->error = AX5043_ERR_NOERROR;

    /* Record previous state and enter idle state */
    prev_state = devp->state;
    prev_chan = ax5043ReadU8(devp, AX5043_REG_PLLLOOP) & AX5043_PLLLOOP_FREQSEL;
    ax5043Idle(devp);

    /* Set TX profile */
    if (profile != NULL) {
        prev_profile = ax5043GetProfile(devp);
        ax5043SetProfile(devp, profile);
    }

    /* Set Frequency Selection */
    uint32_t freq;
    uint8_t pllloop = ax5043ReadU8(devp, AX5043_REG_PLLLOOP);
    if (chan_b) {
        freq = AX5043_REG_TO_FREQ(ax5043ReadU32(devp, AX5043_REG_FREQB), devp->config->xtal_freq);
        pllloop |= AX5043_PLLLOOP_FREQSEL;
    } else {
        freq = AX5043_REG_TO_FREQ(ax5043ReadU32(devp, AX5043_REG_FREQA), devp->config->xtal_freq);
        pllloop &= ~AX5043_PLLLOOP_FREQSEL;
    }
    ax5043WriteU8(devp, AX5043_REG_PLLLOOP, pllloop);
    ax5043SetRFDIV(devp, freq);

    /* Activate synthesizer to lock PLL */
    /* TODO: Can we base this on an interrupt instead of a delay? */
    ax5043SetPWRMode(devp, AX5043_PWRMODE_TX_SYNTH);
    chThdSleepMicroseconds(1);
    if (!(ax5043GetStatus(devp) & AX5043_STATUS_PLL_LOCK)) {
        ax5043SetPWRMode(devp, AX5043_PWRMODE_POWERDOWN);
        devp->error = AX5043_ERR_LOCKLOST;
        return;
    }
    /* Clear FIFO */
    ax5043WriteU8(devp, AX5043_REG_FIFOSTAT, AX5043_FIFOCMD_CLEAR_FIFODAT);

    /* Activate TX */
    ax5043SetPWRMode(devp, AX5043_PWRMODE_TX_FULL);
    devp->state = AX5043_TX;

    size_t transferred = 0;
    size_t offset = 0;
    ax5043WriteU16(devp, AX5043_REG_FIFOTHRESH, AX5043_FIFO_WRITE_LEN);
    while (transferred < total_len) {
        size_t write_len;

        /* Refill buffer if needed */
        if (len == 0 && tx_cb) {
            len = tx_cb(tx_cb_arg);
            offset = 0;
            osalDbgAssert(len != 0,
                    "ax5043TX(), callback returned zero length");
            osalDbgAssert(transferred + len <= total_len,
                    "ax5043TX(), callback returned length exceeding total length");
        }

        /* Determine length of data chunk write */
        write_len = (len < AX5043_FIFO_WRITE_LEN ? len : AX5043_FIFO_WRITE_LEN);

        /* Once there's enough free space, write the data chunk and commit */
        ax5043WaitIRQ(devp, AX5043_IRQ_FIFOTHRFREE, TIME_INFINITE);
        ax5043Exchange(devp, AX5043_REG_FIFODATA, true, &((uint8_t*)buf)[offset], NULL, write_len);
        ax5043WriteU8(devp, AX5043_REG_FIFOSTAT, AX5043_FIFOCMD_COMMIT);

        len -= write_len;
        offset += write_len;
        transferred += write_len;
    }

    ax5043WriteU16(devp, AX5043_REG_RADIOEVENTMASK, AX5043_RADIOEVENT_DONE);
    ax5043WaitIRQ(devp, AX5043_IRQ_RADIOCTRL, TIME_INFINITE);
    ax5043WriteU16(devp, AX5043_REG_RADIOEVENTMASK, 0x0000U);
    ax5043ReadU16(devp, AX5043_REG_RADIOEVENTREQ);

    /* Return to original state */
    if (profile != NULL) {
        ax5043SetProfile(devp, prev_profile);
    }
    switch (prev_state) {
    case AX5043_RX:
        ax5043RX(devp, prev_chan, false);
        break;
    case AX5043_WOR:
        ax5043RX(devp, prev_chan, true);
        break;
    case AX5043_READY:
    default:
        ax5043Idle(devp);
    }
    chMtxUnlock(&devp->tx_lock);
}

/**
 * @brief   Sets register values from a profile.
 *
 * @param[in]   devp        Pointer to the @p AX5043Driver object.
 * @param[in]   profile     Pointer to the @p ax5043_profile_t list of register values.
 *
 * @api
 */
void ax5043SetProfile(AX5043Driver *devp, const ax5043_profile_t *profile) {
    ax5043_state_t prev_state;
    bool prev_chan;

    osalDbgCheck(devp != NULL && devp->config != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043SetProfile(), invalid state");

    devp->profile = profile;

    /* Record previous state and enter idle state */
    prev_state = devp->state;
    prev_chan = ax5043ReadU8(devp, AX5043_REG_PLLLOOP) & AX5043_PLLLOOP_FREQSEL;
    ax5043Idle(devp);

    /* Set all profile values */
    for (const ax5043_profile_t *entry = profile; entry->reg; entry++) {
        switch (entry->len) {
        case 1:
            ax5043WriteU8(devp, entry->reg, entry->val);
            break;
        case 2:
            ax5043WriteU16(devp, entry->reg, entry->val);
            break;
        case 3:
            ax5043WriteU24(devp, entry->reg, entry->val);
            break;
        case 4:
            ax5043WriteU32(devp, entry->reg, entry->val);
            break;
        default:
            break;
        }
    }

    /* Re-range frequencies in case they changed */
    ax5043SetFreq(devp, 0, devp->vcorb, true);
    ax5043SetFreq(devp, 0, devp->vcora, false);

    /* Return to original state */
    switch (prev_state) {
    case AX5043_RX:
        ax5043RX(devp, prev_chan, false);
        break;
    case AX5043_WOR:
        ax5043RX(devp, prev_chan, true);
        break;
    case AX5043_READY:
    default:
        ax5043Idle(devp);
    }
}

/**
 * @brief   Gets the currently active profile.
 *
 * @param[in]   devp        Pointer to the @p AX5043Driver object.
 *
 * @return                  Pointer to the current profile.
 * @api
 */
const ax5043_profile_t *ax5043GetProfile(AX5043Driver *devp) {
    return devp->profile;
}

/**
 * @brief   Sets Carrier Frequency on an AX5043 device.
 *
 * @param[in]  devp         Pointer to the @p AX5043Driver object.
 * @param[in]  freq         Carrier frequency in Hz. If 0, ranges existing reg value.
 * @param[in]  vcor         VCO Range value. Set to 0 if unknown.
 * @param[in]  chan_b       Set channel B frequency if true, channel A otherwise.
 *
 * @return                  Corrected VCOR for given frequency.
 * @api
 */
uint8_t ax5043SetFreq(AX5043Driver *devp, uint32_t freq, uint8_t vcor, bool chan_b) {
    ax5043_state_t prev_state;
    bool prev_chan;

    uint16_t freq_reg = (chan_b ? AX5043_REG_FREQB : AX5043_REG_FREQA);
    uint16_t rng_reg = (chan_b ? AX5043_REG_PLLRANGINGB : AX5043_REG_PLLRANGINGA);

    osalDbgCheck(devp != NULL && devp->config != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043SetFreq(), invalid state");
    osalDbgAssert((freq >= AX5043_RFDIV_DIV1_MIN && freq <= AX5043_RFDIV_DIV1_MAX) ||
                  (freq >= AX5043_RFDIV_DIV2_MIN && freq <= AX5043_RFDIV_DIV2_MAX) ||
                   freq == 0, "ax5043SetFreq(), frequency out of bounds");

    devp->error = AX5043_ERR_NOERROR;

    /* Record previous state and enter idle state */
    prev_state = devp->state;
    prev_chan = ax5043ReadU8(devp, AX5043_REG_PLLLOOP) & AX5043_PLLLOOP_FREQSEL;
    ax5043Idle(devp);

    /* If no VCOR specified, default to 8 */
    if (vcor == 0) {
        vcor = 8;
    }

    /* Enter Standby mode */
    ax5043SetPWRMode(devp, AX5043_PWRMODE_STANDBY);

    /* Wait for XTAL */
    ax5043WaitIRQ(devp, AX5043_IRQ_XTALREADY, TIME_INFINITE);

    /* Set frequencies
     * We first find the GCD of the two frequencies in order to reduce them
     * as much as possible before doing the calculations.
     * NOTE: The programming manual recommends always setting bit 0
     *
     * REG = f_carrier * 2^24 / f_xtal + 1/2
     *     = (f_carrier * 2^25 + f_xtal) / (f_xtal * 2)
     */

    /* Set Frequency Selection */
    uint8_t pllloop = ax5043ReadU8(devp, AX5043_REG_PLLLOOP);
    if (chan_b) {
        pllloop |= AX5043_PLLLOOP_FREQSEL;
    } else {
        pllloop &= ~AX5043_PLLLOOP_FREQSEL;
    }
    ax5043WriteU8(devp, AX5043_REG_PLLLOOP, pllloop);

    /* Set the frequency and RFDIV if needed, and initiate ranging */
    if (freq) {
        ax5043WriteU32(devp, freq_reg, AX5043_FREQ_TO_REG(freq, devp->config->xtal_freq));
    } else {
        freq = AX5043_REG_TO_FREQ(ax5043ReadU32(devp, freq_reg), devp->config->xtal_freq);
    }
    ax5043SetRFDIV(devp, freq);
    ax5043WriteU8(devp, rng_reg, _VAL2FLD(AX5043_PLLRANGING_VCOR, vcor) | AX5043_PLLRANGING_RNGSTART);
    ax5043WaitIRQ(devp, AX5043_IRQ_PLLRNGDONE, TIME_INFINITE);
    vcor = ax5043ReadU8(devp, rng_reg);
    if (vcor & AX5043_PLLRANGING_RNGERR) {
        devp->error = AX5043_ERR_RANGING;
    }
    vcor = _FLD2VAL(AX5043_PLLRANGING_VCOR, vcor);
    if (chan_b) {
        devp->vcorb = vcor;
    } else {
        devp->vcora = vcor;
    }

    /* Return to original state */
    switch (prev_state) {
    case AX5043_RX:
        ax5043RX(devp, prev_chan, false);
        break;
    case AX5043_WOR:
        ax5043RX(devp, prev_chan, true);
        break;
    case AX5043_READY:
    default:
        ax5043Idle(devp);
    }

    return vcor;
}

/**
 * @brief   Gets the current frequency.
 *
 * @param[in]   devp        Pointer to the @p AX5043Driver object.
 *
 * @return                  The frequency in Hz.
 * @api
 */
uint32_t ax5043GetFreq(AX5043Driver *devp) {
    bool chan = ax5043ReadU8(devp, AX5043_REG_PLLLOOP) & AX5043_PLLLOOP_FREQSEL;
    uint16_t freq_reg = (chan ? AX5043_REG_FREQB : AX5043_REG_FREQA);

    return AX5043_REG_TO_FREQ(ax5043ReadU32(devp, freq_reg), devp->config->xtal_freq);
}

/**
 * @brief   Sets Preamble pointer and length for AX5043 transmission  operations.
 *
 * @param[in]  devp         Pointer to the @p AX5043Driver object.
 * @param[in]  preamble     Pointer to the preamble buffer.
 * @param[in]  len          Length of the buffer.
 *
 * @api
 */
void ax5043SetPreamble(AX5043Driver *devp, const void *preamble, size_t len) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert(len <= AX5043_FIFO_SIZE, "ax5043SetPreamble(), Preamble length exceeds max FIFO size");

    devp->preamble = preamble;
    devp->preamble_len = len;
}

/**
 * @brief   Gets the currently active preamble.
 *
 * @param[in]   devp        Pointer to the @p AX5043Driver object.
 *
 * @return                  Pointer to the current preamble.
 * @api
 */
const void *ax5043GetPreamble(AX5043Driver *devp) {
    return devp->preamble;
}

/**
 * @brief   Sets Postamble pointer and length for AX5043 transmission operations.
 *
 * @param[in]  devp         Pointer to the @p AX5043Driver object.
 * @param[in]  postamble    Pointer to the postamble buffer.
 * @param[in]  len          Length of the buffer.
 *
 * @api
 */
void ax5043SetPostamble(AX5043Driver *devp, const void *postamble, size_t len) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert(len <= AX5043_FIFO_SIZE, "ax5043SetPostamble(), Postamble length exceeds max FIFO size");

    devp->postamble = postamble;
    devp->postamble_len = len;
}

/**
 * @brief   Gets the currently active postamble.
 *
 * @param[in]   devp        Pointer to the @p AX5043Driver object.
 *
 * @return                  Pointer to the current postamble.
 * @api
 */
const void *ax5043GetPostamble(AX5043Driver *devp) {
    return devp->postamble;
}

/**
 * @brief   Perform a long (16-bit address) exchange with an AX5043 device.
 * @note    Can be called with NULL values for txbuf and/or rxbuf.
 * @note    A maximum of 256 bytes can be transferred at a time using this function.
 *
 * @param[in]   devp        Pointer to the @p AX5043Driver object
 * @param[in]   reg         Register address
 * @param[in]   write       Indicates Read/Write bit
 * @param[in]   txbuf       Buffer to send data from
 * @param[out]  rxbuf       Buffer to return data in
 * @param[in]   n           Number of bytes to exchange
 *
 * @return                  AX5043 status bits
 * @api
 */
ax5043_status_t ax5043Exchange(AX5043Driver *devp, uint16_t reg, bool write, const void *txbuf, void *rxbuf, size_t n) {
    SPIDriver *spip = NULL;
    ax5043_status_t status = 0;

    osalDbgCheck(devp != NULL && devp->config != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043Exchange(), invalid state");

#if AX5043_USE_SPI
    spip = devp->config->spip;
#if AX5043_SHARED_SPI
    spiAcquireBus(spip);
    spiStart(spip, devp->config->spicfg);
#endif /* AX5043_SHARED_SPI */

    spiSelect(spip);
    while (!palReadLine(devp->config->miso));
    status = ax5043SPIExchange(spip, reg, write, txbuf, rxbuf, n);
    spiUnselect(spip);

#if AX5043_SHARED_SPI
    spiReleaseBus(spip);
#endif /* AX5043_SHARED_SPI */
#endif /* AX5043_USE_SPI */

    return status;
}

/**
 * @brief   Gets the status of the AX5043 device.
 *
 * @param[in]   devp        Pointer to the @p AX5043Driver object.
 *
 * @return                  AX5043 status bits
 * @api
 */
ax5043_status_t ax5043GetStatus(AX5043Driver *devp) {
    SPIDriver *spip = NULL;
    ax5043_status_t status = 0;

    osalDbgCheck(devp != NULL && devp->config != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043GetStatus(), invalid state");

#if AX5043_USE_SPI
    spip = devp->config->spip;
#if AX5043_SHARED_SPI
    spiAcquireBus(spip);
    spiStart(spip, devp->config->spicfg);
#endif /* AX5043_SHARED_SPI */

    spiSelect(spip);
    while (!palReadLine(devp->config->miso));
    spiReceive(spip, 2, &status);
    spiUnselect(spip);

#if AX5043_SHARED_SPI
    spiReleaseBus(spip);
#endif /* AX5043_SHARED_SPI */
#endif /* AX5043_USE_SPI */

    return __REVSH(status);
}

/**
 * @brief   Read a uint8_t value from a register
 *
 * @param[in]   devp        Pointer to the @p AX5043Driver object.
 * @param[in]   reg         Register address
 *
 * @return                  The value in the register
 * @api
 */
uint8_t ax5043ReadU8(AX5043Driver *devp, uint16_t reg) {
    uint8_t value;

    osalDbgCheck(devp != NULL && devp->config != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043ReadU8(), invalid state");

    ax5043Exchange(devp, reg, false, NULL, &value, 1);

    return value;
}

/**
 * @brief   Read a uint16_t value from a register
 *
 * @param[in]   devp        Pointer to the @p AX5043Driver object.
 * @param[in]   reg         Register address
 *
 * @return                  The value in the register
 * @api
 */
uint16_t ax5043ReadU16(AX5043Driver *devp, uint16_t reg) {
    uint16_t value;

    osalDbgCheck(devp != NULL && devp->config != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043ReadU16(), invalid state");

    ax5043Exchange(devp, reg, false, NULL, (uint8_t*)&value, 2);

    return __REVSH(value);
}

/**
 * @brief   Read a uint32_t value from a 24-bit register
 *
 * @param[in]   devp        Pointer to the @p AX5043Driver object.
 * @param[in]   reg         Register address
 *
 * @return                  The value in the register
 * @api
 */
uint32_t ax5043ReadU24(AX5043Driver *devp, uint16_t reg) {
    uint32_t value;

    osalDbgCheck(devp != NULL && devp->config != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043ReadU32(), invalid state");

    ax5043Exchange(devp, reg, false, NULL, (uint8_t*)&value, 3);

    return __REV(value << 8);
}

/**
 * @brief   Read a uint32_t value from a register
 *
 * @param[in]   devp        Pointer to the @p AX5043Driver object.
 * @param[in]   reg         Register address
 *
 * @return                  The value in the register
 * @api
 */
uint32_t ax5043ReadU32(AX5043Driver *devp, uint16_t reg) {
    uint32_t value;

    osalDbgCheck(devp != NULL && devp->config != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043ReadU32(), invalid state");

    ax5043Exchange(devp, reg, false, NULL, (uint8_t*)&value, 4);

    return __REV(value);
}

/**
 * @brief   Write a uint8_t value to a register
 *
 * @param[in]   devp        Pointer to the @p AX5043Driver object.
 * @param[in]   reg         Register address
 * @param[in]   value       Register value
 *
 * @api
 */
void ax5043WriteU8(AX5043Driver *devp, uint16_t reg, uint8_t value) {
    osalDbgCheck(devp != NULL && devp->config != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043WriteU8(), invalid state");

    ax5043Exchange(devp, reg, true, &value, NULL, 1);
}

/**
 * @brief   Write a uint16_t value to a register
 *
 * @param[in]   devp        Pointer to the @p AX5043Driver object.
 * @param[in]   reg         Register address
 * @param[in]   value       Register value
 *
 * @api
 */
void ax5043WriteU16(AX5043Driver *devp, uint16_t reg, uint16_t value) {
    osalDbgCheck(devp != NULL && devp->config != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043WriteU8(), invalid state");

    value = __REVSH(value);
    ax5043Exchange(devp, reg, true, (uint8_t*)&value, NULL, 2);
}

/**
 * @brief   Write a uint32_t value to a 24-bit register
 *
 * @param[in]   devp        Pointer to the @p AX5043Driver object.
 * @param[in]   reg         Register address
 * @param[in]   value       Register value
 *
 * @api
 */
void ax5043WriteU24(AX5043Driver *devp, uint16_t reg, uint32_t value) {
    osalDbgCheck(devp != NULL && devp->config != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043WriteU8(), invalid state");

    value = __REV(value) >> 8;
    ax5043Exchange(devp, reg, true, (uint8_t*)&value, NULL, 3);
}

/**
 * @brief   Write a uint32_t value to a register
 *
 * @param[in]   devp        Pointer to the @p AX5043Driver object.
 * @param[in]   reg         Register address
 * @param[in]   value       Register value
 *
 * @api
 */
void ax5043WriteU32(AX5043Driver *devp, uint16_t reg, uint32_t value) {
    osalDbgCheck(devp != NULL && devp->config != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043WriteU32(), invalid state");

    value = __REV(value);
    ax5043Exchange(devp, reg, true, (uint8_t*)&value, NULL, 4);
}

/** @} */
