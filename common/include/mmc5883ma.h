/**
 * @file    mmc5883ma.h
 * @brief   MMC5883MA Power Monitor.
 *
 * @addtogroup MMC5883MA
 * @ingroup ORESAT
 * @{
 */
#ifndef _MMC5883MA_H_
#define _MMC5883MA_H_

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    Version Identification
 * @{
 */


#define MMC5883MA_I2C_ADDRESS_READ                  (0x30)
#define MMC5883MA_I2C_ADDRESS_WRITE                 (0x30)

#define MMC5883MA_EXPECTED_PRODUCT_CODE              0x0C

//#define HMC5883L_I2C_ADDRESS_READ                   0x3D
//#define HMC5883L_I2C_ADDRESSW_WRITE                 0x3C
//#define HMC5883L_ID_REGISTER_A                      0x0A


/**
 * @brief   MMC5883MA Driver version string.
 */
//#define MMC5883MA_VERSION                      "1.0.0"

/**
 * @brief   MMC5883MA Driver version major number.
 */
//#define MMC5883MA_MAJOR                        1

/**
 * @brief   MMC5883MA Driver version minor number.
 */
//#define MMC5883MA_MINOR                        0

/**
 * @brief   MMC5883MA Driver version patch number.
 */
//#define MMC5883MA_PATCH                        0
/** @} */

/**
 * @name    MMC5883MA Register Addresses
 * @{
 */
#define MMC5883MA_AD_PRDCT_ID_1                0x2F
#define MMC5883MA_AD_Z_THRSHLD                 0x0D 
#define MMC5883MA_AD_Y_THRSHLD                 0x0C
#define MMC5883MA_AD_X_THRSHLD                 0x0B
#define MMC5883MA_AD_INTRNLCTRL2               0x0A
#define MMC5883MA_AD_INTRNLCTRL1               0x09
#define MMC5883MA_AD_INTRNLCTRL0               0x08
#define MMC5883MA_AD_STATUS                    0x07
#define MMC5883MA_AD_TEMPERATURE_OUT           0x06
#define MMC5883MA_AD_ZOUT_HIGH                 0x05
#define MMC5883MA_AD_ZOUT_LOW                  0x04
#define MMC5883MA_AD_YOUT_HIGH                 0x03
#define MMC5883MA_AD_YOUT_LOW                  0x02
#define MMC5883MA_AD_XOUT_HIGH                 0x01
#define MMC5883MA_AD_XOUT_LOW                  0x00
/** @} */

/**
 * @name    MMC5883MA Product Id_1 register fields
 * @{
 */
#define MMC5883MA_PRDCT_ID_1_Pos               (0U)
#define MMC5883MA_PRDCT_ID_1_Msk               (0x7U << MMC5883MA_PRDCT_ID_1_Pos)
#define MMC5883MA_PRDCT_ID                     MMC5883MA_PRDCT_ID_1_Msk
#define MMC5883MA_PRDCT_ID_RST                 (0x0CU << MMC5883MA_PRDCT_ID_1_Pos)
/** @} */

/**
 * @name    MMC5883MA Z Threshold register fields
 * @{
 */
#define MMC5883MA_Z_THRSHLD_Z_MAG_TH_Pos       (0U)
#define MMC5883MA_Z_THRSHLD_Z_MAG_TH_Msk       (0xFFU << MMC5883MA_Z_THRSHLD_Z_MAG_TH_Pos)
#define MMC5883MA_Z_THRSHLD_Z_MAG_TH           MMC5883MA_Z_THRSHLD_Z_MAG_TH_Msk
#define MMC5883MA_Z_THRSHLD_Z_MAG_TH_RST       (0x00U << MMC5883MA_Z_THRSHLD_Z_MAG_TH_Pos)
/** @} */

/**
 * @name    MMC5883MA Y Threshold register fields
 * @{
 */
#define MMC5883MA_Y_THRSHLD_Y_MAG_TH_Pos       (0U)
#define MMC5883MA_Y_THRSHLD_Y_MAG_TH_Msk       (0xFFU << MMC5883MA_Y_THRSHLD_Y_MAG_TH_Pos)
#define MMC5883MA_Y_THRSHLD_Y_MAG_TH           MMC5883MA_Y_THRSHLD_Y_MAG_TH_Msk
#define MMC5883MA_Y_THRSHLD_Y_MAG_TH_RST       (0x00U << MMC5883MA_Y_THRSHLD_Y_MAG_TH_Pos)
/** @} */

/**
 * @name    MMC5883MA X Threshold register fields
 * @{
 */
//#define MMC5883MA_X_THRSHLD_X_MAG_TH_Pos       (0U)
#define MMC5883MA_X_THRSHLD_X_MAG_TH_Msk       (0xFFU << MMC5883MA_X_THRSHLD_X_MAG_TH_Pos)
#define MMC5883MA_X_THRSHLD_X_MAG_TH           MMC5883MA_X_THRSHLD_X_MAG_TH_Msk
#define MMC5883MA_X_THRSHLD_X_MAG_TH_Pos       (0x00U << MMC5883MA_X_THRSHLD_X_MAG_TH_Pos)
/** @} */

/**
 * @name    MMC5883MA Internal Control_2 register fields
 * @{
 */
#define MMC5883MA_INTRNLCTRL2_CM_FREQ_2200_mHz (0x03)
#define MMC5883MA_INTRNLCTRL2_CM_FREQ_1_Hz     (0x04)

#define MMC5883MA_INTRNLCTRL2_CM_FREQ_RST      (0x1U << MMC5883MA_INTRNL_CTRL_2_CM_FREQ_Pos)
#define MMC5883MA_INTRNLCTRL2_MDT_Pos          (5U)
#define MMC5883MA_INTRNLCTRL2_MDT_Msk          (0x1U << MMC5883MA_INTRNLCTRL2_MDT_Pos)
#define MMC5883MA_INTRNLCTRL2_MDT              MMC5883MA_INTRNLCTRL2_MDT_Msk
#define MMC5883MA_INTRNLCTRL2_MDT_EN           (0x1U << MMC5883MA_INTRNLCTRL2_MDT_Pos)
#define MMC5883MA_INTRNLCTRL2_MDT_RST          (0x0U << MMC5883MA_INTRNLCTRL2_MDT_Pos)
#define MMC5883MA_INTRNLCTRL2_MEAS_DONE_Pos    (6U)
#define MMC5883MA_INTRNLCTRL2_MEAS_DONE_Msk    (0x1U << MMC5883MA_INTRNLCTRL2_MEAS_DONE_Pos)
#define MMC5883MA_INTRNLCTRL2_MEAS_DONE        MMC5883MA_INTRNLCTRL2_MEAS_DONE_Msk
#define MMC5883MA_INTRNLCTRL2_MEAS_DONE_EN     (0x1U << MMC5883MA_INTRNLCTRL2_MEAS_DONE_Pos)
#define MMC5883MA_INTRNLCTRL2_MEAS_DONE_RST    (0x0U << MMC5883MA_INTRNLCTRL2_MEAS_DONE_Pos)
/** @} */

/**
 * @name    MMC5883MA Internal Control_1 register fields
 * @{
 */
#define MMC5883MA_INTRNLCTRL1_BW_Pos           (0U)
#define MMC5883MA_INTRNLCTRL1_BW_Msk           (0x3U << MMC5883MA_INTRNLCTRL1_BW_Pos)
#define MMC5883MA_INTRNLCTRL1_BW               MMC5883MA_INTRNLCTRL1_BW_Msk 
#define MMC5883MA_INTRNLCTRL1_BW_ODR_100Hz     (0x0U << MMC5883MA_INTRNLCTRL1_BW_Pos)
#define MMC5883MA_INTRNLCTRL1_BW_ODR_200Hz     (0x1U << MMC5883MA_INTRNLCTRL1_BW_Pos)
#define MMC5883MA_INTRNLCTRL1_BW_ODR_400Hz     (0x2U << MMC5883MA_INTRNLCTRL1_BW_Pos)
#define MMC5883MA_INTRNLCTRL1_BW_ODR_600Hz     (0x3U << MMC5883MA_INTRNLCTRL1_BW_Pos)
#define MMC5883MA_INTRNLCTRL1_SW_RST_Pos       (7U)  
#define MMC5883MA_INTRNLCTRL1_SW_RST_CMD       (0x1U << MMC5883MA_INTRNLCTRL1_SW_RST_Pos)
/** @} */

/**
 * @name    MMC5883MA Internal Control_0 register fields
 * @{
 */
#define MMC5883MA_INTRNLCTRL0_TM_M_Pos         (0U)
#define MMC5883MA_INTRNLCTRL0_TM_M_Msk         (0x1U << MMC5883MA_INTRNLCTRL0_TM_M_Pos)
#define MMC5883MA_INTRNLCTRL0_TM_M             MMC5883MA_INTRNLCTRL0_TM_M_Msk
#define MMC5883MA_INTRNLCTRL0_TM_M_INIT        (0x1U << MMC5883MA_INTRNLCTRL0_TM_M_Pos)
#define MMC5883MA_INTRNLCTRL0_TM_T_Pos         (1U)
#define MMC5883MA_INTRNLCTRL0_TM_T_Msk         (0x1U << MMC5883MA_INTRNLCTRL0_TM_T_Pos)
#define MMC5883MA_INTRNLCTRL0_TM_T             MMC5883MA_INTRNLCTRL0_TM_T_Msk
#define MMC5883MA_INTRNLCTRL0_TM_T_INIT        (0x1U << MMC5883MA_INTRNLCTRL0_TM_T_Pos)
#define MMC5883MA_INTRNLCTRL0_STRT_MDT_Pos     (2U)
#define MMC5883MA_INTRNLCTRL0_STRT_MDT_Msk     (0x1U << MMC5883MA_INTRNLCTRL0_STRT_MDT_Pos)
#define MMC5883MA_INTRNLCTRL0_STRT_MDT         MMC5883MA_INTRNLCTRL0_STRT_MDT_Msk 
#define MMC5883MA_INTRNLCTRL0_STRT_MDT_CMD     (0x1U << MMC5883MA_INTRNLCTRL0_STRT_MDT_Pos)
#define MMC5883MA_INTRNLCTRL0_SET_Pos          (3U)
#define MMC5883MA_INTRNLCTRL0_SET_Msk          (0x1U << MMC5883MA_INTRNLCTRL0_SET_Pos) 
#define MMC5883MA_INTRNLCTRL0_SET              MMC5883MA_INTRNLCTRL0_SET_Msk     
#define MMC5883MA_INTRNLCTRL0_SET_CMD          (0x1U << MMC5883MA_INTRNLCTRL0_SET_Pos) 
#define MMC5883MA_INTRNLCTRL0_RST_Pos          (4U) 
#define MMC5883MA_INTRNLCTRL0_RST_Msk          (0x1U << MMC5883MA_INTRNLCTRL0_RST_Pos) 
#define MMC5883MA_INTRNLCTRL0_RST              MMC5883MA_INTRNLCTRL0_RST_Msk     
#define MMC5883MA_INTRNLCTRL0_RST_CMD          (0x1U << MMC5883MA_INTRNLCTRL0_RST_Pos)   
#define MMC5883MA_INTRNLCTRL0_OTP_Pos          (6U) 
#define MMC5883MA_INTRNLCTRL0_OTP_Msk          (0x1U << MMC5883MA_INTRNLCTRL0_OTP_Pos) 
#define MMC5883MA_INTRNLCTRL0_OTP              MMC5883MA_INTRNLCTRL0_OTP_Msk     
#define MMC5883MA_INTRNLCTRL0_OTP_READ         (0x1U << MMC5883MA_INTRNLCTRL0_OTP_Pos) 
#define MMC5883MA_INTRNLCTRL0_TST_PIN_Pos      (7U)
#define MMC5883MA_INTRNLCTRL0_TST_PIN_Msk      (0x1U << MMC5883MA_INTRNLCTRL0_TST_PIN_Pos)
#define MMC5883MA_INTRNLCTRL0_TST_PIN          MMC5883MA_INTRNLCTRL0_TST_PIN_Msk 
#define MMC5883MA_INTRNLCTRL0_TST_PIN_SLCT     (0x1U << MMC5883MA_INTRNLCTRL0_TST_PIN_Pos)
/** @} */

/**
 * @name    MMC5883MA Status register fields
 * @{
 */
#define MMC5883MA_STATUS_MEAS_M_DONE_Pos       (0U)
#define MMC5883MA_STATUS_MEAS_M_DONE_Msk       (0x1U << MMC5883MA_STATUS_MEAS_M_DONE_Pos)
#define MMC5883MA_STATUS_MEAS_M_DONE           MMC5883MA_STATUS_MEAS_M_DONE_Msk   
#define MMC5883MA_STATUS_MEAS_M_DONE_CLR       (0x1U << MMC5883MA_STATUS_MEAS_M_DONE_Pos)       
#define MMC5883MA_STATUS_MEAS_T_DONE_Pos       (1U)       
#define MMC5883MA_STATUS_MEAS_T_DONE_Msk       (0x1U << MMC5883MA_STATUS_MEAS_T_DONE_Pos)       
#define MMC5883MA_STATUS_MEAS_T_DONE           MMC5883MA_STATUS_MEAS_T_DONE_Msk   
#define MMC5883MA_STATUS_MEAS_T_DONE_CLR       (0x1U << MMC5883MA_STATUS_MEAS_T_DONE_Pos)       
#define MMC5883MA_STATUS_MD_Pos                (2U)     
#define MMC5883MA_STATUS_MD_Msk                (0x1U << MMC5883MA_STATUS_MD_Pos)     
#define MMC5883MA_STATUS_MD                    MMC5883MA_STATUS_MD_Msk        
#define MMC5883MA_STATUS_MD_CLR                (0x1U << MMC5883MA_STATUS_MD_Pos)            
#define MMC5883MA_STATUS_PUMP_ON_Pos           (3U)   
#define MMC5883MA_STATUS_PUMP_ON_Msk           (0x1U << MMC5883MA_STATUS_PUMP_ON_Pos)   
#define MMC5883MA_STATUS_PUMP_ON               MMC5883MA_STATUS_PUMP_ON_Msk   
#define MMC5883MA_STATUS_OTP_RD_DONE_Pos       (4U)       
#define MMC5883MA_STATUS_OTP_RD_DONE_Msk       (0x1U << MMC5883MA_STATUS_OTP_RD_DONE_Pos)       
#define MMC5883MA_STATUS_OTP_RD_DONE           MMC5883MA_STATUS_OTP_RD_DONE_Msk               
/** @} */

/**
 * @name    MMC5883MA Temperature Out register fields
 * @{
 */
#define MMC5883MA_TEMPERATURE_OUT_Pos          (0U)
#define MMC5883MA_TEMPERATURE_OUT_Msk          (0xFFU << MMC5883MA_TEMPERATURE_Pos)
#define MMC5883MA_TEMPERATURE_OUT              MMC5883MA_TEMPERATURE_Msk
/** @} */

/**
 * @name    MMC5883MA Zout High register fields
 * @{
 */
#define MMC5883MA_ZOUT_H_Pos                   (0U)
#define MMC5883MA_ZOUT_H_Msk                   (0xFFU << MMC5883MA_ZOUT_H_Pos)
#define MMC5883MA_ZOUT_H                       MMC5883MA_ZOUT_H_Msk               
/** @} */

/**
 * @name    MMC5883MA Zout Low register fields
 * @{
 */
#define MMC5883MA_ZOUT_L_Pos                   (0U)
#define MMC5883MA_ZOUT_L_Msk                   (0xFFU << MMC5883MA_ZOUT_L_Pos)
#define MMC5883MA_ZOUT_L                       MMC5883MA_ZOUT_L_Msk               
/** @} */

/**
 * @name    MMC5883MA Yout High register fields
 * @{
 */
#define MMC5883MA_YOUT_H_Pos                   (0U)              
#define MMC5883MA_YOUT_H_Msk                   (0xFFU << MMC5883MA_YOUT_H_Pos)
//#define MMC5883MA_YOUT_H_Msk                   MMC5883MA_YOUT_H_Msk
/** @} */

/**
 * @name    MMC5883MA Yout Low register fields
 * @{
 */
#define MMC5883MA_YOUT_L_Pos                   (0U)
#define MMC5883MA_YOUT_L_Msk                   (0xFFU << MMC5883MA_YOUT_L_Pos)
#define MMC5883MA_YOUT_L                       MMC5883MA_YOUT_L_Msk               
/** @} */

/**
 * @name    MMC5883MA Xout High register fields
 * @{
 */
#define MMC5883MA_XOUT_H_Pos                   (0U)
#define MMC5883MA_XOUT_H_Msk                   (0xFFU << MMC5883MA_XOUT_H_Pos)
#define MMC5883MA_XOUT_H                       MMC5883MA_XOUT_H_Msk               
/** @} */

/**
 * @name    MMC5883MA Xout Low register fields
 * @{
 */
#define MMC5883MA_XOUT_L_Pos                   (0U)
#define MMC5883MA_XOUT_L_Msk                   (0xFFU << MMC5883MA_XOUT_L_Pos)
#define MMC5883MA_XOUT_L                       MMC5883MA_XOUT_L_Msk               
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   MMC5883MA I2C interface switch.
 * @details If set to @p TRUE the support for I2C is included.
 * @note    The default is @p TRUE.
 */
#if !defined(MMC5883MA_USE_I2C) || defined(__DOXYGEN__)
#define MMC5883MA_USE_I2C                      TRUE
#endif

/**
 * @brief   MMC5883MA shared I2C switch.
 * @details If set to @p TRUE the device acquires I2C bus ownership
 *          on each transaction.
 * @note    The default is @p FALSE. Requires I2C_USE_MUTUAL_EXCLUSION.
 */
#if !defined(MMC5883MA_SHARED_I2C) || defined(__DOXYGEN__)
#define MMC5883MA_SHARED_I2C                   FALSE
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if MMC5883MA_USE_I2C && !HAL_USE_I2C
#error "MMC5883MA_USE_I2C requires HAL_USE_I2C"
#endif

#if MMC5883MA_SHARED_I2C && !I2C_USE_MUTUAL_EXCLUSION
#error "MMC5883MA_SHARED_I2C requires I2C_USE_MUTUAL_EXCLUSION"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @name    MMC5883MA data structures and types.
 * @{
 */
/**
 * @brief Structure representing a MMC5883MA driver.
 */
typedef struct MMC5883MADriver MMC5883MADriver;

/**
 * @brief   Driver state machine possible states.
 */
typedef enum {
    MMC5883MA_UNINIT = 0,                  /**< Not initialized.                 */
    MMC5883MA_STOP = 1,                    /**< Stopped.                         */
    MMC5883MA_READY = 2,                   /**< Ready.                           */
} mmc5883ma_state_t;

/**
 * @brief   MMC5883MA configuration structure.
 */
typedef struct {
#if (MMC5883MA_USE_I2C) || defined(__DOXYGEN__)
    /**
     * @brief I2C driver associated with this MMC5883MA.
     */
    I2CDriver                   *i2cp;
    /**
     * @brief I2C configuration associated with this MMC5883MA.
     */
    const I2CConfig             *i2ccfg;
    /**
     * @brief MMC5883MA Slave Address
     */
    //i2caddr_t                   saddr;
#endif /* MMC5883MA_USE_I2C */
} MMC5883MAConfig;

/**
 * @brief   @p MMC5883MA specific methods.
 */
#define _mmc5883ma_methods_alone

/**
 * @brief   @p MMC5883MA specific methods with inherited ones.
 */
#define _mmc5883ma_methods                                                     \
    _base_object_methods

/**
 * @extends BaseObjectVMT
 *
 * @brief   @p MMC5883MA virtual methods table.
 */
struct MMC5883MAVMT {
    _mmc5883ma_methods
};

/**
 * @brief   @p MMC5883MADriver specific data.
 */
#define _mmc5883ma_data                                                        \
    _base_object_data                                                       \
    /* Driver state.*/                                                      \
    mmc5883ma_state_t              state;                                      \
    /* Current configuration data.*/                                        \
    const MMC5883MAConfig          *config;

/**
 * @brief MMC5883MA Power Monitor class.
 */
struct MMC5883MADriver {
    /** @brief Virtual Methods Table.*/
    const struct MMC5883MAVMT     *vmt;
    _mmc5883ma_data
};

/** @} */

typedef struct {
	int16_t mx;
	int16_t my;
	int16_t mz;
} mmc5883ma_data_t;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
void mmc5883maObjectInit(MMC5883MADriver *devp);
bool mmc5883maStart(MMC5883MADriver *devp, const MMC5883MAConfig *config);
void mmc5883maStop(MMC5883MADriver *devp);
bool mmc5883maReadData(MMC5883MADriver *devp, mmc5883ma_data_t *dest);
bool mmc5883maI2CReadRegister3(I2CDriver *i2cp, const uint8_t i2c_address, const uint8_t reg_number, uint8_t *dest_value);
bool mmc5883maI2CReadRegister4(I2CDriver *i2cp, const uint8_t i2c_address, const uint8_t reg_number, uint16_t *dest_value);
#ifdef __cplusplus
}
#endif

#endif /* _MMC5883MA_H_ */

/** @} */
