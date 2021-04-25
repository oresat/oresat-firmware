#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "test_bootloader.h"
#include "can_bootloader.h"
#include "chprintf.h"
#include "oresat_f0.h"
#include "fs.h"

#if 0
#include "app_solar.crc32.bin.h"
#else
uint32_t build_app_solar_crc32_bin_len = 0;
unsigned char *build_app_solar_crc32_bin = NULL;
#endif

#if 0
#include "app_imu.crc32.bin.h"
#else
uint32_t build_app_imu_crc32_bin_len = 0;
unsigned char *build_app_imu_crc32_bin = NULL;
#endif

#if 0
#include "app_battery.crc32.bin.h"
#else
uint32_t build_app_battery_crc32_bin_len = 0;
unsigned char *build_app_battery_crc32_bin = NULL;
#endif


//const uint32_t low_cpuid_of_protoboard = 0x1D000800;
//const uint32_t node_of_protoboard = 0x11;

//const uint32_t unique_id_of_solarcard = 0x1800500;

BaseSequentialStream *bootloader_chp_global = NULL;

CANDriver *canp = &CAND1;

// xxd -i app_solar.crc32.bin > app_solar.crc32.bin.h

#if 0
/*
 * This is an example of reading source firmware image data from an in-memory buffer, but this function could be implemented
 * to open a file from a file system, seek to an offset in the file, read some data into dest_buffer and close the file.
 */
uint32_t firmware_blob_read_function(const uint32_t offset, uint8_t *dest_buffer, const uint32_t number_of_bytes, void *arg0) {
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
  can_api_init_can_bootloader_config_t(&can_bl_config, canp, chp, card_unique_id, false, NULL);

  bool r = oresat_firmware_update_m0(&can_bl_config, ORESAT_F0_FIRMWARE_CRC_ADDRESS, app_solar_crc32_bin_len, firmware_blob_read_function);

  print_can_bootloader_config_t(&can_bl_config);
  chprintf(chp, "Firmware update success flag: %u\r\n", r);
}
#endif

lfs_soff_t get_lfs_filesize(char *lfs_filepath) {
	lfs_file_t *lsf_file_handle = file_open(&FSD1, lfs_filepath, LFS_O_RDONLY);
	if (lsf_file_handle == NULL) {
		return (-1);
	}
	const lfs_soff_t lfs_file_length = file_size(&FSD1, lsf_file_handle);

	file_close(&FSD1, lsf_file_handle);
	return (lfs_file_length);
}


uint32_t firmware_blob_read_function_from_lfs(const uint32_t offset, uint8_t *dest_buffer, const uint32_t number_of_bytes, void *arg0) {
	uint32_t return_value = 0;

	char *lsf_filepath = (char*) arg0;

	//chprintf(bootloader_chp_global, "firmware_blob_read_function_from_lfs(): Opening %s\r\n", lsf_filepath);

	lfs_file_t *lsf_file_handle = file_open(&FSD1, lsf_filepath, LFS_O_RDONLY);
	if( lsf_file_handle == NULL ) {
		//chprintf(bootloader_chp_global, "firmware_blob_read_function_from_lfs(): Error in file_open: %d\r\n", FSD1.err);
		return(0);
	}

	const lfs_soff_t lfs_file_length = file_size(&FSD1, lsf_file_handle);
	if( lfs_file_length >= 0 && lfs_file_length > ((int32_t) offset) ) {
		const lfs_soff_t of = file_seek(&FSD1, lsf_file_handle, offset, 0);
		if( of < 0 || of != ((int32_t) offset) ) {
			//FIXME handle error
		} else {
			int ret = file_read(&FSD1, lsf_file_handle, dest_buffer, number_of_bytes);
			if( ret < 0 ) {
				//chprintf(bootloader_chp_global, "Failed file_read(), %d\r\n", ret);
				//FIXME error
			} else {
				return_value = ret;
			}
		}

		//chprintf(bootloader_chp_global, "Read %u bytes from offset %u from file %s\r\n", return_value, of, lsf_filepath);
	} else {
		//chprintf(bootloader_chp_global, "firmware_blob_read_function_from_lfs(): Error lfs_file_length = %d\r\n", lfs_file_length);
	}

	file_close(&FSD1, lsf_file_handle);


	return(return_value);
}


/**
 * This function will update a remote OreSAT node that has gone into bootloader mode with the contents of a file specified
 * by lfs_filepath
 *
 * @param  card_unique_id The OreSAT Node ID or the unique CPU ID low 32 bits, depending on if the target node has it's OPT bytes programmed
 * @param *lfs_filepath The path on the LFS file system containing the firmware image contnts.
 *
 * @return true on success, false otherwise
 */
bool can_fw_update_from_lfs_file(BaseSequentialStream *chp, const uint32_t card_unique_id, char *lfs_filepath) {
  can_bootloader_config_t can_bl_config;
  can_api_init_can_bootloader_config_t(&can_bl_config, canp, chp, card_unique_id, false, lfs_filepath);

  const lfs_soff_t lfs_file_length = get_lfs_filesize(lfs_filepath);

  chprintf(chp, "File Length: %u\r\n", lfs_file_length);

  bool r = oresat_firmware_update_m0(&can_bl_config, ORESAT_F0_FIRMWARE_CRC_ADDRESS, lfs_file_length, firmware_blob_read_function_from_lfs);

  print_can_bootloader_config_t(chp, &can_bl_config);
  chprintf(chp, "Firmware update success flag: %u\r\n", r);

  return(r);
}

bool can_write_node_id(BaseSequentialStream *chp, const uint32_t card_unique_id, const uint8_t data_0_value, const uint8_t data_1_value) {
  can_bootloader_config_t can_bl_config;
  can_api_init_can_bootloader_config_t(&can_bl_config, canp, chp, card_unique_id, false, NULL);

  chprintf(chp, "Trying to put node 0x%X into bootloader mode...\r\n", card_unique_id);
  chThdSleepMilliseconds(10);

  // CAN FIFO 1 on the C3 Node will almost certainly have some cruft bootloader related can messages in it that need to be discarded
  can_api_purge_rx_buffer(&can_bl_config);

  if( ! can_bootloader_initiate(&can_bl_config, 5000) ) {
	  chprintf(chp, "Failed to put node into bootloader mode...\r\n");
	  return(false);
  } else {
	chprintf(chp, "Successfully put node into bootloader mode...\r\n");
  }

  bool ret = can_bootloader_set_opt_data(&can_bl_config, data_0_value, data_1_value);

  return(ret);
}

typedef struct {
	char *filename;
	uint32_t length;
	uint8_t *flash_buffer_ptr;
	uint32_t target_unique_id;
} app_spec_t;

/*===========================================================================*/
/*                                                                       */
/*===========================================================================*/

void write_blob_to_lfs(BaseSequentialStream *chp, char *filename, void *src_buffer, const uint32_t firmware_img_length) {
	//Write data from the firmware blob to the lfs file system
	lfs_file_t *file;
	file = file_open(&FSD1, filename, LFS_O_RDWR | LFS_O_CREAT | LFS_O_TRUNC);
	if (file == NULL) {
		chprintf(chp, "Error in file_open: %d\r\n", FSD1.err);
		return;
	}

	int ret = file_write(&FSD1, file, src_buffer, firmware_img_length);
	if( ret < 0 ) {
		chprintf(chp, "Error in file_write: %d\r\n", ret);
	}

	ret = file_close(&FSD1, file);
	if (ret < 0) {
		chprintf(chp, "Error in file_close: %d\r\n", ret);
		return;
	}

	chprintf(chp, "Successfully wrote %s to LFS file system\r\n", filename);
}

#define NUM_TEST_APPS    6
void cmd_bootloader(BaseSequentialStream *chp, int argc, char *argv[])
{
	bootloader_chp_global = chp;

    if (argc < 1) {
        goto bootloader_usage;
    }

    app_spec_t app_list[NUM_TEST_APPS] = {
    		{"app_imu.crc32.bin", build_app_imu_crc32_bin_len, build_app_imu_crc32_bin, 0x38},
			{"app_battery.crc32.bin", build_app_battery_crc32_bin_len, build_app_battery_crc32_bin, 0x04},
			{"app_solar.crc32.bin", build_app_solar_crc32_bin_len, build_app_solar_crc32_bin, 0x0C},
			{"app_solar.crc32.bin", build_app_solar_crc32_bin_len, build_app_solar_crc32_bin, 0x10},
			{"app_solar.crc32.bin", build_app_solar_crc32_bin_len, build_app_solar_crc32_bin, 0x14},
			{"app_solar.crc32.bin", build_app_solar_crc32_bin_len, build_app_solar_crc32_bin, 0x18},
    };
#if 0
    char filename[] = "app_imu.crc32.bin";
    uint32_t firmware_img_length = build_app_imu_crc32_bin_len;
    uint8_t *firmware_buffer_memory_pointer = build_app_imu_crc32_bin;
    const uint32_t target_unique_id = 0x38;
#else
#endif


    for(int i = 0; i < argc; i++ ) {
    	chprintf(chp, "argv[%u] = %s\r\n", i, argv[i]);
    }

    if (!strcmp(argv[0], "flash_imu") ) {
		can_fw_update_from_lfs_file(chp, app_list[0].target_unique_id, app_list[0].filename);
    } else if (!strcmp(argv[0], "flash_battery") ) {
    	can_fw_update_from_lfs_file(chp, app_list[1].target_unique_id, app_list[1].filename);
    } else if (!strcmp(argv[0], "flash_solar_0C") ) {
		can_fw_update_from_lfs_file(chp, app_list[2].target_unique_id, app_list[2].filename);
    } else if (!strcmp(argv[0], "flash_solar_10") ) {
    	can_fw_update_from_lfs_file(chp, app_list[3].target_unique_id, app_list[3].filename);
    } else if (!strcmp(argv[0], "flash_solar_14") ) {
    	can_fw_update_from_lfs_file(chp, app_list[4].target_unique_id, app_list[4].filename);
    } else if (!strcmp(argv[0], "flash_solar_18") ) {
    	can_fw_update_from_lfs_file(chp, app_list[5].target_unique_id, app_list[5].filename);

    } else if (!strcmp(argv[0], "wfw") && argc >= 1 ) {
    	for(int idx = 0; idx < 3; idx++) {
    		if( app_list[idx].flash_buffer_ptr != NULL ) {
    			write_blob_to_lfs(chp, app_list[idx].filename, app_list[idx].flash_buffer_ptr, app_list[idx].length);
    		}
    	}

    } else if (!strcmp(argv[0], "opt") && argc >= 4 ) {
    	//Example of programming node ID 22 (onto node id 22)   bootloader opt 22 FF 00000022

    	uint8_t data_0 = 0;
    	sscanf(argv[1], "%2hhx", &data_0);

    	uint8_t data_1 = 0;
    	sscanf(argv[2], "%2hhx", &data_1);

    	uint8_t cpu_id_0 = 0;
    	uint8_t cpu_id_1 = 0;
    	uint8_t cpu_id_2 = 0;
    	uint8_t cpu_id_3 = 0;
    	sscanf(argv[3], "%2hhx%2hhx%2hhx%2hhx", &cpu_id_0, &cpu_id_1, &cpu_id_2, &cpu_id_3);

    	uint32_t cpu_id = (cpu_id_0 << 24) |(cpu_id_1 << 16) | (cpu_id_2 << 8) |  cpu_id_3;
    	chprintf(chp, "Looking for CPU ID 0x%X\r\n", cpu_id);

    	if( can_write_node_id(chp, cpu_id, data_0, data_1) ) {
    		chprintf(chp, "Successfully wrote data 0 and data 1 OPT bytes...\r\n");
    	} else {
    		chprintf(chp, "Failed to write data 0 and data 1 OPT bytes...\r\n");
    	}



//    } else if (!strcmp(argv[0], "w") ) {
//    	//test_can_fw_update(chp, unique_id_of_solarcard);
//    	can_fw_update_from_lfs_file(chp, target_unique_id, filename);

    } else {
        goto bootloader_usage;
    }

    return;

bootloader_usage:
    chprintf(chp, "Usage: bootloader <cmd>\r\n"
                  "    wfw: Writes in memory file to LFS file system\r\n"
                  "    opt: <data 0> <data 1> <######## hex cpu unique ID or node ID>\r\n"
                  "    w:   Write firmware to remote node\r\n"
                  "\r\n");
    return;
}


