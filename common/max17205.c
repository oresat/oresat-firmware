/* @brief   MAX17205 Digital to Analog Converter. */

#include "hal.h"
#include "max17205.h"

#ifdef DEBUG_PRINT
#include "chprintf.h"
#define DEBUG_SD ((BaseSequentialStream *) &SD2)
#define dbgprintf(str, ...) chprintf(DEBUG_SD, str, ##__VA_ARGS__)
#else
#define dbgprintf(str, ...)
#endif

#define ARRAY_LEN(x) (sizeof(x)/sizeof(x[0]))

/* See datasheet table 27 and figure 74. The chip has 0x1FF registers but the
 * protocol only allows one byte for register addressing (i.e. registers up to
 * 0x0FF). To get around this the chip responds two separate I2C slave
 * addresses, 0x6C for registers 0x00-0xFF and 0x16 for registers 0x100 -
 * 0x1FF. But wait! Unlike every other datasheet that presents the I2C slave
 * address as a 7 bit value and assumes your I2C driver will right shift and
 * set the read/write lsb, this presents the slave addresses as the 8 bit
 * addresss with read bit set, so we have to unshift them to present it in the
 * format that ChibiOS' driver expects.
 */
#define I2C_ADDR(reg) ((reg > 0xFFU) ? (0x16U >> 1) : (0x6CU >> 1))
#define MEM_ADDR(reg) (reg & 0xFFU)

/**
 * @brief   Reads MAX17205 register as raw value.
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 * @param[in] reg        the register to read
 * @param[out] dest      pointer to location to write read value
 * @return               MSG_OK on success or negative on I2C error
 *
 * @api
 */
static msg_t max17205Read(MAX17205Driver *devp, uint16_t reg, uint16_t *dest) {
    osalDbgCheck(devp != NULL);
    osalDbgCheck(dest != NULL);

    I2CDriver * i2c = devp->config->i2cp;
    uint8_t mem = MEM_ADDR(reg);
    uint8_t buf[2] = {};

    i2cAcquireBus(i2c);
    const msg_t r = i2cMasterTransmitTimeout(i2c, I2C_ADDR(reg), &mem, sizeof(mem), buf, sizeof(buf), TIME_MS2I(50));
    i2cReleaseBus(i2c);

    if (r == MSG_OK) {
        *dest = buf[0] | buf[1] << 8;
    }

    return r;
}

/**
 * @brief   Writes MAX17205 register as raw value.
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 * @param[in] reg        the register to write to
 * @param[in] value      the value to write
 * @return               MSG_OK on success or negative on I2C error
 *
 * @api
 */
static msg_t max17205Write(MAX17205Driver *devp, uint16_t reg, uint16_t value) {
    osalDbgCheck(devp != NULL);

    I2CDriver * i2c = devp->config->i2cp;
    uint8_t buf[3] = {MEM_ADDR(reg), value & 0xFF, (value >> 8) & 0xFF};

    i2cAcquireBus(i2c);
    const msg_t r = i2cMasterTransmitTimeout(i2c, I2C_ADDR(reg), buf, sizeof(buf), NULL, 0, TIME_MS2I(50));
    i2cReleaseBus(i2c);

    return r;
}

/**
 * @brief   Initializes an instance.
 *
 * @param[out] devp     pointer to the @p MAX17205Driver object
 *
 * @init
 */
void max17205ObjectInit(MAX17205Driver *devp) {
    devp->config = NULL;
    devp->state = MAX17205_STOP;
    devp->rsense_uOhm = 0;
}

static msg_t max17205HardwareReset(MAX17205Driver * devp) {
    msg_t r = max17205Write(devp, MAX17205_AD_COMMAND, MAX17205_COMMAND_HARDWARE_RESET);
    if (r != MSG_OK) {
        return r;
    }

    uint32_t check_count = 0;
    uint16_t status = 0;
    do {
        r = max17205Read(devp, MAX17205_AD_STATUS, &status);
        if (r != MSG_OK) {
            return r;
        }
        check_count++;
    } while (!(status & MAX17205_STATUS_POR) && check_count < 10); /* While still resetting */

    if (!(status & MAX17205_STATUS_POR))
        return MSG_RESET;

    r = max17205Write(devp, MAX17205_AD_CONFIG2, MAX17205_CONFIG2_POR_CMD);
    if (r != MSG_OK) {
        return r;
    }

    check_count = 0;
    status = 0;
    do {
        r = max17205Read(devp, MAX17205_AD_STATUS, &status);
        if (r != MSG_OK) {
            return r;
        }
        check_count++;
    } while (!(status & MAX17205_STATUS_POR) && check_count < 10); /* While still resetting */

    if (!(status & MAX17205_STATUS_POR))
        return MSG_RESET;

    return MSG_OK;
}

/**
 * @brief   Configures and activates MAX17205 Complex Driver peripheral.
 *
 * @param[in] devp      pointer to the @p MAX17205Driver object
 * @param[in] config    pointer to the @p MAX17205Config object
 * @return              true on success or false on I2C error
 *
 * @api
 */
bool max17205Start(MAX17205Driver *devp, const MAX17205Config *config) {
    uint32_t comm_error_count = 0;

    osalDbgCheck((devp != NULL) && (config != NULL));
    osalDbgAssert((devp->state == MAX17205_STOP) ||
            (devp->state == MAX17205_READY),
            "max17205Start(), invalid state");

    devp->state = MAX17205_STOP;
    devp->config = config;

    if (max17205Write(devp, MAX17205_AD_CONFIG2, MAX17205_CONFIG2_POR_CMD) != MSG_OK) {
        comm_error_count++;
    }

    // FIXME: is resetting just config2 correct? We should also wait for POR

    for (const max17205_regval_t *pair = config->regcfg; pair->reg; pair++) {
        dbgprintf("Setting MAX17205 register 0x%X to 0x%X\r\n", pair->reg, pair->value);

        if (max17205Write(devp, pair->reg, pair->value) != MSG_OK) {
            comm_error_count++;
        }
    }

    devp->rsense_uOhm = config->rsense_uOhm;
    if (devp->rsense_uOhm == 0) {
        uint16_t nr_sense_value = 0;
        if (max17205Read(devp, MAX17205_AD_NRSENSE, &nr_sense_value) != MSG_OK) {
            ++comm_error_count;
        }
        devp->rsense_uOhm = nr_sense_value;
    }
    osalDbgAssert(devp->rsense_uOhm > 0, "max17205Start(), config->rsense_uOhm or register nRSENSE must be > 0");

    if (comm_error_count == 0) {
        devp->state = MAX17205_READY;
        return true;
    } else {
        devp->state = MAX17205_UNINIT;
    }
    return false;
}

/**
 * @brief   Deactivates the MAX17205 Complex Driver peripheral.
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 *
 * @api
 */
void max17205Stop(MAX17205Driver *devp) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state == MAX17205_STOP) || (devp->state == MAX17205_READY),
            "max17205Stop(), invalid state");

    // FIXME: Given how the chip works does "stop" even make sense?
    if (devp->state == MAX17205_READY) {
        max17205Write(devp, MAX17205_AD_COMMAND, MAX17205_COMMAND_HARDWARE_RESET);
        max17205Write(devp, MAX17205_AD_CONFIG2, MAX17205_CONFIG2_POR_CMD);
    }
    devp->state = MAX17205_STOP;
}

/**
 * @brief   Reads an MAX17205 capacity value from a register in mAh.
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 * @param[in] reg        the register to read from
 * @param[out] dest_mAh  location to write capacity result, in mAh
 * @return               MSG_OK on success or negative on I2C error
 *
 * @details  dest_mAh will be between 0 and up to 327,675,000 mAh but typically
 *           closer to 32,767 depending on the value of rsense_uOhm.
 * @api
 */
msg_t max17205ReadCapacity(MAX17205Driver *devp, const uint16_t reg, uint32_t *dest_mAh) {
    osalDbgAssert(devp->state == MAX17205_READY, "max17205ReadCapacity(), invalid state");

    uint16_t buf = 0;
    const msg_t r = max17205Read(devp, reg, &buf);
    if (r == MSG_OK) {
        // Reference datasheet table 1: Capacity LSB is 5.0μVh/RSENSE where Vh/R=Ah, unsigned.
        *dest_mAh = buf * 5000U / devp->rsense_uOhm;
        dbgprintf("  max17205ReadCapacity(0x%X %s) = %u mAh (raw: 0x%X)\r\n",
            reg, max17205RegToStr(reg), *dest_mAh, buf);
    }
    return r;
}


/**
 * @brief   Reads an MAX17205 percentage value from a register in 1% increments.
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 * @param[in] reg        the register to read from
 * @param[out] dest_pct  location to write percentage result, in 1% increments
 * @return               MSG_OK on success or negative on I2C error
 *
 * @details  dest_pct will be between 0% and 255%.
 *
 * @api
 */
msg_t max17205ReadPercentage(MAX17205Driver *devp, uint16_t reg, uint8_t *dest_pct) {
    osalDbgAssert(devp->state == MAX17205_READY, "max17205ReadPercentage(), invalid state");
    uint16_t buf = 0;
    msg_t r = max17205Read(devp, reg, &buf);
    if (r == MSG_OK) {
        // Reference datasheet table 1: Percentage LSB is 1/256%, unsigned.
        *dest_pct = buf / 256U;
        dbgprintf("  max17205ReadPercentage(0x%X %s) = %u%% (raw: 0x%X)\r\n",
            reg, max17205RegToStr(reg), *dest_pct, buf);
    }
    return r;
}


/* dest_count will be between 0 and 10485 cycles */
msg_t max17205ReadCycles(MAX17205Driver *devp, uint16_t *dest_count) {
    osalDbgAssert(devp->state == MAX17205_READY, "max17205ReadCycles(), invalid state");
    uint16_t buf = 0;
    msg_t r = max17205Read(devp, MAX17205_AD_CYCLES, &buf);
    if (r == MSG_OK) {
        // Reference datasheet page 33: LSB is 16%, unsigned.
        *dest_count = buf * 16U / 100U;
        dbgprintf("  max17205ReadCycles(0x%X %s) = %u%% (raw: 0x%X)\r\n",
            MAX17205_AD_CYCLES, max17205RegToStr(MAX17205_AD_CYCLES), *dest_count, buf);
    }
    return r;
}

/**
 * @brief   Reads an MAX17205 voltage value from a register in mV.
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 * @param[in] reg        the register to read from
 * @param[out] dest_mV   location to write voltage result, in mV
 * @return               MSG_OK on success or negative on I2C error
 *
 * @details  dest_mV will be between 0 and 5119mV.
 *
 * @api
 */
msg_t max17205ReadVoltage(MAX17205Driver *devp, uint16_t reg, uint16_t *dest_mV) {
    osalDbgAssert(devp->state == MAX17205_READY, "max17205ReadVoltage(), invalid state");
    uint16_t buf = 0;
    msg_t r = max17205Read(devp, reg, &buf);
    if (r == MSG_OK) {
        // Reference datasheet Table 1: Voltage LSB is 0.078125mV, unsigend.
        // Converting to mV using integer math would be buf * 78125 / 1_000_000, but that could
        // overflow a uint32_t so remove the common 5^6 factor from both numbers first.
        *dest_mV = buf * 5U / 64U;
        dbgprintf("  max17205ReadVoltage(0x%X %s) = %u mV\r\n", reg, max17205RegToStr(reg), *dest_mV);
    }
    return r;
}

/**
 * dest_mV will be between 0 and 81,918mV but realistically can be
 * at most 76.8V in a 15 cell configuration.
 */
msg_t max17205ReadBatt(MAX17205Driver *devp, uint32_t *dest_mV) {
    osalDbgAssert(devp->state == MAX17205_READY, "max17205ReadBatt(), invalid state");
    uint16_t buf = 0;
    msg_t r = max17205Read(devp, MAX17205_AD_BATT, &buf);
    if (r == MSG_OK) {
        //Reference datasheet page 71: Voltage LSB is 1.25mV, unsigned.
        *dest_mV = buf * 125U / 100U;
        dbgprintf("  max17205ReadBatt(0x%X %s) = %u mV\r\n",
            MAX17205_AD_BATT, max17205RegToStr(MAX17205_AD_BATT), *dest_mV);
    }
    return r;
}

/**
 * max_mV can be between 0mV and 5100mV, starting at 0.
 * min_mV can be between 0mV and 5100mV, starting at 5100.
 */
msg_t max17205ReadMaxMinVoltage(MAX17205Driver *devp, uint16_t * max_mV, uint16_t * min_mV) {
    osalDbgAssert(devp->state == MAX17205_READY, "max17205ReadMaxMinVoltage(), invalid state");
    uint16_t buf = 0;
    msg_t r = max17205Read(devp, MAX17205_AD_MAXMINVOLT, &buf);
    if (r == MSG_OK) {
        // Reference datasheet page 71: register MaxMinVolt is two 8 bit unsigned values with
        // 20mV/LSB, the upper byte being max and lower byte min.
        *max_mV =  (buf >> 8) * 20;
        *min_mV = (buf & 0xFF) * 20;
    }
    return r;
}

/**
 * @brief   Reads an MAX17205 current value from a register in mA.
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 * @param[in] reg        the register to read from
 * @param[out] dest_pct  location to write voltage result, in mV
 * @return               MSG_OK on success or negative on I2C error
 *
 * @details  dest_mA can be between -51,200,000mA and 51,198,437mA but typically
 *           between -5,120mA and 5,119mA depending on rsense_uOhm.
 * @api
 */
msg_t max17205ReadCurrent(MAX17205Driver *devp, uint16_t reg, int32_t *dest_mA) {
    osalDbgAssert(devp->state == MAX17205_READY, "max17205ReadCurrent(), invalid state");
    uint16_t buf = 0;
    msg_t r = max17205Read(devp, reg, &buf);
    if (r == MSG_OK) {
        // Referencce datasheet table 1: Current LSB is 1.5625μV/RSENSE, signed.
        *dest_mA = (int16_t)buf * 15625 / (devp->rsense_uOhm * 10);
        dbgprintf("  max17205ReadCurrent(0x%X %s) = %d mA (raw: 0x%X)\r\n",
            reg, max17205RegToStr(reg), *dest_mA, buf);
    }
    return r;
}

/**
 * Both max_mA and min_mA can be between -102,400,000mA and 102,000,000mA but typically
 * between -10,240mA and 10,200mA depending on rsense_uOhm.
 * max_mA starts at the minimum value.
 * min_mA starts at the maximum value.
 *
 */
msg_t max17205ReadMaxMinCurrent(MAX17205Driver *devp, int32_t * max_mA, int32_t * min_mA) {
    osalDbgAssert(devp->state == MAX17205_READY, "max17205ReadMaxMinCurrent(), invalid state");
    uint16_t buf = 0;
    msg_t r = max17205Read(devp, MAX17205_AD_MAXMINCURR, &buf);
    if (r == MSG_OK) {
        // Reference datasheet page 73: MaxMinCurrent is two packed signed 1 byte values with
        // LSB of 0.40mV/RSENSE.
        int8_t max_raw = (buf >> 8);
        int8_t min_raw = buf & 0xFF;
        *max_mA = max_raw * 400000 / devp->rsense_uOhm;
        *min_mA = min_raw * 400000 / devp->rsense_uOhm;
    }
    return r;
}

/**
 * @brief   Reads an MAX17205 temperature value from a register in 0.001C increments.
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 * @param[in] reg        the register to read from
 * @param[out] dest_mC   location to write temperature output in mC
 * @return               MSG_OK on success or negative on I2C error
 *
 * @details  dest_mC will be between -256,000mC and 255,996mC.
 * @api
 */
msg_t max17205ReadTemperature(MAX17205Driver *devp, uint16_t reg, int32_t *dest_mC) {
    osalDbgAssert(devp->state == MAX17205_READY, "max17205ReadTemperature(), invalid state");
    uint16_t buf = 0;
    msg_t r = max17205Read(devp, reg, &buf);
    if (r == MSG_OK) {
        // Reference Datasheet table 1: Temperature LSB is 1/256C, signed.
        *dest_mC = (int16_t)buf * 1000 / 256;
        dbgprintf("  max17205ReadTemperature(0x%X %s) = %d mC (%u C) (raw: 0x%X)\r\n",
            reg, max17205RegToStr(reg), *dest_mC, (*dest_mC / 1000), buf);
    }
    return r;
}

/**
 * @brief   Reads an MAX17205 temperature value from a register in 1C increments.
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 * @param[in] reg        the register to read from
 * @param[out] dest_C    location to write temperature output in C
 * @return               MSG_OK on success or negative on I2C error
 *
 * @details  dest_C will be between ?? and ??.
 * @api
 */
msg_t max17205ReadAverageTemperature(MAX17205Driver *devp, uint16_t reg, int16_t *dest_C) {
    osalDbgAssert(devp->state == MAX17205_READY, "max17205ReadAverageTemperature(), invalid state");
    uint16_t buf = 0;
    msg_t r = max17205Read(devp, reg, &buf);
    if (r == MSG_OK) {
        // Reference datasheet page 77: "These registers display temperature in degrees
        // Celsius starting at absolute zero, -273ºC or 0ºK with an LSb of 0.1ºC."
        // FIXME: Does that mean signed Celsius or unsigned Kelvin? The converison below
        // assumes signed(!?) Kelvin but this should be checked on a live chip.
        *dest_C = (int16_t)buf / 10 - 273;
        dbgprintf("  max17205ReadTemperature(0x%X %s) = %d C (raw: 0x%X)\r\n",
            reg, max17205RegToStr(reg), *dest_C, buf);
    }
    return r;
}

/**
 * max_C and min_C will be between -128C and 127C.
 */
msg_t max17205ReadMaxMinTemperature(MAX17205Driver *devp, int8_t * max_C, int8_t * min_C) {
    osalDbgAssert(devp->state == MAX17205_READY, "max17205ReadMaxMinTemperature(), invalid state");
    uint16_t buf = 0;
    msg_t r = max17205Read(devp, MAX17205_AD_MAXMINTEMP, &buf);
    if (r == MSG_OK) {
        // Reference datahseet page 76: Two packed signed 1 byte Celceus values with 1C/LSB, with
        // the upper byte max and lower byte min.
        *max_C = buf >> 8;
        *min_C = buf & 0xFF;
    }
    return r;
}

/**
 * @brief   Reads an MAX17205 resistance value from a register in mOhms.
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 * @param[in] reg        the register to read from
 * @param[out] dest_mOhm location to write resistance in mOhms
 * @return               MSG_OK on success or negative on I2C error
 *
 * @details  dest_mOhm will be between 0mOhm and 15,999mOhm.
 *
 * @api
 */

msg_t max17205ReadResistance(MAX17205Driver *devp, uint16_t reg, uint16_t *dest_mOhm) {
    osalDbgAssert(devp->state == MAX17205_READY, "max17205ReadResistance(), invalid state");
    uint16_t buf;
    msg_t r = max17205Read(devp, reg, &buf);
    if (r == MSG_OK) {
        // Reference datasheet table 1: Resistance LSB is 1/4096Ω, unsigned.
        *dest_mOhm = buf * 1000U / 4096U;
    }

    return r;
}

/**
 * @brief   Reads an MAX17205 time value from a register in seconds.
 *
 * @param[in] devp       pointer to the @p MAX17205Driver object
 * @param[in] reg        the register to read from
 * @param[out] dest_S    location to write time in S
 * @return               MSG_OK on success or negative on I2C error
 *
 * @details dest_s will be between 0S and 368,634S.
 *
 * @api
 */
msg_t max17205ReadTime(MAX17205Driver *devp, uint16_t reg, uint32_t *dest_S) {
    osalDbgAssert(devp->state == MAX17205_READY, "max17205ReadTime(), invalid state");
    uint16_t buf = 0;
    msg_t r = max17205Read(devp, reg, &buf);
    if (r == MSG_OK) {
        // Reference datasheet table 1: Time LSB is 5.625s, unsigned.
        *dest_S = buf * 5625U / 1000U;
        dbgprintf("  max17205ReadTime(0x%X %s) = %u seconds (raw: 0x%X)\r\n",
            reg, max17205RegToStr(reg), *dest_S, buf);
    }
    return r;
}

/**
 * The MAX17205 allows for the NV ram to be written no more then 7 times on a single chip.
 * Each time, an additional bit is set in a flash register which can be queried.
 *
 * TODO document this
 */
msg_t max17205ReadNVWriteCountMaskingRegister(MAX17205Driver *devp, uint16_t *reg_dest, uint8_t *number_of_writes_left) {
    osalDbgAssert(devp->state == MAX17205_READY, "max17205ReadNVWriteCountMaskingRegister(), invalid state");
    //Determine the number of times NV memory has been written on this chip.
    //See page 85 of the data sheet

    dbgprintf("Reading NV Masking register...\r\n");

    uint16_t value = 0xE2FA;
    msg_t r = max17205Write(devp, MAX17205_AD_COMMAND, value);
    if (r != MSG_OK ) {
        return r;
    }
    chThdSleepMilliseconds(MAX17205_T_RECAL_MS);

    uint16_t buf;
    r = max17205Read(devp, 0x1ED, &buf);
    if (r != MSG_OK) {
        return r;
    }

    uint8_t mm = (buf & 0xFF) & ((buf >> 8) & 0xFF);
    dbgprintf("Memory Update Masking of register 0x%X is 0x%X\r\n", 0x1ED, mm);

    uint8_t num_left = 7;
    for(uint8_t i = 0; i < 8; i++) {
        if (buf & (1<<i) && num_left > 0) {
            num_left--;
        }
    }

    *reg_dest = buf;
    *number_of_writes_left = num_left;
    return MSG_OK;
}

/**
 * See page 85 of the data sheet
 */
msg_t max17205NonvolatileBlockProgram(MAX17205Driver *devp) {
    osalDbgAssert(devp->state == MAX17205_READY, "max17205NonvolatileBlockProgram(), invalid state");
    //  1. Write desired memory locations to new values.
    //should be done prior to calling this function

    dbgprintf("Clearing CommStat.NVError bit\r\n");
    //  2. Clear CommStat.NVError bit.
    msg_t r = max17205Write(devp, MAX17205_AD_COMMSTAT, MAX17205_COMMSTAT_NVERROR);
    if (r != MSG_OK) {
        return r;
    }

    //  3. Write 0xE904 to the Command register 0x060 to initiate a block copy.
    r = max17205Write(devp, MAX17205_AD_COMMAND, 0xE904);
    if (r != MSG_OK) {
        dbgprintf("Initiated failed to send command to initiate block copy....\r\n");
        return r;
    }
    dbgprintf("Initiated MAX17205 block copy....\r\n");

    //  4. Wait t BLOCK for the copy to complete.
    dbgprintf("Waiting %u ms for block copy to complete....\r\n", MAX17205_T_BLOCK_MS);
    chThdSleepMilliseconds(MAX17205_T_BLOCK_MS); //tBlock(max) is specified as 7360ms in the data sheet, page 16

    uint16_t buf = 0;
    //  5. Check the CommStat.NVError bit. If set, repeat the process. If clear, continue.
    r = max17205Read(devp, MAX17205_AD_COMMSTAT, &buf);
    if (r != MSG_OK) {
        dbgprintf("Failed to query COMMSTAT register...\r\n");
        return r;
    }

    dbgprintf("Read MAX17205_AD_COMMSTAT register 0x%X as 0x%X\r\n", MAX17205_AD_COMMSTAT, buf);
    if (buf & MAX17205_COMMSTAT_NVERROR) {
        //Error bit is set
        dbgprintf("Block copy failed...\r\n");
        return MSG_RESET;
    }
    dbgprintf("Block copy was successful, breaking...\r\n");


    //  6. Write 0x000F to the Command register 0x060 to POR the IC.
    //  7. Wait t POR for the IC to reset.
    //  8. Write 0x0001 to Counter Register 0x0BB to reset firmware.
    //  9. Wait t POR for the firmware to restart.
    dbgprintf("Reseting MAX17205...\r\n");
    if ((r = max17205HardwareReset(devp)) != MSG_OK) {
        dbgprintf("Failed to reset MAX17205\r\n");
        return r;
    }

    return MSG_OK;
}

msg_t max17205ValidateRegisters(MAX17205Driver *devp, const max17205_regval_t * list, size_t len, bool * valid) {
    osalDbgAssert(devp->state == MAX17205_READY, "max17205ValidateRegisters(), invalid state");
    bool matches = true;
    dbgprintf("Current and expected NV settings:\r\n");
    for (size_t i = 0; i < len; ++i) {
        uint16_t buf = 0;
        msg_t r = max17205Read(devp, list[i].reg, &buf);
        if (r != MSG_OK) {
            return r;
        }
        dbgprintf("   %-30s register 0x%X is 0x%X     expected  0x%X\r\n",
            max17205RegToStr(list[i].reg), list[i].reg,
            buf, list[i].value
        );
        if (buf != list[i].value) {
           matches = false;
        }
    }
    *valid = matches;
    return MSG_OK;
}

msg_t max17205WriteRegisters(MAX17205Driver *devp, const max17205_regval_t * list, size_t len) {
    osalDbgAssert(devp->state == MAX17205_READY, "max17205WriteRegisters(), invalid state");
    for (size_t i = 0; i < len; ++i) {
        msg_t r = max17205Write(devp, list[i].reg, list[i].value);
        if (r != MSG_OK) {
            return r;
        }
    }
    return MSG_OK;
}

msg_t max17205PrintintNonvolatileMemory(MAX17205Driver *devp) {
    osalDbgAssert(devp->state == MAX17205_READY, "max17205ReadTime(), invalid state");
    uint16_t masking_register = 0;
    uint8_t num_left = 0;
    msg_t r = max17205ReadNVWriteCountMaskingRegister(devp, &masking_register, &num_left);
    if (r != MSG_OK) {
        return r;
    }

    dbgprintf("\r\nMAX17205 *Volatile* Registers\r\n");
    uint16_t volatile_reg_list[] = {
        MAX17205_AD_PACKCFG,
        MAX17205_AD_DESIGNCAP,
        MAX17205_AD_NRSENSE,
    };

    for(size_t i = 0; i < ARRAY_LEN(volatile_reg_list); ++i) {
        uint16_t buf = 0;
        r = max17205Read(devp, volatile_reg_list[i], &buf);
        if (r != MSG_OK) {
            return r;
        }
        dbgprintf("   %-30s register 0x%X is 0x%X\r\n", max17205RegToStr(volatile_reg_list[i]), volatile_reg_list[i], buf);
    }

    // See table 19 on page 83 of the data sheet to see the list of non-volatile registers
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
    };

    for(size_t i = 0; i < ARRAY_LEN(reg_list); ++i) {
        uint16_t buf = 0;
        r = max17205Read(devp, reg_list[i], &buf);
        if (r != MSG_OK) {
            return r;
        }
        dbgprintf("   %-30s register 0x%X is 0x%X\r\n", max17205RegToStr(reg_list[i]), reg_list[i], buf);
    }
    return MSG_OK;
}


const char* max17205RegToStr(const uint16_t reg) {
    switch (reg) {
        case MAX17205_AD_AVGCELL1:
            return "MAX17205_AD_AVGCELL1";
        case MAX17205_AD_AVGCELL2:
            return "MAX17205_AD_AVGCELL2";
        case MAX17205_AD_AVGVCELL:
            return "MAX17205_AD_AVGVCELL";
        case MAX17205_AD_VCELL:
            return "MAX17205_AD_VCELL";
        case MAX17205_AD_FULLCAP:
            return "MAX17205_AD_FULLCAP";
        case MAX17205_AD_AVCAP:
            return "MAX17205_AD_AVCAP";
        case MAX17205_AD_FULLCAPREP:
            return "MAX17205_AD_FULLCAPREP";
        case MAX17205_AD_MIXCAP:
            return "MAX17205_AD_MIXCAP";
        case MAX17205_AD_TTE:
            return "MAX17205_AD_TTE";
        case MAX17205_AD_TTF:
            return "MAX17205_AD_TTF";
        case MAX17205_AD_AVSOC:
            return "MAX17205_AD_AVSOC";
        case MAX17205_AD_VFSOC:
            return "MAX17205_AD_VFSOC";
        case MAX17205_AD_CYCLES:
            return "MAX17205_AD_CYCLES";
        case MAX17205_AD_TEMP:
            return "MAX17205_AD_TEMP";
        case MAX17205_AD_CURRENT:
            return "MAX17205_AD_CURRENT";
        case MAX17205_AD_AVGCURRENT:
            return "MAX17205_AD_AVGCURRENT";
        case MAX17205_AD_BATT:
            return "MAX17205_AD_BATT";
        case MAX17205_AD_AVGTEMP1:
            return "MAX17205_AD_AVGTEMP1";
        case MAX17205_AD_TEMP1:
            return "MAX17205_AD_TEMP1";
        case MAX17205_AD_AVGTEMP2:
            return "MAX17205_AD_AVGTEMP2";
        case MAX17205_AD_AVGINTTEMP:
            return "MAX17205_AD_AVGINTTEMP";
        case MAX17205_AD_REPCAP:
            return "MAX17205_AD_REPCAP";
        case MAX17205_AD_PACKCFG:
            return "MAX17205_AD_PACKCFG";
        case MAX17205_AD_DESIGNCAP:
            return "MAX17205_AD_DESIGNCAP";
        case MAX17205_AD_REPSOC:
            return "MAX17205_AD_REPSOC";
        case MAX17205_AD_NXTABLE0:
            return "MAX17205_AD_NXTABLE0";
        case MAX17205_AD_NXTABLE1:
            return "MAX17205_AD_NXTABLE1";
        case MAX17205_AD_NXTABLE2:
            return "MAX17205_AD_NXTABLE2";
        case MAX17205_AD_NXTABLE3:
            return "MAX17205_AD_NXTABLE3";
        case MAX17205_AD_NXTABLE4:
            return "MAX17205_AD_NXTABLE4";
        case MAX17205_AD_NXTABLE5:
            return "MAX17205_AD_NXTABLE5";
        case MAX17205_AD_NXTABLE6:
            return "MAX17205_AD_NXTABLE6";
        case MAX17205_AD_NXTABLE7:
            return "MAX17205_AD_NXTABLE7";
        case MAX17205_AD_NXTABLE8:
            return "MAX17205_AD_NXTABLE8";
        case MAX17205_AD_NXTABLE9:
            return "MAX17205_AD_NXTABLE9";
        case MAX17205_AD_NXTABLE10:
            return "MAX17205_AD_NXTABLE10";
        case MAX17205_AD_NXTABLE11:
            return "MAX17205_AD_NXTABLE11";
        case MAX17205_AD_NUSER18C:
            return "MAX17205_AD_NUSER18C";
        case MAX17205_AD_NUSER18D:
            return "MAX17205_AD_NUSER18D";
        case MAX17205_AD_NODSCTH:
            return "MAX17205_AD_NODSCTH";
        case MAX17205_AD_NODSCCFG:
            return "MAX17205_AD_NODSCCFG";
        case MAX17205_AD_NOCVTABLE0:
            return "MAX17205_AD_NOCVTABLE0";
        case MAX17205_AD_NOCVTABLE1:
            return "MAX17205_AD_NOCVTABLE1";
        case MAX17205_AD_NOCVTABLE2:
            return "MAX17205_AD_NOCVTABLE2";
        case MAX17205_AD_NOCVTABLE3:
            return "MAX17205_AD_NOCVTABLE3";
        case MAX17205_AD_NOCVTABLE4:
            return "MAX17205_AD_NOCVTABLE4";
        case MAX17205_AD_NOCVTABLE5:
            return "MAX17205_AD_NOCVTABLE5";
        case MAX17205_AD_NOCVTABLE6:
            return "MAX17205_AD_NOCVTABLE6";
        case MAX17205_AD_NOCVTABLE7:
            return "MAX17205_AD_NOCVTABLE7";
        case MAX17205_AD_NOCVTABLE8:
            return "MAX17205_AD_NOCVTABLE8";
        case MAX17205_AD_NOCVTABLE9:
            return "MAX17205_AD_NOCVTABLE9";
        case MAX17205_AD_NOCVTABLE10:
            return "MAX17205_AD_NOCVTABLE10";
        case MAX17205_AD_NOCVTABLE11:
            return "MAX17205_AD_NOCVTABLE11";
        case MAX17205_AD_NICHGTERM:
            return "MAX17205_AD_NICHGTERM";
        case MAX17205_AD_NFILTERCFG:
            return "MAX17205_AD_NFILTERCFG";
        case MAX17205_AD_NVEMPTY:
            return "MAX17205_AD_NVEMPTY";
        case MAX17205_AD_NLEARNCFG:
            return "MAX17205_AD_NLEARNCFG";
        case MAX17205_AD_NQRTABLE00:
            return "MAX17205_AD_NQRTABLE00";
        case MAX17205_AD_NQRTABLE10:
            return "MAX17205_AD_NQRTABLE10";
        case MAX17205_AD_NQRTABLE20:
            return "MAX17205_AD_NQRTABLE20";
        case MAX17205_AD_NQRTABLE30:
            return "MAX17205_AD_NQRTABLE30";
        case MAX17205_AD_NCYCLES:
            return "MAX17205_AD_NCYCLES";
        case MAX17205_AD_NFULLCAPNOM:
            return "MAX17205_AD_NFULLCAPNOM";
        case MAX17205_AD_NRCOMP0:
            return "MAX17205_AD_NRCOMP0";
        case MAX17205_AD_NTEMPCO:
            return "MAX17205_AD_NTEMPCO";
        case MAX17205_AD_NIAVGEMPTY:
            return "MAX17205_AD_NIAVGEMPTY";
        case MAX17205_AD_NFULLCAPREP:
            return "MAX17205_AD_NFULLCAPREP";
        case MAX17205_AD_NVOLTTEMP:
            return "MAX17205_AD_NVOLTTEMP";
        case MAX17205_AD_NMAXMINCURR:
            return "MAX17205_AD_NMAXMINCURR";
        case MAX17205_AD_NMAXMINVOLT:
            return "MAX17205_AD_NMAXMINVOLT";
        case MAX17205_AD_NMAXMINTEMP:
            return "MAX17205_AD_NMAXMINTEMP";
        case MAX17205_AD_NSOC:
            return "MAX17205_AD_NSOC";
        case MAX17205_AD_NTIMERH:
            return "MAX17205_AD_NTIMERH";
        case MAX17205_AD_NCONFIG:
            return "MAX17205_AD_NCONFIG";
        case MAX17205_AD_NRIPPLECFGCFG:
            return "MAX17205_AD_NRIPPLECFGCFG";
        case MAX17205_AD_NMISCCFG:
            return "MAX17205_AD_NMISCCFG";
        case MAX17205_AD_NDESIGNCAP:
            return "MAX17205_AD_NDESIGNCAP";
        case MAX17205_AD_NHIBCFG:
            return "MAX17205_AD_NHIBCFG";
        case MAX17205_AD_NPACKCFG:
            return "MAX17205_AD_NPACKCFG";
        case MAX17205_AD_NRELAXCFG:
            return "MAX17205_AD_NRELAXCFG";
        case MAX17205_AD_NCONVGCFG:
            return "MAX17205_AD_NCONVGCFG";
        case MAX17205_AD_NNVCFG0:
            return "MAX17205_AD_NNVCFG0";
        case MAX17205_AD_NNVCFG1:
            return "MAX17205_AD_NNVCFG1";
        case MAX17205_AD_NNVCFG2:
            return "MAX17205_AD_NNVCFG2";
        case MAX17205_AD_NVALRTTH:
            return "MAX17205_AD_NVALRTTH";
        case MAX17205_AD_NTALRTTH:
            return "MAX17205_AD_NTALRTTH";
        case MAX17205_AD_NSALRTTH:
            return "MAX17205_AD_NSALRTTH";
        case MAX17205_AD_NIALRTTH:
            return "MAX17205_AD_NIALRTTH";
        case MAX17205_AD_NFULLSOCTHR:
            return "MAX17205_AD_NFULLSOCTHR";
        case MAX17205_AD_NTTFCFG:
            return "MAX17205_AD_NTTFCFG";
        case MAX17205_AD_NCGAIN:
            return "MAX17205_AD_NCGAIN";
        case MAX17205_AD_NTCURVE:
            return "MAX17205_AD_NTCURVE";
        case MAX17205_AD_NTGAIN:
            return "MAX17205_AD_NTGAIN";
        case MAX17205_AD_NTOFF:
            return "MAX17205_AD_NTOFF";
        case MAX17205_AD_NMANFCTRNAME0:
            return "MAX17205_AD_NMANFCTRNAME0";
        case MAX17205_AD_NMANFCTRNAME1:
            return "MAX17205_AD_NMANFCTRNAME1";
        case MAX17205_AD_NMANFCTRNAME2:
            return "MAX17205_AD_NMANFCTRNAME2";
        case MAX17205_AD_NRSENSE:
            return "MAX17205_AD_NRSENSE";
        case MAX17205_AD_NUSER1D0:
            return "MAX17205_AD_NUSER1D0";
        case MAX17205_AD_NUSER1D1:
            return "MAX17205_AD_NUSER1D1";
        case MAX17205_AD_NAGEFCCFG:
            return "MAX17205_AD_NAGEFCCFG";
        case MAX17205_AD_NDESIGNVOLTAGE:
            return "MAX17205_AD_NDESIGNVOLTAGE";
        case MAX17205_AD_NUSER1D4:
            return "MAX17205_AD_NUSER1D4";
        case MAX17205_AD_NRFASTVSHDN:
            return "MAX17205_AD_NRFASTVSHDN";
        case MAX17205_AD_NMANFCTRDATE:
            return "MAX17205_AD_NMANFCTRDATE";
        case MAX17205_AD_NFIRSTUSED:
            return "MAX17205_AD_NFIRSTUSED";
        case MAX17205_AD_NSERIALNUMBER0:
            return "MAX17205_AD_NSERIALNUMBER0";
        case MAX17205_AD_NSERIALNUMBER1:
            return "MAX17205_AD_NSERIALNUMBER1";
        case MAX17205_AD_NSERIALNUMBER2:
            return "MAX17205_AD_NSERIALNUMBER2";
        case MAX17205_AD_NDEVICENAME0:
            return "MAX17205_AD_NDEVICENAME0";
        case MAX17205_AD_NDEVICENAME1:
            return "MAX17205_AD_NDEVICENAME1";
        case MAX17205_AD_NDEVICENAME2:
            return "MAX17205_AD_NDEVICENAME2";
        case MAX17205_AD_NDEVICENAME3:
            return "MAX17205_AD_NDEVICENAME3";
        case MAX17205_AD_NDEVICENAME4:
            return "MAX17205_AD_NDEVICENAME4";
    }
    return "[reg?]";
}

/** @} */
