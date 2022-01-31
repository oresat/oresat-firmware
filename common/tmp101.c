/**
 * @file    tmp101.c
 * @brief   TMP101 temperature sensor
 *
 * @addtogroup TMP101
 * @ingrup ORESAT
 * @{
 */

#include "hal.h"
#include "tmp101.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

#if (TMP101_USE_I2C) || defined(__DOXYGEN__)
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
msg_t tmp101I2CReadRegister(I2CDriver *i2cp, i2caddr_t sad, uint8_t reg, uint8_t* rxbuf, size_t n) {
    return i2cMasterTransmitTimeout(i2cp, sad, &reg, 1, rxbuf, n, TIME_MS2I(50));
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
msg_t tmp101I2CWriteRegister(I2CDriver *i2cp, i2caddr_t sad, uint8_t *txbuf, size_t n) {
    return i2cMasterTransmitTimeout(i2cp, sad, txbuf, n, NULL, 0, TIME_MS2I(50));
}

/**
 * TODO document this
 */
msg_t tmp101I2CReadRegister2(TMP101Driver *devp, const uint8_t reg, uint8_t *dest_2_byte_array)
{
    const uint8_t sensor_addr = devp->config->saddr;

// Prepare for I2C transaction:
#if TMP101_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
#endif /* TMP101_SHARED_I2C */
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);

    const msg_t i2c_result = tmp101I2CReadRegister(devp->config->i2cp, sensor_addr, reg, dest_2_byte_array, 2);

    i2cStop(devp->config->i2cp);

#if TMP101_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* TMP101_SHARED_I2C */

    return i2c_result;
}


/*==========================================================================*/
/* Interface implementation.                                                */
/*==========================================================================*/

static const struct TMP101VMT vmt_device = {
    (size_t)0,
};

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Initializes an instance.
 *
 * @param[out] devp     pointer to the @p TMP101Driver object
 *
 * @init
 */
void tmp101ObjectInit(TMP101Driver *devp) {
    devp->vmt = &vmt_device;
    devp->config = NULL;
    devp->state = TMP101_STOP;
}

/**
 * @brief   Configures and activates TMP101 Complex Driver peripheral.
 *
 * @param[in] devp      pointer to the @p TMP101Driver object
 * @param[in] config    pointer to the @p TMP101Config object
 *
 * @api
 */
void tmp101Start(TMP101Driver *devp, const TMP101Config *config) {
    osalDbgCheck((devp != NULL) && (config != NULL));
    osalDbgAssert((devp->state == TMP101_STOP) ||
            (devp->state == TMP101_READY),
            "tmp101Start(), invalid state");

    devp->config = config;

    /* Configuring common registers, or at minimum start I2C bus. */
#if TMP101_USE_I2C
#if TMP101_SHARED_I2C
    i2cAcquireBus(config->i2cp);
#endif /* TMP101_SHARED_I2C */
    i2cStart(config->i2cp, config->i2ccfg);

#if TMP101_SHARED_I2C
    i2cReleaseBus(config->i2cp);
#endif /* TMP101_SHARED_I2C */
#endif /* TMP101_USE_I2C */

    devp->state = TMP101_READY;
}

/**
 * @brief   Deactivates the TMP101 Complex Driver peripheral.
 *
 * @param[in] devp       pointer to the @p TMP101Driver object
 *
 * @api
 */
void tmp101Stop(TMP101Driver *devp) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state == TMP101_STOP) || (devp->state == TMP101_READY),
            "tmp101Stop(), invalid state");

    if (devp->state == TMP101_READY) {
#if TMP101_USE_I2C
#if TMP101_SHARED_I2C
        i2cAcquireBus(devp->config->i2cp);
#endif /* TMP101_SHARED_I2C */
        i2cStop(devp->config->i2cp);
#if TMP101_SHARED_I2C
        i2cReleaseBus(devp->config->i2cp);
#endif /* TMP101_SHARED_I2C */
#endif /* TMP101_USE_I2C */
    }

    devp->state = TMP101_STOP;
}


//----------------------------------------------------------------------
// @brief   routine to read TMP101 temperature sensor, and return a
//          two-byte reading
//----------------------------------------------------------------------
msg_t tmp101ReadTemperature(TMP101Driver *devp, int16_t *dest_temp_c, int32_t *dest_temp_mC)
{
	uint8_t byte_array[2];

	const msg_t i2c_result = tmp101I2CReadRegister2(devp, TMP101_REG_TEMPERATURE, byte_array);

	if( i2c_result == MSG_OK ) {
		//chprintf((BaseSequentialStream *) &SD2, "byte_array[0] = 0x%X byte_array[1] = 0x%X\r\n", byte_array[0], byte_array[1]);

		uint16_t tmp = (byte_array[0] << 4) | ((byte_array[1] >> 4) & 0x0F);
		if( tmp & (1<<11) ) {
			//Convert 12 bit negative 2's compliment to 16 bit 2's compliment
			tmp |= 0xF000;
		}
		//0.0625 deg C per LSB
		int16_t tmp_signed = tmp;

		if( dest_temp_c != NULL ) {
			*dest_temp_c = (((int32_t) tmp_signed) * 62500) / 1000000;
		}

		if( dest_temp_mC != NULL ) {
			*dest_temp_mC = (((int32_t) tmp_signed) * 62500) / 1000;
		}
	} else {
		*dest_temp_c = 0;
		*dest_temp_mC = 0;
	}

    return i2c_result;
}


#endif /* TMP101_USE_I2C */

/** @} */
