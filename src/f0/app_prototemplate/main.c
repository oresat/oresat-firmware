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
#include "heartmon.h"

#define DEBUG_SERIAL    (BaseSequentialStream*) &SD2

static worker_t heartmon_worker;
static thread_descriptor_t heartmon_worker_desc = {
  .name = "heartmon thread",
  .wbase = THD_WORKING_AREA_BASE(heartmon_wa),
  .wend = THD_WORKING_AREA_END(heartmon_wa),
  .prio = NORMALPRIO,
  .funcp = heartmon,
  .arg = NULL
};

static oresat_config_t oresat_conf = {
  .cand = &CAND1,
  .node_id = ORESAT_DEFAULT_ID,
  .bitrate = ORESAT_DEFAULT_BITRATE,
};

/**
 * @brief App Initialization
 */
static void app_init(void)
{
  /* App initialization */
  reg_worker(&heartmon_worker, &heartmon_worker_desc, true, true);
  
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
  chprintf(DEBUG_SERIAL, "\r\nStarting cantalk app...\r\n");
  oresat_start();
  return 0;
}

