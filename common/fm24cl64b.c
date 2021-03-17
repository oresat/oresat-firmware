/**
 * @file    fm24cl64b.c
 * @brief   FM24CL64B Digital to Analog Converter.
 *
 * @addtogroup FM24CL64B
 * @ingrup ORESAT
 * @{
 */

#include "hal.h"
#include "fm24cl64b.h"

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

#if (FM24CL64B_USE_I2C) || defined(__DOXYGEN__)
/**
 * @brief   Reads registers value using I2C.
 * @pre     The I2C interface must be initialized and the driver started.
 *
 * @param[in]  i2cp      pointer to the I2C interface
 * @param[in]  saddr     slave address without R bit
 * @param[in]  addr      address
 * @param[out] rxbuf     pointer to an output buffer
 * @param[in]  n         number of consecutive register to read
 * @return               the operation status.
 * @notapi
 */
msg_t fm24cl64bI2CReadAddr(I2CDriver *i2cp, i2caddr_t saddr, uint16_t addr,
        uint8_t* rxbuf, size_t n) {
    return i2cMasterTransmitTimeout(i2cp, saddr, &reg, 1, rxbuf, n,
            TIME_INFINITE);
}

/**
 * @brief   Writes a value into a register using I2C.
 * @pre     The I2C interface must be initialized and the driver started.
 *
 * @param[in] i2cp       pointer to the I2C interface
 * @param[in] saddr      slave address without R bit
 * @param[in] txbuf      buffer containing address in first two bytes and data
 * @param[in] n          size of txbuf
 * @return               the operation status.
 * @notapi
 */
msg_t fm24cl64bI2CWriteAddr(I2CDriver *i2cp, i2caddr_t saddr,
        uint8_t *txbuf, size_t n) {
    return i2cMasterTransmitTimeout(i2cp, saddr, txbuf, n, NULL, 0,
            TIME_INFINITE);
}
#endif /* FM24CL64B_USE_I2C */

/*==========================================================================*/
/* Interface implementation.                                                */
/*==========================================================================*/

static const struct FM24CL64BVMT vmt_device = {
    (size_t)0,
};

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Initializes an instance.
 *
 * @param[out] devp     pointer to the @p FM24CL64BDriver object
 *
 * @init
 */
void fm24cl64bObjectInit(FM24CL64BDriver *devp) {
    devp->vmt = &vmt_device;

    devp->config = NULL;

    devp->state = FM24CL64B_STOP;
}

/**
 * @brief   Configures and activates FM24CL64B Complex Driver peripheral.
 *
 * @param[in] devp      pointer to the @p FM24CL64BDriver object
 * @param[in] config    pointer to the @p FM24CL64BConfig object
 *
 * @api
 */
void fm24cl64bStart(FM24CL64BDriver *devp, const FM24CL64BConfig *config) {
    osalDbgCheck((devp != NULL) && (config != NULL));
    osalDbgAssert((devp->state == FM24CL64B_STOP) ||
            (devp->state == FM24CL64B_READY),
            "fm24cl64bStart(), invalid state");

    devp->config = config;

    /* Configuring common registers.*/
#if FM24CL64B_USE_I2C
#if FM24CL64B_SHARED_I2C
    i2cAcquireBus(config->i2cp);
#endif /* FM24CL64B_SHARED_I2C */

    i2cStart(config->i2cp, config->i2ccfg);

#if FM24CL64B_SHARED_I2C
    i2cReleaseBus(config->i2cp);
#endif /* FM24CL64B_SHARED_I2C */
#endif /* FM24CL64B_USE_I2C */
    devp->state = FM24CL64B_READY;
}

/**
 * @brief   Deactivates the FM24CL64B Complex Driver peripheral.
 *
 * @param[in] devp       pointer to the @p FM24CL64BDriver object
 *
 * @api
 */
void fm24cl64bStop(FM24CL64BDriver *devp) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state == FM24CL64B_STOP) || (devp->state == FM24CL64B_READY),
            "fm24cl64bStop(), invalid state");

    if (devp->state == FM24CL64B_READY) {
#if FM24CL64B_USE_I2C
#if FM24CL64B_SHARED_I2C
        i2cAcquireBus(devp->config->i2cp);
        i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* FM24CL64B_SHARED_I2C */

        i2cStop(devp->config->i2cp);

#if FM24CL64B_SHARED_I2C
        i2cReleaseBus(devp->config->i2cp);
#endif /* FM24CL64B_SHARED_I2C */
#endif /* FM24CL64B_USE_I2C */
    }
    devp->state = FM24CL64B_STOP;
}

/**
 * @brief   Reads FM24CL64B memory.
 *
 * @param[in]  devp       pointer to the @p FM24CL64BDriver object
 * @param[in]  addr       the address to start reading from
 * @param[out] buf        the buffer to read data into
 * @param[in]  n          number of bytes to read
 *
 * @api
 */
void fm24cl64bRead(FM24CL64BDriver *devp, uint16_t addr, void *buf, size_t n) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == FM24CL64B_READY,
            "fm24cl64bReadRaw(), invalid state");

#if FM24CL64B_USE_I2C
#if FM24CL64B_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* FM24CL64B_SHARED_I2C */

    fm24cl64bI2CReadAddr(devp->config->i2cp, devp->config->saddr, addr, buf, n);

#if FM24CL64B_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* FM24CL64B_SHARED_I2C */
#endif /* FM24CL64B_USE_I2C */
    return;
}

/**
 * @brief   Writes FM24CL64B memory.
 *
 * @param[in]  devp       pointer to the @p FM24CL64BDriver object
 * @param[in]  addr       the address to start writing to
 * @param[out] buf        the buffer to read data from
 * @param[in]  n          number of bytes to write
 *
 * @api
 */
void fm24cl64bWrite(FM24CL64BDriver *devp, uint16_t addr, void *buf, size_t n) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == FM24CL64B_READY,
            "fm24cl64bReadRaw(), invalid state");

#if FM24CL64B_USE_I2C
#if FM24CL64B_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* FM24CL64B_SHARED_I2C */

    fm24cl64bI2CWriteAddr(devp->config->i2cp, devp->config->saddr, buf, n);

#if FM24CL64B_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* FM24CL64B_SHARED_I2C */
#endif /* FM24CL64B_USE_I2C */
    return;
}

/** @} */

