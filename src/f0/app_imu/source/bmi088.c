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
#include "chprintf.h"
#include "string.h"

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


typedef union {
    int16_t as_int16_type;
    uint8_t as_bytes[1];
} reading_union_t;


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

    if( BMI088AccelerometerPowerOnOrOff(devp, BMI088_ON) != MSG_OK ) {
    	//FIXME better error handling
    	ret = false;
    }

    if( BMI088AccelerometerEnableOrSuspend(devp, BMI088_MODE_ACTIVE) != MSG_OK ) {
    	//FIXME better error handling
    	ret = false;
    }


#if BMI088_SHARED_I2C
    i2cReleaseBus(config->i2cp);
#endif /* BMI088_SHARED_I2C */
#endif /* BMI088_USE_I2C */



    uint8_t chip_id_accelerometer = 0;
    msg_t r = bmi088ReadChipId(devp, &chip_id_accelerometer);
    if ( chip_id_accelerometer != BMI088_ACCL_EXPECTED_CHIP_ID ) {
        chThdSleepMilliseconds(2);
        r =  bmi088ReadChipId(devp, &chip_id_accelerometer);
    }

    if ( chip_id_accelerometer != BMI088_ACCL_EXPECTED_CHIP_ID ) {
    	ret = false;
    }


#if 0
    if( ! ret ) {
    	devp->state = BMI088_UNINIT;
    } else {
    	devp->state = BMI088_READY;
    }
#else
    //FIXME switch this #if block
    devp->state = BMI088_READY;
#endif

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


#if ( 0 )
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
/*
uint16_t bmi088ReadRaw(BMI088Driver *devp, uint8_t reg) {
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == BMI088_READY,
            "bmi088ReadRaw(), invalid state");

#if BMI088_USE_I2C
#if BMI088_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif // * BMI088_SHARED_I2C * /

    buf.reg = reg;
    bmi088I2CReadRegister(devp->config->i2cp, devp->config->acc_saddr, buf.reg, buf.data, sizeof(buf.data));

#if BMI088_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif // * BMI088_SHARED_I2C * /
#endif // * BMI088_USE_I2C * /
    return __REVSH(buf.value);
}
*/
#endif



/**
 * @brief   Reads BMI088 Register as raw 8 bit value.
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @param[in] saddr      slave address
 * @param[in] reg        the register to read from
 *
 * @api
 */
uint8_t bmi088ReadRawU8(BMI088Driver *devp, i2caddr_t saddr, uint8_t reg) {
    i2cbuf_t buf;
    memset(&buf, 0, sizeof(buf));

//    uint8_t data = 0;  // This routine designed to read one byte - TMH
    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == BMI088_READY,
            "bmi088ReadRawU8(), invalid state");
#if BMI088_USE_I2C
#if BMI088_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* BMI088_SHARED_I2C */

    buf.reg = reg;
    msg_t r = bmi088I2CReadRegister(devp->config->i2cp, saddr, buf.reg, buf.data, 1);
    if( r != MSG_OK ) {
    	chprintf((BaseSequentialStream*)&SD2, "Failed to bmi088I2CReadRegister(), r=%d\r\n", r);
    } else {
    	chprintf((BaseSequentialStream*)&SD2, "Successfully read bmi088I2CReadRegister(), r=%d\r\n", r);
    }

//    bmi088I2CReadRegister(devp->config->i2cp, saddr, reg, &data, 1);
#if BMI088_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* BMI088_SHARED_I2C */
#endif /* BMI088_USE_I2C */

    return buf.data[0];
}

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
    msg_t r = bmi088I2CReadRegister(devp->config->i2cp, saddr, buf.reg, buf.data, 1);
    if( r != MSG_OK ) {
    	chprintf((BaseSequentialStream*)&SD2, "Failed to bmi088I2CReadRegister(), r=%d\r\n", r);
    } else {
    	chprintf((BaseSequentialStream*)&SD2, "Successfully read bmi088I2CReadRegister(), r=%d\r\n", r);
    }

#if BMI088_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* BMI088_SHARED_I2C */
#endif /* BMI088_USE_I2C */

    if( r == MSG_OK ) {
    	*dest = buf.data[0];
    }
    return(r);
}

msg_t bmi088ReadRawBuff(BMI088Driver *devp, i2caddr_t saddr, uint8_t reg, uint8_t *dest, uint8_t length) {
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
    msg_t ret = bmi088I2CReadRegister(devp->config->i2cp, saddr, buf.reg, dest, length);

#if BMI088_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* BMI088_SHARED_I2C */
#endif /* BMI088_USE_I2C */

    return(ret);
}


/**
 * @brief   Reads BMI088 Register as raw 16 bit value.
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @param[in] saddr      slave address
 * @param[in] reg        the register to read from
 *
 * @api
 */
uint16_t bmi088ReadRawU16(BMI088Driver *devp, i2caddr_t saddr, uint8_t reg) {
    i2cbuf_t buf;
    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == BMI088_READY,
            "bmi088ReadRawU16(), invalid state");
#if BMI088_USE_I2C
#if BMI088_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* BMI088_SHARED_I2C */
    buf.reg = reg;
    bmi088I2CReadRegister(devp->config->i2cp, saddr, buf.reg, buf.data, 2);
#if BMI088_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* BMI088_SHARED_I2C */
#endif /* BMI088_USE_I2C */
    return buf.value;
}

/**
 * FIXME document this
 */
msg_t bmi088I2CWriteRegisterU8(BMI088Driver *devp, i2caddr_t saddr, uint8_t reg, uint8_t value, const uint32_t post_delay_ms) {
	uint8_t write_buffer[2];

	osalDbgCheck(devp != NULL);

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
msg_t BMI088AccelerometerPowerOnOrOff(BMI088Driver *devp, const bmi088_power_state_t power_state) {
    osalDbgCheck( devp != NULL );
    const uint32_t post_delay_ms = (power_state == BMI088_ON ? 50 : 0);// Per data sheet page 12
    return(bmi088I2CWriteRegisterU8(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_PWR_CTRL, power_state, post_delay_ms));
}


msg_t BMI088AccelerometerEnableOrSuspend(BMI088Driver *devp, bmi088_acc_operating_mode_t operating_mode) {
    osalDbgCheck( devp != NULL );
    return(bmi088I2CWriteRegisterU8(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_PWR_CONF, operating_mode, 0));
}


msg_t BMI088AccelerometerSetFilterAndODR(BMI088Driver *devp, uint8_t acc_filter_and_odr) {
    osalDbgCheck( devp != NULL );
    // 0x40 per data sheet page 22
    return(bmi088I2CWriteRegisterU8(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_CONF, (acc_filter_and_odr | 0x80), 0));
}


// 0x00 self test disabled
// 0x0D positive self test
// 0x09 negative self test

msg_t BMI088AccelerometerSetSelfTestMode(BMI088Driver *devp, uint8_t self_test_mode) {
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
uint8_t readPowerCtrlReg(BMI088Driver *devp){
    uint8_t powerStatus;

    osalDbgCheck(devp != NULL);

    powerStatus = bmi088ReadRawU8(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_PWR_CTRL);

    return powerStatus;
}


uint8_t readPowerConfReg(BMI088Driver *devp){
    uint8_t operationMode;

    osalDbgCheck(devp != NULL);

    operationMode = bmi088ReadRawU8(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_PWR_CONF);

    return operationMode;
}


/**
 * @brief   Reads BMI088 Chip ID.
 *
 * @param[in] devp       Pointer to the @p BMI088Driver object
 * @return               
 *
 * @api
 */
msg_t bmi088ReadChipId(BMI088Driver *devp, uint8_t *dest) {
    osalDbgCheck(devp != NULL);
    msg_t r = bmi088ReadRawU8Err(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_CHIP_ID, dest);
    return r;
}


/**
 * FIXME documentation
 */
msg_t bmi088ReadGyrosChipId(BMI088Driver *devp, uint8_t *dest){

    osalDbgCheck(devp != NULL);

    msg_t r = bmi088ReadRawU8Err(devp, devp->config->gyro_saddr, BMI088_AD_GYR_CHIP_ID, dest);

    return r;
}



// --- SECTION ---

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
     
     errCode = bmi088ReadRawU8(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_ERR_REG);
// 0b00011101 == 0x1D <-- mask per BMI088 datasheet page 20
     return (errCode & 0x1D);   // NEED to use pound define for this mask - TMH
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

    errFatal = bmi088ReadRawU8(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_ERR_REG);

    return (errFatal & 0x01);  // NEED to use pound define for this mask - TMH
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
    uint8_t status;

    osalDbgCheck(devp != NULL);

    status = bmi088ReadRawU8(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_STATUS);

    return (status & 0x80);  // NEED to use pound define for this mask - TMH
}

#if 0
/**
 * @brief   Reads BMI088 ACC X Register.
 * @note    16 bit 2's compliment. Converted from LSB to mg. 
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @Return               Acceleration in X in mg.
 *
 * @api
 */
int16_t bmi088ReadAccInX(BMI088Driver *devp) {
    int16_t accXInMG;
    int16_t accXInt16;
//    int8_t  accXLsb;
//    int8_t  accXMsb;
    //reading_union_t acc_reading;

    osalDbgCheck(devp != NULL);

//    accXLsb     = bmi088ReadRawU8(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_X_LSB);
//    accXMsb     = bmi088ReadRawU8(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_X_MSB);
//    accXInt16   = (accXMsb * 256 + accXLsb);
    accXInt16 = (int16_t)bmi088ReadRawU16(devp, devp->config->acc_saddr, 0x02);
    accXInMG    = accXInt16 / 32768 * 1000 * 2 * (0x41 + 1) * 1.5;

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
int16_t bmi088ReadAccInY(BMI088Driver *devp){
    int16_t accYInMG;
    int16_t accYInt16;
    int8_t  accYLsb;
    int8_t  accYMsb;

    osalDbgCheck(devp != NULL);

    accYLsb     = bmi088ReadRawU8(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_Y_LSB);
    accYMsb     = bmi088ReadRawU8(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_Y_MSB);
    accYInt16   = (accYMsb * 256 + accYLsb);
    accYInMG    = accYInt16 / 32768 * 1000 * 2 * (0x41 + 1) * 1.5;

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
int16_t bmi088ReadAccInZ(BMI088Driver *devp){
    int16_t accZInMG;
    int16_t accZInt16;
    int8_t  accZLsb;
    int8_t  accZMsb;

    osalDbgCheck(devp != NULL);

    accZLsb     = bmi088ReadRawU8(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_Z_LSB);
    accZMsb     = bmi088ReadRawU8(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_Z_LSB);
    accZInt16   = (accZMsb*256 + accZLsb);
    accZInMG    = accZInt16/32768*1000*2*(0x41 + 1)*1.5;

    return accZInMG;
}
#endif

/**
 * FIXME documentation
 */
int32_t bmi088RawAcclTmG(const uint8_t lsb, const uint8_t msb) {
	int16_t accInt16   = (msb << 8) |  lsb;

	int32_t accx_range_register = 0x01;//FIXME query register

	int32_t accMG  = (((accInt16 * 1000 * 2 * (accx_range_register + 1))/ 32768) * 3) / 2;

	return(accMG);
}

/**
 * FIXME documentation
 */
msg_t bmi088ReadAccXYZmG(BMI088Driver *devp, int32_t *dest_accl_x, int32_t *dest_accl_y, int32_t *dest_accl_z ) {
    osalDbgCheck(devp != NULL);

    uint8_t raw_data_buffer[6];
    msg_t r = bmi088ReadRawBuff(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_X_LSB, raw_data_buffer, sizeof(raw_data_buffer));
    if( r == MSG_OK ) {
    	*dest_accl_x = bmi088RawAcclTmG(raw_data_buffer[0], raw_data_buffer[1]);
    	*dest_accl_y = bmi088RawAcclTmG(raw_data_buffer[2], raw_data_buffer[3]);
    	*dest_accl_z = bmi088RawAcclTmG(raw_data_buffer[4], raw_data_buffer[5]);
    }

    return(r);
}



int32_t bmi088RawAcclTmS2(const uint8_t lsb, const uint8_t msb) {
	//FIXME impliment this
	int16_t accInt16   = (msb << 8) |  lsb;

	int32_t accx_range_register = 0x01;//FIXME query register

	int32_t accMG  = (((accInt16 * 1000 * 2 * (accx_range_register + 1))/ 32768) * 3) / 2;

	return(accMG);
}

/**
 * FIXME documentation
 */
msg_t bmi088ReadAccXYZmS2(BMI088Driver *devp, int32_t *dest_accl_x, int32_t *dest_accl_y, int32_t *dest_accl_z, uint16_t *dest_acc_x_raw, uint16_t *dest_acc_y_raw, uint16_t *dest_acc_z_raw) {
    osalDbgCheck(devp != NULL);

    uint8_t raw_data_buffer[6];
    msg_t r = bmi088ReadRawBuff(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_X_LSB, raw_data_buffer, sizeof(raw_data_buffer));
    if( r == MSG_OK ) {
    	*dest_accl_x = bmi088RawAcclTmS2(raw_data_buffer[0], raw_data_buffer[1]);
    	*dest_accl_y = bmi088RawAcclTmS2(raw_data_buffer[2], raw_data_buffer[3]);
    	*dest_accl_z = bmi088RawAcclTmS2(raw_data_buffer[4], raw_data_buffer[5]);

    	*dest_acc_x_raw = raw_data_buffer[0] | (raw_data_buffer[1] << 8);
    	*dest_acc_y_raw = raw_data_buffer[2] | (raw_data_buffer[3] << 8);
    	*dest_acc_z_raw = raw_data_buffer[4] | (raw_data_buffer[5] << 8);
    }

    return(r);
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

    sensorTime0 = bmi088ReadRawU8(devp, devp->config->acc_saddr, BMI088_ACC_SENSOR_TIME_0);
    sensorTime1 = bmi088ReadRawU8(devp, devp->config->acc_saddr, BMI088_ACC_SENSOR_TIME_1);
    sensorTime2 = bmi088ReadRawU8(devp, devp->config->acc_saddr, BMI088_ACC_SENSOR_TIME_2);
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

    DataReady = bmi088ReadRawU8(devp, devp->config->acc_saddr, BMI088_ADDR_ACC_INT_STAT_1);

    return (DataReady & 0x80);
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
    //int16_t  temperature;
    //uint16_t temp_uint11;
    //uint8_t LSB;

    //reading_union_t reading;
    //reading.as_int16_type = 0;

    osalDbgCheck(devp != NULL);

    uint8_t raw_data_buffer[2];
    msg_t r = bmi088ReadRawBuff(devp, devp->config->acc_saddr, BMI088_ADDR_TEMP_MSB, raw_data_buffer, sizeof(raw_data_buffer));
    if( r == MSG_OK ) {
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
 * @brief   Reads BMI088 ACC Temperature sensor data
 *
 * @param[in] devp       pointer to the @p BMI088Driver object
 * @return               11 bit temp value in 2's complement format 
 *
 * @api
 */


#if 0
// -- SECTION --  Gyroscope related routines

uint8_t bmi088ObtainGyroscopesReadings(BMI088Driver *devp, uint8_t* packed_readings) {

//    union reading_union_t {
//      int16_t as_int16_type;
//      uint8_t as_bytes[1];
//    };

//    union reading_union_t gyro_reading;
    reading_union_t gyro_reading;
    gyro_reading.as_int16_type = 0;

    osalDbgCheck(devp != NULL);

    gyro_reading.as_int16_type = (int16_t)bmi088ReadRawU16(devp, devp->config->gyro_saddr, BMI088_AD_GYR_RATE_X_LSB);
    packed_readings[0] = gyro_reading.as_bytes[0];
    packed_readings[1] = gyro_reading.as_bytes[1];

    gyro_reading.as_int16_type = (int16_t)bmi088ReadRawU16(devp, devp->config->gyro_saddr, BMI088_AD_GYR_RATE_Y_LSB);
    packed_readings[2] = gyro_reading.as_bytes[0];
    packed_readings[3] = gyro_reading.as_bytes[1];

    gyro_reading.as_int16_type = (int16_t)bmi088ReadRawU16(devp, devp->config->gyro_saddr, BMI088_AD_GYR_RATE_Z_LSB);
    packed_readings[4] = gyro_reading.as_bytes[0];
    packed_readings[5] = gyro_reading.as_bytes[1];

    return 1;
}
#endif

#if 1

/**
 * FIXME documentation
 */
int32_t bmi088RawGyroToDegPerSec(const uint8_t lsb, const uint8_t msb) {
	int16_t gyroInt16   = (msb << 8) |  lsb;

	int32_t lsb_deg_per_sec = 16384; // for 2000 deg/sec range

	int32_t dps = (gyroInt16 * lsb_deg_per_sec) / 1000;

	return(dps);
}


/**
 * FIXME documentation
 */
msg_t bmi088ReadGyroXYZ(BMI088Driver *devp, int32_t *dest_gyro_x, int32_t *dest_gyro_y, int32_t *dest_gyro_z, uint16_t *dest_gyro_x_raw, uint16_t *dest_gyro_y_raw, uint16_t *dest_gyro_z_raw) {
    osalDbgCheck(devp != NULL);

    uint8_t raw_data_buffer[6];
    msg_t r = bmi088ReadRawBuff(devp, devp->config->gyro_saddr, BMI088_AD_GYR_RATE_X_LSB, raw_data_buffer, sizeof(raw_data_buffer));
    if( r == MSG_OK ) {
    	*dest_gyro_x = bmi088RawGyroToDegPerSec(raw_data_buffer[0], raw_data_buffer[1]);
    	*dest_gyro_y = bmi088RawGyroToDegPerSec(raw_data_buffer[2], raw_data_buffer[3]);
    	*dest_gyro_z = bmi088RawGyroToDegPerSec(raw_data_buffer[4], raw_data_buffer[5]);

    	*dest_gyro_x_raw = raw_data_buffer[0] | (raw_data_buffer[1] << 8);
		*dest_gyro_y_raw = raw_data_buffer[2] | (raw_data_buffer[3] << 8);
		*dest_gyro_z_raw = raw_data_buffer[4] | (raw_data_buffer[5] << 8);
    }

    return(r);
}
#endif








