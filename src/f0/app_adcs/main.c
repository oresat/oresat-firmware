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
#include "blink.h"
#include "source/adcs.h"

static worker_t blink_worker;
static thread_descriptor_t blink_desc = {
    .name = "Blink",
    .wbase = THD_WORKING_AREA_BASE(blink_wa),
    .wend = THD_WORKING_AREA_END(blink_wa),
    .prio = NORMALPRIO,
    .funcp = blink,
    .arg = NULL
};
static worker_t adcs_worker;
static thread_descriptor_t adcs_desc = {
    .name = "ADCS",
    .wbase = THD_WORKING_AREA_BASE(adcs_wa),
    .wend = THD_WORKING_AREA_END(adcs_wa),
    .prio = NORMALPRIO,
    .funcp = adcs,
    .arg = NULL
};

#define ORESAT_ACS_NODE_ID 0x38
static oresat_config_t oresat_conf = {
    .cand = &CAND1,
    .node_id = ORESAT_ACS_NODE_ID, //ORESAT_DEFAULT_ID,
    .bitrate = ORESAT_DEFAULT_BITRATE,
};

/**
 * @brief App Initialization
 */
static void app_init(void)
{
    /* App initialization */
    reg_worker(&blink_worker, &blink_desc, false, true);
    reg_worker(&adcs_worker, &adcs_desc, false, true);

    /* Start up debug output */
    sdStart(&SD2, NULL);
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
