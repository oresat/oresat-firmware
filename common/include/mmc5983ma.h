#ifndef COMMON_INCLUDE_MMC5983MA_H_
#define COMMON_INCLUDE_MMC5983MA_H_





#define MMC5983MA_I2C_ADDRESS_READ                  (0x30)
#define MMC5983MA_I2C_ADDRESS_WRITE                 (0x30)

#define MMC5983MA_EXPECTED_PRODUCT_CODE              0x30


#define MMC5983MA_XOUT_0            0x00
#define MMC5983MA_STATUS            0x08
#define MMC5983MA_CONTROL_0         0x09
#define MMC5983MA_CONTROL_1         0x10
#define MMC5983MA_CONTROL_2         0x11
#define MMC5983MA_CONTROL_3         0x12
#define MMC5983MA_PRODUCT_ID        0x2F




#define MMC5983MA_STATUS_MEAS_M_DONE          (1<<0)

#define MMC5983MA_CONTROL_0_TM_M              (1<<0)
#define MMC5983MA_CONTROL_0_SET               (1<<3)
#define MMC5983MA_CONTROL_0_RESET             (1<<4)

#define MMC5983MA_CONTROL_1_SW_RST_CMD        (1<<7)

#define MMC5983MA_CONTROL_2_CM_FREQ_1HZ       0x01




/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   MMC5983MA I2C interface switch.
 * @details If set to @p TRUE the support for I2C is included.
 * @note    The default is @p TRUE.
 */
#if !defined(MMC5983MA_USE_I2C) || defined(__DOXYGEN__)
#define MMC5983MA_USE_I2C                      TRUE
#endif

/**
 * @brief   MMC5983MA shared I2C switch.
 * @details If set to @p TRUE the device acquires I2C bus ownership
 *          on each transaction.
 * @note    The default is @p FALSE. Requires I2C_USE_MUTUAL_EXCLUSION.
 */
#if !defined(MMC5983MA_SHARED_I2C) || defined(__DOXYGEN__)
#define MMC5983MA_SHARED_I2C                   FALSE
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if MMC5983MA_USE_I2C && !HAL_USE_I2C
#error "MMC5983MA_USE_I2C requires HAL_USE_I2C"
#endif

#if MMC5983MA_SHARED_I2C && !I2C_USE_MUTUAL_EXCLUSION
#error "MMC5983MA_SHARED_I2C requires I2C_USE_MUTUAL_EXCLUSION"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @name    MMC5983MA data structures and types.
 * @{
 */


/**
 * @brief Structure representing a MMC5983MA driver.
 */
typedef struct MMC5983MADriver MMC5983MADriver;


/**
 * @brief   Driver state machine possible states.
 */
typedef enum {
    MMC5983MA_UNINIT = 0,                  /**< Not initialized.                 */
    MMC5983MA_STOP = 1,                    /**< Stopped.                         */
    MMC5983MA_READY = 2,                   /**< Ready.                           */
} mmc5983ma_state_t;

/**
 * @brief   MMC5983MA configuration structure.
 */
typedef struct {
#if (MMC5983MA_USE_I2C) || defined(__DOXYGEN__)
    /**
     * @brief I2C driver associated with this MMC5983MA.
     */
    I2CDriver                   *i2cp;
    /**
     * @brief I2C configuration associated with this MMC5983MA.
     */
    const I2CConfig             *i2ccfg;
    /**
     * @brief MMC5983MA Slave Address
     */
    //i2caddr_t                   saddr;
#endif /* MMC5983MA_USE_I2C */
} MMC5983MAConfig;

/**
 * @brief   @p MMC5983MA specific methods.
 */
#define _mmc5983ma_methods_alone

/**
 * @brief   @p MMC5983MA specific methods with inherited ones.
 */
#define _mmc5983ma_methods                                                     \
    _base_object_methods

/**
 * @extends BaseObjectVMT
 *
 * @brief   @p MMC5983MA virtual methods table.
 */
struct MMC5983MAVMT {
    _mmc5983ma_methods
};


/**
 * @brief   @p MMC5983MADriver specific data.
 */
#define _mmc5983ma_data                       \
    _base_object_data                         \
    /* Driver state.*/                        \
    mmc5983ma_state_t              state;     \
    /* Current configuration data.*/          \
    const MMC5983MAConfig          *config;   \
	float bridge_offset_estimate_x;           \
	float bridge_offset_estimate_y;           \
	float bridge_offset_estimate_z;           \
	uint32_t read_call_count;

/**
 * @brief MMC5983MA Power Monitor class.
 */
struct MMC5983MADriver {
    /** @brief Virtual Methods Table.*/
    const struct MMC5983MAVMT     *vmt;
    _mmc5983ma_data
};



typedef struct {
	int16_t mx;
	int16_t my;
	int16_t mz;
} mmc5983ma_data_t;


/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
void mmc5983maObjectInit(MMC5983MADriver *devp);
bool mmc5983maStart(MMC5983MADriver *devp, const MMC5983MAConfig *config);
void mmc5983maStop(MMC5983MADriver *devp);
bool mmc5983maReadData(MMC5983MADriver *devp, mmc5983ma_data_t *dest);
bool mmc5983maI2CReadRegister3(I2CDriver *i2cp, const uint8_t i2c_address, const uint8_t reg_number, uint8_t *dest_value);
bool mmc5983maI2CReadRegister4(I2CDriver *i2cp, const uint8_t i2c_address, const uint8_t reg_number, uint16_t *dest_value);
#ifdef __cplusplus
}
#endif









#endif /* COMMON_INCLUDE_MMC5983MA_H_ */
