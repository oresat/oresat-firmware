#include <stdlib.h>
#include <string.h>
#include "test_bootloader.h"
#include "can_bootloader.h"
#include "chprintf.h"
#include "oresat_f0.h"

#include "app_solar.crc32.bin.h"

//FIXME duplicate define from oresat_f0.h
//#define ORESAT_F0_FIRMWARE_CRC_ADDRESS                0x0800A000
//const uint32_t low_cpuid_of_protoboard = 0x1D000800;

const uint32_t unique_id_of_solarcard = 0x1800500;

CANDriver *canp = &CAND1;

volatile uint32_t g_can_rx_count = 0;

//#define DEBUG_SD    (BaseSequentialStream *) &SD2

// xxd -i app_protocard2.crc32.bin > ../../../f4/app_f407_discovery/firmware_blob.h
/*
 * This is an example of reading source firmware image data from an in-memory buffer, but this function could be implemented
 * to open a file from a file system, seek to an offset in the file, read some data into dest_buffer and close the file.
 */
uint32_t firmware_blob_read_function(const uint32_t offset, uint8_t *dest_buffer, const uint32_t number_of_bytes) {
	uint32_t dest_index = 0;

	for(; dest_index < number_of_bytes; dest_index++ ) {
		if( (offset + dest_index) < app_solar_crc32_bin_len ) {
			dest_buffer[dest_index] = app_solar_crc32_bin[offset + dest_index];
		} else {
			break;
		}
	}

	return(dest_index);
}

/**
 * @param  card_unique_id The OreSAT Node ID or the unique CPU ID low 32 bits, depending on if the target node has it's OPT bytes programmed
 */
void test_can_fw_update(BaseSequentialStream *chp, const uint32_t card_unique_id) {
  can_bootloader_config_t can_bl_config;
  can_api_init_can_bootloader_config_t(&can_bl_config, canp, chp, card_unique_id, false);

  bool r = oresat_firmware_update_m0(&can_bl_config, ORESAT_F0_FIRMWARE_CRC_ADDRESS, app_solar_crc32_bin_len, firmware_blob_read_function);

  print_can_bootloader_config_t(&can_bl_config);
  chprintf(chp, "Firmware update success flag: %u\r\n", r);
}



/*===========================================================================*/
/*                                                                       */
/*===========================================================================*/
void cmd_bootloader(BaseSequentialStream *chp, int argc, char *argv[])
{
    if (argc < 1) {
        goto bootloader_usage;
    }

    for(int i = 0; i < argc; i++ ) {
    	chprintf(chp, "argv[%u] = %s\r\n", i, argv[i]);
    }

    if (!strcmp(argv[0], "r") ) {
#if 0
    	//test_can_fw_update(chp);
		can_bootloader_config_t can_bl_config;
		can_api_init_can_bootloader_config_t(&can_bl_config, canp, chp, unique_id_of_solarcard, false);
		CANRxFrame msg;
		for(;;) {
			chprintf(chp, "Attempting to RX can frame (g_can_rx_count = %u)...\r\n", g_can_rx_count);
			msg_t r = can_api_receive(&can_bl_config, &msg, 500);
			if( r == MSG_OK ) {
				can_api_print_rx_frame(chp, &msg, "", "");
			} else {
				chprintf(chp, "No CAN frame RXed\r\n");
			}
		}
#endif

    } else if (!strcmp(argv[0], "w") ) {
    	test_can_fw_update(chp, unique_id_of_solarcard);

    } else {
        goto bootloader_usage;
    }

    return;

bootloader_usage:
    chprintf(chp, "Usage: bootloader <cmd>\r\n"
                  "    cmd1: <options>\r\n"
                  "        Does blah\r\n"
                  "    cmd2: <options>\r\n"
                  "        Does other blah\r\n"
                  "\r\n");
    return;
}


