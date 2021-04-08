/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/* ChibiOS header files */
#include "ch.h"
#include "hal.h"
#include "chprintf.h"

/* Project header files */
#include "oresat.h"
#include "blink.h"

#include "MagneticSensorSPI.h"

//=== Serial configuration
static SerialConfig serial_conf ={
	115200,     //Baud rate
	0,          //
	0,          //
	0,          //
};

/* This pointer to a sequential stream actually points to our serial driver.
   To use the serial driver in chprintf we need to cast it and we are using
   this variable to perform a cast only once. 
   from https://www.playembedded.org/blog/vcp-stm32-chibios/ */
//extern static BaseSequentialStream* chp = (BaseSequentialStream*) &LPSD1;

static worker_t worker1;
static thread_descriptor_t worker1_desc = {
    .name = "Magnetic sensor thread",
    .wbase = THD_WORKING_AREA_BASE(sensor_wa),
    .wend = THD_WORKING_AREA_END(sensor_wa),
    .prio = NORMALPRIO,
    .funcp = sensor,
    .arg = NULL
};

static oresat_config_t oresat_conf = {
    &CAND1,
    ORESAT_DEFAULT_ID,
    ORESAT_DEFAULT_BITRATE
};

/**
 * @brief App Initialization
 */
static void app_init(void)
{
    /* Start up debug output */
    sdStart(&LPSD1, &serial_conf);

    chprintf(chp, "\n\rapp_init() started\n\r");
    chThdSleepMilliseconds(1000);

    
    /* App initialization */
    reg_worker(&worker1, &worker1_desc, true, true);

    
}

/**
 * @brief Main Application
 */
int main(void)
{
    // Initialize and start
    oresat_init(&oresat_conf);
    app_init();
    oresat_start();
    return 0;
}
