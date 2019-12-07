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
            TIME_MS2I(10));
}

/**
 * @brief   Writes a value into a register using I2C.
 * @pre     The I2C interface must be initialized and the driver started.
 *
 * @param[in] i2cp       pointer to the I2C interface
 * @param[in] sad        slave address without R bit
 * @param[in] txbuf      buffer containing sub-address value in first position
 *                       and values to write
 * @param[in] n          size of txbuf less one (not considering the first
 *                       element)
 * @return               the operation status.
 * @notapi
 */
msg_t max7310I2CWriteRegister(I2CDriver *i2cp, i2caddr_t sad, uint8_t *txbuf,
        size_t n) {
    return i2cMasterTransmitTimeout(i2cp, sad, txbuf, n + 1, NULL, 0,
            TIME_MS2I(10));
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
    uint8_t cr[2];
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
    cr[0] = MAX7310_AD_ODR;
    cr[1] = config->odr;
    max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr, cr, 1);
    cr[0] = MAX7310_AD_POL;
    cr[1] = config->pol;
    max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr, cr, 1);
    cr[0] = MAX7310_AD_MODE;
    cr[1] = config->iomode;
    max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr, cr, 1);
    cr[0] = MAX7310_AD_TIMEOUT;
    cr[1] = config->timeout;
    max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr, cr, 1);

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
    uint8_t cr[2];

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
        cr[0] = MAX7310_AD_MODE;
        cr[1] = 0xFF;
        max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr, cr, 1);

        /* Reset output reg to 0.*/
        cr[0] = MAX7310_AD_ODR;
        cr[1] = 0;
        max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr, cr, 1);

        /* Reset polarity.*/
        cr[0] = MAX7310_AD_POL;
        cr[1] = 0xF0;
        max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr, cr, 1);

        /* Reset timeout.*/
        cr[0] = MAX7310_AD_TIMEOUT;
        cr[1] = MAX7310_TIMEOUT_ENABLED;
        max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr, cr, 1);

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
    uint8_t retval;

    osalDbgCheck(devp != NULL);

    osalDbgAssert(devp->state == MAX7310_READY,
            "max7310ReadRaw(), invalid state");

#if MAX7310_USE_I2C
#if MAX7310_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* MAX7310_SHARED_I2C */

    max7310I2CReadRegister(devp->config->i2cp, devp->config->saddr, reg, &retval, 1);

#if MAX7310_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* MAX7310_SHARED_I2C */
#endif /* MAX7310_USE_I2C */
    return retval;
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
    uint8_t cr[2];

    osalDbgCheck(devp != NULL);

    osalDbgAssert(devp->state == MAX7310_READY,
            "max7310WriteRaw(), invalid state");

#if MAX7310_USE_I2C
#if MAX7310_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* MAX7310_SHARED_I2C */

    cr[0] = reg;
    cr[1] = value;
    max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr, cr, 1);

#if MAX7310_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* MAX7310_SHARED_I2C */
#endif /* MAX7310_USE_I2C */
}

/** @} */
