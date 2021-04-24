/**
*  @project Oresat-1 solar board firmware
*
*  @file sensor_mon.c
*
*  @authors and contributors
**/

#include "ch.h"
#include "hal.h"
#include "tmp101.h"             // driver for Texas Instruments' TMP101 temperature sensor
#include "CANopen.h"
#include <string.h>
#include "solar.h"


#if 0
#define DEBUG_SD                (BaseSequentialStream *) &SD2
#include "chprintf.h"
#define dbgprintf(str, ...)       chprintf((BaseSequentialStream*) &SD2, str, ##__VA_ARGS__)
#else
#define dbgprintf(str, ...)
#endif


//FIXME I believe MAX() is defined in some common C library???
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(a,b) (((a)<(b))?(a):(b))

#define DEBUG_SD                  (BaseSequentialStream *) &SD2

#define TMP101_SADDR_SENSOR_01  (0x48)
#define TMP101_SADDR_SENSOR_02  (0x4A)

extern const I2CConfig i2cconfig;

static const TMP101Config config_for_temp_sensor_01 = {
    &I2CD2,
    &i2cconfig,
    TMP101_SADDR_SENSOR_01
};

static const TMP101Config config_for_temp_sensor_02 = {
    &I2CD2,
    &i2cconfig,
    TMP101_SADDR_SENSOR_02
};

static TMP101Driver device_driver_for_temp_sensor_01;
static TMP101Driver device_driver_for_temp_sensor_02;


/*===========================================================================*/
/* public functions                                                          */
/*===========================================================================*/

THD_WORKING_AREA(sensor_mon_wa, 0x200);
THD_FUNCTION(sensor_mon, arg)
{
    (void)arg;
    chThdSleepMilliseconds(10);

    dbgprintf("Initializing TMP101 driver instances...\r\n");
    tmp101ObjectInit(&device_driver_for_temp_sensor_01);
    tmp101Start(&device_driver_for_temp_sensor_01, &config_for_temp_sensor_01);

    tmp101ObjectInit(&device_driver_for_temp_sensor_02);
    tmp101Start(&device_driver_for_temp_sensor_02, &config_for_temp_sensor_02);

    dbgprintf("Starting TMP101 loop,\r\n");

    int16_t temp_c = 0;
    int32_t temp_mC = 0;
    if( tmp101ReadTemperature(&device_driver_for_temp_sensor_01, &temp_c, &temp_mC) == MSG_OK ) {
    	OD_PV_Temp.cell1Temp = temp_c;
    	OD_PV_Temp.cell1TempMax = temp_c;
    	OD_PV_Temp.cell1TempMin = temp_c;
    }

    if( tmp101ReadTemperature(&device_driver_for_temp_sensor_02, &temp_c, &temp_mC) == MSG_OK ) {
    	OD_PV_Temp.cell2Temp = temp_c;
    	OD_PV_Temp.cell2TempMax = temp_c;
    	OD_PV_Temp.cell2TempMin = temp_c;
    }


    while (!chThdShouldTerminateX())
    {
        if( tmp101ReadTemperature(&device_driver_for_temp_sensor_01, &temp_c, &temp_mC) == MSG_OK ) {
        	OD_PV_Temp.cell1Temp = temp_c;
        	OD_PV_Temp.cell1TempMax = MAX(temp_c, CO_OD_RAM.PV_Temp.cell1TempMax);
        	OD_PV_Temp.cell1TempMin = MIN(temp_c, CO_OD_RAM.PV_Temp.cell1TempMin);

        	dbgprintf("temp_c 1 = %d C  (%d mC)\r\n", temp_c, temp_mC);
        } else {
        	dbgprintf("Failed to read I2C temperature\r\n");
        	CO_errorReport(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_COMMUNICATION, SOLAR_OD_ERROR_TYPE_TMP101_1_COMM_ERROR);
        }

        if( tmp101ReadTemperature(&device_driver_for_temp_sensor_02, &temp_c, &temp_mC) == MSG_OK ) {
        	OD_PV_Temp.cell2Temp = temp_c;
			OD_PV_Temp.cell2TempMax = MAX(temp_c, CO_OD_RAM.PV_Temp.cell2TempMax);
			OD_PV_Temp.cell2TempMin = MIN(temp_c, CO_OD_RAM.PV_Temp.cell2TempMin);

			dbgprintf("temp_c 2 = %d C  (%d mC)\r\n", temp_c, temp_mC);
        } else {
			dbgprintf("Failed to read I2C temperature\r\n");
			CO_errorReport(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_COMMUNICATION, SOLAR_OD_ERROR_TYPE_TMP101_2_COMM_ERROR);
        }

        chThdSleepMilliseconds(4000);
    }

    palClearLine(LINE_LED);
    chThdExit(MSG_OK);
}


