/**
 * @file    fram.c
 * @brief   FRAM Driver Implementation.
 *
 * @addtogroup FRAM
 * @ingrup ORESAT
 * @{
 */

#include <string.h>
#include "hal.h"
#include "fram.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/
#define BLOCK_SIZE                          512U

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/
FRAMDriver FRAMD1;

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

#if (FRAM_USE_I2C) || defined(__DOXYGEN__)
/**
 * @brief   Reads F-RAM memory using I2C.
 * @pre     The I2C interface must be initialized and the driver started.
 *
 * @param[in]  i2cp     pointer to the I2C interface
 * @param[in]  saddr    slave address without R bit
 * @param[in]  addr     address
 * @param[out] rxbuf    pointer to an output buffer
 * @param[in]  n        number of consecutive bytes to read
 * @return              the operation status.
 * @notapi
 */
msg_t framI2CReadAddr(I2CDriver *i2cp, i2caddr_t saddr, uint16_t addr,
        uint8_t* rxbuf, size_t n) {
    addr = __REVSH(addr);
    return i2cMasterTransmitTimeout(i2cp, saddr, (uint8_t*)(&addr), sizeof(addr), rxbuf, n, TIME_INFINITE);
}

/**
 * @brief   Writes F-RAM memory using I2C.
 * @pre     The I2C interface must be initialized and the driver started.
 *
 * @param[in]  i2cp     pointer to the I2C interface
 * @param[in]  saddr    slave address without R bit
 * @param[in]  addr     address
 * @param[in]  txbuf    buffer containing data
 * @param[in]  n        number of consecutive bytes to write
 * @return              the operation status.
 * @notapi
 */
msg_t framI2CWriteAddr(I2CDriver *i2cp, i2caddr_t saddr, uint16_t addr,
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
#endif /* FRAM_USE_I2C */

/*==========================================================================*/
/* Interface implementation.                                                */
/*==========================================================================*/

static const struct FRAMVMT vmt_device = {
    (size_t)0,
};

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Initializes an instance.
 *
 * @param[out] devp     pointer to the @p FRAMDriver object
 *
 * @init
 */
void framObjectInit(FRAMDriver *devp) {
    devp->vmt = &vmt_device;

    devp->config = NULL;

    devp->state = FRAM_STOP;
}

/**
 * @brief   Configures and activates FRAM Complex Driver peripheral.
 *
 * @param[in] devp      pointer to the @p FRAMDriver object
 * @param[in] config    pointer to the @p FRAMConfig object
 *
 * @api
 */
void framStart(FRAMDriver *devp, const FRAMConfig *config) {
    osalDbgCheck((devp != NULL) && (config != NULL));
    osalDbgAssert((devp->state == FRAM_STOP) ||
            (devp->state == FRAM_READY),
            "framStart(), invalid state");

    devp->config = config;

    /* Configuring common registers.*/
#if FRAM_USE_I2C
#if FRAM_SHARED_I2C
    i2cAcquireBus(config->i2cp);
#endif /* FRAM_SHARED_I2C */

    i2cStart(config->i2cp, config->i2ccfg);

#if FRAM_SHARED_I2C
    i2cReleaseBus(config->i2cp);
#endif /* FRAM_SHARED_I2C */
#endif /* FRAM_USE_I2C */
    devp->state = FRAM_READY;
}

/**
 * @brief   Deactivates the FRAM Complex Driver peripheral.
 *
 * @param[in] devp       pointer to the @p FRAMDriver object
 *
 * @api
 */
void framStop(FRAMDriver *devp) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state == FRAM_STOP) || (devp->state == FRAM_READY),
            "framStop(), invalid state");

    if (devp->state == FRAM_READY) {
#if FRAM_USE_I2C
#if FRAM_SHARED_I2C
        i2cAcquireBus(devp->config->i2cp);
        i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* FRAM_SHARED_I2C */

        i2cStop(devp->config->i2cp);

#if FRAM_SHARED_I2C
        i2cReleaseBus(devp->config->i2cp);
#endif /* FRAM_SHARED_I2C */
#endif /* FRAM_USE_I2C */
    }
    devp->state = FRAM_STOP;
}

/**
 * @brief   Reads FRAM memory.
 *
 * @param[in]  devp       pointer to the @p FRAMDriver object
 * @param[in]  addr       the address to start reading from
 * @param[out] buf        the buffer to read data into
 * @param[in]  n          number of bytes to read
 *
 * @api
 */
void framRead(FRAMDriver *devp, uint16_t addr, void *buf, size_t n) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == FRAM_READY,
            "framReadRaw(), invalid state");

#if FRAM_USE_I2C
#if FRAM_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* FRAM_SHARED_I2C */

    framI2CReadAddr(devp->config->i2cp, devp->config->saddr, addr, buf, n);

#if FRAM_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* FRAM_SHARED_I2C */
#endif /* FRAM_USE_I2C */
    return;
}

/**
 * @brief   Writes FRAM memory.
 *
 * @param[in]  devp       pointer to the @p FRAMDriver object
 * @param[in]  addr       the address to start writing to
 * @param[out] buf        the buffer to read data from
 * @param[in]  n          number of bytes to write
 *
 * @api
 */
void framWrite(FRAMDriver *devp, uint16_t addr, void *buf, size_t n) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == FRAM_READY,
            "framReadRaw(), invalid state");

#if FRAM_USE_I2C
#if FRAM_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* FRAM_SHARED_I2C */

    framI2CWriteAddr(devp->config->i2cp, devp->config->saddr, addr, buf, n);

#if FRAM_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* FRAM_SHARED_I2C */
#endif /* FRAM_USE_I2C */
    return;
}

/** @} */

