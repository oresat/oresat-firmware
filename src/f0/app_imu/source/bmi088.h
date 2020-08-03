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
 * @name    BMI088 Accelerometer Register Addresses
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
#define BMI088_ACC_SOFTRESET_RST            (0xB6U << BMI088_ACC_SOFTRESET_Pos)
/**@} */

/**
 * @name    BMI088 ACC Power Control register fields
 * @{
 */
#define BMI088_ACC_PWR_CTRL_EN_Pos          (0U)
#define BMI088_ACC_PWR_CTRL_EN_Msk          (0xFFU << BMI088_ACC_PWR_CTRL_EN_Pos)
#define BMI088_ACC_PWR_CTRL                 BMI088_ACC_PWR_CTRL_EN_Msk
#define BMI088_ACC_PWR_CTRL_EN_ON           (0x04U << BMI088_ACC_PWR_CTRL_EN_Pos)
#define BMI088_ACC_PWR_CTRL_EN_OFF          (0x00U << BMI088_ACC_PWR_CTRL_EN_Pos)
#define BMI088_ACC_PWR_CTRL_RST             (0x00U << BMI088_ACC_PWR_CTRL_EN_Pos)
/**
 * @name    BMI088 ACC Power Configuration register fields
 * @{
 */
#define BMI088_ACC_PWR_CONF_PWR_SAVE_Pos    (0U)
#define BMI088_ACC_PWR_CONF_PWR_SAVE_Msk    (0xFFU << BMI088_ACC_PWR_CONF_PWR_SAVE_Pos)
#define BMI088_ACC_PWR_CONF_PWR_SAVE        BMI088_ACC_PWR_CONF_PWR_SAVE_Msk
#define BMI088_ACC_PWR_CONF_PWR_SAVE_SSPND  (0x03U << BMI088_ACC_PWR_CONF_PWR_SAVE_Pos)
#define BMI088_ACC_PWR_CONF_PWR_SAVE_ACTIVE (0x00U << BMI088_ACC_PWR_CONF_PWR_SAVE_Pos)
#define BMI088_ACC_PWR_CONF_PWR_SAVE_RST    (0x03U << BMI088_ACC_PWR_CONF_PWR_SAVE_Pos)
/**@}*/

/**
 * @name    BMI088 ACC Self Test register fields
 * @{
 */
#define BMI088_ACC_SELF_TEST_Pos            (0U)
#define BMI088_ACC_SELF_TEST_Msk            (0xFFU << BMI088_ACC_SELF_TEST_Pos)
#define BMI088_ACC_SELF_TEST                BMI088_ACC_SELF_TEST_Msk 
#define BMI088_ACC_SELF_TEST_OFF            (0x00U << BMI088_ACC_SELF_TEST_Pos)
#define BMI088_ACC_SELF_TEST_POS_SIG        (0x0DU << BMI088_ACC_SELF_TEST_Pos)
#define BMI088_ACC_SELF_TEST_NEG_SIG        (0x09U << BMI088_ACC_SELF_TEST_Pos)
#define BMI088_ACC_SELF_TEST_RST            (0x00U << BMI088_ACC_SELF_TEST_Pos)
/**@}*/

/**
 * @name    BMI088 ACC Int Map Data register fields
 * @{
 */
#define BMI088_ACC_MAP_DATA_INT1_FFULL_Pos  (0U)
#define BMI088_ACC_MAP_DATA_INT1_FFULL_Msk  (0x1U << BMI088_ACC_MAP_DATA_INT1_FFULL_Pos)
#define BMI088_ACC_MAP_DATA_INT1_FFULL      BMI088_ACC_MAP_DATA_INT1_FFULL_Msk
#define BMI088_ACC_MAP_DATA_INT1_FWM_Pos    (1U)
#define BMI088_ACC_MAP_DATA_INT1_FWM_Msk    (0x1U << BMI088_ACC_MAP_DATA_INT1_FWM_Pos)
#define BMI088_ACC_MAP_DATA_INT1_FWM        BMI088_ACC_MAP_DATA_INT1_FWM_Msk
#define BMI088_ACC_MAP_DATA_INT1_DRDY_Pos   (2U)
#define BMI088_ACC_MAP_DATA_INT1_DRDY_Msk   (0x1U << BMI088_ACC_MAP_DATA_INT1_DRDY_Pos)
#define BMI088_ACC_MAP_DATA_INT1_DRDY       BMI088_ACC_MAP_DATA_INT1_DRDY_Msk
#define BMI088_ACC_MAP_DATA_INT2_FFUL_Po    (4U)
#define BMI088_ACC_MAP_DATA_INT2_FFULL_M    (0x1U << BMI088_ACC_MAP_INT2_DATA_FFULL_Pos)
#define BMI088_ACC_MAP_DATA_INT2_FFULL      BMI088_ACC_MAP_DATA_INT2_FFULL_Msk 
#define BMI088_ACC_MAP_DATA_INT2_FWM_Pos    (5U)
#define BMI088_ACC_MAP_DATA_INT2_FWM_Msk    (0x1U << BMI088_ACC_MAP_DATA_INT2_FWM_Pos)
#define BMI088_ACC_MAP_DATA_INT2_FWM        BMI088_ACC_MAP_DATA_INT2_FWM_Msk  
#define BMI088_ACC_MAP_DATA_INT2_DRDY_Pos   (6U)
#define BMI088_ACC_MAP_DATA_INT2_DRDY_Msk   (0x1U << BMI088_ACC_MAOP_DATA_INT2_DRDY_Pos)
#define BMI088_ACC_MAP_DATA_INT2_DRDY       BMI088_ACC_MAP_DATA_INT2_DRDY_Msk  
/**@}*/

/**
 * @name    BMI088 ACC Int2 IO Control register fields
 * @{
 */
#define BMI088_ACC_IO_CTRL_INT2_LVL_Pos     (1U)
#define BMI088_ACC_IO_CTRL_INT2_LVL_Msk     (0x1U << BMI088_ACC_IO_CTRL_INT2_LVL_Pos)
#define BMI088_ACC_IO_CTRL_INT2_LVL         BMI088_ACC_IO_CTRL_INT2_LVL_Msk
#define BMI088_ACC_IO_CTRL_INT2_LVL_L       (0x0U << BMI088_ACC_IO_CTRL_INT2_LVL_Pos)
#define BMI088_ACC_IO_CTRL_INT2_LVL_H       (0x1U << BMI088_ACC_IO_CTRL_INT2_LVL_Pos)
#define BMI088_ACC_IO_CTRL_INT2_OD_Pos      (2U)     
#define BMI088_ACC_IO_CTRL_INT2_OD_Msk      (0x1U << BMI088_ACC_IO_CTRL_INT2_OD_Pos)
#define BMI088_ACC_IO_CTRL_INT2_OD          BMI088_ACC_IO_CTRL_INT2_OD_Msk       
#define BMI088_ACC_IO_CTRL_INT2_OD_PSH_PLL  (0x0U << BMI088_ACC_IO_CTRL_INT2_OD_Pos)      
#define BMI088_ACC_IO_CTRL_INT2_OD_OPN_DRN  (0x1U << BMI088_ACC_IO_CTRL_INT2_OD_Pos)   
#define BMI088_ACC_IO_CTRL_INT2_EN_OUT_Pos  (3U)
#define BMI088_ACC_IO_CTRL_INT2_EN_OUT_Msk  (0x1U << BMI088_ACC_IO_CTRL_INT2_OUT_Pos
#define BMI088_ACC_IO_CTRL_INT2_EN_OUT      BMI088_ACC_IO_CTRL_INT2_EN_OUT_Msk
#define BMI088_ACC_IO_CTRL_INT2_EN_IN_Pos   (4U)   
#define BMI088_ACC_IO_CTRL_INT2_EN_IN_Msk   (0x1U << BMI088_ACC_IO_CTRL_INT2_EN_IN_Pos)   
#define BMI088_ACC_IO_CTRL_INT2_EN_IN       BMI088_ACC_IO_CTRL_INT2_EN_IN_Msk
/**@}*/

/**
 * @name    BMI088 ACC Int1 IO Configuration register fields
 * @{
 */
#define BMI088_ACC_IO_CTRL_INT1_LVL_Pos     (1U)
#define BMI088_ACC_IO_CTRL_INT1_LVL_Msk     (0x1U << BMI088_ACC_IO_CTRL_INT1_LVL_Pos)
#define BMI088_ACC_IO_CTRL_INT1_LVL         BMI088_ACC_IO_CTRL_INT1_LVL_Msk
#define BMI088_ACC_IO_CTRL_INT1_LVL_L       (0x0U << BMI088_ACC_IO_CTRL_INT1_LVL_Pos)
#define BMI088_ACC_IO_CTRL_INT1_LVL_H       (0x1U << BMI088_ACC_IO_CTRL_INT1_LVL_Pos)
#define BMI088_ACC_IO_CTRL_INT1_OD_Pos      (2U)     
#define BMI088_ACC_IO_CTRL_INT1_OD_Msk      (0x1U << BMI088_ACC_IO_CTRL_INT1_OD_Pos)
#define BMI088_ACC_IO_CTRL_INT1_OD          BMI088_ACC_IO_CTRL_INT1_OD_Msk       
#define BMI088_ACC_IO_CTRL_INT1_OD_PSH_PLL  (0x0U << BMI088_ACC_IO_CTRL_INT1_OD_Pos)      
#define BMI088_ACC_IO_CTRL_INT1_OD_OPN_DRN  (0x1U << BMI088_ACC_IO_CTRL_INT1_OD_Pos)   
#define BMI088_ACC_IO_CTRL_INT1_EN_OUT_Pos  (3U)
#define BMI088_ACC_IO_CTRL_INT1_EN_OUT_Msk  (0x1U << BMI088_ACC_IO_CTRL_INT1_OUT_Pos
#define BMI088_ACC_IO_CTRL_INT1_EN_OUT      BMI088_ACC_IO_CTRL_INT1_EN_OUT_Msk
#define BMI088_ACC_IO_CTRL_INT1_EN_IN_Pos   (4U)   
#define BMI088_ACC_IO_CTRL_INT1_EN_IN_Msk   (0x1U << BMI088_ACC_IO_CTRL_INT1_EN_IN_Pos)   
#define BMI088_ACC_IO_CTRL_INT1_EN_IN       BMI088_ACC_IO_CTRL_INT1_EN_IN_Msk
/**@}*/


/*
 * @name    BMI088 ACC FIFO configuration 1 register fields
 * @{
 */
#define BMI088_ACC_FIFO_CONFIG1_INT2_EN_Pos (2U)
#define BMI088_ACC_FIFO_CONFIG1_INT2_EN_Msk (0x1U << BMI088_ACC_FIFO_CONFIG1_INT2_EN_Pos)
#define BMI088_ACC_FIFO_CONFIG1_INT2_EN     BMI088_ACC_FIFO_CONFIG1_INT2_EN_Msk 
#define BMI088_ACC_FIFO_CONFIG1_INT1_EN_Pos (3U)    
#define BMI088_ACC_FIFO_CONFIG1_INT1_EN_Msk (0x1U << BMI088_ACC_FIFO_CONFIG1_INT1_EN_Pos)  
#define BMI088_ACC_FIFO_CONFIG1_INT1_EN     BMI088_ACC_FIFO_CONFIG1_INT1_EN_Msk		
#define BMI088_ACC_FIFO_CONFIG1_ACC_EN_Pos  (6U)    
#define BMI088_ACC_FIFO_CONFIG1_ACC_EN_Msk  (0x1U << BMI088_ACC_FIFO_CONFIG1_ACC_EN_Pos) 
#define BMI088_ACC_FIFO_CONFIG1_ACC_EN      BMI088_ACC_FIFO_CONFIG1_ACC_EN_Msk
/** @} */

/**
 * @name    BMI088 ACC FIFO Configuration 0 register fields
 * @{
 */
#define BMI088_ACC_FIFO_CONFIG0_MODE_Pos    (0U)
#define BMI088_ACC_FIFO_CONFIG0_MODE_Msk    (0x1U << BMI088_ACC_FIFO_CONFIG0_MODE_Pos)
#define BMI088_ACC_FIFO_CONFIG0_MODE        BMI088_ACC_FIFO_CONFIG0_MODE_Msk
#define BMI088_ACC_FIFO_CONFIG0_STREAM      (0x0U << BMI088_ACC_FIFI_CONFIG0_MODE_Pos)
#define BMI088_ACC_FIFO_CONFIG0_FIFO        (0x1U << BMI088_ACC_FIFI_CONFIG0_MODE_Pos)
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
#define BMI088_ACC_FIFO_DOWNS_Msk           (0x3U << BMI088_ACC_FIFO_DOWNS_Pos) 
#define BMI088_ACC_FIFO_DOWNS               BMI088_ACC_FIFO_DOWNS_Msk      
/** @} */

/**
 * @name    BMI088 ACC Range register fields
 * @{
 */
#define BMI088_ACC_RANGE_Pos                (0U)
#define BMI088_ACC_RANGE_Msk                (0x3U << BMI088_ACC_RANGE_Pos)
#define BMI088_ACC_RANGE                    BMI088_ACC_RANGE_Msk
#define BMI088_ACC_RANGE_PLUS_MINUS_3g      (0x0U << BMI088_ACC_RANGE_Pos)
#define BMI088_ACC_RANGE_PLUS_MINUS_6g      (0x1U << BMI088_ACC_RANGE_Pos)
#define BMI088_ACC_RANGE_PLUS_MINUS_12g     (0x2U << BMI088_ACC_RANGE_Pos)
#define BMI088_ACC_RANGE_PLUS_MINUS_24g     (0x3U << BMI088_ACC_RANGE_Pos)
/** @} */

/**
 * @name    BMI088 ACC configure register fields
 * @{
 */
#define BMI088_ACC_CONF_ODR_Pos             (0U)
#define BMI088_ACC_CONF_ODR_Msk             (0xFU << BMI088_ACC_CONF_Pos)
#define BMI088_ACC_CONF_ODR                 BMI088_ACC_CONF_Msk
#define BMI088_ACC_CONF_ODR_12500mHZ        (0x5U << BMI088_ACC_CONF_Pos)
#define BMI088_ACC_CONF_ODR_25HZ            (0x6U << BMI088_ACC_CONF_Pos)
#define BMI088_ACC_CONF_ODR_50HZ            (0x7U << BMI088_ACC_CONF_Pos)
#define BMI088_ACC_CONF_ODR_100HZ           (0x8U << BMI088_ACC_CONF_Pos)
#define BMI088_ACC_CONF_ODR_200HZ           (0x9U << BMI088_ACC_CONF_Pos)
#define BMI088_ACC_CONF_ODR_400HZ           (0xAU << BMI088_ACC_CONF_Pos)
#define BMI088_ACC_CONF_ODR_800HZ           (0x0U << BMI088_ACC_CONF_Pos)
#define BMI088_ACC_CONF_ODR_1600HZ          (0x8U << BMI088_ACC_CONF_Pos)
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
 * @name    BMI088 ACC FIFO Length 1 register fields
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
#define BMI088_ACC_SENSOR_TIME_1_Pos        (0U)
#define BMI088_ACC_SENSOR_TIME_1_Msk        (0xFFU << BMI088_ACC_SENSOR_TIME_1_Pos)
#define BMI088_ACC_SENSOR_TIME_1            BMI088_ACC_SENSOR_TIME_1_Msk
/** @} */
/** @} */

/**
 * @name    BMI088 ACC Sensor Time 2 register fields
 * @{
 */
#define BMI088_ACC_SENSOR_TIME_2_Pos        (0U)
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
#define BMI088_ACC_Y_MSB_Msk                (0xFFU << BMI088_ACC_Y_MSB_Pos)
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

/**
 * @name    BMI088 Gyroscope Register Addresses
 * @{
 */
#define BMI088_AD_GYR_CHIP_ID               0x00U
#define BMI088_AD_GYR_RATE_X_LSB            0x02U            
#define BMI088_AD_GYR_RATE_X_MSB            0x03U            
#define BMI088_AD_GYR_RATE_Y_LSB            0x04U            
#define BMI088_AD_GYR_RATE_Y_MSB            0x05U            
#define BMI088_AD_GYR_RATE_Z_LSB            0x06U  
#define BMI088_AD_GYR_RATE_Z_MSB            0x07U         
#define BMI088_AD_GYR_INT_STAT_1            0x0AU  
#define BMI088_AD_GYR_FIFO_STATUS           0x0EU             
#define BMI088_AD_GYR_RANGE                 0x0FU      
#define BMI088_AD_GYR_BANDWIDTH             0x10U           
#define BMI088_AD_GYR_LPM1                  0x11U      
#define BMI088_AD_GYR_SOFTRESET             0x14U           
#define BMI088_AD_GYR_INT_CTRL              0x15U          
#define BMI088_AD_GYR_INT3_INT4_IO_CONFIG   0x16U                     
#define BMI088_AD_GYR_INT3_INT4_IO_MAP      0x18U                  
#define BMI088_AD_GYR_FIFO_WM_EN            0x1EU            
#define BMI088_AD_GYR_FIFO_EXT_INT_S        0x34U                
#define BMI088_AD_GYR_SELF_TEST             0x3CU           
#define BMI088_AD_GYR_CONFIG_0              0x3DU          
#define BMI088_AD_GYR_CONFIG_1              0x3EU        
#define BMI088_AD_GYR_FIFO_DATA             0x3FU           
/** @} */

/**
 * @name    BMI088 Gyroscope Chip ID Register 
 * @{
 */
#define BMI088_GYR_CHIP_ID_Pos              (0U)
#define BMI088_GYR_CHIP_ID_Msk              (0xFF << BMI088_GYR_CHIP_ID_Pos)                
#define BMI088_GYR_CHIP_ID                  BMI088_GYR_CHIP_ID_Msk
/**@} */

/**
 * @name    BMI088 Gyroscope Rate X LSB Register 
 * @{
 */
#define BMI088_GYR_RATE_X_LSB_Pos           (0U)
#define BMI088_GYR_RATE_X_LSB_Msk           (0xFF << BMI088_GYR_RATE_X_LSB_Pos)
#define BMI088_GYR_RATE_X_LSB               BMI088_GYR_RATE_X_LSB_Msk 
/**@} */

/**
 * @name    BMI088 Gyroscope Rate X MSB Register 
 * @{
 */

#define BMI088_GYR_RATE_X_MSB_Pos           (0U)
#define BMI088_GYR_RATE_X_MSB_Msk           (0xFF << BMI088_GYR_RATE_X_MSB_Pos) 
#define BMI088_GYR_RATE_X_MSB               BMI088_GYR_X_MSB_Msk
/**@} */

/**
 * @name    BMI088 Gyroscope Rate y LSB Register 
 * @{
 */

#define BMI088_GYR_RATE_Y_LSB_Pos           (0U)
#define BMI088_GYR_RATE_Y_LSB_Msk           (0xFF << BMI088_GYR_RATE_Y_LSB_Pos)
#define BMI088_GYR_RATE_Y_LSB               BMI088_GYR_Y_LSB_Msk
/**@} */

/**
 * @name    BMI088 Gyroscope Rate Y MSB Register 
 * @{
 */

#define BMI088_GYR_RATE_Y_MSB_Pos           (0U)
#define BMI088_GYR_RATE_Y_MSB_Msk           (0xFF << BMI088_GYR_RATE_Y_MSB_Pos)
#define BMI088_GYR_RATE_Y_MSB               BMI088_GYR_Y_MSB_Msk
/**@} */

/**
 * @name    BMI088 Gyroscope Rate Z LSB Register 
 * @{
 */

#define BMI088_GYR_RATE_Z_LSB_Pos           (0U)
#define BMI088_GYR_RATE_Z_LSB_Msk           (0xFF << BMI088_GYR_RATE_Z_LSB_Pos)
#define BMI088_GYR_RATE_Z_LSB               BMI088_GYR_Z_LSB_Msk
/**@} */

/**
 * @name    BMI088 Gyroscope Rate Z MSB Register 
 * @{
 */

#define BMI088_GYR_RATE_Z_MSB_Pos           (0U)
#define BMI088_GYR_RATE_Z_MSB_Msk           (0xFF << BMI088_GYR_RATE_Z_MSB_Pos)
#define BMI088_GYR_RATE_Z_MSB               BMI088_GYR_Z_MSB_Msk
/**@} */

/**
 * @name    BMI088 Gyroscope Int Stat 1 Register 
 * @{
 */
#define BMI088_GYR_INT_STAT1_FIFO_INT_Pos   (4U)   
#define BMI088_GYR_INT_STAT1_FIFO_INT_Msk   (0x1U << BMI088_GYR_INT_STAT1_FIFIO_INT_Pos)
#define BMI088_GYR_INT_STAT1_FIFO_INT       BMI088_GYR_INT_STAT1_FIFO_INT_Msk
#define BMI088_GYR_INT_STAT1_DRDY_Pos       (7U)   
#define BMI088_GYR_INT_STAT1_DRDY_Msk       (0x1U << BMI088_GYR_INT_STAT1_DRDY_Pos)
#define BMI088_GYR_INT_STAT1_DRDY           BMI088_GYR_INT_STAT1_DRDY_Msk
/**@} */

/**
 * @name    BMI088 Gyroscope FIFO Status Register 
 * @{
 */
#define BMI088_GYR_FIFO_STATUS_OVERRUN_Pos  (7U)
#define BMI088_GYR_FIFO_STATUS_OVERRUN_Msk  (0x1U << BMI088_GYR_FIFO_STATUS_OVERRUN_Pos)
#define BMI088_GYR_FIFO_STATUS_OVERRUN      BMI088_GYR_FIFO_STATUS_OVERRUN_Ms
#define BMI088_GYR_FIFO_STATUS_FRAMECNT_Pos (0U)
#define BMI088_GYR_FIFO_STATUS_FRAMECNT_Msk (0x7FU << BMI088_GYR_FIFO_STATUS_OVERRUN_Pos)
#define BMI088_GYR_FIFO_STATUS_FRAMECNT     BMI088_GYR_FIFO_STATUS_OVERRUN_Mskk
/**@} */

/**
 * @name    BMI088 Gyroscope Range Register 
 * @{
 */
#define BMI088_GYR_RANGE_Pos                (0U) 
#define BMI088_GYR_RANGE_Msk                (0xFFU << BMI088_GYR_RANGE_Pos)
#define BMI088_GYR_RANGE                    BMI088_GYR_RANGE_Msk
#define BMI088_GYR_RANGE_2K                 (0x00U BMI088_GYR_RANGE_Pos)
#define BMI088_GYR_RANGE_1K                 (0x01U BMI088_GYR_RANGE_Pos)
#define BMI088_GYR_RANGE_500                (0x02U BMI088_GYR_RANGE_Pos)
#define BMI088_GYR_RANGE_250                (0x03U BMI088_GYR_RANGE_Pos)
#define BMI088_GYR_RANGE_125                (0x04U BMI088_GYR_RANGE_Pos)
/**@} */

/**
 * @name    BMI088 Gyroscope Bandwidth Register 
 * @{
 */
#define BMI088_GYR_BANDWIDTH_Pos            (0U)  
#define BMI088_GYR_BANDWIDTH_Msk            (0xFFU << BMI088_GYR_BANDWIDTH_Pos) 
#define BMI088_GYR_BANDWIDTH                BMI088_GYR_BANDWIDTH_Msk  
#define BMI088_GYR_BANDWIDTH_2KHZ_532HZ     (0x00U << BMI088_GYR_BANDWIDTH_Pos)
#define BMI088_GYR_BANDWIDTH_2KHZ_230HZ     (0x01U << BMI088_GYR_BANDWIDTH_Pos) 
#define BMI088_GYR_BANDWIDTH_1KHZ_116HZ     (0x02U << BMI088_GYR_BANDWIDTH_Pos)
#define BMI088_GYR_BANDWIDTH_400HZ_47HZ     (0x03U << BMI088_GYR_BANDWIDTH_Pos)
#define BMI088_GYR_BANDWIDTH_200HZ_23HZ     (0x04U << BMI088_GYR_BANDWIDTH_Pos)
#define BMI088_GYR_BANDWIDTH_100HZ_12HZ     (0x05U << BMI088_GYR_BANDWIDTH_Pos) 
#define BMI088_GYR_BANDWIDTH_200HZ_64HZ     (0x06U << BMI088_GYR_BANDWIDTH_Pos) 
#define BMI088_GYR_BANDWIDTH_100HZ_32HZ     (0x07U << BMI088_GYR_BANDWIDTH_Pos)
/**@} */

/**
 * @name    BMI088 Gyroscope LPM1 Register 
 * @{
 */
#define BMI088_GYR_LPM1_Pos                 (0U)   
#define BMI088_GYR_LPM1_Msk                 (0xFFU << BMI088_GYR_LPM1_Pos)
#define BMI088_GYR_LPM1                     BMI088_GYR_LPM1_Msk
#define BMI088_GYR_LPM1_PM_NORMAL           (0x00U << BMI088_GYR_LPM1_Pos)
#define BMI088_GYR_LPM1_PM_SUSPEND          (0x80U << BMI088_GYR_LPM1_Pos)
#define BMI088_GYR_LPM1_PM_DEEP_SUSPEND     (0x20U << BMI088_GYR_LPM1_Pos)
/**@} */

/**
 * @name    BMI088 Gyroscope Soft Reset Register 
 * @{
 */
#define BMI088_GYR_SOFT_RESET_Pos           (0U)
#define BMI088_GYR_SOFT_RESET_Msk           (0xFFU << BMI088_GYR_SOFT_RESET_Pos)
#define BMI088_GYR_SOFT_RESET               BMI088_GYR_SOFT_RESET_Msk
#define BMI088_GYR_SOFT_RESET_CMD           (0xB6 << BMI088_GYR_SOFT_RESET_Pos)  
/**@} */

/**
 * @name    BMI088 Gyroscope Int Control Register 
 * @{
 */
#define BMI088_GYR_FIFO_INT_EN_Pos          (6U)
#define BMI088_GYR_FIFO_INT_EN_Msk          (0x1U << BMI088_GYR_FIFO_INT_EN_Pos)
#define BMI088_GYR_FIFO_INT_EN              BMI088_GYR_FIFO_INT_EN_Msk
#define BMI088_GYR_NEW_DATA_INT_Pos         (7U)
#define BMI088_GYR_NEW_DATA_INT_Msk         (0x1U << BMI088_GYR_NEW_DATA_INT_Pos)
#define BMI088_GYR_NEW_DATA_INT             (0x1U << BMI088_GYR_NEW_DATA_INT_Pos)
/**@} */

/**
 * @name    BMI088 Gyroscope Int3 Int4 IO Configure Register 
 * @{
 */
#define BMI088_GYR_INT3_LVL_Pos             (0U)
#define BMI088_GYR_INT3_LVL_Msk             (0x1U << BMI088_GYR_INT3_LVL_Pos)
#define BMI088_GYR_INT3_LVL                 BMI088_GYR_INT3_LVL_Msk
#define BMI088_GYR_INT3_LVL_L               (0x0U << BMI088_GYR_INT3_LVL_Pos)
#define BMI088_GYR_INT3_LVL_H               (0x1U << BMI088_GYR_INT3_LVL_Pos)
#define BMI088_GYR_INT3_OD_Pos              (1U)
#define BMI088_GYR_INT3_OD_Msk              (0x1U << BMI088_GYR_INT3_OD_Pos)
#define BMI088_GYR_INT3_LVL                 BMI088_GYR_INT3_OD_Msk
#define BMI088_GYR_INT3_OD_OPEN_DRAIN       (0x1U << BMI088_GYR_INT3_OD_Pos)  
#define BMI088_GYR_INT3_OD_PUSH_PULL        (0x0U << BMI088_GYR_INT3_OD_Pos) 
#define BMI088_GYR_INT4_LVL_Pos             (2U)
#define BMI088_GYR_INT4_LVL_Msk             (0x1U << BMI088_GYR_INT4_LVL_Pos)
#define BMI088_GYR_INT4_LVL                 BMI088_GYR_INT4_LVL_Msk
#define BMI088_GYR_INT4_LVL_L               (0x0U << BMI088_GYR_INT4_LVL_Pos)
#define BMI088_GYR_INT4_LVL_H               (0x1U << BMI088_GYR_INT4_LVL_Pos)
#define BMI088_GYR_INT4_OD_Pos              (3U)
#define BMI088_GYR_INT4_OD_Msk              (0x1U << BMI088_GYR_INT4_OD_Pos)
#define BMI088_GYR_INT4_OD                  BMI088_GYR_INT4_OD_Msk
#define BMI088_GYR_INT4_OD_OPEN_DRAIN       (0x1U << BMI088_GYR_INT4_OD_Pos)
#define BMI088_GYR_INT4_OD_PUSH_PULL        (0x0U << BMI088_GYR_INT4_OD_Pos)
/**@} */

/**
 * @name    BMI088 Gyroscope Int3 Int4 IO Map  Register 
 * @{
 */
#define BMI088_GYR_INT3_DRDY_Pos            (0U)
#define BMI088_GYR_INT3_DRDY_Msk            (0x1U << BMI088_GYR_INT3_DRDY_Pos)
#define BMI088_GYR_INT3_DRDY                BMI088_GYR_INT3_DRDY_Msk
#define BMI088_GYR_INT3_DRDY_RST            (0x0U << BMI088_GYR_INT3_DRDY_Pos)
#define BMI088_GYR_INT3_FIFO_Pos            (2U)
#define BMI088_GYR_INT3_FIFO_Msk            (0x1U << BMI088_GYR_INT3_FIFO_Pos)
#define BMI088_GYR_INT3_FIFO                BMI088_GYR_INT3_FIFO
#define BMI088_GYR_INT3_FIFO_RST            (0x0U <<  BMI088_GYR_INT3_FIFO_Pos)
#define BMI088_GYR_INT4_FIFO_Pos            (5U)
#define BMI088_GYR_INT4_FIFO_Msk            (0x1U << BMI088_GYR_INT4_FIFO_Pos)
#define BMI088_GYR_INT4_FIFO                BMI088_GYR_INT4_FIFO_Msk
#define BMI088_GYR_INT4_FIFO_RST            (0x0U << BMI088_GYR_INT4_FIFO_Pos)
#define BMI088_GYR_INT4_DRDY_Pos            (7U)
#define BMI088_GYR_INT4_DRDY_Msk            (0x1U << BMI088_GYR_INT4_DRDY_Pos)  
#define BMI088_GYR_INT4_DRDY                BMI088_GYR_INT4_DRDY_Msk
#define BMI088_GYR_INT4_DRDY_RST            (0x0U << BMI088_GYR_INT$_DRDY_Pos)
/**@} */

/**
 * @name    BMI088 Gyroscope FIFO Watermark Enable  Register 
 * @{
 */
#define BMI088_GYR_WM_EN_Pos                (0U)
#define BMI088_GYR_WM_WN_Msk                (0xFFU << BMI088_GYR_WM_EN_Pos)
#define BMI088_GYR_WM_EN                    BMI088_GYR_WM_EN_Msk 
#define BMI088_GYR_WM_INT_DISABLE           (0x08U << BMI088_GYR_WM_EN_Pos)
#define BMI088_GYR_WM_INT_ENABLE            (0x88U << BMI088_GYR_WM_EN_Pos)
#define BMI088_GYR_WM_RST                   (0x08U << BMI088_GYR_WM_EN_Pos)
/**@} */

/**
 * @name    BMI088 Gyroscope External Synchronization  Register 
 * @{
 */
#define BMI088_GYR_EXT_FIFO_S_SELECT_Pos    (4U)
#define BMI088_GYR_EXT_FIFO_S_SELECT_Msk    (0x1U << BMI088_GYR_EXT_INT_S_Pos)
#define BMI088_GYR_EXT_FIFO_S_SELECT        BMI088_GYR_EXT_INT_S_Msk
#define BMI088_GYR_EXT_FIFO_S_SELECT_INT4   (0x1U << BMI088_GYR_EXT_INT_S_Pos)
#define BMI088_GYR_EXT_FIFO_S_SELECT_INT3   (0x0U << BMI088_GYR_EXT_INT_S_Pos)
#define BMI088_GYR_EXT_FIFO_S_EN_Pos        (0x5U)
#define BMI088_GYR_EXT_FIFO_S_EN_Msk        (0x1U << BMI088_GYR_EXT_FIFO_S_EN_Pos)
#define BMI088_GYR_EXT_FIFO_S_EN            BMI088_GYR_EXT_FIFO_S_EN_Msk
/**@} */

/**
 * @name    BMI088 Gyroscope Self Test Register 
 * @{
 */
#define BMI088_GYR_SELF_TEST_Pos            (0U)  
#define BMI088_GYR_SELF_TEST_Msk            (0x17U << BMI088_GYR_SELF_TEST_Pos)
#define BMI088_GYR_SELF_TEST                BMI088_GYR_SELF_TEST_Msk
#define BMI088_GYR_SELF_TEST_TRIG_BIST      (0x1U << BMI088_GYR_SELF_TEST_Pos)
#define BMI088_GYR_SELF_TEST_BIST_RDY       (0x2U << BMI088_GYR_SELF_TEST_Pos)
#define BMI088_GYR_SELF_TEST_BIST_FAIL      (0x4U << BMI088_GYR_SELF_TEST_Pos)
#define BMI088_GYR_SELF_TEST_RATE_OK        (0x10 << BMI088_GYR_SELF_TEST_Pos)
/**@} */

/**
 * @name    BMI088 Gyroscope FIFO Config 0 Register 
 * @{
 */
#define BMI088_GYR_FIFO_CONFIG_0_Pos        (0U) 
#define BMI088_GYR_FIFO_CONFIG_0_Msk        (0x7FU << BMI088_GYR_FIFO_CONFIG_0_Pos)
#define BMI088_GYR_FIFO_CONFIG_0            BMI088_GYR_FIFO_CONFIG_0_Msk
#define BMI088_GYR_FIFO_CONFIG_0_RST        (0x00  <<  BMI088_GYR_FIFO_CONFIG_0_Pos)
/**@} */

/**
 * @name    BMI088 Gyroscope FIFO Config 1 Register 
 * @{
 */
#define BMI088_GYR_FIFO_CONFIG_1_Pos        (0U)
#define BMI088_GYR_FIFO_CONFIG_1_Msk        (0xFFU << BMI088_GYR_FIFO_CONFIG_1_Pos)
#define BMI088_GYR_FIFO_CONFIG_1            BMI088_GYR_FIFO_CONFIG_1_Msk
#define BMI088_GYR_FIFO_CONFIG_1_STREAM     (0x80U << BMI088_GYR_FIFO_CONFIG_1_Pos)
#define BMI088_GYR_FIFO_CONFIG_1_FIFO       (0x40U << BMI088_GYR_FIFO_CONFIG_1_Pos)
/**@} */

/**
 * @name    BMI088 Gyroscope FIFO Data Register 
 * @{
 */
#define BMI088_GYR_FIFO_DATA_Pos            (0U)
#define BMI088_GYR_FIFO_DATA_Msk            (0xFFU << BMI088_GYR_FIFO_DATA_Pos)
#define BMI088_GYR_FIFO_DATA                BMI088_GYR_FIFO_DATA_Msk
/**@} */



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
