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





#define WORK_IN_PROGRESS__TMP101AN_DRIVER
#ifndef WORK_IN_PROGRESS__TMP101AN_DRIVER

/**
 * @name    TMP101 Configuration register fields
 * @{
 */
#define TMP101_CONFIG_MODE_Pos              (0U)
#define TMP101_CONFIG_MODE_Msk              (0x7U << TMP101_CONFIG_MODE_Pos)
#define TMP101_CONFIG_MODE                  TMP101_CONFIG_MODE_Msk
#define TMP101_CONFIG_MODE_SHDN             (0x0U << TMP101_CONFIG_MODE_Pos)
#define TMP101_CONFIG_MODE_SHUNT            (0x1U << TMP101_CONFIG_MODE_Pos)
#define TMP101_CONFIG_MODE_VBUS             (0x2U << TMP101_CONFIG_MODE_Pos)
#define TMP101_CONFIG_MODE_SHUNT_VBUS       (0x3U << TMP101_CONFIG_MODE_Pos)
#define TMP101_CONFIG_MODE_CONT             (0x4U << TMP101_CONFIG_MODE_Pos)
#define TMP101_CONFIG_VSHCT_Pos             (3U)
#define TMP101_CONFIG_VSHCT_Msk             (0x7U << TMP101_CONFIG_VSHCT_Pos)
#define TMP101_CONFIG_VSHCT                 TMP101_CONFIG_VSHCT_Msk
#define TMP101_CONFIG_VSHCT_140US           (0x0U << TMP101_CONFIG_VSHCT_Pos)
#define TMP101_CONFIG_VSHCT_204US           (0x1U << TMP101_CONFIG_VSHCT_Pos)
#define TMP101_CONFIG_VSHCT_332US           (0x2U << TMP101_CONFIG_VSHCT_Pos)
#define TMP101_CONFIG_VSHCT_588US           (0x3U << TMP101_CONFIG_VSHCT_Pos)
#define TMP101_CONFIG_VSHCT_1100US          (0x4U << TMP101_CONFIG_VSHCT_Pos)
#define TMP101_CONFIG_VSHCT_2116US          (0x5U << TMP101_CONFIG_VSHCT_Pos)
#define TMP101_CONFIG_VSHCT_4156US          (0x6U << TMP101_CONFIG_VSHCT_Pos)
#define TMP101_CONFIG_VSHCT_8224US          (0x7U << TMP101_CONFIG_VSHCT_Pos)
#define TMP101_CONFIG_VBUSCT_Pos            (6U)
#define TMP101_CONFIG_VBUSCT_Msk            (0x7U << TMP101_CONFIG_VBUSCT_Pos)
#define TMP101_CONFIG_VBUSCT                TMP101_CONFIG_VBUSCT_Msk
#define TMP101_CONFIG_VBUSCT_140US          (0x0U << TMP101_CONFIG_VSHCT_Pos)
#define TMP101_CONFIG_VBUSCT_204US          (0x1U << TMP101_CONFIG_VSHCT_Pos)
#define TMP101_CONFIG_VBUSCT_332US          (0x2U << TMP101_CONFIG_VSHCT_Pos)
#define TMP101_CONFIG_VBUSCT_588US          (0x3U << TMP101_CONFIG_VSHCT_Pos)
#define TMP101_CONFIG_VBUSCT_1100US         (0x4U << TMP101_CONFIG_VSHCT_Pos)
#define TMP101_CONFIG_VBUSCT_2116US         (0x5U << TMP101_CONFIG_VSHCT_Pos)
#define TMP101_CONFIG_VBUSCT_4156US         (0x6U << TMP101_CONFIG_VSHCT_Pos)
#define TMP101_CONFIG_VBUSCT_8224US         (0x7U << TMP101_CONFIG_VSHCT_Pos)
#define TMP101_CONFIG_AVG_Pos               (9U)
#define TMP101_CONFIG_AVG_Msk               (0x7U << TMP101_CONFIG_AVG_Pos)
#define TMP101_CONFIG_AVG                   TMP101_CONFIG_AVG_Msk
#define TMP101_CONFIG_AVG_1                 (0x0U << TMP101_CONFIG_AVG_Pos)
#define TMP101_CONFIG_AVG_4                 (0x1U << TMP101_CONFIG_AVG_Pos)
#define TMP101_CONFIG_AVG_16                (0x2U << TMP101_CONFIG_AVG_Pos)
#define TMP101_CONFIG_AVG_64                (0x3U << TMP101_CONFIG_AVG_Pos)
#define TMP101_CONFIG_AVG_128               (0x4U << TMP101_CONFIG_AVG_Pos)
#define TMP101_CONFIG_AVG_256               (0x5U << TMP101_CONFIG_AVG_Pos)
#define TMP101_CONFIG_AVG_512               (0x6U << TMP101_CONFIG_AVG_Pos)
#define TMP101_CONFIG_AVG_1024              (0x7U << TMP101_CONFIG_AVG_Pos)
#define TMP101_CONFIG_RST_Pos               (15U)
#define TMP101_CONFIG_RST_Msk               (0x1U << TMP101_CONFIG_RST_Pos)
#define TMP101_CONFIG_RST                   TMP101_CONFIG_RST_Msk
/** @} */

/**
 * @name    TMP101 Shunt Voltage register fields
 * @{
 */
#define TMP101_SHUNT_Pos                    (0U)
#define TMP101_SHUNT_Msk                    (0xFFFFU << TMP101_SHUNT_Pos)
#define TMP101_SHUNT                        TMP101_SHUNT_Msk
/** @} */

/**
 * @name    TMP101 VBUS Voltage register fields
 * @{
 */
#define TMP101_VBUS_Pos                     (0U)
#define TMP101_VBUS_Msk                     (0x7FFFU << TMP101_VBUS_Pos)
#define TMP101_VBUS                         TMP101_VBUS_Msk
/** @} */

/**
 * @name    TMP101AN temperature sensor register fields
 * @{
 */
#define TMP101_POWER_Pos                    (0U)
#define TMP101_POWER_Msk                    (0xFFFFU << TMP101_POWER_Pos)
#define TMP101_POWER                        TMP101_POWER_Msk
/** @} */

/**
 * @name    TMP101 Current register fields
 * @{
 */
#define TMP101_CURRENT_Pos                  (0U)
#define TMP101_CURRENT_Msk                  (0xFFFFU << TMP101_CURRENT_Pos)
#define TMP101_CURRENT                      TMP101_CURRENT_Msk
/** @} */

/**
 * @name    TMP101 Calibration register fields
 * @{
 */
#define TMP101_CAL_Pos                      (0U)
#define TMP101_CAL_Msk                      (0x7FFFU << TMP101_CAL_Pos)
#define TMP101_CAL                          TMP101_CAL_Msk
/** @} */

/**
 * @name    TMP101 Alert Mask/Enable register fields
 * @{
 */
#define TMP101_ME_LEN_Pos                   (0U)
#define TMP101_ME_LEN_Msk                   (0x1U << TMP101_ME_LEN_Pos)
#define TMP101_ME_LEN                       TMP101_ME_LEN_Msk
#define TMP101_ME_APOL_Pos                  (1U)
#define TMP101_ME_APOL_Msk                  (0x1U << TMP101_ME_APOL_Pos)
#define TMP101_ME_APOL                      TMP101_ME_APOL_Msk
#define TMP101_ME_OVF_Pos                   (2U)
#define TMP101_ME_OVF_Msk                   (0x1U << TMP101_ME_OVF_Pos)
#define TMP101_ME_OVF                       TMP101_ME_OVF_Msk
#define TMP101_ME_CVRF_Pos                  (3U)
#define TMP101_ME_CVRF_Msk                  (0x1U << TMP101_ME_CVRF_Pos)
#define TMP101_ME_CVRF                      TMP101_ME_CVRF_Msk
#define TMP101_ME_AFF_Pos                   (4U)
#define TMP101_ME_AFF_Msk                   (0x1U << TMP101_ME_AFF_Pos)
#define TMP101_ME_AFF                       TMP101_ME_AFF_Msk
#define TMP101_ME_CNVR_Pos                  (10U)
#define TMP101_ME_CNVR_Msk                  (0x1U << TMP101_ME_CNVR_Pos)
#define TMP101_ME_CNVR                      TMP101_ME_CNVR_Msk
#define TMP101_ME_POL_Pos                   (11U)
#define TMP101_ME_POL_Msk                   (0x1U << TMP101_ME_POL_Pos)
#define TMP101_ME_POL                       TMP101_ME_POL_Msk
#define TMP101_ME_BUL_Pos                   (12U)
#define TMP101_ME_BUL_Msk                   (0x1U << TMP101_ME_BUL_Pos)
#define TMP101_ME_BUL                       TMP101_ME_BUL_Msk
#define TMP101_ME_BOL_Pos                   (13U)
#define TMP101_ME_BOL_Msk                   (0x1U << TMP101_ME_BOL_Pos)
#define TMP101_ME_BOL                       TMP101_ME_BOL_Msk
#define TMP101_ME_SUL_Pos                   (14U)
#define TMP101_ME_SUL_Msk                   (0x1U << TMP101_ME_SUL_Pos)
#define TMP101_ME_SUL                       TMP101_ME_SUL_Msk
#define TMP101_ME_SOL_Pos                   (15U)
#define TMP101_ME_SOL_Msk                   (0x1U << TMP101_ME_SOL_Pos)
#define TMP101_ME_SOL                       TMP101_ME_SOL_Msk
/** @} */

/**
 * @name    TMP101 Alert Limit register fields
 * @{
 */ 
#define TMP101_LIM_Pos                      (0U)
#define TMP101_LIM_Msk                      (0xFFFFU << TMP101_LIM_Pos)
#define TMP101_LIM                          TMP101_LIM_Msk
/** @} */

/**
 * @name    TMP101 Manufacturer ID register fields
 * @{
 */
#define TMP101_MFG_ID_Pos                   (0U)
#define TMP101_MFG_ID_Msk                   (0xFFFFU << TMP101_MFG_ID_Pos)
#define TMP101_MFG_ID                       TMP101_MFG_ID_Msk
/** @} */

/**
 * @name    TMP101 Die ID register fields
 * @{
 */
#define TMP101_DIE_ID_RID_Pos               (0U)
#define TMP101_DIE_ID_RID_Msk               (0xFU << TMP101_DIE_ID_RID_Pos)
#define TMP101_DIE_ID_RID                   TMP101_DIE_ID_RID_Msk
#define TMP101_DIE_ID_DID_Pos               (4U)
#define TMP101_DIE_ID_DID_Msk               (0xFFFU << TMP101_DIE_ID_DID_Pos)
#define TMP101_DIE_ID_DID                   TMP101_DIE_ID_DID_Msk
/** @} */

#endif // TMP101AN work removing unneeded template code - TMH


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
    I2CDriver                   *i2cp;
    /**
     * @brief I2C configuration associated with this TMP101.
     */
    const I2CConfig             *i2ccfg;
    /**
     * @brief TMP101 Slave Address
     */
    i2caddr_t                   saddr;
#endif /* TMP101_USE_I2C */
//    /**
//     * @brief TMP101 configuration reg value
//     */
//    uint16_t                    cfg;

//    /**
//     * @brief TMP101 calibration reg value
//     */
//    uint16_t                    cal;
//    /**
//     * @brief Optional Current LSB value for use in calculations
//     */
//    uint16_t                    curr_lsb;
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

//bool read_tmp101an_temperature_v1(uint32_t option);
bool read_tmp101an_temperature_v1(TMP101Driver* device_ptr, unsigned int option);

#ifdef __cplusplus
}
#endif

#endif /* _TMP101_H_ */

/** @} */
