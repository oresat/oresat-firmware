#ifndef _CRC_H_
#define _CRC_H_

#include <stddef.h>
#include <stdint.h>

#if !defined(USE_CRC_HW)
#define USE_CRC_HW                  FALSE
#endif

#ifdef __cplusplus
extern "C" {
#endif

uint32_t crc32_hw(const uint32_t block[], size_t len, uint32_t crc);
uint32_t crc32_sw(const uint8_t block[], size_t len, uint32_t crc);
uint32_t crc32(const uint8_t block[], size_t len, uint32_t crc);
uint16_t crc16_ccitt_hw(const uint16_t block[], size_t len, uint16_t crc);
uint16_t crc16_ccitt_sw(const uint8_t block[], size_t len, uint16_t crc);
uint16_t crc16_ccitt_new(const uint8_t block[], size_t len, uint16_t crc);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif /*_CRC_H_*/
