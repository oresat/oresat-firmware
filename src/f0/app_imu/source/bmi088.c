/**
 * @file    bmi088.c
 * @brief   BMI088 6DoF inertial measurement unit.
 *
 * @addtogroup BMI088
 * @ingrup ORESAT
 * @{
 */

#include "hal.h"
#include "bmi088.h"

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

#if (BMI088_USE_I2C) || defined(__DOXYGEN__)
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
msg_t bmi088I2CReadRegister(I2CDriver *i2cp, i2caddr_t sad, uint8_t reg,
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
msg_t bmi088I2CWriteRegister(I2CDriver *i2cp, i2caddr_t sad, uint8_t *txbuf,
        size_t n) {
    return i2cMasterTransmitTimeout(i2cp, sad, txbuf, n, NULL, 0,
            TIME_INFINITE);
}
#endif /* BMI088_USE_I2C */

/*==========================================================================*/
/* Interface implementation.                                                */
/*==========================================================================*/

static const struct BMI088VMT vmt_device = {
    (size_t)0,
};

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Initializes an instance.
 *
 * @param[out] devp     pointer to the @p BMI088Driver object
 *
 * @init
 */
void bmi088ObjectInit(BMI088Driver *devp) {
    devp->vmt = &vmt_device;

    devp->config = NULL;

    devp->state = BMI088_STOP;
}

/**
 * @brief   Configures and activates BMI088 Complex Driver peripheral.
 *
 * @param[in] devp      pointer to the @p BMI088Driver object
 * @param[in] config    pointer to the @p BMI088Config object
 *
 * @api
 */
void bmi088Start(BMI088Driver *devp, const BMI088Config *config) {
    i2cbuf_t buf;

    osalDbgCheck((devp != NULL) && (config != NULL));
    osalDbgAssert((devp->state == BMI088_STOP) ||
            (devp->state == BMI088_READY),
            "bmi088Start(), invalid state");

    devp->config = config;

    /* Configuring common registers.*/
#if BMI088_USE_I2C
#if BMI088_SHARED_I2C
    i2cAcquireBus(config->i2cp);
#endif /* BMI088_SHARED_I2C */

    i2cStart(config->i2cp, config->i2ccfg);
    buf.reg = BMI088_AD_CONFIG;
    buf.value = __REVSH(BMI088_CONFIG_RST);
    bmi088I2CWriteRegister(config->i2cp, config->saddr, buf.buf, sizeof(buf));
    do {
        bmi088I2CReadRegister(config->i2cp, config->saddr, BMI088_AD_CONFIG,
                                                buf.data, sizeof(buf.data));
    } while (buf.data[0] & 0x80U); /* While still resetting */
    buf.reg = BMI088_AD_CONFIG;
    buf.value = __REVSH(config->cfg);
    bmi088I2CWriteRegister(config->i2cp, config->saddr, buf.buf, sizeof(buf));
    buf.reg = BMI088_AD_CAL;
    buf.value = __REVSH(config->cal);
    bmi088I2CWriteRegister(config->i2cp, config->saddr, buf.buf, sizeof(buf));

#if BMI088_SHARED_I2C
    i2cReleaseBus(config->i2cp);
#endif /* BMI088_SHARED_I2C */
#endif /* BMI088_USE_I2C */
    devp->state = BMI088_READY;
}

/**
 * @brief   Deactivates the BMI088 Complex Driver peripheral.
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 *
 * @api
 */
void bmi088Stop(BMI088Driver *devp) {
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state == BMI088_STOP) || (devp->state == BMI088_READY),
            "bmi088Stop(), invalid state");

    if (devp->state == BMI088_READY) {
#if BMI088_USE_I2C
#if BMI088_SHARED_I2C
        i2cAcquireBus(devp->config->i2cp);
        i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* BMI088_SHARED_I2C */

        /* Reset to input.*/
        buf.reg = BMI088_AD_CONFIG;
        buf.value = __REVSH(BMI088_CONFIG_RST);
        bmi088I2CWriteRegister(devp->config->i2cp, devp->config->saddr, buf.buf, sizeof(buf));

        i2cStop(devp->config->i2cp);
#if BMI088_SHARED_I2C
        i2cReleaseBus(devp->config->i2cp);
#endif /* BMI088_SHARED_I2C */
#endif /* BMI088_USE_I2C */
    }
    devp->state = BMI088_STOP;
}

/**
 * @brief   Sets BMI088 Alert type and value
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @param[in] alert_me   the value to write to Mask/Enable register (0 to disable)
 * @param[in] alert_lim  the value to write to Alert Limit register
 *
 * @api
 */

/**
 * @brief   Reads BMI088 Register as raw value.
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @param[in] reg        the register to read from
 *
 * @api
 */
uint16_t bmi088ReadRaw(BMI088Driver *devp, uint8_t reg) {
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == BMI088_READY,
            "bmi088ReadRaw(), invalid state");

#if BMI088_USE_I2C
#if BMI088_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* BMI088_SHARED_I2C */

    buf.reg = reg;
    bmi088I2CReadRegister(devp->config->i2cp, devp->config->saddr, buf.reg, buf.data, sizeof(buf.data));

#if BMI088_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* BMI088_SHARED_I2C */
#endif /* BMI088_USE_I2C */
    return __REVSH(buf.value);
}

/**
 * @brief   Reads BMI088 Shunt voltage.
 *
 * @param[in] devp       Pointer to the @p BMI088Driver object
 * @return               Shunt voltage in 0.1uV increments
 *
 * @api
 */

/**
 * @brief   Reads BMI088 VBUS voltage.
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @return               VBUS voltage in 0.01mV increments
 *
 * @api
 */

/**
 * @brief   Reads BMI088 Current.
 * @note    Requires curr_lsb to be set in config
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @return               Current in increments of @p curr_lsb
 *
 * @api
 */

/**
 * @brief   Reads BMI088 Power.
 * @note    Requires curr_lsb to be set in config
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @return               Power in increments of @p curr_lsb * 25V
 *
 * @api
 */

/** @} */
