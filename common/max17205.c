/**
 * @file    max17205.c
 * @brief   MAX17205 Digital to Analog Converter.
 *
 * @addtogroup MAX17205
 * @ingrup ORESAT
 * @{
 */

#include "hal.h"
#include "max17205.h"

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

#if (MAX17205_USE_I2C) || defined(__DOXYGEN__)
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
msg_t max17205I2CReadRegister(I2CDriver *i2cp, i2caddr_t sad, uint8_t reg,
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
msg_t max17205I2CWriteRegister(I2CDriver *i2cp, i2caddr_t sad, uint8_t *txbuf,
        size_t n) {
    return i2cMasterTransmitTimeout(i2cp, sad, txbuf, n, NULL, 0,
            TIME_INFINITE);
}
#endif /* MAX17205_USE_I2C */

/*==========================================================================*/
/* Interface implementation.                                                */
/*==========================================================================*/

static const struct MAX17205VMT vmt_device = {
    (size_t)0,
};

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Initializes an instance.
 *
 * @param[out] devp     pointer to the @p MAX17205Driver object
 *
 * @init
 */
void max17205ObjectInit(MAX17205Driver *devp) {
    devp->vmt = &vmt_device;

    devp->config = NULL;

    devp->state = MAX17205_STOP;
}

/**
 * @brief   Configures and activates MAX17205 Complex Driver peripheral.
 *
 * @param[in] devp      pointer to the @p MAX17205Driver object
 * @param[in] config    pointer to the @p MAX17205Config object
 *
 * @api
 */
void max17205Start(MAX17205Driver *devp, const MAX17205Config *config) {
    i2cbuf_t buf;

    osalDbgCheck((devp != NULL) && (config != NULL));
    osalDbgAssert((devp->state == MAX17205_STOP) ||
            (devp->state == MAX17205_READY),
            "max17205Start(), invalid state");

    devp->config = config;

    /* Configuring common registers.*/
#if MAX17205_USE_I2C
#if MAX17205_SHARED_I2C
    i2cAcquireBus(config->i2cp);
#endif /* MAX17205_SHARED_I2C */

    i2cStart(config->i2cp, config->i2ccfg);

    /* Reset device */
    buf.reg = MAX17205_AD(MAX17205_AD_COMMAND);
    buf.value = MAX17205_COMMAND_HARDWARE_RESET;
    max17205I2CWriteRegister(config->i2cp, MAX17205_SA(MAX17205_AD_COMMAND), buf.buf, sizeof(buf));
    do {
        max17205I2CReadRegister(config->i2cp, MAX17205_SA(MAX17205_AD_COMMAND), MAX17205_AD(MAX17205_AD_STATUS),
                                                buf.data, sizeof(buf.data));
    } while (!(buf.value & MAX17205_STATUS_POR)); /* While still resetting */
    buf.reg = MAX17205_AD(MAX17205_AD_CONFIG2);
    buf.value = MAX17205_SETVAL(MAX17205_AD_CONFIG2, MAX17205_CONFIG2_POR_CMD);
    max17205I2CWriteRegister(config->i2cp, MAX17205_SA(MAX17205_AD_CONFIG2), buf.buf, sizeof(buf));

    for (const max17205_regval_t *pair = config->regcfg; pair->reg; pair++) {
        buf.reg = MAX17205_AD(pair->reg);
        buf.value = pair->value;
        max17205I2CWriteRegister(config->i2cp, MAX17205_SA(pair->reg), buf.buf, sizeof(buf));
    }

#if MAX17205_SHARED_I2C
    i2cReleaseBus(config->i2cp);
#endif /* MAX17205_SHARED_I2C */
#endif /* MAX17205_USE_I2C */
    devp->state = MAX17205_READY;
}

/**
 * @brief   Deactivates the MAX17205 Complex Driver peripheral.
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 *
 * @api
 */
void max17205Stop(MAX17205Driver *devp) {
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state == MAX17205_STOP) || (devp->state == MAX17205_READY),
            "max17205Stop(), invalid state");

    if (devp->state == MAX17205_READY) {
#if MAX17205_USE_I2C
#if MAX17205_SHARED_I2C
        i2cAcquireBus(devp->config->i2cp);
        i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* MAX17205_SHARED_I2C */

        /* Reset device */
        buf.reg = MAX17205_AD(MAX17205_AD_COMMAND);
        buf.value = MAX17205_COMMAND_HARDWARE_RESET;
        max17205I2CWriteRegister(devp->config->i2cp, MAX17205_SA(MAX17205_AD_COMMAND), buf.buf, sizeof(buf));
        buf.reg = MAX17205_AD(MAX17205_AD_CONFIG2);
        buf.value = MAX17205_SETVAL(MAX17205_AD_CONFIG2, MAX17205_CONFIG2_POR_CMD);
        max17205I2CWriteRegister(devp->config->i2cp, MAX17205_SA(MAX17205_AD_CONFIG2), buf.buf, sizeof(buf));

        i2cStop(devp->config->i2cp);
#if MAX17205_SHARED_I2C
        i2cReleaseBus(devp->config->i2cp);
#endif /* MAX17205_SHARED_I2C */
#endif /* MAX17205_USE_I2C */
    }
    devp->state = MAX17205_STOP;
}

/**
 * @brief   Reads MAX17205 register as raw value.
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 * @param[in] reg        the register to read
 *
 * @api
 */
uint16_t max17205ReadRaw(MAX17205Driver *devp, uint16_t reg) {
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);

    osalDbgAssert(devp->state == MAX17205_READY,
            "max17205ReadRaw(), invalid state");

#if MAX17205_USE_I2C
#if MAX17205_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* MAX17205_SHARED_I2C */

    buf.reg = MAX17205_AD(reg);
    max17205I2CReadRegister(devp->config->i2cp, MAX17205_SA(reg), buf.reg, buf.data, sizeof(buf.data));

#if MAX17205_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* MAX17205_SHARED_I2C */
#endif /* MAX17205_USE_I2C */
    return buf.value;
}

/**
 * @brief   Writes MAX17205 register as raw value.
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 * @param[in] reg        the register to write to
 * @param[in] value      the value to write
 *
 * @api
 */
void max17205WriteRaw(MAX17205Driver *devp, uint16_t reg, uint16_t value) {
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);

    osalDbgAssert(devp->state == MAX17205_READY,
            "max17205WriteRaw(), invalid state");

#if MAX17205_USE_I2C
#if MAX17205_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* MAX17205_SHARED_I2C */

    buf.reg = MAX17205_AD(reg);
    buf.value = value;
    max17205I2CWriteRegister(devp->config->i2cp, MAX17205_SA(reg), buf.buf, sizeof(buf));

#if MAX17205_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* MAX17205_SHARED_I2C */
#endif /* MAX17205_USE_I2C */
}

/** @} */
