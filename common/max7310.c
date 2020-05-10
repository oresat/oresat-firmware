/**
 * @file    max7310.c
 * @brief   MAX7310 GPIO Expander code.
 *
 * @addtogroup MAX7310
 * @ingrup ORESAT
 * @{
 */

#include "hal.h"
#include "max7310.h"

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
        uint8_t data;
    };
    uint8_t buf[2];
} i2cbuf_t;

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

#if (MAX7310_USE_I2C) || defined(__DOXYGEN__)
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
msg_t max7310I2CReadRegister(I2CDriver *i2cp, i2caddr_t sad, uint8_t reg,
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
 * @param[in] txbuf      buffer containing command in first byte and high
 *                       and low data bytes
 * @param[in] n          size of txbuf
 * @return               the operation status.
 * @notapi
 */
msg_t max7310I2CWriteRegister(I2CDriver *i2cp, i2caddr_t sad, uint8_t *txbuf,
        size_t n) {
    return i2cMasterTransmitTimeout(i2cp, sad, txbuf, n, NULL, 0,
            TIME_INFINITE);
}
#endif /* MAX7310_USE_I2C */

/*==========================================================================*/
/* Interface implementation.                                                */
/*==========================================================================*/

static const struct MAX7310VMT vmt_device = {
    (size_t)0,
};

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Initializes an instance.
 *
 * @param[out] devp     pointer to the @p MAX7310Driver object
 *
 * @init
 */
void max7310ObjectInit(MAX7310Driver *devp) {
    devp->vmt = &vmt_device;

    devp->config = NULL;

    devp->state = MAX7310_STOP;
}

/**
 * @brief   Configures and activates MAX7310 Complex Driver peripheral.
 *
 * @param[in] devp      pointer to the @p MAX7310Driver object
 * @param[in] config    pointer to the @p MAX7310Config object
 *
 * @api
 */
void max7310Start(MAX7310Driver *devp, const MAX7310Config *config) {
    i2cbuf_t buf;
    osalDbgCheck((devp != NULL) && (config != NULL));

    osalDbgAssert((devp->state == MAX7310_STOP) ||
            (devp->state == MAX7310_READY),
            "max7310Start(), invalid state");

    devp->config = config;

    /* Configuring common registers.*/
#if MAX7310_USE_I2C
#if MAX7310_SHARED_I2C
    i2cAcquireBus(config->i2cp);
#endif /* MAX7310_SHARED_I2C */

    i2cStart(config->i2cp, config->i2ccfg);
    buf.reg = MAX7310_AD_ODR;
    buf.data = config->odr;
    max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr,
            buf.buf, sizeof(buf));
    buf.reg = MAX7310_AD_POL;
    buf.data = config->pol;
    max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr,
            buf.buf, sizeof(buf));
    buf.reg = MAX7310_AD_MODE;
    buf.data = config->iomode;
    max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr,
            buf.buf, sizeof(buf));
    buf.reg = MAX7310_AD_TIMEOUT;
    buf.data = config->timeout;
    max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr,
            buf.buf, sizeof(buf));

#if MAX7310_SHARED_I2C
    i2cReleaseBus(config->i2cp);
#endif /* MAX7310_SHARED_I2C */
#endif /* MAX7310_USE_I2C */
    devp->state = MAX7310_READY;
}

/**
 * @brief   Deactivates the MAX7310 Complex Driver peripheral.
 *
 * @param[in] devp       pointer to the @p MAX7310Driver object
 *
 * @api
 */
void max7310Stop(MAX7310Driver *devp) {
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);

    osalDbgAssert((devp->state == MAX7310_STOP) || (devp->state == MAX7310_READY),
            "max7310Stop(), invalid state");

    if (devp->state == MAX7310_READY) {
#if MAX7310_USE_I2C
#if MAX7310_SHARED_I2C
        i2cAcquireBus(devp->config->i2cp);
        i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* MAX7310_SHARED_I2C */

        /* Reset to input.*/
        buf.reg = MAX7310_AD_MODE;
        buf.data = 0xFF;
        max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr,
                buf.buf, sizeof(buf));

        /* Reset output reg to 0.*/
        buf.reg = MAX7310_AD_ODR;
        buf.data = 0;
        max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr,
                buf.buf, sizeof(buf));

        /* Reset polarity.*/
        buf.reg = MAX7310_AD_POL;
        buf.data = 0xF0;
        max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr,
                buf.buf, sizeof(buf));

        /* Reset timeout.*/
        buf.reg = MAX7310_AD_TIMEOUT;
        buf.data = MAX7310_TIMEOUT_ENABLED;
        max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr,
                buf.buf, sizeof(buf));

        i2cStop(devp->config->i2cp);
#if MAX7310_SHARED_I2C
        i2cReleaseBus(devp->config->i2cp);
#endif /* MAX7310_SHARED_I2C */
#endif /* MAX7310_USE_I2C */
    }
    devp->state = MAX7310_STOP;
}

/**
 * @brief   Reads MAX7310 register as raw value.
 *
 * @param[in] devp       pointer to the @p MAX7310Driver object
 * @param[in] reg        the register to read
 *
 * @api
 */
uint8_t max7310ReadRaw(MAX7310Driver *devp, uint8_t reg) {
    uint8_t value;

    osalDbgCheck(devp != NULL);

    osalDbgAssert(devp->state == MAX7310_READY,
            "max7310ReadRaw(), invalid state");

#if MAX7310_USE_I2C
#if MAX7310_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* MAX7310_SHARED_I2C */

    max7310I2CReadRegister(devp->config->i2cp, devp->config->saddr, reg, &value, sizeof(value));

#if MAX7310_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* MAX7310_SHARED_I2C */
#endif /* MAX7310_USE_I2C */
    return value;
}

/**
 * @brief   Writes MAX7310 register as raw value.
 *
 * @param[in] devp       pointer to the @p MAX7310Driver object
 * @param[in] reg        the register to write to
 * @param[in] value      the value to write
 *
 * @api
 */
void max7310WriteRaw(MAX7310Driver *devp, uint8_t reg, uint8_t value) {
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);

    osalDbgAssert(devp->state == MAX7310_READY,
            "max7310WriteRaw(), invalid state");

#if MAX7310_USE_I2C
#if MAX7310_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* MAX7310_SHARED_I2C */

    buf.reg = reg;
    buf.data = value;
    max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr, buf.buf, sizeof(buf));

#if MAX7310_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* MAX7310_SHARED_I2C */
#endif /* MAX7310_USE_I2C */
}

/**
 * @brief   Sets MAX7310 pin
 *
 * @param[in] devp       pointer to the @p MAX7310Driver object
 * @param[in] pin        pin to set
 *
 * @api
 */
void max7310SetPin(MAX7310Driver *devp, uint8_t pin) {
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);

    osalDbgAssert(devp->state == MAX7310_READY,
            "max7310SetPin(), invalid state");

#if MAX7310_USE_I2C
#if MAX7310_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* MAX7310_SHARED_I2C */

    buf.reg = MAX7310_AD_ODR;
    max7310I2CReadRegister(devp->config->i2cp, devp->config->saddr, buf.reg, &buf.data, sizeof(buf.data));
    buf.data |= MAX7310_PIN_MASK(pin);
    max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr, buf.buf, sizeof(buf));

#if MAX7310_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* MAX7310_SHARED_I2C */
#endif /* MAX7310_USE_I2C */
}

/**
 * @brief   Clear MAX7310 pin
 *
 * @param[in] devp       pointer to the @p MAX7310Driver object
 * @param[in] pin        pin to clear
 *
 * @api
 */
void max7310ClearPin(MAX7310Driver *devp, uint8_t pin) {
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);

    osalDbgAssert(devp->state == MAX7310_READY,
            "max7310SetPin(), invalid state");

#if MAX7310_USE_I2C
#if MAX7310_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* MAX7310_SHARED_I2C */

    buf.reg = MAX7310_AD_ODR;
    max7310I2CReadRegister(devp->config->i2cp, devp->config->saddr, buf.reg, &buf.data, sizeof(buf.data));
    buf.data &= ~MAX7310_PIN_MASK(pin);
    max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr, buf.buf, sizeof(buf));

#if MAX7310_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* MAX7310_SHARED_I2C */
#endif /* MAX7310_USE_I2C */
}

/**
 * @brief   Toggle MAX7310 pin
 *
 * @param[in] devp       pointer to the @p MAX7310Driver object
 * @param[in] pin        pin to toggle
 *
 * @api
 */
void max7310TogglePin(MAX7310Driver *devp, uint8_t pin) {
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);

    osalDbgAssert(devp->state == MAX7310_READY,
            "max7310SetPin(), invalid state");

#if MAX7310_USE_I2C
#if MAX7310_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* MAX7310_SHARED_I2C */

    buf.reg = MAX7310_AD_ODR;
    max7310I2CReadRegister(devp->config->i2cp, devp->config->saddr, buf.reg, &buf.data, sizeof(buf.data));
    buf.data ^= MAX7310_PIN_MASK(pin);
    max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr, buf.buf, sizeof(buf));

#if MAX7310_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* MAX7310_SHARED_I2C */
#endif /* MAX7310_USE_I2C */
}

/** @} */
