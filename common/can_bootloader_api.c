#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "can_bootloader_api.h"
#include "string.h"


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


msg_t can_api_transmit(CANDriver *canp, CANTxFrame *msg, const uint32_t timeout_ms, BaseSequentialStream *chp) {
	const msg_t r = canTransmit(canp, CAN_ANY_MAILBOX, msg, TIME_MS2I(timeout_ms));
	if( r == MSG_OK ) {
		can_api_print_tx_frame(chp, msg, "", " - SUCCESS");
	} else {
		can_api_print_tx_frame(chp, msg, "", " - FAIL");
	}
	return(r);
}


bool can_bootloader_initiate(CANDriver *canp, BaseSequentialStream *chp) {
	CANRxFrame msg;
	memset(&msg, 0, sizeof(msg));
	msg_t r = can_api_receive(canp, &msg, 3000, chp);
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


bool can_bootloader_test(CANDriver *canp, BaseSequentialStream *chp) {
	if( ! can_bootloader_initiate(canp, chp) ) {
		chprintf(chp, "Failed to put node into bootloader mode...\r\n");
		return(false);
	}




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


