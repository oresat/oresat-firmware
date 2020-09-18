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
#define SI41XX_DATA_Pos                     (4U)
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
 * @param[in]   devp        Pointer to the @p SI41XXDriver object
 * @param[in]   addr        Register address
 * @param[in]   data        Data to write to register
 *
 * @notapi
 */
void si41xxWriteRegister(SI41XXDriver *devp, uint8_t addr, uint32_t data) {
    uint32_t i = 22;
    uint32_t word = _VAL2FLD(SI41XX_ADDRESS, addr)
                  | _VAL2FLD(SI41XX_DATA, data);

    osalDbgCheck((devp != NULL) && (devp->config != NULL));

    palClearLine(devp->config->sen);

    while (i--) {
        palClearLine(devp->config->sclk);

        palWriteLine(devp->config->sdata, (word & SI41XX_MSB ? PAL_HIGH : PAL_LOW));
        palSetLine(devp->config->sclk);
        word <<= 1;
    }

    palSetLine(devp->config->sen);
}

#if (SI41XX_USE_MUTUAL_EXCLUSION) || defined(__DOXYGEN__)
/**
 * @brief   Gains exclusive access to the SI41XX bus.
 * @details This function tries to gain ownership to the SI41XX bus, if the bus
 *          is already being used then the invoking thread is queued.
 * @pre     In order to use this function the option @p SI41XX_USE_MUTUAL_EXCLUSION
 *          must be enabled.
 *
 * @param[in]   devp        Pointer to the @p SI41XXDriver object
 *
 * @notapi
 */
void si41xxAcquireBus(SI41XXDriver *devp) {
  osalDbgCheck(devp != NULL);

  osalMutexLock(&devp->mutex);
}

/**
 * @brief   Releases exclusive access to the SI41XX bus.
 * @pre     In order to use this function the option @p SI41XX_USE_MUTUAL_EXCLUSION
 *          must be enabled.
 *
 * @param[in]   devp        Pointer to the @p SI41XXDriver object
 *
 * @notapi
 */
void si41xxReleaseBus(SI41XXDriver *devp) {
  osalDbgCheck(devp != NULL);

  osalMutexUnlock(&devp->mutex);
}
#endif /* SI41XX_USE_MUTUAL_EXCLUSION */
#endif /* SI41XX_USE_SERIAL */

/**
 * @brief   Calculates N-Div and R-Div values.
 * @details This function calculates N and R division values needed to provided
 *          the specified frequency from the reference frequency defined in the
 *          device configuration.
 *
 * @param[in]   devp        Pointer to the @p SI41XXDriver object
 * @param[in]   freq        Desired output frequency
 * @param[out]  ndiv        Calculated N-Divider value
 * @param[out]  rdiv        Calculated R-Divider value
 *
 * @notapi
 */
void si41xxCalcDiv(SI41XXDriver *devp, uint32_t freq, uint32_t *ndiv, uint32_t *rdiv) {
    osalDbgCheck(devp != NULL && devp->config != NULL && ndiv != NULL && rdiv != NULL);
    osalDbgAssert(devp->config->ref_freq != 0 && freq != 0,
            "si41xxCalcDiv(), non-zero values required");

    uint32_t ref_freq = devp->config->ref_freq;
    uint32_t n1 = ref_freq, n2 = freq;

    /* Find GCD of both frequencies */
    while (n1 != n2) {
        if (n1 > n2) {
            n1 -= n2;
        } else {
            n2 -= n1;
        }
    }
    /* Calculate needed N and R values */
    *ndiv = freq / n1;
    *rdiv = ref_freq / n1;
}

/*==========================================================================*/
/* Interface implementation.                                                */
/*==========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Initializes an instance.
 *
 * @param[out]  devp        Pointer to the @p SI41XXDriver object
 *
 * @init
 */
void si41xxObjectInit(SI41XXDriver *devp) {
    devp->config = NULL;

#if SI41XX_USE_MUTUAL_EXCLUSION
    osalMutexObjectInit(&devp->mutex);
#endif

    devp->state = SI41XX_STOP;
}

/**
 * @brief   Configures and activates SI41XX Driver peripheral.
 *
 * @param[in]   devp        Pointer to the @p SI41XXDriver object
 * @param[in]   config      Pointer to the @p SI41XXConfig object
 *
 * @api
 */
void si41xxStart(SI41XXDriver *devp, SI41XXConfig *config) {
    osalDbgCheck((devp != NULL) && (config != NULL));
    osalDbgAssert((devp->state == SI41XX_STOP) || (devp->state == SI41XX_READY),
            "si41xxStart(), invalid state");

    devp->config = config;

#if SI41XX_USE_SERIAL
#if SI41XX_SHARED_SERIAL
    si41xxAcquireBus(devp);
#endif /* SI41XX_SHARED_SERIAL */

    si41xxWriteRegister(devp, SI41XX_REG_CONFIG, SI41XX_CONFIG_AUTOKP | SI41XX_CONFIG_AUTOPDB |
                                        _VAL2FLD(SI41XX_CONFIG_AUXSEL, SI41XX_AUXSEL_LOCKDET) |
                                        _VAL2FLD(SI41XX_CONFIG_IFDIV, config->if_div));
    si41xxWriteRegister(devp, SI41XX_REG_PHASE_GAIN, 0x00000U);
#if SI41XX_HAS_IF
    si41xxWriteRegister(devp, SI41XX_REG_IF_NDIV, _VAL2FLD(SI41XX_IF_NDIV, devp->config->if_n));
    si41xxWriteRegister(devp, SI41XX_REG_IF_RDIV, _VAL2FLD(SI41XX_IF_RDIV, devp->config->if_r));
#endif
#if SI41XX_HAS_RF1
    si41xxWriteRegister(devp, SI41XX_REG_RF1_NDIV, _VAL2FLD(SI41XX_RF1_NDIV, devp->config->rf1_n));
    si41xxWriteRegister(devp, SI41XX_REG_RF1_RDIV, _VAL2FLD(SI41XX_RF1_RDIV, devp->config->rf1_r));
#endif
#if SI41XX_HAS_RF2
    si41xxWriteRegister(devp, SI41XX_REG_RF2_NDIV, _VAL2FLD(SI41XX_RF2_NDIV, devp->config->rf2_n));
    si41xxWriteRegister(devp, SI41XX_REG_RF2_RDIV, _VAL2FLD(SI41XX_RF2_RDIV, devp->config->rf2_r));
#endif

#if SI41XX_SHARED_SERIAL
    si41xxReleaseBus(devp);
#endif /* SI41XX_SHARED_SERIAL */
#endif /* SI41XX_USE_SERIAL */
    devp->state = SI41XX_READY;
}

/**
 * @brief   Deactivates the SI41XX Complex Driver peripheral.
 *
 * @param[in]   devp        Pointer to the @p SI41XXDriver object
 *
 * @api
 */
void si41xxStop(SI41XXDriver *devp) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state == SI41XX_STOP) || (devp->state == SI41XX_READY),
            "si41xxStop(), invalid state");

#if SI41XX_USE_SERIAL
#if SI41XX_SHARED_SERIAL
    si41xxAcquireBus(devp);
#endif /* SI41XX_SHARED_SERIAL */

    si41xxWriteRegister(devp, SI41XX_REG_PWRDOWN, 0x00000U);
    si41xxWriteRegister(devp, SI41XX_REG_CONFIG, 0x00000U);

#if SI41XX_SHARED_SERIAL
    si41xxReleaseBus(devp);
#endif /* SI41XX_SHARED_SERIAL */
#endif /* SI41XX_USE_SERIAL */
    devp->state = SI41XX_STOP;
}

/**
 * @brief   Writes a raw value to an SI41XX register.
 *
 * @param[in]   devp        Pointer to the @p SI41XXDriver object
 * @param[in]   reg         The register to write to
 * @param[in]   value       The value to write
 *
 * @api
 */
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

#if (SI41XX_HAS_IF) || defined(__DOXYGEN__)
/**
 * @brief   Sets IF N and R values to provide the desired frequency.
 *
 * @param[in]   devp        Pointer to the @p SI41XXDriver object
 * @param[in]   freq        The desired frequency
 *
 * @return                  Successfully set frequency
 * @api
 */
bool si41xxSetIF(SI41XXDriver *devp, uint32_t freq) {
    uint32_t n, r;
    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state == SI41XX_READY),
            "si41xxSetIF(), invalid state");

    /* Calculate N and R values */
    si41xxCalcDiv(devp, freq << devp->config->if_div, &n, &r);

    /* Check that values are within bounds of programmable values */
    if (n >= (SI41XX_IF_NDIV + 1) || r >= (SI41XX_IF_RDIV + 1)) {
        return false;
    }
    devp->config->if_n = n;
    devp->config->if_r = r;

#if SI41XX_USE_SERIAL
#if SI41XX_SHARED_SERIAL
    si41xxAcquireBus(devp);
#endif /* SI41XX_SHARED_SERIAL */

    si41xxWriteRegister(devp, SI41XX_REG_IF_NDIV, _VAL2FLD(SI41XX_IF_NDIV, n));
    si41xxWriteRegister(devp, SI41XX_REG_IF_RDIV, _VAL2FLD(SI41XX_IF_RDIV, r));

#if SI41XX_SHARED_SERIAL
    si41xxReleaseBus(devp);
#endif /* SI41XX_SHARED_SERIAL */
#endif /* SI41XX_USE_SERIAL */
    return true;
}

/**
 * @brief   Sets IF divider value.
 *
 * @param[in]   devp        Pointer to the @p SI41XXDriver object
 * @param[in]   div         The divisor (1,2,4,8)
 *
 * @return                  Successfully set divisor
 * @api
 */
bool si41xxSetIFDiv(SI41XXDriver *devp, uint8_t div) {
    uint8_t i;
    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state == SI41XX_READY),
            "si41xxSetIFDiv(), invalid state");

    /* Check that values are within bounds of programmable values */
    if (!((div != 0) && ((div & (div - 1))))) {
        return false;
    }
    for (i = 0; i < 4 && (div & 1); i++, div >>= 1);
    if (i == 4) {
        return false;
    }
    devp->config->if_div = i;

#if SI41XX_USE_SERIAL
#if SI41XX_SHARED_SERIAL
    si41xxAcquireBus(devp);
#endif /* SI41XX_SHARED_SERIAL */

    si41xxWriteRegister(devp, SI41XX_REG_CONFIG, _VAL2FLD(SI41XX_CONFIG_IFDIV, i));

#if SI41XX_SHARED_SERIAL
    si41xxReleaseBus(devp);
#endif /* SI41XX_SHARED_SERIAL */
#endif /* SI41XX_USE_SERIAL */
    return true;
}
#endif /* SI41XX_HAS_IF */

#if (SI41XX_HAS_RF1) || defined(__DOXYGEN__)
/**
 * @brief   Sets RF1 dividers to provide the desired frequency.
 *
 * @param[in]   devp        Pointer to the @p SI41XXDriver object
 * @param[in]   freq        The desired frequency
 *
 * @return                  Successfully set frequency
 * @api
 */
bool si41xxSetRF1(SI41XXDriver *devp, uint32_t freq) {
    uint32_t n, r;
    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state == SI41XX_READY),
            "si41xxSetRF1(), invalid state");

    /* Calculate N and R values */
    si41xxCalcDiv(devp, freq, &n, &r);

    /* Check that values are within bounds of programmable values */
    if (n >= (SI41XX_RF1_NDIV + 1) || r >= (SI41XX_RF1_RDIV + 1)) {
        return false;
    }
    devp->config->rf1_n = n;
    devp->config->rf1_r = r;

#if SI41XX_USE_SERIAL
#if SI41XX_SHARED_SERIAL
    si41xxAcquireBus(devp);
#endif /* SI41XX_SHARED_SERIAL */

    si41xxWriteRegister(devp, SI41XX_REG_RF1_NDIV, _VAL2FLD(SI41XX_RF1_NDIV, n));
    si41xxWriteRegister(devp, SI41XX_REG_RF1_RDIV, _VAL2FLD(SI41XX_RF1_RDIV, r));

#if SI41XX_SHARED_SERIAL
    si41xxReleaseBus(devp);
#endif /* SI41XX_SHARED_SERIAL */
#endif /* SI41XX_USE_SERIAL */
    return true;
}
#endif /* SI41XX_HAS_RF1 */

#if (SI41XX_HAS_RF2) || defined(__DOXYGEN__)
/**
 * @brief   Sets RF2 dividers to provide the desired frequency.
 *
 * @param[in]   devp        Pointer to the @p SI41XXDriver object
 * @param[in]   freq        The desired frequency
 *
 * @return                  Successfully set frequency
 * @api
 */
bool si41xxSetRF2(SI41XXDriver *devp, uint32_t freq) {
    uint32_t n, r;
    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state == SI41XX_READY),
            "si41xxSetRF2(), invalid state");

    /* Calculate N and R values */
    si41xxCalcDiv(devp, freq, &n, &r);

    /* Check that values are within bounds of programmable values */
    if (n >= (SI41XX_RF2_NDIV + 1) || r >= (SI41XX_RF2_RDIV + 1)) {
        return false;
    }
    devp->config->rf2_n = n;
    devp->config->rf2_r = r;

#if SI41XX_USE_SERIAL
#if SI41XX_SHARED_SERIAL
    si41xxAcquireBus(devp);
#endif /* SI41XX_SHARED_SERIAL */

    si41xxWriteRegister(devp, SI41XX_REG_RF2_NDIV, _VAL2FLD(SI41XX_RF2_NDIV, n));
    si41xxWriteRegister(devp, SI41XX_REG_RF2_RDIV, _VAL2FLD(SI41XX_RF2_RDIV, r));

#if SI41XX_SHARED_SERIAL
    si41xxReleaseBus(devp);
#endif /* SI41XX_SHARED_SERIAL */
#endif /* SI41XX_USE_SERIAL */
    return true;
}
#endif /* SI41XX_HAS_RF2 */

/** @} */
