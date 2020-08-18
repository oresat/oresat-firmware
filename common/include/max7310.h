/**
 * @file    max7310.h
 * @brief   MAX7310 GPIO Expander header.
 *
 * @addtogroup MAX7310
 * @ingroup ORESAT
 * @{
 */
#ifndef _MAX7310_H_
#define _MAX7310_H_

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    Version Identification
 * @{
 */
/**
 * @brief   MAX7310 Driver version string.
 */
#define MAX7310_VERSION                     "1.0.0"

/**
 * @brief   MAX7310 Driver version major number.
 */
#define MAX7310_MAJOR                       1

/**
 * @brief   MAX7310 Driver version minor number.
 */
#define MAX7310_MINOR                       0

/**
 * @brief   MAX7310 Driver version patch number.
 */
#define MAX7310_PATCH                       0
/** @} */

/**
 * @name    MAX7310 Device Characteristics
 *
 * @{
 */

#define MAX7310_MIN_ADDR                    0x8
#define MAX7310_MAX_ADDR                    0x3F

/** @} */

/**
 * @name    MAX7310 Register addresses
 * @{
 */
#define MAX7310_AD_INPUT                    0x00
#define MAX7310_AD_ODR                      0x01
#define MAX7310_AD_POL                      0x02
#define MAX7310_AD_MODE                     0x03
#define MAX7310_AD_TIMEOUT                  0x04
/** @} */

/**
 * @name    MAX7310 General IO pin register bits
 * @{
 */
#define MAX7310_REG_MASK                    0xFF
#define MAX7310_PIN_MASK(n)                 (1 << n)
/** @} */

/**
 * @name    MAX7310 Output data register bits
 * @{
 */
#define MAX7310_PIN_ODR_LOW(n)              (0 << n)
#define MAX7310_PIN_ODR_HIGH(n)             (1 << n)
/** @} */

/**
 * @name    MAX7310 Polarity register bits
 * @{
 */
#define MAX7310_PIN_POL_STD(n)              (0 << n)
#define MAX7310_PIN_POL_INV(n)              (1 << n)
/** @} */

/**
 * @name    MAX7310 Mode register bits
 * @{
 */
#define MAX7310_PIN_MODE_OUTPUT(n)          (0 << n)
#define MAX7310_PIN_MODE_INPUT(n)           (1 << n)
/** @} */

/**
 * @name    MAX7310_TIMEOUT register bits
 * @{
 */
#define MAX7310_TIMEOUT_MASK                0x01
#define MAX7310_TIMEOUT_EN                  1
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   MAX7310 I2C interface switch.
 * @details If set to @p TRUE the support for I2C is included.
 * @note    The default is @p TRUE.
 */
#if !defined(MAX7310_USE_I2C) || defined(__DOXYGEN__)
#define MAX7310_USE_I2C                     TRUE
#endif

/**
 * @brief   MAX7310 shared I2C switch.
 * @details If set to @p TRUE the device acquires I2C bus ownership
 *          on each transaction.
 * @note    The default is @p FALSE. Requires I2C_USE_MUTUAL_EXCLUSION.
 */
#if !defined(MAX7310_SHARED_I2C) || defined(__DOXYGEN__)
#define MAX7310_SHARED_I2C                  FALSE
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if MAX7310_USE_I2C && !HAL_USE_I2C
#error "MAX7310_USE_I2C requires HAL_USE_I2C"
#endif

#if MAX7310_SHARED_I2C && !I2C_USE_MUTUAL_EXCLUSION
#error "MAX7310_SHARED_I2C requires I2C_USE_MUTUAL_EXCLUSION"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @name    MAX7310 data structures and types.
 * @{
 */
/**
 * @brief Structure representing a MAX7310 driver.
 */
typedef struct MAX7310Driver MAX7310Driver;

/**
 * @brief   MAX7310 timout configuration.
 */
typedef enum {
    MAX7310_TIMEOUT_DISABLED = 0x00,  /**< Timeout disabled.                */
    MAX7310_TIMEOUT_ENABLED = 0x01    /**< Timeout enabled.                 */
} max7310_timeout_t;

/**
 * @brief   Driver state machine possible states.
 */
typedef enum {
    MAX7310_UNINIT = 0,               /**< Not initialized.                 */
    MAX7310_STOP = 1,                 /**< Stopped.                         */
    MAX7310_READY = 2,                /**< Ready.                           */
} max7310_state_t;

/**
 * @brief MAX7310 configuration structure.
 */
typedef struct {
#if (MAX7310_USE_I2C) || defined(__DOXYGEN__)
    /**
     * @brief I2C driver associated with this MAX7310.
     */
    I2CDriver                   *i2cp;
    /**
     * @brief I2C configuration associated with this MAX7310.
     */
    const I2CConfig             *i2ccfg;
    /**
     * @brief MAX7310 Slave Address
     */
    i2caddr_t                   saddr;
#endif /* MAX7310_USE_I2C */
    /**
     * @brief MAX7310 output states
     */
    uint8_t                     odr;
    /**
     * @brief MAX7310 polarity inversion
     */
    uint8_t                     pol;
    /**
     * @brief MAX7310 IO mode
     */
    uint8_t                     iomode;
    /**
     * @brief MAX7310 timeout setting
     */
    max7310_timeout_t           timeout;
} MAX7310Config;

/**
 * @brief   @p MAX7310 specific methods.
 */
#define _max7310_methods_alone                                              \
    /* Change output state of MAX7310 ports.*/                              \
    msg_t (*set_output)(MAX7310Driver *devp, uint8_t output);               \
    /* Change polarity of MAX7310 ports.*/                                  \
    msg_t (*set_polarity)(MAX7310Driver *devp, uint8_t polarity);           \
    /* Change IO mode of MAX7310 ports.*/                                   \
    msg_t (*set_iomode)(MAX7310Driver *devp, uint8_t iomode);               \
    /* Change timeout setting of MAX7310.*/                                 \
    msg_t (*set_timeout)(MAX7310Driver *devp, max7310_timeout_t timeout);

/**
 * @brief   @p MAX7310 specific methods with inherited ones.
 */
#define _max7310_methods                                                    \
    _base_object_methods

/**
 * @extends BaseObjectVMT
 *
 * @brief @p MAX7310 virtual methods table.
 */
struct MAX7310VMT {
    _max7310_methods
};

/**
 * @brief   @p MAX7310Driver specific data.
 */
#define _max7310_data                                                       \
    _base_object_data                                                       \
    /* Driver state.*/                                                      \
    max7310_state_t           state;                                        \
    /* Current configuration data.*/                                        \
    const MAX7310Config       *config;

/**
 * @brief MAX710 GPIO Expander class.
 */
struct MAX7310Driver {
    /** @brief Virtual Mthods Table.*/
    const struct MAX7310VMT     *vmt;
    _max7310_data
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
void max7310ObjectInit(MAX7310Driver *devp);
void max7310Start(MAX7310Driver *devp, const MAX7310Config *config);
void max7310Stop(MAX7310Driver *devp);
uint8_t max7310ReadRaw(MAX7310Driver *devp, uint8_t reg);
void max7310WriteRaw(MAX7310Driver *devp, uint8_t reg, uint8_t value);
void max7310SetPin(MAX7310Driver *devp, uint8_t pin);
void max7310ClearPin(MAX7310Driver *devp, uint8_t pin);
void max7310TogglePin(MAX7310Driver *devp, uint8_t pin);
#ifdef __cplusplus
}
#endif

#endif /* _MAX7310_H_ */

/** @} */
