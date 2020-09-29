/**
 * @file    ax5043.c
 * @brief   AX5043 Radio.
 *
 * @addtogroup AX5043
 * @ingrup ORESAT
 * @{
 */
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "ch.h"
#include "hal.h"
#include "ax5043.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/**
 * @brief   ChibiOS Event masks for AX5043.
 */
#define AX5043_EVENT_IRQ                    EVENT_MASK(0)
#define AX5043_EVENT_TERMINATE              EVENT_MASK(1)

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
        uint8_t         data[256];
    };
    uint8_t             buf[256 + sizeof(uint16_t)];
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
ax5043_status_t ax5043SPIExchange(SPIDriver *spip, uint16_t reg, bool write, const uint8_t *txbuf, uint8_t *rxbuf, size_t n) {
    spibuf_t sendbuf;
    spibuf_t recvbuf;

    /* Ensure we don't exceed 256 bytes of data */
    n = (n <= 256 ? n : 256);

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
 * @brief   FIFO worker thread for handling AX5043 data.
 *
 * @param[in]   arg         Pointer to the @p AX5043Driver object
 *
 * @notapi
 */
THD_FUNCTION(fifo_worker, arg) {
    AX5043Driver *devp = arg;
    ax5043_mailbox_t *mbp = NULL;
    ax5043_chunk_t *chunkp = NULL;
    uint8_t buf[256];
    size_t fifo_len;

    osalDbgCheck(devp != NULL);

    while (!chThdShouldTerminateX()) {
        if (devp->state == AX5043_RX) {
            /* Wait for FIFO data */
            if (ax5043WaitIRQ(devp, AX5043_IRQ_FIFONOTEMPTY, TIME_INFINITE) & AX5043_EVENT_TERMINATE) {
                continue;
            }

            /* Get data from FIFO */
            fifo_len = ax5043ReadU16(devp, AX5043_REG_FIFOCOUNT);
            ax5043Exchange(devp, AX5043_REG_FIFODATA, false, NULL, buf, fifo_len);

            /* Decode chunks */
            size_t pos = 0;
            size_t chunk_len = 0;;
            while (pos != fifo_len) {
                /* Set chunk pointer to base of next chunk */
                chunkp = (ax5043_chunk_t*)&buf[pos];
                /* Determine chunk length */
                if (_FLD2VAL(AX5043_FIFOCHUNK_SIZE, chunkp->header) == 0x7U) {
                    chunk_len = chunkp->length;
                    pos += chunk_len + 2;
                } else {
                    chunk_len = _FLD2VAL(AX5043_FIFOCHUNK_SIZE, chunkp->header);
                    pos += chunk_len + 1;
                }
                /* Process chunk */
                switch (_FLD2VAL(AX5043_FIFOCHUNK_CMD, chunkp->header)) {
                case AX5043_CHUNKCMD_DATA:
                    /* TODO: Handle error flags */
                    /* Start of new packet */
                    if (chunkp->data.flags & AX5043_CHUNK_DATARX_PKTSTART) {
                        /* Acquire mailbox if needed */
                        if (mbp == NULL) {
                            chMBFetchTimeout(&devp->mb_free, (msg_t*)&mbp, TIME_INFINITE);
                        }
                        mbp->index = 0;
                    }

                    /* Copy packet data */
                    osalDbgAssert(mbp != NULL, "fifo_worker(),  NULL mailbox");
                    if (mbp->index + chunk_len >= AX5043_MAILBOX_SIZE) {
                        chSysLock();
                        chMBPostI(&devp->mb_filled, (msg_t)mbp);
                        chSysUnlock();
                        chMBFetchTimeout(&devp->mb_free, (msg_t*)&mbp, TIME_INFINITE);
                        mbp->index = 0;
                    }
                    memcpy(&mbp->data[mbp->index], chunkp->data.data, chunk_len);
                    mbp->index += chunk_len;

                    /* End of packet */
                    if (chunkp->data.flags & AX5043_CHUNK_DATARX_PKTEND) {
                        chSysLock();
                        chMBPostI(&devp->mb_filled, (msg_t)mbp);
                        chSysUnlock();
                        mbp = NULL;
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
                    if (chunk_len == 2) {
                        devp->ant0rssi = chunkp->antrssi2.rssi;
                        devp->bgndnoise = chunkp->antrssi2.bgndnoise;
                    } else if (chunk_len == 3) {
                        devp->ant0rssi = chunkp->antrssi3.ant0rssi;
                        devp->ant1rssi = chunkp->antrssi3.ant1rssi;
                        devp->bgndnoise = chunkp->antrssi3.bgndnoise;
                    }
                    break;
                default:
                    break;
                }
                pos += chunk_len;
            }
        } else if (devp->state == AX5043_TX) {
            /* Wait for free space in FIFO */
            if (ax5043WaitIRQ(devp, AX5043_IRQ_FIFOTHRFREE, TIME_INFINITE) & AX5043_EVENT_TERMINATE) {
                continue;
            }

            /* Get free space */
            fifo_len = ax5043ReadU16(devp, AX5043_REG_FIFOFREE);

            /* Copy data. If no data, terminate TX */
            fifo_len = devp->tx_cb(buf, fifo_len);
            if (fifo_len == 0) {
                break;
            }

            /* Write to FIFO */
            ax5043Exchange(devp, AX5043_REG_FIFODATA, true, buf, NULL, fifo_len);
            ax5043WriteU8(devp, AX5043_REG_FIFOSTAT, AX5043_FIFOCMD_COMMIT);
        } else {
            break;
        }
    }

    if (mbp != NULL) {
        chSysLock();
        chMBPostI(&devp->mb_free, (msg_t)mbp);
        chSysUnlock();
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

/*==========================================================================*/
/* Interface implementation.                                                */
/*==========================================================================*/

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

    devp->irq_worker = NULL;
    chEvtObjectInit(&devp->irq_event);

    devp->fifo_worker = NULL;

    chMBObjectInit(&devp->mb_filled, devp->mb_filled_queue, AX5043_MAILBOX_COUNT);
    chMBObjectInit(&devp->mb_free, devp->mb_free_queue, AX5043_MAILBOX_COUNT);
    chSysLock();
    for (uint32_t i = 0; i < AX5043_MAILBOX_COUNT; i++) {
        chMBPostI(&devp->mb_free, (msg_t)&devp->mb_buf[i]);
    }
    chSysUnlock();

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
        devp->irq_worker = chThdCreateFromHeap(NULL, 0x1000, "ax5043_irq_worker", HIGHPRIO, irq_worker, devp);
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
        ax5043SetPWRMode(devp, AX5043_PWRMODE_POWERDOWN);
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

        /* Disable the interrupt handler and worker thread */
        palDisableLineEvent(devp->config->irq);
        palSetLineCallback(devp->config->irq, NULL, NULL);
        chThdTerminate(devp->irq_worker);
        chEvtSignal(devp->irq_worker, AX5043_EVENT_TERMINATE);
        chThdWait(devp->irq_worker);
        devp->irq_worker = NULL;
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
        if (devp->fifo_worker) {
            chThdTerminate(devp->fifo_worker);
            chEvtSignal(devp->fifo_worker, AX5043_EVENT_TERMINATE);
            chThdWait(devp->fifo_worker);
            devp->fifo_worker = NULL;
        }

        ax5043SetPWRMode(devp, AX5043_PWRMODE_POWERDOWN);

        devp->state = AX5043_READY;
    }
}

/**
 * @brief   Puts AX5043 into receive mode.
 *
 * @param[in]  devp         Pointer to the @p AX5043Driver object.
 *
 * @api
 */
void ax5043RX(AX5043Driver *devp, bool chan_b) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert(((devp->state == AX5043_READY) ||
                   (devp->state == AX5043_RX) ||
                   (devp->state == AX5043_WOR) ||
                   (devp->state == AX5043_TX)), "ax5043RX(), invalid state");

    bool cur_chan = ax5043ReadU8(devp, AX5043_REG_PLLLOOP) & AX5043_PLLLOOP_FREQSEL;

    if (devp->state != AX5043_RX || chan_b != cur_chan) {
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
        ax5043WriteU16(devp, AX5043_REG_FIFOTHRESH, 128);

        /* Activate RX */
        ax5043SetPWRMode(devp, AX5043_PWRMODE_RX_FULL);
        devp->state = AX5043_RX;

        /* Start the FIFO worker */
        devp->fifo_worker = chThdCreateFromHeap(NULL, 0x1000, "ax5043_fifo_worker", HIGHPRIO-1, fifo_worker, devp);
    }
}

/**
 * @brief   Puts AX5043 into wake-on-radio mode.
 *
 * @param[in]  devp         Pointer to the @p AX5043Driver object.
 *
 * @api
 */
void ax5043WOR(AX5043Driver *devp, bool chan_b) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert(((devp->state == AX5043_READY) ||
                   (devp->state == AX5043_RX) ||
                   (devp->state == AX5043_WOR) ||
                   (devp->state == AX5043_TX)), "ax5043WOR(), invalid state");

    bool cur_chan = ax5043ReadU8(devp, AX5043_REG_PLLLOOP) & AX5043_PLLLOOP_FREQSEL;

    if (devp->state != AX5043_WOR || chan_b != cur_chan) {
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
        ax5043WriteU16(devp, AX5043_REG_FIFOTHRESH, 128);

        ax5043SetPWRMode(devp, AX5043_PWRMODE_RX_WOR);
        devp->state = AX5043_WOR;

        devp->fifo_worker = chThdCreateFromHeap(NULL, 0x400, "ax5043_fifo_worker", HIGHPRIO-1, fifo_worker, devp);
    }
}

/**
 * @brief   Puts AX5043 into transmit mode and transmits a packet.
 *
 * @param[in]  devp         Pointer to the @p AX5043Driver object.
 * @param[in]  tx_cb        Transmit FIFO fill callback.
 *
 * TODO: This still needs preamble code
 * @api
 */
void ax5043TX(AX5043Driver *devp, ax5043_tx_cb_t tx_cb, bool chan_b) {
    ax5043_state_t prev_state;
    bool prev_chan;
    osalDbgCheck(devp != NULL && tx_cb != NULL);
    osalDbgAssert(((devp->state == AX5043_READY) ||
                   (devp->state == AX5043_RX) ||
                   (devp->state == AX5043_WOR) ||
                   (devp->state == AX5043_TX)), "ax5043TX(), invalid state");

    devp->error = AX5043_ERR_NOERROR;
    devp->tx_cb = tx_cb;

    /* Record previous state */
    prev_state = devp->state;
    prev_chan = ax5043ReadU8(devp, AX5043_REG_PLLLOOP) & AX5043_PLLLOOP_FREQSEL;

    /* Enter idle state first */
    ax5043Idle(devp);

    /* Set Frequency Selection */
    uint8_t pllloop = ax5043ReadU8(devp, AX5043_REG_PLLLOOP);
    if (chan_b) {
        pllloop |= AX5043_PLLLOOP_FREQSEL;
    } else {
        pllloop &= ~AX5043_PLLLOOP_FREQSEL;
    }
    ax5043WriteU8(devp, AX5043_REG_PLLLOOP, pllloop);

    /* Activate synthesizer to lock PLL */
    ax5043SetPWRMode(devp, AX5043_PWRMODE_TX_SYNTH);
    chThdSleepMicroseconds(1);
    if (!(ax5043GetStatus(devp) & AX5043_STATUS_PLL_LOCK)) {
        ax5043SetPWRMode(devp, AX5043_PWRMODE_POWERDOWN);
        devp->error = AX5043_ERR_LOCKLOST;
        return;
    }
    /* Clear FIFO and set threshold */
    ax5043WriteU8(devp, AX5043_REG_FIFOSTAT, AX5043_FIFOCMD_CLEAR_FIFODAT);
    ax5043WriteU16(devp, AX5043_REG_FIFOTHRESH, 128);

    /* Activate TX */
    ax5043SetPWRMode(devp, AX5043_PWRMODE_TX_FULL);
    devp->state = AX5043_TX;

    /* Start the FIFO worker */
    devp->fifo_worker = chThdCreateFromHeap(NULL, 0x1000, "ax5043_fifo_worker", HIGHPRIO-1, fifo_worker, devp);

    /* Wait for transmission to finish */
    chThdWait(devp->fifo_worker);
    devp->fifo_worker = NULL;
    devp->tx_cb = NULL;

    /* Return to original state */
    switch (prev_state) {
    case AX5043_RX:
        ax5043RX(devp, prev_chan);
        break;
    case AX5043_WOR:
        ax5043WOR(devp, prev_chan);
        break;
    case AX5043_READY:
    default:
        ax5043Idle(devp);
    }
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
    osalDbgCheck(devp != NULL && devp->config != NULL);
    osalDbgAssert((devp->state == AX5043_READY), "ax5043SetProfile(), invalid state");

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
}

/**
 * @brief   Sets Carrier Frequency on an AX5043 device.
 *
 * @param[in]  devp         Pointer to the @p AX5043Driver object.
 * @param[in]  freq         Carrier frequency in Hz. If 0, ranges existing reg value.
 * @param[in]  vcor         VCO Range value. Set to 0 if unknown.
 * @param[in]  chan_b       Set channel B frequency if true, channel A otherwise.
 *
 * @return                  Corrected VCOR for given frequency
 * @api
 */
uint8_t ax5043SetFreq(AX5043Driver *devp, uint32_t freq, uint8_t vcor, bool chan_b) {
    uint16_t freq_reg = (chan_b ? AX5043_REG_FREQB : AX5043_REG_FREQA);
    uint16_t rng_reg = (chan_b ? AX5043_REG_PLLRANGINGB : AX5043_REG_PLLRANGINGA);

    osalDbgCheck(devp != NULL && devp->config != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043SetFreq(), invalid state");
    osalDbgAssert((freq >= AX5043_RFDIV_DIV1_MIN && freq <= AX5043_RFDIV_DIV1_MAX) ||
                  (freq >= AX5043_RFDIV_DIV2_MIN && freq <= AX5043_RFDIV_DIV2_MAX) ||
                   freq == 0, "ax5043SetFreq(), frequency out of bounds");

    devp->error = AX5043_ERR_NOERROR;

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

    ax5043SetPWRMode(devp, AX5043_PWRMODE_POWERDOWN);

    return vcor;
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
ax5043_status_t ax5043Exchange(AX5043Driver *devp, uint16_t reg, bool write, const uint8_t *txbuf, uint8_t *rxbuf, size_t n) {
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

/*===========================*/
/* TODO: START OVERHAUL HERE */
/*===========================*/

/*
 * TODO: Switch to direct register configuration, use structs
 */
/**
 * @brief   Gets AX5043 configuration values from the AX5043 driver structure.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 * @param[in]  conf_name          configuration variable name.
 *
 * @return                        value in configuration variable.
 *
 * @api
 */
uint32_t ax5043_get_conf_val(AX5043Driver *devp, uint8_t conf_name) {
    int i = 0;

    osalDbgCheck(devp != NULL && devp->config != NULL);
    /* TODO: Add state sanity check */
    /*osalDbgAssert((devp->state == AX5043_READY) ||, "ax5043_get_conf_val(), invalid state");*/

    ax5043_confval_t* entry = devp->config->conf_values;
    while (entry[i].conf_name != AX5043_PHY_END) {
        if (entry[i].conf_name == conf_name){
            return entry[i].val;
        }
        i++;
    }
    devp->error = AX5043_ERR_VAL_NOT_IN_CONF;
    return 0;
}

/**
 * @brief   Sets AX5043 configuration values from the AX5043 driver structure.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 * @param[in]  conf_name          configuration variable name.
 * @param[in]  value              value in configuration variable.
 *
 * @return                        0 if successful, else 0x11.
 * @api
 */
uint8_t ax5043_set_conf_val(AX5043Driver *devp, uint8_t conf_name, uint32_t value) {
    int i = 0;

    osalDbgCheck(devp != NULL && devp->config != NULL);
    /* TODO: Add state sanity check */
    /*osalDbgAssert((devp->state == AX5043_READY) ||, "ax5043_set_conf_val(), invalid state");*/

    ax5043_confval_t* entry = devp->config->conf_values;
    while (entry[i].conf_name != AX5043_PHY_END) {
        if (entry[i].conf_name == conf_name){
            entry[i].val = value;
            return 0;
        }
        i++;
    }
    devp->error = AX5043_ERR_VAL_NOT_IN_CONF;
    return AX5043_ERR_VAL_NOT_IN_CONF;
}

/**
 * @brief   Transmit loop to transmit bytes of a packet.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 * @param[in]  packet_len         Complete packet length including mac.
 * @param[in]  axradio_txbuffer   pointer to packet.
 * @param[in]  packet_bytes_sent length before the packet.
 *
 * @api
 * TODO Standardize the error handling, remove packet_bytes_sent, simplify the code.
 */
void transmit_loop(AX5043Driver *devp, uint16_t packet_len,uint8_t axradio_txbuffer[]){
    uint8_t free_fifo_bytes;
    uint8_t packet_end_indicator = 0;
    uint16_t packet_bytes_sent = 0;
    uint8_t flags = 0;
    uint16_t packet_len_to_be_sent = 0;
    uint8_t synclen = ax5043_get_conf_val(devp, AX5043_FRAMING_SYNCLEN);

    while (packet_end_indicator == 0) {
        if (ax5043ReadU8(devp,AX5043_REG_FIFOFREE1))
            free_fifo_bytes = 0xff;
        else
            free_fifo_bytes = ax5043ReadU8(devp,AX5043_REG_FIFOFREE0);
        /* Make sure sixteen bytes in FIFO are free. We can do with minimum 4 bytes free but taking in 16 here */
        if (free_fifo_bytes < 19) {
            /* FIFO commit */
            ax5043WriteU8(devp,AX5043_REG_FIFOSTAT, 4);
            continue;
        }

        switch (devp->state) {
        case AX5043_TX_LONGPREAMBLE:
            if (!packet_bytes_sent) {
                devp->state = AX5043_TX_SHORTPREAMBLE;
                packet_bytes_sent = ax5043_get_conf_val(devp, AX5043_PHY_PREAMBLE_LEN);
                break;
            }

            free_fifo_bytes = 7;
            if (packet_bytes_sent < 7)
                free_fifo_bytes = packet_bytes_sent;
            packet_bytes_sent -= free_fifo_bytes;
            free_fifo_bytes <<= 5;
            ax5043WriteU8(devp,AX5043_REG_FIFODATA, AX5043_CHUNKCMD_REPEATDATA | _VAL2FLD(AX5043_FIFOCHUNK_SIZE, 3));
            ax5043WriteU8(devp,AX5043_REG_FIFODATA, ax5043_get_conf_val(devp, AX5043_PHY_PREAMBLE_FLAGS));
            ax5043WriteU8(devp,AX5043_REG_FIFODATA, free_fifo_bytes);
            ax5043WriteU8(devp,AX5043_REG_FIFODATA, ax5043_get_conf_val(devp, AX5043_PHY_PREAMBLE_BYTE));
            break;

        case AX5043_TX_SHORTPREAMBLE:
            if (!packet_bytes_sent) {
                uint8_t preamble_appendbits = ax5043_get_conf_val(devp, AX5043_PHY_PREAMBLE_APPENDBITS);
                if (preamble_appendbits) {
                    uint8_t byte;
                    ax5043WriteU8(devp,AX5043_REG_FIFODATA, AX5043_CHUNKCMD_DATA | _VAL2FLD(AX5043_FIFOCHUNK_SIZE, 2));
                    ax5043WriteU8(devp,AX5043_REG_FIFODATA, 0x1C);
                    byte = ax5043_get_conf_val(devp, AX5043_PHY_PREAMBLE_APPENDPATTERN);
                    if (ax5043ReadU8(devp,AX5043_REG_PKTADDRCFG) & 0x80) {
                        // msb first -> stop bit below
                        byte &= 0xFF << (8-preamble_appendbits);
                        byte |= 0x80 >> preamble_appendbits;
                    } else {
                        // lsb first -> stop bit above
                        byte &= 0xFF >> (8-preamble_appendbits);
                        byte |= 0x01 << preamble_appendbits;
                    }
                    ax5043WriteU8(devp,AX5043_REG_FIFODATA, byte);
                }
                if (_FLD2VAL(AX5043_FRAMING_FRMMODE, ax5043ReadU8(devp,AX5043_REG_FRAMING)) == AX5043_FRMMODE_RAW_PATMATCH && synclen) {
                    /* Write SYNC word if framing mode is raw_patternmatch, might use SYNCLEN > 0 as a criterion, but need to make sure SYNCLEN=0 for WMBUS.
                       Chip automatically sends SYNCWORD but matching in RX works via MATCH0PAT) */
                    int8_t len_byte = synclen;
                    uint8_t i = (len_byte & 0x07) ? 0x04 : 0;
                    /* SYNCLEN in bytes, rather than bits. Ceiled to next integer e.g. fractional bits are counted as full bits */
                    len_byte += 7;
                    len_byte >>= 3;
                    ax5043WriteU8(devp,AX5043_REG_FIFODATA, AX5043_CHUNKCMD_DATA  | _VAL2FLD(AX5043_FIFOCHUNK_SIZE, (len_byte + 1)));
                    ax5043WriteU8(devp,AX5043_REG_FIFODATA, ax5043_get_conf_val(devp, AX5043_FRAMING_SYNCFLAGS) | i);

                    uint8_t syncword[4] = {ax5043_get_conf_val(devp, AX5043_FRAMING_SYNCWORD0),
                        ax5043_get_conf_val(devp, AX5043_FRAMING_SYNCWORD1),
                        ax5043_get_conf_val(devp, AX5043_FRAMING_SYNCWORD2),
                        ax5043_get_conf_val(devp, AX5043_FRAMING_SYNCWORD3)};
                    for (i = 0; i < len_byte; ++i) {
                        ax5043WriteU8(devp,AX5043_REG_FIFODATA, syncword[i]);
                    }
                }
                devp->state = AX5043_TX_PACKET;
                continue;
            }
            free_fifo_bytes = 255;
            if (packet_bytes_sent < 255*8)
                free_fifo_bytes = packet_bytes_sent >> 3;
            if (free_fifo_bytes) {
                packet_bytes_sent -= ((uint16_t)free_fifo_bytes) << 3;
                ax5043WriteU8(devp,AX5043_REG_FIFODATA, AX5043_CHUNKCMD_REPEATDATA | _VAL2FLD(AX5043_FIFOCHUNK_SIZE, 3));
                ax5043WriteU8(devp,AX5043_REG_FIFODATA, ax5043_get_conf_val(devp, AX5043_PHY_PREAMBLE_FLAGS));
                ax5043WriteU8(devp,AX5043_REG_FIFODATA, free_fifo_bytes);
                ax5043WriteU8(devp,AX5043_REG_FIFODATA, ax5043_get_conf_val(devp, AX5043_PHY_PREAMBLE_BYTE));
                continue;
            }
            {
                uint8_t byte = ax5043_get_conf_val(devp, AX5043_PHY_PREAMBLE_BYTE) ;
                free_fifo_bytes = packet_bytes_sent;
                packet_bytes_sent = 0;
                ax5043WriteU8(devp,AX5043_REG_FIFODATA, AX5043_CHUNKCMD_DATA | _VAL2FLD(AX5043_FIFOCHUNK_SIZE, 2));
                ax5043WriteU8(devp,AX5043_REG_FIFODATA, 0x1C);
                if (ax5043ReadU8(devp,AX5043_REG_PKTADDRCFG) & 0x80) {
                    /* MSB first -> stop bit below */
                    byte &= 0xFF << (8-free_fifo_bytes);
                    byte |= 0x80 >> free_fifo_bytes;
                } else {
                    // lsb first -> stop bit above
                    byte &= 0xFF >> (8-free_fifo_bytes);
                    byte |= 0x01 << free_fifo_bytes;
                }
                ax5043WriteU8(devp,AX5043_REG_FIFODATA, byte);
            }
            continue;

        case AX5043_TX_PACKET:
            flags = 0;
            packet_len_to_be_sent = 0;
            if (!packet_bytes_sent)
                /* Flag byte indicates packetstart */
                flags |= 0x01;

            packet_len_to_be_sent = packet_len - packet_bytes_sent;
            /* 3 bytes of FIFO commands are written before payload can be written to FIFO */
            if (free_fifo_bytes >= packet_len_to_be_sent + 3) {
                /* Flag byte indicates packet end */
                flags |= 0x02;
            }
            else{
                packet_len_to_be_sent = free_fifo_bytes - 3;
            }


            ax5043WriteU8(devp,AX5043_REG_FIFODATA, AX5043_CHUNKCMD_DATA | AX5043_CHUNKSIZE_VAR);
            /* Write FIFO chunk length byte. Length includes the flag byte, thus the +1 */
            ax5043WriteU8(devp,AX5043_REG_FIFODATA, packet_len_to_be_sent + 1);
            ax5043WriteU8(devp,AX5043_REG_FIFODATA, flags);
            ax5043Exchange(devp, AX5043_REG_FIFODATA, true, &axradio_txbuffer[packet_bytes_sent], NULL, packet_len_to_be_sent);
            packet_bytes_sent += packet_len_to_be_sent;
            if (flags & 0x02){
                packet_end_indicator = 1;
                /* Enable radio event done (REVRDONE) event */
                ax5043WriteU16(devp,AX5043_REG_RADIOEVENTMASK, AX5043_RADIOEVENT_DONE);
                ax5043WriteU8(devp,AX5043_REG_FIFOSTAT, 4); // commit
            }
            break;

        default:
            packet_end_indicator = 1;
            devp->error = AX5043_ERR_UNEXPECTED_STATE;
        }
    }
    devp->state = AX5043_TX;
}

/**
 * @brief   Transmits a packet.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 * @param[in]  addr               remote destination address of packet.
 * @param[in]  pkt                pointer to packet.
 * @param[in]  pktlen             packet length.
 *
 * @param[out] AX5043_ERR        Error code.
 *
 * @api
 * TODO Standardize the error handling, Maybe move address to a driver config structure
 */
uint8_t transmit_packet(AX5043Driver *devp, const struct axradio_address *addr, const uint8_t *pkt, uint16_t pktlen) {
    uint16_t packet_len;
    uint8_t axradio_txbuffer[260];

    uint8_t maclen = ax5043_get_conf_val(devp, AX5043_FRAMING_MACLEN);
    uint8_t destaddrpos = ax5043_get_conf_val(devp, AX5043_FRAMING_DESTADDRPOS);
    uint8_t addrlen = ax5043_get_conf_val(devp, AX5043_FRAMING_ADDRLEN);
    uint8_t sourceaddrpos = ax5043_get_conf_val(devp, AX5043_FRAMING_SOURCEADDRPOS);
    uint8_t lenmask = ax5043_get_conf_val(devp, AX5043_FRAMING_LENMASK);
    uint8_t lenoffs = ax5043_get_conf_val(devp, AX5043_FRAMING_LENOFFS);
    uint8_t lenpos = ax5043_get_conf_val(devp, AX5043_FRAMING_LENPOS);

    packet_len = pktlen + maclen;
    if (packet_len > sizeof(axradio_txbuffer))
        return AX5043_ERR_INVALID;

    /* Prepare the MAC segment of the packet */
    memset(axradio_txbuffer, 0, maclen);
    memcpy(&axradio_txbuffer[maclen], pkt, pktlen);
    if (destaddrpos != 0xff) {
        memcpy(&axradio_txbuffer[destaddrpos], &addr->addr, addrlen);
    }
    if (sourceaddrpos != 0xff) {
        uint32_t axradio_localaddr = __REV(devp->config->addr);
        memcpy(&axradio_txbuffer[sourceaddrpos], &axradio_localaddr, addrlen);
    }
    if (lenmask) {
        /* Calculate payload length and update the MAC of payload */
        uint8_t len_byte = (uint8_t)(packet_len - lenoffs) & lenmask;
        axradio_txbuffer[lenpos] = (axradio_txbuffer[lenpos] & (uint8_t)~lenmask) | len_byte;
    }
    /*Clear radioevent flag. This indicator is set when packet is out */
    ax5043ReadU16(devp,AX5043_REG_RADIOEVENTREQ);
    /* Clear leftover FIFO data & flags */
    ax5043WriteU8(devp, AX5043_REG_FIFOSTAT, 3);
    devp->state = AX5043_TX_LONGPREAMBLE;

    /*Code for 4-FSK mode */
    if ((ax5043ReadU8(devp,AX5043_REG_MODULATION) & 0x0F) == 9) {
        ax5043WriteU8(devp,AX5043_REG_FIFODATA, AX5043_CHUNKCMD_DATA | AX5043_CHUNKSIZE_VAR);
        /* Length including flags */
        ax5043WriteU8(devp,AX5043_REG_FIFODATA, 2);
        /* Flag PKTSTART -> dibit sync */
        ax5043WriteU8(devp,AX5043_REG_FIFODATA, 0x01);
        /* Dummy byte for forcing dibit sync */
        ax5043WriteU8(devp,AX5043_REG_FIFODATA, 0x11);
    }
    transmit_loop(devp, packet_len, axradio_txbuffer);
    ax5043SetPWRMode(devp, AX5043_PWRMODE_TX_FULL);

    /* Clear radio event register, enable DONE, and wait for interrupt */
    ax5043ReadU16(devp, AX5043_REG_RADIOEVENTREQ);
    ax5043WriteU16(devp, AX5043_REG_RADIOEVENTMASK, AX5043_RADIOEVENT_DONE);
    ax5043WaitIRQ(devp, AX5043_IRQ_RADIOCTRL, TIME_INFINITE);
    ax5043WriteU16(devp, AX5043_REG_RADIOEVENTMASK, 0x0000U);
    ax5043ReadU16(devp, AX5043_REG_RADIOEVENTREQ);

    ax5043WriteU16(devp,AX5043_REG_RADIOEVENTMASK, 0x0000U);
    devp->error = AX5043_ERR_NOERROR;
    return AX5043_ERR_NOERROR;
}

/** @} */
