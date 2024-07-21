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
#include "diode_test.h"

static oresat_config_t oresat_conf = {
  .cand = &CAND1,
  .node_id = DTC_NODE_ID,
  .bitrate = ORESAT_DEFAULT_BITRATE,
};

static worker_t blink_worker;
static thread_descriptor_t blink_worker_desc = {
  .name = "blink count tpdo thread",
  .wbase = THD_WORKING_AREA_BASE(blink_wa),
  .wend = THD_WORKING_AREA_END(blink_wa),
  .prio = NORMALPRIO,
  .funcp = blink,
  .arg = NULL
};

static worker_t dtc_watch_worker;
static thread_descriptor_t dtc_watch_worker_desc = {
  .name = "stc watcher thread",
  .wbase = THD_WORKING_AREA_BASE(dtc_watch_wa),
  .wend = THD_WORKING_AREA_END(dtc_watch_wa),
  .prio = NORMALPRIO,
  .funcp = dtc_watch,
  .arg = NULL
};

static worker_t ctrl_thread_worker;
static thread_descriptor_t ctrl_thread_worker_desc = {
  .name = "control thread",
  .wbase = THD_WORKING_AREA_BASE(ctrl_thread_wa),
  .wend = THD_WORKING_AREA_END(ctrl_thread_wa),
  .prio = NORMALPRIO,
  .funcp = ctrl_thread,
  .arg = NULL
};

/**
 * @brief App Initialization
 */
static void app_init(void)
{
  /* App initialization */
  dtc_init();  
  reg_worker(&blink_worker, &blink_worker_desc, true, true);
  reg_worker(&dtc_watch_worker, &dtc_watch_worker_desc, true, true);
  reg_worker(&ctrl_thread_worker, &ctrl_thread_worker_desc, true, true);
  
  /* Start up serial for debug output */
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
  chprintf(DEBUG_SERIAL, "\r\nStarting app_diode...\r\n");
  oresat_start();

  return 0;
}
