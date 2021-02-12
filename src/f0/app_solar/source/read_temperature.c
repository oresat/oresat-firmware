/**
*  @project Oresat-1 solar board firmware
*
*  @file read_temperature.c
*
*  @authors and contributors
**/

#include "ch.h"
#include "hal.h"
#include "chprintf.h"          // for serial debugging
#include "tmp101an.h"          // driver for Texas Instruments' TMP101AN temperature sensor
#include "read_temperature.h"

#include <string.h>



//----------------------------------------------------------------------
// - SECTION - pound defines
//----------------------------------------------------------------------

#define SOLAR_BOARD_TEMPERATURE_READINGS_FREQ_IN_MS (4000)
#define TEMPERATURE_READING_SAMPLE_SIZE_TO_AVERAGE (10)



//----------------------------------------------------------------------
// - SECTION - file scoped vars and structures
//----------------------------------------------------------------------

// Peripheral structures first, configuration and driver:

static const I2CConfig i2cconfig = {
    STM32_TIMINGR_PRESC(0xBU) |
    STM32_TIMINGR_SCLDEL(0x4U) | STM32_TIMINGR_SDADEL(0x2U) |
    STM32_TIMINGR_SCLH(0xFU)  | STM32_TIMINGR_SCLL(0x13U),
    0,
    0
};


static const TMP101Config config_for_temp_sensor_01 =
{
    &I2CD2,
    &i2cconfig,
    I2C_ADDR_SENSOR_01
};

static TMP101Driver device_driver_for_temp_sensor_01;

static const TMP101Config config_for_temp_sensor_02 =
{
    &I2CD2,
    &i2cconfig,
    I2C_ADDR_SENSOR_02
};

static TMP101Driver device_driver_for_temp_sensor_02;


static uint16_t readings_sensor_01[TEMPERATURE_READING_SAMPLE_SIZE_TO_AVERAGE] = {0};
static uint16_t readings_sensor_02[TEMPERATURE_READING_SAMPLE_SIZE_TO_AVERAGE] = {0};



//----------------------------------------------------------------------
// - SECTION - public functions
//----------------------------------------------------------------------

bool initialize_temperature_sensor_device_objects(void)
{
    tmp101ObjectInit(&device_driver_for_temp_sensor_01);
    tmp101Start(&device_driver_for_temp_sensor_01, &config_for_temp_sensor_01);

    tmp101ObjectInit(&device_driver_for_temp_sensor_02);
    tmp101Start(&device_driver_for_temp_sensor_02, &config_for_temp_sensor_02);

    return true;
}



THD_WORKING_AREA(read_temperature_wa, WORKING_AREA_SIZE_FOR_READ_TEMPERATURE_THREAD);
THD_FUNCTION(read_temperature, arg)
{
    (void)arg;

    chprintf((BaseSequentialStream *) &SD2, "stub code in new thread:\r\n");
//    bool init_status_flag = initialize_temperature_sensor_device_objects();
//    if (!init_status_flag)
//        { /* problem initializing device drivers! */ }

    chprintf((BaseSequentialStream *) &SD2, "initializing drivers . . .\r\n");
    tmp101ObjectInit(&device_driver_for_temp_sensor_01);
    tmp101Start(&device_driver_for_temp_sensor_01, &config_for_temp_sensor_01);
    tmp101ObjectInit(&device_driver_for_temp_sensor_02);
    tmp101Start(&device_driver_for_temp_sensor_02, &config_for_temp_sensor_02);

    memset(readings_sensor_02, 0, (TEMPERATURE_READING_SAMPLE_SIZE_TO_AVERAGE * sizeof(uint16_t)));
    memset(readings_sensor_01, 0, (TEMPERATURE_READING_SAMPLE_SIZE_TO_AVERAGE * sizeof(uint16_t)));

    chprintf((BaseSequentialStream *) &SD2, "done.  Starting loop,\r\n");


    while (!chThdShouldTerminateX())
    {
        chprintf((BaseSequentialStream *) &SD2, "in read temperature while loop,\r\n");

        read_tmp101an_temperature_v1(&device_driver_for_temp_sensor_01, 1);

        chprintf((BaseSequentialStream *) &SD2, "back from sensor reading call,\r\n");
        chThdSleepMilliseconds(SOLAR_BOARD_TEMPERATURE_READINGS_FREQ_IN_MS);
    }

    palClearLine(LINE_LED);
    chThdExit(MSG_OK);
}
