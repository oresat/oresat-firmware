/**
 * @file    fram.h
 * @brief   F-RAM Driver.
 *
 * @addtogroup FRAM
 * @ingroup ORESAT
 * @{
 */
#ifndef _FRAM_H_
#define _FRAM_H_

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    Version Identification
 * @{
 */
/**
 * @brief   FRAM Driver version string.
 */
#define FRAM_VERSION                        "1.0.0"

/**
 * @brief   FRAM Driver version major number.
 */
#define FRAM_MAJOR                          1

/**
 * @brief   FRAM Driver version minor number.
 */
#define FRAM_MINOR                          0

/**
 * @brief   FRAM Driver version patch number.
 */
#define FRAM_PATCH                          0
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   FRAM I2C interface switch.
 * @details If set to @p TRUE the support for I2C is included.
 * @note    The default is @p TRUE.
 */
#if !defined(FRAM_USE_I2C) || defined(__DOXYGEN__)
#define FRAM_USE_I2C                        TRUE
#endif

/**
 * @brief   FRAM shared I2C switch.
 * @details If set to @p TRUE the device acquires I2C bus ownership
 *          on each transaction.
 * @note    The default is @p FALSE. Requires I2C_USE_MUTUAL_EXCLUSION.
 */
#if !defined(FRAM_SHARED_I2C) || defined(__DOXYGEN__)
#define FRAM_SHARED_I2C                     FALSE
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if FRAM_USE_I2C && !HAL_USE_I2C
#error "FRAM_USE_I2C requires HAL_USE_I2C"
#endif

#if FRAM_SHARED_I2C && !I2C_USE_MUTUAL_EXCLUSION
#error "FRAM_SHARED_I2C requires I2C_USE_MUTUAL_EXCLUSION"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @name    FRAM data structures and types.
 * @{
 */
/**
 * @brief Structure representing a FRAM driver.
 */
typedef struct FRAMDriver FRAMDriver;

/**
 * @brief   Driver state machine possible states.
 */
typedef enum {
    FRAM_UNINIT = 0,               /**< Not initialized.                 */
    FRAM_STOP = 1,                 /**< Stopped.                         */
    FRAM_READY = 2,                /**< Ready.                           */
} fram_state_t;

/**
 * @brief   FRAM configuration structure.
 */
typedef struct {
#if (FRAM_USE_I2C) || defined(__DOXYGEN__)
    /**
     * @brief I2C driver associated with this FRAM.
     */
    I2CDriver                   *i2cp;
    /**
     * @brief I2C configuration associated with this FRAM.
     */
    const I2CConfig             *i2ccfg;
    /**
     * @brief FRAM Slave Address
     */
    i2caddr_t                   saddr;
#endif /* FRAM_USE_I2C */
} FRAMConfig;

/**
 * @brief   @p FRAM specific methods.
 */
#define _fram_methods_alone

/**
 * @brief   @p FRAM specific methods with inherited ones.
 */
#define _fram_methods                                                       \
    _base_object_methods

/**
 * @extends BaseObjectVMT
 *
 * @brief   @p FRAM virtual methods table.
 */
struct FRAMVMT {
    _fram_methods
};

/**
 * @brief   @p FRAMDriver specific data.
 */
#define _fram_data                                                          \
    _base_object_data                                                       \
    /* Driver state.*/                                                      \
    fram_state_t              state;                                        \
    /* Current configuration data.*/                                        \
    const FRAMConfig          *config;

/**
 * @brief FRAM Power Monitor class.
 */
struct FRAMDriver {
    /** @brief Virtual Methods Table.*/
    const struct FRAMVMT     *vmt;
    _fram_data
};

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
extern FRAMDriver FRAMD1;

void framObjectInit(FRAMDriver *devp);
void framStart(FRAMDriver *devp, const FRAMConfig *config);
void framStop(FRAMDriver *devp);
void framRead(FRAMDriver *devp, uint16_t addr, void *buf, size_t n);
void framWrite(FRAMDriver *devp, uint16_t addr, void *buf, size_t n);
#ifdef __cplusplus
}
#endif

#endif /* _FRAM_H_ */

/** @} */

