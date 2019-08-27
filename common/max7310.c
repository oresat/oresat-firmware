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
 * @note    IF_ADD_INC bit must be 1 in CTRL_REG8
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
            TIME_INFINITE);
}
#endif /* MAX7310_USE_I2C */

/*==========================================================================*/
/* Interface implementation.                                                */
/*==========================================================================*/

/**
 * @brief   Set the output state of the ports.
 *
 * @param[in]   devp    MAX7310 Driver pointer
 * @param[in]   output  New output register value
 *
 * @return      msg     The result of the setting operation
 */
static msg_t set_output(MAX7310Driver *devp, uint8_t output) {

    return MSG_OK;
}

/**
 * @brief   Set the polarity of the ports.
 *
 * @param[in]   devp    MAX7310 Driver pointer
 * @param[in]   polarity New polarity register value
 *
 * @return      msg     The result of the setting operation
 */
static msg_t set_polarity(MAX7310Driver *devp, uint8_t polarity) {

    return MSG_OK;
}

/**
 * @brief   Set the IO mode of the ports.
 *
 * @param[in]   devp    MAX7310 Driver pointer
 * @param[in]   iomode  New IO mode configuration value
 *
 * @return      msg     The result of the setting operation
 */
static msg_t set_iomode(MAX7310Driver *devp, uint8_t iomode) {

    return MSG_OK;
}

/**
 * @brief   Set the timeout mode of the device.
 *
 * @param[in]   devp    MAX7310 Driver pointer
 * @param[in]   timeout New timeout setting
 *
 * @return      msg     The result of the setting operation
 */
static msg_t set_timeout(MAX7310Driver *devp, max7310_timeout_t timeout) {

    return MSG_OK;
}

static const struct MAX7310VMT vmt_device = {
    (size_t)0,
    set_output, set_polarity, set_iomode, set_timeout
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
    uint8_t cr[5];
    osalDbgCheck((devp != NULL) && (config != NULL));

    osalDbgAssert((devp->state == MAX7310_STOP) ||
            (devp->state == MAX7310_READY),
            "max7310Start(), invalid state");

    devp->config = config;

    /* Configuring common registers.*/
    cr[0] = MAX7310_AD_OUTPUT_REG;
    cr[1] = devp->config->output;
    cr[2] = devp->config->polarity;
    cr[3] = devp->config->iomode;
    cr[4] = devp->config->timeout;
#if MAX7310_USE_I2C
#if MAX7310_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
#endif /* MAX7310_SHARED_I2C */

    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
    max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr,
            cr, 5);

#if MAX7310_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
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
        cr[0] = MAX7310_AD_CONFIG_REG;
        cr[1] = 0xFF;
        max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr,
                cr, 1);

        /* Reset output reg to 0.*/
        cr[0] = MAX7310_AD_OUTPUT_REG;
        cr[1] = 0;
        max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr,
                cr, 1);

        /* Reset polarity.*/
        cr[0] = MAX7310_AD_POLARITY_REG;
        cr[1] = 0xF0;
        max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr,
                cr, 1);

        /* Reset timeout.*/
        cr[0] = MAX7310_AD_TIMEOUT;
        cr[1] = MAX7310_TIMEOUT_ENABLED;
        max7310I2CWriteRegister(devp->config->i2cp, devp->config->saddr,
                cr, 1);

        i2cStop(devp->config->i2cp);
#if MAX7310_SHARED_I2C
        i2cReleaseBus(devp->config->i2cp);
#endif /* MAX7310_SHARED_I2C */
#endif /* MAX7310_USE_I2C */
    }
    devp->state = MAX7310_STOP;
}
/** @} */
