/**
 * @file    si41xx.c
 * @brief   SI41XX Radio.
 *
 * @addtogroup SI41XX
 * @ingrup ORESAT
 * @{
 */

#include "hal.h"
#include "si41xx.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/**
 * @name    SI41XX SERIAL Word fields
 * @{
 */
#define SI41XX_ADDRESS_Pos                  (0U)
#define SI41XX_ADDRESS_Msk                  (0xFU << SI41XX_ADDRESS_Pos)
#define SI41XX_ADDRESS                      SI41XX_ADDRESS_Msk
#define SI41XX_DATA_Pos                     (5U)
#define SI41XX_DATA_Msk                     (0x3FFFFU << SI41XX_DATA_Pos)
#define SI41XX_DATA                         SI41XX_DATA_Msk
#define SI41XX_MSB_Pos                      (21U)
#define SI41XX_MSB_Msk                      (0x1U << SI41XX_MSB_Pos)
#define SI41XX_MSB                          SI41XX_MSB_Msk
#define SI41XX_WORD_Pos                     (0U)
#define SI41XX_WORD_Msk                     (0x3FFFFFU << SI41XX_WORD_Pos)
#define SI41XX_WORD                         SI41XX_WORD_Msk
/** @} */

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

#if (SI41XX_USE_SERIAL) || defined(__DOXYGEN__)
/**
 * @brief   Writes to an SI41xx device using its serial interface.
 *
 * @param[in]   devp        SI41XXDriver
 * @param[in]   addr        Register address
 * @param[in]   data        Data to write to register
 *
 * @notapi
 */
void si41xxWriteRegister(SI41XXDriver *devp, uint8_t addr, uint32_t data) {
    uint32_t word = _VAL2FLD(SI41XX_ADDRESS, addr)
                  | _VAL2FLD(SI41XX_DATA, data);

    osalDbgCheck((devp != NULL) && (devp->config != NULL));

    palClearLine(devp->config->sen);

    while (word & SI41XX_WORD) {
        palClearLine(devp->config->sclk);

        palWriteLine(devp->config->sdata, (word & SI41XX_MSB ? PAL_HIGH : PAL_LOW));
        palSetLine(devp->config->sclk);
        word <<= 1;
    }

    palSetLine(devp->config->sen);
}

#if (SI41XX_USE_MUTUAL_EXCLUSION == TRUE) || defined(__DOXYGEN__)
/**
 * @brief   Gains exclusive access to the I2C bus.
 * @details This function tries to gain ownership to the I2C bus, if the bus
 *          is already being used then the invoking thread is queued.
 * @pre     In order to use this function the option @p I2C_USE_MUTUAL_EXCLUSION
 *          must be enabled.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @notapi
 */
void si41xxAcquireBus(SI41XXDriver *devp) {
  osalDbgCheck(devp != NULL);

  osalMutexLock(&devp->mutex);
}

/**
 * @brief   Releases exclusive access to the I2C bus.
 * @pre     In order to use this function the option @p I2C_USE_MUTUAL_EXCLUSION
 *          must be enabled.
 *
 * @param[in] i2cp      pointer to the @p I2CDriver object
 *
 * @api
 */
void si41xxReleaseBus(SI41XXDriver *devp) {
  osalDbgCheck(devp != NULL);

  osalMutexUnlock(&devp->mutex);
}
#endif /* SI41XX_USE_MUTUAL_EXCLUSION == TRUE */

#endif /* SI41XX_USE_SERIAL */

/*==========================================================================*/
/* Interface implementation.                                                */
/*==========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

void si41xxObjectInit(SI41XXDriver *devp) {
    devp->config = NULL;

#if SI41XX_USE_MUTUAL_EXCLUSION == TRUE
    osalMutexObjectInit(&devp->mutex);
#endif

    devp->state = SI41XX_STOP;
}

void si41xxStart(SI41XXDriver *devp, const SI41XXConfig *config) {
    osalDbgCheck((devp != NULL) && (config != NULL));
    osalDbgAssert((devp->state == SI41XX_STOP) || (devp->state == SI41XX_READY),
            "si41xxStart(), invalid state");

#if SI41XX_USE_SERIAL
#if SI41XX_SHARED_SERIAL
    si41xxAcquireBus(devp);
#endif /* SI41XX_SHARED_SERIAL */

    si41xxWriteRegister(devp, SI41XX_REG_CONFIG, SI41XX_CONFIG_AUTOKP | _VAL2FLD(SI41XX_CONFIG_AUXSEL, SI41XX_AUXSEL_LOCKDET));
    si41xxWriteRegister(devp, SI41XX_REG_PHASE_GAIN, 0x00000);
#if SI41XX_HAS_IF
    si41xxWriteRegister(devp, SI41XX_REG_IF_NDIV, devp->config->if_n);
    si41xxWriteRegister(devp, SI41XX_REG_IF_RDIV, devp->config->if_r);
#endif
#if SI41XX_HAS_RF1
    si41xxWriteRegister(devp, SI41XX_REG_RF1_NDIV, devp->config->rf1_n);
    si41xxWriteRegister(devp, SI41XX_REG_RF1_RDIV, devp->config->rf1_r);
#endif
#if SI41XX_HAS_RF2
    si41xxWriteRegister(devp, SI41XX_REG_RF2_NDIV, devp->config->rf2_n);
    si41xxWriteRegister(devp, SI41XX_REG_RF2_RDIV, devp->config->rf2_r);
#endif
    si41xxWriteRegister(devp, SI41XX_REG_PWRDOWN, SI41XX_POWERDOWN_PBRB | SI41XX_POWERDOWN_PBIB);

#if SI41XX_SHARED_SERIAL
    si41xxReleaseBus(devp);
#endif /* SI41XX_SHARED_SERIAL */
#endif /* SI41XX_USE_SERIAL */
    devp->state = SI41XX_READY;
}

void si41xxStop(SI41XXDriver *devp) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state == SI41XX_STOP) || (devp->state == SI41XX_READY),
            "si41xxStop(), invalid state");

#if SI41XX_USE_SERIAL
#if SI41XX_SHARED_SERIAL
    si41xxAcquireBus(devp);
#endif /* SI41XX_SHARED_SERIAL */

#if SI41XX_SHARED_SERIAL
    si41xxReleaseBus(devp);
#endif /* SI41XX_SHARED_SERIAL */
#endif /* SI41XX_USE_SERIAL */
    devp->state = SI41XX_STOP;
}

void si41xxWriteRaw(SI41XXDriver *devp, uint8_t reg, uint32_t value) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state == SI41XX_STOP) || (devp->state == SI41XX_READY),
            "si41xxWriteRaw(), invalid state");

#if SI41XX_USE_SERIAL
#if SI41XX_SHARED_SERIAL
    si41xxAcquireBus(devp);
#endif /* SI41XX_SHARED_SERIAL */

    si41xxWriteRegister(devp, reg, value);

#if SI41XX_SHARED_SERIAL
    si41xxReleaseBus(devp);
#endif /* SI41XX_SHARED_SERIAL */
#endif /* SI41XX_USE_SERIAL */
}

/** @} */
