/**
 * @file    max580x.h
 * @brief   MAX580X Digital to Analog Converter.
 *
 * @addtogroup MAX580X
 * @ingroup ORESAT
 * @{
 */
#ifndef _MAX580X_H_
#define _MAX580X_H_

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    Version Identification
 * @{
 */
/**
 * @brief   MAX580X Driver version string.
 */
#define MAX580X_VERSION                     "1.0.0"

/**
 * @brief   MAX580X Driver version major number.
 */
#define MAX580X_MAJOR                       1

/**
 * @brief   MAX580X Driver version minor number.
 */
#define MAX580X_MINOR                       0

/**
 * @brief   MAX580X Driver version patch number.
 */
#define MAX580X_PATCH                       0
/** @} */

/**
 * @name    MAX580X Commands
 * @{
 */
#define MAX580X_CMD_NOP                     (0U << 4)
#define MAX580X_CMD_REF                     (2U << 4)
#define MAX580X_CMD_SOFTWARE                (3U << 4)
#define MAX580X_CMD_POWER                   (4U << 4)
#define MAX580X_CMD_CONFIG                  (5U << 4)
#define MAX580X_CMD_DEFAULT                 (6U << 4)
#define MAX580X_CMD_RETURN                  (7U << 4)
#define MAX580X_CMD_CODE                    (8U << 4)
#define MAX580X_CMD_LOAD                    (9U << 4)
#define MAX580X_CMD_CODE_LOAD               (10U << 4)
/** @} */

/**
 * @name    MAX580X REF Command fields
 * @{
 */
#define MAX580X_REF_EXT                     (0U << 0)
#define MAX580X_REF_2500                    (1U << 0)
#define MAX580X_REF_2048                    (2U << 0)
#define MAX580X_REF_4096                    (3U << 0)
#define MAX580X_REF_INT_STBY                (1U << 2)
#define MAX580X_REF_INT_EN                  (1U << 3)
/** @} */

/**
 * @name    MAX580X SOFTWARE Command fields
 * @{
 */
#define MAX580X_SOFTWARE_END                (0U << 0)
#define MAX580X_SOFTWARE_GATE               (1U << 0)
#define MAX580X_SOFTWARE_CLR                (4U << 0)
#define MAX580X_SOFTWARE_RST                (5U << 0)
/** @} */

/**
 * @name    MAX580X POWER Command fields
 * @{
 */
#define MAX580X_POWER_NORMAL                (0U << 6)
#define MAX580X_POWER_1K                    (1U << 6)
#define MAX580X_POWER_100K                  (2U << 6)
#define MAX580X_POWER_HI_Z                  (3U << 6)
/** @} */

/**
 * @name    MAX580X CONFIG Command fields
 * @{
 */
#define MAX580X_CONFIG_AUX_GATE             (3U << 3)
#define MAX580X_CONFIG_AUX_CLEAR            (6U << 3)
#define MAX580X_CONFIG_AUX_NONE             (7U << 3)
/** @} */

/**
 * @name    MAX580X DEFAULT Command Fields
 * @{
 */
#define MAX580X_DEFAULT_POR                 (0U << 5)
#define MAX580X_DEFAULT_ZERO                (1U << 5)
#define MAX580X_DEFAULT_MID                 (2U << 5)
#define MAX580X_DEFAULT_FULL                (3U << 5)
#define MAX580X_DEFAULT_RETURN              (4U << 5)
/** @} */

/**
 * @name    MAX580X RETURN/CODE Data Fields
 * @{
 */
#define MAX580X_DAC2VAL(field,res)          __REVSH(field >> (16 - res))
#define MAX580X_VAL2DAC(val,res)            __REVSH(val << (16 - res))
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   MAX580X I2C interface switch.
 * @details If set to @p TRUE the support for I2C is included.
 * @note    The default is @p TRUE.
 */
#if !defined(MAX580X_USE_I2C) || defined(__DOXYGEN__)
#define MAX580X_USE_I2C                     TRUE
#endif

/**
 * @brief   MAX580X shared I2C switch.
 * @details If set to @p TRUE the device acquires I2C bus ownership
 *          on each transaction.
 * @note    The default is @p FALSE. Requires I2C_USE_MUTUAL_EXCLUSION.
 */
#if !defined(MAX580X_SHARED_I2C) || defined(__DOXYGEN__)
#define MAX580X_SHARED_I2C                  FALSE
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if MAX580X_USE_I2C && !HAL_USE_I2C
#error "MAX580X_USE_I2C requires HAL_USE_I2C"
#endif

#if MAX580X_SHARED_I2C && !I2C_USE_MUTUAL_EXCLUSION
#error "MAX580X_SHARED_I2C requires I2C_USE_MUTUAL_EXCLUSION"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @name    MAX580X data structures and types.
 * @{
 */
/**
 * @brief Structure representing a MAX580X driver.
 */
typedef struct MAX580XDriver MAX580XDriver;

/**
 * @name    MAX580X Part IDs
 */
typedef enum {
    MAX5805 = 0x82,
    MAX5803 = 0x8A,
    MAX5804 = 0x92,
} max580x_devid_t;

/**
 * @name    MAX580X DAC Resolutions
 */
typedef enum {
    MAX5803_RES = 8,
    MAX5804_RES = 10,
    MAX5805_RES = 12,
} max580x_res_t;

/**
 * @name    MAX580X DAC Registers
 */
typedef enum {
    MAX580X_RETURN = MAX580X_CMD_RETURN,
    MAX580X_CODE = MAX580X_CMD_CODE,
    MAX580X_CODE_LOAD = MAX580X_CMD_CODE_LOAD,
} max580x_reg_t;

/**
 * @brief   Driver state machine possible states.
 */
typedef enum {
    MAX580X_UNINIT = 0,               /**< Not initialized.                 */
    MAX580X_STOP = 1,                 /**< Stopped.                         */
    MAX580X_READY = 2,                /**< Ready.                           */
} max580x_state_t;

/**
 * @brief MAX580X configuration structure.
 */
typedef struct {
#if (MAX580X_USE_I2C) || defined(__DOXYGEN__)
    /**
     * @brief I2C driver associated with this MAX580X.
     */
    I2CDriver                   *i2cp;
    /**
     * @brief I2C configuration associated with this MAX580X.
     */
    const I2CConfig             *i2ccfg;
    /**
     * @brief MAX580X Slave Address
     */
    i2caddr_t                   saddr;
#endif /* MAX580X_USE_I2C */
    /**
     * @brief MAX580X reference configuration
     */
    uint8_t                     ref;
    /**
     * @brief MAX580X power configuration
     */
    uint8_t                     power;
    /**
     * @brief MAX580X aux configuration
     */
    uint8_t                     aux;
    /**
     * @brief MAX580X default configuration
     */
    uint8_t                     default_cfg;
} MAX580XConfig;

/**
 * @brief   @p MAX580X specific methods.
 */
#define _max580x_methods_alone

/**
 * @brief   @p MAX580X specific methods with inherited ones.
 */
#define _max580x_methods                                                    \
    _base_object_methods

/**
 * @extends BaseObjectVMT
 *
 * @brief @p MAX580X virtual methods table.
 */
struct MAX580XVMT {
    _max580x_methods
};

/**
 * @brief   @p MAX580XDriver specific data.
 */
#define _max580x_data                                                       \
    _base_object_data                                                       \
    /* Driver state.*/                                                      \
    max580x_state_t           state;                                        \
    /* Current configuration data.*/                                        \
    const MAX580XConfig       *config;                                      \
    max580x_res_t             res;                                          \
    uint16_t                  range;

/**
 * @brief MAX710 GPIO Expander class.
 */
struct MAX580XDriver {
    /** @brief Virtual Mthods Table.*/
    const struct MAX580XVMT     *vmt;
    _max580x_data
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
void max580xObjectInit(MAX580XDriver *devp);
void max580xStart(MAX580XDriver *devp, const MAX580XConfig *config);
void max580xStop(MAX580XDriver *devp);
uint16_t max580xReadRaw(MAX580XDriver *devp, max580x_reg_t reg);
void max580xWriteRaw(MAX580XDriver *devp, max580x_reg_t reg, uint16_t value);
uint32_t max580xReadVoltage(MAX580XDriver *devp, max580x_reg_t reg);
void max580xWriteVoltage(MAX580XDriver *devp, max580x_reg_t reg, uint32_t voltage);
void max580xLoad(MAX580XDriver *devp);
#ifdef __cplusplus
}
#endif

#endif /* _MAX580X_H_ */

/** @} */
