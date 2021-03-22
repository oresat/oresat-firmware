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
#include "oresat_f0.h"

#include "firmware_blob.h"

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



// xxd -i app_protocard2.crc32.bin > ../../../f4/app_f407_discovery/firmware_blob.h
/*
 * This is an example of reading source firmware image data from an in-memory buffer, but this function could be implemented
 * to open a file from a file system, seek to an offset in the file, read some data into dest_buffer and close the file.
 */
uint32_t firmware_blob_read_function(const uint32_t offset, uint8_t *dest_buffer, const uint32_t number_of_bytes) {
	uint32_t dest_index = 0;

	for(; dest_index < number_of_bytes; dest_index++ ) {
		if( (offset + dest_index) < app_protocard2_crc32_bin_len ) {
			dest_buffer[dest_index] = app_protocard2_crc32_bin[offset + dest_index];
		} else {
			break;
		}
	}

	return(dest_index);
}

uint32_t test_read_function(const uint32_t offset, uint8_t *dest_buffer, const uint32_t number_of_bytes) {
	chprintf(DEBUG_SD, "Calling test_read_function(%u, x, %u)\r\n", offset, number_of_bytes);

	uint32_t dest_index = 0;
	for(; dest_index < number_of_bytes; dest_index++ ) {
		dest_buffer[dest_index] = (offset + dest_index) % 0xFF;
	}

	return(dest_index);
}

void test_garbage_can_transmit(void) {
	while(1) {
		CANTxFrame tx_msg;
		memset(&tx_msg, 0, sizeof(tx_msg));
		tx_msg.SID = 0x55;
		tx_msg.DLC = 8;
		memset(&tx_msg.data8, 0x55, sizeof(tx_msg.data8));

		can_api_print_tx_frame(DEBUG_SD, &tx_msg, "", "");

		canTransmit(CAN_DRIVER, CAN_ANY_MAILBOX, &tx_msg, TIME_MS2I(150));
		chThdSleepMilliseconds(1000);
	}
}


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


#define TARGET_STM32_BOOTLOADER       0


  //http://www.bittiming.can-wiki.info/
#if TARGET_STM32_BOOTLOADER
  cancfg.btr = (CAN_BTR_SJW(0) | CAN_BTR_TS1(12) | CAN_BTR_TS2(1) | CAN_BTR_BRP(20));
#else
  cancfg.btr = (CAN_BTR_SJW(0) | CAN_BTR_TS1(10) | CAN_BTR_TS2(1) | CAN_BTR_BRP(2));
#endif
  cancfg.mcr = (
		  /* MCR (Master Control Register) */
		  CAN_MCR_ABOM      |     //Automatic Bus-Off Management
		  CAN_MCR_AWUM      |     //Automatic Wakeup Mode
		  CAN_MCR_TXFP      |     //Transmit FIFO Priority
		  0/*CAN_MCR_NART*/   );       // No Automatic Retransmission

  chprintf(DEBUG_SD, "Initializing CAN peripheral with MCR = 0x%X\r\n", cancfg.mcr);
  chprintf(DEBUG_SD, "Initializing CAN peripheral with BTR = 0x%X\r\n", cancfg.btr);


  canSTM32SetFilters(CAN_DRIVER, 0, 0, NULL);
  canStart(CAN_DRIVER, &cancfg);

  /* Put CAN module in normal mode */
  //canSTM32SetFilters(&CAND2, 0, 0, NULL);
  //canStart(&CAND2, &cancfg);

  chprintf(DEBUG_SD, "Done starting CAN peripheral\r\n");


  //can_bootloader_test(CAN_DRIVER, DEBUG_SD);
  /*
   * Creates the example thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

#if TARGET_STM32_BOOTLOADER
  can_bootloader_config_t can_bl_config;
  can_api_init_can_bootloader_config_t(&can_bl_config, CAN_DRIVER, DEBUG_SD, 0, true);

  //can_bootloader_initiate(&can_bl_config, 3000);
  //can_bootloader_test(&can_bl_config);
  oresat_firmware_update_m0(&can_bl_config, 0x08000000, 16, test_read_function);

#else
  const uint32_t low_cpuid_of_protoboard = 0x1D000800;
  can_bootloader_config_t can_bl_config;
  can_api_init_can_bootloader_config_t(&can_bl_config, CAN_DRIVER, DEBUG_SD, low_cpuid_of_protoboard, false);

  //test_garbage_can_transmit();
  //oresat_firmware_update_m0(&can_bl_config, ORESAT_F0_FIRMWARE_CRC_ADDRESS, 72, test_read_function);

  oresat_firmware_update_m0(&can_bl_config, ORESAT_F0_FIRMWARE_CRC_ADDRESS, app_protocard2_crc32_bin_len, firmware_blob_read_function);
#endif

  print_can_bootloader_config_t(&can_bl_config);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state.
   */
  while (true) {
#if 0
	  CANTxFrame tx_msg;
	  memset(&tx_msg, 0, sizeof(tx_msg));
	  tx_msg.SID = 0x79;
	  tx_msg.DLC = 8;
	  memset(&tx_msg.data8, 0x55, sizeof(tx_msg.data8));

	  can_api_print_tx_frame(DEBUG_SD, &tx_msg, "TXing: ", "");

	  canTransmit(CAN_DRIVER, CAN_ANY_MAILBOX, &tx_msg, TIME_MS2I(150));

#endif

#if 0
	  CANRxFrame rx_msg;
	  memset(&rx_msg, 0, sizeof(rx_msg));
	  chprintf(DEBUG_SD, "CAN State: %u\r\n", (CAN_DRIVER)->state);
	  chprintf(DEBUG_SD, "Attempting CAN RX....\r\n");
	  can_api_receive(&can_bl_config, &rx_msg, 1000);
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






