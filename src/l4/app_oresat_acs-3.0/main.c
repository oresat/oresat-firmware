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
#include "acs_common.h"

/** 
 *	Project header files
 */
#include "acs.h"

ACS acs = { }; /// Global ACS struct

/**
 *	Structure for serial configuration
 */
static SerialConfig ser_cfg =
{
	115200,  /// Baud rate
	0,       //
	0,       //
	0,       //
};

/**
 *	pinConfig: for pin configuration
 *  /// TODO: fix the board file so
 *	/// this can go away
 */
static void pinConfig(void)
{
//	palSetPadMode(GPIOA,GPIOA_LED_GREEN,PAL_MODE_OUTPUT_PUSHPULL);
};

/**
 *	App initialization function
 */
static void app_init(void)
{
	pinConfig();

  /// Initialize CAN
  canRPDOObjectInit(
    CAN_PDO_1, 
    CAN_ID_DEFAULT, 
    CAN_BUF_SIZE, 
    acs.can_buf.cmd
  );
	
  canTPDOObjectInit(
    CAN_PDO_1, 
    CAN_ID_DEFAULT, 
    0, 
    0, 
    CAN_BUF_SIZE, 
    acs.can_buf.status
  );

  acs_init(&acs);

  sdStart(&DEBUG_SERIAL, &ser_cfg);	/// Start serial support

  dbgSerialOut("Serial driver started...\n\r", 0, 300);
  chprintf(DEBUG_CHP, "Serial test...\n\r");
  float test = 11.2;
  chprintf(DEBUG_CHP, "%d\n\r",(int)(test * 10));
  chprintf(DEBUG_CHP, "%f\n\r",test);
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

#ifdef DEBUG_LOOP
	chThdCreateStatic( /// Create CANdbg thread
		waCANDBG_Thread,
		sizeof(waCANDBG_Thread),
		NORMALPRIO,
		CANDBG_Thread,
		&acs	
	);
#endif

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
	oresat_init(CAN_NODE_ID);

	/**
	 * App init and main
	 */
	app_init();
	app_main();

	return 0;
}
