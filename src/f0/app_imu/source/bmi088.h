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
#define BMI088_AD_ACC_SOFTRESET             0x7EU
#define BMI088_AD_ACC_PWR_CTRL              0x7DU
#define BMI088_AD_ACC_PWR_CONF              0x7CU
#define BMI088_AD_ACC_SELF_TEST             0x6DU
#define BMI088_AD_INT_MAP_DATA              0x58U
#define BMI088_AD_INT2_IO_CTRL              0x54U
#define BMI088_AD_INT1_IO_CTRL              0x53U
#define BMI088_AD_FIFO_CONFIG_1             0x49U
#define BMI088_AD_FIFO_CONFIG_0             0x48U
#define BMI088_AD_FIFO_WTM_1                0x47U
#define BMI088_AD_FIFO_WTM_0                0x46U
#define BMI088_AD_FIFO_DOWNS                0x45U 
#define BMI088_AD_ACC_RANGE                 0x41U
#define BMI088_AD_ACC_CONF                  0x40U
#define BMI088_AD_FIFO_DATA                 0x26U
#define BMI088_AD_FIFO_LENGTH_1             0x25U
#define BMI088_AD_FIFO_LENGTH_1             0x24U
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
 * @name    BMI088 ACC Soft Reset register fields
 * @{
 */
#define BMI088_ACC_SOFTRESET_Pos            (0U)
#define BMI088_ACC_SFOTRESET_Msk            (0xFFU << BMI088_ACC_SOFT_RESET_Pos)
#define BMI088_ACC_SOFTRESET                BMI088_ACC_SOFTRESET_Msk
#define BMI088_ACC_SOFTRESET_CMD            (0xB6U)
/**@} */

/**
 * @name    BMI088 ACC Power Control register fields
 * @{
 */
#define BMI088_ACC_PWR_CTRL_Pos             (0U)
#define BMI088_ACC_PWR_CTRL_Msk             (0xFFU << BMI088_ACC_PWR_CTRL_Pos)
#define BMI088_ACC_PWR_CTRL                 BMI088_ACC_PWR_CTRL_Msk
#define BMI088_ACC_PWR_CTRL_EN_ON           (0x00U)
#define BMI088_ACC_PWR_CTRL_EN_OFF          (0x04U)      
/**
 * @name    BMI088 ACC Power Configuration register fields
 * @{
 */
#define BMI088_ACC_PWR_CONF_Pos             (0U)
#define BMI088_ACC_PWR_CONF_Msk             (0xFFU << BMI088_ACC_PWR_CONF_Pos)
#define BMI088_ACC_PWR_CONF                 BMI088_ACC_PWR_CONF_Msk
#define BMI088_ACC_PWR_CONF_PWR_SAVE_SSPND  (0x03U)
#define BMI088_ACC_PWR_CONF_PWR_SAVE_ACTIVE (0x00U)
/**@}*/

/**
 * @name    BMI088 ACC Self Test register fields
 * @{
 */
#define BMI088_ACC_SELF_TEST_Pos            (0U)
#define BMI088_ACC_SELF_TEST_Msk            (0xFFU << BMI088_ACC_SELF_TEST_Pos)
#define BMI088_ACC_SELF_TEST                BMI088_ACC_SELF_TEST_Msk 
#define BMI088_ACC_SELF_TEST_OFF            (0x0U)
#define BMI088_ACC_SELF_TEST_POS_SIG        (0xDU)
#define BMI088_ACC_SELF_TEST_NEG_SIG        (0x9U)
/**@}*/

/**
 * @name    BMI088 ACC Int Map Data register fields
 * @{
 */
#define BMI088_ACC_INT1_MAP_DATA_FFULL_Pos  (0U)
#define BMI088_ACC_INT1_MAP_DATA_FFULL_Msk  (0x1U << BMI088_ACC_INT1_MAP_DATA_FFULL_Pos)
#define BMI088_ACC_INT1_MAP_DATA_FFULL      BMI088_ACC_INT1_MAP_DATA_FFULL_Msk
#define BMI088_ACC_INT1_MAP_DATA_FWM_Pos    (1U)
#define BMI088_ACC_INT1_MAP_DATA_FWM_Msk    (0x1U << BMI088_ACC_INT1_MAP_DATA_FWM_Pos)
#define BMI088_ACC_INT1_MAP_DATA_FWM        BMI088_ACC_INT1_MAP_DATA_FWM_Msk
#define BMI088_ACC_INT1_MAP_DATA_DRDY_Pos   (2U)
#define BMI088_ACC_INT1_MAP_DATA_DRDY_Msk   (0x1U << BMI088_ACC_INT1_MAP_DATA_DRDY_Pos)
#define BMI088_ACC_INT1_MAP_DATA_DRDY       BMI088_ACC_INT1_MAP_DATA_DRDY_Msk
#define BMI088_ACC_INT2_MAP_DATA_FFUL_Po    (4U)
#define BMI088_ACC_INT2_MAP_DATA_FFULL_M    (0x1U << BMI088_ACC_INT2_MAP_DATA_FFULL_Pos)
#define BMI088_ACC_INT2_MAP_DATA_FFULL      BMI088_ACC_INT2_MAP_DATA_FFULL_Msk 
#define BMI088_ACC_INT2_MAP_DATA_FWM_Pos    (5U)
#define BMI088_ACC_INT2_MAP_DATA_FWM_Msk    (0x1U BMI088_ACC_INT2_MAP_DATA_FWM_Pos)
#define BMI088_ACC_INT2_MAP_DATA_FWM        BMI088_ACC_INT2_MAP_DATA_FWM_Msk  
#define BMI088_ACC_INT2_MAP_DATA_DRDY_Pos   (6U)
#define BMI088_ACC_INT2_MAP_DATA_DRDY_Msk   (0x1U << BMI088_ACC_INT2_MAP_DATA_DRDY_Pos)
#define BMI088_ACC_INT2_MAP_DATA_DRDY       BMI088_ACC_INT2_MAP_DATA_DRDY_Msk  
/**@}*/

/**
 * @name    BMI088 ACC Int2 IO Control Configuration register fields
 * @{
 */
#define BMI088_ACC_INT2_IO_CTRL_Pos         (1U)
#define BMI088_ACC_INT2_IO_CTRL_Msk         (0x1EU << BMI088_ACC_INT2_IO_CTRL_Pos)
#define BMI088_ACC_INT2_IO_CTRL             BMI088_ACC_INT2_IO_CTRL_Msk
#define BMI088_ACC_INT2_IO_CTRL_LVL         (0x1U BMI088_ACC_INT2_IO_CTRL_Pos)
#define BMI088_ACC_INT2_IO_CTRL_OD          (0x2U BMI088_ACC_INT2_IO_CTRL_Pos)
#define BMI088_ACC_INT2_IO_CTRL_OUT         (0x3U BMI088_ACC_INT2_IO_CTRL_Pos)
#define BMI088_ACC_INT2_IO_CTRL_IN          (0x4U BMI088_ACC_INT2_IO_CTRL_Pos) 
/**@}*/

/**
 * @name    BMI088 ACC Int1 IO Configuration register fields
 * @{
 */
#define BMI088_ACC_INT1_IO_CTRL_Pos         (1U)
#define BMI088_ACC_INT1_IO_CTRL_Msk         (0x1EU << BMI088_ACC_INT1_IO_CTRL_Pos)
#define BMI088_ACC_INT1_IO_CTRL             BMI088_ACC_INT1_IO_CTRL_Msk
#define BMI088_ACC_INT1_IO_CTRL_LVL         (0x1U <<  BMI088_ACC_INT1_IO_CTRL_Pos)
#define BMI088_ACC_INT1_IO_CTRL_OD          (0x2U <<  BMI088_ACC_INT1_IO_CTRL_Pos)
#define BMI088_ACC_INT1_IO_CTRL_OUT         (0x3U <<  BMI088_ACC_INT1_IO_CTRL_Pos)
#define BMI088_ACC_INT1_IO_CTRL_IN          (0x4U <<  BMI088_ACC_INT1_IO_CTRL_Pos)
/**@}*/


 /*
 * @name    BMI088 ACC FIFO configuration 1 register fields
 * @{
 */
#define BMI088_ACC_FIFO_CONFIG_1_Pos        (2U)
#define BMI088_ACC_FIFO_CONFIG_1_Msk        (0x13U << BMI088_ACC_FIFO_CONFIG_1_Pos)
#define BMI088_ACC_FIFO_CONFIG_1            BMI088_ACC_FIFO_CONFIG_1_Msk
#define BMI088_ACC_FIFO_CONFIG_1_INT2_EN    (0x01U << BMI088_ACC_FIFO_CONFIG_1_Pos)
#define BMI088_ACC_FIFO_CONFIG_1_INT1_EN    (0x02U << BMI088_ACC_FIFO_CONFIG_1_Pos)
#define BMI088_ACC_FIFO_CONFIG_1_ACC_EN     (0x10U << BMI088_ACC_FIFO_CONFIG_1_Pos)
/** @} */

/**
 * @name    BMI088 ACC FIFO Configuration 0 register fields
 * @{
 */
#define BMI088_ACC_FIFO_CONFIG_0_Pos        (0U)
#define BMI088_ACC_FIFO_CONFIG_0_Msk        (0x1U << BMI088_ACC_FIFO_CONFIG_0_Pos)
#define BMI088_ACC_FIFO_CONFIG_0            BMI088_ACC_FIFO_CONFIG_0_Msk
#define BMI088_ACC_FIFO_CONFIG_0_STREAM     (0x0U << BMI088_ACC_FIFI_CONFIG_0_Pos) 
#define BMI088_ACC_FIFO_CONFIG_0_FIFO       (0x1U << BMI088_ACC_FIFI_CONFIG_0_Pos)
/** @} */

/**
 * @name    BMI088 ACC FIFO Watermark 1 register fields
 * @{
 */
#define BMI088_ACC_FIFO_WTM_1_Pos           (0U) 
#define BMI088_ACC_FIFO_WTM_1_Msk           (0x1FU << BMI088_ACC_FIFO_WTM_1_Pos) 
#define BMI088_ACC_FIFO_WTM_1               BMI088_ACC_FIFO_WTM_1_Msk
/** @} */

/**
 * @name    BMI088 ACC FIFO Watermark 0 register fields
 * @{
 */
#define BMI088_ACC_FIFO_WTM_0_Pos          (0U) 
#define BMI088_ACC_FIFO_WTM_0_Msk          (0xFFU << BMI088_ACC_FIFO_WTM_1_Pos) 
#define BMI088_ACC_FIFO_WTM_0              BMI088_ACC_FIFO_WTM_0_Msk
/** @} */

/**
 * @name    BMI088 ACC FIFO DOWNS register fields
 * @{
 */
#define BMI088_ACC_FIFO_DOWNS_Pos           (5U) 
#define BMI088_ACC_FIFO_DOWNS_Msk           (0x7U << BMI088_ACC_FIFO_DOWNS_Pos) 
#define BMI088_ACC_FIFO_DOWNS               BMI088_ACC_FIFO_DOWNS_Msk      
/** @} */

/**
 * @name    BMI088 ACC Range register fields
 * @{
 */
#define BMI088_ACC_RANGE_Pos                (0U)
#define BMI088_ACC_RANGE_Msk                (0x3U << BMI088_ACC_RANGE_Pos)
#define BMI088_ACC_RANGE                    BMI088_ACC_RANGE_Msk
#define BMI088_ACC_RANGE_3g                 (0x0U << BMI088_ACC_RANGE_Pos)
#define BMI088_ACC_RANGE_6g                 (0x1U << BMI088_ACC_RANGE_Pos)
#define BMI088_ACC_RANGE_12g                (0x2U << BMI088_ACC_RANGE_Pos)
#define BMI088_ACC_RANGE_24g                (0x3U << BMI088_ACC_RANGE_Pos)
/** @} */

/**
 * @name    BMI088 ACC configure register fields
 * @{
 */
#define BMI088_ACC_CONF_ODR_Pos             (0U)
#define BMI088_ACC_CONF_ODR_Msk             (0xFU << BMI088_ACC_CONF_Pos)
#define BMI088_ACC_CONF_ODR                 BMI088_ACC_CONF_Msk
#define BMI088_ACC_CONF_ODR_12_5_HZ         (0x5U << BMI088_ACC_CONF_Pos)
#define BMI088_ACC_CONF_ODR_25_HZ           (0x6U << BMI088_ACC_CONF_Pos)
#define BMI088_ACC_CONF_ODR_50_HZ           (0x7U << BMI088_ACC_CONF_Pos)
#define BMI088_ACC_CONF_ODR_100_HZ          (0x8U << BMI088_ACC_CONF_Pos)
#define BMI088_ACC_CONF_ODR_200_HZ          (0x9U << BMI088_ACC_CONF_Pos)
#define BMI088_ACC_CONF_ODR_400_HZ          (0xAU << BMI088_ACC_CONF_Pos)
#define BMI088_ACC_CONF_ODR_800_HZ          (0x0U << BMI088_ACC_CONF_Pos)
#define BMI088_ACC_CONF_ODR_1600_HZ         (0x8U << BMI088_ACC_CONF_Pos)
#define BMI088_ACC_CONF_BWP_Pos             (4U)
#define BMI088_ACC_CONF_BWP_Msk             (0xFU << BMI088_ACC_CONF_BWP_Pos)
#define BMI088_ACC_CONF_BWP                 BMI088_ACC_CONF_BWP_Msk
#define BMI088_ACC_CONF_BWP_OSR4            (0x8U << BMI088_ACC_CONF_Pos)
#define BMI088_ACC_CONF_BWP_OSR2            (0x9U << BMI088_ACC_CONF_Pos)
#define BMI088_ACC_CONF_BWP_NORMAL          (0xAU << BMI088_ACC_CONF_Pos)
/** @} */

/**
 * @name    BMI088 ACC FIFO Data register fields
 * @{
 */
#define BMI088_ACC_FIFO_DATA_Pos            (0U)
#define BMI088_ACC_FIFO_DATA_Msk            (0xFFU << BMI088_ACC_FIFO_DATA_Pos)         
#define BMI088_ACC_FIFO_DATA                BMI088_ACC_FIFO_DATA_Msk        
/** @} */

/**
 * @name    BMI088 ACC FIFO Length 0 register fields
 * @{
 */
#define BMI088_ACC_FIFO_LENGTH_0_Pos        (0U)
#define BMI088_ACC_FIFO_LENGTH_0_Msk        (0xFFU << BMI088_ACC_LENGTH_0_Pos)
#define BMI088_ACC_FIFO_LENGTH_0            BMI088_ACC_FIFO_LENGTH_0_Msk
/** @} */

/**
 * @name    BMI088 ACC FIFO Length 0 register fields
 * @{
 */
#define BMI088_ACC_FIFO_LENGTH_1_Pos        (0U)
#define BMI088_ACC_FIFO_LENGTH_1_Msk        (0x3FU << BMI088_ACC_LENGTH_1_Pos)
#define BMI088_ACC_FIFO_LENGTH_1            BMI088_ACC_FIFO_LENGTH_1_Msk
/** @} */

/**
 * @name    BMI088 ACC Temp LSB register fields
 * @{
 */
#define BMI088_ACC_TEMP_LSB_Pos             (5U)
#define BMI088_ACC_TEMP_LSB_Msk             (0x7U << BMI088_ACC_TEMP_LSB_Pos)
#define BMI088_ACC_TEMP_LSB                 BMI088_ACC_TEMP_LSB_Msk
/** @} *//**

 * @name    BMI088 ACC Temp MSB register fields
 * @{
 */
#define BMI088_ACC_TEMP_MSB_Pos             (0U)
#define BMI088_ACC_TEMP_MSB_Msk             (0xFFU << BMI088_ACC_TEMP_MSB_Pos)
#define BMI088_ACC_TEMP_MSB                 BMI088_ACC_TEMP_MSB_Msk
/** @} */

/**
 * @name    BMI088 ACC Int Stat 1 register fields
 * @{
 */
#define BMI088_ACC_INT_STAT_1_Pos           (7U)
#define BMI088_ACC_INT_STAT_1_Msk           (0x1U << BMI088_ACC_INT_STAT_1_Pos)
#define BMI088_ACC_INT_STAT_1               BMI088_ACC_INT_STAT_1_Msk
#define BMI088_ACC_INT_STAT_1_DRDY          (0x1U << BMI088_ACC_INT_STAT_1_Pos)
/** @} */

/**
 * @name    BMI088 ACC Sensor Time 0 register fields
 * @{
 */
#define BMI088_ACC_SENSOR_TIME_0_Pos        (0U)
#define BMI088_ACC_SENSOR_TIME_0_Msk        (0xFFU << BMI088_ACC_SENSOR_TIME_0_Pos)
#define BMI088_ACC_SENSOR_TIME_0            BMI088_ACC_SENSOR_TIME_0_Msk
/** @} */

/**
 * @name    BMI088 ACC Sensor Time 1 register fields
 * @{
 */
#define BMI088_ACC_SENSOR_TIME_1_Pos        (7U)
#define BMI088_ACC_SENSOR_TIME_1_Msk        (0xFFU << BMI088_ACC_SENSOR_TIME_1_Pos)
#define BMI088_ACC_SENSOR_TIME_1            BMI088_ACC_SENSOR_TIME_1_Msk
/** @} */
/** @} */

/**
 * @name    BMI088 ACC Sensor Time 2 register fields
 * @{
 */
#define BMI088_ACC_SENSOR_TIME_2_Pos        (7U)
#define BMI088_ACC_SENSOR_TIME_2_Msk        (0xFFU << BMI088_ACC_SENSOR_TIME_2_Pos)
#define BMI088_ACC_SENSOR_TIME_2            BMI088_ACC_SENSOR_TIME_2_Msk
/** @} */
/** @} */

/**
 * @name    BMI088 ACC Z MSB register fields
 * @{
 */
#define BMI088_ACC_Z_MSB_Pos                (0U)
#define BMI088_ACC_Z_MSB_MsK                (0XFFU << BMI088_ACC_Z_MSB_Pos )
#define BMI088_ACC_Z_MSB                    BMI088_ACC_Z_MSB_Msk
/** @} */

/**
 * @name    BMI088 ACC Z LSB register fields
 * @{
 */
#define BMI088_ACC_Z_LSB_Pos                (0U)
#define BMI088_ACC_Z_LSB_Msk                (0xFFU << BMI088_ACC_Z_LSB_Pos)
#define BMI088_ACC_Z_LSB                    BMI088_ACC_Z_LSB_Msk
/** @} */

/**
 * @name    BMI088 ACC Y MSB register fields
 * @{
 */
#define BMI088_ACC_Y_MSB_Pos                (0U)
#define BMI088_ACC_Y_MSB_MsK                (0xFFU << BMI088_ACC_Y_MSB_Pos)
#define BMI088_ACC_Y_MSB                    BMI088_ACC_Y_MSB_Msk
/** @} */

/**
 * @name    BMI088 ACC Y LSB register fields
 * @{
 */
#define BMI088_ACC_Y_LSB_Pos                (0U)
#define BMI088_ACC_Y_LSB_Msk                (0xFFU << BMI088_ACC_Y_LSB_Pos)
#define BMI088_ACC_Y_LSB                    BMI088_ACC_Y_LSB_Msk
/** @} */

/**
 * @name    BMI088 ACC X MSB register fields
 * @{
 */
#define BMI088_ACC_X_MSB_Pos                (0U)
#define BMI088_ACC_X_MSB_Msk                (0xFFU << BMI088_ACC_X_MSB_Pos)
#define BMI088_ACC_X_MSB                    BMI088_ACC_X_MSB_Msk
/** @} */

/**
 * @name    BMI088 ACC X LSB register fields
 * @{
 */
#define BMI088_ACC_X_LSB_Pos                (0U)
#define BMI088_ACC_X_LSB_Msk                (0xFFU << BMI088_ACC_X_LSB_Pos)
#define BMI088_ACC_X_LSB                    BMI088_ACC_x_LSB_Msk
/** @} */

/**
 * @name    BMI088 ACC Status register fields
 * @{
 */
#define BMI088_ACC_STATUS_Pos               (7U)
#define BMI088_ACC_STATUS_Msk               (0x1U << BMI088_ACC_STATUS_Pos)
#define BMI088_ACC_STATUS                   BMI088_ACC_STATUS_Msk
/** @} */

/**
 * @name    BMI088 ACC Error register fields
 * @{
 */
#define BMI088_ACC_ERR_FATAL_Pos            (0U)
#define BMI088_ACC_ERR_FATAL_Msk            (0x1U << BMI088_ACC_ERR_FATAL_Pos)
#define BMI088_ACC_ERR_FATAL                BMI088_ACC_ERR_FATAL_Msk
#define BMI088_ACC_ERR_CODE_Pos             (2U)
#define BMI088_ACC_ERR_CODE_Msk             (0x7U << BMI088_ACC_ERR_CODE_Pos)
#define BMI088_ACC_ERR_CODE                 BMI088_ACC_ERR_CODE_Msk
/** @} */

/**
 * @name    BMI088 ACC Chip ID register fields
 * @{
 */
#define BMI088_ACC_CHIP_ID_Pos              (0U)
#define BMI088_ACC_CHIP_ID_Msk              (0xFFU << BMI088_ACC_CHIP_ID_Pos)
#define BMI088_ACC_CHIP_ID                  BMI088_ACC_CHIP_ID_Msk
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
