/**
 * @file    si41xx.h
 * @brief   SI41XX Radio.
 *
 * @addtogroup SI41XX
 * @ingroup ORESAT
 * @{
 */
#ifndef _SI41XX_H_
#define _SI41XX_H_

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    Version Identification
 * @{
 */
/**
 * @brief   SI41XX Driver version string.
 */
#define SI41XX_VERSION                      "1.0.0"

/**
 * @brief   SI41XX Driver version major number.
 */
#define SI41XX_MAJOR                        1

/**
 * @brief   SI41XX Driver version minor number.
 */
#define SI41XX_MINOR                        0

/**
 * @brief   SI41XX Driver version patch number.
 */
#define SI41XX_PATCH                        0
/** @} */

/**
 * @name    Device Types
 * @{
 */
#define SI4112                              0
#define SI4113                              1
#define SI4122                              2
#define SI4123                              3
#define SI4133                              4
/** @} */

/**
 * @name    SI41XX Register Addresses
 * @{
 */
#define SI41XX_REG_CONFIG                   0x0U
#define SI41XX_REG_PHASE_GAIN               0x1U
#define SI41XX_REG_PWRDOWN                  0x2U
#define SI41XX_REG_RF1_NDIV                 0x3U
#define SI41XX_REG_RF2_NDIV                 0x4U
#define SI41XX_REG_IF_NDIV                  0x5U
#define SI41XX_REG_RF1_RDIV                 0x6U
#define SI41XX_REG_RF2_RDIV                 0x7U
#define SI41XX_REG_IF_RDIV                  0x8U
/** @} */

/**
 * @name    SI41XX Main Configuration register fields
 * @{
 */
#define SI41XX_CONFIG_RFPWR_Pos             (1U)
#define SI41XX_CONFIG_RFPWR_Msk             (0x1U << SI41XX_CONFIG_RFPWR_Pos)
#define SI41XX_CONFIG_RFPWR                 SI41XX_CONFIG_RFPWR_Msk
#define SI41XX_CONFIG_AUTOKP_Pos            (2U)
#define SI41XX_CONFIG_AUTOKP_Msk            (0x1U << SI41XX_CONFIG_AUTOKP_Pos)
#define SI41XX_CONFIG_AUTOKP                SI41XX_CONFIG_AUTOKP_Msk
#define SI41XX_CONFIG_AUTOPDB_Pos           (3U)
#define SI41XX_CONFIG_AUTOPDB_Msk           (0x1U << SI41XX_CONFIG_AUTOPDB_Pos)
#define SI41XX_CONFIG_AUTOPDB               SI41XX_CONFIG_AUTOPDB_Msk
#define SI41XX_CONFIG_LPWR_Pos              (5U)
#define SI41XX_CONFIG_LPWR_Msk              (0x1U << SI41XX_CONFIG_LPWR_Pos)
#define SI41XX_CONFIG_LPWR                  SI41XX_CONFIG_LPWR_Msk
#define SI41XX_CONFIG_IFDIV_Pos             (10U)
#define SI41XX_CONFIG_IFDIV_Msk             (0x3U << SI41XX_CONFIG_IFDIV_Pos)
#define SI41XX_CONFIG_IFDIV                 SI41XX_CONFIG_IFDIV_Msk
#define SI41XX_IFDIV_DIV1                   (0x0U)
#define SI41XX_IFDIV_DIV2                   (0x1U)
#define SI41XX_IFDIV_DIV4                   (0x2U)
#define SI41XX_IFDIV_DIV8                   (0x3U)
#define SI41XX_CONFIG_AUXSEL_Pos            (12U)
#define SI41XX_CONFIG_AUXSEL_Msk            (0x3U << SI41XX_CONFIG_AUXSEL_Pos)
#define SI41XX_CONFIG_AUXSEL                SI41XX_CONFIG_AUXSEL_Msk
#define SI41XX_AUXSEL_LOW                   (0x1U)
#define SI41XX_AUXSEL_LOCKDET               (0x3U)
/** @} */

/**
 * @name    SI41XX Phase Detector Gain register fields
 * @{
 */
#define SI41XX_PHASEGAIN_KP1_Pos            (0U)
#define SI41XX_PHASEGAIN_KP1_Msk            (0x3U << SI41XX_PHASEGAIN_KP1_Pos)
#define SI41XX_PHASEGAIN_KP1                SI41XX_PHASEGAIN_KP1_Msk
#define SI41XX_PHASEGAIN_KP2_Pos            (2U)
#define SI41XX_PHASEGAIN_KP2_Msk            (0x3U << SI41XX_PHASEGAIN_KP2_Pos)
#define SI41XX_PHASEGAIN_KP2                SI41XX_PHASEGAIN_KP2_Msk
#define SI41XX_PHASEGAIN_KPI_Pos            (4U)
#define SI41XX_PHASEGAIN_KPI_Msk            (0x3U << SI41XX_PHASEGAIN_KPI_Pos)
#define SI41XX_PHASEGAIN_KPI                SI41XX_PHASEGAIN_KPI_Msk
/** @} */

/**
 * @name    SI41XX Powerdown register fields
 * @{
 */
#define SI41XX_POWERDOWN_PBRB_Pos           (0U)
#define SI41XX_POWERDOWN_PBRB_Msk           (0x1U << SI41XX_POWERDOWN_PBRB_Pos)
#define SI41XX_POWERDOWN_PBRB               SI41XX_POWERDOWN_PBRB_Msk
#define SI41XX_POWERDOWN_PBIB_Pos           (1U)
#define SI41XX_POWERDOWN_PBIB_Msk           (0x1U << SI41XX_POWERDOWN_PBIB_Pos)
#define SI41XX_POWERDOWN_PBIB               SI41XX_POWERDOWN_PBIB_Msk
/** @} */

/**
 * @name    SI41XX RF1 N-Divider register fields
 * @{
 */
#define SI41XX_RF1_NDIV_Pos                 (0U)
#define SI41XX_RF1_NDIV_Msk                 (0x3FFFFU << SI41XX_RF1_NDIV_Pos)
#define SI41XX_RF1_NDIV                     SI41XX_RF1_NDIV_Msk
/** @} */

/**
 * @name    SI41XX RF2 N-Divider register fields
 * @{
 */
#define SI41XX_RF2_NDIV_Pos                 (0U)
#define SI41XX_RF2_NDIV_Msk                 (0x1FFFFU << SI41XX_RF2_NDIV_Pos)
#define SI41XX_RF2_NDIV                     SI41XX_RF2_NDIV_Msk
/** @} */

/**
 * @name    SI41XX IF N-Divider register fields
 * @{
 */
#define SI41XX_IF_NDIV_Pos                  (0U)
#define SI41XX_IF_NDIV_Msk                  (0xFFFFU << SI41XX_IF_NDIV_Pos)
#define SI41XX_IF_NDIV                      SI41XX_IF_NDIV_Msk
/** @} */

/**
 * @name    SI41XX RF1 R-Divider register fields
 * @{
 */
#define SI41XX_RF1_RDIV_Pos                 (0U)
#define SI41XX_RF1_RDIV_Msk                 (0x1FFFU << SI41XX_RF1_RDIV_Pos)
#define SI41XX_RF1_RDIV                     SI41XX_RF1_RDIV_Msk
/** @} */

/**
 * @name    SI41XX RF2 R-Divider register fields
 * @{
 */
#define SI41XX_RF2_RDIV_Pos                 (0U)
#define SI41XX_RF2_RDIV_Msk                 (0x1FFFU << SI41XX_RF2_RDIV_Pos)
#define SI41XX_RF2_RDIV                     SI41XX_RF2_RDIV_Msk
/** @} */

/**
 * @name    SI41XX IF R-Divider register fields
 * @{
 */
#define SI41XX_IF_RDIV_Pos                  (0U)
#define SI41XX_IF_RDIV_Msk                  (0x1FFFU << SI41XX_IF_RDIV_Pos)
#define SI41XX_IF_RDIV                      SI41XX_IF_RDIV_Msk
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   SI41XX device type.
 * @details Defines the device type, which defines features availabe.
 * @note    The default is @p TRUE.
 */
#if !defined(SI41XX_DEVICE) || defined(__DOXYGEN__)
#define SI41XX_DEVICE                       SI4133
#endif

/**
 * @brief   SI41XX Mutual Exclusion.
 * @details Enables mutual exclusion code for SI41XX driver.
 * @note    The default is @p TRUE.
 */
#if !defined(SI41XX_USE_MUTUAL_EXCLUSION) || defined(__DOXYGEN__)
#define SI41XX_USE_MUTUAL_EXCLUSION         FALSE
#endif

/**
 * @brief   SI41XX SERIAL interface switch.
 * @details If set to @p TRUE the support for SI41XX SERIAL is included.
 * @note    The default is @p TRUE.
 */
#if !defined(SI41XX_USE_SERIAL) || defined(__DOXYGEN__)
#define SI41XX_USE_SERIAL                   TRUE
#endif

/**
 * @brief   SI41XX shared SERIAL switch.
 * @details If set to @p TRUE the device acquires SI41XX SERIAL bus ownership
 *          on each transaction.
 * @note    The default is @p FALSE. Requires SI41XX_USE_MUTUAL_EXCLUSION.
 */
#if !defined(SI41XX_SHARED_SERIAL) || defined(__DOXYGEN__)
#define SI41XX_SHARED_SERIAL                FALSE
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if SI41XX_USE_SERIAL && !HAL_USE_PAL
#error "SI41XX_USE_SERIAL requires HAL_USE_PAL"
#endif

#if SI41XX_SHARED_SERIAL && !SI41XX_USE_MUTUAL_EXCLUSION
#error "SI41XX_SHARED_SERIAL requires SI41XX_USE_MUTUAL_EXCLUSION"
#endif

#if (SI41XX_DEVICE != SI4112 && \
     SI41XX_DEVICE != SI4113 && \
     SI41XX_DEVICE != SI4122 && \
     SI41XX_DEVICE != SI4123 && \
     SI41XX_DEVICE != SI4133)
#error "SI41XX_DEVICE is unknown device type"
#endif

#if (SI41XX_DEVICE == SI4112 || SI41XX_DEVICE == SI4122 || SI41XX_DEVICE == SI4123 || SI41XX_DEVICE == SI4133)
#define SI41XX_HAS_IF                       TRUE
#else
#define SI41XX_HAS_IF                       FALSE
#endif

#if (SI41XX_DEVICE == SI4113 || SI41XX_DEVICE == SI4123 || SI41XX_DEVICE == SI4133)
#define SI41XX_HAS_RF1                      TRUE
#else
#define SI41XX_HAS_RF1                      FALSE
#endif

#if (SI41XX_DEVICE == SI4113 || SI41XX_DEVICE == SI4122 || SI41XX_DEVICE == SI4133)
#define SI41XX_HAS_RF2                      TRUE
#else
#define SI41XX_HAS_RF2                      FALSE
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @name    SI41XX data structures and types.
 * @{
 */
/**
 * @brief   Driver state machine possible states.
 */
typedef enum {
    SI41XX_UNINIT,              /**< Not initialized.                   */
    SI41XX_STOP,                /**< Stopped.                           */
    SI41XX_READY                /**< Ready.                             */
} si41xx_state_t;

/**
 * @brief   SI41XX configuration structure.
 */
typedef struct{
#if (SI41XX_USE_SERIAL) || defined(__DOXYGEN__)
    /**
     * @brief   SI41XX SERIAL Enable Line.
     */
    ioline_t                    sen;
    /**
     * @brief   SI41XX SERIAL CLK Line.
     */
    ioline_t                    sclk;
    /**
     * @brief   SI41XX SERIAL DATA Line.
     */
    ioline_t                    sdata;
#endif /* SI41XX_USE_SERIAL */
    /**
     * @brief   SI41XX Reference frequency.
     */
    uint32_t                    ref_freq;
#if SI41XX_HAS_IF
    /**
     * @brief   SI41XX IF Output Divider register value.
     */
    uint8_t                     if_div;
    /**
     * @brief   SI41XX IF N-Divider value.
     */
    uint32_t                    if_n;
    /**
     * @brief   SI41XX IF R-Divider value.
     */
    uint32_t                    if_r;
#endif /* SI41XX_HAS_IF */
#if SI41XX_HAS_RF1
    /**
     * @brief   SI41XX RF1 N-Divider value.
     */
    uint32_t                    rf1_n;
    /**
     * @brief   SI41XX RF1 R-Divider value.
     */
    uint32_t                    rf1_r;
#endif /* SI41XX_HAS_RF1 */
#if SI41XX_HAS_RF2
    /**
     * @brief   SI41XX RF2 N-Divider value.
     */
    uint32_t                    rf2_n;
    /**
     * @brief   SI41XX RF2 R-Divider value.
     */
    uint32_t                    rf2_r;
#endif /* SI41XX_HAS_RF2 */
} SI41XXConfig;

/**
 * @brief SI41XX Radio class.
 */
typedef struct SI41XXDriver {
    /**
     * @brief   Driver state.
     */
    si41xx_state_t              state;
    /**
     * @brief   Current configuration data.
     */
    SI41XXConfig                *config;
#if SI41XX_USE_MUTUAL_EXCLUSION || defined(__DOXYGEN__)
    /**
     * @brief   Mutex protecting the bus.
     */
    mutex_t                     mutex;
#endif /* SI41XX_USE_MUTUAL_EXCLUSION */
    uint8_t                     pwr;
} SI41XXDriver;
/** @} */

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
void si41xxObjectInit(SI41XXDriver *devp);
void si41xxStart(SI41XXDriver *devp, SI41XXConfig *config);
void si41xxStop(SI41XXDriver *devp);
void si41xxWriteRaw(SI41XXDriver *devp, uint8_t reg, uint32_t data);
#if SI41XX_HAS_IF
bool si41xxSetIF(SI41XXDriver *devp, uint32_t freq);
bool si41xxSetIFDiv(SI41XXDriver *devp, uint8_t div);
#endif
#if SI41XX_HAS_RF1
bool si41xxSetRF1(SI41XXDriver *devp, uint32_t freq);
#endif
#if SI41XX_HAS_RF2
bool si41xxSetRF2(SI41XXDriver *devp, uint32_t freq);
#endif
#ifdef __cplusplus
}
#endif

#endif /* _SI41XX_H_ */

/** @} */
