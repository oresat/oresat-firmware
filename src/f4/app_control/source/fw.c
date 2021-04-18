#include <stdlib.h>
#include <string.h>

#include "fw.h"
#include "fs.h"

#define FLASH_OPTKEY1                       0x08192A3BU
#define FLASH_OPTKEY2                       0x4C5D6E7FU

#define FLASH_BANK_OFFSET                   0x100000U
#define BUF_SIZE                            256

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
