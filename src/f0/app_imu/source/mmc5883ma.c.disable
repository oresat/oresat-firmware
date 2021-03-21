/**
 * @file    mmc5883ma.c
 * @brief   MMC5883MA Digital to Analog Converter.
 *
 * @addtogroup MMC5883MA
 * @ingrup ORESAT
 * @{
 */

#include "hal.h"
#include "mmc5883ma.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/
typedef union {
    struct __attribute__((packed)) {
        uint8_t reg;
        union {
            uint8_t data[2];
            uint16_t value;
        };
    };
    uint8_t buf[3];
} i2cbuf_t;

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

#if (MMC5883MA_USE_I2C) || defined(__DOXYGEN__)
/**
 * @brief   Reads registers value using I2C.
 * @pre     The I2C interface must be initialized and the driver started.
 *
 * @param[in]  i2cp      pointer to the I2C interface
 * @param[in]  sad       slave address without R bit
 * @param[in]  reg       first sub-register address
 * @param[out] rxbuf     pointer to an output buffer
 * @param[in]  n         number of consecutive register to read
 * @return               the operation status.
 * @notapi
 */
msg_t mmc5883maI2CReadRegister(I2CDriver *i2cp, i2caddr_t sad, uint8_t reg,
        uint8_t* rxbuf, size_t n) {
    return i2cMasterTransmitTimeout(i2cp, sad, &reg, 1, rxbuf, n,
            TIME_INFINITE);
}

/**
 * @brief   Writes a value into a register using I2C.
 * @pre     The I2C interface must be initialized and the driver started.
 *
 * @param[in] i2cp       pointer to the I2C interface
 * @param[in] sad        slave address without R bit
 * @param[in] txbuf      buffer containing reg in first byte and high
 *                       and low data bytes
 * @param[in] n          size of txbuf
 * @return               the operation status.
 * @notapi
 */
msg_t mmc5883maI2CWriteRegister(I2CDriver *i2cp, i2caddr_t sad, uint8_t *txbuf,
        size_t n) {
    return i2cMasterTransmitTimeout(i2cp, sad, txbuf, n, NULL, 0,
            TIME_INFINITE);
}
#endif /* MMC5883MA_USE_I2C */

/*==========================================================================*/
/* Interface implementation.                                                */
/*==========================================================================*/

static const struct MMC5883MAVMT vmt_device = {
    (size_t)0,
};

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Initializes an instance.
 *
 * @param[out] devp     pointer to the @p MMC5883MADriver object
 *
 * @init
 */
void mmc5883maObjectInit(MMC5883MADriver *devp) {
    devp->vmt = &vmt_device;

    devp->config = NULL;

    devp->state = MMC5883MA_STOP;
}

/**
 * @brief   Configures and activates MMC5883MA Complex Driver peripheral.
 *
 * @param[in] devp      pointer to the @p MMC5883MADriver object
 * @param[in] config    pointer to the @p MMC5883MAConfig object
 *
 * @api
 */
void mmc5883maStart(MMC5883MADriver *devp, const MMC5883MAConfig *config) {
    i2cbuf_t buf;

    osalDbgCheck((devp != NULL) && (config != NULL));
    osalDbgAssert((devp->state == MMC5883MA_STOP) ||
            (devp->state == MMC5883MA_READY),
            "mmc5883maStart(), invalid state");

    devp->config = config;

    /* Configuring common registers.*/
#if MMC5883MA_USE_I2C
#if MMC5883MA_SHARED_I2C
    i2cAcquireBus(config->i2cp);
#endif /* MMC5883MA_SHARED_I2C */

    i2cStart(config->i2cp, config->i2ccfg);
    buf.reg = MMC5883MA_AD_CONFIG;
    buf.value = __REVSH(MMC5883MA_CONFIG_RST);
    mmc5883maI2CWriteRegister(config->i2cp, config->saddr, buf.buf, sizeof(buf));
    do {
        mmc5883maI2CReadRegister(config->i2cp, config->saddr, MMC5883MA_AD_CONFIG,
                                                buf.data, sizeof(buf.data));
    } while (buf.data[0] & 0x80U); /* While still resetting */
    buf.reg = MMC5883MA_AD_CONFIG;
    buf.value = __REVSH(config->cfg);
    mmc5883maI2CWriteRegister(config->i2cp, config->saddr, buf.buf, sizeof(buf));
    buf.reg = MMC5883MA_AD_CAL;
    buf.value = __REVSH(config->cal);
    mmc5883maI2CWriteRegister(config->i2cp, config->saddr, buf.buf, sizeof(buf));

#if MMC5883MA_SHARED_I2C
    i2cReleaseBus(config->i2cp);
#endif /* MMC5883MA_SHARED_I2C */
#endif /* MMC5883MA_USE_I2C */
    devp->state = MMC5883MA_READY;
}

/**
 * @brief   Deactivates the MMC5883MA Complex Driver peripheral.
 *
 * @param[in] devp       pointer to the @p MMC5883MADriver object
 *
 * @api
 */
void mmc5883maStop(MMC5883MADriver *devp) {
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state == MMC5883MA_STOP) || (devp->state == MMC5883MA_READY),
            "mmc5883maStop(), invalid state");

    if (devp->state == MMC5883MA_READY) {
#if MMC5883MA_USE_I2C
#if MMC5883MA_SHARED_I2C
        i2cAcquireBus(devp->config->i2cp);
        i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* MMC5883MA_SHARED_I2C */

        /* Reset to input.*/
        buf.reg = MMC5883MA_AD_CONFIG;
        buf.value = __REVSH(MMC5883MA_CONFIG_RST);
        mmc5883maI2CWriteRegister(devp->config->i2cp, devp->config->saddr, buf.buf, sizeof(buf));

        i2cStop(devp->config->i2cp);
#if MMC5883MA_SHARED_I2C
        i2cReleaseBus(devp->config->i2cp);
#endif /* MMC5883MA_SHARED_I2C */
#endif /* MMC5883MA_USE_I2C */
    }
    devp->state = MMC5883MA_STOP;
}

/**
 * @brief   Sets MMC5883MA Alert type and value
 *
 * @param[in] devp       pointer to the @p MMC5883MADriver object
 * @param[in] alert_me   the value to write to Mask/Enable register (0 to disable)
 * @param[in] alert_lim  the value to write to Alert Limit register
 *
 * @api
 */
void mmc5883maSetAlert(MMC5883MADriver *devp, uint16_t alert_me, uint16_t alert_lim) {
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == MMC5883MA_READY,
            "mmc5883maSetAlert(), invalid state");

#if MMC5883MA_USE_I2C
#if MMC5883MA_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* MMC5883MA_SHARED_I2C */

    buf.reg = MMC5883MA_AD_LIM;
    buf.value = __REVSH(alert_lim);
    mmc5883maI2CWriteRegister(devp->config->i2cp, devp->config->saddr, buf.buf, sizeof(buf));
    buf.reg = MMC5883MA_AD_ME;
    buf.value = __REVSH(alert_me);
    mmc5883maI2CWriteRegister(devp->config->i2cp, devp->config->saddr, buf.buf, sizeof(buf));

#if MMC5883MA_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* MMC5883MA_SHARED_I2C */
#endif /* MMC5883MA_USE_I2C */
}

/**
 * @brief   Reads MMC5883MA Register as raw value.
 *
 * @param[in] devp       pointer to the @p MMC5883MADriver object
 * @param[in] reg        the register to read from
 *
 * @api
 */
uint16_t mmc5883maReadRaw(MMC5883MADriver *devp, uint8_t reg) {
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == MMC5883MA_READY,
            "mmc5883maReadRaw(), invalid state");

#if MMC5883MA_USE_I2C
#if MMC5883MA_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* MMC5883MA_SHARED_I2C */

    buf.reg = reg;
    mmc5883maI2CReadRegister(devp->config->i2cp, devp->config->saddr, buf.reg, buf.data, sizeof(buf.data));

#if MMC5883MA_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* MMC5883MA_SHARED_I2C */
#endif /* MMC5883MA_USE_I2C */
    return __REVSH(buf.value);
}

/**
 * @brief   Reads MMC5883MA Shunt voltage.
 *
 * @param[in] devp       Pointer to the @p MMC5883MADriver object
 * @return               Shunt voltage in 0.1uV increments
 *
 * @api
 */
int16_t mmc5883maReadShunt(MMC5883MADriver *devp) {
    int16_t voltage;

    osalDbgCheck(devp != NULL);

    voltage = mmc5883maReadRaw(devp, MMC5883MA_AD_SHUNT) * 25;

    return voltage;
}

/**
 * @brief   Reads MMC5883MA VBUS voltage.
 *
 * @param[in] devp       pointer to the @p MMC5883MADriver object
 * @return               VBUS voltage in 0.01mV increments
 *
 * @api
 */
uint16_t mmc5883maReadVBUS(MMC5883MADriver *devp) {
    uint16_t voltage;

    osalDbgCheck(devp != NULL);

    voltage = mmc5883maReadRaw(devp, MMC5883MA_AD_VBUS) * 125;

    return voltage;
}

/**
 * @brief   Reads MMC5883MA Current.
 * @note    Requires curr_lsb to be set in config
 *
 * @param[in] devp       pointer to the @p MMC5883MADriver object
 * @return               Current in increments of @p curr_lsb
 *
 * @api
 */
int16_t mmc5883maReadCurrent(MMC5883MADriver *devp) {
    int16_t current;

    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->config->curr_lsb,
            "mmc5883maReadCurrent(): invalid curr_lsb value");

    current = mmc5883maReadRaw(devp, MMC5883MA_AD_CURRENT) * devp->config->curr_lsb;

    return current;
}

/**
 * @brief   Reads MMC5883MA Power.
 * @note    Requires curr_lsb to be set in config
 *
 * @param[in] devp       pointer to the @p MMC5883MADriver object
 * @return               Power in increments of @p curr_lsb * 25V
 *
 * @api
 */
uint16_t mmc5883maReadPower(MMC5883MADriver *devp) {
    uint16_t power;

    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->config->curr_lsb,
            "mmc5883maReadCurrent(): invalid curr_lsb value");

    power = mmc5883maReadRaw(devp, MMC5883MA_AD_POWER) * devp->config->curr_lsb * 25;

    return power;
}

/** @} */
