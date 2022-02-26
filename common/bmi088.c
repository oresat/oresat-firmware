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
msg_t bmi088I2CReadRegister(I2CDriver *i2cp, i2caddr_t saddr, uint8_t reg,
        uint8_t* rxbuf, size_t n) {
    return i2cMasterTransmitTimeout(i2cp, saddr, &reg, 1, rxbuf, n, TIME_MS2I(50));
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
msg_t bmi088I2CWriteRegister(I2CDriver *i2cp, i2caddr_t saddr, uint8_t *txbuf,
        size_t n) {
    return i2cMasterTransmitTimeout(i2cp, saddr, txbuf, n, NULL, 0, TIME_MS2I(50));
}
#endif /* BMI088_USE_I2C */

/*==========================================================================*/
/* Interface implementation.                                                */
/*==========================================================================*/

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
bool bmi088Start(BMI088Driver *devp, const BMI088Config *config) {
    bool ret = true;

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

#if (0)
    i2cbuf_t buf;

// Following value assignment does not seem right per BMI088 datasheet - TMH:
    buf.reg = BMI088_ADDR_ACC_PWR_CONF;     // this accelerometer register address is 0x7C
    buf.value = BMI088_ADDR_ACC_SOFTRESET;  // this value defined as 0x7E, which is another register address not 0x00 nor 0x03.
    bmi088I2CWriteRegister(config->i2cp, config->acc_saddr, buf.buf, sizeof(buf));
    do {
        bmi088I2CReadRegister(config->i2cp, config->acc_saddr, BMI088_ADDR_ACC_PWR_CONF,
                                                buf.data, sizeof(buf.data));
    } while (buf.data[0] & 0x80U); /* While still resetting */

    buf.reg = BMI088_ADDR_ACC_STATUS;
    buf.value = __REVSH(config->cal);
    bmi088I2CWriteRegister(config->i2cp, config->acc_saddr, buf.buf, sizeof(buf));
#endif


    if( bmi088AccelerometerPowerOnOrOff(devp, BMI088_ON) != MSG_OK ) {
        ret = false;
    }

    if( bmi088AccelerometerEnableOrSuspend(devp, BMI088_MODE_ACTIVE) != MSG_OK ) {
        ret = false;
    }

    if( bmi088SetGyroBandwidth(devp, BMI088_GYR_BANDWIDTH_100HZ_32HZ) != MSG_OK ) {
        ret = false;
    }

    if( bmi088SetGyroRange(devp, BMI088_GYR_RANGE_1K) != MSG_OK ) {
        ret = false;
    }

#if BMI088_SHARED_I2C
    i2cReleaseBus(config->i2cp);
#endif /* BMI088_SHARED_I2C */
#endif /* BMI088_USE_I2C */

    if( ret ) {
        devp->state = BMI088_READY;
    }

    return(ret);
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
        buf.reg = BMI088_ADDR_ACC_PWR_CONF;
        buf.value = __REVSH(BMI088_ADDR_ACC_SOFTRESET);
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
 * Reads an 8 bit register value into *dest
 * TODO more documentation
 */
msg_t bmi088ReadRawU8Err(BMI088Driver *devp, i2caddr_t saddr, uint8_t reg, uint8_t *dest) {
    i2cbuf_t buf;
    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == BMI088_READY,
            "bmi088ReadRawU8(), invalid state");
#if BMI088_USE_I2C
#if BMI088_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* BMI088_SHARED_I2C */

    buf.reg = reg;
    const msg_t r = bmi088I2CReadRegister(devp->config->i2cp, saddr, buf.reg, buf.data, 1);

#if BMI088_SHARED_I2C
    i2cStop(devp->config->i2cp);
    i2cReleaseBus(devp->config->i2cp);
#endif /* BMI088_SHARED_I2C */
#endif /* BMI088_USE_I2C */

    if( r == MSG_OK ) {
        *dest = buf.data[0];
    }
    return(r);
}

/**
 * TODO document this
 */
msg_t bmi088ReadRawBuff(BMI088Driver *devp, i2caddr_t saddr, uint8_t reg, uint8_t *dest, uint8_t length) {

    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == BMI088_READY,
            "bmi088ReadRawU8(), invalid state");
#if BMI088_USE_I2C
#if BMI088_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* BMI088_SHARED_I2C */

    const msg_t ret = bmi088I2CReadRegister(devp->config->i2cp, saddr, reg, dest, length);

#if BMI088_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* BMI088_SHARED_I2C */
#endif /* BMI088_USE_I2C */

    return(ret);
}


/**
 * TODO document this
 */
msg_t bmi088I2CWriteRegisterU8(BMI088Driver *devp, i2caddr_t saddr, uint8_t reg, uint8_t value, const uint32_t post_delay_ms) {
    osalDbgCheck(devp != NULL);

    uint8_t write_buffer[2];

    write_buffer[0] = reg;
    write_buffer[1] = value;

    msg_t r = bmi088I2CWriteRegister(devp->config->i2cp, saddr, write_buffer, sizeof(write_buffer));
    if( post_delay_ms > 0 ) {
        chThdSleepMilliseconds(post_delay_ms);
    }
    return(r);
}


/**
 * @brief   Soft Reset Command.
 *
 * @param[in] devp       Pointer to the @p BMI088Driver object
 * @param[in] soft_rst   write 0xB6 to soft reset register (Do not write any other value to this register)
 *
 * @api
 */
msg_t bmi088SoftReset(BMI088Driver *devp) {
    osalDbgCheck(devp != NULL);
    // 0xB6 is magic number from data sheet page 35
    return(bmi088I2CWriteRegisterU8(devp, devp->config->acc_saddr, BMI088_ACC_SOFTRESET, 0xB6, 0));
}


/**
 * @brief   Enable BMI088 Accelerometer.
 *
 * @param[in] devp       Pointer to the @p BMI088Driver object
 * @param[in] enable     Value to write to enable: 4, to disable: 0;
 * @api
 * @note   2021-03-30 Ted observes I2C lines only showing two bytes sent, saddr and
 *         sensor register address, when sizeof(write_buffer) used as fourth
 *         parameter in call to bmi088I2CWriteRegister() routine.
 */
msg_t bmi088AccelerometerPowerOnOrOff(BMI088Driver *devp, const bmi088_power_state_t power_state) {
    osalDbgCheck( devp != NULL );
    const uint32_t post_delay_ms = (power_state == BMI088_ON ? 50 : 0);// Per data sheet page 12
    return(bmi088I2CWriteRegisterU8(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_PWR_CTRL, power_state, post_delay_ms));
}

/**
 * TODO document this
 */
msg_t bmi088AccelerometerEnableOrSuspend(BMI088Driver *devp, const bmi088_acc_operating_mode_t operating_mode) {
    osalDbgCheck( devp != NULL );
    return(bmi088I2CWriteRegisterU8(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_PWR_CONF, operating_mode, 0));
}

/**
 * TODO document this
 */
msg_t bmi088AccelerometerSetFilterAndODR(BMI088Driver *devp, const uint8_t acc_filter_and_odr) {
    osalDbgCheck( devp != NULL );
    // 0x40 per data sheet page 22
    return(bmi088I2CWriteRegisterU8(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_CONF, (acc_filter_and_odr | 0x80), 0));
}


// 0x00 self test disabled
// 0x0D positive self test
// 0x09 negative self test

msg_t bmi088AccelerometerSetSelfTestMode(BMI088Driver *devp, const uint8_t self_test_mode) {
    osalDbgCheck( devp != NULL );
    // per BMI088 data sheet page 16
    return(bmi088I2CWriteRegisterU8(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_SELF_TEST, self_test_mode, 50));
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
msg_t bmi088ReadPowerCtrlReg(BMI088Driver *devp, uint8_t *dest){
    osalDbgCheck(devp != NULL);
    return(bmi088ReadRawU8Err(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_PWR_CTRL, dest));
}

/**
 * TODO document this
 */
msg_t bmi088ReadPowerConfReg(BMI088Driver *devp, uint8_t *dest){
    osalDbgCheck(devp != NULL);
    return(bmi088ReadRawU8Err(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_PWR_CONF, dest));
}

/**
 * @brief   Reads BMI088 Chip ID.
 *
 * @param[in] devp       Pointer to the @p BMI088Driver object
 * @return
 *
 * @api
 */
msg_t bmi088ReadAccelerometerChipId(BMI088Driver *devp, uint8_t *dest) {
    osalDbgCheck(devp != NULL);
    return(bmi088ReadRawU8Err(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_CHIP_ID, dest));
}


/**
 * FIXME documentation
 */
msg_t bmi088ReadGyroChipId(BMI088Driver *devp, uint8_t *dest){
    osalDbgCheck(devp != NULL);
    return(bmi088ReadRawU8Err(devp, devp->config->gyro_saddr, BMI088_AD_GYR_CHIP_ID, dest));
}


/**
 * @brief   Reads BMI088  Error Code Register.
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @return               0x00: No Error
 *                       0x01: Error Occurred in Accelerometer configuration
 * @api
 */
msg_t bmi088ReadErrCode(BMI088Driver *devp, uint8_t *dest){
     osalDbgCheck( devp != NULL);
     return(bmi088ReadRawU8Err(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_ERR_REG, dest));
// 0b00011101 == 0x1D <-- mask per BMI088 datasheet page 20
}

/**
 * @brief   Reads BMI088 Error Fatal Register.
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @return               Flag: fatal Error; cleared by power-on-reset or soft-reset
 *
 * @api
 */
msg_t bmi088ReadErrFatal(BMI088Driver *devp, uint8_t *dest){
    osalDbgCheck(devp != NULL);
    msg_t r = bmi088ReadRawU8Err(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_ERR_REG, dest);
    if( r == MSG_OK ) {
        *dest &= 0x01;
    }
    return(r);
}

/**
 * @brief   Reads BMI088 ACC Status Register.
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @return               Data ready for accelerometer. Reset when one acceleration data register is read out.
 *
 * @api
 */
msg_t bmi088ReadAccelerometerStatus(BMI088Driver *devp, uint8_t *dest){
    osalDbgCheck(devp != NULL);
    msg_t r = bmi088ReadRawU8Err(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_STATUS, dest);
    if( r == MSG_OK ) {
        *dest &= 0x80;
    }
    return(r);
}


/**
 * Convert raw lsb/msb of accelerometer into milli-G's
 * TODO document this
 */
int32_t bmi088RawAcclTmG(const uint8_t lsb, const uint8_t msb) {
    const int16_t accInt16   = (msb << 8) |  lsb;

    const int32_t accx_range_register = 0x01;//FIXME query register for dynamic value. Using the power up default for now

    const int32_t accMG  = (((accInt16 * 1000 * 2 * (accx_range_register + 1))/ 32768) * 3) / 2;

    return(accMG);
}

/**
 * Read X/Y/Z accelerometer readings
 * TODO more documentation
 */
msg_t bmi088ReadAccelerometerXYZmG(BMI088Driver *devp, bmi088_accelerometer_sample_t *dest) {
    osalDbgCheck(devp != NULL);

    uint8_t raw_data_buffer[6];
    msg_t r = bmi088ReadRawBuff(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_X_LSB, raw_data_buffer, sizeof(raw_data_buffer));
    if( r == MSG_OK ) {
        dest->accl_x = bmi088RawAcclTmG(raw_data_buffer[0], raw_data_buffer[1]);
        dest->accl_y = bmi088RawAcclTmG(raw_data_buffer[2], raw_data_buffer[3]);
        dest->accl_z = bmi088RawAcclTmG(raw_data_buffer[4], raw_data_buffer[5]);

        dest->accl_x_raw = raw_data_buffer[0] | (raw_data_buffer[1] << 8);
        dest->accl_y_raw = raw_data_buffer[2] | (raw_data_buffer[3] << 8);
        dest->accl_z_raw = raw_data_buffer[4] | (raw_data_buffer[5] << 8);
    }

    return(r);
}


/**
 * @brief   Reads BMI088 Interrupt Status Register.
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @return               interrupt status
 *
 * @api
 */
msg_t bmi088ReadIntStat(BMI088Driver *devp, uint8_t *dest){
    osalDbgCheck(devp != NULL);

    msg_t r = bmi088ReadRawU8Err(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_INT_STAT_1, dest);
    if( r == MSG_OK ) {
        *dest &= 0x80;
    }
    return(r);
}

/**
 * @brief   Reads BMI088 ACC Temperature sensor data
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @return               11 bit temp value in 2's complement format
 *
 * @api
 */

msg_t bmi088ReadTemp(BMI088Driver *devp, int16_t *dest_temp_c){
    osalDbgCheck(devp != NULL);

    uint8_t raw_data_buffer[2];
    msg_t r = bmi088ReadRawBuff(devp, devp->config->acc_saddr, BMI088_ADDR_TEMP_MSB, raw_data_buffer, sizeof(raw_data_buffer));
    if( r == MSG_OK ) {
        //TODO validate that this handles negative temperatures correctly
        //This code block is directly from the datasheet
        int16_t  temp_int11 = 0;
        uint32_t temp_uint11 = ( raw_data_buffer[0] * 8 ) + ( raw_data_buffer[1] / 32 );

        if (temp_uint11 > 1023) {
          temp_int11 = (temp_uint11 - 2048);
        } else {
          temp_int11 = temp_uint11;
        }
        *dest_temp_c = ((temp_int11 * 125) / 1000) + 23;
    }

    return(r);
}


/**
 * FIXME documentation
 */
int32_t bmi088RawGyroToDegPerSec(const uint8_t lsb, const uint8_t msb) {
    //TODO verify this calculation with real world known rotation rate data
    const int16_t gyroInt16   = (msb << 8) |  lsb;

    const int32_t deg_per_sec_per_lsb = 32768; // for 1000 deg/sec range

    const int32_t dps = (gyroInt16 * 1000) /  deg_per_sec_per_lsb;

    return(dps);
}


/**
 * FIXME documentation
 */
msg_t bmi088ReadGyroXYZ(BMI088Driver *devp, bmi088_gyro_sample_t *dest) {
    osalDbgCheck(devp != NULL);

    uint8_t raw_data_buffer[6];
    msg_t r = bmi088ReadRawBuff(devp, devp->config->gyro_saddr, BMI088_AD_GYR_RATE_X_LSB, raw_data_buffer, sizeof(raw_data_buffer));
    if( r == MSG_OK ) {
        dest->gyro_x = bmi088RawGyroToDegPerSec(raw_data_buffer[0], raw_data_buffer[1]);
        dest->gyro_y = bmi088RawGyroToDegPerSec(raw_data_buffer[2], raw_data_buffer[3]);
        dest->gyro_z = bmi088RawGyroToDegPerSec(raw_data_buffer[4], raw_data_buffer[5]);

        dest->gyro_x_raw = raw_data_buffer[0] | (raw_data_buffer[1] << 8);
        dest->gyro_y_raw = raw_data_buffer[2] | (raw_data_buffer[3] << 8);
        dest->gyro_z_raw = raw_data_buffer[4] | (raw_data_buffer[5] << 8);
    }

    return(r);
}

msg_t bmi088SetGyroBandwidth(BMI088Driver *devp, const uint8_t bandwidth) {
    return bmi088I2CWriteRegisterU8(devp, devp->config->gyro_saddr, BMI088_AD_GYR_BANDWIDTH, bandwidth, 0);
}

msg_t bmi088SetGyroRange(BMI088Driver *devp, const uint8_t range) {
    return bmi088I2CWriteRegisterU8(devp, devp->config->gyro_saddr, BMI088_AD_GYR_RANGE, range, 0);
}
