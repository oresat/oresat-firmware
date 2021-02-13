/**
 * @file    tmp101.h
 * @brief   TMP101AN temperature sensor driver
 *
 * @addtogroup TMP101
 * @ingroup ORESAT
 * @{
 */
#ifndef _TMP101_H_
#define _TMP101_H_

#include <chprintf.h>

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    Version Identification
 * @{
 */
/**
 * @brief   TMP101 Driver version string.
 */
#define TMP101_VERSION                      "1.0.0"

/**
 * @brief   TMP101 Driver version major number.
 */
#define TMP101_MAJOR                        1

/**
 * @brief   TMP101 Driver version minor number.
 */
#define TMP101_MINOR                        0

/**
 * @brief   TMP101 Driver version patch number.
 */
#define TMP101_PATCH                        0
/** @} */


/**
 * @name    TMP101 Register Addresses
 * @{
 */
#define TMP101_REG_TEMPERATURE_READING      0x00U
#define TMP101_REG_CONFIGURATION            0x01U
#define TMP101_REG_TEMP_SETPOINT_LOW        0x10U
#define TMP101_REG_TEMP_SETPOINT_HIGH       0x11U
/** @} */


// ORESAT_TASK_001 - add temperature sensor driver:
// 2021-02-08 MON - first steps temperature reading
#define OPTION_SENSOR_01 (1)
#define OPTION_SENSOR_02 (2)

#define I2C_ADDR_SENSOR_01 (0x48)
#define I2C_ADDR_SENSOR_02 (0x4A)



/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   TMP101 I2C interface switch.
 * @details If set to @p TRUE the support for I2C is included.
 * @note    The default is @p TRUE.
 */
#if !defined(TMP101_USE_I2C) || defined(__DOXYGEN__)
#define TMP101_USE_I2C                      TRUE
#endif

/**
 * @brief   TMP101 shared I2C switch.
 * @details If set to @p TRUE the device acquires I2C bus ownership
 *          on each transaction.
 * @note    The default is @p FALSE. Requires I2C_USE_MUTUAL_EXCLUSION.
 */
#if !defined(TMP101_SHARED_I2C) || defined(__DOXYGEN__)
#define TMP101_SHARED_I2C                   TRUE
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if TMP101_USE_I2C && !HAL_USE_I2C
#error "TMP101_USE_I2C requires HAL_USE_I2C"
#endif

#if TMP101_SHARED_I2C && !I2C_USE_MUTUAL_EXCLUSION
#error "TMP101_SHARED_I2C requires I2C_USE_MUTUAL_EXCLUSION"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @name    TMP101 data structures and types.
 * @{
 */
/**
 * @brief Structure representing a TMP101 driver.
 */
typedef struct TMP101Driver TMP101Driver;

/**
 * @brief   Driver state machine possible states.
 */
typedef enum {
    TMP101_UNINIT = 0,                  /**< Not initialized.                 */
    TMP101_STOP = 1,                    /**< Stopped.                         */
    TMP101_READY = 2,                   /**< Ready.                           */
} tmp101_state_t;


/**
 * @brief   TMP101 configuration structure.
 */

typedef struct {
#if (TMP101_USE_I2C) || defined(__DOXYGEN__)
    /**
     * @brief I2C driver associated with this TMP101.
     */
    I2CDriver           *i2cp;
    /**
     * @brief I2C configuration associated with this TMP101.
     */
    const I2CConfig     *i2ccfg;
    /**
     * @brief TMP101 Slave Address
     */
    i2caddr_t           saddr;
#endif /* TMP101_USE_I2C */
} TMP101Config;

/**
 * @brief   @p TMP101 specific methods.
 */
#define _tmp101_methods_alone

/**
 * @brief   @p TMP101 specific methods with inherited ones.
 */
#define _tmp101_methods                                                     \
    _base_object_methods

/**
 * @extends BaseObjectVMT
 *
 * @brief   @p TMP101 virtual methods table.
 */
struct TMP101VMT {
    _tmp101_methods
};

/**
 * @brief   @p TMP101Driver specific data.
 */
#define _tmp101_data                                                        \
    _base_object_data                                                       \
    /* Driver state.*/                                                      \
    tmp101_state_t              state;                                      \
    /* Current configuration data.*/                                        \
    const TMP101Config          *config;

/**
 * @brief TMP101AN temperature sensor class.
 */
struct TMP101Driver {
    /** @brief Virtual Methods Table.*/
    const struct TMP101VMT     *vmt;
    _tmp101_data
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
void tmp101ObjectInit(TMP101Driver *devp);
void tmp101Start(TMP101Driver *devp, const TMP101Config *config);
void tmp101Stop(TMP101Driver *devp);

// void tmp101SetAlert(TMP101Driver *devp, uint16_t alert_me, uint16_t alert_lim);
// uint16_t tmp101ReadRaw(TMP101Driver *devp, uint8_t reg);
// int32_t tmp101ReadShunt(TMP101Driver *devp);
// uint32_t tmp101ReadVBUS(TMP101Driver *devp);
// int32_t tmp101ReadCurrent(TMP101Driver *devp);
// uint32_t tmp101ReadPower(TMP101Driver *devp);

bool read_tmp101an_temperature_v1(TMP101Driver* device_ptr, unsigned int option);

msg_t read_tmp101an_temperature_v2(TMP101Driver *devp, uint8_t* byte_array);

#ifdef __cplusplus
}
#endif

#endif /* _TMP101_H_ */

/** @} */
