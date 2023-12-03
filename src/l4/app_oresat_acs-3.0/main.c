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
//#include "shell.h"
//#include "acs_command.h"

static oresat_config_t oresat_conf = {
  .cand = &CAND1,
  .node_id = CAN_NOD_ID,
  .bitrate = ORESAT_DEFAULT_BITRATE,
};

ACS acs = { }; /// Global ACS struct

/**
 * @brief App Initialization
 */
static void app_init(void)
{
  /// App initialization 
  acs_init(&acs);

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
}

/**
 * @brief Main Application
 */
int main(void)
{
  /**
	 * ChibiOS and OreSat init
	 */
  oresat_init(&oresat_conf);
  app_init();
  app_main();
  oresat_start();
  return 0;
}
