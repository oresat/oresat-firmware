/**
 * @file    mmc5983ma.c
 * @brief   MMC5983MA Magnetometer
 *
 * @addtogroup MMC5983MA
 * @ingrup ORESAT
 * @{
 */

#include "ch.h"
#include "hal.h"
#include "mmc5983ma.h"
#include "string.h"
#include "chprintf.h"


#define DEBUG_SD    (BaseSequentialStream*) &SD2


/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/
#define MMC5983MA_DEFAULT_I2C_TIMEOUT      50
#define MMC5983MA_DATA_READ_I2C_TIMEOUT    250

#if (MMC5983MA_USE_I2C) || defined(__DOXYGEN__)

bool mmc5983maI2CWriteRegister2(I2CDriver *i2cp, const uint8_t reg_number, const uint8_t value) {
	uint8_t tx[2];
	tx[0] = reg_number;
	tx[1] = value;

    if( i2cMasterTransmitTimeout(i2cp, MMC5983MA_I2C_ADDRESS_WRITE, tx, 2, NULL, 0, MMC5983MA_DEFAULT_I2C_TIMEOUT) == MSG_OK ) {
    	return(true);
    }
    return(false);
}

bool mmc5983maI2CReadRegister2(I2CDriver *i2cp, const uint8_t reg_number, uint8_t *dest_value) {
	chprintf(DEBUG_SD, "MMC5983MA: reading register %u\r\n", reg_number);
	uint8_t tx[2];
	tx[0] = reg_number;
	tx[1] = 0;
	uint8_t rx[2];
	rx[0] = 0;
	rx[1] = 0;

    if( i2cMasterTransmitTimeout(i2cp, (i2caddr_t) MMC5983MA_I2C_ADDRESS_READ, tx, 1, rx, 1, MMC5983MA_DEFAULT_I2C_TIMEOUT) == MSG_OK ) {
    	*dest_value = rx[0];
    	return(true);
    }
    return(false);
}


bool mmc5983maI2CReadRegister3(I2CDriver *i2cp, const uint8_t i2c_address, const uint8_t reg_number, uint8_t *dest_value) {
	uint8_t tx[2];
	tx[0] = reg_number;
	tx[1] = 0;
	uint8_t rx[2];
	rx[0] = 0;
	rx[1] = 0;

    if( i2cMasterTransmitTimeout(i2cp, (i2caddr_t) i2c_address, tx, 1, rx, 1, MMC5983MA_DEFAULT_I2C_TIMEOUT) == MSG_OK ) {
    	*dest_value = rx[0];
    	return(true);
    }
    return(false);
}

bool mmc5983maI2CReadRegister4(I2CDriver *i2cp, const uint8_t i2c_address, const uint8_t reg_number, uint16_t *dest_value) {
	uint8_t tx[2];
	tx[0] = reg_number;
	tx[1] = 0;
	uint8_t rx[2];
	rx[0] = 0;
	rx[1] = 0;

    if( i2cMasterTransmitTimeout(i2cp, (i2caddr_t) i2c_address, tx, 1, rx, 2, MMC5983MA_DEFAULT_I2C_TIMEOUT) == MSG_OK ) {
    	*dest_value = rx[0] | rx[1];
    	return(true);
    }
    return(false);
}

#endif /* MMC5983MA_USE_I2C */

/*==========================================================================*/
/* Interface implementation.                                                */
/*==========================================================================*/

static const struct MMC5983MAVMT vmt_device = {
    (size_t)0,
};


/**
 * @brief   Initializes an instance.
 *
 * @param[out] devp     pointer to the @p MMC5983MADriver object
 *
 * @init
 */
void mmc5983maObjectInit(MMC5983MADriver *devp) {
    devp->vmt = &vmt_device;

    devp->config = NULL;

    devp->state = MMC5983MA_STOP;

    devp->bridge_offset_estimate_x = 0;
    devp->bridge_offset_estimate_y = 0;
    devp->bridge_offset_estimate_z = 0;
    devp->read_call_count = 0;
}


bool mmc5983maSoftReset(MMC5983MADriver *devp) {
	chprintf(DEBUG_SD, "Resetting MMC5983...\r\n");
	bool r = mmc5983maI2CWriteRegister2(devp->config->i2cp, MMC5983MA_CONTROL_1, MMC5983MA_CONTROL_1_SW_RST_CMD);
	chThdSleepMilliseconds(5);
	return(r);
}





/**
 * @brief   Configures and activates MMC5983MA Complex Driver peripheral.
 *
 * @param[in] devp      pointer to the @p MMC5983MADriver object
 * @param[in] config    pointer to the @p MMC5983MAConfig object
 *
 * @api
 */
uint8_t mmc5983ma_product_id_readback;

bool mmc5983maStart(MMC5983MADriver *devp, const MMC5983MAConfig *config) {
    osalDbgCheck((devp != NULL) && (config != NULL));
    osalDbgAssert((devp->state == MMC5983MA_STOP) ||
            (devp->state == MMC5983MA_READY),
            "mmc5983maStart(), invalid state");

    devp->config = config;

    /* Configuring common registers.*/
#if MMC5983MA_USE_I2C
#if MMC5983MA_SHARED_I2C
    i2cAcquireBus(config->i2cp);
#endif /* MMC5983MA_SHARED_I2C */

    i2cStart(config->i2cp, config->i2ccfg);

    devp->state = MMC5983MA_READY;


    bool found_mmc5983ma_flag = false;

    //Probe I2C bus to see what's attached
    if( ! mmc5983maI2CReadRegister3(devp->config->i2cp, MMC5983MA_I2C_ADDRESS_READ, MMC5983MA_PRODUCT_ID, &mmc5983ma_product_id_readback) ) {
    	chprintf(DEBUG_SD, "Failed to read product code from MMC5983MA chip, i2c comm failure\r\n");
    } else {
    	if( mmc5983ma_product_id_readback == MMC5983MA_EXPECTED_PRODUCT_CODE ) {
			chprintf(DEBUG_SD, "Successfully read product code from MMC5983MA (good), 0x%X\r\n", mmc5983ma_product_id_readback);
			found_mmc5983ma_flag = true;
    	} else {
    		chprintf(DEBUG_SD, "ERROR: unexpected product ID code from MMC5983MA, read 0x%X, expected 0x%X\r\n", mmc5983ma_product_id_readback, MMC5983MA_EXPECTED_PRODUCT_CODE);
    	}
    }

    if( found_mmc5983ma_flag ) {
		mmc5983maSoftReset(devp);

		if( ! mmc5983maI2CReadRegister2(devp->config->i2cp, MMC5983MA_PRODUCT_ID, &mmc5983ma_product_id_readback) ) {
			devp->state = MMC5983MA_STOP;
		} else {
			chprintf(DEBUG_SD, "Read MMC5983MA product code as 0x%X, expected 0x%X\r\n", mmc5983ma_product_id_readback, MMC5983MA_EXPECTED_PRODUCT_CODE);
			if( mmc5983ma_product_id_readback != MMC5983MA_EXPECTED_PRODUCT_CODE ) {
				chprintf(DEBUG_SD, "ERROR: Read incorrect MMC5983MA product code!!!\r\n");
				devp->state = MMC5983MA_STOP;
			}
		}

		if( devp->state == MMC5983MA_READY ) {

//			FIXME add init code for 1hz output rate

//			if( ! mmc5983maI2CWriteRegister2(devp->config->i2cp, MMC5983MA_CONTROL_1, )) {
//				devp->state = MMC5983MA_STOP;
//			}

			if( ! mmc5983maI2CWriteRegister2(devp->config->i2cp, MMC5983MA_CONTROL_2, MMC5983MA_CONTROL_2_CM_FREQ_1HZ)) {
				devp->state = MMC5983MA_STOP;
			}

			if( ! mmc5983maI2CWriteRegister2(devp->config->i2cp, MMC5983MA_CONTROL_0, MMC5983MA_CONTROL_0_TM_M)) {
				devp->state = MMC5983MA_STOP;
			}

		}
    } else {
    	devp->state = MMC5983MA_STOP;
    }

    i2cStop(devp->config->i2cp);

#if MMC5983MA_SHARED_I2C
    i2cReleaseBus(config->i2cp);
#endif /* MMC5983MA_SHARED_I2C */
#endif /* MMC5983MA_USE_I2C */


    return(devp->state == MMC5983MA_READY);
}

/**
 * @brief   Deactivates the MMC5983MA Complex Driver peripheral.
 *
 * @param[in] devp       pointer to the @p MMC5983MADriver object
 *
 * @api
 */
void mmc5983maStop(MMC5983MADriver *devp) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state == MMC5983MA_STOP) || (devp->state == MMC5983MA_READY),
            "mmc5983maStop(), invalid state");

    if (devp->state == MMC5983MA_READY) {
#if MMC5983MA_USE_I2C
#if MMC5983MA_SHARED_I2C
        i2cAcquireBus(devp->config->i2cp);
        i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* MMC5983MA_SHARED_I2C */

        //The MMC will be in low power mode after being reset
        mmc5983maSoftReset(devp);

        i2cStop(devp->config->i2cp);
#if MMC5983MA_SHARED_I2C
        i2cReleaseBus(devp->config->i2cp);
#endif /* MMC5983MA_SHARED_I2C */
#endif /* MMC5983MA_USE_I2C */
    }
    devp->state = MMC5983MA_STOP;
}




const char* msg_t_to_str(const msg_t v) {
    switch (v) {
    case MSG_OK:
        return ("MSG_OK");
    case MSG_TIMEOUT:
        return ("MSG_TIMEOUT");
    case MSG_RESET:
        return ("MSG_RESET");
    default:
        return ("MSG_???");
    }
}

int32_t mmc5983maRawToMilliGauss(const int16_t raw) {
	float gauss = 1000.0 * ((float) raw) / 4096.0;
	return(gauss);
}

bool mmc5983maReadData(MMC5983MADriver *devp, mmc5983ma_data_t *dest) {
	osalDbgCheck((devp != NULL));
//	osalDbgAssert((devp->state != MMC5983MA_READY),
//	            "mmc5983maStart(), invalid state");

	if( devp->state != MMC5983MA_READY ) {
//		chprintf(DEBUG_SD, "ERROR: MMC5983MA driver not in MMC5983MA_READY state\r\n");
		return(false);
	}

	devp->read_call_count++;

	bool ret = false;

    /* Configuring common registers.*/
#if MMC5983MA_USE_I2C
#if MMC5983MA_SHARED_I2C
    i2cAcquireBus(config->i2cp);
#endif /* MMC5983MA_SHARED_I2C */


    uint8_t rx[10];
    memset(rx, 0, sizeof(rx));

//    chprintf(DEBUG_SD, "MMC5983MA reading status register\r\n");chThdSleepMilliseconds(10);

    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
    bool r = mmc5983maI2CReadRegister2(devp->config->i2cp, MMC5983MA_STATUS, &rx[0]);
    i2cStop(devp->config->i2cp);

    if( ! r ) {
    	ret = false;

    } else if( rx[0] & MMC5983MA_STATUS_MEAS_M_DONE ) {
//    	chprintf(DEBUG_SD, "MMC5983MA status register = 0x%X\r\n", rx[0]);chThdSleepMilliseconds(10);

		memset(rx, 0, sizeof(rx));
//		uint8_t reg = MMC5983MA_XOUT_0;
		uint8_t tx[2];
		tx[0] = MMC5983MA_XOUT_0;
		tx[1] = 0;

//		chprintf(DEBUG_SD, "MMC5983MA reading data registers\r\n");chThdSleepMilliseconds(10);

		i2cStart(devp->config->i2cp, devp->config->i2ccfg);
		msg_t r = i2cMasterTransmitTimeout(devp->config->i2cp, MMC5983MA_I2C_ADDRESS_READ, tx, 1, rx, 7, MMC5983MA_DATA_READ_I2C_TIMEOUT);
		i2cStop(devp->config->i2cp);

		chprintf(DEBUG_SD, "MMC5983MA done reading data registers: (%d, %d, %d), r=%d (%s), state=%d\r\n", dest->mx, dest->my, dest->mz, r, msg_t_to_str(r), devp->state);chThdSleepMilliseconds(10);

		if( r == MSG_OK ) {
			//Note The data sheet says this is 4096 counts/gauss
			dest->mx = saturate_int32_t(((uint32_t) (rx[0] << 8) | rx[1]) - 32768, INT16_MIN, INT16_MAX);
			dest->my = saturate_int32_t(((uint32_t) (rx[2] << 8) | rx[3]) - 32768, INT16_MIN, INT16_MAX);
			dest->mz = saturate_int32_t(((uint32_t) (rx[4] << 8) | rx[5]) - 32768, INT16_MIN, INT16_MAX);
			ret = true;

			if( devp->read_call_count > 20 ) {
				//This will periodically clear any bias on the magnetometer
				devp->read_call_count = 0;

				i2cStart(devp->config->i2cp, devp->config->i2ccfg);
				if( ! mmc5983maI2CWriteRegister2(devp->config->i2cp, MMC5983MA_CONTROL_0, MMC5983MA_CONTROL_0_SET)) {

				}
				i2cStop(devp->config->i2cp);
				chThdSleepMilliseconds(1);

				tx[0] = MMC5983MA_XOUT_0;
				tx[1] = 0;
				memset(rx, 0, sizeof(rx));
				i2cStart(devp->config->i2cp, devp->config->i2ccfg);
				msg_t r = i2cMasterTransmitTimeout(devp->config->i2cp, MMC5983MA_I2C_ADDRESS_READ, tx, 1, rx, 7, MMC5983MA_DATA_READ_I2C_TIMEOUT);
				i2cStop(devp->config->i2cp);

				mmc5983ma_data_t dest_temp;
				dest_temp.mx = saturate_int32_t(((uint32_t) (rx[0] << 8) | rx[1]) - 32768, INT16_MIN, INT16_MAX);
				dest_temp.my = saturate_int32_t(((uint32_t) (rx[2] << 8) | rx[3]) - 32768, INT16_MIN, INT16_MAX);
				dest_temp.mz = saturate_int32_t(((uint32_t) (rx[4] << 8) | rx[5]) - 32768, INT16_MIN, INT16_MAX);


				const int32_t delta_set_reset_x = dest_temp.mx - dest->mx;
				const int32_t delta_set_reset_y = dest_temp.my - dest->my;
				const int32_t delta_set_reset_z = dest_temp.mz - dest->mz;

				const float bridge_offset_midpoint_x = ((float) delta_set_reset_x) / 2.0;
				const float bridge_offset_midpoint_y = ((float) delta_set_reset_y) / 2.0;
				const float bridge_offset_midpoint_z = ((float) delta_set_reset_z) / 2.0;

				//Modify tracked bridge offset estimate, but filter the data slightly.
				const float filter_coefficient = 4.0;
				devp->bridge_offset_estimate_x = devp->bridge_offset_estimate_x + ((bridge_offset_midpoint_x - devp->bridge_offset_estimate_x) / filter_coefficient);
				devp->bridge_offset_estimate_y = devp->bridge_offset_estimate_y + ((bridge_offset_midpoint_y - devp->bridge_offset_estimate_y) / filter_coefficient);
				devp->bridge_offset_estimate_z = devp->bridge_offset_estimate_z + ((bridge_offset_midpoint_z - devp->bridge_offset_estimate_z) / filter_coefficient);

				i2cStart(devp->config->i2cp, devp->config->i2ccfg);
				if( ! mmc5983maI2CWriteRegister2(devp->config->i2cp, MMC5983MA_CONTROL_0, MMC5983MA_CONTROL_0_RESET)) {

				}
				i2cStop(devp->config->i2cp);
				chThdSleepMilliseconds(1);
			}

			dest->mx += devp->bridge_offset_estimate_x;
			dest->my += devp->bridge_offset_estimate_y;
			dest->mz += devp->bridge_offset_estimate_z;
		} else {
			dest->mx = 0;
			dest->my = 0;
			dest->mz = 0;

			ret = false;
		}


//		chprintf(DEBUG_SD, "MMC5983MA starting new conversion\r\n");chThdSleepMilliseconds(10);
		// Start a new conversion
		i2cStart(devp->config->i2cp, devp->config->i2ccfg);
		if( ! mmc5983maI2CWriteRegister2(devp->config->i2cp, MMC5983MA_CONTROL_0, MMC5983MA_CONTROL_0_TM_M)) {
			devp->state = MMC5983MA_STOP;
		}
		i2cStop(devp->config->i2cp);
		chThdSleepMilliseconds(1);

    }

#if MMC5983MA_SHARED_I2C
    i2cReleaseBus(config->i2cp);
#endif /* MMC5983MA_SHARED_I2C */
#endif /* MMC5983MA_USE_I2C */

    return(ret);
}












