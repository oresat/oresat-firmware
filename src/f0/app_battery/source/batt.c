#include "ch.h"
#include "batt.h"
#include "max17205.h"
#include "CANopen.h"
#include "OD.h"
#include <sys/param.h>

#define ENABLE_NV_MEMORY_UPDATE_CODE      1

#ifdef DEBUG_PRINT
#include "chprintf.h"
#define DEBUG_SD &SD2
#define dbgprintf(str, ...) chprintf((BaseSequentialStream *)DEBUG_SD, str, ##__VA_ARGS__)
#else
#define dbgprintf(str, ...)
#endif

#define ARRAY_LEN(x) (sizeof(x)/sizeof(x[0]))
#define CLAMP(val, low, high) MIN(MAX(val, low), high)

#define NCELLS          2U          /* Number of cells */

typedef enum {
    BATTERY_OD_ERROR_INFO_CODE_NONE = 0,
    BATTERY_OD_ERROR_INFO_CODE_PACK_1_COMM_ERROR,
    BATTERY_OD_ERROR_INFO_CODE_PACK_2_COMM_ERROR,
    BATTERY_OD_ERROR_INFO_CODE_PACK_FAIL_SAFE_HEATING,
    BATTERY_OD_ERROR_INFO_CODE_PACK_FAIL_SAFE_CHARGING,
} battery_od_error_info_code_t;

typedef enum {
    BATTERY_STATE_MACHINE_STATE_NOT_HEATING = 0,
    BATTERY_STATE_MACHINE_STATE_HEATING,
} battery_heating_state_machine_state_t;

typedef enum {
    STATUS_BIT_HEATER = 0,
    STATUS_BIT_DCHG_DIS,
    STATUS_BIT_CHG_DIS,
    STATUS_BIT_DCHG_STAT,
    STATUS_BIT_CHG_STAT
} status_bits;

/*
  The values for batt_nv_programing_cfg are detailed in the google document "MAX17205 Register Values"
  These values were generated using the windows tool from Maxim and while they are probably not totally
  correct yield generally reasonable read back values from the MAX17 chip.
 */
static const max17205_regval_t batt_nv_programing_cfg[] = {
    {MAX17205_AD_NDESIGNCAP,   0x1450 }, // 5200 (0.5 increments)
    {MAX17205_AD_NPACKCFG,     0x3EA2 },
    {MAX17205_AD_NNVCFG0,      0x09A0 }, // was 0x00B0 -- try Wizard=0x09A0 (old comment: 0x0920)
    {MAX17205_AD_NNVCFG1,      0x8006 }, // was 0xC000 -- try Wizard=0x8006
    {MAX17205_AD_NNVCFG2,      0xFF0A },
    {MAX17205_AD_NICHGTERM,    0x0034 }, // was 0x0034 -- try Wizard=0x14D
    {MAX17205_AD_NVEMPTY,      0x965A }, // VE = 0x12C * 10mV = 3.0v; VR = 0x5A * 40mV = 3.6v
    {MAX17205_AD_NTCURVE,      0x0064 },
    {MAX17205_AD_NTGAIN,       0xF49A },
    {MAX17205_AD_NTOFF,        0x16A1 },

    {MAX17205_AD_NFULLCAPREP,  0x1450 },
    {MAX17205_AD_NFULLCAPNOM,  0x1794 }, // was 0x1450 -- try Wizard=0x1794

    // Missing from in flight fw, but present in Wizard output with m5 EZ battery model:
    {MAX17205_AD_NQRTABLE00,   0x2280 },
    {MAX17205_AD_NQRTABLE10,   0x1000 },
    {MAX17205_AD_NQRTABLE20,   0x0681 },
    {MAX17205_AD_NQRTABLE30,   0x0682 },
    {MAX17205_AD_NIAVGEMPTY,   0xEBB0 },
    {MAX17205_AD_NCONFIG,      0x0211 },
    {MAX17205_AD_NMISCCFG,     0x3070 },
    {MAX17205_AD_NCONVGCFG,    0x2241 },
    {MAX17205_AD_NFULLSOCTHR,  0x5005 },
    {MAX17205_AD_NRIPPLECFGCFG,0x0204 },
    {0,0}
};


static const max17205_regval_t batt_cfg[] = {
    {MAX17205_AD_PACKCFG, MAX17205_SETVAL(MAX17205_AD_PACKCFG,
                                          _VAL2FLD(MAX17205_PACKCFG_NCELLS, NCELLS) |
                                          MAX17205_PACKCFG_BALCFG_40 |
                                          MAX17205_PACKCFG_BTEN |
                                          MAX17205_PACKCFG_CHEN |
                                          MAX17205_PACKCFG_TDEN |
                                          MAX17205_PACKCFG_A1EN |
                                          MAX17205_PACKCFG_A2EN )},
    {MAX17205_AD_NRSENSE, MAX17205_RSENSE2REG(10000U)},
    {MAX17205_AD_CONFIG, MAX17205_CONFIG_TEN | MAX17205_CONFIG_ETHRM},
    {0,0}
};


static const MAX17205Config max17205configPack1 = {
    .i2cp = &I2CD1,
    .regcfg = batt_cfg,
    .rsense_uOhm = 10000,
};

static const MAX17205Config max17205configPack2 = {
    .i2cp = &I2CD2,
    .regcfg = batt_cfg,
    .rsense_uOhm = 10000,
};

static MAX17205Driver max17205devPack1;
static MAX17205Driver max17205devPack2;

typedef struct {
    bool is_data_valid;
    uint8_t pack_number;

    uint32_t batt_mV;
    uint16_t v_cell_1_mV;
    uint16_t v_cell_2_mV;
    uint16_t v_cell_mV;
    uint16_t v_cell_avg_mV;
    uint16_t v_cell_max_volt_mV;
    uint16_t v_cell_min_volt_mV;

    int32_t current_mA;
    int32_t avg_current_mA;
    int32_t max_current_mA;
    int32_t min_current_mA;

    uint8_t available_state_of_charge; //Percent
    uint8_t present_state_of_charge; //Percent
    uint8_t reported_state_of_charge; //Percent

    uint32_t time_to_full_seconds;
    uint32_t time_to_empty_seconds;

    uint32_t full_capacity_mAh;
    uint32_t available_capacity_mAh;
    uint32_t mix_capacity_mAh;
    uint32_t reported_capacity_mAh;

    uint16_t cycles; // count

    int16_t temp_1_C;
    int16_t avg_temp_1_C;
    int16_t avg_int_temp_C;
    int8_t temp_min_C;
    int8_t temp_max_C;
} batt_pack_data_t;

static batt_pack_data_t pack_1_data;
static batt_pack_data_t pack_2_data;

battery_heating_state_machine_state_t current_batery_state_machine_state = BATTERY_STATE_MACHINE_STATE_NOT_HEATING;


/**
 * @brief Runs the battery state machine, responsible for turning on/off heaters, charging, discharging etc.
 *
 * @*pk1_data[in] Current data for pack 1
 * @*pk2_data[in] Current data for pack 2
 */
void run_battery_heating_state_machine(batt_pack_data_t *pk1_data, batt_pack_data_t *pk2_data) {
    if (!pk1_data->is_data_valid || !pk2_data->is_data_valid) {
        //Fail safe
        palClearLine(LINE_HEATER_ON_1);
        palClearLine(LINE_HEATER_ON_2);
        palClearLine(LINE_MOARPWR);

        //CO_errorReport(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_HARDWARE, BATTERY_OD_ERROR_INFO_CODE_PACK_FAIL_SAFE_HEATING);
        return;
    }
    const uint16_t total_state_of_charge = (pk1_data->present_state_of_charge + pk2_data->present_state_of_charge) / 2;

    switch (current_batery_state_machine_state) {
        case BATTERY_STATE_MACHINE_STATE_HEATING:
            dbgprintf("Turning heaters ON\r\n");
            palSetLine(LINE_MOARPWR);
            palSetLine(LINE_HEATER_ON_1);
            palSetLine(LINE_HEATER_ON_2);
            //Once they’re greater than 5 °C or the combined pack capacity is < 25%

            if( (pk1_data->avg_temp_1_C > 5 && pk2_data->avg_temp_1_C > 5) || (total_state_of_charge < 25) ) {
                current_batery_state_machine_state = BATTERY_STATE_MACHINE_STATE_NOT_HEATING;
            }
            break;
        case BATTERY_STATE_MACHINE_STATE_NOT_HEATING:
            dbgprintf("Turning heaters OFF\r\n");
            palClearLine(LINE_HEATER_ON_1);
            palClearLine(LINE_HEATER_ON_2);
            palClearLine(LINE_MOARPWR);

            if( (pk1_data->avg_temp_1_C < -5 || pk2_data->avg_temp_1_C < -5) && (pk1_data->present_state_of_charge > 25 || pk2_data->present_state_of_charge > 25) ) {
                current_batery_state_machine_state = BATTERY_STATE_MACHINE_STATE_HEATING;
            }
            break;
        default:
            current_batery_state_machine_state = BATTERY_STATE_MACHINE_STATE_NOT_HEATING;
            break;
    }
}

/**
 * @brief Query the MAX17 chip for a given pack and populate *pk_data with the current status/state represented in the MAX17
 *
 * @param[in] *pk_data Destination into which to store MAX17 pack data.
 * @param[in] line_dchg_dis ioline to control the discharge disable pin.
 * @param[in] line_chg_dis ioline to control of the charge disable pin.
 */
void update_battery_charging_state(batt_pack_data_t *pk_data, const ioline_t line_dchg_dis, const ioline_t line_chg_dis) {
    dbgprintf("LINE_DCHG_STAT_PK1 = %u\r\n", palReadLine(LINE_DCHG_STAT_PK1));
    dbgprintf("LINE_CHG_STAT_PK1 = %u\r\n", palReadLine(LINE_CHG_STAT_PK1));
    dbgprintf("LINE_DCHG_STAT_PK2 = %u\r\n", palReadLine(LINE_DCHG_STAT_PK2));
    dbgprintf("LINE_CHG_STAT_PK2 = %u\r\n", palReadLine(LINE_CHG_STAT_PK2));

    if (!pk_data->is_data_valid) {
        //fail safe mode
        //palSetLine(line_dchg_dis);
        //palSetLine(line_chg_dis);

        //CO_errorReport(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_HARDWARE, BATTERY_OD_ERROR_INFO_CODE_PACK_FAIL_SAFE_CHARGING);
        return;
    }

    if( pk_data->v_cell_mV < 3000 || pk_data->present_state_of_charge < 20 ) {
        //Disable discharge on both packs
        dbgprintf("Disabling discharge on pack %u\r\n", pk_data->pack_number);
        //palSetLine(line_dchg_dis);
    } else {
        dbgprintf("Enabling discharge on pack %u\r\n", pk_data->pack_number);
        //Allow discharge on both packs
        //palClearLine(line_dchg_dis);
    }


    if( pk_data->v_cell_mV > 4100 ) {
        dbgprintf("Disabling charging on pack %u\r\n", pk_data->pack_number);
        //palSetLine(line_chg_dis);
    } else {
        dbgprintf("Enabling charging on pack %u\r\n", pk_data->pack_number);
        //palClearLine(line_chg_dis);
        if( pk_data->present_state_of_charge > 90 ) {
            const int16_t vcell_delta_mV = pk_data->v_cell_1_mV - pk_data->v_cell_2_mV;

            if( vcell_delta_mV < -50 || vcell_delta_mV > 50 ) {
                //TODO command cell  balancing - this appears to be done in hardware based on config registers???
            }
        }
    }
}

/**
 * @param *driver[in] The MAX17 driver object to use to query pack data from
 * @param *dest[out] Destination into which to store pack data currently tracked in the MAX17
 *
 * @return true on success, false otherwise
 */
bool populate_pack_data(MAX17205Driver *driver, batt_pack_data_t *dest) {
    msg_t r = 0;
    memset(dest, 0, sizeof(*dest));

    if( driver->state != MAX17205_READY ) {
        return false;
    }

    dest->is_data_valid = true;


    if( (r = max17205ReadAverageTemperature(driver, MAX17205_AD_TEMP1, &dest->temp_1_C)) != MSG_OK ) {
        dest->is_data_valid = false;
    }
    if( (r = max17205ReadAverageTemperature(driver, MAX17205_AD_AVGTEMP1, &dest->avg_temp_1_C)) != MSG_OK ) {
        dest->is_data_valid = false;
    }
    if( (r = max17205ReadAverageTemperature(driver, MAX17205_AD_AVGINTTEMP, &dest->avg_int_temp_C)) != MSG_OK ) {
        dest->is_data_valid = false;
    }
    if( (r = max17205ReadMaxMinTemperature(driver, &dest->temp_max_C, &dest->temp_min_C)) != MSG_OK ) {
        dest->is_data_valid = false;
    }

    dbgprintf("avg_temp_1_C = %d C, ", dest->avg_temp_1_C);
    dbgprintf("temp_1_C = %d C, ", dest->temp_1_C);
    dbgprintf("avg_int_temp_C = %d C, ", dest->avg_int_temp_C);
    dbgprintf("temp_min_C = %d C, ", dest->temp_min_C);
    dbgprintf("temp_max_C = %d C", dest->temp_max_C);
    dbgprintf("\r\n");

    /* Record pack and cell voltages to object dictionary */
    if( (r = max17205ReadVoltage(driver, MAX17205_AD_AVGCELL1, &dest->v_cell_1_mV)) != MSG_OK ) {
        dest->is_data_valid = false;
    }

    if( (r = max17205ReadVoltage(driver, MAX17205_AD_AVGVCELL, &dest->v_cell_avg_mV)) != MSG_OK ) {
    dest->is_data_valid = false;
   }
    if( (r = max17205ReadVoltage(driver, MAX17205_AD_VCELL, &dest->v_cell_mV)) != MSG_OK ) {
        dest->is_data_valid = false;
    }
    if( (r = max17205ReadBatt(driver, &dest->batt_mV)) != MSG_OK ) {
        dest->is_data_valid = false;
    }

    if( dest->is_data_valid ) {
        dest->v_cell_2_mV = dest->batt_mV - dest->v_cell_1_mV;
    }

    dbgprintf("cell1_mV = %u, cell2_mV = %u, vcell_mV = %u, batt_mV = %u\r\n", dest->v_cell_1_mV, dest->v_cell_2_mV, dest->v_cell_mV, dest->batt_mV);

    if( (r = max17205ReadMaxMinVoltage(driver, &dest->v_cell_max_volt_mV, &dest->v_cell_min_volt_mV)) != MSG_OK ) {
        dest->is_data_valid = false;
    } else {
        dbgprintf("vcell_max_volt_mV = %u, vcell_min_volt_mV = %u\r\n", dest->v_cell_max_volt_mV, dest->v_cell_min_volt_mV);
    }


    if( (r = max17205ReadCurrent(driver, MAX17205_AD_CURRENT, &dest->current_mA)) != MSG_OK ) {
        dest->is_data_valid = false;
    }
    if( (r = max17205ReadCurrent(driver, MAX17205_AD_AVGCURRENT, &dest->avg_current_mA)) != MSG_OK ) {
        dest->is_data_valid = false;
    }

    if( (r = max17205ReadMaxMinCurrent(driver, &dest->max_current_mA, &dest->min_current_mA)) != MSG_OK ) {
        dest->is_data_valid = false;
    } else {
        dbgprintf("max_mA = %d, min_mA = %d\r\n", dest->max_current_mA, dest->min_current_mA);
    }

    dbgprintf("avg_current_mA = %d mA\r\n", dest->avg_current_mA);


    /* capacity */
    if( (r = max17205ReadCapacity(driver, MAX17205_AD_FULLCAPREP, &dest->full_capacity_mAh)) != MSG_OK ) {
        dest->is_data_valid = false;
    }
    if( (r = max17205ReadCapacity(driver, MAX17205_AD_AVCAP, &dest->available_capacity_mAh)) != MSG_OK ) {
        dest->is_data_valid = false;
    }
    if( (r = max17205ReadCapacity(driver, MAX17205_AD_MIXCAP, &dest->mix_capacity_mAh)) != MSG_OK ) {
        dest->is_data_valid = false;
    }
    if( (r = max17205ReadCapacity(driver, /*MAX17205_AD_REPCAP*/ MAX17205_AD_VFREMCAP, &dest->reported_capacity_mAh)) != MSG_OK ) {
        dest->is_data_valid = false;
    }



    dbgprintf("full_capacity_mAh = %u, available_capacity_mAh = %u, mix_capacity = %u, reported_capacity_mAh = %u\r\n",
            dest->full_capacity_mAh, dest->available_capacity_mAh, dest->mix_capacity_mAh, dest->reported_capacity_mAh);

    /* state of charge */
    if( (r = max17205ReadTime(driver, MAX17205_AD_TTE, &dest->time_to_empty_seconds)) != MSG_OK ) {
        dest->is_data_valid = false;
    }
    if( (r = max17205ReadTime(driver, MAX17205_AD_TTF, &dest->time_to_full_seconds)) != MSG_OK ) {
        dest->is_data_valid = false;
    }

    if( (r = max17205ReadPercentage(driver, MAX17205_AD_AVSOC, &dest->available_state_of_charge)) != MSG_OK ) {
        dest->is_data_valid = false;
    }
    if( (r = max17205ReadPercentage(driver, MAX17205_AD_VFSOC, &dest->present_state_of_charge)) != MSG_OK ) {
        dest->is_data_valid = false;
    }
    if( (r = max17205ReadPercentage(driver, MAX17205_AD_REPSOC, &dest->reported_state_of_charge)) != MSG_OK ) {
        dest->is_data_valid = false;
    }


    dbgprintf("time_to_empty = %u (seconds), time_to_full = %u (seconds), available_state_of_charge = %u%%, present_state_of_charge = %u%%\r\n", dest->time_to_empty_seconds, dest->time_to_full_seconds, dest->available_state_of_charge, dest->present_state_of_charge);

    /* other info */
    if( (r = max17205ReadCycles(driver, &dest->cycles)) != MSG_OK ) {
        dest->is_data_valid = false;
    }

    dbgprintf("cycles = %u\r\n", dest->cycles);

    return dest->is_data_valid;
}

/**
 * Helper function to trigger write of volatile memory on MAX71205 chip.
 * Returns true if NV was written, false otherwise.
 */
bool prompt_nv_memory_write(MAX17205Driver *devp, const char *pack_str) {
    dbgprintf("\r\n%s\r\n", pack_str);

    uint16_t masking_register = 0;
    uint8_t num_writes_left = 0;
    if (max17205ReadNVWriteCountMaskingRegister(devp, &masking_register, &num_writes_left) == MSG_OK) {
        dbgprintf("Memory Update Masking of register is 0x%X, num_writes_left = %u\r\n",
            masking_register, num_writes_left);
    }

    bool all_elements_match = false;
    msg_t r = max17205ValidateRegisters(devp, batt_nv_programing_cfg, ARRAY_LEN(batt_nv_programing_cfg), &all_elements_match);
    if (r != MSG_OK) {
        return false;
    }

    if (all_elements_match) {
        dbgprintf("All NV RAM elements already match expected values...\r\n");
        return false;
    }
    dbgprintf("One or more NV RAM elements don't match expected values...\r\n");

#if ENABLE_NV_MEMORY_UPDATE_CODE && defined(DEBUG_PRINT)
    r = max17205WriteRegisters(devp, batt_nv_programing_cfg, ARRAY_LEN(batt_nv_programing_cfg));
    if (r != MSG_OK) {
        dbgprintf("Failed to write new NV RAM reg values\n");
        return false;
    }
    dbgprintf("Successfully wrote new NV RAM reg values\r\n");

    all_elements_match = false;
    r = max17205ValidateRegisters(devp, batt_nv_programing_cfg, ARRAY_LEN(batt_nv_programing_cfg), &all_elements_match);
    if (r != MSG_OK) {
        return false;
    }
    if (!all_elements_match) {
        dbgprintf("NV RAM elements failed to update after write.\r\n");
        return false;
    }
    dbgprintf("All NV RAM elements now match expected values.\r\n");

#if ENABLE_NV_MEMORY_UPDATE_CODE && defined(DEBUG_PRINT)
    // Answer n to just use the changes in the volatile registers
    dbgprintf("Write NV memory on MAX17205 for %s ? y/n? ", pack_str);
    uint8_t ch = 0;
    sdRead(DEBUG_SD, &ch, 1);
    dbgprintf("\r\n");

    if (ch == 'y') {
        dbgprintf("Attempting to write non volatile memory on MAX17205...\r\n");
        chThdSleepMilliseconds(50);

        if (max17205NonvolatileBlockProgram(devp) == MSG_OK ) {
            dbgprintf("Successfully wrote non volatile memory on MAX17205...\r\n");
        } else {
            dbgprintf("Failed to write non volatile memory on MAX17205...\r\n");
        }
        return true; // NV changes made
    }
#endif

    //Now make the chip use the changes written to the shadow registers.
    max17205FirmwareReset(devp);
    return false; // no NV changes made
}

/**
 * @brief Populates CANOpen data structure values with values from the current battery pack data.
 *
 * @param *pack_data[in] Source of data for populating/publishing pack data.
 */
void populate_od_pack_data(batt_pack_data_t *pack_data) {
    uint8_t state_bitmask = 0;

    if (pack_data->pack_number == 1) {
        OD_RAM.x4000_pack_1.vbatt = MIN(pack_data->batt_mV, UINT16_MAX);
        OD_RAM.x4000_pack_1.vcell_max = pack_data->v_cell_max_volt_mV;
        OD_RAM.x4000_pack_1.vcell_min = pack_data->v_cell_min_volt_mV;
        OD_RAM.x4000_pack_1.vcell = pack_data->v_cell_mV;
        OD_RAM.x4000_pack_1.vcell_1 = pack_data->v_cell_1_mV;
        OD_RAM.x4000_pack_1.vcell_2 = pack_data->v_cell_2_mV;
        OD_RAM.x4000_pack_1.vcell_avg = pack_data->v_cell_avg_mV;
        OD_RAM.x4000_pack_1.current = CLAMP(pack_data->current_mA, INT16_MIN, INT16_MAX);
        OD_RAM.x4000_pack_1.current_avg = CLAMP(pack_data->avg_current_mA, INT16_MIN, INT16_MAX);
        OD_RAM.x4000_pack_1.current_max = CLAMP(pack_data->max_current_mA, INT16_MIN, INT16_MAX);
        OD_RAM.x4000_pack_1.current_min = CLAMP(pack_data->min_current_mA, INT16_MIN, INT16_MAX);
        OD_RAM.x4000_pack_1.full_capacity = MIN(pack_data->full_capacity_mAh, UINT16_MAX);
        OD_RAM.x4000_pack_1.reported_capacity = MIN(pack_data->reported_capacity_mAh, UINT16_MAX);
        OD_RAM.x4000_pack_1.time_to_empty = MIN(pack_data->time_to_empty_seconds, UINT16_MAX);
        OD_RAM.x4000_pack_1.time_to_full = MIN(pack_data->time_to_full_seconds, UINT16_MAX);
        OD_RAM.x4000_pack_1.cycles = pack_data->cycles;
        OD_RAM.x4000_pack_1.reported_state_of_charge = pack_data->reported_state_of_charge;
        OD_RAM.x4000_pack_1.temperature = CLAMP(pack_data->temp_1_C, INT8_MIN, INT8_MAX);
        OD_RAM.x4000_pack_1.temperature_avg = CLAMP(pack_data->avg_temp_1_C, INT8_MIN, INT8_MAX);
        OD_RAM.x4000_pack_1.temperature_min = pack_data->temp_min_C;
        OD_RAM.x4000_pack_1.temperature_max = pack_data->temp_max_C;

        if (palReadLine(LINE_HEATER_ON_1)) {
            state_bitmask |= (1 << STATUS_BIT_HEATER);
        }
        if (palReadLine(LINE_DCHG_DIS_PK1)) {
            state_bitmask |= (1 << STATUS_BIT_DCHG_DIS);
        }
        if (palReadLine(LINE_CHG_DIS_PK1)) {
            state_bitmask |= (1 << STATUS_BIT_CHG_DIS);
        }
        if (palReadLine(LINE_DCHG_STAT_PK1)) {
            state_bitmask |= (1 << STATUS_BIT_DCHG_STAT);
        }
        if (palReadLine(LINE_CHG_STAT_PK1)) {
            state_bitmask |= (1 << STATUS_BIT_CHG_STAT);
        }
        OD_RAM.x4000_pack_1.status = state_bitmask;
    } else if (pack_data->pack_number == 2) {
        OD_RAM.x4001_pack_2.vbatt = MIN(pack_data->batt_mV, UINT16_MAX);
        OD_RAM.x4001_pack_2.vcell_max = pack_data->v_cell_max_volt_mV;
        OD_RAM.x4001_pack_2.vcell_min = pack_data->v_cell_min_volt_mV;
        OD_RAM.x4001_pack_2.vcell = pack_data->v_cell_mV;
        OD_RAM.x4001_pack_2.vcell_1 = pack_data->v_cell_1_mV;
        OD_RAM.x4001_pack_2.vcell_2 = pack_data->v_cell_2_mV;
        OD_RAM.x4001_pack_2.vcell_avg = pack_data->v_cell_avg_mV;
        OD_RAM.x4001_pack_2.current = CLAMP(pack_data->current_mA, INT16_MIN, INT16_MAX);
        OD_RAM.x4001_pack_2.current_avg = CLAMP(pack_data->avg_current_mA, INT16_MIN, INT16_MAX);
        OD_RAM.x4001_pack_2.current_max = CLAMP(pack_data->max_current_mA, INT16_MIN, INT16_MAX);
        OD_RAM.x4001_pack_2.current_min = CLAMP(pack_data->min_current_mA, INT16_MIN, INT16_MAX);
        OD_RAM.x4001_pack_2.full_capacity = MIN(pack_data->full_capacity_mAh, UINT16_MAX);
        OD_RAM.x4001_pack_2.reported_capacity = MIN(pack_data->reported_capacity_mAh, UINT16_MAX);
        OD_RAM.x4001_pack_2.time_to_empty = MIN(pack_data->time_to_empty_seconds, UINT16_MAX);
        OD_RAM.x4001_pack_2.time_to_full = MIN(pack_data->time_to_full_seconds, UINT16_MAX);
        OD_RAM.x4001_pack_2.cycles = pack_data->cycles;
        OD_RAM.x4001_pack_2.reported_state_of_charge = pack_data->reported_state_of_charge;
        OD_RAM.x4001_pack_2.temperature = CLAMP(pack_data->temp_1_C, INT8_MIN, INT8_MAX);
        OD_RAM.x4001_pack_2.temperature_avg = CLAMP(pack_data->avg_temp_1_C, INT8_MIN, INT8_MAX);
        OD_RAM.x4001_pack_2.temperature_min = pack_data->temp_min_C;
        OD_RAM.x4001_pack_2.temperature_max = pack_data->temp_max_C;

        if (palReadLine(LINE_HEATER_ON_2)) {
            state_bitmask |= (1 << STATUS_BIT_HEATER);
        }
        if (palReadLine(LINE_DCHG_DIS_PK2)) {
            state_bitmask |= (1 << STATUS_BIT_DCHG_DIS);
        }
        if (palReadLine(LINE_CHG_DIS_PK2)) {
            state_bitmask |= (1 << STATUS_BIT_CHG_DIS);
        }
        if (palReadLine(LINE_DCHG_STAT_PK2)) {
            state_bitmask |= (1 << STATUS_BIT_DCHG_STAT);
        }
        if (palReadLine(LINE_CHG_STAT_PK2)) {
            state_bitmask |= (1 << STATUS_BIT_CHG_STAT);
        }
        OD_RAM.x4001_pack_2.status = state_bitmask;
    }
}


/* Battery monitoring thread */
THD_WORKING_AREA(batt_wa, 0x400);
THD_FUNCTION(batt, arg)
{
    (void)arg;

    max17205ObjectInit(&max17205devPack1);
    max17205ObjectInit(&max17205devPack2);
    const bool pack_1_init_flag = max17205Start(&max17205devPack1, &max17205configPack1);
    dbgprintf("max17205Start(pack1) = %u\r\n", pack_1_init_flag);

#if 0
    max17205PrintintNonvolatileMemory(&max17205configPack1);
    while(1) {
        chThdSleepMilliseconds(1000);
    }
#endif

    const bool pack_2_init_flag = max17205Start(&max17205devPack2, &max17205configPack2);
    dbgprintf("max17205Start(pack2) = %u\r\n", pack_2_init_flag);

#if 1
    bool nv_written = false;

    if( pack_1_init_flag ) {
        nv_written |= prompt_nv_memory_write(&max17205devPack1, "Pack 1");
    } else {
        dbgprintf("Skipping NV prompt for pack 1 as it failed to initialize...\r\n");
    }

    if( pack_2_init_flag ) {
        nv_written |= prompt_nv_memory_write(&max17205devPack2, "Pack 2");
    } else {
        dbgprintf("Skipping NV prompt for pack 2 as it failed to initialize...\r\n");
    }

    if (nv_written) {
        dbgprintf("Done with NV RAM update code, disable ENABLE_NV_MEMORY_UPDATE_CODE and re-write firmware.\r\n");
        for (;;) {
            dbgprintf(".");
            chThdSleepMilliseconds(1000);
        }
    }
#endif

    uint32_t loop = 0;
    while (!chThdShouldTerminateX()) {
        loop++;
        chThdSleepMilliseconds(500);
        palToggleLine(LINE_LED);
        if (loop % 2 == 0) {
            continue; // we want light to blink at 2Hz, but code to run at 1Hz
        }

        dbgprintf("================================= %u ms\r\n", TIME_I2MS(chVTGetSystemTime()));

        dbgprintf("Populating Pack 1 Data\r\n");
        if (populate_pack_data(&max17205devPack1, &pack_1_data) ) {
            pack_1_data.pack_number = 1;
            populate_od_pack_data(&pack_1_data);
        } else {
           // CO_errorReport(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_COMMUNICATION, BATTERY_OD_ERROR_INFO_CODE_PACK_1_COMM_ERROR);
        }

        dbgprintf("\r\nPopulating Pack 2 Data\r\n");
        if (populate_pack_data(&max17205devPack2, &pack_2_data) ) {
            pack_2_data.pack_number = 2;
            populate_od_pack_data(&pack_2_data);
        } else {
            //CO_errorReport(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_COMMUNICATION, BATTERY_OD_ERROR_INFO_CODE_PACK_2_COMM_ERROR);
        }

        run_battery_heating_state_machine(&pack_1_data, &pack_2_data);
        update_battery_charging_state(&pack_1_data, LINE_DCHG_DIS_PK1, LINE_CHG_DIS_PK1);
        update_battery_charging_state(&pack_2_data, LINE_DCHG_DIS_PK2, LINE_CHG_DIS_PK2);
    }

    dbgprintf("Terminating battery thread...\r\n");

    max17205Stop(&max17205devPack1);
    max17205Stop(&max17205devPack2);

    palClearLine(LINE_LED);
    chThdExit(MSG_OK);
}
