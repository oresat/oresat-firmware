#include "ch.h"
#include "batt.h"
#include "max17205.h"
#include "CANopen.h"
#include "chprintf.h"

#define DEBUG_SERIAL    (BaseSequentialStream*) &SD2

#define NCELLS          2U          /* Number of cells */

typedef enum {
	BATTERY_STATE_MACHINE_STATE_NOT_HEATING = 0,
	BATTERY_STATE_MACHINE_STATE_HEATING,
} battery_heating_state_machine_state_t;


static const I2CConfig i2cconfig_1 = {
    STM32_TIMINGR_PRESC(0xBU) |
    STM32_TIMINGR_SCLDEL(0x4U) | STM32_TIMINGR_SDADEL(0x2U) |
    STM32_TIMINGR_SCLH(0xFU)  | STM32_TIMINGR_SCLL(0x13U),
    0,
    0
};

//TODO timing for i2c2 is different the i2c1. Scope the lines and match them up.
static const I2CConfig i2cconfig_2 = {
    STM32_TIMINGR_PRESC(0xFU) |
    STM32_TIMINGR_SCLDEL(0x4U) | STM32_TIMINGR_SDADEL(0x2U) |
    STM32_TIMINGR_SCLH(0xFU)  | STM32_TIMINGR_SCLL(0x13U),
    0,
    0
};

static const max17205_regval_t batt_cfg[] = {
    {MAX17205_AD_PACKCFG, MAX17205_SETVAL(MAX17205_AD_PACKCFG,
                                          _VAL2FLD(MAX17205_PACKCFG_NCELLS, NCELLS) |
                                          MAX17205_PACKCFG_BALCFG_40 |
										  MAX17205_PACKCFG_CHEN |
										  MAX17205_PACKCFG_TDEN |
										  MAX17205_PACKCFG_A1EN |
										  MAX17205_PACKCFG_A2EN )},
    {MAX17205_AD_NRSENSE, MAX17205_RSENSE2REG(10000U)},
    {0,0}
};

static const MAX17205Config max17205configPack1 = {
	&I2CD1,
	&i2cconfig_1,
    batt_cfg
};

static const MAX17205Config max17205configPack2 = {
	&I2CD2,
	&i2cconfig_2,
    batt_cfg
};

static MAX17205Driver max17205devPack1;
static MAX17205Driver max17205devPack2;

typedef struct {
	bool is_data_valid;

	uint16_t cell1_mV;
	uint16_t cell2_mV;
	uint16_t VCell_mV;
	uint16_t VCell_max_volt_mV;
	uint16_t VCell_min_volt_mV;
	uint16_t batt_mV;//x

	int16_t avg_current_mA;
	int16_t max_current_mA;
	int16_t min_current_mA;

	uint16_t available_state_of_charge; //Percent
	uint16_t present_state_of_charge; //Percent

	uint16_t time_to_full; // seconds
	uint16_t time_to_empty; // seconds

	uint16_t full_capacity_mAh;
	uint16_t available_capacity_mAh;
	uint16_t mix_capacity;
	uint16_t reporting_capacity_mAh;

	uint16_t cycles; // count

	int16_t avg_temp_1_C;
	int16_t avg_temp_2_C;
	int16_t avg_int_temp_C;
} batt_pack_data_t;

static batt_pack_data_t pack_1_data;
static batt_pack_data_t pack_2_data;

battery_heating_state_machine_state_t current_batery_state_machine_state = BATTERY_STATE_MACHINE_STATE_NOT_HEATING;

/**
 * TODO document this
 */
void run_battery_heating_state_machine(batt_pack_data_t *pk1_data, batt_pack_data_t *pk2_data) {
	if( pk1_data->is_data_valid && pk2_data->is_data_valid ) {
		int16_t avg_temp_1_C = pk1_data->avg_temp_1_C;
		int16_t avg_temp_2_C = pk2_data->avg_temp_1_C;

		uint16_t present_state_of_charge_1 = pk1_data->present_state_of_charge;
		uint16_t present_state_of_charge_2 = pk2_data->present_state_of_charge;

		const uint16_t total_state_of_charge = (present_state_of_charge_1 + present_state_of_charge_2) / 2;


		switch (current_batery_state_machine_state) {
			case BATTERY_STATE_MACHINE_STATE_HEATING:
				chprintf(DEBUG_SERIAL, "Turning heaters ON\r\n");
				palSetLine(LINE_MOARPWR);
				palSetLine(LINE_HEATER_ON_1);
				palSetLine(LINE_HEATER_ON_2);
				CO_OD_RAM.heaterStatus = 1;
				//Once they’re greater than 5 °C or the combined pack capacity is < 25%

				if( (avg_temp_1_C > 5 && avg_temp_2_C > 5) || (total_state_of_charge < 25) ) {
					current_batery_state_machine_state = BATTERY_STATE_MACHINE_STATE_NOT_HEATING;
				}
				break;
			case BATTERY_STATE_MACHINE_STATE_NOT_HEATING:
				chprintf(DEBUG_SERIAL, "Turning heaters OFF\r\n");
				palClearLine(LINE_HEATER_ON_1);
				palClearLine(LINE_HEATER_ON_2);
				palClearLine(LINE_MOARPWR);
				CO_OD_RAM.heaterStatus = 0;

				if( (avg_temp_1_C < -5 || avg_temp_2_C < -5) && (present_state_of_charge_1 > 25 || present_state_of_charge_2 > 25) ) {
					current_batery_state_machine_state = BATTERY_STATE_MACHINE_STATE_HEATING;
				}
				break;
			default:
				current_batery_state_machine_state = BATTERY_STATE_MACHINE_STATE_NOT_HEATING;
				break;
		}
	} else {
		//Fail safe
		palClearLine(LINE_HEATER_ON_1);
		palClearLine(LINE_HEATER_ON_2);
		palClearLine(LINE_MOARPWR);
	}
}

/**
 * TODO document this
 */
void update_battery_charging_state(batt_pack_data_t *pk_data, const ioline_t line_dchg_dis, const ioline_t line_chg_dis, const char* pk_str) {

	chprintf(DEBUG_SERIAL, "LINE_DCHG_STAT_PK1 = %u\r\n", palReadLine(LINE_DCHG_STAT_PK1));
	chprintf(DEBUG_SERIAL, "LINE_CHG_STAT_PK1 = %u\r\n", palReadLine(LINE_CHG_STAT_PK1));
	chprintf(DEBUG_SERIAL, "LINE_DCHG_STAT_PK2 = %u\r\n", palReadLine(LINE_DCHG_STAT_PK2));
	chprintf(DEBUG_SERIAL, "LINE_CHG_STAT_PK2 = %u\r\n", palReadLine(LINE_CHG_STAT_PK2));

	if( pk_data->is_data_valid ) {
		if( pk_data->VCell_mV < 3000 || pk_data->present_state_of_charge < 20 ) {
			//Disable discharge on both packs
			chprintf(DEBUG_SERIAL, "Disabling discharge on %s\r\n", pk_str);
			palSetLine(line_dchg_dis);
		} else {
			chprintf(DEBUG_SERIAL, "Enabling discharge on %s\r\n", pk_str);
			//Allow discharge on both packs
			palClearLine(line_dchg_dis);
		}


		if( pk_data->VCell_mV > 4100 ) {
			chprintf(DEBUG_SERIAL, "Disabling charging on %s\r\n", pk_str);
			palSetLine(line_chg_dis);
		} else {
			chprintf(DEBUG_SERIAL, "Enabling charging on %s\r\n", pk_str);
			palClearLine(line_chg_dis);
			if( pk_data->present_state_of_charge > 90 ) {
				const int16_t vcell_delta_mV = pk_data->cell1_mV - pk_data->cell2_mV;

				if( vcell_delta_mV < -50 || vcell_delta_mV > 50 ) {
					//TODO command cell  balancing - this appears to be done in hardware based on config registers???
				}
			}
		}
	} else {
		//fail safe mode
		palSetLine(line_dchg_dis);
		palSetLine(line_chg_dis);
	}
}

/**
 * TODO document this
 */
bool populate_pack_data(MAX17205Driver *driver, batt_pack_data_t *dest) {
	msg_t r = 0;
	memset(dest, 0, sizeof(*dest));
	dest->is_data_valid = true;


    if( (r = max17205ReadAverageTemperature(driver, MAX17205_AD_AVGTEMP1, &dest->avg_temp_1_C)) != MSG_OK ) {
    	dest->is_data_valid = false;
    }
    if( (r = max17205ReadAverageTemperature(driver, MAX17205_AD_AVGTEMP2, &dest->avg_temp_2_C)) != MSG_OK ) {
    	dest->is_data_valid = false;
    }
    if( (r = max17205ReadAverageTemperature(driver, MAX17205_AD_AVGINTTEMP, &dest->avg_int_temp_C)) != MSG_OK ) {
    	dest->is_data_valid = false;
    }

    chprintf(DEBUG_SERIAL, "avg_temp_1_C = %d C, ", dest->avg_temp_1_C);
    chprintf(DEBUG_SERIAL, "avg_temp_2_C = %d C, ", dest->avg_temp_2_C);
    chprintf(DEBUG_SERIAL, "avg_int_temp_C = %d C", dest->avg_int_temp_C);
    chprintf(DEBUG_SERIAL, "\r\n");

    /* Record pack and cell voltages to object dictionary */
    if( (r = max17205ReadVoltage(driver, MAX17205_AD_AVGCELL1, &dest->cell1_mV)) != MSG_OK ) {
    	dest->is_data_valid = false;
    }

    if( (r = max17205ReadVoltage(driver, MAX17205_AD_AVGVCELL, &dest->VCell_mV)) != MSG_OK ) {
    	dest->is_data_valid = false;
    }
    if( (r = max17205ReadBattVoltage(driver, MAX17205_AD_BATT, &dest->batt_mV)) != MSG_OK ) {
    	dest->is_data_valid = false;
    }

    if( dest->is_data_valid ) {
    	dest->cell2_mV = dest->batt_mV - dest->cell1_mV;
    }

    chprintf(DEBUG_SERIAL, "cell1_mV = %u, cell2_mV = %u, VCell_mV = %u, batt_mV = %u\r\n", dest->cell1_mV, dest->cell2_mV, dest->VCell_mV, dest->batt_mV);

    uint16_t max_min_volt_raw = 0;
    if( (r = max17205ReadRaw(driver, MAX17205_AD_MAXMINVOLT, &max_min_volt_raw)) != MSG_OK ) {
		dest->is_data_valid = false;
	} else {
		dest->VCell_max_volt_mV = (max_min_volt_raw >> 8) * 20;
		dest->VCell_min_volt_mV = (max_min_volt_raw & 0xFF) * 20;
		chprintf(DEBUG_SERIAL, "VCell_max_volt_mV = %u, VCell_min_volt_mV = %u\r\n", dest->VCell_max_volt_mV, dest->VCell_min_volt_mV);
	}


    if( (r = max17205ReadCurrent(driver, MAX17205_AD_AVGCURRENT, &dest->avg_current_mA)) != MSG_OK ) {
		dest->is_data_valid = false;
	}

    uint16_t max_min_current_raw = 0;
    if( (r = max17205ReadRaw(driver, MAX17205_AD_MAXMINCURR, &max_min_current_raw)) != MSG_OK ) {
		dest->is_data_valid = false;
	} else {
		//Assumes Rsense = 0.01 ohms
		int8_t max_raw = (max_min_current_raw >> 8);
		int8_t min_raw = max_min_current_raw & 0xFF;
		dest->max_current_mA = ((int16_t) max_raw) * 40;// 0.0004/0.01 = 0.04
		dest->min_current_mA = ((int16_t) min_raw) * 40;// 0.0004/0.01 = 0.04

		chprintf(DEBUG_SERIAL, "max_mA = %d, min_mA = %d\r\n", dest->max_current_mA, dest->min_current_mA);
	}

    chprintf(DEBUG_SERIAL, "avg_current_mA = %d mA\r\n", dest->avg_current_mA);


    /* capacity */
	if( (r = max17205ReadCapacity(driver, MAX17205_AD_FULLCAP, &dest->full_capacity_mAh)) != MSG_OK ) {
		dest->is_data_valid = false;
    }
	if( (r = max17205ReadCapacity(driver, MAX17205_AD_AVCAP, &dest->available_capacity_mAh)) != MSG_OK ) {
		dest->is_data_valid = false;
	}
	if( (r = max17205ReadCapacity(driver, MAX17205_AD_MIXCAP, &dest->mix_capacity)) != MSG_OK ) {
		dest->is_data_valid = false;
	}
	if( (r = max17205ReadCapacity(driver, MAX17205_AD_REPCAP, &dest->reporting_capacity_mAh)) != MSG_OK ) {
		dest->is_data_valid = false;
	}



    chprintf(DEBUG_SERIAL, "full_capacity_mAh = %u, available_capacity_mAh = %u, mix_capacity = %u\r\n", dest->full_capacity_mAh, dest->available_capacity_mAh, dest->mix_capacity);



    /* state of charge */
    if( (r = max17205ReadTime(driver, MAX17205_AD_TTE, &dest->time_to_empty)) != MSG_OK ) {
    	dest->is_data_valid = false;
	}
    if( (r = max17205ReadTime(driver, MAX17205_AD_TTF, &dest->time_to_full)) != MSG_OK ) {
    	dest->is_data_valid = false;
	}

    if( (r = max17205ReadPercentage(driver, MAX17205_AD_AVSOC, &dest->available_state_of_charge)) != MSG_OK ) {
    	dest->is_data_valid = false;
	}
    if( (r = max17205ReadPercentage(driver, MAX17205_AD_VFSOC, &dest->present_state_of_charge)) != MSG_OK ) {
    	dest->is_data_valid = false;
	}


    chprintf(DEBUG_SERIAL, "time_to_empty = %u (seconds), time_to_full = %u (seconds), available_state_of_charge = %u%%, present_state_of_charge = %u%%\r\n", dest->time_to_empty, dest->time_to_full, dest->available_state_of_charge, dest->present_state_of_charge);

    /* other info */
    if( (r = max17205ReadRaw(driver, MAX17205_AD_CYCLES, &dest->cycles)) != MSG_OK ) {
    	dest->is_data_valid = false;
	}

    chprintf(DEBUG_SERIAL, "cycles = %u\r\n", dest->cycles);


    return(dest->is_data_valid);
}

/* Battery monitoring thread */
THD_WORKING_AREA(batt_wa, 0x400);
THD_FUNCTION(batt, arg)
{
    (void)arg;

    max17205ObjectInit(&max17205devPack1);
    max17205ObjectInit(&max17205devPack2);
    const bool pack_1_init_flag = max17205Start(&max17205devPack1, &max17205configPack1);
    chprintf(DEBUG_SERIAL, "max17205Start(pack1) = %u\r\n", pack_1_init_flag);

    /*
    max17205PrintintNonvolatileMemory(&max17205configPack1);
    while(1) {
    	chThdSleepMilliseconds(1000);
    }
    */

    const bool pack_2_init_flag = max17205Start(&max17205devPack2, &max17205configPack2);
    chprintf(DEBUG_SERIAL, "max17205Start(pack2) = %u\r\n", pack_2_init_flag);


    uint16_t pack_1_comm_rx_error_count = 0;
    uint16_t pack_2_comm_rx_error_count = 0;
    while (!chThdShouldTerminateX()) {
    	chprintf(DEBUG_SERIAL, "================================= %u ms\r\n", TIME_I2MS(chVTGetSystemTime()));
    	for(uint32_t sl = 0; sl < 3500; sl += 50) {
    		chprintf(DEBUG_SERIAL, "    %u ms\r\n", TIME_I2MS(chVTGetSystemTime()));
    		chThdSleepMilliseconds(50);
    	}
    	//chThdSleepMilliseconds(1000);

    	chprintf(DEBUG_SERIAL, "Populating Pack 1 Data\r\n");
    	if( ! populate_pack_data(&max17205devPack1, &pack_1_data) ) {
    		pack_1_comm_rx_error_count++;
    	}

    	chprintf(DEBUG_SERIAL, "\r\nPopulating Pack 2 Data\r\n");
    	chThdSleepMilliseconds(100);
    	if( ! populate_pack_data(&max17205devPack2, &pack_2_data) ) {
    		pack_2_comm_rx_error_count++;
    	}


    	CO_OD_RAM.battery1.maxSubIndex = 1;
		CO_OD_RAM.battery1.vbatt = pack_1_data.batt_mV;
		CO_OD_RAM.battery1.VCellMax = pack_1_data.VCell_max_volt_mV;
		CO_OD_RAM.battery1.VCellMin = pack_1_data.VCell_min_volt_mV;
		CO_OD_RAM.battery1.VCell = pack_1_data.cell1_mV;
		CO_OD_RAM.battery1.VCell2 = pack_1_data.cell2_mV;
		CO_OD_RAM.battery1.currentAvg = pack_1_data.avg_current_mA;
		CO_OD_RAM.battery1.currentMax = pack_1_data.max_current_mA;
		CO_OD_RAM.battery1.currentMin = pack_1_data.min_current_mA;
		CO_OD_RAM.battery1.fullCapacity = pack_1_data.full_capacity_mAh;
		CO_OD_RAM.battery1.timeToEmpty = pack_1_data.time_to_empty;
		CO_OD_RAM.battery1.timeToFull = pack_1_data.time_to_full;
		CO_OD_RAM.battery1.cycles = pack_1_data.cycles;
		CO_OD_RAM.battery1.availableCapacity = pack_1_data.available_capacity_mAh;
		CO_OD_RAM.battery1.availableStateOfCharge = pack_1_data.available_state_of_charge;
		CO_OD_RAM.battery1.presentStateOfCharge = pack_1_data.present_state_of_charge;
		CO_OD_RAM.battery1.mixCapacity = pack_1_data.mix_capacity;
		CO_OD_RAM.battery1.reportingCapacity = pack_1_data.reporting_capacity_mAh;
		CO_OD_RAM.battery1.tempAvg1 = pack_1_data.avg_temp_1_C;
		CO_OD_RAM.battery1.tempAvg2 = pack_1_data.avg_temp_2_C;
		CO_OD_RAM.battery1.tempAvgInt = pack_1_data.avg_int_temp_C;
		CO_OD_RAM.battery1.dischargeDisable = palReadLine(LINE_DCHG_DIS_PK1);
		CO_OD_RAM.battery1.chargeDisable = palReadLine(LINE_CHG_DIS_PK1);
		CO_OD_RAM.battery1.dischargeStatus = palReadLine(LINE_DCHG_STAT_PK1);
		CO_OD_RAM.battery1.chargeStatus = palReadLine(LINE_CHG_STAT_PK1);


		CO_OD_RAM.battery2.maxSubIndex = 2;
		CO_OD_RAM.battery2.vbatt = pack_2_data.batt_mV;
		CO_OD_RAM.battery2.VCellMax = pack_2_data.VCell_max_volt_mV;
		CO_OD_RAM.battery2.VCellMin = pack_2_data.VCell_min_volt_mV;
		CO_OD_RAM.battery2.VCell = pack_2_data.cell1_mV;
		CO_OD_RAM.battery2.VCell2 = pack_2_data.cell2_mV;
		CO_OD_RAM.battery2.currentAvg = pack_2_data.avg_current_mA;
		CO_OD_RAM.battery2.currentMax = pack_2_data.max_current_mA;
		CO_OD_RAM.battery2.currentMin = pack_2_data.min_current_mA;
		CO_OD_RAM.battery2.fullCapacity = pack_2_data.full_capacity_mAh;
		CO_OD_RAM.battery2.timeToEmpty = pack_2_data.time_to_empty;
		CO_OD_RAM.battery2.timeToFull = pack_2_data.time_to_full;
		CO_OD_RAM.battery2.cycles = pack_2_data.cycles;
		CO_OD_RAM.battery2.availableCapacity = pack_2_data.available_capacity_mAh;
		CO_OD_RAM.battery2.availableStateOfCharge = pack_2_data.available_state_of_charge;
		CO_OD_RAM.battery2.presentStateOfCharge = pack_2_data.present_state_of_charge;
		CO_OD_RAM.battery2.mixCapacity = pack_2_data.mix_capacity;
		CO_OD_RAM.battery2.reportingCapacity = pack_2_data.reporting_capacity_mAh;
		CO_OD_RAM.battery2.tempAvg1 = pack_2_data.avg_temp_1_C;
		CO_OD_RAM.battery2.tempAvg2 = pack_2_data.avg_temp_2_C;
		CO_OD_RAM.battery2.tempAvgInt = pack_2_data.avg_int_temp_C;
		CO_OD_RAM.battery2.dischargeDisable = palReadLine(LINE_DCHG_DIS_PK2);
		CO_OD_RAM.battery2.chargeDisable = palReadLine(LINE_CHG_DIS_PK2);
		CO_OD_RAM.battery2.dischargeStatus = palReadLine(LINE_DCHG_STAT_PK2);
		CO_OD_RAM.battery2.chargeStatus = palReadLine(LINE_CHG_STAT_PK2);


        run_battery_heating_state_machine(&pack_1_data, &pack_2_data);
        update_battery_charging_state(&pack_1_data, LINE_DCHG_DIS_PK1, LINE_CHG_DIS_PK1, "PK1");
        update_battery_charging_state(&pack_2_data, LINE_DCHG_DIS_PK2, LINE_CHG_DIS_PK2, "PK2");

        palToggleLine(LINE_LED);
    }

    chprintf(DEBUG_SERIAL, "Terminating battery thread...\r\n");

    max17205Stop(&max17205devPack1);
    max17205Stop(&max17205devPack2);

    palClearLine(LINE_LED);
    chThdExit(MSG_OK);
}
