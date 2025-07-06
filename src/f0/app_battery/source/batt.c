#include "ch.h"
#include "batt.h"
#include "max17205.h"
#include "CANopen.h"
#include "OD.h"
#include "chtime.h"
#include "oresat_f0.h"
#include "flash_f0.h"
#include "crc.h"
#include <sys/param.h>
#include <string.h>

//Dump complete battery history
//#define VERBOSE_DEBUG 1

//If batt_nv_programing_cfg registers do not match current, rewrite the RAM shadow then prompt to write to NV.
#define ENABLE_NV_MEMORY_UPDATE_CODE 0
#define NV_WRITE_PROMPT_TIMEOUT_S 15

//If state of charge is known to be full, set LS bits D6-D0 of LearnCfg register to 0b111
//and write MixCap and RepCap registers to 2600.
#define ENABLE_LEARN_COMPLETE 0

//This was disabled per discussion in Slack on April 25, 2021.
#define ENABLE_CHARGING_CONTROL 0

#if defined(DEBUG_PRINT) && ENABLE_NV_MEMORY_UPDATE_CODE
#define ENABLE_NV_WRITE_PROMPT 1
#endif

//Voltage below which we should stop everything until charging starts
#define SHUTDOWN_MV 2850

//Full battery detection thresholds
#define BATT_FULL_THRESHOLD_MV 8000
#define EOC_THRESHOLD_MA 50
#define CELL_CAPACITY_MAH 2600
#define CELL_CAPACITY_MAH_RAW 0x1450

#define MAX_HIST_STORE_RETRIES 4
#define RUNTIME_BATT_STORE_INTERVAL_MS 300000U // 5 minutes

#ifdef DEBUG_PRINT
#include "chprintf.h"
#define DEBUG_SD &SD2
#define dbgprintf(str, ...) chprintf((BaseSequentialStream *)DEBUG_SD, str, ##__VA_ARGS__)
#else
#define dbgprintf(str, ...)
#endif

#define ARRAY_LEN(x) (sizeof(x)/sizeof(x[0]))
#define CLAMP(val, low, high) MIN(MAX(val, low), high)

#define NCELLS          2U          /* Number of cells per pack */
#define NPACKS          2U          /* Number of packs */

//Some of the code and data below requires 2 packs of 2 cells. Any other configuration may require changes.
STATIC_ASSERT(NCELLS == 2);
STATIC_ASSERT(NPACKS == 2);

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
static const uint16_t PACKCFG = (_VAL2FLD(MAX17205_PACKCFG_NCELLS, NCELLS) |
                                 MAX17205_PACKCFG_BALCFG_40 |
                                 MAX17205_PACKCFG_BTEN |
                                 MAX17205_PACKCFG_CHEN |
                                 MAX17205_PACKCFG_TDEN |
                                 MAX17205_PACKCFG_A1EN |
                                 MAX17205_PACKCFG_A2EN);

static const max17205_regval_t batt_nv_programing_cfg[] = {
    {MAX17205_AD_NPACKCFG,     PACKCFG },
    {MAX17205_AD_NNVCFG0,      0x09A0 }, // was 0x00B0 -- try Wizard=0x09A0 (old comment: 0x0920)
    {MAX17205_AD_NNVCFG1,      0x8006 }, // was 0xC000 -- try Wizard=0x8006
    {MAX17205_AD_NNVCFG2,      0xFF0A }, // life logging every 10 cycles
    {MAX17205_AD_NICHGTERM,    0x014D }, // was 0x0034 -- try Wizard=0x14D
    {MAX17205_AD_NVEMPTY,      0x965A }, // VE = 0x12C * 10mV = 3.0v; VR = 0x5A * 40mV = 3.6v
    {MAX17205_AD_NTCURVE,      0x0064 },
    {MAX17205_AD_NTGAIN,       0xF49A },
    {MAX17205_AD_NTOFF,        0x16A1 },
    {MAX17205_AD_NDESIGNCAP,   0x1450 }, // 5200 (0.5 increments)
    {MAX17205_AD_NFULLCAPREP,  0x1450 },
    {MAX17205_AD_NFULLCAPNOM,  0x1A22 }, // Wizard=0x1794; full learning cycle found 0x1A22 on average of 2 packs

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
    {MAX17205_AD_NRCOMP0,      0x006F }
};

static const max17205_regval_t batt_cfg[] = {
    {MAX17205_AD_PACKCFG, PACKCFG},
    {MAX17205_AD_NRSENSE, MAX17205_RSENSE2REG(10000U)},
    {MAX17205_AD_CONFIG, MAX17205_CONFIG_TEN | MAX17205_CONFIG_ETHRM}
};

typedef struct {
    bool is_data_valid;

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
    int16_t temp_2_C;
    int16_t int_temp_C;
    int16_t avg_temp_1_C;
    int16_t avg_temp_2_C;
    int16_t avg_int_temp_C;
    int8_t temp_min_C;
    int8_t temp_max_C;
} batt_pack_data_t;

static battery_heating_state_machine_state_t current_battery_state_machine_state = BATTERY_STATE_MACHINE_STATE_NOT_HEATING;

// All state for a pack is contained in this structure.
typedef struct pack {
    bool init;
    bool updated;
    MAX17205Driver drvr;
    MAX17205Config conf;
    batt_pack_data_t data;
    ioline_t heater_on;
    ioline_t line_dchg_dis;
    ioline_t line_chg_dis;
    ioline_t line_dchg_stat;
    ioline_t line_chg_stat;
    uint8_t pack_number;
    char *name;
} pack_t;

// All packs defined here, including non-zero initial data.
static pack_t packs[NPACKS] = {
    {.conf.i2cp = &I2CD1,
     .conf.regcfg = batt_cfg,
     .conf.rsense_uOhm = 10000,
     .heater_on = LINE_HEATER_ON_1,
     .line_dchg_dis = LINE_DCHG_DIS_PK1,
     .line_chg_dis = LINE_CHG_DIS_PK1,
     .line_dchg_stat = LINE_DCHG_STAT_PK1,
     .line_chg_stat = LINE_CHG_STAT_PK1,
     .pack_number = 1,
     .name = "Pack 1"},
    {.conf.i2cp = &I2CD2,
     .conf.regcfg = batt_cfg,
     .conf.rsense_uOhm = 10000,
     .heater_on = LINE_HEATER_ON_2,
     .line_dchg_dis = LINE_DCHG_DIS_PK2,
     .line_chg_dis = LINE_CHG_DIS_PK2,
     .line_dchg_stat = LINE_DCHG_STAT_PK2,
     .line_chg_stat = LINE_CHG_STAT_PK2,
     .pack_number = 2,
     .name = "Pack 2"}
};

// raw register values to store at runtime per pack;
// restoring after a reset should result in accurate
// fuel gauge estimates
typedef struct __attribute__((packed)) runtime_pack_data {
    uint16_t mixcap; // MAX17205_AD_MIXCAP
    uint16_t repcap; // MAX17205_AD_REPCAP
} runtime_pack_data_t;

// entry to append to already-written flash at next update interval
typedef struct __attribute__((packed)) runtime_battery_data {
    runtime_pack_data_t packs[NPACKS];
    uint32_t rst_cycle : 16;    // number of reset cycles so far
    uint32_t minute : 12;       // number of minutes so far during a cycle
    uint32_t unused : 3;        // must be 0
    uint32_t estimated : 1;     // set to 1 if previous value was invalid or none found in flash
    uint32_t crc;               // crc calculated over all fields prior to this field
} runtime_battery_data_t;

#define NUM_BATT_HIST_ENTRIES ((STM32F093_FLASH_PAGE_SIZE) / sizeof(runtime_battery_data_t))
runtime_battery_data_t *battery_history = (runtime_battery_data_t *) __flash3_base__;
static runtime_battery_data_t *last_used;
static runtime_battery_data_t last_batt_hist_entry;

static void print_runtime_entry(runtime_battery_data_t *data)
{
    dbgprintf("rst_cycle=%d, minute=%d, unused=%d, estimated=%d, crc=0x%08X\r\n",
              data->rst_cycle, data->minute, data->unused, data->estimated, data->crc);
    for (unsigned int j = 0; j < NPACKS; j++) {
        dbgprintf("   pack %u: mixcap:0x%04X, repcap:0x%04X\r\n", j + 1, data->packs[j].mixcap, data->packs[j].repcap);
    }
}

static void print_batt_hist(void)
{
    runtime_battery_data_t *data = battery_history;

    dbgprintf("Runtime battery history:\r\nentry size=%lu, entry count=%u\r\n",
              sizeof(runtime_battery_data_t), NUM_BATT_HIST_ENTRIES);

    for (unsigned int i = 0; i < NUM_BATT_HIST_ENTRIES; i++) {
        if (!flashIsErasedF091((flashaddr_t)data, sizeof(runtime_battery_data_t))) {
            dbgprintf("%u. ", i);
            print_runtime_entry(data);
        } else {
            dbgprintf("%u. Found erased entry. Done.\r\n", i);
            break;
        }
        data++;
    }
}

static void find_last_batt_hist(void)
{
    runtime_battery_data_t *data = battery_history;
    last_used = NULL;

    for (unsigned int i = 0; i < NUM_BATT_HIST_ENTRIES; i++) {
        if (flashIsErasedF091((flashaddr_t)data, sizeof(runtime_battery_data_t))) {
            break;
        }
        uint32_t check_crc = crc32((uint8_t *)data, sizeof(*data) - sizeof(data->crc), 0);
        bool good = true;

        if (check_crc == data->crc) {
            for (unsigned int j = 0; j < NPACKS; j++) {
                if ((data->packs[j].mixcap > CELL_CAPACITY_MAH_RAW) ||
                    (data->packs[j].repcap > CELL_CAPACITY_MAH_RAW)) {
                    good = false;
                    dbgprintf("Values out of range on entry %u pack %u\r\n", i, j + 1);
                }
            }
            if (good) {
                last_used = data;
            }
        } else {
            dbgprintf("CRC failure on entry %u\r\n", i);
        }
        data++;
    }
    if (last_used != NULL) {
        dbgprintf("Selected last used runtime entry:\r\n");
        print_runtime_entry(last_used);
        memcpy(&last_batt_hist_entry, last_used, sizeof(last_batt_hist_entry));
        // We have started a new cycle, so advance this counter now (used below)
        last_batt_hist_entry.rst_cycle++;
    }
}

static bool add_next_batt_hist(runtime_battery_data_t *new_data)
{
    if (last_used == NULL) {
        last_used = battery_history;
    } else {
        last_used++;
    }

    if (last_used < &battery_history[NUM_BATT_HIST_ENTRIES]) {
        if (flashWriteF091((flashaddr_t)last_used, (uint8_t *)new_data, sizeof(runtime_battery_data_t)) == FLASH_RETURN_SUCCESS) {
            return true;
        } else {
            dbgprintf("Error writing to flash\r\n");
        }
    }
    last_used = NULL;
    return false;
}

static void load_latest_batt_hist(pack_t *pack)
{
    if (last_used == NULL) {
        dbgprintf("No latest battery history to load\r\n");
        return;
    }

    msg_t r;

    dbgprintf("Loading entry to pack %u:\r\n", pack->pack_number);
    print_runtime_entry(last_used);
    r = max17205Write(&pack->drvr, MAX17205_AD_MIXCAP, last_used->packs[pack->pack_number - 1].mixcap);
    r = max17205Write(&pack->drvr, MAX17205_AD_REPCAP, last_used->packs[pack->pack_number - 1].repcap);
}

static bool store_current_batt_hist(void)
{
    runtime_battery_data_t new_data;
    unsigned int i;
    msg_t r;
    uint16_t tmp;

    for (i = 0; i < NPACKS; i++) {
        r = max17205Read(&packs[i].drvr, MAX17205_AD_MIXCAP, &tmp);
        if (r != MSG_OK) {
            new_data.packs[i].mixcap = 0;
        } else {
            new_data.packs[i].mixcap = tmp;
        }
        r = max17205Read(&packs[i].drvr, MAX17205_AD_REPCAP, &tmp);
        if (r != MSG_OK) {
            new_data.packs[i].repcap = 0;
        } else {
            new_data.packs[i].repcap = tmp;
        }
    }
    new_data.rst_cycle = last_batt_hist_entry.rst_cycle;
    new_data.minute = TIME_I2S(chVTGetSystemTime()) / 60;
    new_data.unused = 0;
    new_data.estimated = false;
    new_data.crc = crc32((uint8_t *)&new_data, sizeof(new_data) - sizeof(new_data.crc), 0);
    dbgprintf("Storing new runtime battery entry:\r\n");
    print_runtime_entry(&new_data);
    for (i = 0; i < MAX_HIST_STORE_RETRIES; i++) {
        if (add_next_batt_hist(&new_data)) {
            memcpy(&last_batt_hist_entry, &new_data, sizeof(last_batt_hist_entry));
            dbgprintf("Done.\r\n");
            return true;
        } else {
            dbgprintf("Erasing page.\r\n");
            flashEraseF091((flashaddr_t)battery_history, STM32F093_FLASH_PAGE_SIZE);
        }
    }
    dbgprintf("ERROR: Unable to store current battery history.\r\n");
    return false;
}

/**
 * @brief Runs the battery state machine, responsible for turning on/off heaters, charging, discharging etc.
 */
static void run_battery_heating_state_machine(void) {
    unsigned int i;

    for (i = 0; i < NPACKS; i++) {
        if (!packs[i].data.is_data_valid) {
            //Fail safe
            palClearLine(LINE_HEATER_ON_1);
            palClearLine(LINE_HEATER_ON_2);
            palClearLine(LINE_MOARPWR);
            dbgprintf("FAILSAFE: turning heaters OFF\r\n");
            //CO_errorReport(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_HARDWARE, BATTERY_OD_ERROR_INFO_CODE_PACK_FAIL_SAFE_HEATING);
            return;
        }
    }

    switch (current_battery_state_machine_state) {
        case BATTERY_STATE_MACHINE_STATE_HEATING:
            palSetLine(LINE_MOARPWR);
            palSetLine(LINE_HEATER_ON_1);
            palSetLine(LINE_HEATER_ON_2);

            //Once they’re greater than 5 °C or the combined pack capacity is < 25%
            bool warm_enough = true;
            uint16_t total_state_of_charge = 0;
            for (i = 0; i < NPACKS; i++) {
                if( packs[i].data.avg_temp_1_C <= 5 ) {
                    warm_enough = false;
                }
                total_state_of_charge += packs[i].data.present_state_of_charge;
            }
            total_state_of_charge /= NPACKS;
            if( warm_enough || (total_state_of_charge < 25) ) {
                current_battery_state_machine_state = BATTERY_STATE_MACHINE_STATE_NOT_HEATING;
                dbgprintf("Turning heaters OFF\r\n");
            }
            break;
        case BATTERY_STATE_MACHINE_STATE_NOT_HEATING:
            palClearLine(LINE_HEATER_ON_1);
            palClearLine(LINE_HEATER_ON_2);
            palClearLine(LINE_MOARPWR);

            //Once they’re less than -5 °C and the combined pack capacity is > 25%
            bool too_cold = false;
            bool full_enough = false;
            for (i = 0; i < NPACKS; i++) {
                if( packs[i].data.avg_temp_1_C < -5 ) {
                    too_cold = true;
                }
                if( packs[i].data.present_state_of_charge > 25 ) {
                    full_enough = true;
                }
            }
            if( too_cold && full_enough ) {
                current_battery_state_machine_state = BATTERY_STATE_MACHINE_STATE_HEATING;
                dbgprintf("Turning heaters ON\r\n");
            }
            break;
        default:
            current_battery_state_machine_state = BATTERY_STATE_MACHINE_STATE_NOT_HEATING;
            dbgprintf("Unknown state: turning heaters OFF\r\n");
            break;
    }
}

/**
 * @brief Query the MAX17 chip for a given pack and populate *pk_data with the current status/state represented in the MAX17
 *
 * @param[in] *pack Destination into which to store MAX17205
 *       pack data.
 */
static void update_battery_charging_state(const pack_t *pack) {
    dbgprintf("LINE_DCHG_STAT_PK%d = %u\r\n", pack->pack_number, palReadLine(pack->line_dchg_stat));
    dbgprintf("LINE_CHG_STAT_PK%d  = %u\r\n", pack->pack_number, palReadLine(pack->line_chg_stat));

#if !ENABLE_CHARGING_CONTROL
    (void)pack;
#else
    const batt_pack_data_t * const pk_data = &pack->data;

    if (!pk_data->is_data_valid) {
        //fail safe mode
        palSetLine(pack->line_dchg_dis);
        palSetLine(pack->line_chg_dis);
        dbgprintf("ERROR: %s data is invalid; disabling charging and discharging\r\n", pack->name);
        //CO_errorReport(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_HARDWARE, BATTERY_OD_ERROR_INFO_CODE_PACK_FAIL_SAFE_CHARGING);
        return;
    }
    if( pk_data->v_cell_mV < 3000 || pk_data->present_state_of_charge < 20 ) {
        //Disable discharge on both packs
        dbgprintf("Disabling discharge on pack %u\r\n", pack->pack_number);
        palSetLine(pack->line_dchg_dis);
    } else {
        dbgprintf("Enabling discharge on pack %u\r\n", pack->pack_number);
        //Allow discharge on both packs
        palClearLine(pack->line_dchg_dis);
    }


    if( pk_data->v_cell_mV > 4100 ) {
        dbgprintf("Disabling charging on pack %u\r\n", pack->pack_number);
        palSetLine(pack->line_chg_dis);
    } else {
        dbgprintf("Enabling charging on pack %u\r\n", pack->pack_number);
        palClearLine(pack->line_chg_dis);
    }
#endif
}

/**
 * @param *driver[in] The MAX17 driver object to use to query pack data from
 * @param *dest[out] Destination into which to store pack data currently tracked in the MAX17
 *
 * @return true on success, false otherwise
 */
static bool populate_pack_data(MAX17205Driver *driver, batt_pack_data_t *dest) {
    msg_t r = 0;
    memset(dest, 0, sizeof(*dest));

    if( driver->state != MAX17205_READY ) {
        return false;
    }

    dest->is_data_valid = true;


    if( (r = max17205ReadAverageTemperature(driver, MAX17205_AD_TEMP1, &dest->temp_1_C)) != MSG_OK ) {
        dest->is_data_valid = false;
    }
    if( (r = max17205ReadAverageTemperature(driver, MAX17205_AD_TEMP2, &dest->temp_2_C)) != MSG_OK ) {
        dest->is_data_valid = false;
    }
    if( (r = max17205ReadAverageTemperature(driver, MAX17205_AD_INTTEMP, &dest->int_temp_C)) != MSG_OK ) {
        dest->is_data_valid = false;
    }
    if( (r = max17205ReadAverageTemperature(driver, MAX17205_AD_AVGTEMP1, &dest->avg_temp_1_C)) != MSG_OK ) {
        dest->is_data_valid = false;
    }
    if( (r = max17205ReadAverageTemperature(driver, MAX17205_AD_AVGTEMP2, &dest->avg_temp_2_C)) != MSG_OK ) {
        dest->is_data_valid = false;
    }
    if( (r = max17205ReadAverageTemperature(driver, MAX17205_AD_AVGINTTEMP, &dest->avg_int_temp_C)) != MSG_OK ) {
        dest->is_data_valid = false;
    }
    if( (r = max17205ReadMaxMinTemperature(driver, &dest->temp_max_C, &dest->temp_min_C)) != MSG_OK ) {
        dest->is_data_valid = false;
    }

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

    if( (r = max17205ReadMaxMinVoltage(driver, &dest->v_cell_max_volt_mV, &dest->v_cell_min_volt_mV)) != MSG_OK ) {
        dest->is_data_valid = false;
    }

    if( (r = max17205ReadCurrent(driver, MAX17205_AD_CURRENT, &dest->current_mA)) != MSG_OK ) {
        dest->is_data_valid = false;
    }
    if( (r = max17205ReadCurrent(driver, MAX17205_AD_AVGCURRENT, &dest->avg_current_mA)) != MSG_OK ) {
        dest->is_data_valid = false;
    }

    if( (r = max17205ReadMaxMinCurrent(driver, &dest->max_current_mA, &dest->min_current_mA)) != MSG_OK ) {
        dest->is_data_valid = false;
    }

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
    if( (r = max17205ReadCapacity(driver, MAX17205_AD_REPCAP, &dest->reported_capacity_mAh)) != MSG_OK ) {
        dest->is_data_valid = false;
    }

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

    /* other info */
    if( (r = max17205ReadCycles(driver, &dest->cycles)) != MSG_OK ) {
        dest->is_data_valid = false;
    }

    dbgprintf("\r\n");

    dbgprintf("Temperature (C): Th1: avg = %d, cur = %d, Th2: avg = %d, cur = %d, Int: avg = %d, cur = %d, max = %d, min = %d\r\n",
              dest->avg_temp_1_C, dest->temp_1_C, dest->avg_temp_2_C, dest->temp_2_C, dest->avg_int_temp_C, dest->int_temp_C, dest->temp_min_C, dest->temp_max_C);

    dbgprintf("Voltage (mV):    cell1 = %u, cell2 = %u, vcell = %u, max = %d, min %d, batt = %u\r\n",
              dest->v_cell_1_mV, dest->v_cell_2_mV, dest->v_cell_mV, dest->v_cell_max_volt_mV, dest->v_cell_min_volt_mV, dest->batt_mV);

    dbgprintf("Current (mA):    cur = %d, max = %d, min = %d, avg = %d\r\n",
              dest->current_mA, dest->max_current_mA, dest->min_current_mA, dest->avg_current_mA);

    dbgprintf("Capacity (mAh):  full = %u, available = %u, mix = %u, reported = %u\r\n",
              dest->full_capacity_mAh, dest->available_capacity_mAh, dest->mix_capacity_mAh, dest->reported_capacity_mAh);

    dbgprintf("Time (seconds):  to_empty =%u, to_full = %u\r\n",
              dest->time_to_empty_seconds, dest->time_to_full_seconds);

    dbgprintf("SOC (%%):         reported = %u%%\r\n",
              dest->reported_state_of_charge);

    dbgprintf("cycles = %u\r\n", dest->cycles);

    dbgprintf("\r\n");

    return dest->is_data_valid;
}

/**
 * Helper function to trigger write of volatile memory on MAX71205 chip.
 * Returns true if NV RAM was written, false otherwise.
 */
static bool nv_ram_write(MAX17205Driver *devp, const char *pack_str) {
#ifndef DEBUG_PRINT
    (void)pack_str;
#endif
    dbgprintf("\r\nEnsure NV RAM settings are correct for %s\r\n", pack_str);

    bool all_elements_match = false;
    msg_t r = max17205ValidateRegisters(devp, batt_nv_programing_cfg, ARRAY_LEN(batt_nv_programing_cfg), &all_elements_match);
    if (r != MSG_OK) {
        return false;
    }

    if (all_elements_match) {
        dbgprintf("All NV RAM elements already match expected values...\r\n");
        return false;
    } else {
        dbgprintf("One or more NV RAM elements don't match expected values...\r\n");
    }

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

    //Now make the chip use the changes written to the shadow registers.
    max17205FirmwareReset(devp);
    return true;
}

/**
 * Helper function to trigger write of volatile memory on MAX71205 chip.
 * Returns true if NV was written, false otherwise.
 */
#if defined(DEBUG_PRINT) && ENABLE_NV_MEMORY_UPDATE_CODE
static bool prompt_nv_write(MAX17205Driver *devp, const char *pack_str) {
    dbgprintf("\r\nWrite NV RAM to NV%s\r\n", pack_str);

    uint16_t masking_register = 0;
    uint8_t num_writes_left = 0;
    if (max17205ReadNVWriteCountMaskingRegister(devp, &masking_register, &num_writes_left) == MSG_OK) {
        dbgprintf("Memory Update Masking of register is 0x%X, num_writes_left = %u\r\n",
            masking_register, num_writes_left);
    }

    if (num_writes_left > 0) {
        // Answer n to just use the changes in the volatile registers
        dbgprintf("Write NV memory on MAX17205 for %s ? y/n? ", pack_str);
        uint8_t ch = 0;
        sdReadTimeout(DEBUG_SD, &ch, 1, TIME_S2I(NV_WRITE_PROMPT_TIMEOUT_S)); // wait for input but timeout
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
        } else {
            dbgprintf("Update skipped.\r\n");
        }
    } else {
        dbgprintf("No more NV writes remain.\r\n");
    }

    return false; // no NV changes made
}
#endif // defined(DEBUG_PRINT) && ENABLE_NV_MEMORY_UPDATE_CODE

//If state of charge is known to be full, set LS bits D6-D0 of LearnCfg register to 0b111
//and write MixCap and RepCap registers to 2600.
#if ENABLE_LEARN_COMPLETE && defined(DEBUG_PRINT)
static bool update_learning_complete(MAX17205Driver *devp, pack_t *pack) {
    batt_pack_data_t *pack_data = &pack->data;
    bool ret = false;

    if ((pack_data->batt_mV > BATT_FULL_THRESHOLD_MV) &&
        (pack_data->avg_current_mA < EOC_THRESHOLD_MA) &&
        (pack_data->avg_current_mA >= 0) &&
        (pack_data->full_capacity_mAh >= CELL_CAPACITY_MAH) ) {

        dbgprintf("Pack %d seems full\r\n", pack->pack_number);
        uint8_t state;
        msg_t r = max17205ReadLearnState(devp, &state);
        if (r != MSG_OK) {
            dbgprintf("Error reading learn state\r\n");
            return ret;
        }
        dbgprintf("Learning state = %u\r\n", state);
        if (state == MAX17205_LEARN_COMPLETE) {
            dbgprintf("Learning is already complete.\r\n");
        } else {
            r = max17205WriteLearnState(devp, MAX17205_LEARN_COMPLETE);
            if (r != MSG_OK) {
                dbgprintf("Error writing learn state\r\n");
                return ret;
            }
            r = max17205ReadLearnState(devp, &state);
            if (r != MSG_OK) {
                dbgprintf("Error checking learn state\r\n");
                return ret;
            }
            if (state != 7) {
                dbgprintf("Error setting state = %u; is %u\r\n", MAX17205_LEARN_COMPLETE, state);
                return ret;
            }
            dbgprintf("Learning state set = %u\r\n", state);
            ret = true;
        }
        pack_data->mix_capacity_mAh = pack_data->reported_capacity_mAh = pack_data->full_capacity_mAh;
        if ( (r = max17205WriteCapacity(devp, MAX17205_AD_MIXCAP, pack_data->mix_capacity_mAh)) != MSG_OK ) {
            dbgprintf("Failed to write MIXCAP\r\n");
        } else if ( (r = max17205WriteCapacity(devp, MAX17205_AD_REPCAP, pack_data->reported_capacity_mAh)) != MSG_OK ) {
            dbgprintf("Failed to write REPCAP\r\n");
        } else {
            dbgprintf("Mixcap and repcap set to %u\r\n", pack_data->full_capacity_mAh);
        }
        return ret;
    }
    return false;
}
#endif // ENABLE_LEARN_COMPLETE


/**
 * @brief Populates CANOpen data structure values with values from the current battery pack data.
 *
 * @param *pack_data[in] Source of data for populating/publishing pack data.
 */
static void populate_od_pack_data(pack_t *pack) {
    batt_pack_data_t *pack_data = &pack->data;
    uint8_t state_bitmask = 0;

    if( palReadLine(pack->heater_on) ) {
        state_bitmask |= (1 << STATUS_BIT_HEATER);
    }
    if( palReadLine(pack->line_dchg_dis) ) {
        state_bitmask |= (1 << STATUS_BIT_DCHG_DIS);
    }
    if (palReadLine(pack->line_chg_dis) ) {
        state_bitmask |= (1 << STATUS_BIT_CHG_DIS);
    }
    if( palReadLine(pack->line_dchg_stat) ) {
        state_bitmask |= (1 << STATUS_BIT_DCHG_STAT);
    }
    if( palReadLine(pack->line_chg_stat) ) {
        state_bitmask |= (1 << STATUS_BIT_CHG_STAT);
    }

    if (pack->pack_number == 1) {
        OD_RAM.x4000_pack_1.status = state_bitmask;
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
    } else if (pack->pack_number == 2) {
        OD_RAM.x4001_pack_2.status = state_bitmask;
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
    } else {
        dbgprintf("ERROR: pack number not expected: %d\r\n", pack->pack_number);
    }
}

static bool check_for_low_batteries(void)
{
    msg_t r;
    unsigned int i;

    dbgprintf("Check for critically low batteries\r\n");
    for (i = 0; i < NPACKS; i++) {
        if ((r = max17205ReadVoltage(&packs[i].drvr, MAX17205_AD_AVGCELL1, &packs[i].data.v_cell_1_mV)) != MSG_OK) {
            packs[i].data.v_cell_1_mV = 0;
        }
        if ((r = max17205ReadBatt(&packs[i].drvr, &packs[i].data.batt_mV)) != MSG_OK) {
            packs[i].data.batt_mV = 0;
        }
        packs[i].data.v_cell_2_mV = packs[i].data.batt_mV - packs[i].data.v_cell_1_mV;
        if ((packs[i].data.v_cell_1_mV < SHUTDOWN_MV) || (packs[i].data.v_cell_2_mV < SHUTDOWN_MV)) {
            dbgprintf("Batteries are critically low!\r\n");
            return true;
        }
    }

    dbgprintf("Batteries are not critically low\r\n");
    return false;
}

static void wait_for_charge(void)
{
    msg_t r;
    unsigned int i;

    dbgprintf("Critically low batteries; waiting for charging...\r\n");
    while (!chThdShouldTerminateX()) {
        chThdSleepMilliseconds(5000);
        palToggleLine(LINE_LED);

        for (i = 0; i < NPACKS; i++) {
            if ((r = max17205ReadCurrent(&packs[i].drvr, MAX17205_AD_CURRENT, &packs[i].data.current_mA)) != MSG_OK) {
                packs[i].data.current_mA = 0;
            }
            if (packs[i].data.current_mA > 20) {
                dbgprintf("Charging detected -- continuing\r\n");
                return;
            }
        }
        if (!check_for_low_batteries()) {
            break;
        }
    }
}

static void manage_calibration(void)
{
#if defined(DEBUG_PRINT)
    unsigned int i;
#if defined(ENABLE_NV_WRITE_PROMPT)
    bool nv_written = false;
#endif

    for (i = 0; i < NPACKS; i++) {
        dbgprintf("%s:\r\n", packs[i].name);
        max17205PrintVolatileMemory(&packs[i].drvr);

#if ENABLE_LEARN_COMPLETE
        // If ENABLE_LEARN_COMPLETE and ENABLE_NV_MEMORY_UPDATE_CODE and DEBUG_PRINT are all enabled, we will only prompt to update
        // NV when learning is complete. If ENABLE_LEARN_COMPLETE is not enabled but the others are, then we will only prompt to update
        // NV if there is a change to NV RAM required (done prior to the main loop).
        packs[i].updated = update_learning_complete(&packs[i].drvr, &packs[i]);
#endif
#if defined(ENABLE_NV_WRITE_PROMPT)
        if (packs[i].init && packs[i].updated) {
            nv_written |= prompt_nv_write(&packs[i].drvr, packs[i].name);
            packs[i].updated = false;
        }
#endif
    }

#if defined(ENABLE_NV_WRITE_PROMPT)
    if (nv_written) {
        dbgprintf("Done with NV RAM update code, disable ENABLE_NV_MEMORY_UPDATE_CODE and re-write firmware.\r\n");
        for (;;) {
            dbgprintf(".");
            chThdSleepMilliseconds(1000);
        }
    }
#endif
#endif
}

/* Battery monitoring thread */
THD_WORKING_AREA(batt_wa, 0x400);
THD_FUNCTION(batt, arg)
{
    (void)arg;
    unsigned int i;

#if defined(VERBOSE_DEBUG)
    print_batt_hist();
#endif
    find_last_batt_hist();

    for (i = 0; i < NPACKS; i++) {
        max17205ObjectInit(&packs[i].drvr);
        packs[i].init = max17205Start(&packs[i].drvr, &packs[i].conf);
        dbgprintf("max17205Start(%s) = %u\r\n", packs[i].name, packs[i].init);
    }

    if (check_for_low_batteries()) {
        wait_for_charge();
    }

    for (i = 0; i < NPACKS; i++) {
        packs[i].updated = nv_ram_write(&packs[i].drvr, packs[i].name);

        max17205PrintVolatileMemory(&packs[i].drvr);
        max17205PrintNonvolatileMemory(&packs[i].drvr);
#if defined(VERBOSE_DEBUG)
        max17205ReadHistory(&packs[i].drvr);
#endif
    }

    // Let MAX17205s startup and run for a bit. Overwriting the MIXCAP and REPCAP values
    // too quickly leads to bad measurements otherwise.
    chThdSleepMilliseconds(500);
    for (i = 0; i < NPACKS; i++) {
        load_latest_batt_hist(&packs[i]);
    }

    uint32_t loop = 0;
    uint32_t ms = 0;
    uint32_t next_update_ms = RUNTIME_BATT_STORE_INTERVAL_MS;

    while (!chThdShouldTerminateX()) {
        loop++;
        chThdSleepMilliseconds(500);
        palToggleLine(LINE_LED);
        if (loop % 2 == 0) {
            continue; // we want light to blink at 2Hz, but code to run at 1Hz
        }

        ms = TIME_I2MS(chVTGetSystemTime());

        if (ms >= next_update_ms) {
            next_update_ms = ms + RUNTIME_BATT_STORE_INTERVAL_MS;
            store_current_batt_hist();
        }

#if defined(DEBUG_PRINT)
        dbgprintf("================================= loop %u, %u.%03u s\r\n", loop, ms / 1000, ms % 1000);
#endif

        for (i = 0; i < NPACKS; i++) {
            dbgprintf("Populating %s Data\r\n", packs[i].name);

            if (populate_pack_data(&packs[i].drvr, &packs[i].data) ) {
                populate_od_pack_data(&packs[i]);
            } else {
                // TODO: do we need to keep this around? Adding the loop results in the wrong error code on pack 2.
                // CO_errorReport(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_COMMUNICATION, BATTERY_OD_ERROR_INFO_CODE_PACK_1_COMM_ERROR);
            }
            if ((packs[i].data.v_cell_1_mV < SHUTDOWN_MV) || (packs[i].data.v_cell_2_mV < SHUTDOWN_MV)) {
                wait_for_charge(); // TODO: discuss with team -- this prevents heating when the batteries are too low
            }
        }

        run_battery_heating_state_machine();

        for (i = 0; i < NPACKS; i++) {
            update_battery_charging_state(&packs[i]);
        }

        if ((loop % 240) == 1) {
            manage_calibration();
        }
    }

    dbgprintf("Terminating battery thread...\r\n");

    for (i = 0; i < NPACKS; i++) {
        max17205Stop(&packs[i].drvr);
    }

    palClearLine(LINE_LED);
    chThdExit(MSG_OK);
}
