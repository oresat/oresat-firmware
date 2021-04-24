#ifndef COMMON_INCLUDE_ORESAT_F0_H_
#define COMMON_INCLUDE_ORESAT_F0_H_

/* TODO: It'd be nice to derive these values from the linker script as the authoratative source */
#define ORESAT_F0_FLASH_START_ADDRESS                 0x08000000

#define ORESAT_F0_FIRMWARE_CRC_ADDRESS                0x0800A000
#define ORESAT_F0_FIRMWARE_LENGTH_ADDRESS             (ORESAT_F0_FIRMWARE_CRC_ADDRESS + 0x4)
#define ORESAT_F0_FIRMWARE_VERSION_ADDRESS            (ORESAT_F0_FIRMWARE_CRC_ADDRESS + 0x8)
#define ORESAT_F0_FIRMWARE_CODE_ADDRESS               (ORESAT_F0_FIRMWARE_CRC_ADDRESS + 0x400)
#define ORESAT_F0_FIRMWARE_CODE_END_ADDRESS           0x0803C000

#define ORESAT_F0_FIRMWARE_MAXIMUM_LENGTH             (ORESAT_F0_FIRMWARE_CODE_END_ADDRESS - ORESAT_F0_FIRMWARE_CRC_ADDRESS)


#ifdef __cplusplus
extern "C" {
#endif

extern int __flash0_base__;
extern size_t __flash0_size__;
extern int __flash0_end__;
extern int __flash1_base__;
extern size_t __flash1_size__;
extern int __flash1_end__;

#ifdef __cplusplus
}
#endif /*__cplusplus*/



#endif /* COMMON_INCLUDE_ORESAT_F0_H_ */
