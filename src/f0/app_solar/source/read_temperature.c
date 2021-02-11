/**
*  @project Oresat-1 solar board firmware
*
*  @file read_temperature.c
*
*  @authors and contributors
**/

#include "ch.h"
#include "hal.h"
#include "chprintf.h"   // for serial debugging
#include "tmp101an.h"   // driver for Texas Instruments' TMP101AN temperature sensor



#define SOLAR_BOARD_TEMPERATURE_READINGS_FREQ_IN_MS (4000)
#define TEMPERATURE_READING_SAMPLE_SIZE_TO_AVERAGE (10)


static uint16_t readings_sensor_01[TEMPERATURE_READING_SAMPLE_SIZE_TO_AVERAGE] = {0};
static uint16_t readings_sensor_02[TEMPERATURE_READING_SAMPLE_SIZE_TO_AVERAGE] = {0};



THD_WORKING_AREA(read_temperature_wa, 0x80);
THD_FUNCTION(read_temperature, arg)
{
    (void)arg;

    while (!chThdShouldTerminateX()) {
//        palToggleLine(LINE_LED);
        chprintf((BaseSequentialStream *) &SD2, "stub code in new thread\r\n");
        chThdSleepMilliseconds(SOLAR_BOARD_TEMPERATURE_READINGS_FREQ_IN_MS);
    }

    palClearLine(LINE_LED);
    chThdExit(MSG_OK);
}
