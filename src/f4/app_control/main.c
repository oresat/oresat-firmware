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
#include "fram.h"
#include "fs.h"
#include "opd.h"
#include "comms.h"
#include "rtc.h"
#include "CO_master.h"
#ifdef SHELL_ENABLE
#include "cli.h"
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

#ifdef SHELL_ENABLE
static worker_t cli_worker;
static thread_descriptor_t cli_desc = {
    .name = "Shell",
    .wbase = THD_WORKING_AREA_BASE(cli_wa),
    .wend = THD_WORKING_AREA_END(cli_wa),
    .prio = NORMALPRIO,
    .funcp = cli,
    .arg = NULL
};
#endif
static worker_t wdt_worker;
static thread_descriptor_t wdt_desc = {
    .name = "WDT",
    .wbase = THD_WORKING_AREA_BASE(wdt_wa),
    .wend = THD_WORKING_AREA_END(wdt_wa),
    .prio = HIGHPRIO,
    .funcp = wdt,
    .arg = NULL
};
static worker_t c3_worker;
static thread_descriptor_t c3_desc = {
    .name = "C3",
    .wbase = THD_WORKING_AREA_BASE(c3_wa),
    .wend = THD_WORKING_AREA_END(c3_wa),
    .prio = NORMALPRIO,
    .funcp = c3,
    .arg = NULL
};

static I2CConfig i2ccfg = {
    OPMODE_I2C,
    100000,
    STD_DUTY_CYCLE,
};

static FRAMConfig framcfg = {
    .i2cp = &I2CD2,
    .i2ccfg = &i2ccfg,
    .saddr = 0x50,
};

static SDCConfig sdccfg = {
    .bus_width = SDC_MODE_4BIT,
};

static FSConfig fscfg = {
    .sdcp = &SDCD1,
    .sdccfg = &sdccfg,
    .mmc_pwr = LINE_MMC_PWR,
};

static oresat_config_t oresat_conf = {
    .cand = &CAND1,
    .node_id = 0x01,
    .bitrate = ORESAT_DEFAULT_BITRATE,
};

/**
 * @brief App Initialization
 */
static void app_init(void)
{
#ifdef SHELL_ENABLE
    /* Initialize shell and start serial interface */
    shellInit();
    sdStart(&SD3, NULL);
    /* Register shell worker thread */
    reg_worker(&cli_worker, &cli_desc, true, true);
#endif

    /* Initialize FRAM */
    framObjectInit(&FRAMD1);
    framStart(&FRAMD1, &framcfg);

    /* Prepare filesystem */
    fs_init(&FSD1);
    fs_start(&FSD1, &fscfg);

    /* Initialize OPD */
    opd_init();
    opd_start();

    /* Initialize SDO client */
    sdo_init();

    /* Initialize and start radio systems */
    comms_init();
    comms_start();

    /* Register WDT and C3 worker thread */
    reg_worker(&wdt_worker, &wdt_desc, true, true);
    reg_worker(&c3_worker, &c3_desc, true, true);

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
