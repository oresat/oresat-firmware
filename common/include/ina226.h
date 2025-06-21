#ifndef _INA226_H_
#define _INA226_H_
/* INA226 Digital to Analog Converter */

#if !HAL_USE_I2C
#error "INA226 requires HAL_USE_I2C"
#endif

#if !I2C_USE_MUTUAL_EXCLUSION
#error "INA226 requires I2C_USE_MUTUAL_EXCLUSION"
#endif

// INA226 Configuration register fields
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
    /**
     * @brief I2C driver associated with this INA226.
     */
    I2CDriver                   *i2cp;
    /**
     * @brief INA226 Slave Address
     */
    i2caddr_t                   saddr;
    /**
     * @brief INA226 configuration reg value
     */
    uint16_t                    cfg;
    /**
     * @brief Shunt resistor value
     */
    uint16_t                    rshunt_mOhm;
    /**
     * @brief Current LSB value for use in calculations
     */
    uint16_t                    curr_lsb_uA;
} INA226Config;


/**
 * @brief INA226 Power Monitor class.
 */
typedef struct INA226Driver {
    /* Driver state.*/
    ina226_state_t              state;
    /* Current configuration data.*/
    const INA226Config          *config;
    /* Time for a single power conversion in system ticks */
    systime_t t_conversion;
} INA226Driver;

void ina226ObjectInit(INA226Driver *devp);
msg_t ina226Start(INA226Driver *devp, const INA226Config *config);
msg_t ina226Stop(INA226Driver *devp);
msg_t ina226ReadShunt(INA226Driver *devp, int32_t *voltage_uV);
msg_t ina226ReadVBUS(INA226Driver *devp, int32_t *voltage_mV);
msg_t ina226ReadCurrent(INA226Driver *devp, int32_t *current_uA);
msg_t ina226ReadPower(INA226Driver *devp, int32_t *power_mW);
msg_t ina226TriggerOneShotConversion(INA226Driver *devp);
msg_t ina226CheckConversionStatus(INA226Driver *devp, bool *conversion_ready);

#endif /* _INA226_H_ */
