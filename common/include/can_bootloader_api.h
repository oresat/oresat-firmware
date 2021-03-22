#ifndef COMMON_INCLUDE_CAN_BOOTLOADER_API_H_
#define COMMON_INCLUDE_CAN_BOOTLOADER_API_H_
#include "ch.h"
#include "hal.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ORESAT_F0_FLASH_PAGE_SIZE                     2048

#define BOOTLOADER_EXPECTED_FIRST_FRAME_ID           0x79
#define STM32_BOOTLOADER_SYNCHRONIZATION_SID         0x79
#define CAN_ANNOUNCE_MAGIC_NUMBER                    0x04030201
#define STM32_BOOTLOADER_CAN_ACK                     0x79
#define STM32_BOOTLOADER_CAN_NACK                    0x1F
#define CAN_BOOTLOADER_WRITE_MEMORY_RESPONSE_SID     0x04


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


typedef uint32_t (*firmware_read_function_ptr_t)(const uint32_t offset, uint8_t *dest_buffer, const uint32_t number_of_bytes);

typedef struct {
	CANDriver *canp;
	BaseSequentialStream *chp;//debug stream
	uint32_t low_cpu_id;
	bool stm32_bootloader_mode;

	uint32_t read_fail_count;
	uint32_t write_fail_count;
	uint32_t erase_fail_count;
	uint32_t verify_fail_count;
	uint32_t ack_count;
	uint32_t nack_count;
	uint32_t unknown_count;
	uint32_t can_tx_fail_count;
	uint32_t initiate_connection_count;
	uint32_t connection_verify_fail;
} can_bootloader_config_t;

bool can_api_init_can_bootloader_config_t(can_bootloader_config_t *can_bl_config, CANDriver *canp, BaseSequentialStream *chp, const uint32_t low_cpu_id, const bool stm32_bootloader_mode);

bool can_bootloader_initiate(can_bootloader_config_t *can_bl_config, const uint32_t timeout_ms);
void print_can_bootloader_config_t(can_bootloader_config_t *can_bl_config);
bool oresat_firmware_update_m0(can_bootloader_config_t *can_bl_config, const uint32_t base_address, const uint32_t total_firmware_length_bytes, firmware_read_function_ptr_t read_function_pointer);

const char* oresat_bootloader_can_command_t_to_str(const oresat_bootloader_can_command_t v);

void can_api_print_rx_frame(BaseSequentialStream *chp, CANRxFrame *msg, const char *pre_msg, const char *post_msg);
void can_api_print_tx_frame(BaseSequentialStream *chp, CANTxFrame *msg, const char *pre_msg, const char *post_msg);
msg_t can_api_receive(can_bootloader_config_t *can_bl_config, CANRxFrame *msg, const uint32_t timeout_ms);

bool can_bootloader_test(can_bootloader_config_t *can_bl_config);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif /* COMMON_INCLUDE_CAN_BOOTLOADER_API_H_ */
