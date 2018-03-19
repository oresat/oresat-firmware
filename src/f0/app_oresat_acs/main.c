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

/*
 *	OreSat: Attitude Control System
 *	Portland State Aerospace Society (PSAS)
 *	
 *  // be wery wery quiet i'm hunting wabbits...
 *
 *	// add your name if you code things
 *	// and you are paying attention
 *	// and you want your code things in
 *	// space 
 *	
 *	// o_0
 *
 *	Chad Coates	
 *
 */

//=== ChibiOS header files
#include "ch.h"
#include "hal.h"
#include "chprintf.h"

//=== Project header files
#include "can.h"
#include "acs.h"
#include "acs_bldc.h"

ACSdata data;
//uint8_t data[8];

static SerialConfig ser_cfg = {
	115200,     //Baud rate
	0,          //
	0,          //
	0,          //
};

static void app_init(void){
//	acs_init();	 
	bldcInit();
	can_initRPDO(0,0,8,data.acs);
//	initTPDO();

	sdStart(&SD2,&ser_cfg); // Start up debug output
}

static void app_main(void){
/*		
	chThdCreateStatic(
		waACSThread,
		sizeof(waACSThread),
		NORMALPRIO,
		ACSThread,
		NULL
	);
//*/
//*
	chThdCreateStatic(
		wa_bldcThread,
		sizeof(wa_bldcThread), 
		NORMALPRIO, 
		bldcThread, 
		NULL
	);
//*/

/*
	chThdCreateStatic(
		wa_acsThread,
		sizeof(wa_acsThread), 
		NORMALPRIO, 
		acsThread, 
		NULL
	);
//*/
	while(true){
		chThdSleepMilliseconds(1000);
	}
}

int main(void) {
	halInit();
	chSysInit();
	
	can_init(CAN_NODE,200);
  can_start();
	
	app_init();
	app_main();
	
	return 0;
}

//! @}
