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
/* TODO: Do we need these here? */
/**
 * @brief   Morse code for alphabets and numbers.
 */
static const char *alpha[] = {
    ".-",   //A
    "-...", //B
    "-.-.", //C
    "-..",  //D
    ".",    //E
    "..-.", //F
    "--.",  //G
    "....", //H
    "..",   //I
    ".---", //J
    "-.-",  //K
    ".-..", //L
    "--",   //M
    "-.",   //N
    "---",  //O
    ".--.", //P
    "--.-", //Q
    ".-.",  //R
    "...",  //S
    "-",    //T
    "..-",  //U
    "...-", //V
    ".--",  //W
    "-..-", //X
    "-.--", //Y
    "--..", //Z
};

static const char *num[] = {
    "-----", //0
    ".----", //1
    "..---", //2
    "...--", //3
    "....-", //4
    ".....", //5
    "-....", //6
    "--...", //7
    "---..", //8
    "----.", //9
};

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/
typedef union {
    struct __attribute__((packed)) {
        union {
            uint16_t    reg;
            uint16_t    status;
        };
        uint8_t         *data;
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
 * @pre     The SPI interface must be initialized and the driver started.
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
    sendbuf.reg = __REVSH((reg & 0x0FFF) | 0x7000 | (write << 16));

    /* Copy the TX data to the sending buffer */
    if (txbuf != NULL) {
        memcpy(sendbuf.data, txbuf, n);
    }

    /* Perform the exchange */
    /* We always receive because we need the status bits */
    spiSelect(spip);
    if (txbuf != NULL) {
        spiExchange(spip, n + sizeof(uint16_t), sendbuf.buf, recvbuf.buf);
    } else if (rxbuf != NULL) {
        spiReceive(spip, n + sizeof(uint16_t), recvbuf.buf);
    } else {
        /* Status only */
        spiReceive(spip, sizeof(uint16_t), recvbuf.buf);
    }
    spiUnselect(spip);

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

}

/**
 * @brief   Sets powermode register of AX5043.
 *
 * @param[in]  devp         Pointer to the @p AX5043Driver object.
 * @param[in]  pwrmode      Power mode register value.
 *
 * @return                  Most significant status bits (S14...S8)
 * @notapi
 */
ax5043_status_t ax5043SetPWRMode(AX5043Driver *devp, uint8_t pwrmode) {
    uint8_t regval = 0;

    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043SetPWRMode(), invalid state");

    ax5043Exchange(devp, AX5043_REG_PWRMODE, false, NULL, &regval, 1);
    regval &= ~AX5043_PWRMODE;
    regval |= _VAL2FLD(AX5043_PWRMODE, pwrmode);
    return ax5043Exchange(devp, AX5043_REG_PWRMODE, true, &regval, NULL, 1);
}

/*==========================================================================*/
/* Interface implementation.                                                */
/*==========================================================================*/

static const struct AX5043VMT vmt_device = {
    (size_t)0,
};

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
    devp->vmt = &vmt_device;

    devp->config = NULL;

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
    osalDbgAssert((devp->state == AX5043_STOP) ||
            (devp->state == AX5043_READY),
            "ax5043Start(), invalid state");

    devp->config = config;
    devp->error = AX5043_ERR_NOERROR;

    /* Register interrupt handler for device */
    palSetLineCallback(config->irq, ax5043IRQHandler, devp);
    palEnableLineEvent(config->irq, PAL_EVENT_MODE_RISING_EDGE);

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

    /* Transition to ready state */
    devp->state = AX5043_READY;

    /*===========================*/
    /* TODO: START OVERHAUL HERE */
    /*===========================*/

    /* TODO: What are these for exactly? */
    devp->rf_freq_off3 = 0;
    devp->rf_freq_off2 = 0;
    devp->rf_freq_off1 = 0;
    devp->rssi = 0;

    ax5043_set_regs_group(devp,common);
    ax5043_set_regs_group(devp,tx);

    /* TODO: Should this be configurable at runtime? */
    /* Configure PLL Loop for internal 100kHz filter, bypass external */
    ax5043WriteU8(devp, AX5043_REG_PLLLOOP, AX5043_PLLLOOP_DIRECT | _VAL2FLD(AX5043_PLLLOOP_FLT, AX5043_FLT_INTERN_100KHZ));
    /* Configure PLL Charge Pump Current for 68uA (8.5uA * 8) */
    ax5043WriteU8(devp, AX5043_REG_PLLCPI, 0x08);

    /* Enter Standby mode */
    ax5043SetPWRMode(devp, AX5043_PWRMODE_STANDBY);

    /* FSK */
    /* TODO: Make this configurable, not static in here */
    ax5043WriteU8(devp, AX5043_REG_MODULATION, AX5043_MODULATION_FSK);
    ax5043WriteU32(devp, AX5043_REG_FSKDEV, 0x000000);

    /* Wait for XTAL */
    while ((ax5043ReadU8(devp, AX5043_REG_XTALSTATUS) & 0x01) == 0){
        chThdSleepMilliseconds(1);
    }

    /* Set frequency */
    /* TODO: Make this configurable, not static in here */
    uint32_t f = __REVSH(ax5043_get_conf_val(devp, AX5043_PHY_CHANFREQ));
    ax5043WriteU32(devp, AX5043_REG_FREQA, f);

    /* PLL autoranging */
    uint8_t r;
    uint8_t pll_init_val = ax5043_get_conf_val(devp, AX5043_PHY_CHANPLLRNGINIT);
    if( !(pll_init_val & 0xF0) ) { // start values for ranging available
        r = pll_init_val | 0x10;
    }
    else {
        r = 0x18;
    }
    ax5043WriteU8(devp, AX5043_REG_PLLRANGINGA, r);
    chThdSleepMilliseconds(1);
    while ((ax5043ReadU8(devp, AX5043_REG_PLLRANGINGA) & 0x10) != 0)
    {
        chThdSleepMilliseconds(1);
    }
    int8_t value = ax5043ReadU8(devp, AX5043_REG_PLLRANGINGA);
    ax5043_set_conf_val(devp, AX5043_PHY_CHANPLLRNG, value);
    devp->state = AX5043_PLL_RANGE_DONE;

    ax5043SetPWRMode(devp, AX5043_PWRMODE_POWERDOWN);
    ax5043_set_regs_group(devp,common);
    ax5043_set_regs_group(devp,rx);

    uint8_t pll_val = ax5043_get_conf_val(devp, AX5043_PHY_CHANPLLRNG);
    ax5043WriteU8(devp, AX5043_REG_PLLRANGINGA, (pll_val & 0x0F));
    f = ax5043_get_conf_val(devp, AX5043_PHY_CHANFREQ);
    ax5043WriteU32(devp, AX5043_REG_FREQA, f);

    ax5043_set_regs_group(devp,local_address);
}

/**
 * @brief   Deactivates the AX5043 Radio Driver.
 *
 * @param[in]   devp        Pointer to the @p AX5043Driver object
 *
 * @api
 */
void ax5043Stop(AX5043Driver *devp) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state == AX5043_STOP) ||
            (devp->state == AX5043_READY),
            "ax5043Stop(), invalid state");

    if (devp->state != AX5043_STOP) {
        ax5043SetPWRMode(devp, AX5043_PWRMODE_POWERDOWN);
        devp->state = AX5043_OFF;
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

        /* Disable the interrupt handler */
        palDisableLineEvent(devp->config->irq);
        palSetLineCallback(devp->config->irq, NULL, NULL);
    }

    /* Transition to stop state */
    devp->state = AX5043_STOP;
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

    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043ReadU8(), invalid state");

#if AX5043_USE_SPI
    spip = devp->config->spip;
#if AX5043_SHARED_SPI
    spiAcquireBus(spip);
    spiStart(spip, devp->config->spicfg);
#endif /* AX5043_SHARED_SPI */

    status = ax5043SPIExchange(spip, reg, write, txbuf, rxbuf, n);

#if AX5043_SHARED_SPI
    spiReleaseBus(spip);
#endif /* AX5043_SHARED_SPI */
#endif /* AX5043_USE_SPI */

    return __REVSH(status);
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

    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043GetStatus(), invalid state");
#if AX5043_USE_SPI
    spip = devp->config->spip;
#if AX5043_SHARED_SPI
    spiAcquireBus(spip);
    spiStart(spip, devp->config->spicfg);
#endif /* AX5043_SHARED_SPI */

    spiSelect(spip);
    spiReceive(spip, 2, &status);
    spiUnselect(spip);

#if AX5043_SHARED_SPI
    spiReleaseBus(spip);
#endif /* AX5043_SHARED_SPI */
#endif /* AX5043_USE_SPI */

    return __REVSH(status);
}

/**
 * @brief   Read a raw uint8_t value from a register
 *
 * @param[in]   devp        Pointer to the @p AX5043Driver object.
 * @param[in]   reg         Register address
 *
 * @return                  The value in the register
 * @api
 */
uint8_t ax5043ReadU8(AX5043Driver *devp, uint16_t reg) {
    uint8_t value;

    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043ReadU8(), invalid state");

    ax5043Exchange(devp, reg, false, NULL, &value, sizeof(value));

    return value;
}

/**
 * @brief   Read a raw uint16_t value from a register
 *
 * @param[in]   devp        Pointer to the @p AX5043Driver object.
 * @param[in]   reg         Register address
 *
 * @return                  The value in the register
 * @api
 */
uint16_t ax5043ReadU16(AX5043Driver *devp, uint16_t reg) {
    uint16_t value;

    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043ReadU8(), invalid state");

    ax5043Exchange(devp, reg, false, NULL, (uint8_t*)&value, sizeof(value));

    return __REVSH(value);
}

/**
 * @brief   Read a raw uint32_t value from a register
 *
 * @param[in]   devp        Pointer to the @p AX5043Driver object.
 * @param[in]   reg         Register address
 *
 * @return                  The value in the register
 * @api
 */
uint32_t ax5043ReadU32(AX5043Driver *devp, uint16_t reg) {
    uint32_t value;

    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043ReadU32(), invalid state");

    ax5043Exchange(devp, reg, false, NULL, (uint8_t*)&value, sizeof(value));

    return __REV(value);
}

/**
 * @brief   Write a raw uint8_t value to a register
 *
 * @param[in]   devp        Pointer to the @p AX5043Driver object.
 * @param[in]   reg         Register address
 * @param[in]   value       Register value
 *
 * @api
 */
void ax5043WriteU8(AX5043Driver *devp, uint16_t reg, uint8_t value) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043WriteU8(), invalid state");

    ax5043Exchange(devp, reg, true, &value, NULL, sizeof(value));
}

/**
 * @brief   Write a raw uint16_t value to a register
 *
 * @param[in]   devp        Pointer to the @p AX5043Driver object.
 * @param[in]   reg         Register address
 * @param[in]   value       Register value
 *
 * @api
 */
void ax5043WriteU16(AX5043Driver *devp, uint16_t reg, uint16_t value) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043WriteU8(), invalid state");

    value = __REVSH(value);
    ax5043Exchange(devp, reg, true, (uint8_t*)&value, NULL, sizeof(value));
}

/**
 * @brief   Write a raw uint32_t value to a register
 *
 * @param[in]   devp        Pointer to the @p AX5043Driver object.
 * @param[in]   reg         Register address
 * @param[in]   value       Register value
 *
 * @api
 */
void ax5043WriteU32(AX5043Driver *devp, uint16_t reg, uint32_t value) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043WriteU32(), invalid state");

    value = __REV(value);
    ax5043Exchange(devp, reg, true, (uint8_t*)&value, NULL, sizeof(value));
}

/**
 * @brief   Resets the AX5043 device into POWERDOWN state.
 *
 * @param[in]  devp         Pointer to the @p AX5043Driver object.
 *
 * @return                  AX5043 status bits
 * @api
 */
ax5043_status_t ax5043Reset(AX5043Driver *devp) {
    SPIDriver *spip = NULL;
    ax5043_status_t status = 0;
    uint8_t regval = 0;

    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state != AX5043_UNINIT), "ax5043Reset(), invalid state");

#if AX5043_USE_SPI
    spip = devp->config->spip;
#if AX5043_SHARED_SPI
    spiAcquireBus(spip);
    spiStart(spip, devp->config->spicfg);
#endif /* AX5043_SHARED_SPI */

    /* Wait for device to become active */
    spiUnselect(spip);
    chThdSleepMicroseconds(1);
    spiSelect(spip);
    while (!palReadLine(devp->config->miso));

#if AX5043_SHARED_SPI
    spiReleaseBus(spip);
#endif /* AX5043_SHARED_SPI */
#endif /* AX5043_USE_SPI */

    /* Reset the chip through powermode register */
    regval = AX5043_PWRMODE_RESET;
    ax5043WriteU8(devp, AX5043_REG_PWRMODE, regval);

    /* Write to PWRMODE: XOEN, REFEN and POWERDOWN mode. Clear RST bit.
       Page 33 in programming manual */
    /* TODO: Maybe no XOEN and possible REFEN? */
    regval = AX5043_PWRMODE_XOEN | AX5043_PWRMODE_REFEN | AX5043_PWRMODE_POWERDOWN;
    ax5043WriteU8(devp, AX5043_REG_PWRMODE, regval);

    /* Verify functionality with SCRATCH register */
    regval = 0xAA;
    ax5043Exchange(devp, AX5043_REG_SCRATCH, true, &regval, NULL, 1);
    regval = 0x55;
    ax5043Exchange(devp, AX5043_REG_SCRATCH, true, &regval, &regval, 1);
    if (regval != 0xAA) {
        devp->error = AX5043_ERR_NOT_CONNECTED;
    }
    status = ax5043Exchange(devp, AX5043_REG_SCRATCH, true, NULL, &regval, 1);
    if (regval != 0x55) {
        devp->error = AX5043_ERR_NOT_CONNECTED;
    }

    devp->state = AX5043_READY;
    return status;
}

/*===========================*/
/* TODO: START OVERHAUL HERE */
/*===========================*/

/*
 * TODO: Switch to direct register configuration, use structs
 */
/**
 * @brief   Sets AX5043 registers.
 *
 * @param[in]  devp         Pointer to the @p AX5043Driver object.
 * @param[in]  group        register group that needs to be written.
 *
 * @return                  Most significant status bits (S14...S8)
 * @api
 */
uint8_t ax5043_set_regs_group(AX5043Driver *devp, ax5043_reg_group_t group) {
    ax5043_status_t status = 0;
    int i = 0;

    osalDbgCheck(devp != NULL);
    /* TODO: Add state sanity check */
    /*osalDbgAssert((devp->state == AX5043_READY) ||, "ax5043_set_regs_group(), invalid state");*/

    ax5043_regval_t* entry = devp->config->reg_values;
    while (entry[i].reg != AX5043_REG_END) {
        if (entry[i].group == group){
            status = ax5043Exchange(devp, entry[i].reg, true, &entry[i].val, NULL, 1);
        }
        i++;
    }

    devp->status = status;

    /* Return last status from AX5043 while writting the register */
    return status;
}

/**
 * @brief   Gets AX5043 register values from the AX5043 driver structure.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 * @param[in]  reg_name           register name.
 *
 * @return                        register value.
 * @api
 */
uint8_t ax5043_get_reg_val(AX5043Driver *devp, uint16_t reg_name) {
    int i = 0;

    osalDbgCheck(devp != NULL);
    /* TODO: Add state sanity check */
    /*osalDbgAssert((devp->state == AX5043_READY) ||, "ax5043_get_reg_val(), invalid state");*/

    ax5043_regval_t* entry = devp->config->reg_values;
    while (entry[i].reg != AX5043_REG_END) {
        if (entry[i].reg == reg_name){
            return entry[i].val;
        }
        i++;
    }
    devp->error = AX5043_ERR_REG_NOT_IN_CONF;
    return 0;
}

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

    osalDbgCheck(devp != NULL);
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

    osalDbgCheck(devp != NULL);
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
 * @brief   Prepare AX5043 for tx.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 *
 * @api
 */
void ax5043_prepare_tx(AX5043Driver *devp){
    osalDbgCheck(devp != NULL);
    /* TODO: Add state sanity check */
    /*osalDbgAssert((devp->state == AX5043_READY) ||, "ax5043_prepare_tx(), invalid state");*/

    ax5043SetPWRMode(devp, AX5043_PWRMODE_STANDBY);
    ax5043SetPWRMode(devp, AX5043_PWRMODE_FIFO_EN);

    /* TODO */
    ax5043_set_regs_group(devp,tx);
    ax5043_init_registers_common(devp);

    /* Set FIFO threshold and interrupt mask */
    ax5043WriteU16(devp, AX5043_REG_FIFOTHRESH, 0x0080);
    ax5043WriteU16(devp, AX5043_REG_IRQMASK, 0x0100);

    /* Wait for XTAL */
    while ((ax5043ReadU8(devp, AX5043_REG_XTALSTATUS) & 0x01) == 0) {
        chThdSleepMilliseconds(1);
    }

    devp->status = ax5043GetStatus(devp);
    devp->state = AX5043_TX;
}

/**
 * @brief   prepare AX5043 for rx.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 *
 * @api
 */
void ax5043_prepare_rx(AX5043Driver *devp){
    osalDbgCheck(devp != NULL);
    /* TODO: Add state sanity check */
    /*osalDbgAssert((devp->state == AX5043_READY) ||, "ax5043_prepare_rx(), invalid state");*/

    ax5043_set_regs_group(devp,rx);
    ax5043_init_registers_common(devp);

    /* Updates RSSI reference value, Sets a group of RX registers */
    uint8_t rssireference = ax5043_get_conf_val(devp, AX5043_PHY_RSSIREFERENCE) ;
    ax5043WriteU8(devp, AX5043_REG_RSSIREFERENCE, rssireference);
    ax5043_set_regs_group(devp,rx_cont);
    /* Resets FIFO, changes powermode to FULL RX */
    ax5043WriteU8(devp, AX5043_REG_FIFOSTAT, 0x03);
    ax5043SetPWRMode(devp, AX5043_PWRMODE_RX_FULL);
    /* Sets FIFO threshold and interrupt mask */
    ax5043WriteU16(devp, AX5043_REG_FIFOTHRESH, 0x0080);
    ax5043WriteU16(devp, AX5043_REG_IRQMASK, 0x0001);

    devp->status = ax5043GetStatus(devp);
    devp->state = AX5043_RX;
}

/**
 * @brief   Does PLL ranging.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 *
 * @returns                       PLLVCOI Register content.
 * @api
 */
uint8_t axradio_get_pllvcoi(AX5043Driver *devp){
    osalDbgCheck(devp != NULL);
    /* TODO: Add state sanity check */
    /*osalDbgAssert((devp->state == AX5043_READY) ||, "ax5043_get_pllvcoi(), invalid state");*/

    uint8_t x = ax5043_get_conf_val(devp, AX5043_PHY_CHANVCOIINIT) ;
    uint8_t pll_init_val = ax5043_get_conf_val(devp, AX5043_PHY_CHANPLLRNGINIT);
    uint8_t pll_val = ax5043_get_conf_val(devp, AX5043_PHY_CHANPLLRNG);
    if (x & 0x80) {
        if (!(pll_init_val & 0xF0)) {
            x += (pll_val & 0x0F) - (pll_init_val & 0x0F);
            x &= 0x3f;
            x |= 0x80;
        }
        return x;
    }
    return ax5043ReadU8(devp, AX5043_REG_PLLVCOI);
}

/**
 * @brief   Initialized AX5043 registers common to RX and TX.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 *
 * @api
 */
void ax5043_init_registers_common(AX5043Driver *devp){
    osalDbgCheck(devp != NULL);
    /* TODO: Add state sanity check */
    /*osalDbgAssert((devp->state == AX5043_READY) ||, "ax5043_init_registers_common(), invalid state");*/

    uint8_t rng = ax5043_get_conf_val(devp, AX5043_PHY_CHANPLLRNG);
    if (rng & 0x20)
        devp->status = AX5043_ERR_PLLRNG_VAL;
    if (ax5043ReadU8(devp, AX5043_REG_PLLLOOP) & 0x80) {
        ax5043WriteU8(devp, AX5043_REG_PLLRANGINGB, (rng & 0x0F));
    }
    else {
        ax5043WriteU8(devp, AX5043_REG_PLLRANGINGA, (rng & 0x0F));
    }
    rng = axradio_get_pllvcoi(devp);
    if (rng & 0x80)
        ax5043WriteU8(devp, AX5043_REG_PLLVCOI, rng);
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
            ax5043WriteU8(devp,AX5043_REG_FIFODATA, AX5043_PAYLOADCMD_REPEATDATA | (3 << 5));
            ax5043WriteU8(devp,AX5043_REG_FIFODATA, ax5043_get_conf_val(devp, AX5043_PHY_PREAMBLE_FLAGS));
            ax5043WriteU8(devp,AX5043_REG_FIFODATA, free_fifo_bytes);
            ax5043WriteU8(devp,AX5043_REG_FIFODATA, ax5043_get_conf_val(devp, AX5043_PHY_PREAMBLE_BYTE));
            break;

        case AX5043_TX_SHORTPREAMBLE:
            if (!packet_bytes_sent) {
                uint8_t preamble_appendbits = ax5043_get_conf_val(devp, AX5043_PHY_PREAMBLE_APPENDBITS);
                if (preamble_appendbits) {
                    uint8_t byte;
                    ax5043WriteU8(devp,AX5043_REG_FIFODATA, AX5043_PAYLOADCMD_DATA | (2 << 5));
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
                if ((ax5043ReadU8(devp,AX5043_REG_FRAMING) & 0x0E) == 0x06 && synclen) {
                    /* Write SYNC word if framing mode is raw_patternmatch, might use SYNCLEN > 0 as a criterion, but need to make sure SYNCLEN=0 for WMBUS.
                       Chip automatically sends SYNCWORD but matching in RX works via MATCH0PAT) */
                    int8_t len_byte = synclen;
                    uint8_t i = (len_byte & 0x07) ? 0x04 : 0;
                    /* SYNCLEN in bytes, rather than bits. Ceiled to next integer e.g. fractional bits are counted as full bits */
                    len_byte += 7;
                    len_byte >>= 3;
                    ax5043WriteU8(devp,AX5043_REG_FIFODATA, AX5043_PAYLOADCMD_DATA | ((len_byte + 1) << 5));
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
                ax5043WriteU8(devp,AX5043_REG_FIFODATA, AX5043_PAYLOADCMD_REPEATDATA | (3 << 5));
                ax5043WriteU8(devp,AX5043_REG_FIFODATA, ax5043_get_conf_val(devp, AX5043_PHY_PREAMBLE_FLAGS));
                ax5043WriteU8(devp,AX5043_REG_FIFODATA, free_fifo_bytes);
                ax5043WriteU8(devp,AX5043_REG_FIFODATA, ax5043_get_conf_val(devp, AX5043_PHY_PREAMBLE_BYTE));
                continue;
            }
            {
                uint8_t byte = ax5043_get_conf_val(devp, AX5043_PHY_PREAMBLE_BYTE) ;
                free_fifo_bytes = packet_bytes_sent;
                packet_bytes_sent = 0;
                ax5043WriteU8(devp,AX5043_REG_FIFODATA, AX5043_PAYLOADCMD_DATA | (2 << 5));
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


            ax5043WriteU8(devp,AX5043_REG_FIFODATA, AX5043_PAYLOADCMD_DATA | (7 << 5));
            /* Write FIFO chunk length byte. Length includes the flag byte, thus the +1 */
            ax5043WriteU8(devp,AX5043_REG_FIFODATA, packet_len_to_be_sent + 1);
            ax5043WriteU8(devp,AX5043_REG_FIFODATA, flags);
            ax5043Exchange(devp, AX5043_REG_FIFODATA, true, &axradio_txbuffer[packet_bytes_sent], NULL, packet_len_to_be_sent);
            packet_bytes_sent += packet_len_to_be_sent;
            if (flags & 0x02){
                packet_end_indicator = 1;
                /* Enable radio event done (REVRDONE) event */
                ax5043WriteU8(devp,AX5043_REG_RADIOEVENTMASK0, 0x01);
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
    uint8_t axradio_txbuffer[PKTDATA_BUFLEN];
    uint8_t axradio_localaddr[4];

    uint8_t maclen = ax5043_get_conf_val(devp, AX5043_FRAMING_MACLEN);
    uint8_t destaddrpos = ax5043_get_conf_val(devp, AX5043_FRAMING_DESTADDRPOS);
    uint8_t addrlen = ax5043_get_conf_val(devp, AX5043_FRAMING_ADDRLEN);
    uint8_t sourceaddrpos = ax5043_get_conf_val(devp, AX5043_FRAMING_SOURCEADDRPOS);
    uint8_t lenmask = ax5043_get_conf_val(devp, AX5043_FRAMING_LENMASK);
    uint8_t lenoffs = ax5043_get_conf_val(devp, AX5043_FRAMING_LENOFFS);
    uint8_t lenpos = ax5043_get_conf_val(devp, AX5043_FRAMING_LENPOS);

    axradio_localaddr[0] = ax5043_get_reg_val(devp, AX5043_REG_PKTADDR0);
    axradio_localaddr[1] = ax5043_get_reg_val(devp, AX5043_REG_PKTADDR1);
    axradio_localaddr[2] = ax5043_get_reg_val(devp, AX5043_REG_PKTADDR2);
    axradio_localaddr[3] = ax5043_get_reg_val(devp, AX5043_REG_PKTADDR3);

    packet_len = pktlen + maclen;
    if (packet_len > sizeof(axradio_txbuffer))
        return AX5043_ERR_INVALID;

    /* Prepare the MAC segment of the packet */
    memset(axradio_txbuffer, 0, maclen);
    memcpy(&axradio_txbuffer[maclen], pkt, pktlen);
    if (destaddrpos != 0xff)
        memcpy(&axradio_txbuffer[destaddrpos], &addr->addr, addrlen);
    if (sourceaddrpos != 0xff)
        memcpy(&axradio_txbuffer[sourceaddrpos], axradio_localaddr, addrlen);
    if (lenmask) {
        /* Calculate payload length and update the MAC of payload */
        uint8_t len_byte = (uint8_t)(packet_len - lenoffs) & lenmask;
        axradio_txbuffer[lenpos] = (axradio_txbuffer[lenpos] & (uint8_t)~lenmask) | len_byte;
    }
    /*Clear radioevent flag. This indicator is set when packet is out */
    ax5043ReadU8(devp,AX5043_REG_RADIOEVENTREQ0);
    /* Clear leftover FIFO data & flags */
    ax5043WriteU8(devp, AX5043_REG_FIFOSTAT, 3);
    devp->state = AX5043_TX_LONGPREAMBLE;

    /*Code for 4-FSK mode */
    if ((ax5043ReadU8(devp,AX5043_REG_MODULATION) & 0x0F) == 9) {
        ax5043WriteU8(devp,AX5043_REG_FIFODATA, AX5043_PAYLOADCMD_DATA | (7 << 5));
        /* Length including flags */
        ax5043WriteU8(devp,AX5043_REG_FIFODATA, 2);
        /* Flag PKTSTART -> dibit sync */
        ax5043WriteU8(devp,AX5043_REG_FIFODATA, 0x01);
        /* Dummy byte for forcing dibit sync */
        ax5043WriteU8(devp,AX5043_REG_FIFODATA, 0x11);
    }
    transmit_loop(devp, packet_len, axradio_txbuffer);
    ax5043SetPWRMode(devp, AX5043_PWRMODE_TX_FULL);

    ax5043ReadU8(devp,AX5043_REG_RADIOEVENTREQ0);
    while (ax5043ReadU8(devp,AX5043_REG_RADIOSTATE) != 0) {
        chThdSleepMilliseconds(1);
    }

    ax5043WriteU8(devp,AX5043_REG_RADIOEVENTMASK0, 0x00);
    devp->error = AX5043_ERR_NOERROR;
    return AX5043_ERR_NOERROR;
}

/**
 * @brief   Receive loop to recieve bytes from FIFO.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 * @param[out] axradio_rxbuffer[] Pointer to array where the packet will be kept.
 *
 * @return                        Length of packet received.
 *
 * @api
 * TODO return a -ve return code if there are any errors
 */
uint8_t receive_loop(AX5043Driver *devp, uint8_t axradio_rxbuffer[]) {
    uint8_t fifo_cmd;
    uint8_t i;
    uint8_t chunk_len;
    uint8_t bytesRead = 0;

    /* Clear interrupt */
    ax5043ReadU8(devp, AX5043_REG_RADIOEVENTREQ0);
    devp->state = AX5043_RX_LOOP;
    /* Loop until FIFO not empty */
    while ((ax5043ReadU8(devp, AX5043_REG_FIFOSTAT) & 0x01) != 1) {
        /* FIFO read comman */
        fifo_cmd = ax5043ReadU8(devp, AX5043_REG_FIFODATA);
        /* Top 3 bits encode payload length */
        chunk_len = (fifo_cmd & 0xE0) >> 5;
        /* 7 means variable length, get length byte from next read */
        if (chunk_len == 7)
            chunk_len = ax5043ReadU8(devp, AX5043_REG_FIFODATA);
        fifo_cmd &= 0x1F;
        switch (fifo_cmd) {
        case AX5043_PAYLOADCMD_DATA:
            if (chunk_len!=0){
                /* Discard the flag */
                ax5043ReadU8(devp, AX5043_REG_FIFODATA);
                chunk_len = chunk_len - 1;
                ax5043Exchange(devp, AX5043_REG_FIFODATA, false, NULL, axradio_rxbuffer, chunk_len);
            }
            break;

        case AX5043_PAYLOADCMD_RFFREQOFFS:
            if (chunk_len == 3){
                devp->rf_freq_off3 = ax5043ReadU8(devp, AX5043_REG_FIFODATA);
                devp->rf_freq_off2 = ax5043ReadU8(devp, AX5043_REG_FIFODATA);
                devp->rf_freq_off1 = ax5043ReadU8(devp, AX5043_REG_FIFODATA);
            }
            else{
                for(i=0;i<chunk_len;i++){
                    devp->dropped[i] = ax5043ReadU8(devp, AX5043_REG_FIFODATA);
                    devp->error = AX5043_ERR_FIFO_CHUNK;
                }
            }
            break;

        case AX5043_PAYLOADCMD_FREQOFFS:
            if (chunk_len == 2){
                devp->rf_freq_off3 = 0;
                devp->rf_freq_off2 = ax5043ReadU8(devp, AX5043_REG_FIFODATA);
                devp->rf_freq_off1 = ax5043ReadU8(devp, AX5043_REG_FIFODATA);
            }
            else{
                for(i=0;i<chunk_len;i++){
                    devp->dropped[i] = ax5043ReadU8(devp, AX5043_REG_FIFODATA);
                    devp->error = AX5043_ERR_FIFO_CHUNK;
                }
            }
            break;

        case AX5043_PAYLOADCMD_RSSI:
            if (chunk_len == 1){
                devp->rssi = ax5043ReadU8(devp, AX5043_REG_FIFODATA);
            }
            else{
                for(i=0;i<chunk_len;i++){
                    devp->dropped[i] = ax5043ReadU8(devp, AX5043_REG_FIFODATA);
                    devp->error = AX5043_ERR_FIFO_CHUNK;
                }
            }
            break;

        default:
            devp->error = AX5043_ERR_FIFO_CMD;
            for(i=0;i<chunk_len;i++){
                devp->dropped[i] = ax5043ReadU8(devp, AX5043_REG_FIFODATA);
            }
        }
        devp->state = AX5043_RX;
    }
    return bytesRead;
}

/**
 * @brief   Prepare for CW mode
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 *
 * @return                        Length of packet received.
 *
 * @api
 * TODO return a -ve return code if there are any errors
 */
uint8_t ax5043_prepare_cw(AX5043Driver *devp){
    ax5043WriteU8(devp, AX5043_REG_FSKDEV2, 0x00);
    ax5043WriteU8(devp, AX5043_REG_FSKDEV1, 0x00);
    ax5043WriteU8(devp, AX5043_REG_FSKDEV0, 0x00);
    ax5043WriteU8(devp, AX5043_REG_TXRATE2, 0x00);
    ax5043WriteU8(devp, AX5043_REG_TXRATE1, 0x00);
    ax5043WriteU8(devp, AX5043_REG_TXRATE0, 0x01);

    ax5043SetPWRMode(devp, AX5043_PWRMODE_TX_FULL);

    /* This is not mentioned in datasheet or programming manual but is required.
     * Removing this will make the transmission to transmit in low power for a few seconds
     * before it reaches peak power */
    /* FIFO reset */
    ax5043WriteU8(devp, AX5043_REG_FIFOSTAT, 0x03);
    ax5043WriteU8(devp, AX5043_REG_FIFODATA, (AX5043_PAYLOADCMD_REPEATDATA|0x60));
    /* Preamble flag */
    ax5043WriteU8(devp, AX5043_REG_FIFODATA, 0x38);
    ax5043WriteU8(devp, AX5043_REG_FIFODATA, 0xff);
    /* Preamble */
    ax5043WriteU8(devp, AX5043_REG_FIFODATA, 0x55);
    /* FIFO Commit */
    ax5043WriteU8(devp, AX5043_REG_FIFOSTAT, 0x04);

    ax5043SetPWRMode(devp, AX5043_PWRMODE_STANDBY);
    devp->state = AX5043_CW;
    return 0;
}

/**
 * @brief   Send Morse dot and dash over the air
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 * @param[in]  dot_dash_time      time in milliseconds for transmiter to be on.
 */
void ax5043_morse_dot_dash(AX5043Driver *devp, uint16_t dot_dash_time){
    ax5043SetPWRMode(devp, AX5043_PWRMODE_TX_FULL);
    ax5043WriteU8(devp, AX5043_REG_FIFODATA, (AX5043_PAYLOADCMD_REPEATDATA|0x60));
    /* Preamble flag */
    ax5043WriteU8(devp, AX5043_REG_FIFODATA, 0x38);
    ax5043WriteU8(devp, AX5043_REG_FIFODATA, 0xFF);
    /* Preamble */
    ax5043WriteU8(devp, AX5043_REG_FIFODATA, 0x00);
    /* FIFO Commit */
    ax5043WriteU8(devp, AX5043_REG_FIFOSTAT, 0x04);
    chThdSleepMilliseconds(dot_dash_time);
    ax5043SetPWRMode(devp, AX5043_PWRMODE_STANDBY);

}

/**
 * @brief   Convert an alphabet or number to morse dot and dash
 *
 * @param[in]  letter             An alphabet or number.
 *
 * @return                        Length of packet received.
 */
const char *ax5043_ascii_to_morse(char letter){
    letter = tolower(letter);

    if (isalpha(letter)){
        return alpha[letter-'a'];
    }
    else if (isdigit(letter)){
        return num[letter-'0'];
    }

    return " ";
}

/**
 * @brief   Convert a message to morse code and transmit it.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 * @param[in]  wpm                words per minute.
 * @param[in]  beaconMessage      Message to be transmitted.
 * @param[in]  pktlen             Length of packet/beacon message.
 */
void ax5043_send_cw(AX5043Driver *devp, int wpm, char beaconMessage[], uint16_t pktlen ){
    int element;
    int index = 0;
    const char *morse;

    uint16_t ditLength = 1200/wpm;
    uint16_t letter_space = ditLength*3;
    uint16_t word_space = ditLength*7;
    uint16_t element_space = ditLength;
    uint16_t dash = ditLength*3;

    while (index < pktlen){
        morse = ax5043_ascii_to_morse(beaconMessage[index]);

        element = 0;
        while (morse[element] != '\0'){
            switch(morse[element]){
            case '-':
                ax5043_morse_dot_dash(devp, dash);
                break;
            case '.':
                ax5043_morse_dot_dash(devp, ditLength);
                break;
            }

            if (morse[element] == ' '){
                chThdSleepMilliseconds(word_space);
            }
            else if (morse[element+1] != '\0'){
                chThdSleepMilliseconds(element_space);
            }
            else if (morse[element+1] == '\0'){
                chThdSleepMilliseconds(letter_space);
            }
            element++;
        }

        index++;
    }
}

/** @} */
