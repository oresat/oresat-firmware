#ifndef COMMON_INCLUDE_CAN_BOOTLOADER_API_H_
#define COMMON_INCLUDE_CAN_BOOTLOADER_API_H_

#ifdef __cplusplus
extern "C" {
#endif


#define BOOTLOADER_EXPECTED_FIRST_FRAME_ID           0x79
#define CAN_ANNOUNCE_MAGIC_NUMBER                    0x04030201
#define STM32_BOOTLOADER_CAN_ACK                     0x79
#define STM32_BOOTLOADER_CAN_NACK                    0x1F


typedef enum {
	ORESAT_BOOTLOADER_CAN_COMMAND_GET = 0x00,
	//ORESAT_BOOTLOADER_CAN_COMMAND_GET_VERSION = 0x01,
	//ORESAT_BOOTLOADER_CAN_COMMAND_GET_ID = 0x02,
	//ORESAT_BOOTLOADER_CAN_COMMAND_SPEED = 0x03,
	ORESAT_BOOTLOADER_CAN_COMMAND_READ_MEMORY = 0x11,
	ORESAT_BOOTLOADER_CAN_COMMAND_GO = 0x21,
	ORESAT_BOOTLOADER_CAN_COMMAND_WRITE_MEMORY = 0x31,
	ORESAT_BOOTLOADER_CAN_COMMAND_ERASE = 0x43,
	//ORESAT_BOOTLOADER_CAN_COMMAND_WRITE_PROTECT = 0x63,
	//ORESAT_BOOTLOADER_CAN_COMMAND_WRITE_UNPROTECT = 0x73,
	//ORESAT_BOOTLOADER_CAN_COMMAND_READOUT_PROTECT = 0x82,
	//ORESAT_BOOTLOADER_CAN_COMMAND_READOUT_UNPROTECT = 0x92
} oresat_bootloader_can_command_t;


const char* oresat_bootloader_can_command_t_to_str(const oresat_bootloader_can_command_t v);
void can_api_print_rx_frame(BaseSequentialStream *chp, CANRxFrame *msg, const char *pre_msg, const char *post_msg);
void can_api_print_tx_frame(BaseSequentialStream *chp, CANTxFrame *msg, const char *pre_msg, const char *post_msg);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif /* COMMON_INCLUDE_CAN_BOOTLOADER_API_H_ */
