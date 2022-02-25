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
#include "persist.h"
#include "fs.h"
#include "node_mgr.h"
#include "comms.h"
#include "rtc.h"
#include "CO_master.h"
#ifdef SHELL_ENABLE
#include "cli.h"
#endif

static const oresat_node_t nodes[] = {
    {0x04, 0x18, 10000, true, "Battery 0"},
    /*{0x08, 0x1D, 10000, true, "Battery 1"},*/
    {0x0C, 0x00, 10000, false, "Solar Panel 0"},
    {0x10, 0x00, 10000, false, "Solar Panel 1"},
    {0x14, 0x00, 10000, false, "Solar Panel 2"},
    {0x18, 0x00, 10000, false, "Solar Panel 3"},
    /*{0x1C, 0x00, 10000, false, "Solar Panel 4"},*/
    /*{0x20, 0x00, 10000, false, "Solar Panel 5"},*/
    /*{0x24, 0x00, 10000, false, "Solar Panel 6"},*/
    /*{0x28, 0x00, 10000, false, "Solar Panel 7"},*/
    {0x2C, 0x1C, 10000, false, "Star Tracker 0"},
    /*{0x30, 0x00, 10000, false, "Star Tracker 1"},*/
    {0x34, 0x19, 10000, false, "GPS"},
    {0x38, 0x1A, 10000, false, "ACS"},
    /*{0x3C, 0x20, 10000, false, "RWB 0"},*/
    /*{0x40, 0x21, 10000, false, "RWB 1"},*/
    /*{0x44, 0x22, 10000, false, "RWB 2"},*/
    /*{0x48, 0x23, 10000, false, "RWB 3"},*/
    {0x4C, 0x1B, 10000, false, "DxWiFi"},
    {0x50, 0x1E, 10000, false, "CFC"},
    {0, 0, 0, 0, NULL}
};

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
    .prio = NORMALPRIO + 1,
    .funcp = c3,
    .arg = NULL
};
static worker_t node_mgr_worker;
static thread_descriptor_t node_mgr_desc = {
    .name = "Node Manager",
    .wbase = THD_WORKING_AREA_BASE(node_mgr_wa),
    .wend = THD_WORKING_AREA_END(node_mgr_wa),
    .prio = NORMALPRIO,
    .funcp = node_mgr,
    .arg = (void*)&nodes
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

    /* Register WDT and C3 worker thread */
    reg_worker(&wdt_worker, &wdt_desc, true, true);
    reg_worker(&node_mgr_worker, &node_mgr_desc, true, true);
    reg_worker(&c3_worker, &c3_desc, true, true);
    start_worker(&wdt_worker);

    /* Start crypto driver */
    cryStart(&CRYD1, NULL);

    /* Initialize FRAM */
    framObjectInit(&FRAMD1);
    framStart(&FRAMD1, &framcfg);

    /* Restore OD variables if available */
    persistRestoreAll();

    /* Prepare filesystem */
    fs_init(&FSD1);
    fs_start(&FSD1, &fscfg);

    /* Initialize SDO client */
    sdo_init();

    /* Initialize and start radio systems */
    comms_init();
    comms_start();
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
