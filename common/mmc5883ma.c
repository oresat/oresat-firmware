/**
 * @file    mmc5883ma.c
 * @brief   MMC5883MA Magnetometer
 *
 * @addtogroup MMC5883MA
 * @ingrup ORESAT
 * @{
 */

#include "ch.h"
#include "hal.h"
#include "mmc5883ma.h"
#include "string.h"
#include "chprintf.h"

#define DEBUG_SD    (BaseSequentialStream*) &SD2

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/
//typedef union {
//    struct __attribute__((packed)) {
//        uint8_t reg;
//        union {
//            uint8_t data[2];
//            uint16_t value;
//        };
//    };
//    uint8_t buf[3];
//} i2cbuf_t;

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/
#define MMC5883MA_DEFAULT_I2C_TIMEOUT      50

#if (MMC5883MA_USE_I2C) || defined(__DOXYGEN__)

bool mmc5883maI2CWriteRegister2(I2CDriver *i2cp, const uint8_t reg_number, const uint8_t value) {
	uint8_t tx[2];
	tx[0] = reg_number;
	tx[1] = value;

    if( i2cMasterTransmitTimeout(i2cp, MMC5883MA_I2C_ADDRESS_WRITE, tx, 2, NULL, 0, MMC5883MA_DEFAULT_I2C_TIMEOUT) == MSG_OK ) {
    	return(true);
    }
    return(false);
}

bool mmc5883maI2CReadRegister2(I2CDriver *i2cp, const uint8_t reg_number, uint8_t *dest_value) {
	uint8_t tx[2];
	tx[0] = reg_number;
	tx[1] = 0;
	uint8_t rx[2];
	rx[0] = 0;
	rx[1] = 0;

    if( i2cMasterTransmitTimeout(i2cp, (i2caddr_t) MMC5883MA_I2C_ADDRESS_READ, tx, 1, rx, 1, MMC5883MA_DEFAULT_I2C_TIMEOUT) == MSG_OK ) {
    	*dest_value = rx[0];
    	return(true);
    }
    return(false);
}


bool mmc5883maI2CReadRegister3(I2CDriver *i2cp, const uint8_t i2c_address, const uint8_t reg_number, uint8_t *dest_value) {
	uint8_t tx[2];
	tx[0] = reg_number;
	tx[1] = 0;
	uint8_t rx[2];
	rx[0] = 0;
	rx[1] = 0;

    if( i2cMasterTransmitTimeout(i2cp, (i2caddr_t) i2c_address, tx, 1, rx, 1, MMC5883MA_DEFAULT_I2C_TIMEOUT) == MSG_OK ) {
    	*dest_value = rx[0];
    	return(true);
    }
    return(false);
}

bool mmc5883maI2CReadRegister4(I2CDriver *i2cp, const uint8_t i2c_address, const uint8_t reg_number, uint16_t *dest_value) {
	uint8_t tx[2];
	tx[0] = reg_number;
	tx[1] = 0;
	uint8_t rx[2];
	rx[0] = 0;
	rx[1] = 0;

    if( i2cMasterTransmitTimeout(i2cp, (i2caddr_t) i2c_address, tx, 1, rx, 2, MMC5883MA_DEFAULT_I2C_TIMEOUT) == MSG_OK ) {
    	*dest_value = rx[0] | rx[1];
    	return(true);
    }
    return(false);
}

#endif /* MMC5883MA_USE_I2C */

/*==========================================================================*/
/* Interface implementation.                                                */
/*==========================================================================*/

static const struct MMC5883MAVMT vmt_device = {
    (size_t)0,
};

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/


bool mmc5883maReadData(MMC5883MADriver *devp, mmc5883ma_data_t *dest) {
	osalDbgCheck((devp != NULL));
//	osalDbgAssert((devp->state != MMC5883MA_READY),
//	            "mmc5883maStart(), invalid state");

	if( devp->state != MMC5883MA_READY ) {
		return(false);
	}


	static uint32_t read_call_count = 0;
	read_call_count++;
	if( read_call_count > 20 ) {
		//This will periodically clear any bias on the magnetometer
		read_call_count = 0;

		if( ! mmc5883maI2CWriteRegister2(devp->config->i2cp, MMC5883MA_AD_INTRNLCTRL0, MMC5883MA_INTRNLCTRL0_SET)) {

		}
		chThdSleepMilliseconds(1);

		if( ! mmc5883maI2CWriteRegister2(devp->config->i2cp, MMC5883MA_AD_INTRNLCTRL0, MMC5883MA_INTRNLCTRL0_RST)) {

		}
		chThdSleepMilliseconds(1);
	}


	bool ret = false;

    /* Configuring common registers.*/
#if MMC5883MA_USE_I2C
#if MMC5883MA_SHARED_I2C
    i2cAcquireBus(config->i2cp);
#endif /* MMC5883MA_SHARED_I2C */


    uint8_t rx[10];
    memset(rx, 0, sizeof(rx));

    uint8_t reg = MMC5883MA_AD_XOUT_LOW;

    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
    msg_t r = i2cMasterTransmitTimeout(devp->config->i2cp, MMC5883MA_I2C_ADDRESS_READ, &reg, 1, rx, 6, MMC5883MA_DEFAULT_I2C_TIMEOUT);
    i2cStop(devp->config->i2cp);

	dest->mx = (rx[0] << 8) | rx[1];
	dest->my = (rx[2] << 8) | rx[3];
	dest->mz = (rx[4] << 8) | rx[5];

    if( r == MSG_OK ) {
    	ret = true;
    }

#if MMC5883MA_SHARED_I2C
    i2cReleaseBus(config->i2cp);
#endif /* MMC5883MA_SHARED_I2C */
#endif /* MMC5883MA_USE_I2C */

    return(ret);
}

/**
 * @brief   Initializes an instance.
 *
 * @param[out] devp     pointer to the @p MMC5883MADriver object
 *
 * @init
 */
void mmc5883maObjectInit(MMC5883MADriver *devp) {
    devp->vmt = &vmt_device;

    devp->config = NULL;

    devp->state = MMC5883MA_STOP;
}

bool mmc5883maSoftReset(MMC5883MADriver *devp) {
	chprintf(DEBUG_SD, "Resetting MMC4883...\r\n");
	bool r = mmc5883maI2CWriteRegister2(devp->config->i2cp, MMC5883MA_AD_INTRNLCTRL1, MMC5883MA_INTRNLCTRL1_SW_RST_CMD);
	chThdSleepMilliseconds(5);
	return(r);
}

/**
 * @brief   Configures and activates MMC5883MA Complex Driver peripheral.
 *
 * @param[in] devp      pointer to the @p MMC5883MADriver object
 * @param[in] config    pointer to the @p MMC5883MAConfig object
 *
 * @api
 */
uint8_t mmc_product_id_readback;

bool mmc5883maStart(MMC5883MADriver *devp, const MMC5883MAConfig *config) {
//    i2cbuf_t buf;

    osalDbgCheck((devp != NULL) && (config != NULL));
    osalDbgAssert((devp->state == MMC5883MA_STOP) ||
            (devp->state == MMC5883MA_READY),
            "mmc5883maStart(), invalid state");

    devp->config = config;

    /* Configuring common registers.*/
#if MMC5883MA_USE_I2C
#if MMC5883MA_SHARED_I2C
    i2cAcquireBus(config->i2cp);
#endif /* MMC5883MA_SHARED_I2C */

    i2cStart(config->i2cp, config->i2ccfg);

    devp->state = MMC5883MA_READY;


    bool found_mmc5883ma_flag = false;

    //Probe I2C bus to see what's attached
    if( ! mmc5883maI2CReadRegister3(devp->config->i2cp, MMC5883MA_I2C_ADDRESS_READ, MMC5883MA_AD_PRDCT_ID_1, &mmc_product_id_readback) ) {
    	chprintf(DEBUG_SD, "Failed to read product code from MMC5883MA chip, i2c comm failure\r\n");
    } else {
    	if( mmc_product_id_readback == MMC5883MA_EXPECTED_PRODUCT_CODE ) {
			chprintf(DEBUG_SD, "Successfully read product code from MMC5883MA (good), 0x%X\r\n", mmc_product_id_readback);
			found_mmc5883ma_flag = true;
    	} else {
    		chprintf(DEBUG_SD, "ERROR: unexpected product ID code from MMC5883MA, read 0x%X, expectex 0x%X\r\n", mmc_product_id_readback, MMC5883MA_EXPECTED_PRODUCT_CODE);
    	}
    }

    if( found_mmc5883ma_flag ) {
		mmc5883maSoftReset(devp);

		if( ! mmc5883maI2CReadRegister2(devp->config->i2cp, MMC5883MA_AD_PRDCT_ID_1, &mmc_product_id_readback) ) {
			devp->state = MMC5883MA_STOP;
		} else {
			chprintf(DEBUG_SD, "Read MMC5883MA product code as 0x%X, expected 0x%X\r\n", mmc_product_id_readback, MMC5883MA_EXPECTED_PRODUCT_CODE);
			if( mmc_product_id_readback != MMC5883MA_EXPECTED_PRODUCT_CODE ) {
				chprintf(DEBUG_SD, "ERROR: Read incorrect MMC5883MA product code!!!\r\n");
				devp->state = MMC5883MA_STOP;
			}
		}

		if( devp->state == MMC5883MA_READY ) {
			if( ! mmc5883maI2CWriteRegister2(devp->config->i2cp, MMC5883MA_AD_INTRNLCTRL2, MMC5883MA_INTRNLCTRL2_CM_FREQ_1_Hz)) {
				devp->state = MMC5883MA_STOP;
			}
		}
    } else {
    	devp->state = MMC5883MA_STOP;
    }

    i2cStop(devp->config->i2cp);

#if MMC5883MA_SHARED_I2C
    i2cReleaseBus(config->i2cp);
#endif /* MMC5883MA_SHARED_I2C */
#endif /* MMC5883MA_USE_I2C */


    return(devp->state == MMC5883MA_READY);
}

/**
 * @brief   Deactivates the MMC5883MA Complex Driver peripheral.
 *
 * @param[in] devp       pointer to the @p MMC5883MADriver object
 *
 * @api
 */
void mmc5883maStop(MMC5883MADriver *devp) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state == MMC5883MA_STOP) || (devp->state == MMC5883MA_READY),
            "mmc5883maStop(), invalid state");

    if (devp->state == MMC5883MA_READY) {
#if MMC5883MA_USE_I2C
#if MMC5883MA_SHARED_I2C
        i2cAcquireBus(devp->config->i2cp);
        i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* MMC5883MA_SHARED_I2C */

        //The MMC will be in low power mode after being reset
        mmc5883maSoftReset(devp);

        i2cStop(devp->config->i2cp);
#if MMC5883MA_SHARED_I2C
        i2cReleaseBus(devp->config->i2cp);
#endif /* MMC5883MA_SHARED_I2C */
#endif /* MMC5883MA_USE_I2C */
    }
    devp->state = MMC5883MA_STOP;
}



/** @} */
