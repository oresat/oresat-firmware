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
#include "oresat_f0.h"
#include "can_hw.h"
#include "crc32.h"
#include <string.h>
#include "flash_f0.h"
#include "can_bootloader_api.h"
#include "oresat_misc.h"

#define SCB_AIRCR_SYSRESETREQ                        (1 << 2)

#define BOOTLOADER_VERSION                           0xAB
#define CAN_DRIVER                                   &CAND1

#define CAN_RECEIVE_TIMEOUT                          TIME_MS2I(150)
#define CAN_RECEIVE_TIMEOUT_LONG                     TIME_MS2I(500)
#define CAN_TRANSMIT_TIMEOUT                         TIME_MS2I(150)
#define TEMP_WRITE_BUFFER_SIZE                       4096
#define BOOTLOADER_VALIDATED_FIRMWARE_MAGIC_NUMBER   0x12345678

//Memory address at the 31k mark, not allocated or cleared by CRT of hte OS due to linker script specifying RAM as 31k instead of the full 32k
volatile uint32_t *bootloader_magic_number_pointer = (uint32_t *) 0x20007C00;

uint32_t *cpu_unique_id_low = (uint32_t *) 0x1FFFF7AC;
uint8_t bootloader_temp_write_buffer[TEMP_WRITE_BUFFER_SIZE]; //Spec says maximum of 2048 bytes needed for buffer

#define DEBUG_SD    (BaseSequentialStream *)          &SD2

void soft_reset_cortex_m0(void) {
	canStop(CAN_DRIVER);
	sdStop(&SD2);

	chSysDisable();

	__DSB();
	SCB->AIRCR = ((0x5FA << 16) | SCB_AIRCR_SYSRESETREQ);
	__DSB();

	while (1) {
	}
}

/**
 * @return True if the key meta-data fields of the firmware image are reasonable and valid. False other wise
 */
bool validate_firmware_meta_data(const uint32_t length, const uint32_t expected_crc32) {
	if (length == 0|| expected_crc32 == 0 || length == UINT32_MAX || expected_crc32 == UINT32_MAX) {
		return (false);
	}

	if( length >= ORESAT_F0_FIRMWARE_MAXIMUM_LENGTH) {
		return(false);
	}

	return (true);
}

/**
 * @param *base_address Memory address at which the firmware metadata is located
 * @param length Number of bytes to CRC
 * @param expected_crc32 Expected CRC value of memory
 *
 * @return True if the CRC of flash matche, false otherwise
 */
bool validate_firmware_image(void *base_address, const uint32_t length, const uint32_t expected_crc32) {
	if( ! validate_firmware_meta_data(length, expected_crc32) ) {
		return(false);
	}

	const uint32_t crc_of_flash_data = crc32(0, base_address, length);

	if( crc_of_flash_data != expected_crc32 ) {
		return(false);
	}

	return(true);
}

void branch_to_firmware_image(void) {
	chSysDisable();

	__set_MSP(*(uint32_t*) ORESAT_F0_FIRMWARE_CODE_ADDRESS);
	(*(void (**)()) (ORESAT_F0_FIRMWARE_CODE_ADDRESS + 4))();
}

/**
 *  @return true if the firmware image is valid, false otherwise
 */
bool check_firmware_crc_and_branch(const bool print_serial_output) {
	const uint32_t firmware_expected_crc    = *((uint32_t *) ORESAT_F0_FIRMWARE_CRC_ADDRESS);
	const uint32_t firmware_expected_length = *((uint32_t *) ORESAT_F0_FIRMWARE_LENGTH_ADDRESS);
	const uint32_t firmware_version = *((uint32_t *) ORESAT_F0_FIRMWARE_VERSION_ADDRESS);
	const bool firmware_metadata_valid = validate_firmware_meta_data(firmware_expected_length, firmware_expected_crc);

	const bool is_firmware_valid = validate_firmware_image((void*) ORESAT_F0_FIRMWARE_LENGTH_ADDRESS, firmware_expected_length, firmware_expected_crc);

	if( print_serial_output ) {
		chprintf(DEBUG_SD, "firmware_expected_crc = 0x%X\r\n", firmware_expected_crc);
		chprintf(DEBUG_SD, "firmware_expected_length = %u\r\n", firmware_expected_length);
		if( firmware_metadata_valid ) {
			chprintf(DEBUG_SD, "firmware_actual CRC = 0x%X\r\n", crc32(0, (void*) ORESAT_F0_FIRMWARE_LENGTH_ADDRESS, firmware_expected_length));
		}
		chprintf(DEBUG_SD, "firmware_version = %u\r\n", firmware_version);
		chprintf(DEBUG_SD, "firmware_metadata_valid = %u\r\n", firmware_metadata_valid);
		chprintf(DEBUG_SD, "is_firmware_valid = %u\r\n", is_firmware_valid);
	}

	return(is_firmware_valid);
}


msg_t can_bootloader_transmit(CANTxFrame *msg) {
	const msg_t r = canTransmit(CAN_DRIVER, CAN_ANY_MAILBOX, msg, CAN_TRANSMIT_TIMEOUT);
	if( r == MSG_OK ) {
		can_api_print_tx_frame(DEBUG_SD, msg, "", " - SUCCESS");
	} else {
		can_api_print_tx_frame(DEBUG_SD, msg, "", " - FAIL");
	}
	chThdSleepMilliseconds(20);
	return(r);
}

msg_t can_bootloader_receive(CANRxFrame *msg) {
	msg_t r = canReceive(CAN_DRIVER, CAN_ANY_MAILBOX, msg, CAN_RECEIVE_TIMEOUT);
	if( r == MSG_OK ) {
		can_api_print_rx_frame(DEBUG_SD, msg, "", "");
	}
	return(r);
}

msg_t can_bootloader_receive2(CANRxFrame *msg, sysinterval_t timeout) {
	const msg_t r = canReceive(CAN_DRIVER, CAN_ANY_MAILBOX, msg, timeout);
	if( r == MSG_OK ) {
#if 1
		can_api_print_rx_frame(DEBUG_SD, msg, "", "");
#else
		chprintf(DEBUG_SD, "CAN RX: SID = 0x%X DLC = %u [", msg->SID, msg->DLC);
		for(int i = 0; i < msg->DLC && i < 8; i++ ) {
			chprintf(DEBUG_SD, " 0x%X", msg->data8[i]);
		}
		chprintf(DEBUG_SD, " ]\r\n");
#endif
	}
	return(r);
}


void can_bootloader_init_frame(CANTxFrame *msg, const uint32_t sid, const uint32_t dlc) {
	memset(msg, 0, sizeof(*msg));
	msg->SID = sid;
	msg->IDE = CAN_IDE_STD;
	msg->DLC = dlc;
}

/**
 * Sends a ACK or NACK to the host to indicate success or failure of a given CAN command
 *
 * @sid The command ID for which this ack/nack is with respect.
 * @ack_flag ture if an ACK is to be sent, false if a NACK is to be sent
 */
bool can_bootloader_send_ack_nack(const uint32_t sid, const bool ack_flag) {
	msg_t tx_r;
	CANTxFrame tx_msg;
	can_bootloader_init_frame(&tx_msg, sid, 1);
	if( ack_flag ) {
		tx_msg.data8[0] = STM32_BOOTLOADER_CAN_ACK;
	} else {
		tx_msg.data8[0] = STM32_BOOTLOADER_CAN_NACK;
	}

	if( (tx_r = can_bootloader_transmit(&tx_msg)) != MSG_OK ) {
		return(false);
	}
	return(true);
}

bool can_bootloader_send_ack(const uint32_t sid) {
	chprintf(DEBUG_SD, "Transmitting CAN bootloader ACK\r\n");
	return(can_bootloader_send_ack_nack(sid, true));
}

bool can_bootloader_send_nack(const uint32_t sid) {
	chprintf(DEBUG_SD, "Transmitting CAN bootloader NACK\r\n");
	return(can_bootloader_send_ack_nack(sid, false));
}

/**
 * @return true if the page_number can be erased, false otherwise
 */
bool is_flash_page_eraseable(const uint8_t page_number) {
	extern int __flash0_end__;
	uint32_t *bootloader_end_flash = (uint32_t *) &__flash0_end__;
	uint32_t last_bootloader_page_number = ((((uint32_t)bootloader_end_flash) - 0x08000000) / STM32F093_FLASH_PAGE_SIZE) - 1;

	//chprintf(DEBUG_SD, "last_bootloader_page_number = %u\r\n", last_bootloader_page_number);

	if( page_number > last_bootloader_page_number && page_number <= FLASH_PAGE_COUNT) {
		return(true);
	}

	return(false);
}

/**
 * @return true if the given flash address can be written to, false otherwise.
 */
bool is_flash_write_address_valid(const uint8_t *address) {
	extern int __flash0_base__;
	extern int __flash0_end__;
	uint8_t *bootloader_start_flash = (uint8_t *) &__flash0_base__;
	uint8_t *bootloader_end_flash = (uint8_t *) &__flash0_end__;

	if( address >= bootloader_start_flash && address < bootloader_end_flash ) {
		//Disallow writes to flash where the bootloader is stored
		return(false);
	}

	extern int __ram0_base__;
	extern int __ram0_end__;

	uint8_t *ram_start = (uint8_t *) &__ram0_base__;
	uint8_t *ram_end = (uint8_t *) &__ram0_end__;
	if( address >= ram_start && address < ram_end ) {
		//Disallow writes to RAM as it will corrupt the execution of the bootloader
		return(false);
	}

	if( address >= bootloader_end_flash && address <= ((uint8_t *) 0x0803FFFF) ) {
		return(true);
	}

	return(false);
}

bool is_flash_write_address_range_valid(const uint8_t *address, const uint32_t length) {
	if( ! is_flash_write_address_valid(address) ) {
		return(false);
	}
	if( ! is_flash_write_address_valid(address + length)) {
		return(false);
	}
	return(true);
}


void can_bootloader_handle_fram(CANRxFrame *rx_msg) {
	msg_t tx_r;
	const uint32_t command_sid = rx_msg->SID;
	chprintf(DEBUG_SD, "Handling frame SID 0x%X %s\r\n", command_sid, oresat_bootloader_can_command_t_to_str(command_sid));

	CANTxFrame reply_msg;
	memset(&reply_msg, 0, sizeof(reply_msg));


	switch ((oresat_bootloader_can_command_t) command_sid) {
		case ORESAT_BOOTLOADER_CAN_COMMAND_GET:
		{
			can_bootloader_send_ack(command_sid);

			const uint8_t cmd_list[] = {BOOTLOADER_VERSION,
					ORESAT_BOOTLOADER_CAN_COMMAND_GET,
					ORESAT_BOOTLOADER_CAN_COMMAND_READ_MEMORY,
					ORESAT_BOOTLOADER_CAN_COMMAND_GO,
					ORESAT_BOOTLOADER_CAN_COMMAND_WRITE_MEMORY,
					ORESAT_BOOTLOADER_CAN_COMMAND_ERASE };

			can_bootloader_init_frame(&reply_msg, command_sid, 1);
			reply_msg.data8[0] = sizeof(cmd_list) - 1; //number of tx messages sent below
			if( (tx_r = can_bootloader_transmit(&reply_msg)) != MSG_OK ) {
				chprintf(DEBUG_SD, "Failed to transmit response - 1.\r\n");
			}

			for(uint32_t i = 0; i < sizeof(cmd_list); i++ ) {
				can_bootloader_init_frame(&reply_msg, command_sid, 1);
				reply_msg.data8[0] = cmd_list[i];
				if( (tx_r = can_bootloader_transmit(&reply_msg)) != MSG_OK ) {
					chprintf(DEBUG_SD, "Failed to transmit response - 2.\r\n");
				}
			}

			can_bootloader_send_ack(command_sid);
		}
			break;
		case ORESAT_BOOTLOADER_CAN_COMMAND_READ_MEMORY:
		{
			const uint8_t *address_to_read_from = (uint8_t *) ((rx_msg->data8[0] << 24) | (rx_msg->data8[1] << 16) | (rx_msg->data8[2] << 8) | rx_msg->data8[3]);
			const uint8_t number_of_bytes_to_read = rx_msg->data8[4];

			chprintf(DEBUG_SD, "Address to read from: 0x%X\r\n", address_to_read_from);
			chprintf(DEBUG_SD, "Number of bytes to read: %u\r\n", number_of_bytes_to_read);

			can_bootloader_send_ack(command_sid);

			for(int i = 0; i < number_of_bytes_to_read;) {
				can_bootloader_init_frame(&reply_msg, command_sid, 0);
				for(int j = 0; j < 8 && i < number_of_bytes_to_read; j++, i++) {
					reply_msg.data8[j] = address_to_read_from[i];
					reply_msg.DLC++;
				}

				if( (tx_r = can_bootloader_transmit(&reply_msg)) != MSG_OK ) {
					chprintf(DEBUG_SD, "Failed to transmit response data.\r\n");
				} else {
					chprintf(DEBUG_SD, "Transmitted %u bytes in response to read request.\r\n", reply_msg.DLC);
				}
			}

			can_bootloader_send_ack(command_sid);
		}
			break;
		case ORESAT_BOOTLOADER_CAN_COMMAND_GO:
		{
			can_bootloader_send_ack(command_sid);

			chprintf(DEBUG_SD, "Reseting cortex M0...\r\n");
			chThdSleepMilliseconds(100);

			soft_reset_cortex_m0();
		}
			break;
		case ORESAT_BOOTLOADER_CAN_COMMAND_WRITE_MEMORY:
		{
			const uint8_t *write_address = (uint8_t *) ((rx_msg->data8[0] << 24) | (rx_msg->data8[1] << 16) | (rx_msg->data8[2] << 8) | rx_msg->data8[3]);
			const uint8_t number_of_bytes_to_write = rx_msg->data8[4];
			msg_t r = 0;

			if( is_flash_write_address_range_valid(write_address, number_of_bytes_to_write) ) {
				can_bootloader_send_ack(command_sid);

				uint32_t temp_buffer_index = 0;
				while( temp_buffer_index < number_of_bytes_to_write ) {
					CANRxFrame write_rx_frame;
					if( (r = can_bootloader_receive(&write_rx_frame)) != MSG_OK ) {
						//Failed to receive an expected frame of data to be written
						break;
					}
					if( write_rx_frame.SID != 0x04 ) {//Recommended ID based on AN3154
						//Wrong SID, protocol misalignment?
						break;
					}

					for(int frame_idx = 0; frame_idx < write_rx_frame.DLC && frame_idx < 8; frame_idx++ ) {
						if( temp_buffer_index < TEMP_WRITE_BUFFER_SIZE ) {
							//Based on the protocol spec, the host will send a maximum of 2048 bytes for writing (1 page worth)
							bootloader_temp_write_buffer[temp_buffer_index] = write_rx_frame.data8[frame_idx];
							temp_buffer_index++;
						} else {
							break;
						}
					}

					can_bootloader_send_ack(command_sid);
				}

				chprintf(DEBUG_SD, "number_of_bytes_to_write = %u\r\n", number_of_bytes_to_write);
				chprintf(DEBUG_SD, "temp_buffer_index = %u\r\n", temp_buffer_index);


				if( number_of_bytes_to_write > 0 && temp_buffer_index == number_of_bytes_to_write ) {
					chprintf(DEBUG_SD, "Writing data to flash...\r\n");

					int fw_r = flashWriteF091((uintptr_t) write_address, bootloader_temp_write_buffer, number_of_bytes_to_write);

					if( fw_r == FLASH_RETURN_SUCCESS ) {
						chprintf(DEBUG_SD, "Successfully wrote data to flash...\r\n");
						can_bootloader_send_ack(command_sid);
					} else {
						chprintf(DEBUG_SD, "Failed to write data to flash...\r\n");
						can_bootloader_send_nack(command_sid);
					}
				} else {
					chprintf(DEBUG_SD, "Incorrect number of bytes to write...\r\n");
					can_bootloader_send_nack(command_sid);
				}
			} else {
				chprintf(DEBUG_SD, "Address 0x%X outside of valid write range...\r\n", write_address);
				can_bootloader_send_nack(command_sid);
			}
		}
			break;
		case ORESAT_BOOTLOADER_CAN_COMMAND_ERASE:
		{
			//const uint32_t number_of_pages_to_erase = rx_msg->DLC;
			const uint32_t number_of_pages_to_erase = rx_msg->data8[0] + 1;
			chprintf(DEBUG_SD, "number_of_pages_to_erase = %u\r\n", number_of_pages_to_erase);

			can_bootloader_send_ack(command_sid);

			for(uint32_t i = 1; i <= number_of_pages_to_erase && i < 8; i++ ) {
				int error_count = 0;

				const uint32_t page_number_to_erase = rx_msg->data8[i];
				if( is_flash_page_eraseable(page_number_to_erase) ) {
					chprintf(DEBUG_SD, "Erasing page number = %u\r\n", page_number_to_erase);
					chThdSleepMilliseconds(10);

					int re = flashPageEraseF091(page_number_to_erase);

					if( re == FLASH_RETURN_SUCCESS ) {
						chprintf(DEBUG_SD, "Successfully erased page\r\n");
					} else {
						chprintf(DEBUG_SD, "Failed to erase page\r\n");
						error_count++;
					}
				} else {
					chprintf(DEBUG_SD, "Page %u cannot be erased.\r\n", page_number_to_erase);
					chThdSleepMilliseconds(10);
					error_count++;
				}

				chprintf(DEBUG_SD, "Done with erase command\r\n");

				if( error_count > 0 ) {
					can_bootloader_send_nack(command_sid);
				} else {
					can_bootloader_send_ack(command_sid);
				}
			}
		}
			break;
	}
}

void can_bootloader_announce_presence_on_bus(void) {

	CANTxFrame txmsg;
	memset(&txmsg, 0, sizeof(txmsg));
	txmsg.SID = 0;
	txmsg.DLC = 8;
	txmsg.data32[0] = 0x04030201;
	txmsg.data32[1] = *cpu_unique_id_low;

	chprintf(DEBUG_SD, "Bootloader announcing presence on bus...\r\n");
	can_bootloader_transmit(&txmsg);
}

void can_bootloader_run(const bool is_firmware_a_valid) {
	CANConfig cancfg;
	memset(&cancfg, 0, sizeof(cancfg));
	// Tool for calculating STM32 bit timing: http://www.bittiming.can-wiki.info/
	cancfg.btr = CAN_BTR(1000);
    cancfg.mcr = (
            /* MCR (Master Control Register) */
            CAN_MCR_ABOM      |     //Automatic Bus-Off Management
            CAN_MCR_AWUM      |     //Automatic Wakeup Mode
            CAN_MCR_TXFP      |     //Transmit FIFO Priority
            0 /*CAN_MCR_NART*/   );       // No Automatic Retransmission


    chprintf(DEBUG_SD, "Initializing CAN peripheral with MCR = 0x%X\r\n", cancfg.mcr);
    chprintf(DEBUG_SD, "Initializing CAN peripheral with BTR = 0x%X\r\n", cancfg.btr);

	/* Put CAN module in normal mode */
	canSTM32SetFilters(CAN_DRIVER, 0, 0, NULL);
	canStart(CAN_DRIVER, &cancfg);
	chprintf(DEBUG_SD, "Done starting CAN peripheral\r\n");

	can_bootloader_announce_presence_on_bus();

	CANRxFrame rxmsg;
	const systime_t start_time = TIME_I2MS(chVTGetSystemTime());
	bool got_stay_bootloader_frame = false;

	//palSetLineMode(LINE_LED, PAL_MODE_OUTPUT_PUSHPULL);

	const uint32_t ms_threshold = 3000;
	while ( true ) {
		if( is_firmware_a_valid ) {
			if( (! got_stay_bootloader_frame) && ((TIME_I2MS(chVTGetSystemTime())) - start_time) >= ms_threshold ) {
				chprintf(DEBUG_SD, "No CAN frame after %u ms, reseting and running main firmware...\r\n", ms_threshold);
				break;
			}
		}

	    //palToggleLine(LINE_LED);

		const msg_t r = can_bootloader_receive2(&rxmsg, CAN_RECEIVE_TIMEOUT_LONG);
		if( r == MSG_OK ) {
			if( ! got_stay_bootloader_frame ) {
				if( rxmsg.SID == BOOTLOADER_EXPECTED_FIRST_FRAME_ID && rxmsg.DLC == 8 ) {
					if( rxmsg.data32[0] == *cpu_unique_id_low && rxmsg.data32[1] == CAN_ANNOUNCE_MAGIC_NUMBER ) {
						//Host will TX a reply frame with the magic number and CPU unique ID values swapped to indicaet this node should stay in bootloader mode
						chprintf(DEBUG_SD, "RXed frame to stay in bootloader mode...\r\n");
						got_stay_bootloader_frame = true;
					}
				}
			} else {
				can_bootloader_handle_fram(&rxmsg);
			}
		} else {
			if( r == MSG_TIMEOUT ) {
				chprintf(DEBUG_SD, ".");
				//can_bootloader_announce_presence_on_bus();
			} else {
				chprintf(DEBUG_SD, "Error receiving CAN frame: %s\r\n", msg_t_to_str(r));
			}
		}
	}

	canStop(CAN_DRIVER);
}

int main(void)
{
	if( (*bootloader_magic_number_pointer) == BOOTLOADER_VALIDATED_FIRMWARE_MAGIC_NUMBER ) {
		//Previous power cycle validated the firmware, just run the firmware without bootstraping the OS.
		//We specifically want to branch to the firmware image with the CPU as close to out of reset mode as possible.
		*bootloader_magic_number_pointer = 0;
		__DSB();
		if( check_firmware_crc_and_branch(false) ) {
			branch_to_firmware_image();
		}
	}

	//Note: none of this actually gets run because the __reset_handler_hook branchs to either the A or B firmware images
    halInit();
    chSysInit();

    sdStart(&SD2, NULL);
    chprintf(DEBUG_SD, "\r\n=======================================\r\n");
    chprintf(DEBUG_SD, "Bootloader started...\r\n");

	extern int __flash0_base__;
	extern int __flash0_end__;
	chprintf(DEBUG_SD, "Bootloader __flash0_base__ = 0x%X\r\n", (uint8_t *) &__flash0_base__);
	chprintf(DEBUG_SD, "Bootloader __flash0_end__ = 0x%X\r\n", (uint8_t *) &__flash0_end__);

	extern stkalign_t __main_thread_stack_base__;
	extern stkalign_t __main_thread_stack_end__;
	chprintf(DEBUG_SD, "Stack size: %u\r\n", ((uint8_t *) &__main_thread_stack_end__) - ((uint8_t *) &__main_thread_stack_base__));

	chThdSleepMilliseconds(50);

#if 0
	for(int i = 0; i < 140; i++ ) {
		chprintf(DEBUG_SD, "is_page_eraseable(%u) = %u\r\n", i, is_flash_page_eraseable(i));
	}
#endif

	chprintf(DEBUG_SD, "Checking firmware validity...\r\n"); chThdSleepMilliseconds(50);

    bool is_firmware_a_valid = check_firmware_crc_and_branch(true);
    is_firmware_a_valid = false;
    chprintf(DEBUG_SD, "Current is_firmware_a_valid = %u\r\n", is_firmware_a_valid);chThdSleepMilliseconds(20);
    can_bootloader_run(is_firmware_a_valid);

    if( is_firmware_a_valid ) {
    	*bootloader_magic_number_pointer = BOOTLOADER_VALIDATED_FIRMWARE_MAGIC_NUMBER;
    } else {
    	*bootloader_magic_number_pointer = 0;
    }

    chprintf(DEBUG_SD, "set *bootloader_magic_number_pointer = 0x%X\r\n", *bootloader_magic_number_pointer);
    chprintf(DEBUG_SD, "reseting MCU\r\n");
    chThdSleepMilliseconds(50);

    soft_reset_cortex_m0();

    return 0;
}

