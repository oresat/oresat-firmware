#include <stdlib.h>
#include <string.h>

#include "fw.h"
#include "mmc.h"
#include "chprintf.h"

#define FLASH_OPTKEY1                       0x08192A3BU
#define FLASH_OPTKEY2                       0x4C5D6E7FU

#define FLASH_BANK_SIZE                     0x100000U
#define BUF_SIZE                            256

uint8_t buf[BUF_SIZE];

/*===========================================================================*/
/* Firmware control                                                          */
/*===========================================================================*/
void cmd_fw(BaseSequentialStream *chp, int argc, char *argv[])
{

    if (argc < 1) {
        goto fw_usage;
    }

    if (!strcmp(argv[0], "unlock")) {
        eflStart(&EFLD1, NULL);
    } else if (!strcmp(argv[0], "lock")) {
        eflStop(&EFLD1);
    } else if (!strcmp(argv[0], "erase")) {
        flash_error_t ret;

        /* Start erase operation */
        if (argc > 1) {
            /* Get sector and sanity check */
            flash_sector_t sector = strtoul(argv[1], NULL, 0);
            if (sector >= 24) goto fw_usage;

            /* Erase Sector */
            chprintf(chp, "Erasing sector %u... ", sector);
            ret = flashStartEraseSector(&EFLD1, sector);
        } else {
            /* Erase Bank 2 */
            chprintf(chp, "Erasing Bank 2... ");
            ret = flashStartEraseAll(&EFLD1);
        }

        /* Wait for erase operation to complete */
        if (ret == FLASH_NO_ERROR) {
            ret = flashWaitErase((BaseFlash*)&EFLD1);
        }

        /* Verify completion */
        if (ret != FLASH_NO_ERROR) {
            chprintf(chp, "Error with erase operation: %d\r\n", ret);
            return;
        }
        chprintf(chp, "Done!\r\n");
    } else if (!strcmp(argv[0], "verify") && argc > 1) {
        /* Get sector and sanity check */
        flash_sector_t sector = strtoul(argv[1], NULL, 0);
        if (sector >= 24) goto fw_usage;
        /* Query for completion status and verify */
        chprintf(chp, "Erase query returned %d\r\n", flashQueryErase(&EFLD1, NULL));
        chprintf(chp, "Erase verify returned %d\r\n", flashVerifyErase(&EFLD1, sector));
    } else if (!strcmp(argv[0], "read") && argc > 3) {
        uint32_t offset = strtoul(argv[1], NULL, 0);
        uint32_t size = strtoul(argv[2], NULL, 0);
        lfs_file_t file;
        flash_error_t ret;
        int err = 0;

        err = lfs_file_open(&lfs, &file, argv[3], LFS_O_RDWR | LFS_O_CREAT | LFS_O_TRUNC);
        if (err) {
            chprintf(chp, "Error in file open: %d\r\n", err);
            goto fw_usage;
        }
        do {
            uint32_t n = size;
            if (n > BUF_SIZE) {
                n = BUF_SIZE;
            }

            ret = flashRead(&EFLD1, offset, n, buf);
            if (ret != FLASH_NO_ERROR) {
                chprintf(chp, "Error in flash read: %d\r\n", ret);
                lfs_file_close(&lfs, &file);
                return;
            }
            if (lfs_file_write(&lfs, &file, buf, n) < 0) {
                chprintf(chp, "Error in file write: %d\r\n", n);
                lfs_file_close(&lfs, &file);
                return;
            }

            offset += n;
            size -= n;
        } while (size);

        lfs_file_close(&lfs, &file);
    } else if (!strcmp(argv[0], "write") && argc > 2) {
        uint32_t offset = strtoul(argv[1], NULL, 0);
        lfs_ssize_t n;
        lfs_file_t file;
        flash_error_t ret;
        int err = 0;

        err = lfs_file_open(&lfs, &file, argv[2], LFS_O_RDONLY);
        if (err) {
            chprintf(chp, "Error in file open: %d\r\n", err);
            goto fw_usage;
        }

        while ((n = lfs_file_read(&lfs, &file, buf, BUF_SIZE)) > 0) {
            ret = flashProgram(&EFLD1, offset, n, buf);
            if (ret != FLASH_NO_ERROR) {
                chprintf(chp, "Error in flash write\r\n");
                lfs_file_close(&lfs, &file);
                return;
            }
            offset += n;
        }
        if (n < 0) {
            chprintf(chp, "Error in file read: %d\r\n", n);
        }

        lfs_file_close(&lfs, &file);
    } else if (!strcmp(argv[0], "bank") && argc > 1) {
        uint32_t bank = strtoul(argv[1], NULL, 0);
        if (bank > 1) {
            goto fw_usage;
        }

        if (flashQueryErase(&EFLD1, NULL) != FLASH_NO_ERROR) {
            chprintf(chp, "Flash busy\r\n");
            return;
        }

        FLASH->OPTKEYR |= FLASH_OPTKEY1;
        FLASH->OPTKEYR |= FLASH_OPTKEY2;

        FLASH->OPTCR &= ~FLASH_OPTCR_BFB2;
        FLASH->OPTCR |= (bank << FLASH_OPTCR_BFB2_Pos);
        FLASH->OPTCR |= FLASH_OPTCR_OPTSTRT;

        while ((FLASH->SR & FLASH_SR_BSY) != 0);

        FLASH->OPTCR |= FLASH_OPTCR_OPTLOCK;
    } else if (!strcmp(argv[0], "status")) {
        chprintf(chp, "OPTCR: %08X\r\n", FLASH->OPTCR);
        chprintf(chp, "BFB2: %s\r\nFB_MODE: %s\r\n", (FLASH->OPTCR & FLASH_OPTCR_BFB2 ? "SET" : "CLEAR"), (SYSCFG->MEMRMP & SYSCFG_MEMRMP_UFB_MODE ? "SET" : "CLEAR"));
    } else {
        goto fw_usage;
    }

    return;

fw_usage:
    chprintf(chp,  "Usage: fw <command>\r\n"
                   "    unlock:\r\n"
                   "        Unlock the flash to perform operations\r\n"
                   "    lock:\r\n"
                   "        Lock the flash\r\n"
                   "    erase [sector]:\r\n"
                   "        Erase [sector] or Bank 2 if no sector provided\r\n"
                   "    verify <sector>:\r\n"
                   "        Verify sector erased\r\n"
                   "    read <offset> <size> <file>:\r\n"
                   "        Read <size> bytes of flash starting at <offset> into <file>\r\n"
                   "    write <offset> <file>:\r\n"
                   "        Write <file> to flash starting at <offset>\r\n"
                   "    bank <num>:\r\n"
                   "        Set flash bank to <num> for next boot\r\n"
                   "    status:\r\n"
                   "        Display the status of embedded flash subsystem\r\n"
                   "\r\n");
    return;
}
