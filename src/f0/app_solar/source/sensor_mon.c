/**
*  @project Oresat-1 solar board firmware
*
*  @file sensor_mon.c
*
*  @authors and contributors
**/

#include "ch.h"
#include "hal.h"
#include "solar.h"
#include "tmp101.h"             // driver for Texas Instruments' TMP101 temperature sensor
#include "chprintf.h"           // for serial debugging

#include <string.h>

#define SOLAR_BOARD_TEMPERATURE_READINGS_FREQ_IN_MS (4000)
#define DELAY_BETWEEN_TEMP_READINGS_IN_MS (50)


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

    chprintf((BaseSequentialStream *) &SD2, "initializing TMP101 driver instances...\r\n");
    tmp101ObjectInit(&device_driver_for_temp_sensor_01);
    tmp101Start(&device_driver_for_temp_sensor_01, &config_for_temp_sensor_01);

    tmp101ObjectInit(&device_driver_for_temp_sensor_02);
    tmp101Start(&device_driver_for_temp_sensor_02, &config_for_temp_sensor_02);

    chprintf((BaseSequentialStream *) &SD2, "Starting TMP101 loop,\r\n");

    while (!chThdShouldTerminateX())
    {
    	chprintf((BaseSequentialStream *) &SD2, "=========================================\r\n");
    	int16_t temp_c;
    	int32_t temp_mC;
        if( read_tmp101an_temperature(&device_driver_for_temp_sensor_01, &temp_c, &temp_mC) != MSG_OK ) {
        	chprintf((BaseSequentialStream *) &SD2, "Failed to read I2C temperature\r\n");
        }

        chprintf((BaseSequentialStream *) &SD2, "temp_c 1 = %d C  (%d mC)\r\n", temp_c, temp_mC);

        chThdSleepMilliseconds(DELAY_BETWEEN_TEMP_READINGS_IN_MS);

        if( read_tmp101an_temperature(&device_driver_for_temp_sensor_02, &temp_c, &temp_mC) != MSG_OK ) {
        	chprintf((BaseSequentialStream *) &SD2, "Failed to read I2C temperature\r\n");
        }

        chprintf((BaseSequentialStream *) &SD2, "temp_c 2 = %d C  (%d mC)\r\n", temp_c, temp_mC);
        chThdSleepMilliseconds(SOLAR_BOARD_TEMPERATURE_READINGS_FREQ_IN_MS - DELAY_BETWEEN_TEMP_READINGS_IN_MS);
    }

    palClearLine(LINE_LED);
    chThdExit(MSG_OK);
}


