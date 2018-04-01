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

//=== ChibiOS header files
#include "ch.h"
#include "hal.h"
#include "chprintf.h"

//=== Project header files
//#include "can.h"
#include "acs_bldc.h"

//=== Serial configuration
static SerialConfig ser_cfg = {
	115200,     //Baud rate
	0,          //
	0,          //
	0,          //
};

// bldc control thread
static THD_WORKING_AREA(wa_bldcThread,128);
static THD_FUNCTION(bldcThread,arg){
  (void)arg;
  chRegSetThreadName("bldc");
//	bldcSinStart();
	
  while(!chThdShouldTerminateX()){
    chThdSleepMilliseconds(500);
  }
}

static void app_init(void){
	// Start up debug output
	bldcInit();
	sdStart(&SD2, &ser_cfg);
}

static void app_main(void){
	chThdCreateStatic(
		wa_bldcThread,
		sizeof(wa_bldcThread), 
		NORMALPRIO, 
		bldcThread, 
		NULL
	);

	/*
	 * Begin main loop
	 */
	while (true){
		chThdSleepMilliseconds(1000);
	}
}

int main(void) {
	/*
	 * System initializations.
	 * - HAL initialization, this also initializes the configured device drivers
	 *   and performs the board-specific initializations.
	 * - Kernel initialization, the main() function becomes a thread and the
	 *   RTOS is active.
	 */
	halInit();
	chSysInit();
	// Initialize CAN Subsystem
	//can_init();
	// Start CAN threads
	//can_start();

	// Initialize and start app
	app_init();
	app_main();

	return 0;
}

//! @}
