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

/// ChibiOS header files 
#include "ch.h"
#include "hal.h"

/// Project header files 
#include "oresat.h"
#include "acs_common.h"
#include "acs.h"
#include "blink.h"
//#include "shell.h"
//#include "acs_command.h"

static worker_t worker1;
static thread_descriptor_t worker1_desc = {
  .name = "Example blinky thread",
  .wbase = THD_WORKING_AREA_BASE(blink_wa),
  .wend = THD_WORKING_AREA_END(blink_wa),
  .prio = NORMALPRIO,
  .funcp = blink,
  .arg = NULL
};

static oresat_config_t oresat_conf = {
  .cand = &CAND1,
  .node_id = ORESAT_DEFAULT_ID,
  .bitrate = ORESAT_DEFAULT_BITRATE,
};

ACS acs = { }; /// Global ACS struct

/**
 * @brief App Initialization
 */
static void app_init(void)
{
  
  acs_init(&acs);

  /// App initialization 
  reg_worker(&worker1, &worker1_desc, false, true);

  /// Start up debug output 
  sdStart(&LPSD1, NULL);
}

/**
 * App main function
 */
static void app_main(void)
{

//*
	chThdCreateStatic( /// Create ACS thread
		waACS_Thread,
		sizeof(waACS_Thread),
		NORMALPRIO + 1,
		ACS_Thread,
		&acs	
	);
//*/

  while(true)
  { 
    /// main loop
		chThdSleepMilliseconds(1000);
	}
}

/**
 * @brief Main Application
 */
int main(void)
{
  /**
	 * ChibiOS and OreSat init
	 */
	halInit();
	chSysInit();

  /// Initialize and start
  oresat_init(&oresat_conf);
  app_init();
  oresat_start();
  app_main();
  return 0;
}
