#ifndef SRC_F0_APP_BOOTLOADER_SOURCE_CRC32_H_
#define SRC_F0_APP_BOOTLOADER_SOURCE_CRC32_H_

#include <stdint.h>

uint32_t crc32( uint32_t crc, const uint8_t * data_ptr, uint32_t size );
uint32_t crc32_update( uint32_t crc, uint8_t data );


#endif /* SRC_F0_APP_BOOTLOADER_SOURCE_CRC32_H_ */
