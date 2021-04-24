/**
 * @file    max17205.c
 * @brief   MAX17205 Digital to Analog Converter.
 *
 * @addtogroup MAX17205
 * @ingrup ORESAT
 * @{
 */

#include "hal.h"
#include "max17205.h"

#if 1
#include "chprintf.h"
#define dbgprintf(str, ...)       chprintf((BaseSequentialStream*) &SD2, str, ##__VA_ARGS__)
#else
#define dbgprintf(str, ...)
#endif

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

#if (MAX17205_USE_I2C) || defined(__DOXYGEN__)

/**
 * See page 85 of the data sheet
 */
msg_t max17205NonvolatileBlockProgram(const MAX17205Config *config) {
	i2cbuf_t buf;
	msg_t r;

	//	1. Write desired memory locations to new values.
	//should be done prior to calling this function

	dbgprintf("Clearing CommStat.NVError bit\r\n");
	//	2. Clear CommStat.NVError bit.
	buf.reg = MAX17205_AD(MAX17205_AD_COMMSTAT);
	buf.value = MAX17205_COMMSTAT_NVERROR;
	if( (r = max17205I2CWriteRegister(config->i2cp, MAX17205_SA(MAX17205_AD_COMMSTAT), buf.buf, sizeof(buf.buf))) != MSG_OK ) {
		return(r);
	}

	//	3. Write 0xE904 to the Command register 0x060 to initiate a block copy.
	buf.reg = MAX17205_AD(MAX17205_AD_COMMAND);
	buf.value = 0xE904;
	if( (r = max17205I2CWriteRegister(config->i2cp, MAX17205_SA(MAX17205_AD_COMMAND), buf.buf, sizeof(buf.buf))) != MSG_OK ) {
		dbgprintf("Initiated failed to send command to initiate block copy....\r\n");
		return(r);
	} else {
		dbgprintf("Initiated MAX17205 block copy....\r\n");
	}


	//	4. Wait t BLOCK for the copy to complete.

	dbgprintf("Waiting %u ms for block copy to complete....\r\n", MAX17205_T_BLOCK_MS);
	chThdSleepMilliseconds(MAX17205_T_BLOCK_MS); //tBlock(max) is specified as 7360ms in the data sheet, page 16


	bool successful_block_copy_flag = false;
	//	5. Check the CommStat.NVError bit. If set, repeat the process. If clear, continue.
	if( (r = max17205I2CReadRegister(config->i2cp, MAX17205_SA(MAX17205_AD_COMMAND), MAX17205_AD(MAX17205_AD_COMMSTAT), buf.data, sizeof(buf.data))) != MSG_OK ) {
		dbgprintf("Failed to query COMMSTAT register...\r\n");
		return(r);
	} else {
		dbgprintf("Read MAX17205_AD_COMMSTAT register 0x%X as 0x%X\r\n", MAX17205_AD_COMMSTAT, buf.value);
		if( buf.value & MAX17205_COMMSTAT_NVERROR ) {
			//Error bit is set
			dbgprintf("Block copy failed...\r\n");
		} else {
			dbgprintf("Block copy was successful, breaking...\r\n");
			successful_block_copy_flag = true;
		}
	}

	if( ! successful_block_copy_flag ) {
		return(MSG_RESET);
	}


	//	6. Write 0x000F to the Command register 0x060 to POR the IC.
	//	7. Wait t POR for the IC to reset.
	//	8. Write 0x0001 to Counter Register 0x0BB to reset firmware.
	//	9. Wait t POR for the firmware to restart.
	if( (r = max17205HardwareReset(config->i2cp)) != MSG_OK ) {
		dbgprintf("Failed to reset MAX17205\r\n");
		return(r);
	}

	return(MSG_OK);
}



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
msg_t max17205I2CReadRegister(I2CDriver *i2cp, i2caddr_t sad, uint8_t reg,
        uint8_t* rxbuf, size_t n) {
    return i2cMasterTransmitTimeout(i2cp, sad, &reg, 1, rxbuf, n,
            TIME_MS2I(50));
}

/**
 * @brief   Writes a value into a register using I2C.
 * @pre     The I2C interface must be initialized and the driver started.
 *
 * @param[in] i2cp       pointer to the I2C interface
 * @param[in] sad        slave address without R bit
 * @param[in] txbuf      buffer containing command in first byte and high
 *                       and low data bytes
 * @param[in] n          size of txbuf
 * @return               the operation status.
 * @notapi
 */
msg_t max17205I2CWriteRegister(I2CDriver *i2cp, i2caddr_t sad, uint8_t *txbuf,
        size_t n) {
    return i2cMasterTransmitTimeout(i2cp, sad, txbuf, n, NULL, 0,
    		TIME_MS2I(50));
}
#endif /* MAX17205_USE_I2C */

/*==========================================================================*/
/* Interface implementation.                                                */
/*==========================================================================*/

static const struct MAX17205VMT vmt_device = {
    (size_t)0,
};

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Initializes an instance.
 *
 * @param[out] devp     pointer to the @p MAX17205Driver object
 *
 * @init
 */
void max17205ObjectInit(MAX17205Driver *devp) {
    devp->vmt = &vmt_device;

    devp->config = NULL;

    devp->state = MAX17205_STOP;
}

msg_t max17205HardwareReset(I2CDriver *i2cp) {
	i2cbuf_t buf;
	msg_t r;

	dbgprintf("Reseting MAX17205...\r\n");

	buf.reg = MAX17205_AD(MAX17205_AD_COMMAND);
	buf.value = MAX17205_COMMAND_HARDWARE_RESET;
	if( (r = max17205I2CWriteRegister(i2cp, MAX17205_SA(MAX17205_AD_COMMAND), buf.buf, sizeof(buf))) != MSG_OK ) {
		dbgprintf("Cmd register write failed...\r\n");
		//return(r);
	}
	chThdSleepMilliseconds(10);

	uint32_t check_count = 0;
	do {
		if( max17205I2CReadRegister(i2cp, MAX17205_SA(MAX17205_AD_COMMAND), MAX17205_AD(MAX17205_AD_STATUS), buf.data, sizeof(buf.data)) != MSG_OK ) {
			//do nothing
			dbgprintf("Waiting for MAX17205 to complete reset...\r\n");
			chThdSleepMilliseconds(10);
		}
		check_count++;
	} while (!(buf.value & MAX17205_STATUS_POR) && check_count < 10); /* While still resetting */

	//FIXME doesn't handle failure to POR properly
	return(MSG_OK);
}

/**
 * @brief   Configures and activates MAX17205 Complex Driver peripheral.
 *
 * @param[in] devp      pointer to the @p MAX17205Driver object
 * @param[in] config    pointer to the @p MAX17205Config object
 *
 * @api
 */
bool max17205Start(MAX17205Driver *devp, const MAX17205Config *config) {
    i2cbuf_t buf;
    uint32_t comm_error_count = 0;

    osalDbgCheck((devp != NULL) && (config != NULL));
    osalDbgAssert((devp->state == MAX17205_STOP) ||
            (devp->state == MAX17205_READY),
            "max17205Start(), invalid state");

    devp->config = config;

    /* Configuring common registers.*/
#if MAX17205_USE_I2C
#if MAX17205_SHARED_I2C
    i2cAcquireBus(config->i2cp);
#endif /* MAX17205_SHARED_I2C */

    i2cStart(config->i2cp, config->i2ccfg);

    /* Reset device */
#if 0
    max17205HardwareReset(config->i2cp);
#endif


#if 0
    //Read npkgcfg         0xA02
    if( max17205I2CReadRegister(config->i2cp, MAX17205_SA(MAX17205_AD_COMMAND), MAX17205_AD(MAX17205_AD_PACKCFG), buf.data, sizeof(buf.data)) == MSG_OK ) {
		dbgprintf("Read MAX17205_AD_PACKCFG register 0x%X as 0x%X\r\n", MAX17205_AD_PACKCFG, buf.value);
	}
#endif



    buf.reg = MAX17205_AD(MAX17205_AD_CONFIG2);
    buf.value = MAX17205_SETVAL(MAX17205_AD_CONFIG2, MAX17205_CONFIG2_POR_CMD);
    if( max17205I2CWriteRegister(config->i2cp, MAX17205_SA(MAX17205_AD_CONFIG2), buf.buf, sizeof(buf)) != MSG_OK ) {
    	comm_error_count++;
    }

    for (const max17205_regval_t *pair = config->regcfg; pair->reg; pair++) {
        buf.reg = MAX17205_AD(pair->reg);
        buf.value = pair->value;

        dbgprintf("Setting MAX17205 register 0x%X to 0x%X\r\n", buf.reg, buf.value);

        if( max17205I2CWriteRegister(config->i2cp, MAX17205_SA(pair->reg), buf.buf, sizeof(buf)) != MSG_OK ) {
        	comm_error_count++;
        }
    }

#if MAX17205_SHARED_I2C
    i2cReleaseBus(config->i2cp);
#endif /* MAX17205_SHARED_I2C */
#endif /* MAX17205_USE_I2C */

    if( comm_error_count == 0 ) {
    	devp->state = MAX17205_READY;
    	return(true);
    } else {
    	devp->state = MAX17205_UNINIT;
    }
    return(false);
}

/**
 * @brief   Deactivates the MAX17205 Complex Driver peripheral.
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 *
 * @api
 */
void max17205Stop(MAX17205Driver *devp) {
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state == MAX17205_STOP) || (devp->state == MAX17205_READY),
            "max17205Stop(), invalid state");

    if (devp->state == MAX17205_READY) {
#if MAX17205_USE_I2C
#if MAX17205_SHARED_I2C
        i2cAcquireBus(devp->config->i2cp);
        i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* MAX17205_SHARED_I2C */

        /* Reset device */
        buf.reg = MAX17205_AD(MAX17205_AD_COMMAND);
        buf.value = MAX17205_COMMAND_HARDWARE_RESET;
        max17205I2CWriteRegister(devp->config->i2cp, MAX17205_SA(MAX17205_AD_COMMAND), buf.buf, sizeof(buf));
        buf.reg = MAX17205_AD(MAX17205_AD_CONFIG2);
        buf.value = MAX17205_SETVAL(MAX17205_AD_CONFIG2, MAX17205_CONFIG2_POR_CMD);
        max17205I2CWriteRegister(devp->config->i2cp, MAX17205_SA(MAX17205_AD_CONFIG2), buf.buf, sizeof(buf));

        i2cStop(devp->config->i2cp);
#if MAX17205_SHARED_I2C
        i2cReleaseBus(devp->config->i2cp);
#endif /* MAX17205_SHARED_I2C */
#endif /* MAX17205_USE_I2C */
    }
    devp->state = MAX17205_STOP;
}

/**
 * @brief   Reads MAX17205 register as raw value.
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 * @param[in] reg        the register to read
 *
 * @api
 */
msg_t max17205ReadRaw(MAX17205Driver *devp, uint16_t reg, uint16_t *output_dest) {
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == MAX17205_READY,
            "max17205ReadRaw(), invalid state");

#if MAX17205_USE_I2C
#if MAX17205_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* MAX17205_SHARED_I2C */

    buf.reg = MAX17205_AD(reg);

    const msg_t r = max17205I2CReadRegister(devp->config->i2cp, MAX17205_SA(reg), buf.reg, buf.data, sizeof(buf.data));

    //dbgprintf("max17205I2CReadRegister(0x%X), r = %d", reg, r);

#if MAX17205_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* MAX17205_SHARED_I2C */
#endif /* MAX17205_USE_I2C */

    if( r == MSG_OK ) {
    	*output_dest = buf.value;
    	//dbgprintf(" value = %u 0x%X", buf.value, buf.value);
    }
    //dbgprintf("\r\n");

    return(r);
}

/**
 * @brief   Writes MAX17205 register as raw value.
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 * @param[in] reg        the register to write to
 * @param[in] value      the value to write
 *
 * @api
 */
msg_t max17205WriteRaw(MAX17205Driver *devp, uint16_t reg, uint16_t value) {
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == MAX17205_READY,
            "max17205WriteRaw(), invalid state");

#if MAX17205_USE_I2C
#if MAX17205_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* MAX17205_SHARED_I2C */

    buf.reg = MAX17205_AD(reg);
    buf.value = value;
    const msg_t r = max17205I2CWriteRegister(devp->config->i2cp, MAX17205_SA(reg), buf.buf, sizeof(buf));

#if MAX17205_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* MAX17205_SHARED_I2C */
#endif /* MAX17205_USE_I2C */

    return(r);
}


/**
 * @brief   Reads an MAX17205 capacity value from a register in mAh.
 * @pre     nRSENSE register must be set to a value with a LSB of 10uOhm
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 * @param[in] reg        the register to read from
 *
 * @api
 */
msg_t max17205ReadCapacity(MAX17205Driver *devp, const uint16_t reg, uint16_t *dest)
{
	uint16_t reg_value = 0;
	const msg_t r = max17205ReadRaw(devp, reg, &reg_value);

	if( r == MSG_OK ) {
		uint16_t nr_sense_value = 0;

		const msg_t r2 = max17205ReadRaw(devp, MAX17205_AD_NRSENSE, &nr_sense_value);
		if( r2 == MSG_OK ) {
			*dest = reg_value * 5000U / MAX17205_REG2RSENSE(nr_sense_value);

			dbgprintf("  max17205ReadCapacityChecked(0x%X %s) = %u mAh (raw: %u 0x%X)\r\n", reg, max17205RegToStr(reg), *dest, reg_value, reg_value);
		} else {
			return(r2);
		}
	} else {
		return(r);
	}

	return(MSG_OK);
}


/**
 * @brief   Reads an MAX17205 percentage value from a register in 1% increments.
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 * @param[in] reg        the register to read from
 *
 * @api
 */
msg_t max17205ReadPercentage(MAX17205Driver *devp, uint16_t reg, uint16_t *dest)
{
	uint16_t temp = 0;
    msg_t r = max17205ReadRaw(devp, reg, &temp);

    if( r == MSG_OK ) {
    	*dest = temp / 256U;
    	dbgprintf("  max17205ReadPercentageChecked(0x%X %s) = %u%% (raw: %u 0x%X)\r\n", reg, max17205RegToStr(reg), *dest, temp, temp);
    }
    return(r);
}


/**
 * @brief   Reads an MAX17205 voltage value from a register in mV.
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 * @param[in] reg        the register to read from
 *
 * @api
 */
msg_t max17205ReadVoltage(MAX17205Driver *devp, uint16_t reg, uint16_t *dest)
{
	uint16_t temp = 0;
	msg_t r = max17205ReadRaw(devp, reg, &temp);

	if( r == MSG_OK ) {
		//Output is in millivolts. LSB unit is 0.078125mV
		*dest = (((uint32_t) temp) * 78125U) / 1000000U;
		dbgprintf("  max17205ReadVoltageChecked(0x%X %s) = %u mV\r\n", reg, max17205RegToStr(reg), *dest);
	}
	return(r);
}

/**
 * @brief   Reads an MAX17205 voltage value from a register in mV.
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 * @param[in] reg        the register to read from
 *
 * @api
 */
msg_t max17205ReadBattVoltage(MAX17205Driver *devp, uint16_t reg, uint16_t *dest)
{
	uint16_t temp = 0;
	msg_t r = max17205ReadRaw(devp, reg, &temp);

	if( r == MSG_OK ) {
		//Output is in millivolts. LSB unit is 1.25mV
		*dest = (((uint32_t) temp) * 125U) / 100U;
		dbgprintf("  max17205ReadBattVoltage(0x%X %s) = %u mV\r\n", reg, max17205RegToStr(reg), *dest);
	}
	return(r);
}


/**
 * @brief   Reads an MAX17205 current value from a register in mA.
 * @pre     nRSENSE register must be set to a value with a LSB of 10uOhm
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 * @param[in] reg        the register to read from
 *
 * @api
 */
msg_t max17205ReadCurrent(MAX17205Driver *devp, uint16_t reg, int16_t *dest)
{
	uint16_t temp = 0;
	msg_t r = max17205ReadRaw(devp, reg, &temp);

	if( r == MSG_OK ) {
		int16_t temp_signed = temp;
		//Assumes Rsense = 0.01 ohms
		*dest = ((int32_t)temp_signed * 15625) / 100000;// 156.25 uA / 100 / 1000 uA/mA

		dbgprintf("  max17205ReadCurrent(0x%X %s) = %d mA (raw: %d 0x%X)\r\n", reg, max17205RegToStr(reg), *dest, temp_signed, temp);
	}
	return(r);
}


/**
 * @brief   Reads an MAX17205 temperature value from a register in 0.001C increments.
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 * @param[in] reg        the register to read from
 *
 * @api
 */
msg_t max17205ReadTemperature(MAX17205Driver *devp, uint16_t reg, int16_t *dest)
{
	uint16_t temp = 0;
	msg_t r = max17205ReadRaw(devp, reg, &temp);
	if( r == MSG_OK ) {
		int16_t temp_signed = temp;

		*dest = temp_signed * 1000U / 256U;
		dbgprintf("  max17205ReadTemperatureChecked(0x%X %s) = %d mC (%u C) (raw: %d 0x%X)\r\n", reg, max17205RegToStr(reg), *dest, (*dest / 1000), temp_signed, temp);
	}
    return(r);
}

/**
 * @brief   Reads an MAX17205 temperature value from a register in 1C increments.
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 * @param[in] reg        the register to read from
 *
 * @api
 */
msg_t max17205ReadAverageTemperature(MAX17205Driver *devp, uint16_t reg, int16_t *dest)
{
	uint16_t temp = 0;
	msg_t r = max17205ReadRaw(devp, reg, &temp);
	if( r == MSG_OK ) {
		int16_t temp_signed = temp;

		*dest = (temp_signed / 10) - 273;
		dbgprintf("  max17205ReadTemperatureChecked(0x%X %s) = %d C (raw: %d 0x%X)\r\n", reg, max17205RegToStr(reg), *dest, temp_signed, temp);
	}
    return(r);
}

/**
 * @brief   Reads an MAX17205 resistance value from a register in mOhms.
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 * @param[in] reg        the register to read from
 *
 * @api
 */
/*
inline uint16_t max17205ReadResistance(MAX17205Driver *devp, uint16_t reg)
{
    return max17205ReadRaw(devp, reg) * 1000U / 4096U;
}
*/

msg_t max17205ReadResistance(MAX17205Driver *devp, uint16_t reg, uint16_t *dest)
{
	uint16_t temp;
	msg_t r = max17205ReadRaw(devp, reg, &temp);
	if( r == MSG_OK ) {
		*dest = temp * 1000U / 4096U;
	}

	return(r);
}

/**
 * @brief   Reads an MAX17205 time value from a register in seconds.
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 * @param[in] reg        the register to read from
 *
 * @api
 */
msg_t max17205ReadTime(MAX17205Driver *devp, uint16_t reg, uint16_t *dest)
{
	uint16_t temp = 0;
    msg_t r = max17205ReadRaw(devp, reg, &temp);
    if( r == MSG_OK ) {
    	*dest = temp * 5625U / 1000;

    	uint16_t minutes = *dest / 60;
    	dbgprintf("  max17205ReadTimeChecked(0x%X %s) = %u seconds (%u minutes) (raw: %u 0x%X)\r\n", reg, max17205RegToStr(reg), *dest, minutes, temp, temp);
    }
    return(r);
}

/**
 * The MAX17205 allows for the NV ram to be written no more then 7 times on a single chip. Each time, an additional bit is set in a flash register which can be queried.
 *
 * TODO document this
 */
msg_t max17205ReadNVWriteCountMaskingRegister(const MAX17205Config *config, uint16_t *reg_dest, uint8_t *number_of_writes_left) {
	//Determine the number of times NV memory has been written on this chip.
	//See page 85 of the data sheet

	dbgprintf("Reading NV Masking register...\r\n");
	i2cbuf_t buf;

	buf.reg = MAX17205_AD_COMMAND;
	buf.value = 0xE2FA;
	if( max17205I2CWriteRegister(config->i2cp, MAX17205_SA(MAX17205_AD_COMMAND), buf.buf, sizeof(buf.buf)) == MSG_OK ) {
		chThdSleepMilliseconds(MAX17205_T_RECAL_MS);

		if( max17205I2CReadRegister(config->i2cp, MAX17205_SA(0x1ED), 0xED, buf.data, sizeof(buf.data)) == MSG_OK ) {
			uint8_t mm = (buf.value & 0xFF) & ((buf.value >> 8) & 0xFF);
			dbgprintf("Memory Update Masking of register 0x%X is 0x%X\r\n", 0x1ED, mm);

			uint8_t num_left = 7;
			for(uint8_t i = 0; i < 8; i++) {
				if( buf.value & (1<<i) && num_left > 0) {
					num_left--;
				}
			}

			*reg_dest = buf.value;
			*number_of_writes_left = num_left;
			return(MSG_OK);
		}
	}

	return(MSG_TIMEOUT);
}

/**
 * TODO document this
 */
msg_t max17205PrintintNonvolatileMemory(const MAX17205Config *config) {
	i2cbuf_t buf;


	uint16_t masking_register = 0;
	uint8_t num_left = 0;
	if( max17205ReadNVWriteCountMaskingRegister(config, &masking_register, &num_left) == MSG_OK ) {

	}


	dbgprintf("\r\nMAX17205 *Volatile* Registers\r\n");
	uint16_t volatile_reg_list[] = {
			MAX17205_AD_PACKCFG,
			MAX17205_AD_DESIGNCAP,
			MAX17205_AD_NRSENSE,
			0
	};

	for(int i = 0; volatile_reg_list[i] != 0;i++) {
		if( max17205I2CReadRegister(config->i2cp, MAX17205_SA(MAX17205_AD_COMMAND), MAX17205_AD(volatile_reg_list[i]), buf.data, sizeof(buf.data)) == MSG_OK ) {
			dbgprintf("   %-30s register 0x%X is 0x%X\r\n", max17205RegToStr(volatile_reg_list[i]), volatile_reg_list[i], buf.value);
		}
	}


	//See table 19 on page 83 of the data sheet to see the list of non-volatile registers
	dbgprintf("\r\nMAX17205 Non-Volatile Registers\r\n");
	uint16_t reg_list[] = {
			MAX17205_AD_NXTABLE0,
			MAX17205_AD_NXTABLE1,
			MAX17205_AD_NXTABLE2,
			MAX17205_AD_NXTABLE3,
			MAX17205_AD_NXTABLE4,
			MAX17205_AD_NXTABLE5,
			MAX17205_AD_NXTABLE6,
			MAX17205_AD_NXTABLE7,
			MAX17205_AD_NXTABLE8,
			MAX17205_AD_NXTABLE9,
			MAX17205_AD_NXTABLE10,
			MAX17205_AD_NXTABLE11,
			MAX17205_AD_NUSER18C,
			MAX17205_AD_NUSER18D,
			MAX17205_AD_NODSCTH,
			MAX17205_AD_NODSCCFG,
			MAX17205_AD_NOCVTABLE0,
			MAX17205_AD_NOCVTABLE1,
			MAX17205_AD_NOCVTABLE2,
			MAX17205_AD_NOCVTABLE3,
			MAX17205_AD_NOCVTABLE4,
			MAX17205_AD_NOCVTABLE5,
			MAX17205_AD_NOCVTABLE6,
			MAX17205_AD_NOCVTABLE7,
			MAX17205_AD_NOCVTABLE8,
			MAX17205_AD_NOCVTABLE9,
			MAX17205_AD_NOCVTABLE10,
			MAX17205_AD_NOCVTABLE11,
			MAX17205_AD_NICHGTERM,
			MAX17205_AD_NFILTERCFG,
			MAX17205_AD_NVEMPTY,
			MAX17205_AD_NLEARNCFG,
			MAX17205_AD_NQRTABLE00,
			MAX17205_AD_NQRTABLE10,
			MAX17205_AD_NQRTABLE20,
			MAX17205_AD_NQRTABLE30,
			MAX17205_AD_NCYCLES,
			MAX17205_AD_NFULLCAPNOM,
			MAX17205_AD_NRCOMP0,
			MAX17205_AD_NTEMPCO,
			MAX17205_AD_NIAVGEMPTY,
			MAX17205_AD_NFULLCAPREP,
			MAX17205_AD_NVOLTTEMP,
			MAX17205_AD_NMAXMINCURR,
			MAX17205_AD_NMAXMINVOLT,
			MAX17205_AD_NMAXMINTEMP,
			MAX17205_AD_NSOC,
			MAX17205_AD_NTIMERH,
			MAX17205_AD_NCONFIG,
			MAX17205_AD_NRIPPLECFGCFG,
			MAX17205_AD_NMISCCFG,
			MAX17205_AD_NDESIGNCAP,
			MAX17205_AD_NHIBCFG,
			MAX17205_AD_NPACKCFG,
			MAX17205_AD_NRELAXCFG,
			MAX17205_AD_NCONVGCFG,
			MAX17205_AD_NNVCFG0,
			MAX17205_AD_NNVCFG1,
			MAX17205_AD_NNVCFG2,
			MAX17205_AD_NVALRTTH,
			MAX17205_AD_NTALRTTH,
			MAX17205_AD_NSALRTTH,
			MAX17205_AD_NIALRTTH,
			MAX17205_AD_NFULLSOCTHR,
			MAX17205_AD_NTTFCFG,
			MAX17205_AD_NCGAIN,
			MAX17205_AD_NTCURVE,
			MAX17205_AD_NTGAIN,
			MAX17205_AD_NTOFF,
			MAX17205_AD_NMANFCTRNAME0,
			MAX17205_AD_NMANFCTRNAME1,
			MAX17205_AD_NMANFCTRNAME2,
			MAX17205_AD_NRSENSE,
			MAX17205_AD_NUSER1D0,
			MAX17205_AD_NUSER1D1,
			MAX17205_AD_NAGEFCCFG,
			MAX17205_AD_NDESIGNVOLTAGE,
			MAX17205_AD_NUSER1D4,
			MAX17205_AD_NRFASTVSHDN,
			MAX17205_AD_NMANFCTRDATE,
			MAX17205_AD_NFIRSTUSED,
			MAX17205_AD_NSERIALNUMBER0,
			MAX17205_AD_NSERIALNUMBER1,
			MAX17205_AD_NSERIALNUMBER2,
			MAX17205_AD_NDEVICENAME0,
			MAX17205_AD_NDEVICENAME1,
			MAX17205_AD_NDEVICENAME2,
			MAX17205_AD_NDEVICENAME3,
			MAX17205_AD_NDEVICENAME4,
			0
	};

	for(int i = 0; reg_list[i] != 0;i++) {
		if( max17205I2CReadRegister(config->i2cp, MAX17205_SA(MAX17205_AD_COMMAND), MAX17205_AD(reg_list[i]), buf.data, sizeof(buf.data)) == MSG_OK ) {
			dbgprintf("   %-30s register 0x%X is 0x%X\r\n", max17205RegToStr(reg_list[i]), reg_list[i], buf.value);
		}
	}

	return(MSG_OK);
}


const char* max17205RegToStr(const uint16_t reg) {
	switch (reg) {
		case MAX17205_AD_AVGCELL1:
			return ("MAX17205_AD_AVGCELL1");
		case MAX17205_AD_AVGCELL2:
			return ("MAX17205_AD_AVGCELL2");
		case MAX17205_AD_AVGVCELL:
			return("MAX17205_AD_AVGVCELL");
		case MAX17205_AD_FULLCAP:
			return ("MAX17205_AD_FULLCAP");
		case MAX17205_AD_AVCAP:
			return ("MAX17205_AD_AVCAP");
		case MAX17205_AD_MIXCAP:
			return ("MAX17205_AD_MIXCAP");
		case MAX17205_AD_TTE:
			return ("MAX17205_AD_TTE");
		case MAX17205_AD_TTF:
			return ("MAX17205_AD_TTF");
		case MAX17205_AD_AVSOC:
			return ("MAX17205_AD_AVSOC");
		case MAX17205_AD_VFSOC:
			return ("MAX17205_AD_VFSOC");
		case MAX17205_AD_CYCLES:
			return ("MAX17205_AD_CYCLES");
		case MAX17205_AD_TEMP:
			return("MAX17205_AD_TEMP");
		case MAX17205_AD_AVGCURRENT:
			return("MAX17205_AD_AVGCURRENT");
		case MAX17205_AD_BATT:
			return("MAX17205_AD_BATT");
		case MAX17205_AD_AVGTEMP1:
			return("MAX17205_AD_AVGTEMP1");
		case MAX17205_AD_AVGTEMP2:
			return("MAX17205_AD_AVGTEMP2");
		case MAX17205_AD_AVGINTTEMP:
			return("MAX17205_AD_AVGINTTEMP");
		case MAX17205_AD_REPCAP:
			return("MAX17205_AD_REPCAP");
		case MAX17205_AD_PACKCFG:
			return("MAX17205_AD_PACKCFG");
		case MAX17205_AD_DESIGNCAP:
			return("MAX17205_AD_DESIGNCAP");


		case MAX17205_AD_NXTABLE0:
			return ("MAX17205_AD_NXTABLE0");
		case MAX17205_AD_NXTABLE1:
			return ("MAX17205_AD_NXTABLE1");
		case MAX17205_AD_NXTABLE2:
			return ("MAX17205_AD_NXTABLE2");
		case MAX17205_AD_NXTABLE3:
			return ("MAX17205_AD_NXTABLE3");
		case MAX17205_AD_NXTABLE4:
			return ("MAX17205_AD_NXTABLE4");
		case MAX17205_AD_NXTABLE5:
			return ("MAX17205_AD_NXTABLE5");
		case MAX17205_AD_NXTABLE6:
			return ("MAX17205_AD_NXTABLE6");
		case MAX17205_AD_NXTABLE7:
			return ("MAX17205_AD_NXTABLE7");
		case MAX17205_AD_NXTABLE8:
			return ("MAX17205_AD_NXTABLE8");
		case MAX17205_AD_NXTABLE9:
			return ("MAX17205_AD_NXTABLE9");
		case MAX17205_AD_NXTABLE10:
			return ("MAX17205_AD_NXTABLE10");
		case MAX17205_AD_NXTABLE11:
			return ("MAX17205_AD_NXTABLE11");
		case MAX17205_AD_NUSER18C:
			return ("MAX17205_AD_NUSER18C");
		case MAX17205_AD_NUSER18D:
			return ("MAX17205_AD_NUSER18D");
		case MAX17205_AD_NODSCTH:
			return ("MAX17205_AD_NODSCTH");
		case MAX17205_AD_NODSCCFG:
			return ("MAX17205_AD_NODSCCFG");
		case MAX17205_AD_NOCVTABLE0:
			return ("MAX17205_AD_NOCVTABLE0");
		case MAX17205_AD_NOCVTABLE1:
			return ("MAX17205_AD_NOCVTABLE1");
		case MAX17205_AD_NOCVTABLE2:
			return ("MAX17205_AD_NOCVTABLE2");
		case MAX17205_AD_NOCVTABLE3:
			return ("MAX17205_AD_NOCVTABLE3");
		case MAX17205_AD_NOCVTABLE4:
			return ("MAX17205_AD_NOCVTABLE4");
		case MAX17205_AD_NOCVTABLE5:
			return ("MAX17205_AD_NOCVTABLE5");
		case MAX17205_AD_NOCVTABLE6:
			return ("MAX17205_AD_NOCVTABLE6");
		case MAX17205_AD_NOCVTABLE7:
			return ("MAX17205_AD_NOCVTABLE7");
		case MAX17205_AD_NOCVTABLE8:
			return ("MAX17205_AD_NOCVTABLE8");
		case MAX17205_AD_NOCVTABLE9:
			return ("MAX17205_AD_NOCVTABLE9");
		case MAX17205_AD_NOCVTABLE10:
			return ("MAX17205_AD_NOCVTABLE10");
		case MAX17205_AD_NOCVTABLE11:
			return ("MAX17205_AD_NOCVTABLE11");
		case MAX17205_AD_NICHGTERM:
			return ("MAX17205_AD_NICHGTERM");
		case MAX17205_AD_NFILTERCFG:
			return ("MAX17205_AD_NFILTERCFG");
		case MAX17205_AD_NVEMPTY:
			return ("MAX17205_AD_NVEMPTY");
		case MAX17205_AD_NLEARNCFG:
			return ("MAX17205_AD_NLEARNCFG");
		case MAX17205_AD_NQRTABLE00:
			return ("MAX17205_AD_NQRTABLE00");
		case MAX17205_AD_NQRTABLE10:
			return ("MAX17205_AD_NQRTABLE10");
		case MAX17205_AD_NQRTABLE20:
			return ("MAX17205_AD_NQRTABLE20");
		case MAX17205_AD_NQRTABLE30:
			return ("MAX17205_AD_NQRTABLE30");
		case MAX17205_AD_NCYCLES:
			return ("MAX17205_AD_NCYCLES");
		case MAX17205_AD_NFULLCAPNOM:
			return ("MAX17205_AD_NFULLCAPNOM");
		case MAX17205_AD_NRCOMP0:
			return ("MAX17205_AD_NRCOMP0");
		case MAX17205_AD_NTEMPCO:
			return ("MAX17205_AD_NTEMPCO");
		case MAX17205_AD_NIAVGEMPTY:
			return ("MAX17205_AD_NIAVGEMPTY");
		case MAX17205_AD_NFULLCAPREP:
			return ("MAX17205_AD_NFULLCAPREP");
		case MAX17205_AD_NVOLTTEMP:
			return ("MAX17205_AD_NVOLTTEMP");
		case MAX17205_AD_NMAXMINCURR:
			return ("MAX17205_AD_NMAXMINCURR");
		case MAX17205_AD_NMAXMINVOLT:
			return ("MAX17205_AD_NMAXMINVOLT");
		case MAX17205_AD_NMAXMINTEMP:
			return ("MAX17205_AD_NMAXMINTEMP");
		case MAX17205_AD_NSOC:
			return ("MAX17205_AD_NSOC");
		case MAX17205_AD_NTIMERH:
			return ("MAX17205_AD_NTIMERH");
		case MAX17205_AD_NCONFIG:
			return ("MAX17205_AD_NCONFIG");
		case MAX17205_AD_NRIPPLECFGCFG:
			return ("MAX17205_AD_NRIPPLECFGCFG");
		case MAX17205_AD_NMISCCFG:
			return ("MAX17205_AD_NMISCCFG");
		case MAX17205_AD_NDESIGNCAP:
			return ("MAX17205_AD_NDESIGNCAP");
		case MAX17205_AD_NHIBCFG:
			return ("MAX17205_AD_NHIBCFG");

		case MAX17205_AD_NPACKCFG:
			return ("MAX17205_AD_NPACKCFG");
		case MAX17205_AD_NRELAXCFG:
			return ("MAX17205_AD_NRELAXCFG");
		case MAX17205_AD_NCONVGCFG:
			return ("MAX17205_AD_NCONVGCFG");
		case MAX17205_AD_NNVCFG0:
			return ("MAX17205_AD_NNVCFG0");
		case MAX17205_AD_NNVCFG1:
			return ("MAX17205_AD_NNVCFG1");
		case MAX17205_AD_NNVCFG2:
			return ("MAX17205_AD_NNVCFG2");
		case MAX17205_AD_NVALRTTH:
			return ("MAX17205_AD_NVALRTTH");
		case MAX17205_AD_NTALRTTH:
			return ("MAX17205_AD_NTALRTTH");
		case MAX17205_AD_NSALRTTH:
			return ("MAX17205_AD_NSALRTTH");
		case MAX17205_AD_NIALRTTH:
			return ("MAX17205_AD_NIALRTTH");
		case MAX17205_AD_NFULLSOCTHR:
			return ("MAX17205_AD_NFULLSOCTHR");
		case MAX17205_AD_NTTFCFG:
			return ("MAX17205_AD_NTTFCFG");
		case MAX17205_AD_NCGAIN:
			return ("MAX17205_AD_NCGAIN");
		case MAX17205_AD_NTCURVE:
			return ("MAX17205_AD_NTCURVE");
		case MAX17205_AD_NTGAIN:
			return ("MAX17205_AD_NTGAIN");
		case MAX17205_AD_NTOFF:
			return ("MAX17205_AD_NTOFF");
		case MAX17205_AD_NMANFCTRNAME0:
			return ("MAX17205_AD_NMANFCTRNAME0");
		case MAX17205_AD_NMANFCTRNAME1:
			return ("MAX17205_AD_NMANFCTRNAME1");
		case MAX17205_AD_NMANFCTRNAME2:
			return ("MAX17205_AD_NMANFCTRNAME2");
		case MAX17205_AD_NRSENSE:
			return ("MAX17205_AD_NRSENSE");
		case MAX17205_AD_NUSER1D0:
			return ("MAX17205_AD_NUSER1D0");
		case MAX17205_AD_NUSER1D1:
			return ("MAX17205_AD_NUSER1D1");
		case MAX17205_AD_NAGEFCCFG:
			return ("MAX17205_AD_NAGEFCCFG");
		case MAX17205_AD_NDESIGNVOLTAGE:
			return ("MAX17205_AD_NDESIGNVOLTAGE");
		case MAX17205_AD_NUSER1D4:
			return ("MAX17205_AD_NUSER1D4");
		case MAX17205_AD_NRFASTVSHDN:
			return ("MAX17205_AD_NRFASTVSHDN");
		case MAX17205_AD_NMANFCTRDATE:
			return ("MAX17205_AD_NMANFCTRDATE");
		case MAX17205_AD_NFIRSTUSED:
			return ("MAX17205_AD_NFIRSTUSED");
		case MAX17205_AD_NSERIALNUMBER0:
			return ("MAX17205_AD_NSERIALNUMBER0");
		case MAX17205_AD_NSERIALNUMBER1:
			return ("MAX17205_AD_NSERIALNUMBER1");
		case MAX17205_AD_NSERIALNUMBER2:
			return ("MAX17205_AD_NSERIALNUMBER2");
		case MAX17205_AD_NDEVICENAME0:
			return ("MAX17205_AD_NDEVICENAME0");
		case MAX17205_AD_NDEVICENAME1:
			return ("MAX17205_AD_NDEVICENAME1");
		case MAX17205_AD_NDEVICENAME2:
			return ("MAX17205_AD_NDEVICENAME2");
		case MAX17205_AD_NDEVICENAME3:
			return ("MAX17205_AD_NDEVICENAME3");
		case MAX17205_AD_NDEVICENAME4:
			return ("MAX17205_AD_NDEVICENAME4");

	}

	return("[reg?]");
}

/** @} */
