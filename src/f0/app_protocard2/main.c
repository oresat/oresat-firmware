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
#include "oresat_f0.h"
#include <string.h>
#include "blink.h"


static worker_t worker1;

static oresat_config_t oresat_conf = {
    &CAND1,
	ORESAT_PROTOCARD_NODE_ID,
    ORESAT_DEFAULT_BITRATE
};

/**
 * @brief App Initialization
 */
static void app_init(void)
{
    /* App initialization */
    init_worker(&worker1, "Example blinky thread", blink_wa, sizeof(blink_wa), NORMALPRIO, blink, NULL, true);
    reg_worker(&worker1);

    /* Start up debug output */
    sdStart(&SD2, NULL);
    chprintf(DEBUG_SD, "\r\nInitiaized debug output...\r\n");
}

/**
 * @brief Main Application
 */
int main(void)
{
    oresat_init2(true);
    app_init();

    chprintf((BaseSequentialStream *) &SD2, "\r\n===================================================\r\n"); chThdSleepMilliseconds(30);

    chprintf(DEBUG_SD, "running oresat_start()\r\n"); chThdSleepMilliseconds(30);
    oresat_start(&oresat_conf);

    chprintf(DEBUG_SD, "running main() long loop\r\n"); chThdSleepMilliseconds(30);
    while(1) {
    	chThdSleepMilliseconds(1000);
    }
    return 0;
}




