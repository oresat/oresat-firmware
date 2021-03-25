/**
 * @file    bmi088.c
 * @brief   BMI088 6DoF inertial measurement unit.
 *
 * @addtogroup BMI088
 * @ingrup ORESAT
 * @{
 */

#include "hal.h"
#include "bmi088.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/
typedef union {
    struct __attribute__((packed)) {
        uint8_t reg;
        union {
            uint8_t data[2];
            uint16_t value;
        };
    };
    uint8_t buf[3];
} i2cbuf_t;

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

#if (BMI088_USE_I2C) || defined(__DOXYGEN__)
/**
 * @brief   Reads registers value using I2C.
 * @pre     The I2C interface must be initialized and the driver started.
 *
 * @param[in]  i2cp      pointer to the I2C interface
 * @param[in]  sad       slave address without R bit
 * @param[in]  reg       first sub-register address
 * @param[out] rxbuf     pointer to an output buffer
 * @param[in]  n         number of consecutive register to read
 * @return               the operation status.
 * @notapi
 */
msg_t bmi088I2CReadRegister(I2CDriver *i2cp, i2caddr_t sad, uint8_t reg,
        uint8_t* rxbuf, size_t n) {
    return i2cMasterTransmitTimeout(i2cp, sad, &reg, 1, rxbuf, n,
            TIME_INFINITE);
}

/**
 * @brief   Writes a value into a register using I2C.
 * @pre     The I2C interface must be initialized and the driver started.
 *
 * @param[in] i2cp       pointer to the I2C interface
 * @param[in] sad        slave address without R bit
 * @param[in] txbuf      buffer containing reg in first byte and high
 *                       and low data bytes
 * @param[in] n          size of txbuf
 * @return               the operation status.
 * @notapi
 */
msg_t bmi088I2CWriteRegister(I2CDriver *i2cp, i2caddr_t sad, uint8_t *txbuf,
        size_t n) {
    return i2cMasterTransmitTimeout(i2cp, sad, txbuf, n, NULL, 0,
            TIME_INFINITE);
}
#endif /* BMI088_USE_I2C */

/*==========================================================================*/
/* Interface implementation.                                                */
/*==========================================================================*/

static const struct BMI088VMT vmt_device = {
    (size_t)0,
};

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Initializes an instance.
 *
 * @param[out] devp     pointer to the @p BMI088Driver object
 *
 * @init
 */
void bmi088ObjectInit(BMI088Driver *devp) {
    devp->vmt = &vmt_device;

    devp->config = NULL;

    devp->state = BMI088_STOP;
}

/**
 * @brief   Configures and activates BMI088 Complex Driver peripheral.
 *
 * @param[in] devp      pointer to the @p BMI088Driver object
 * @param[in] config    pointer to the @p BMI088Config object
 *
 * @api
 */
void bmi088Start(BMI088Driver *devp, const BMI088Config *config) {
    i2cbuf_t buf;

    osalDbgCheck((devp != NULL) && (config != NULL));
    osalDbgAssert((devp->state == BMI088_STOP) ||
            (devp->state == BMI088_READY),
            "bmi088Start(), invalid state");

    devp->config = config;

    /* Configuring common registers.*/
#if BMI088_USE_I2C
#if BMI088_SHARED_I2C
    i2cAcquireBus(config->i2cp);
#endif /* BMI088_SHARED_I2C */

    i2cStart(config->i2cp, config->i2ccfg);
    buf.reg = BMI088_AD_ACC_PWR_CONF;
    buf.value = BMI088_AD_ACC_SOFTRESET;
    bmi088I2CWriteRegister(config->i2cp, config->acc_saddr, buf.buf, sizeof(buf));
    do {
        bmi088I2CReadRegister(config->i2cp, config->acc_saddr, BMI088_AD_ACC_PWR_CONF,
                                                buf.data, sizeof(buf.data));
    } while (buf.data[0] & 0x80U); /* While still resetting */
    buf.reg = BMI088_AD_ACC_PWR_CONF;
    buf.value = __REVSH(config->cfg);
    bmi088I2CWriteRegister(config->i2cp, config->acc_saddr, buf.buf, sizeof(buf));
    buf.reg = BMI088_AD_ACC_STATUS;
    buf.value = __REVSH(config->cal);
    bmi088I2CWriteRegister(config->i2cp, config->acc_saddr, buf.buf, sizeof(buf));

// 2021-03-25 -
    uint8_t chipId = bmi088ReadChipId(devp);
    if ( chipId == 0 ) { }


#if BMI088_SHARED_I2C
    i2cReleaseBus(config->i2cp);
#endif /* BMI088_SHARED_I2C */
#endif /* BMI088_USE_I2C */
    devp->state = BMI088_READY;
}

/**
 * @brief   Deactivates the BMI088 Complex Driver peripheral.
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 *
 * @api
 */
void bmi088Stop(BMI088Driver *devp) {
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state == BMI088_STOP) || (devp->state == BMI088_READY),
            "bmi088Stop(), invalid state");

    if (devp->state == BMI088_READY) {
#if BMI088_USE_I2C
#if BMI088_SHARED_I2C
        i2cAcquireBus(devp->config->i2cp);
        i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* BMI088_SHARED_I2C */

        /* Reset to input.*/
        buf.reg = BMI088_AD_ACC_PWR_CONF;
        buf.value = __REVSH(BMI088_AD_ACC_SOFTRESET);
        bmi088I2CWriteRegister(devp->config->i2cp, devp->config->acc_saddr, buf.buf, sizeof(buf));

        i2cStop(devp->config->i2cp);
#if BMI088_SHARED_I2C
        i2cReleaseBus(devp->config->i2cp);
#endif /* BMI088_SHARED_I2C */
#endif /* BMI088_USE_I2C */
    }
    devp->state = BMI088_STOP;
}
/**
 * @brief   Sets BMI088 Alert type and value
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @param[in] alert_me   the value to write to Mask/Enable register (0 to disable)
 * @param[in] alert_lim  the value to write to Alert Limit register
 *
 * @api
 */

/**
 * @brief   Reads BMI088 Register as raw value.
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @param[in] reg        the register to read from
 *
 * @api
 */
uint16_t bmi088ReadRaw(BMI088Driver *devp, uint8_t reg) {
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == BMI088_READY,
            "bmi088ReadRaw(), invalid state");

#if BMI088_USE_I2C
#if BMI088_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* BMI088_SHARED_I2C */

    buf.reg = reg;
    bmi088I2CReadRegister(devp->config->i2cp, devp->config->acc_saddr, buf.reg, buf.data, sizeof(buf.data));

#if BMI088_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* BMI088_SHARED_I2C */
#endif /* BMI088_USE_I2C */
    return __REVSH(buf.value);
}

/**
 * @brief   Soft Reset Command.
 *
 * @param[in] devp       Pointer to the @p BMI088Driver object
 * @param[in] soft_rst   write 0xB6 to soft reset register (Do not write any other value to this register)
 *               
 * @api
 */
void bmi088SoftReset(BMI088Driver *devp, uint8_t softRst){
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);

    buf.reg = BMI088_ACC_SOFTRESET;
    buf.value = softRst;
    bmi088I2CWriteRegister(devp->config->i2cp, devp->config->acc_saddr, buf.buf, sizeof(buf));    
}

/**
 * @brief   Enable BMI088 Accelerometer.
 *
 * @param[in] devp       Pointer to the @p BMI088Driver object              
 * @param[in] enable     Value to write to enable: 4, to disable: 0;
 * @api
 */
void accEnable(BMI088Driver *devp, uint8_t enable){
    i2cbuf_t buf;

    osalDbgCheck( devp != NULL );
    
    buf.reg = BMI088_ACC_PWR_CTRL;
    buf.value = enable;
    bmi088I2CWriteRegister(devp->config->i2cp, devp->config->acc_saddr, buf.buf, sizeof(buf));
}

/**
 * @brief   Read Power Control Register BMI088 Accelerometer.
 *
 * @param[in] devp       Pointer to the @p BMI088Driver object
 *
 * @eturn                Power Status
 *
 * @api
 */
uint8_t readPwrCtrlReg(BMI088Driver *devp){
    uint8_t powerStatus;

    osalDbgCheck(devp != NULL);

    powerStatus = bmi088ReadRaw(devp, BMI088_ACC_PWR_CTRL);

    return powerStatus;
}

/**
 * @brief   Reads BMI088 Chip ID.
 *
 * @param[in] devp       Pointer to the @p BMI088Driver object
 * @return               
 *
 * @api
 */
uint8_t bmi088ReadChipId(BMI088Driver *devp){
    uint8_t chipId;

    osalDbgCheck(devp != NULL);

    chipId = bmi088ReadRaw(devp, BMI088_AD_ACC_CHIP_ID);

    return chipId;    
}

/**
 * @brief   Reads BMI088  Error Code Register.
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @return               0x00: No Error
 *                       0x01: Error Occurred in Accelerometer configuration
 * @api
 */
uint8_t bmi088ReadErrCode(BMI088Driver *devp){
     uint8_t errCode;

     osalDbgCheck( devp != NULL);
     
     errCode = bmi088ReadRaw(devp, BMI088_ACC_ERR_CODE);

     return errCode;   
}

/**
 * @brief   Reads BMI088 Error Fatal Register.
 * 
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @return               Flag: fatal Error; cleared by power-on-reset or soft-reset 
 *
 * @api
 */
uint8_t bmi088ReadErrFatal(BMI088Driver *devp){
    uint8_t errFatal;

    osalDbgCheck(devp != NULL);

    errFatal = bmi088ReadRaw(devp, BMI088_ACC_ERR_FATAL);

    return errFatal;
}

/**
 * @brief   Reads BMI088 ACC Status Register.
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @return               Data ready for accelerometer. Reset when one acceleration data register is read out.
 *
 * @api
 */
uint8_t bmi088ReadAccStatus(BMI088Driver *devp){
    uint8_t stat;

    osalDbgCheck(devp != NULL);

    stat = bmi088ReadRaw(devp, BMI088_ACC_STATUS);

    return stat;
}

/**
 * @brief   Reads BMI088 ACC X Register.
 * @note    16 bit 2's compliment. Converted from LSB to mg. 
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @Return               Acceleration in X in mg.
 *
 * @api
 */
uint8_t bmi088ReadAccInX(BMI088Driver *devp){
    int16_t accXInMG;
    int16_t accXInt16;
    int8_t  accXLsb;
    int8_t  accXMsb;

    osalDbgCheck(devp != NULL);

    accXLsb     = bmi088ReadRaw(devp, BMI088_ACC_X_LSB);
    accXMsb     = bmi088ReadRaw(devp, BMI088_ACC_X_MSB);
    accXInt16   = (accXMsb*256 + accXLsb);
    accXInMG    = accXInt16/32768*1000*2*(0x41 + 1)*1.5;

    return accXInMG;
}
/**
 * @brief   Reads BMI088 ACC Y Register.
 * @note    16 bit 2's compliment. Converted from LSB to mg. 
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @Return               Acceleration in Y in mg.
 *
 * @api
 */
uint8_t bmi088ReadAccInY(BMI088Driver *devp){
    int16_t accYInMG;
    int16_t accYInt16;
    int8_t  accYLsb;
    int8_t  accYMsb;

    osalDbgCheck(devp != NULL);

    accYLsb     = bmi088ReadRaw(devp, BMI088_ACC_Y_LSB);
    accYMsb     = bmi088ReadRaw(devp, BMI088_ACC_Y_MSB);
    accYInt16   = (accYMsb*256 + accYLsb);
    accYInMG    = accYInt16/32768*1000*2*(0x41 + 1)*1.5;

    return accYInMG;
}
/**
 * @brief   Reads BMI088 ACC Z Register.
 * @note    16 bit 2's compliment. Converted from LSB to mg. 
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @Return               Acceleration in Z in mg.
 *
 * @api
 */
uint8_t bmi088ReadAccInZ(BMI088Driver *devp){
    int16_t accZInMG;
    int16_t accZInt16;
    int8_t  accZLsb;
    int8_t  accZMsb;

    osalDbgCheck(devp != NULL);

    accZLsb     = bmi088ReadRaw(devp, BMI088_ACC_Z_LSB);
    accZMsb     = bmi088ReadRaw(devp, BMI088_ACC_Z_MSB);
    accZInt16   = (accZMsb*256 + accZLsb);
    accZInMG    = accZInt16/32768*1000*2*(0x41 + 1)*1.5;

    return accZInMG;
}
/**
 * @brief   Reads BMI088 Sensortime Data register.
 * @note    Sensor time data stored in 3 consecutive 8 bit registers with sensor time 0 containing the LSB.
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @return               24 bit count value. 
 *
 * @api
 */
uint32_t bmi088ReadSensorTimeData(BMI088Driver *devp){
    uint8_t   sensorTime0;
    uint8_t   sensorTime1;
    uint8_t   sensorTime2;
    uint32_t  sensorTime;

    osalDbgCheck(devp != NULL);

    sensorTime0 = bmi088ReadRaw(devp, BMI088_ACC_SENSOR_TIME_0);
    sensorTime1 = bmi088ReadRaw(devp, BMI088_ACC_SENSOR_TIME_1);
    sensorTime2 = bmi088ReadRaw(devp, BMI088_ACC_SENSOR_TIME_2);
    sensorTime  = (sensorTime2 << 16) | (sensorTime1 << 8) | sensorTime0;

    return sensorTime;
}

/**
 * @brief   Reads BMI088 Interrupt Status Register.
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @return               interrupt status 
 *
 * @api
 */
uint8_t bmi088ReadIntStat(BMI088Driver *devp){
    uint8_t DataReady;

    osalDbgCheck(devp != NULL);

    DataReady = bmi088ReadRaw(devp, BMI088_ACC_INT_STAT_1);

    return DataReady;
}

/**
 * @brief   Reads BMI088 ACC Temperature sensor data
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @return               11 bit temp value in 2's complement format 
 *
 * @api
 */

  uint16_t bmi088ReadTemp(BMI088Driver *devp){
    int16_t  temperature;
    uint16_t temp_uint11;
    int16_t  temp_int11;
    uint8_t LSB;

    osalDbgCheck(devp != NULL);

    temp_uint11 = (BMI088_ACC_TEMP_MSB*8) + (BMI088_ACC_TEMP_LSB/32);

    if (temp_uint11 > 1023) {
      temp_int11 = (temp_uint11 - 2048);
    }
    else {
      temp_int11 = temp_uint11;
    }	
    
    LSB = 1;

    temperature = (temp_int11*0.125)/(LSB) + 23;

    return temperature;
}

/**
 * @brief   Reads BMI088 ACC Temperature sensor data
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @return               11 bit temp value in 2's complement format 
 *
 * @api
 */
