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
#define DELAY_BETWEEN_TEMP_READINGS_IN_MS (50)

#define SIZE_OF_TMP101AN_READING_REGISTER_IN_BYTES (2)

#define TEMPERATURE_READING_SAMPLE_SIZE_TO_AVERAGE (10)
#define MULTIPLIER_TO_RETAIN_TENTHS (10)



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

static uint32_t reading_sensor_01_average = 0;
static uint32_t reading_sensor_02_average = 0;



//----------------------------------------------------------------------
// - SECTION - private functions
//----------------------------------------------------------------------

bool store_reading(uint8_t sensor_addr, uint16_t latest_reading)
{
    bool routine_status = true;

    switch (sensor_addr)
    {
        case I2C_ADDR_SENSOR_01:
chprintf((BaseSequentialStream *) &SD2, "from sensor 0x%02X storing rdg %u = %u\r\n", sensor_addr, readings_sensor_01_index, latest_reading);
            readings_sensor_01[readings_sensor_01_index] = latest_reading;
            ++readings_sensor_01_index;
            if ( readings_sensor_01_index >= TEMPERATURE_READING_SAMPLE_SIZE_TO_AVERAGE )
                { readings_sensor_01_index = 0; }
            if ( readings_sensor_01_count < (TEMPERATURE_READING_SAMPLE_SIZE_TO_AVERAGE - 1))
                { ++readings_sensor_01_count; }
            break;

        case I2C_ADDR_SENSOR_02:
chprintf((BaseSequentialStream *) &SD2, "from sensor 0x%02X storing rdg %u = %u\r\n", sensor_addr, readings_sensor_02_index, latest_reading);
            readings_sensor_02[readings_sensor_02_index] = latest_reading;
            ++readings_sensor_02_index;
            if ( readings_sensor_02_index >= TEMPERATURE_READING_SAMPLE_SIZE_TO_AVERAGE )
                { readings_sensor_02_index = 0; }
            if ( readings_sensor_02_count < (TEMPERATURE_READING_SAMPLE_SIZE_TO_AVERAGE - 1))
                { ++readings_sensor_02_count; }
            break;

        default:
chprintf((BaseSequentialStream *) &SD2, "WARNING - unrecognized sensor address 0x%02X\r\n", sensor_addr);
            routine_status = false;  // got invalid temperature sensor I2C address
    }

    return routine_status;

} // end routine store_reading()



bool update_min_max_temperature(uint8_t sensor_addr, uint16_t latest_reading)
{
    bool routine_status = true;

    switch (sensor_addr)
    {
        case I2C_ADDR_SENSOR_01:
            if ( latest_reading < reading_sensor_01_min )
            {
                reading_sensor_01_min = latest_reading;
            }
            if ( latest_reading > reading_sensor_01_min )
            {
                reading_sensor_01_max = latest_reading;
            }
            break;

        case I2C_ADDR_SENSOR_02:
            if ( latest_reading < reading_sensor_02_min )
            {
                reading_sensor_02_min = latest_reading;
            }
            if ( latest_reading > reading_sensor_02_min )
            {
                reading_sensor_02_max = latest_reading;
            }
            break;

        default:
            routine_status = false;  // got invalid temperature sensor I2C address
    }

    return routine_status;

} // end update_min_max_temperature()



bool update_average_temperature(uint8_t sensor_addr)
{
    bool routine_status = false;
    uint16_t i = 0;
    uint32_t sum_of_readings = 0;

    switch (sensor_addr)
    {
        case I2C_ADDR_SENSOR_01:
            if ( readings_sensor_01_count > 0 )
            {
                i = readings_sensor_01_count;
                while ( i > 0 )
                {
                    sum_of_readings += readings_sensor_01[(i - 1)];
                    i--;
                }
                reading_sensor_01_average = ((sum_of_readings * MULTIPLIER_TO_RETAIN_TENTHS) / readings_sensor_01_count);
                routine_status = true;
            }
            break;

        case I2C_ADDR_SENSOR_02:
            if ( readings_sensor_02_count > 0 )
            {
                i = readings_sensor_02_count;
                while ( i > 0 )
                {
                    sum_of_readings += readings_sensor_02[(i - 1)];
                    i--;
                }
                reading_sensor_02_average = ((sum_of_readings * MULTIPLIER_TO_RETAIN_TENTHS) / readings_sensor_02_count);
                routine_status = true;
            }
            break;

        default:
            routine_status = false;  // got invalid temperature sensor I2C address
    }

    return routine_status;

} // end routine update_average_temperature()



bool convert_reading_to_degrees_c(uint16_t reading)
{
// 2021-02-19 FRI - from TMP101AN datasheet:
//   0x7FF =    128 C
//   0x190 =     25 C
//   0x004 =   0.25 C
//   0x000 =      0 C
//   0xFFC =  -0.25 C
//   0xE70 =    -25 C
//   0x800 =   -128 C

// So given that 0x190 or 400 corresponds to 25 C, each differential of
// value one (1) represents 0.0625 degrees C.  Accuracy of sensor likely
// much less than this, but step wise difference is about 0.063 C.
//
// Also appears that MSB is sign bit.  When sign bit is set we must
// compute temperature as 0x1000 - reading and use signed integer.  Hmm,
// we may just be able to scale these values and use signed integers
// as is, once we confirm that C implements signed integers in 2's
// compliment mode.  Wikipedia article says ARM processors use 2's
// compliment as do many other contemporary cerca 2021 processor families.


}



bool report_temperature_stats(uint8_t sensor_addr)
{
    bool routine_status = true;

    switch (sensor_addr)
    {
        case I2C_ADDR_SENSOR_01:
            chprintf((BaseSequentialStream *) &SD2, "temp sensor 01 min, max, average:  %u, %u, %u\r\n",
              reading_sensor_01_min, reading_sensor_01_max, reading_sensor_01_average);
            break;

        case I2C_ADDR_SENSOR_02:
            chprintf((BaseSequentialStream *) &SD2, "temp sensor 02 min, max, average:  %u, %u, %u\r\n",
              reading_sensor_02_min, reading_sensor_02_max, reading_sensor_02_average);
            break;

        default:
            routine_status = false;
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
// 2021-02-12 - Ted observes that when reading TMP101AN register bytes of
//  the latest temperature reading, the first byte typically returns in range
//  17..31, and second byte either 0 or 128.  This indicates that TMP101AN
//  default A/D resolution is nine (9) bits.  Can be configured for up to
//  12 bit resolution.  Four bits in the two byte register always read zero.
//  Bit-wise shifting on line assigning temperature to variable 'latest_reading'
//  converts sensor bytes into correctly scaled 16-bit integer:
        read_tmp101an_temperature_v2(&device_driver_for_temp_sensor_01, byte_array);

        latest_reading = ((byte_array[0] << 4) | (byte_array[1] >> 4));

        store_reading(device_driver_for_temp_sensor_01.config->saddr, latest_reading);
        update_min_max_temperature(device_driver_for_temp_sensor_01.config->saddr, latest_reading);
        update_average_temperature(device_driver_for_temp_sensor_01.config->saddr);
        chThdSleepMilliseconds(DELAY_BETWEEN_TEMP_READINGS_IN_MS);

// Read second temperature sensor, update stats:
        read_tmp101an_temperature_v2(&device_driver_for_temp_sensor_02, byte_array);

        latest_reading = ((byte_array[0] << 4) | (byte_array[1] >> 4));

        store_reading(device_driver_for_temp_sensor_02.config->saddr, latest_reading);
        update_min_max_temperature(device_driver_for_temp_sensor_02.config->saddr, latest_reading);
        update_average_temperature(device_driver_for_temp_sensor_02.config->saddr);

        report_temperature_stats(device_driver_for_temp_sensor_01.config->saddr);
        report_temperature_stats(device_driver_for_temp_sensor_02.config->saddr);

        chThdSleepMilliseconds(SOLAR_BOARD_TEMPERATURE_READINGS_FREQ_IN_MS - DELAY_BETWEEN_TEMP_READINGS_IN_MS);
    }

    palClearLine(LINE_LED);
    chThdExit(MSG_OK);
}



// --- EOF ---
