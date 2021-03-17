/**
 * @file    fm24cl64b.h
 * @brief   FM24CL64B F-RAM.
 *
 * @addtogroup FM24CL64B
 * @ingroup ORESAT
 * @{
 */
#ifndef _FM24CL64B_H_
#define _FM24CL64B_H_

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    Version Identification
 * @{
 */
/**
 * @brief   FM24CL64B Driver version string.
 */
#define FM24CL64B_VERSION                   "1.0.0"

/**
 * @brief   FM24CL64B Driver version major number.
 */
#define FM24CL64B_MAJOR                     1

/**
 * @brief   FM24CL64B Driver version minor number.
 */
#define FM24CL64B_MINOR                     0

/**
 * @brief   FM24CL64B Driver version patch number.
 */
#define FM24CL64B_PATCH                     0
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   FM24CL64B I2C interface switch.
 * @details If set to @p TRUE the support for I2C is included.
 * @note    The default is @p TRUE.
 */
#if !defined(FM24CL64B_USE_I2C) || defined(__DOXYGEN__)
#define FM24CL64B_USE_I2C                   TRUE
#endif

/**
 * @brief   FM24CL64B shared I2C switch.
 * @details If set to @p TRUE the device acquires I2C bus ownership
 *          on each transaction.
 * @note    The default is @p FALSE. Requires I2C_USE_MUTUAL_EXCLUSION.
 */
#if !defined(FM24CL64B_SHARED_I2C) || defined(__DOXYGEN__)
#define FM24CL64B_SHARED_I2C                FALSE
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if FM24CL64B_USE_I2C && !HAL_USE_I2C
#error "FM24CL64B_USE_I2C requires HAL_USE_I2C"
#endif

#if FM24CL64B_SHARED_I2C && !I2C_USE_MUTUAL_EXCLUSION
#error "FM24CL64B_SHARED_I2C requires I2C_USE_MUTUAL_EXCLUSION"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @name    FM24CL64B data structures and types.
 * @{
 */
/**
 * @brief Structure representing a FM24CL64B driver.
 */
typedef struct FM24CL64BDriver FM24CL64BDriver;

/**
 * @brief   Driver state machine possible states.
 */
typedef enum {
    FM24CL64B_UNINIT = 0,               /**< Not initialized.                 */
    FM24CL64B_STOP = 1,                 /**< Stopped.                         */
    FM24CL64B_READY = 2,                /**< Ready.                           */
} fm24cl64b_state_t;

/**
 * @brief   FM24CL64B configuration structure.
 */
typedef struct {
#if (FM24CL64B_USE_I2C) || defined(__DOXYGEN__)
    /**
     * @brief I2C driver associated with this FM24CL64B.
     */
    I2CDriver                   *i2cp;
    /**
     * @brief I2C configuration associated with this FM24CL64B.
     */
    const I2CConfig             *i2ccfg;
    /**
     * @brief FM24CL64B Slave Address
     */
    i2caddr_t                   saddr;
#endif /* FM24CL64B_USE_I2C */
} FM24CL64BConfig;

/**
 * @brief   @p FM24CL64B specific methods.
 */
#define _fm24cl64b_methods_alone

/**
 * @brief   @p FM24CL64B specific methods with inherited ones.
 */
#define _fm24cl64b_methods                                                  \
    _base_object_methods

/**
 * @extends BaseObjectVMT
 *
 * @brief   @p FM24CL64B virtual methods table.
 */
struct FM24CL64BVMT {
    _fm24cl64b_methods
};

/**
 * @brief   @p FM24CL64BDriver specific data.
 */
#define _fm24cl64b_data                                                     \
    _base_object_data                                                       \
    /* Driver state.*/                                                      \
    fm24cl64b_state_t              state;                                   \
    /* Current configuration data.*/                                        \
    const FM24CL64BConfig          *config;

/**
 * @brief FM24CL64B Power Monitor class.
 */
struct FM24CL64BDriver {
    /** @brief Virtual Methods Table.*/
    const struct FM24CL64BVMT     *vmt;
    _fm24cl64b_data
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
void fm24cl64bObjectInit(FM24CL64BDriver *devp);
void fm24cl64bStart(FM24CL64BDriver *devp, const FM24CL64BConfig *config);
void fm24cl64bStop(FM24CL64BDriver *devp);
void fm24cl64bRead(FM24CL64BDriver *devp, uint16_t addr, void *buf, size_t n);
void fm24cl64bWrite(FM24CL64BDriver *devp, uint16_t addr, void *buf, size_t n);
#ifdef __cplusplus
}
#endif

#endif /* _FM24CL64B_H_ */

/** @} */

