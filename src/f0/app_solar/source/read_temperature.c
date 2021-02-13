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
#define SIZE_OF_TMP101AN_READING_REGISTER_IN_BYTES (2)



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

// used to index arrays of temperature readings stored to compute running average:
static uint16_t readings_sensor_01_index = 0;
static uint16_t readings_sensor_02_index = 0;

// used to figure correct average whether readings array full or not full:
static uint16_t readings_sensor_01_count = 0;
static uint16_t readings_sensor_02_count = 0;

static uint16_t reading_sensor_01_min = 0;
static uint16_t reading_sensor_01_max = 0;

static uint16_t reading_sensor_02_min = 0;
static uint16_t reading_sensor_02_max = 0;



//----------------------------------------------------------------------
// - SECTION - private functions
//----------------------------------------------------------------------

bool store_reading(uint8_t sensor_addr, uint16_t latest_reading)
{
    bool routine_status = true;

    switch (sensor_addr)
    {
        case I2C_ADDR_SENSOR_01:
            readings_sensor_01[readings_sensor_01_index] = latest_reading;
            ++readings_sensor_01_index;
            if ( readings_sensor_01_index >= TEMPERATURE_READING_SAMPLE_SIZE_TO_AVERAGE )
                { readings_sensor_01_index = 0; }
            if ( readings_sensor_01_count < (TEMPERATURE_READING_SAMPLE_SIZE_TO_AVERAGE - 1))
                { ++readings_sensor_01_count; }
            break;

        case I2C_ADDR_SENSOR_02:
            readings_sensor_02[readings_sensor_02_index] = latest_reading;
            ++readings_sensor_02_index;
            if ( readings_sensor_02_index >= TEMPERATURE_READING_SAMPLE_SIZE_TO_AVERAGE )
                { readings_sensor_02_index = 0; }
            if ( readings_sensor_02_count < (TEMPERATURE_READING_SAMPLE_SIZE_TO_AVERAGE - 1))
                { ++readings_sensor_02_count; }
            break;

        default:
            routine_status = false;  // got invalid temperature sensor I2C address
    }

    return routine_status;
}



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

    uint8_t byte_array[SIZE_OF_TMP101AN_READING_REGISTER_IN_BYTES];

    uint16_t latest_reading = 0;

    memset(byte_array, 0, SIZE_OF_TMP101AN_READING_REGISTER_IN_BYTES);

//    chprintf((BaseSequentialStream *) &SD2, "stub code in new thread:\r\n");

    chprintf((BaseSequentialStream *) &SD2, "initializing TMP101AN driver instances...\r\n");
    tmp101ObjectInit(&device_driver_for_temp_sensor_01);
    tmp101Start(&device_driver_for_temp_sensor_01, &config_for_temp_sensor_01);
    tmp101ObjectInit(&device_driver_for_temp_sensor_02);
    tmp101Start(&device_driver_for_temp_sensor_02, &config_for_temp_sensor_02);

    chprintf((BaseSequentialStream *) &SD2, "zeroing readings arrays...\r\n");
    memset(readings_sensor_02, 0, (TEMPERATURE_READING_SAMPLE_SIZE_TO_AVERAGE * sizeof(uint16_t)));
    memset(readings_sensor_01, 0, (TEMPERATURE_READING_SAMPLE_SIZE_TO_AVERAGE * sizeof(uint16_t)));

    chprintf((BaseSequentialStream *) &SD2, "Starting loop,\r\n");


    while (!chThdShouldTerminateX())
    {
        chprintf((BaseSequentialStream *) &SD2, "calling for temp' reading...\r\n");

//        read_tmp101an_temperature_v1(&device_driver_for_temp_sensor_01, 1);
        read_tmp101an_temperature_v2(&device_driver_for_temp_sensor_01, byte_array);

        chprintf((BaseSequentialStream *) &SD2, "back from sensor reading call,\r\n");
        chThdSleepMilliseconds(SOLAR_BOARD_TEMPERATURE_READINGS_FREQ_IN_MS);

// 2021-02-12 - Ted observes that first byte typically returned in range
//  17..31, and second byte either 0 or 128.  This indicates that TMP101AN
//  default A/D resolution is nine (9) bits.  Can be configured for up to
//  12 bit resolution.  Shifts on following line convert two bytes into a
//  properly scaled 16 bit value:
        latest_reading = ((byte_array[0] << 4) | (byte_array[1] >> 4));

        store_reading(device_driver_for_temp_sensor_01.config->saddr, latest_reading);
    }

    palClearLine(LINE_LED);
    chThdExit(MSG_OK);
}



// --- EOF ---
