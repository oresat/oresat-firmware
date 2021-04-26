#include <stdlib.h>
#include <string.h>
#include "test_fw.h"
#include "fw.h"
#include "chprintf.h"

/*===========================================================================*/
/* Firmware control                                                          */
/*===========================================================================*/
void cmd_fw(BaseSequentialStream *chp, int argc, char *argv[])
{

    if (argc < 1) {
        goto fw_usage;
    }

    if (!strcmp(argv[0], "erase")) {
        flash_error_t ret;

        /* Start the driver, unlocking the flash */
        eflStart(&EFLD1, NULL);

        /* Start erase operation */
        if (argc > 1) {
            /* Get sector and sanity check */
            flash_sector_t sector = strtoul(argv[1], NULL, 0);
            if (sector >= EFLD1.descriptor->sectors_count) {
                chprintf(chp, "Invalid sector\r\n");
                goto fw_usage;
            }

            /* Erase Sector */
            chprintf(chp, "Erasing sector %u... ", sector);
            ret = flashStartEraseSector(&EFLD1, sector);
        } else {
            /* Erase Bank 2 */
            chprintf(chp, "Erasing Bank %d... ", (SYSCFG->MEMRMP & SYSCFG_MEMRMP_UFB_MODE ? BANK_0 : BANK_1));
            ret = flashStartEraseAll(&EFLD1);
        }

        /* Wait for erase operation to complete */
        if (ret == FLASH_NO_ERROR) {
            /* Initiated successfully, wait for completion */
            ret = flashWaitErase((BaseFlash*)&EFLD1);
        }

        /* Verify completion */
        if (ret != FLASH_NO_ERROR) {
            chprintf(chp, "Error with erase operation: %d\r\n", ret);
            return;
        }
        chprintf(chp, "Done!\r\n");

        /* Stop the driver, locking the flash */
        eflStop(&EFLD1);
    } else if (!strcmp(argv[0], "verifyerase") && argc > 1) {
        /* Start the driver, unlocking the flash */
        eflStart(&EFLD1, NULL);

        /* Get sector and sanity check */
        flash_sector_t sector = strtoul(argv[1], NULL, 0);
        if (sector >= EFLD1.descriptor->sectors_count) {
            chprintf(chp, "Invalid sector\r\n");
            goto fw_usage;
        }

        /* Query for completion status and verify erase */
        chprintf(chp, "Erase query returned %d\r\n", flashQueryErase(&EFLD1, NULL));
        chprintf(chp, "Erase verify returned %d\r\n", flashVerifyErase(&EFLD1, sector));

        /* Stop the driver, locking the flash */
        eflStop(&EFLD1);
    } else if (!strcmp(argv[0], "read") && argc > 3) {
        flash_offset_t offset = strtoul(argv[1], NULL, 0);
        size_t len = strtoul(argv[2], NULL, 0);
        int err;

        chprintf(chp, "Reading %d bytes of flash to %s starting at offset 0x%06X... ", len, argv[3], offset);
        err = fw_read(&EFLD1, argv[3], offset, len);
        if (err != 0) {
            chprintf(chp, "Error: Return code %d\r\n", err);
            return;
        }
        chprintf(chp, "Done!\r\n");
    } else if (!strcmp(argv[0], "write") && argc > 2) {
        uint32_t offset = strtoul(argv[1], NULL, 0);
        int err;

        chprintf(chp, "Writing %s to flash at offset %05X... ", argv[2], offset);
        err = fw_write(&EFLD1, argv[2], offset);
        if (err != 0) {
            chprintf(chp, "Error: Return code %d\r\n", err);
            return;
        }
        chprintf(chp, "Done!\r\n");
    } else if (!strcmp(argv[0], "flash") && argc > 2) {
        uint32_t crc = strtoul(argv[2], NULL, 0);
        int err;

        chprintf(chp, "Erasing offline bank and writing %s... ", argv[1]);
        err = fw_flash(&EFLD1, argv[1], crc);
        if (err != 0) {
            chprintf(chp, "Error: Return code %d\r\n", err);
            return;
        }
        chprintf(chp, "Done!\r\n");
    } else if (!strcmp(argv[0], "crc") && argc > 2) {
        fw_bank_t bank;
        size_t len = strtoul(argv[2], NULL, 0);
        if (argv[1][0] == '0') {
            bank = BANK_0;
        } else if (argv[1][0] == '1') {
            bank = BANK_1;
        } else {
            goto fw_usage;
        }

        chprintf(chp, "Bank %d CRC: 0x%08X\r\n\r\n", bank, fw_crc(&EFLD1, bank, len));
    } else if (!strcmp(argv[0], "verify") && argc > 1) {
        fw_bank_t bank;
        uint32_t crc;
        if (argv[1][0] == '0') {
            bank = BANK_0;
        } else if (argv[1][0] == '1') {
            bank = BANK_1;
        } else {
            goto fw_usage;
        }

        chprintf(chp, "Verifying FW in bank %d... ", bank);
        crc = fw_verify(&EFLD1, bank);
        chprintf(chp, "%s! CRC: 0x%08X\r\n\r\n", (crc ? "VALID" : "INVALID"), crc);
    } else if (!strcmp(argv[0], "setinfo") && argc > 3) {
        fw_bank_t bank;
        fw_info_t fw_info;
        fw_info.crc  = strtoul(argv[2], NULL, 0);
        fw_info.len  = strtoul(argv[3], NULL, 0);
        if (argv[1][0] == '0') {
            bank = BANK_0;
        } else if (argv[1][0] == '1') {
            bank = BANK_1;
        } else {
            goto fw_usage;
        }

        chprintf(chp, "Setting FW info for bank %d... ", bank);
        fw_set_info(fw_info, bank);
        chprintf(chp, "Done\r\n");
    } else if (!strcmp(argv[0], "bank") && argc > 1) {
        uint32_t bank;
        if (argv[1][0] == '0') {
            bank = BANK_0;
        } else if (argv[1][0] == '1') {
            bank = BANK_1;
        } else {
            goto fw_usage;
        }

        chprintf(chp, "Setting next boot bank to %d... ", bank);
        int err = fw_set_bank(&EFLD1, bank);
        if (err != FLASH_NO_ERROR) {
            chprintf(chp, "Error: Return code %d\r\n\r\n", err);
            return;
        }
        chprintf(chp, "Done!\r\n\r\n");
    } else {
        goto fw_usage;
    }

    return;

fw_usage:
    chprintf(chp,  "Usage: fw <command>\r\n"
                   "    erase [sector]:\r\n"
                   "        Erase [sector] or the offline bank if no sector provided\r\n"
                   "    verifyerase <sector>:\r\n"
                   "        Verify sector erased\r\n"
                   "    read <offset> <size> <file>:\r\n"
                   "        Read <size> bytes of flash starting at <offset> into <file>\r\n"
                   "    write <offset> <file>:\r\n"
                   "        Write <file> to flash starting at <offset>\r\n"
                   "    flash <file> <expected_crc>:\r\n"
                   "        Write <file> to offline bank\r\n"
                   "    crc <bank> <len>:\r\n"
                   "        Print CRC for <bank> assuming length <len>\r\n"
                   "    verify <bank>:\r\n"
                   "        Verify firmware in <bank> against CRC\r\n"
                   "    setinfo <bank> <crc> <length>:\r\n"
                   "        Set <bank> health info to <crc> and <length>\r\n"
                   "    bank <num>:\r\n"
                   "        Set flash bank to <num> for next boot\r\n"
                   "\r\n");
    return;
}
