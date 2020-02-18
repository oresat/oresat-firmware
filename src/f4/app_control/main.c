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
#include "shell.h"

/* Project header files */
#include "oresat.h"
#include "opd.h"
#include "command.h"

/*
 * Workers
 */
static worker_t shell_worker;

/*
 * Working area for driver.
 */
static uint8_t sd_scratchpad[512];

/*
 * SDIO configuration.
 */
static const SDCConfig sdccfg = {
  sd_scratchpad,
  SDC_MODE_4BIT
};

static oresat_config_t oresat_conf = {
    &CAND1,
    0x01,
    ORESAT_DEFAULT_BITRATE
};

/**
 * @brief App Initialization
 */
static void app_init(void)
{
    /* App initialization */
    init_worker(&shell_worker, "Command Shell", cmd_wa, sizeof(cmd_wa), NORMALPRIO, cmd, NULL);
    reg_worker(&shell_worker);

    /* Initialize OPD */
    opd_init();
    opd_start();

    /* Initialize shell and start serial interface */
    shellInit();
    sdStart(&SD2, NULL);

    /* Initializes SDIO drivers */
    sdcStart(&SDCD1, &sdccfg);
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
