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

/**
 * ChibiOS header files
 */
#include "ch.h"
#include "hal.h"
#include "shell.h"
#include "acs_common.h"

/** 
 *	Project header files
 */
#include "acs.h"
#include "oresat.h"
#include "acs_command.h"

ACS acs = { }; /// Global ACS struct

/**
 *	App initialization function
 */
static void app_init(void)
{
  acs_init(&acs);

  /* Initialize shell and start serial interface */
  shellInit();
  
  /*oresat_start(&CAND1);*/
  sdStart(&DEBUG_SERIAL, &ser_cfg);	/// Start serial support
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
  { /// main loop
		chThdSleepMilliseconds(1000);
	}
}

/**
 * Application main function
 */
int main(void)
{
	/**
	 * ChibiOS and OreSat init
	 */
	halInit();
	chSysInit();
  oresat_init(ORESAT_DEFAULT_ID, ORESAT_DEFAULT_BITRATE);

	/**
	 * App init and main
	 */
	app_init();
	app_main();

	return 0;
}
