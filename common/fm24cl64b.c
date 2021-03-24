/**
 * @file    fm24cl64b.c
 * @brief   FM24CL64B Digital to Analog Converter.
 *
 * @addtogroup FM24CL64B
 * @ingrup ORESAT
 * @{
 */

#include <string.h>
#include "hal.h"
#include "fm24cl64b.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/
#define BLOCK_SIZE                          512U

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/
FM24CL64BDriver FRAMD1;

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

typedef union {
    struct __attribute__((packed)) {
        uint16_t addr;
        uint8_t data[BLOCK_SIZE];
    };
    uint8_t buf[sizeof(uint16_t) + BLOCK_SIZE];
} i2cbuf_t;

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

#if (FM24CL64B_USE_I2C) || defined(__DOXYGEN__)
/**
 * @brief   Reads registers value using I2C.
 * @pre     The I2C interface must be initialized and the driver started.
 *
 * @param[in]  i2cp     pointer to the I2C interface
 * @param[in]  saddr    slave address without R bit
 * @param[in]  addr     address
 * @param[out] rxbuf    pointer to an output buffer
 * @param[in]  n        number of consecutive register to read
 * @return              the operation status.
 * @notapi
 */
msg_t fm24cl64bI2CReadAddr(I2CDriver *i2cp, i2caddr_t saddr, uint16_t addr,
        uint8_t* rxbuf, size_t n) {
    addr = __REVSH(addr);
    return i2cMasterTransmitTimeout(i2cp, saddr, (uint8_t*)(&addr), sizeof(addr), rxbuf, n, TIME_INFINITE);
}

/**
 * @brief   Writes a value into a register using I2C.
 * @pre     The I2C interface must be initialized and the driver started.
 *
 * @param[in]  i2cp     pointer to the I2C interface
 * @param[in]  saddr    slave address without R bit
 * @param[in]  addr     address
 * @param[in]  txbuf    buffer containing address in first two bytes and data
 * @param[in]  n        size of txbuf
 * @return              the operation status.
 * @notapi
 */
msg_t fm24cl64bI2CWriteAddr(I2CDriver *i2cp, i2caddr_t saddr, uint16_t addr,
        uint8_t *txbuf, size_t n) {
    i2cbuf_t i2cbuf;
    size_t size, offset = 0;
    msg_t ret;

    while (n) {
        size = (n < BLOCK_SIZE ? n : BLOCK_SIZE);
        i2cbuf.addr = __REVSH(addr + offset);
        memcpy(i2cbuf.data, &txbuf[offset], size);
        ret = i2cMasterTransmitTimeout(i2cp, saddr, i2cbuf.buf, sizeof(i2cbuf.buf), NULL, 0, TIME_INFINITE);
        offset += size;
        n -= size;
    }

    return ret;
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

    fm24cl64bI2CWriteAddr(devp->config->i2cp, devp->config->saddr, addr, buf, n);

#if FM24CL64B_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* FM24CL64B_SHARED_I2C */
#endif /* FM24CL64B_USE_I2C */
    return;
}

/** @} */

