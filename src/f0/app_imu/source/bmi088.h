/*
 * @file    bmi088.h
 * @brief   BMI088 Power Monitor.
 *
 * @addtogroup BMI088
 * @ingroup ORESAT
 * @{
 */
#ifndef _BMI088_H_
#define _BMI088_H_

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    Version Identification
 * @{
 */
/**
 * @brief   BMI088 Driver version string.
 */
#define BMI088_VERSION                      "1.0.0"

/**
 * @brief   BMI088 Driver version major number.
 */
#define BMI088_MAJOR                        1

/**
 * @brief   BMI088 Driver version minor number.
 */
#define BMI088_MINOR                        0

/**
 * @brief   BMI088 Driver version patch number.
 */
#define BMI088_PATCH                        0
/** @} */

/**
 * @name    BMI088 Register Addresses
 * @{
 */
#define BMI088_AD_ACC_SOFT_RESET            0x7EU
#define BMI088_AD_ACC_PWR_CTRL              0x7DU
#define BMI088_AD_ACC_PWR_CONF              0x7CU
#define BMI088_AD_ACC_SELF_TEST             0x6DU
#define BMI088_AD_INT_MAP_DATA              0x58U
#define BMI088_AD_INT2_IO_CTRL              0x54U
#define BMI088_AD_INT1_IO_CTRL              0x53U
#define BMI088_AD_ACC_RANGE                 0x41U
#define BMI088_AD_ACC_CONF                  0x40U
#define BMI088_AD_TEMP_LSB                  0x23U
#define BMI088_AD_TEMP_MSB                  0x22U
#define BMI088_AD_ACC_INT_STAT_1            0x1DU
#define BMI088_AD_SENSORTIME_2              0x1AU
#define BMI088_AD_SENSORTIME_1              0x19U
#define BMI088_AD_SENSORTIME_0              0x18U
#define BMI088_AD_ACC_Z_MSB                 0x17U
#define BMI088_AD_ACC_Z_LSB                 0x16U
#define BMI088_AD_ACC_Y_MSB                 0x15U
#define BMI088_AD_ACC_Y_LSB                 0x14U
#define BMI088_AD_ACC_X_MSB                 0x13U
#define BMI088_AD_ACC_X_LSB                 0x12U
#define BMI088_AD_ACC_STATUS                0x03U
#define BMI088_AD_ACC_ERR_REG               0x02U
#define BMI088_AD_ACC_CHIP_ID               0x00U
/** @} */

/**
 * @name    BMI088 Configuration register fields
 * @{
 */
#define BMI088_CONFIG_SOFTRESET_Pos         (0x7EU)
#define BMI088_ACC_SOFTRESET_Msk            (0x07U << BMI088_ACC_SOFTRESET_Pos)
#define BMI088_ACC_SOFTRESET                BMI088_ACC_SOFTRESET_Msk
#define BMI088_ACC_POWER_CONTROL_Pos        (0x07D)
#define BMI088_ACC_POWER_CONTROL_Msk        (0x07U << BMI_ACC_POWER_CONTROL_Pos)
#define BMI088_ACC_POWER_CONTROL            BMI088_ACC_POWER_CONTROL_Msk
#define BMI088_ACC_POWER_CONTROL_EN_OFF     (0x00U << BMI_ACC_POWER_CONTROL_Pos)
#define BMI088_ACC_POWER_CONTROL_EN_ON      (0x04U << BMI_ACC_POWER_CONTROL_Pos)
#define BMI088_ACC_POWER_CONF_Pos           (0x7CU)
#define BMI088_ACC_POWER_CONF_Msk           (0x07U << BMI_ACC_POWER_CONF_Pos)
#define BMI088_ACC_POWER_CONF               BMI088_POWER_CONF_Msk
#define BMI088_ACC_POWER_CONF_SAVE_SUSPEND  (0x03U << BMI_ACC_POWER_CONF_Pos)
#define BMI088_ACC_POWER_CONF_SAVE_ACTIVE   (0x00U << BMI088_ACC_POWER_CONF_Pos)
#define BMI088_ACC_SELF_TEST_Pos            (0x6DU)
#define BMI088_ACC_SELF_TEST_Msk            (0x07U << BMI088_ACC_SELF_TEST_Pos)
#define BMI088_ACC_SELF_TEST                BMI088_ACC_SELF_TEST_Msk
#define BMI088_ACC_SELF_TEST_OFF            (0x00U << BMI088_ACC_SELF_TEST_Pos)
#define BMI088_ACC_SELF_TEST_EN_POS_ST_SIG  (0x0DU << BMI088_ACC_SELF_TEST_Pos)
#define BMI088_ACC_SELF_TEST_EN_NEG_ST_SIG  (0x09U << BMI088_ACC_SELF_TEST_Pos)	
#define BMI088_ACC_INT_MAP_DATA_Pos        (0x58U)
#define BMI088_ACC_INT_MAP_DATA_Msk        (0x07U << BMI088_ACC_INT_MAP_DATA_Pos)
#define BMI088_ACC_INT_MAP_DATA            BMI088_ACC_INT_MAP_DATA_Msk
#define BMI088_ACC_INT_MAP_DATA_INT1_DRDY  (0x00U << BMI088_ACC_INT_MAP_DATA_Pos)
#define BMI088_ACC_INT_MAP_DATA_INT2_DRDY  (0x00U << BMI088_ACC_INT_MAP_DATA_Pos)
#define BMI088_ACC_INT1_IO_CONF_Pos        (0x53U)
#define BMI088_ACC_INT1_IO_CONF_Msk         ()
#define BMI088_ACC_INT1_IO_CONF             BMI088_ACC_INT1_IO_CONF_Msk 
#define BMI088_ACC_INT2_IO_CONF_Pos         ()
#define BMI088_ACC_INT2_IO_CONF_Msk         ()
#define BMI088_ACC_INT2_IO_CONF             BMI088_ACC_INT2_Msk
#define BMI088_ACC_RANGE_Pos                ()
#define BMI088_ACC_RANGE_Msk                ()
#define BMI088_ACC_RANGE                    BMI088_ACC_RANGE_Msk
#define BMI088_ACC_CONF_Pos                 () 
#define BMI088_ACC_CONF_Msk                 ()
#define BMI088_ACC_CONF                     BMI088_ACC_CONF
 /**
 * @name    BMI088 Shunt Voltage register fields
 * @{
 */
#define BMI088_                             (0U)
#define BMI088_                    (0xFFFFU << BMI088_SHUNT_Pos)
#define BMI088_
/** @} */

/**
 * @name    BMI088 VBUS Voltage register fields
 * @{
 */
#define BMI088_VBUS_Pos                     (0U)
#define BMI088_VBUS_Msk                     (0x7FFFU << BMI088_VBUS_Pos)
#define BMI088_VBUS                         BMI088_VBUS_Msk
/** @} */

/**
 * @name    BMI088 Power register fields
 * @{
 */
#define BMI088_POWER_Pos                    (0U)
#define BMI088_POWER_Msk                    (0xFFFFU << BMI088_POWER_Pos)
#define BMI088_POWER                        BMI088_POWER_Msk
/** @} */

/**
 * @name    BMI088 Current register fields
 * @{
 */
#define BMI088_CURRENT_Pos                  (0U)
#define BMI088_CURRENT_Msk                  (0xFFFFU << BMI088_CURRENT_Pos)
#define BMI088_CURRENT                      BMI088_CURRENT_Msk
/** @} */

/**
 * @name    BMI088 Calibration register fields
 * @{
 */
#define BMI088_CAL_Pos                      (0U)
#define BMI088_CAL_Msk                      (0x7FFFU << BMI088_CAL_Pos)
#define BMI088_CAL                          BMI088_CAL_Msk
/** @} */

/**
 * @name    BMI088 Alert Mask/Enable register fields
 * @{
 */
#define BMI088_ME_LEN_Pos                   (0U)
#define BMI088_ME_LEN_Msk                   (0x1U << BMI088_ME_LEN_Pos)
#define BMI088_ME_LEN                       BMI088_ME_LEN_Msk
#define BMI088_ME_APOL_Pos                  (1U)
#define BMI088_ME_APOL_Msk                  (0x1U << BMI088_ME_APOL_Pos)
#define BMI088_ME_APOL                      BMI088_ME_APOL_Msk
#define BMI088_ME_OVF_Pos                   (2U)
#define BMI088_ME_OVF_Msk                   (0x1U << BMI088_ME_OVF_Pos)
#define BMI088_ME_OVF                       BMI088_ME_OVF_Msk
#define BMI088_ME_CVRF_Pos                  (3U)
#define BMI088_ME_CVRF_Msk                  (0x1U << BMI088_ME_CVRF_Pos)
#define BMI088_ME_CVRF                      BMI088_ME_CVRF_Msk
#define BMI088_ME_AFF_Pos                   (4U)
#define BMI088_ME_AFF_Msk                   (0x1U << BMI088_ME_AFF_Pos)
#define BMI088_ME_AFF                       BMI088_ME_AFF_Msk
#define BMI088_ME_CNVR_Pos                  (10U)
#define BMI088_ME_CNVR_Msk                  (0x1U << BMI088_ME_CNVR_Pos)
#define BMI088_ME_CNVR                      BMI088_ME_CNVR_Msk
#define BMI088_ME_POL_Pos                   (11U)
#define BMI088_ME_POL_Msk                   (0x1U << BMI088_ME_POL_Pos)
#define BMI088_ME_POL                       BMI088_ME_POL_Msk
#define BMI088_ME_BUL_Pos                   (12U)
#define BMI088_ME_BUL_Msk                   (0x1U << BMI088_ME_BUL_Pos)
#define BMI088_ME_BUL                       BMI088_ME_BUL_Msk
#define BMI088_ME_BOL_Pos                   (13U)
#define BMI088_ME_BOL_Msk                   (0x1U << BMI088_ME_BOL_Pos)
#define BMI088_ME_BOL                       BMI088_ME_BOL_Msk
#define BMI088_ME_SUL_Pos                   (14U)
#define BMI088_ME_SUL_Msk                   (0x1U << BMI088_ME_SUL_Pos)
#define BMI088_ME_SUL                       BMI088_ME_SUL_Msk
#define BMI088_ME_SOL_Pos                   (15U)
#define BMI088_ME_SOL_Msk                   (0x1U << BMI088_ME_SOL_Pos)
#define BMI088_ME_SOL                       BMI088_ME_SOL_Msk
/** @} */

/**
 * @name    BMI088 Alert Limit register fields
 * @{
 */
#define BMI088_LIM_Pos                      (0U)
#define BMI088_LIM_Msk                      (0xFFFFU << BMI088_LIM_Pos)
#define BMI088_LIM                          BMI088_LIM_Msk
/** @} */

/**
 * @name    BMI088 Manufacturer ID register fields
 * @{
 */
#define BMI088_MFG_ID_Pos                   (0U)
#define BMI088_MFG_ID_Msk                   (0xFFFFU << BMI088_MFG_ID_Pos)
#define BMI088_MFG_ID                       BMI088_MFG_ID_Msk
/** @} */

/**
 * @name    BMI088 Die ID register fields
 * @{
 */
#define BMI088_DIE_ID_RID_Pos               (0U)
#define BMI088_DIE_ID_RID_Msk               (0xFU << BMI088_DIE_ID_RID_Pos)
#define BMI088_DIE_ID_RID                   BMI088_DIE_ID_RID_Msk
#define BMI088_DIE_ID_DID_Pos               (4U)
#define BMI088_DIE_ID_DID_Msk               (0xFFFU << BMI088_DIE_ID_DID_Pos)
#define BMI088_DIE_ID_DID                   BMI088_DIE_ID_DID_Msk
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   BMI088 I2C interface switch.
 * @details If set to @p TRUE the support for I2C is included.
 * @note    The default is @p TRUE.
 */
#if !defined(BMI088_USE_I2C) || defined(__DOXYGEN__)
#define BMI088_USE_I2C                      TRUE
#endif

/**
 * @brief   BMI088 shared I2C switch.
 * @details If set to @p TRUE the device acquires I2C bus ownership
 *          on each transaction.
 * @note    The default is @p FALSE. Requires I2C_USE_MUTUAL_EXCLUSION.
 */
#if !defined(BMI088_SHARED_I2C) || defined(__DOXYGEN__)
#define BMI088_SHARED_I2C                   FALSE
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if BMI088_USE_I2C && !HAL_USE_I2C
#error "BMI088_USE_I2C requires HAL_USE_I2C"
#endif

#if BMI088_SHARED_I2C && !I2C_USE_MUTUAL_EXCLUSION
#error "BMI088_SHARED_I2C requires I2C_USE_MUTUAL_EXCLUSION"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @name    BMI088 data structures and types.
 * @{
 */
/**
 * @brief Structure representing a BMI088 driver.
 */
typedef struct BMI088Driver BMI088Driver;

/**
 * @brief   Driver state machine possible states.
 */
typedef enum {
    BMI088_UNINIT = 0,                  /**< Not initialized.                 */
    BMI088_STOP = 1,                    /**< Stopped.                         */
    BMI088_READY = 2,                   /**< Ready.                           */
} bmi088_state_t;

/**
 * @brief   BMI088 configuration structure.
 */
typedef struct {
#if (BMI088_USE_I2C) || defined(__DOXYGEN__)
    /**
     * @brief I2C driver associated with this BMI088.
     */
    I2CDriver                   *i2cp;
    /**
     * @brief I2C configuration associated with this BMI088.
     */
    const I2CConfig             *i2ccfg;
    /**
     * @brief BMI088 Slave Address
     */
    i2caddr_t                   saddr;
#endif /* BMI088_USE_I2C */
    /**
     * @brief BMI088 configuration reg value
     */
    uint16_t                    cfg;
    /**
     * @brief BMI088 calibration reg value
     */
    uint16_t                    cal;
    /**
     * @brief Optional Current LSB value for use in calculations
     */
    uint16_t                    curr_lsb;
} BMI088Config;

/**
 * @brief   @p BMI088 specific methods.
 */
#define _bmi088_methods_alone

/**
 * @brief   @p BMI088 specific methods with inherited ones.
 */
#define _bmi088_methods                                                     \
    _base_object_methods

/**
 * @extends BaseObjectVMT
 *
 * @brief   @p BMI088 virtual methods table.
 */
struct BMI088VMT {
    _bmi088_methods
};

/**
 * @brief   @p BMI088Driver specific data.
 */
#define _bmi088_data                                                        \
    _base_object_data                                                       \
    /* Driver state.*/                                                      \
    bmi088_state_t              state;                                      \
    /* Current configuration data.*/                                        \
    const BMI088Config          *config;

/**
 * @brief BMI088 Power Monitor class.
 */
struct BMI088Driver {
    /** @brief Virtual Methods Table.*/
    const struct BMI088VMT     *vmt;
    _bmi088_data
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
void bmi088ObjectInit(BMI088Driver *devp);
void bmi088Start(BMI088Driver *devp, const BMI088Config *config);
void bmi088Stop(BMI088Driver *devp);
void bmi088SetAlert(BMI088Driver *devp, uint16_t alert_me, uint16_t alert_lim);
uint16_t bmi088ReadRaw(BMI088Driver *devp, uint8_t reg);
int16_t bmi088ReadShunt(BMI088Driver *devp);
uint16_t bmi088ReadVBUS(BMI088Driver *devp);
int16_t bmi088ReadCurrent(BMI088Driver *devp);
uint16_t bmi088ReadPower(BMI088Driver *devp);
#ifdef __cplusplus
}
#endif

#endif /* _BMI088_H_ */

/** @} */
