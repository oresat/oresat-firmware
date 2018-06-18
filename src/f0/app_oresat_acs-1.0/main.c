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

//=== Project header files
#include "acs.h"

// global ACS structure
ACS acs = {};

//=== Serial configuration
static SerialConfig ser_cfg ={
	115200,     //Baud rate
	0,          //
	0,          //
	0,          //
};

/**
 * @brief Application initialization section
 *
 */
static void app_init(void) {
	acsInit(&acs);

	/// initialization of CAN resources for sending and
	/// receiving. registers two 8-byte uint8_t arrays
	/// with the CAN bus. these are shared resources
	/// between the ACS and the CAN bus
	canRPDOObjectInit(CAN_PDO_1,CAN_ID_DEFAULT,CAN_BUF_SIZE,acs.can_buf.recv);
	canTPDOObjectInit(CAN_PDO_1,CAN_ID_DEFAULT,0,0,CAN_BUF_SIZE,acs.can_buf.send);
	/// serial output for debugging
	sdStart(&SD2, &ser_cfg);
}

/**
 * @brief main appliction section
 *
 * starts the acs thread and then sleeps
 *
 */
static void app_main(void) {
	chThdCreateStatic(
		wa_acsThread,
		sizeof(wa_acsThread), 
		NORMALPRIO+1, 
		acsThread, 
		&acs	
	);

	while (true){
		chThdSleepMilliseconds(1000);
	}
}

/**
 * @brief main
 *
 * calls initialization functions
 * and then calls app_main()
 *
 */
int main(void){
	halInit();
	chSysInit();
	oresat_init(CAN_NODE);

	/// Initialize and start app
	app_init();
	app_main();

	return 0;
}
