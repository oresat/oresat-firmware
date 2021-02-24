#include <stdlib.h>
#include <string.h>

#include "fw.h"
#include "mmc.h"
#include "chprintf.h"

#define FLASH_BANK_SIZE 0x100000U
#define BUF_SIZE        256
#define SYNC_SIZE       0x400

uint8_t buf[BUF_SIZE];

/*===========================================================================*/
/* Deployer Testing                                                          */
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
        int err = 0;

        err = lfs_file_open(&lfs, &file, argv[3], LFS_O_RDWR | LFS_O_CREAT);
        if (err) {
            chprintf(chp, "Error in file open: %d\r\n", err);
            goto fw_usage;
        }
        do {
            uint32_t n = size;
            if (n > BUF_SIZE) {
                n = BUF_SIZE;
            }

            flashRead(&EFLD1, offset, n, buf);
            if (lfs_file_write(&lfs, &file, buf, n) >= SYNC_SIZE) {
                lfs_file_sync(&lfs, &file);
            }

            offset += n;
            size -= n;
        } while (size);
        lfs_file_close(&lfs, &file);
    } else if (!strcmp(argv[0], "write") && argc > 2) {
        chprintf(chp, "Unimplemented\r\n");
    } else if (!strcmp(argv[0], "status")) {
        chprintf(chp, "BFB2: %s\r\nFB_MODE: %s\r\n", (FLASH->OPTCR & FLASH_OPTCR_BFB2 ? "SET" : "CLEAR"), (SYSCFG->MEMRMP & SYSCFG_MEMRMP_UFB_MODE ? "SET" : "CLEAR"));
    } else {
        goto fw_usage;
    }

    return;

fw_usage:
    chprintf(chp,  "Usage: fw <command>\r\n"
                   "    unlock:                 Unlock the flash to perform operations\r\n"
                   "    lock:                   Lock the flash\r\n"
                   "    erase [sector]:         Erase [sector] or Bank 2 if no sector provided\r\n"
                   "    verify <sector>:        Verify sector erased\r\n"
                   "    read <offset> <size>:   Read <size> bytes of flash starting at <offset>\r\n"
                   "    write <offset> <file>:  Write <file> to flash starting at <offset>\r\n"
                   "    status:                 Display the status of embedded flash subsystem\r\n"
                   "\r\n");
    return;
}
