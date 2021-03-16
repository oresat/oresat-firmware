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

#include "ch.h"
#include "hal.h"
#include "rt_test_root.h"
#include "oslib_test_root.h"
#include "chprintf.h"
#include "string.h"
#include "can_bootloader_api.h"

#define DEBUG_SD    (BaseSequentialStream *) &SD2

/*
 * This is a periodic thread that does absolutely nothing except flashing
 * a LED.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {
  (void)arg;
  chRegSetThreadName("blinker");
  while (true) {
    palSetPad(GPIOD, GPIOD_LED3);       /* Orange.  */
    chThdSleepMilliseconds(500);
    palClearPad(GPIOD, GPIOD_LED3);     /* Orange.  */
    chThdSleepMilliseconds(500);
  }
}

#define   CAN_DRIVER  &CAND1

#define   CAN_BTR(n) (CAN_BTR_SJW(0)|CAN_BTR_TS1(11)|CAN_BTR_TS2(1)|CAN_BTR_BRP((3000/n)-1))

/*
 * Application entry point.
 */
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

  /*
   * Activates the serial driver 2 using the driver default configuration.
   * PA2(TX) and PA3(RX) are routed to USART2.
   */
  sdStart(&SD2, NULL);

  palSetPadMode(GPIOA, 2, PAL_MODE_ALTERNATE(7));
  palSetPadMode(GPIOA, 3, PAL_MODE_ALTERNATE(7));
  chprintf(DEBUG_SD, "\r\n=======================================\r\n");
  chprintf(DEBUG_SD, "\r\n=========== discovery =================\r\n");
  chprintf(DEBUG_SD, "STM32_PCLK2 = %u\r\n", STM32_PCLK2);


  palSetPadMode(GPIOB, 8, PAL_MODE_ALTERNATE(9)); //CAN 1 RX
  palSetPadMode(GPIOB, 9, PAL_MODE_ALTERNATE(9)); //CAN 1 TX

  palSetPadMode(GPIOB, 5, PAL_MODE_ALTERNATE(9)); //CAN 2 RX
  palSetPadMode(GPIOB, 13, PAL_MODE_ALTERNATE(9)); //CAN 2 TX


  CANConfig cancfg;
  memset(&cancfg, 0, sizeof(cancfg));

  cancfg.btr = (CAN_BTR_SJW(0) | CAN_BTR_TS1(10) | CAN_BTR_TS2(1) | CAN_BTR_BRP(2));
  cancfg.mcr = (
		  /* MCR (Master Control Register) */
		  CAN_MCR_ABOM      |     //Automatic Bus-Off Management
		  CAN_MCR_AWUM      |     //Automatic Wakeup Mode
		  CAN_MCR_TXFP      |     //Transmit FIFO Priority
		  CAN_MCR_NART/*CAN_MCR_NART*/   );       // No Automatic Retransmission


  chprintf(DEBUG_SD, "Initializing CAN peripheral with MCR = 0x%X\r\n", cancfg.mcr);
  chprintf(DEBUG_SD, "Initializing CAN peripheral with BTR = 0x%X\r\n", cancfg.btr);


  canSTM32SetFilters(CAN_DRIVER, 0, 0, NULL);
  canStart(CAN_DRIVER, &cancfg);

  /* Put CAN module in normal mode */
  //canSTM32SetFilters(&CAND2, 0, 0, NULL);
  //canStart(&CAND2, &cancfg);

  chprintf(DEBUG_SD, "Done starting CAN peripheral\r\n");



  can_bootloader_test(CAN_DRIVER, DEBUG_SD);
  /*
   * Creates the example thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state.
   */
  while (true) {
#if 1
	  CANTxFrame tx_msg;
	  memset(&tx_msg, 0, sizeof(tx_msg));
	  tx_msg.SID = 0x55;
	  tx_msg.DLC = 8;
	  memset(&tx_msg.data8, 0x55, sizeof(tx_msg.data8));

	  //can_api_print_tx_frame(DEBUG_SD, &tx_msg, "", "");

	  //canTransmit(CAN_DRIVER, CAN_ANY_MAILBOX, &tx_msg, TIME_MS2I(150));
#endif

#if 1
	  CANRxFrame rx_msg;
	  memset(&rx_msg, 0, sizeof(rx_msg));
	  chprintf(DEBUG_SD, "CAN State: %u\r\n", CAND2.state);
	  chprintf(DEBUG_SD, "Attempting CAN RX....\r\n");
	  msg_t r = can_api_receive(CAN_DRIVER, &rx_msg, 1000, DEBUG_SD);
#endif


#if 0
    if (palReadPad(GPIOA, GPIOA_BUTTON)) {
      test_execute((BaseSequentialStream *)&SD2, &rt_test_suite);
      test_execute((BaseSequentialStream *)&SD2, &oslib_test_suite);
    }
#endif
    chThdSleepMilliseconds(500);
  }
}






