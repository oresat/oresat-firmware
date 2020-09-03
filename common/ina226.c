/**
 * @file    ina226.c
 * @brief   INA226 Digital to Analog Converter.
 *
 * @addtogroup INA226
 * @ingrup ORESAT
 * @{
 */

#include "hal.h"
#include "ina226.h"

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

#if (INA226_USE_I2C) || defined(__DOXYGEN__)
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
msg_t ina226I2CReadRegister(I2CDriver *i2cp, i2caddr_t sad, uint8_t reg,
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
msg_t ina226I2CWriteRegister(I2CDriver *i2cp, i2caddr_t sad, uint8_t *txbuf,
        size_t n) {
    return i2cMasterTransmitTimeout(i2cp, sad, txbuf, n, NULL, 0,
            TIME_INFINITE);
}
#endif /* INA226_USE_I2C */

/*==========================================================================*/
/* Interface implementation.                                                */
/*==========================================================================*/

static const struct INA226VMT vmt_device = {
    (size_t)0,
};

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Initializes an instance.
 *
 * @param[out] devp     pointer to the @p INA226Driver object
 *
 * @init
 */
void ina226ObjectInit(INA226Driver *devp) {
    devp->vmt = &vmt_device;

    devp->config = NULL;

    devp->state = INA226_STOP;
}

/**
 * @brief   Configures and activates INA226 Complex Driver peripheral.
 *
 * @param[in] devp      pointer to the @p INA226Driver object
 * @param[in] config    pointer to the @p INA226Config object
 *
 * @api
 */
void ina226Start(INA226Driver *devp, const INA226Config *config) {
    i2cbuf_t buf;

    osalDbgCheck((devp != NULL) && (config != NULL));
    osalDbgAssert((devp->state == INA226_STOP) ||
            (devp->state == INA226_READY),
            "ina226Start(), invalid state");

    devp->config = config;

    /* Configuring common registers.*/
#if INA226_USE_I2C
#if INA226_SHARED_I2C
    i2cAcquireBus(config->i2cp);
#endif /* INA226_SHARED_I2C */

    i2cStart(config->i2cp, config->i2ccfg);
    buf.reg = INA226_AD_CONFIG;
    buf.value = __REVSH(INA226_CONFIG_RST);
    ina226I2CWriteRegister(config->i2cp, config->saddr, buf.buf, sizeof(buf));
    do {
        ina226I2CReadRegister(config->i2cp, config->saddr, INA226_AD_CONFIG,
                                                buf.data, sizeof(buf.data));
    } while (buf.data[0] & 0x80U); /* While still resetting */
    buf.reg = INA226_AD_CONFIG;
    buf.value = __REVSH(config->cfg);
    ina226I2CWriteRegister(config->i2cp, config->saddr, buf.buf, sizeof(buf));
    buf.reg = INA226_AD_CAL;
    buf.value = __REVSH(config->cal);
    ina226I2CWriteRegister(config->i2cp, config->saddr, buf.buf, sizeof(buf));

#if INA226_SHARED_I2C
    i2cReleaseBus(config->i2cp);
#endif /* INA226_SHARED_I2C */
#endif /* INA226_USE_I2C */
    devp->state = INA226_READY;
}

/**
 * @brief   Deactivates the INA226 Complex Driver peripheral.
 *
 * @param[in] devp       pointer to the @p INA226Driver object
 *
 * @api
 */
void ina226Stop(INA226Driver *devp) {
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state == INA226_STOP) || (devp->state == INA226_READY),
            "ina226Stop(), invalid state");

    if (devp->state == INA226_READY) {
#if INA226_USE_I2C
#if INA226_SHARED_I2C
        i2cAcquireBus(devp->config->i2cp);
        i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* INA226_SHARED_I2C */

        /* Reset to input.*/
        buf.reg = INA226_AD_CONFIG;
        buf.value = __REVSH(INA226_CONFIG_RST);
        ina226I2CWriteRegister(devp->config->i2cp, devp->config->saddr, buf.buf, sizeof(buf));

        i2cStop(devp->config->i2cp);
#if INA226_SHARED_I2C
        i2cReleaseBus(devp->config->i2cp);
#endif /* INA226_SHARED_I2C */
#endif /* INA226_USE_I2C */
    }
    devp->state = INA226_STOP;
}

/**
 * @brief   Sets INA226 Alert type and value
 *
 * @param[in] devp       pointer to the @p INA226Driver object
 * @param[in] alert_me   the value to write to Mask/Enable register (0 to disable)
 * @param[in] alert_lim  the value to write to Alert Limit register
 *
 * @api
 */
void ina226SetAlert(INA226Driver *devp, uint16_t alert_me, uint16_t alert_lim) {
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == INA226_READY,
            "ina226SetAlert(), invalid state");

#if INA226_USE_I2C
#if INA226_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* INA226_SHARED_I2C */

    buf.reg = INA226_AD_LIM;
    buf.value = __REVSH(alert_lim);
    ina226I2CWriteRegister(devp->config->i2cp, devp->config->saddr, buf.buf, sizeof(buf));
    buf.reg = INA226_AD_ME;
    buf.value = __REVSH(alert_me);
    ina226I2CWriteRegister(devp->config->i2cp, devp->config->saddr, buf.buf, sizeof(buf));

#if INA226_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* INA226_SHARED_I2C */
#endif /* INA226_USE_I2C */
}

/**
 * @brief   Reads INA226 Register as raw value.
 *
 * @param[in] devp       pointer to the @p INA226Driver object
 * @param[in] reg        the register to read from
 *
 * @api
 */
uint16_t ina226ReadRaw(INA226Driver *devp, uint8_t reg) {
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == INA226_READY,
            "ina226ReadRaw(), invalid state");

#if INA226_USE_I2C
#if INA226_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* INA226_SHARED_I2C */

    buf.reg = reg;
    ina226I2CReadRegister(devp->config->i2cp, devp->config->saddr, buf.reg, buf.data, sizeof(buf.data));

#if INA226_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* INA226_SHARED_I2C */
#endif /* INA226_USE_I2C */
    return __REVSH(buf.value);
}

/**
 * @brief   Reads INA226 Shunt voltage.
 *
 * @param[in] devp       Pointer to the @p INA226Driver object
 * @return               Shunt voltage in 1uV increments
 *
 * @api
 */
int32_t ina226ReadShunt(INA226Driver *devp) {
    int32_t voltage;

    osalDbgCheck(devp != NULL);

    voltage = ((int16_t)ina226ReadRaw(devp, INA226_AD_SHUNT) * 25)/10;

    return voltage;
}

/**
 * @brief   Reads INA226 VBUS voltage.
 *
 * @param[in] devp       pointer to the @p INA226Driver object
 * @return               VBUS voltage in 1uV increments
 *
 * @api
 */
uint32_t ina226ReadVBUS(INA226Driver *devp) {
    uint32_t voltage;

    osalDbgCheck(devp != NULL);

    voltage = ina226ReadRaw(devp, INA226_AD_VBUS) * 1250;

    return voltage;
}

/**
 * @brief   Reads INA226 Current.
 * @note    Requires curr_lsb to be set in config
 *
 * @param[in] devp       pointer to the @p INA226Driver object
 * @return               Current in increments of @p curr_lsb
 *
 * @api
 */
int32_t ina226ReadCurrent(INA226Driver *devp) {
    int32_t current;

    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->config->curr_lsb,
            "ina226ReadCurrent(): invalid curr_lsb value");

    current = (int16_t)ina226ReadRaw(devp, INA226_AD_CURRENT) * devp->config->curr_lsb;

    return current;
}

/**
 * @brief   Reads INA226 Power.
 * @note    Requires curr_lsb to be set in config
 *
 * @param[in] devp       pointer to the @p INA226Driver object
 * @return               Power in increments of @p curr_lsb * 25V
 *
 * @api
 */
uint32_t ina226ReadPower(INA226Driver *devp) {
    uint32_t power;

    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->config->curr_lsb,
            "ina226ReadCurrent(): invalid curr_lsb value");

    power = ina226ReadRaw(devp, INA226_AD_POWER) * devp->config->curr_lsb * 25;

    return power;
}

/** @} */
