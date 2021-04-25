#include <stdlib.h>
#include <string.h>
#include "test_crc.h"
#include "crc.h"
#include "301/crc16-ccitt.h"
#include "fs.h"
#include "chprintf.h"

/*===========================================================================*/
/* CRC Subsystem                                                             */
/*===========================================================================*/
void cmd_crc(BaseSequentialStream *chp, int argc, char *argv[])
{
    if (argc < 1) {
        goto crc_usage;
    }

    if (!strcmp(argv[0], "check")) {
        uint8_t test[] = {
            0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
            0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
            0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
            0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
        };
        uint32_t hw_32 = 0xFFFFFFFFU, sw_32 = 0xFFFFFFFFU;
        uint32_t lfscrc= 0xFFFFFFFFU;
        uint16_t hw_16 = 0xFFFFU;
        uint16_t sw_16 = 0xFFFFU;
        uint16_t ccitt = 0xFFFFU;

        hw_32 = crc32_hw((uint32_t*)test, sizeof(test)/sizeof(uint32_t), hw_32);
        sw_32 = crc32_sw(test, sizeof(test), sw_32);
#if (STM32_CRC_PROGRAMMABLE == TRUE)
        hw_16 = crc16_ccitt_hw((uint16_t*)test, sizeof(test)/sizeof(uint16_t), hw_16);
#endif
        sw_16 = crc16_ccitt_sw(test, sizeof(test), sw_16);
        ccitt = crc16_ccitt(test, sizeof(test), ccitt);
        lfscrc = lfs_crc(lfscrc, test, sizeof(test));
#if (STM32_CRC_PROGRAMMABLE == FALSE)
        chprintf(chp, "CRC16_HW NOT SUPPORTED\r\n");
#endif
        chprintf(chp, "CRC32_HW:    %08X\r\n"
                      "CRC32_SW:    %08X\r\n"
                      "LFS_CRC:     %08X\r\n"
                      "CRC16_HW:    %04X\r\n"
                      "CRC16_SW:    %04X\r\n"
                      "CCITT:       %04X\r\n\r\n",
                      ~hw_32, ~sw_32, ~lfscrc, hw_16, sw_16, ccitt);

        hw_32 = sw_32 = lfscrc = 0xFFFFFFFFU;
        hw_16 = sw_16 = ccitt = 0xFFFFU;
        for (size_t i = 0; i < sizeof(test); i+=4) {
            hw_32 = crc32_hw((uint32_t*)(&test[i]), 1, hw_32);
        }
        for (size_t i = 0; i < sizeof(test); i+=4) {
            sw_32 = crc32_sw(&test[i], sizeof(uint32_t), sw_32);
        }
        for (size_t i = 0; i < sizeof(test); i+=4) {
            lfscrc = lfs_crc(lfscrc, &test[i], sizeof(uint32_t));
        }
#if (STM32_CRC_PROGRAMMABLE == TRUE)
        for (size_t i = 0; i < sizeof(test); i+=4) {
            hw_16 = crc16_ccitt_hw((uint16_t*)(&test[i]), sizeof(uint32_t)/sizeof(uint16_t), hw_16);
        }
#endif
        for (size_t i = 0; i < sizeof(test); i+=4) {
            sw_16 = crc16_ccitt_sw(&test[i], sizeof(uint32_t), sw_16);
        }
        for (size_t i = 0; i < sizeof(test); i+=4) {
            ccitt = crc16_ccitt(&test[i], sizeof(uint32_t), ccitt);
        }
        chprintf(chp, "CRC32_HW:    %08X\r\n"
                      "CRC32_SW:    %08X\r\n"
                      "LFS_CRC:     %08X\r\n"
                      "CRC16_HW:    %04X\r\n"
                      "CRC16_SW:    %04X\r\n"
                      "CCITT:       %04X\r\n\r\n",
                      ~hw_32, ~sw_32, ~lfscrc, hw_16, sw_16, ccitt);
    } else {
        goto crc_usage;
    }

    return;

crc_usage:
    chprintf(chp,  "Usage: crc <command>\r\n"
                   "    check:\r\n"
                   "        Check consistency of CRC implementations\r\n"
                   "\r\n");
    return;
}
