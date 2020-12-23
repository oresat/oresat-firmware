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
#include "wdt.h"
#include "c3.h"
#include "opd.h"
#include "comms.h"
#include "time_sync.h"
#include "CO_master.h"
#ifdef SHELL_ENABLE
#include "cmd.h"
#endif

/*
static const oresat_node_t nodes[] = {
    {0x02, 0x00, 2000, "Battery 1"},
    {0x03, 0x00, 2000, "Battery 2"},
    {0x04, 0x00, 2000, "Solar Panel 1"},
    {0x05, 0x00, 2000, "Solar Panel 2"},
    {0x06, 0x00, 2000, "Solar Panel 3"},
    {0x07, 0x00, 2000, "Solar Panel 4"},
    {0x08, 0x00, 2000, "Solar Panel 5"},
    {0x09, 0x00, 2000, "Solar Panel 6"},
    {0x0A, 0x00, 2000, "Solar Panel 7"},
    {0x0B, 0x00, 2000, "Solar Panel 8"},
    {0x31, 0x18, 2000, "Protocard 1"},
    {0x32, 0x19, 2000, "Protocard 2"},
    {0x33, 0x1A, 2000, "Protocard 3"},
    {0x11, 0x1D, 2000, "Star Tracker"}
};
*/

static worker_t wdt_worker;
static worker_t c3_worker;
#ifdef SHELL_ENABLE
static worker_t cmd_worker;
#endif

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
    /* Initialize WDT worker thread */
    init_worker(&wdt_worker, "WDT", wdt_wa, sizeof(wdt_wa), NORMALPRIO, wdt, NULL, true);
    reg_worker(&wdt_worker);

    /* Initialize C3 worker thread */
    init_worker(&c3_worker, "C3", c3_wa, sizeof(c3_wa), NORMALPRIO, c3, NULL, true);
    reg_worker(&c3_worker);

    /* Initialize shell worker thread */
#ifdef SHELL_ENABLE
    init_worker(&cmd_worker, "Shell", cmd_wa, sizeof(cmd_wa), NORMALPRIO, cmd, NULL, true);
    reg_worker(&cmd_worker);
#endif

    /* Initialize OPD */
    opd_init();
    opd_start();

    /* Initialize SDO client */
    sdo_init();

    /* Initialize and start radio systems */
    comms_init();
    comms_start();

    /* Initialize shell and start serial interface */
#ifdef SHELL_ENABLE
    shellInit();
#endif
    sdStart(&SD3, NULL);

    /* Configure SCET time object */
    CO_OD_configure(CO->SDO[0], OD_2010_SCET, OD_SCET_Func, NULL, 0, 0);
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
