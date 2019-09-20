/**
 * @file    ina226.h
 * @brief   INA226 Digital to Analog Converter.
 *
 * @addtogroup INA226
 * @ingroup ORESAT
 * @{
 */
#ifndef _INA226_H_
#define _INA226_H_

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    Version Identification
 * @{
 */
/**
 * @brief   INA226 Driver version string.
 */
#define INA226_VERSION                      "1.0.0"

/**
 * @brief   INA226 Driver version major number.
 */
#define INA226_MAJOR                        1

/**
 * @brief   INA226 Driver version minor number.
 */
#define INA226_MINOR                        0

/**
 * @brief   INA226 Driver version patch number.
 */
#define INA226_PATCH                        0
/** @} */

/**
 * @name    INA226 Register Addresses
 * @{
 */
#define INA226_AD_CONFIG                    0x00U
#define INA226_AD_SHUNT                     0x01U
#define INA226_AD_VBUS                      0x02U
#define INA226_AD_POWER                     0x03U
#define INA226_AD_CURRENT                   0x04U
#define INA226_AD_CAL                       0x05U
#define INA226_AD_ME                        0x06U
#define INA226_AD_LIM                       0x07U
#define INA226_AD_MFG_ID                    0xFEU
#define INA226_AD_DIE_ID                    0xFFU
/** @} */

/**
 * @name    INA226 Configuration register fields
 * @{
 */
#define INA226_CONFIG_MODE_Pos              (0U)
#define INA226_CONFIG_MODE_Msk              (0x7U << INA226_CONFIG_MODE_Pos)
#define INA226_CONFIG_MODE                  INA226_CONFIG_MODE_Msk
#define INA226_CONFIG_MODE_SHDN             (0x0U << INA226_CONFIG_MODE_Pos)
#define INA226_CONFIG_MODE_SHUNT            (0x1U << INA226_CONFIG_MODE_Pos)
#define INA226_CONFIG_MODE_VBUS             (0x2U << INA226_CONFIG_MODE_Pos)
#define INA226_CONFIG_MODE_SHUNT_VBUS       (0x3U << INA226_CONFIG_MODE_Pos)
#define INA226_CONFIG_MODE_CONT             (0x4U << INA226_CONFIG_MODE_Pos)
#define INA226_CONFIG_VSHCT_Pos             (3U)
#define INA226_CONFIG_VSHCT_Msk             (0x7U << INA226_CONFIG_VSHCT_Pos)
#define INA226_CONFIG_VSHCT                 INA226_CONFIG_VSHCT_Msk
#define INA226_CONFIG_VSHCT_140US           (0x0U << INA226_CONFIG_VSHCT_Pos)
#define INA226_CONFIG_VSHCT_204US           (0x1U << INA226_CONFIG_VSHCT_Pos)
#define INA226_CONFIG_VSHCT_332US           (0x2U << INA226_CONFIG_VSHCT_Pos)
#define INA226_CONFIG_VSHCT_588US           (0x3U << INA226_CONFIG_VSHCT_Pos)
#define INA226_CONFIG_VSHCT_1100US          (0x4U << INA226_CONFIG_VSHCT_Pos)
#define INA226_CONFIG_VSHCT_2116US          (0x5U << INA226_CONFIG_VSHCT_Pos)
#define INA226_CONFIG_VSHCT_4156US          (0x6U << INA226_CONFIG_VSHCT_Pos)
#define INA226_CONFIG_VSHCT_8224US          (0x7U << INA226_CONFIG_VSHCT_Pos)
#define INA226_CONFIG_VBUSCT_Pos            (6U)
#define INA226_CONFIG_VBUSCT_Msk            (0x7U << INA226_CONFIG_VBUSCT_Pos)
#define INA226_CONFIG_VBUSCT                INA226_CONFIG_VBUSCT_Msk
#define INA226_CONFIG_VBUSCT_140US          (0x0U << INA226_CONFIG_VSHCT_Pos)
#define INA226_CONFIG_VBUSCT_204US          (0x1U << INA226_CONFIG_VSHCT_Pos)
#define INA226_CONFIG_VBUSCT_332US          (0x2U << INA226_CONFIG_VSHCT_Pos)
#define INA226_CONFIG_VBUSCT_588US          (0x3U << INA226_CONFIG_VSHCT_Pos)
#define INA226_CONFIG_VBUSCT_1100US         (0x4U << INA226_CONFIG_VSHCT_Pos)
#define INA226_CONFIG_VBUSCT_2116US         (0x5U << INA226_CONFIG_VSHCT_Pos)
#define INA226_CONFIG_VBUSCT_4156US         (0x6U << INA226_CONFIG_VSHCT_Pos)
#define INA226_CONFIG_VBUSCT_8224US         (0x7U << INA226_CONFIG_VSHCT_Pos)
#define INA226_CONFIG_AVG_Pos               (9U)
#define INA226_CONFIG_AVG_Msk               (0x7U << INA226_CONFIG_AVG_Pos)
#define INA226_CONFIG_AVG                   INA226_CONFIG_AVG_Msk
#define INA226_CONFIG_AVG_1                 (0x0U << INA226_CONFIG_AVG_Pos)
#define INA226_CONFIG_AVG_4                 (0x1U << INA226_CONFIG_AVG_Pos)
#define INA226_CONFIG_AVG_16                (0x2U << INA226_CONFIG_AVG_Pos)
#define INA226_CONFIG_AVG_64                (0x3U << INA226_CONFIG_AVG_Pos)
#define INA226_CONFIG_AVG_128               (0x4U << INA226_CONFIG_AVG_Pos)
#define INA226_CONFIG_AVG_256               (0x5U << INA226_CONFIG_AVG_Pos)
#define INA226_CONFIG_AVG_512               (0x6U << INA226_CONFIG_AVG_Pos)
#define INA226_CONFIG_AVG_1024              (0x7U << INA226_CONFIG_AVG_Pos)
#define INA226_CONFIG_RST_Pos               (15U)
#define INA226_CONFIG_RST_Msk               (0x1U << INA226_CONFIG_RST_Pos)
#define INA226_CONFIG_RST                   INA226_CONFIG_RST_Msk
/** @} */

/**
 * @name    INA226 Shunt Voltage register fields
 * @{
 */
#define INA226_SHUNT_Pos                    (0U)
#define INA226_SHUNT_Msk                    (0xFFFFU << INA226_SHUNT_Pos)
#define INA226_SHUNT                        INA226_SHUNT_Msk
/** @} */

/**
 * @name    INA226 VBUS Voltage register fields
 * @{
 */
#define INA226_VBUS_Pos                     (0U)
#define INA226_VBUS_Msk                     (0x7FFFU << INA226_VBUS_Pos)
#define INA226_VBUS                         INA226_VBUS_Msk
/** @} */

/**
 * @name    INA226 Power register fields
 * @{
 */
#define INA226_POWER_Pos                    (0U)
#define INA226_POWER_Msk                    (0xFFFFU << INA226_POWER_Pos)
#define INA226_POWER                        INA226_POWER_Msk
/** @} */

/**
 * @name    INA226 Current register fields
 * @{
 */
#define INA226_CURRENT_Pos                  (0U)
#define INA226_CURRENT_Msk                  (0xFFFFU << INA226_CURRENT_Pos)
#define INA226_CURRENT                      INA226_CURRENT_Msk
/** @} */

/**
 * @name    INA226 Calibration register fields
 * @{
 */
#define INA226_CAL_Pos                      (0U)
#define INA226_CAL_Msk                      (0x7FFFU << INA226_CAL_Pos)
#define INA226_CAL                          INA226_CAL_Msk
/** @} */

/**
 * @name    INA226 Alert Mask/Enable register fields
 * @{
 */
#define INA226_ME_LEN_Pos                   (0U)
#define INA226_ME_LEN_Msk                   (0x1U << INA226_ME_LEN_Pos)
#define INA226_ME_LEN                       INA226_ME_LEN_Msk
#define INA226_ME_APOL_Pos                  (1U)
#define INA226_ME_APOL_Msk                  (0x1U << INA226_ME_APOL_Pos)
#define INA226_ME_APOL                      INA226_ME_APOL_Msk
#define INA226_ME_OVF_Pos                   (2U)
#define INA226_ME_OVF_Msk                   (0x1U << INA226_ME_OVF_Pos)
#define INA226_ME_OVF                       INA226_ME_OVF_Msk
#define INA226_ME_CVRF_Pos                  (3U)
#define INA226_ME_CVRF_Msk                  (0x1U << INA226_ME_CVRF_Pos)
#define INA226_ME_CVRF                      INA226_ME_CVRF_Msk
#define INA226_ME_AFF_Pos                   (4U)
#define INA226_ME_AFF_Msk                   (0x1U << INA226_ME_AFF_Pos)
#define INA226_ME_AFF                       INA226_ME_AFF_Msk
#define INA226_ME_CNVR_Pos                  (10U)
#define INA226_ME_CNVR_Msk                  (0x1U << INA226_ME_CNVR_Pos)
#define INA226_ME_CNVR                      INA226_ME_CNVR_Msk
#define INA226_ME_POL_Pos                   (11U)
#define INA226_ME_POL_Msk                   (0x1U << INA226_ME_POL_Pos)
#define INA226_ME_POL                       INA226_ME_POL_Msk
#define INA226_ME_BUL_Pos                   (12U)
#define INA226_ME_BUL_Msk                   (0x1U << INA226_ME_BUL_Pos)
#define INA226_ME_BUL                       INA226_ME_BUL_Msk
#define INA226_ME_BOL_Pos                   (13U)
#define INA226_ME_BOL_Msk                   (0x1U << INA226_ME_BOL_Pos)
#define INA226_ME_BOL                       INA226_ME_BOL_Msk
#define INA226_ME_SUL_Pos                   (14U)
#define INA226_ME_SUL_Msk                   (0x1U << INA226_ME_SUL_Pos)
#define INA226_ME_SUL                       INA226_ME_SUL_Msk
#define INA226_ME_SOL_Pos                   (15U)
#define INA226_ME_SOL_Msk                   (0x1U << INA226_ME_SOL_Pos)
#define INA226_ME_SOL                       INA226_ME_SOL_Msk
/** @} */

/**
 * @name    INA226 Alert Limit register fields
 * @{
 */
#define INA226_LIM_Pos                      (0U)
#define INA226_LIM_Msk                      (0xFFFFU << INA226_LIM_Pos)
#define INA226_LIM                          INA226_LIM_Msk
/** @} */

/**
 * @name    INA226 Manufacturer ID register fields
 * @{
 */
#define INA226_MFG_ID_Pos                   (0U)
#define INA226_MFG_ID_Msk                   (0xFFFFU << INA226_MFG_ID_Pos)
#define INA226_MFG_ID                       INA226_MFG_ID_Msk
/** @} */

/**
 * @name    INA226 Die ID register fields
 * @{
 */
#define INA226_DIE_ID_RID_Pos               (0U)
#define INA226_DIE_ID_RID_Msk               (0xFU << INA226_DIE_ID_RID_Pos)
#define INA226_DIE_ID_RID                   INA226_DIE_ID_RID_Msk
#define INA226_DIE_ID_DID_Pos               (4U)
#define INA226_DIE_ID_DID_Msk               (0xFFFU << INA226_DIE_ID_DID_Pos)
#define INA226_DIE_ID_DID                   INA226_DIE_ID_DID_Msk
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   INA226 I2C interface switch.
 * @details If set to @p TRUE the support for I2C is included.
 * @note    The default is @p TRUE.
 */
#if !defined(INA226_USE_I2C) || defined(__DOXYGEN__)
#define INA226_USE_I2C                      TRUE
#endif

/**
 * @brief   INA226 shared I2C switch.
 * @details If set to @p TRUE the device acquires I2C bus ownership
 *          on each transaction.
 * @note    The default is @p FALSE. Requires I2C_USE_MUTUAL_EXCLUSION.
 */
#if !defined(INA226_SHARED_I2C) || defined(__DOXYGEN__)
#define INA226_SHARED_I2C                   FALSE
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if INA226_USE_I2C && !HAL_USE_I2C
#error "INA226_USE_I2C requires HAL_USE_I2C"
#endif

#if INA226_SHARED_I2C && !I2C_USE_MUTUAL_EXCLUSION
#error "INA226_SHARED_I2C requires I2C_USE_MUTUAL_EXCLUSION"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @name    INA226 data structures and types.
 * @{
 */
/**
 * @brief Structure representing a INA226 driver.
 */
typedef struct INA226Driver INA226Driver;

/**
 * @brief   Driver state machine possible states.
 */
typedef enum {
    INA226_UNINIT = 0,                  /**< Not initialized.                 */
    INA226_STOP = 1,                    /**< Stopped.                         */
    INA226_READY = 2,                   /**< Ready.                           */
} ina226_state_t;

/**
 * @brief   INA226 configuration structure.
 */
typedef struct {
#if (INA226_USE_I2C) || defined(__DOXYGEN__)
    /**
     * @brief I2C driver associated with this INA226.
     */
    I2CDriver                   *i2cp;
    /**
     * @brief I2C configuration associated with this INA226.
     */
    const I2CConfig             *i2ccfg;
    /**
     * @brief INA226 Slave Address
     */
    i2caddr_t                   saddr;
#endif /* INA226_USE_I2C */
    /**
     * @brief INA226 configuration reg value
     */
    uint16_t                    cfg;
    /**
     * @brief INA226 calibration reg value, sets Current_LSB
     */
    uint16_t                    cal;
} INA226Config;

/**
 * @brief   @p INA226 specific methods.
 */
#define _ina226_methods_alone

/**
 * @brief   @p INA226 specific methods with inherited ones.
 */
#define _ina226_methods                                                     \
    _base_object_methods

/**
 * @extends BaseObjectVMT
 *
 * @brief   @p INA226 virtual methods table.
 */
struct INA226VMT {
    _ina226_methods
};

/**
 * @brief   @p INA226Driver specific data.
 */
#define _ina226_data                                                        \
    _base_object_data                                                       \
    /* Driver state.*/                                                      \
    ina226_state_t              state;                                      \
    /* Current configuration data.*/                                        \
    const INA226Config          *config;

/**
 * @brief MAX710 GPIO Expander class.
 */
struct INA226Driver {
    /** @brief Virtual Mthods Table.*/
    const struct INA226VMT     *vmt;
    _ina226_data
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
void ina226ObjectInit(INA226Driver *devp);
void ina226Start(INA226Driver *devp, const INA226Config *config);
void ina226Stop(INA226Driver *devp);
uint16_t ina226ReadRaw(INA226Driver *devp, uint8_t reg);
void ina226SetAlert(INA226Driver *devp, uint16_t alert_me, uint16_t alert_lim);
int32_t ina226ReadShunt(INA226Driver *devp);
uint32_t ina226ReadVBUS(INA226Driver *devp);
int32_t ina226ReadCurrent(INA226Driver *devp);
uint32_t ina226ReadPower(INA226Driver *devp);
#ifdef __cplusplus
}
#endif

#endif /* _INA226_H_ */

/** @} */
