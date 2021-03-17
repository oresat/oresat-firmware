#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "can_bootloader_api.h"
#include "string.h"
#include "oresat_f0.h"


#define DEFAULT_RETRY_LIMIT     3


void can_api_print_rx_frame(BaseSequentialStream *chp, CANRxFrame *msg, const char *pre_msg, const char *post_msg) {
	chprintf(chp, "RX Frame: %s ", pre_msg);

	chprintf(chp, "SID = 0x%X ", msg->SID);
	chprintf(chp, "DLC = %u ", msg->DLC);
	chprintf(chp, "RTR = %u ", msg->RTR);
	chprintf(chp, "IDE = %u ", msg->IDE);

	chprintf(chp, "[ ");
	for(int i = 0; i < msg->DLC; i++ ) {
		chprintf(chp, "0x%X ", msg->data8[i]);
	}
	chprintf(chp, "] ");

	chprintf(chp, "%s", post_msg);
	chprintf(chp, "\r\n");
}


void can_api_print_tx_frame(BaseSequentialStream *chp, CANTxFrame *msg, const char *pre_msg, const char *post_msg) {
	chprintf(chp, "TX Frame: %s ", pre_msg);

	chprintf(chp, "SID = 0x%X ", msg->SID);
	chprintf(chp, "DLC = %u ", msg->DLC);
	chprintf(chp, "RTR = %u ", msg->RTR);
	chprintf(chp, "IDE = %u ", msg->IDE);

	chprintf(chp, "[ ");
	for(int i = 0; i < msg->DLC; i++ ) {
		chprintf(chp, "0x%X ", msg->data8[i]);
	}
	chprintf(chp, "] ");

	chprintf(chp, "%s", post_msg);
	chprintf(chp, "\r\n");
}


msg_t can_api_receive(CANDriver *canp, CANRxFrame *msg, const uint32_t timeout_ms, BaseSequentialStream *chp) {
	msg_t r = canReceive(canp, CAN_ANY_MAILBOX, msg, TIME_MS2I(timeout_ms));
	if( r == MSG_OK ) {
		can_api_print_rx_frame(chp, msg, "", "");
	}
	return(r);
}

void can_api_purge_rx_buffer(CANDriver *canp, BaseSequentialStream *chp) {
	CANRxFrame msg;
	for(int i = 0; i < 3; i++ ) {
		if( can_api_receive(canp, &msg, 5, chp) != MSG_OK ) {
			//break;
		}
	}
}

msg_t can_api_transmit(CANDriver *canp, CANTxFrame *msg, const uint32_t timeout_ms, BaseSequentialStream *chp) {
	const msg_t r = canTransmit(canp, CAN_ANY_MAILBOX, msg, TIME_MS2I(timeout_ms));
	if( r == MSG_OK ) {
		can_api_print_tx_frame(chp, msg, "", " - SUCCESS");
	} else {
		can_api_print_tx_frame(chp, msg, "", " - FAIL");
	}
	return(r);
}


bool can_bootloader_initiate(CANDriver *canp, const uint32_t timeout_ms, const uint32_t low_cpu_id, BaseSequentialStream *chp) {
	CANRxFrame msg;
	memset(&msg, 0, sizeof(msg));
	msg_t r = can_api_receive(canp, &msg, timeout_ms, chp);
	if( r == MSG_OK ) {
		if( msg.SID == ORESAT_BOOTLOADER_CAN_COMMAND_GET && msg.DLC == 8 ) {
			if( msg.data8[0] == 0x01 && msg.data8[1] == 0x02 && msg.data8[2] == 0x03 && msg.data8[3] == 0x04 ) {
				CANTxFrame tx_msg;
				memset(&tx_msg, 0, sizeof(tx_msg));
				tx_msg.SID = BOOTLOADER_EXPECTED_FIRST_FRAME_ID;
				tx_msg.DLC = 8;
				tx_msg.data8[0] = msg.data8[4];
				tx_msg.data8[1] = msg.data8[5];
				tx_msg.data8[2] = msg.data8[6];
				tx_msg.data8[3] = msg.data8[7];
				tx_msg.data8[4] = 0x01;
				tx_msg.data8[5] = 0x02;
				tx_msg.data8[6] = 0x03;
				tx_msg.data8[7] = 0x04;

				r = can_api_transmit(canp, &tx_msg, 100, chp);
				if( r == MSG_OK ) {
					chprintf(chp, "Successfully put remote node into bootloader mode...\r\n");
					return(true);
				}
			}
		}
	} else {
		chprintf(chp, "Failed to receive CAN frame to initiate CAN bootloader on a device...\r\n");
	}
	return(false);
}

bool can_bootloader_wait_for_ack(CANDriver *canp, const uint32_t sid_match, BaseSequentialStream *chp) {
	CANRxFrame rx_msg;
	memset(&rx_msg, 0, sizeof(rx_msg));

	msg_t r = can_api_receive(canp, &rx_msg, 1000, chp);
	if( r == MSG_OK ) {
		if( rx_msg.SID == sid_match && rx_msg.data8[0] == STM32_BOOTLOADER_CAN_ACK ) {
			can_api_print_rx_frame(chp, &rx_msg, "", " - ACK");
		} else if( rx_msg.SID == sid_match && rx_msg.data8[0] == STM32_BOOTLOADER_CAN_NACK ) {
			can_api_print_rx_frame(chp, &rx_msg, "", " - NACK");
		} else {
			can_api_print_rx_frame(chp, &rx_msg, "", " - UNKNOWN");
		}

		return(true);
	} else {
		chprintf(chp, "Failed to get CAN frame while waiting for ACK/NACK\r\n");
	}
	return(false);
}

bool can_bootloader_read_data(CANDriver *canp, const uint32_t memory_address, const uint32_t num_bytes_to_read, uint8_t *dest_buffer, const uint32_t dest_buffer_length, BaseSequentialStream *chp) {
	if( canp == NULL || dest_buffer == NULL ) {
		return(false);
	}

	//can_api_purge_rx_buffer(canp, chp);

	msg_t r = 0;

	CANTxFrame tx_msg;
	memset(&tx_msg, 0, sizeof(tx_msg));
	tx_msg.SID = ORESAT_BOOTLOADER_CAN_COMMAND_READ_MEMORY;
	tx_msg.DLC = 5;
	tx_msg.data8[0] = (memory_address >> 24) & 0xFF;
	tx_msg.data8[1] = (memory_address >> 16) & 0xFF;
	tx_msg.data8[2] = (memory_address >> 8) & 0xFF;
	tx_msg.data8[3] = (memory_address >> 0) & 0xFF;
	tx_msg.data8[4] = num_bytes_to_read;

	if( (r = can_api_transmit(canp, &tx_msg, 100, chp)) != MSG_OK ) {
		return(false);
	}
	if( ! can_bootloader_wait_for_ack(canp, ORESAT_BOOTLOADER_CAN_COMMAND_READ_MEMORY, chp) ) {
		return(false);
	}

	//const uint32_t expected_frame_count = math.ceil((num_bytes_to_read) / 8.0);
	uint32_t expected_frame_count = num_bytes_to_read / 8;
	if( num_bytes_to_read % 8 > 0 ) {
		expected_frame_count++;
	}

	chprintf(chp, "expected_frame_count = %u\r\n", expected_frame_count);

	uint32_t dest_buffer_index = 0;
	for(uint32_t i = 0; i < expected_frame_count; i++) {
		CANRxFrame rx_msg;
		memset(&rx_msg, 0, sizeof(rx_msg));
		msg_t r = can_api_receive(canp, &rx_msg, 1000, chp);
		if( r == MSG_OK ) {
			for(uint32_t j = 0; j < rx_msg.DLC && dest_buffer_index < dest_buffer_length && j < sizeof(rx_msg.data8); j++ ) {
				dest_buffer[dest_buffer_index] = rx_msg.data8[j];
				dest_buffer_index++;
			}
		}
	}

	chprintf(chp, "final dest_buffer_index = %u\r\n", dest_buffer_index);

	if( ! can_bootloader_wait_for_ack(canp, ORESAT_BOOTLOADER_CAN_COMMAND_READ_MEMORY, chp) ) {
		return(false);
	}


	chprintf(chp, "Successfully read memory from remote device...\r\n");
	for(uint32_t i = 0; i < dest_buffer_index; i++ ) {
		chprintf(chp, " 0x%X", 	dest_buffer[i]);
	}
	chprintf(chp, "\r\n\r\n");

	return(true);
}


bool can_bootloader_erase_page(CANDriver *canp, const uint32_t page_number, BaseSequentialStream *chp) {
	msg_t r = 0;

	CANTxFrame tx_msg;
	memset(&tx_msg, 0, sizeof(tx_msg));
	tx_msg.SID = ORESAT_BOOTLOADER_CAN_COMMAND_ERASE;
	tx_msg.DLC = 2;
	tx_msg.data8[0] = 0;
	tx_msg.data8[1] = page_number;


	if( (r = can_api_transmit(canp, &tx_msg, 100, chp)) != MSG_OK ) {
		return(false);
	}
	if( ! can_bootloader_wait_for_ack(canp, ORESAT_BOOTLOADER_CAN_COMMAND_ERASE, chp) ) {
		return(false);
	}
	if( ! can_bootloader_wait_for_ack(canp, ORESAT_BOOTLOADER_CAN_COMMAND_ERASE, chp) ) {
		return(false);
	}

	chprintf(chp, "Successfully erased page %u on remote device\r\n", page_number);
	return(true);
}


bool can_bootloader_write_memory(CANDriver *canp, const uint32_t memory_address, const uint8_t *src_buffer, const uint32_t num_bytes, BaseSequentialStream *chp) {
	msg_t r = 0;

	CANTxFrame tx_msg;
	memset(&tx_msg, 0, sizeof(tx_msg));
	tx_msg.SID = ORESAT_BOOTLOADER_CAN_COMMAND_WRITE_MEMORY;
	tx_msg.DLC = 5;
	tx_msg.data8[0] = (memory_address >> 24) & 0xFF;
	tx_msg.data8[1] = (memory_address >> 16) & 0xFF;
	tx_msg.data8[2] = (memory_address >> 8) & 0xFF;
	tx_msg.data8[3] = (memory_address >> 0) & 0xFF;
	tx_msg.data8[4] = num_bytes;


	if( (r = can_api_transmit(canp, &tx_msg, 100, chp)) != MSG_OK ) {
		return(false);
	}
	if( ! can_bootloader_wait_for_ack(canp, ORESAT_BOOTLOADER_CAN_COMMAND_WRITE_MEMORY, chp) ) {
		return(false);
	}


	uint32_t idx = 0;
	while(1) {
		memset(&tx_msg, 0, sizeof(tx_msg));
		tx_msg.SID = 0x04;

		while( idx < num_bytes && tx_msg.DLC < 8 ) {
			tx_msg.data8[tx_msg.DLC] = src_buffer[idx];
			tx_msg.DLC++;
			idx++;
		}

		if( tx_msg.DLC > 0 ) {
			if( (r = can_api_transmit(canp, &tx_msg, 100, chp)) != MSG_OK ) {
				return(false);
			}
			if( ! can_bootloader_wait_for_ack(canp, ORESAT_BOOTLOADER_CAN_COMMAND_WRITE_MEMORY, chp) ) {
				return(false);
			}
		} else {
			break;
		}
	}

	if( ! can_bootloader_wait_for_ack(canp, ORESAT_BOOTLOADER_CAN_COMMAND_WRITE_MEMORY, chp) ) {
		return(false);
	}

	chprintf(chp, "Successfully wrote memory on remote device...\r\n");

	return(true);
}


bool can_bootloader_go(CANDriver *canp, const uint32_t memory_address, BaseSequentialStream *chp) {
	msg_t r = 0;

	CANTxFrame tx_msg;
	memset(&tx_msg, 0, sizeof(tx_msg));
	tx_msg.SID = ORESAT_BOOTLOADER_CAN_COMMAND_GO;
	tx_msg.DLC = 4;
	tx_msg.data8[0] = (memory_address >> 24) & 0xFF;
	tx_msg.data8[1] = (memory_address >> 16) & 0xFF;
	tx_msg.data8[2] = (memory_address >> 8) & 0xFF;
	tx_msg.data8[3] = (memory_address >> 0) & 0xFF;


	if( (r = can_api_transmit(canp, &tx_msg, 100, chp)) != MSG_OK ) {
		return(false);
	}
	if( ! can_bootloader_wait_for_ack(canp, ORESAT_BOOTLOADER_CAN_COMMAND_GO, chp) ) {
		return(false);
	}

	return(true);
}


bool can_bootloader_test(CANDriver *canp, const uint32_t low_cpu_id, BaseSequentialStream *chp) {
	if( ! can_bootloader_initiate(canp, 4000, low_cpu_id, chp) ) {
		chprintf(chp, "Failed to put node into bootloader mode...\r\n");
		return(false);
	}
	//bool can_bootloader_read_data(CANDriver *canp, const uint32_t memory_address, const uint32_t num_bytes_to_read, uint8_t *dest_buffer, const uint32_t dest_buffer_length, BaseSequentialStream *chp) {
	static uint8_t temp_buffer[128];
	if( ! can_bootloader_read_data(canp, 0x8000000, 4, temp_buffer, sizeof(temp_buffer), chp) ) {
		return(false);
	}

	if( ! can_bootloader_erase_page(canp, 20, chp) ) {
		return(false);
	}

	temp_buffer[0] = 0x0D;
	temp_buffer[1] = 0x0E;
	temp_buffer[2] = 0x0A;
	temp_buffer[3] = 0x0D;
	temp_buffer[4] = 0x0B;
	temp_buffer[5] = 0x0E;
	temp_buffer[6] = 0x0E;
	temp_buffer[7] = 0x0F;
	if( ! can_bootloader_write_memory(canp, 0x800A000, temp_buffer, 8, chp) ) {
		return(false);
	}

	if( ! can_bootloader_read_data(canp, 0x800A000, 16, temp_buffer, sizeof(temp_buffer), chp) ) {
		return(false);
	}

	if( ! can_bootloader_go(canp, 0x800A000, chp) ) {
		return(false);
	}

	return(true);
}

bool can_bootloader_check_communication(CANDriver *canp, BaseSequentialStream *chp) {
	can_api_purge_rx_buffer(canp, chp);

	uint8_t trash_buffer[8];

	if( ! can_bootloader_read_data(canp, ORESAT_F0_FIRMWARE_CRC_ADDRESS, sizeof(trash_buffer), trash_buffer, sizeof(trash_buffer), chp)) {
		return(false);
	}

	return(true);
}

/**
 * Verify and re-initiate the connection to the M0 cpu if it powered off mid process
 */
bool can_bootloader_verify_retry_connection(CANDriver *canp, const uint32_t low_cpu_id, BaseSequentialStream *chp) {
	for(int i = 0; i < 5; i++ ) {
		if( can_bootloader_check_communication(canp, chp) ) {
			return(true);
		} else {
			if( can_bootloader_initiate(canp, 15000, low_cpu_id, chp) ) {
				return(true);
			}
		}
	}

	return(false);
}

/**
 * Wrapped to deal with solar cards that power on and off at variable times.
 */
bool can_bootloader_erase_page_reliable(CANDriver *canp, const uint32_t page_number, const uint32_t low_cpu_id, BaseSequentialStream *chp) {
	for (int i = 0; i < DEFAULT_RETRY_LIMIT; i++) {
		if(can_bootloader_erase_page(canp, page_number, chp)) {
			return (true);
		}
		if( ! can_bootloader_verify_retry_connection(canp, low_cpu_id, chp) ) {
			return(false);
		}
	}

	return (false);
}

/**
 * Wrapped to deal with solar cards that power on and off at variable times.
 */
bool can_bootloader_write_memory_reliable(CANDriver *canp, const uint32_t memory_address, const uint8_t *src_buffer, const uint32_t num_bytes, const uint32_t low_cpu_id, BaseSequentialStream *chp) {
	for (int i = 0; i < DEFAULT_RETRY_LIMIT; i++) {
		if (can_bootloader_write_memory(canp, memory_address, src_buffer, num_bytes, chp)) {
			return (true);
		}
		if( ! can_bootloader_verify_retry_connection(canp, low_cpu_id, chp) ) {
			return(false);
		}
	}

	return (false);
}

/**
 * Wrapped to deal with solar cards that power on and off at variable times.
 */
bool can_bootloader_read_data_reliable(CANDriver *canp, const uint32_t memory_address, const uint32_t num_bytes_to_read, uint8_t *dest_buffer, const uint32_t dest_buffer_length, const uint32_t low_cpu_id, BaseSequentialStream *chp) {
	for (int i = 0; i < DEFAULT_RETRY_LIMIT; i++) {
		if(can_bootloader_read_data(canp, memory_address, num_bytes_to_read, dest_buffer, dest_buffer_length, chp)) {
			return(true);
		}
		if( ! can_bootloader_verify_retry_connection(canp, low_cpu_id, chp) ) {
			return(false);
		}
	}

	return(false);
}


bool can_bootloader_verify_memory_reliable(CANDriver *canp, const uint32_t base_memory_address, const uint8_t *src_buffer, const uint32_t num_bytes, const uint32_t low_cpu_id, BaseSequentialStream *chp)
{
	chprintf(chp, "Verifying %u bytes at address 0x%X\r\n", num_bytes, base_memory_address);

	uint8_t temp_buff[16];

	uint32_t current_offset = 0;
	//uint32_t current_offset2 = 0;
	while(current_offset < num_bytes) {
		if( ! can_bootloader_read_data_reliable(canp, base_memory_address + current_offset, sizeof(temp_buff), temp_buff, sizeof(temp_buff), low_cpu_id, chp)) {
			return(false);
		}
#if 0
		for(uint32_t i = 0; i < sizeof(temp_buff) && current_offset2 < num_bytes; i++ ) {
			chprintf(chp, "0x%X    0x%X\r\n", src_buffer[current_offset2], temp_buff[i]);
			current_offset2++;
		}
#endif

		for( uint32_t i = 0; i < sizeof(temp_buff) && current_offset < num_bytes; i++ ) {
			if( src_buffer[current_offset] != temp_buff[i] ) {
				chprintf(chp, "ERROR: Failed verification! 0x%X != 0x%X, %u, %u\r\n", src_buffer[current_offset], temp_buff[i], current_offset, i);
				return(false);
			}

			current_offset++;
		}
	}

	return(true);
}


#define M0_FIRMWARE_UPDATE_WRITE_CHUNK_SIZE     64
uint8_t m0_firmware_temp_buffer[M0_FIRMWARE_UPDATE_WRITE_CHUNK_SIZE];


bool oresat_firmware_update_m0(CANDriver *canp, const uint32_t base_address, const uint32_t low_cpu_id, const uint32_t total_firmware_length_bytes, firmware_read_function_ptr_t read_function_pointer, BaseSequentialStream *chp) {
	if( ! can_bootloader_initiate(canp, 5000, low_cpu_id, chp) ) {
		chprintf(chp, "Failed to put node into bootloader mode...\r\n");
		return(false);
	}


	uint32_t temp_address = base_address;
	while(temp_address <= (base_address + total_firmware_length_bytes) ) {
		const uint32_t page_number = (temp_address - ORESAT_F0_FLASH_START_ADDRESS) / ORESAT_F0_FLASH_PAGE_SIZE;

		if( ! can_bootloader_erase_page_reliable(canp, page_number, low_cpu_id, chp) ) {
			return(false);
		}

		temp_address += ORESAT_F0_FLASH_PAGE_SIZE;
	}


	uint32_t current_file_offset = 0;

	while (current_file_offset < total_firmware_length_bytes) {
		uint32_t bytes_to_write_to_flash = M0_FIRMWARE_UPDATE_WRITE_CHUNK_SIZE;
		if( (current_file_offset + bytes_to_write_to_flash) > total_firmware_length_bytes ) {
			bytes_to_write_to_flash = total_firmware_length_bytes - current_file_offset;
			if( bytes_to_write_to_flash > M0_FIRMWARE_UPDATE_WRITE_CHUNK_SIZE ) {
				bytes_to_write_to_flash = M0_FIRMWARE_UPDATE_WRITE_CHUNK_SIZE;
			}
		}

		if( ! read_function_pointer(current_file_offset, m0_firmware_temp_buffer, bytes_to_write_to_flash) ) {
			return(false);
		}

		if( ! can_bootloader_write_memory_reliable(canp, (base_address + current_file_offset), m0_firmware_temp_buffer, bytes_to_write_to_flash, low_cpu_id, chp) ) {
			return(false);
		}

		current_file_offset += bytes_to_write_to_flash;
	}


	current_file_offset = 0;

	while (current_file_offset < total_firmware_length_bytes) {
		uint32_t bytes_to_write_to_flash = M0_FIRMWARE_UPDATE_WRITE_CHUNK_SIZE;
		if( (current_file_offset + bytes_to_write_to_flash) > total_firmware_length_bytes ) {
			bytes_to_write_to_flash = total_firmware_length_bytes - current_file_offset;
			if( bytes_to_write_to_flash > M0_FIRMWARE_UPDATE_WRITE_CHUNK_SIZE ) {
				bytes_to_write_to_flash = M0_FIRMWARE_UPDATE_WRITE_CHUNK_SIZE;
			}
		}

		if( ! read_function_pointer(current_file_offset, m0_firmware_temp_buffer, bytes_to_write_to_flash) ) {
			return(false);
		}

		if( ! can_bootloader_verify_memory_reliable(canp, (base_address + current_file_offset), m0_firmware_temp_buffer, bytes_to_write_to_flash, low_cpu_id, chp) ) {
			return(false);
		}

		current_file_offset += bytes_to_write_to_flash;
	}

	can_bootloader_go(canp, ORESAT_F0_FIRMWARE_CODE_ADDRESS, chp);

	chprintf(chp, "\r\nSuccessfully wrote and verified firmware image to remote MCU device...\r\n\r\n");

	return(true);
}


const char* oresat_bootloader_can_command_t_to_str(const oresat_bootloader_can_command_t v) {
	switch (v) {
		case ORESAT_BOOTLOADER_CAN_COMMAND_GET:
			return ("ORESAT_BOOTLOADER_CAN_COMMAND_GET");
		case ORESAT_BOOTLOADER_CAN_COMMAND_READ_MEMORY:
			return ("ORESAT_BOOTLOADER_CAN_COMMAND_READ_MEMORY");
		case ORESAT_BOOTLOADER_CAN_COMMAND_GO:
			return ("ORESAT_BOOTLOADER_CAN_COMMAND_GO");
		case ORESAT_BOOTLOADER_CAN_COMMAND_WRITE_MEMORY:
			return ("ORESAT_BOOTLOADER_CAN_COMMAND_WRITE_MEMORY");
		case ORESAT_BOOTLOADER_CAN_COMMAND_ERASE:
			return ("ORESAT_BOOTLOADER_CAN_COMMAND_ERASE");
	}

	if( v == STM32_BOOTLOADER_CAN_ACK ) {
		return("ACK");
	}
	if( v == STM32_BOOTLOADER_CAN_NACK ) {
		return("NACK");
	}

	return ("???");
}


