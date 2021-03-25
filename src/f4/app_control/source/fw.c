#include <stdlib.h>
#include <string.h>

#include "fw.h"
#include "fs.h"
#include "chprintf.h"

#define FLASH_OPTKEY1                       0x08192A3BU
#define FLASH_OPTKEY2                       0x4C5D6E7FU

#define FLASH_BANK_OFFSET                   0x100000U
#define BUF_SIZE                            256

typedef enum {
    BANK_0 = 0,
    BANK_1 = 1
} fw_bank_t;

uint8_t buf[BUF_SIZE];

int fw_read(EFlashDriver *eflp, char *filename, flash_offset_t offset, size_t len)
{
    lfs_file_t *file;
    int err;

    file = file_open(&FSD1, filename, LFS_O_WRONLY | LFS_O_CREAT | LFS_O_TRUNC);
    if (file == NULL) {
        return FSD1.err;
    }

    do {
        ssize_t n = len;
        if (n > BUF_SIZE) {
            n = BUF_SIZE;
        }

        err = flashRead(eflp, offset, n, buf);
        if (err != FLASH_NO_ERROR) {
            break;
        }
        n = file_write(&FSD1, file, buf, n);
        if (n < 0) {
            err = n;
            break;
        }

        offset += n;
        len -= n;
    } while (len);

    err = file_close(&FSD1, file);
    return err;
}

int fw_write(EFlashDriver *eflp, char *filename, flash_offset_t offset)
{
    lfs_file_t *file;
    ssize_t n;
    int err;

    file = file_open(&FSD1, filename, LFS_O_RDONLY);
    if (file == NULL) {
        return FSD1.err;
    }

    while ((n = file_read(&FSD1, file, buf, BUF_SIZE)) > 0) {
        err = flashProgram(eflp, offset, n, buf);
        if (err != FLASH_NO_ERROR) {
            break;
        }
        offset += n;
    }
    if (n != 0) {
        err = n;
    }

    err = file_close(&FSD1, file);
    return err;
}

int fw_flash(EFlashDriver *eflp, char *filename)
{
    int err;

    /* Erase the offline flash bank */
    err = flashStartEraseAll(eflp);
    if (err != FLASH_NO_ERROR)
        goto fw_flash_fail;
    /* Wait for erase operation to complete */
    err = flashWaitErase((BaseFlash*)eflp);
    if (err != FLASH_NO_ERROR)
        goto fw_flash_fail;
    /* Write new firmware image to offline bank */
    err = fw_write(eflp, filename, FLASH_BANK_OFFSET);

fw_flash_fail:
    return err;
}

int fw_set_bank(EFlashDriver *eflp, fw_bank_t bank)
{
    int err;

    err = flashQueryErase(eflp, NULL);
    if (err != FLASH_NO_ERROR)
        return err;
    /* Unlock option byte control register */
    eflp->flash->OPTKEYR |= FLASH_OPTKEY1;
    eflp->flash->OPTKEYR |= FLASH_OPTKEY2;

    /* Set bank bit appropriately */
    eflp->flash->OPTCR &= ~FLASH_OPTCR_BFB2;
    eflp->flash->OPTCR |= (bank << FLASH_OPTCR_BFB2_Pos);
    eflp->flash->OPTCR |= FLASH_OPTCR_OPTSTRT;

    /* Wait for operation to finish */
    while ((eflp->flash->SR & FLASH_SR_BSY) != 0);

    /* Lock option byte control register */
    eflp->flash->OPTCR |= FLASH_OPTCR_OPTLOCK;

    return err;
}

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
    } else if (!strcmp(argv[0], "verify") && argc > 1) {
        /* Start the driver, unlocking the flash */
        eflStart(&EFLD1, NULL);

        /* Get sector and sanity check */
        flash_sector_t sector = strtoul(argv[1], NULL, 0);
        if (sector >= EFLD1.descriptor->sectors_count) {
            chprintf(chp, "Invalid sector\r\n");
            goto fw_usage;
        }

        /* Query for completion status and verify */
        chprintf(chp, "Erase query returned %d\r\n", flashQueryErase(&EFLD1, NULL));
        chprintf(chp, "Erase verify returned %d\r\n", flashVerifyErase(&EFLD1, sector));

        /* Stop the driver, locking the flash */
        eflStop(&EFLD1);
    } else if (!strcmp(argv[0], "read") && argc > 3) {
        flash_offset_t offset = strtoul(argv[1], NULL, 0);
        size_t len = strtoul(argv[2], NULL, 0);
        int err;

        /* Start the driver, unlocking the flash */
        eflStart(&EFLD1, NULL);

        chprintf(chp, "Reading %d bytes of flash to %s starting at offset 0x%06X... ", len, argv[3], offset);
        err = fw_read(&EFLD1, argv[3], offset, len);
        if (err != 0) {
            chprintf(chp, "Error: Return code %d\r\n", err);
            return;
        }
        chprintf(chp, "Done!\r\n");

        /* Stop the driver, locking the flash */
        eflStop(&EFLD1);
    } else if (!strcmp(argv[0], "write") && argc > 2) {
        uint32_t offset = strtoul(argv[1], NULL, 0);
        int err;

        /* Start the driver, unlocking the flash */
        eflStart(&EFLD1, NULL);

        chprintf(chp, "Writing %s to flash at offset %05X... ", argv[2], offset);
        err = fw_write(&EFLD1, argv[2], offset);
        if (err != 0) {
            chprintf(chp, "Error: Return code %d\r\n", err);
            return;
        }
        chprintf(chp, "Done!\r\n");

        /* Stop the driver, locking the flash */
        eflStop(&EFLD1);
    } else if (!strcmp(argv[0], "flash") && argc > 1) {
        int err;

        /* Start the driver, unlocking the flash */
        eflStart(&EFLD1, NULL);

        chprintf(chp, "Erasing offline bank and writing %s... ", argv[1]);
        err = fw_flash(&EFLD1, argv[1]);
        if (err != 0) {
            chprintf(chp, "Error: Return code %d\r\n", err);
            return;
        }
        chprintf(chp, "Done!\r\n");

        /* Stop the driver, locking the flash */
        eflStop(&EFLD1);
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
    } else if (!strcmp(argv[0], "status")) {
        chprintf(chp, "Current Bank: %d\r\nNext Boot Bank: %d\r\n\r\n",
                (SYSCFG->MEMRMP & SYSCFG_MEMRMP_UFB_MODE ? BANK_1 : BANK_0),
                (FLASH->OPTCR & FLASH_OPTCR_BFB2 ? BANK_1 : BANK_0));
    } else {
        goto fw_usage;
    }

    return;

fw_usage:
    chprintf(chp,  "Usage: fw <command>\r\n"
                   "    erase [sector]:\r\n"
                   "        Erase [sector] or the offline bank if no sector provided\r\n"
                   "    verify <sector>:\r\n"
                   "        Verify sector erased\r\n"
                   "    read <offset> <size> <file>:\r\n"
                   "        Read <size> bytes of flash starting at <offset> into <file>\r\n"
                   "    write <offset> <file>:\r\n"
                   "        Write <file> to flash starting at <offset>\r\n"
                   "    flash <file>:\r\n"
                   "        Write <file> to offline bank\r\n"
                   "    bank <num>:\r\n"
                   "        Set flash bank to <num> for next boot\r\n"
                   "    status:\r\n"
                   "        Display the status of embedded flash subsystem\r\n"
                   "\r\n");
    return;
}
