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

/* Project header files */
#include "oresat.h"
#include "batt.h"

static worker_t battery_worker;

static oresat_config_t oresat_conf = {
    &CAND1,
    0x02,
    ORESAT_DEFAULT_BITRATE
};

/**
 * @brief App Initialization
 */
static void app_init(void)
{
    /* App initialization */
    init_worker(&battery_worker, "Battery monitoring thread", batt_wa, sizeof(batt_wa), NORMALPRIO, batt, NULL);
    reg_worker(&battery_worker);

    /* Start up debug output */
    sdStart(&SD2, NULL);
}

/**
 * @brief Main Application
 */
int main(void)
{
    // Initialize and start
    oresat_init();
    app_init();
    oresat_start(&oresat_conf);
    return 0;
}
