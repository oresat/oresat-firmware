#include <stdlib.h>
#include <string.h>

#include "fw.h"
#include "fs.h"
#include "crc.h"
#include "persist.h"
#include "fram.h"

#define FLASH_OPTKEY1                       0x08192A3BU
#define FLASH_OPTKEY2                       0x4C5D6E7FU
#define FLASH_BANK_OFFSET                   0x100000U
#define BUF_SIZE                            256

uint8_t buf[BUF_SIZE];

int fw_read(EFlashDriver *eflp, char *filename, flash_offset_t offset, size_t len)
{
    lfs_file_t *file;
    int ret;

    file = file_open(&FSD1, filename, LFS_O_WRONLY | LFS_O_CREAT | LFS_O_TRUNC);
    if (file == NULL) {
        return FSD1.err;
    }

    eflStart(&EFLD1, NULL);
    while (len) {
        ssize_t n = len;
        if (n > BUF_SIZE) {
            n = BUF_SIZE;
        }

        ret = flashRead(eflp, offset, n, buf);
        if (ret != FLASH_NO_ERROR) {
            break;
        }
        n = file_write(&FSD1, file, buf, n);
        if (n < 0) {
            ret = n;
            break;
        }

        offset += n;
        len -= n;
    };
    eflStop(&EFLD1);

    ret = file_close(&FSD1, file);
    return ret;
}

int fw_write(EFlashDriver *eflp, char *filename, flash_offset_t offset)
{
    lfs_file_t *file;
    ssize_t n;
    int ret;

    file = file_open(&FSD1, filename, LFS_O_RDONLY);
    if (file == NULL) {
        return FSD1.err;
    }

    eflStart(&EFLD1, NULL);
    while ((n = file_read(&FSD1, file, buf, BUF_SIZE)) > 0) {
        ret = flashProgram(eflp, offset, n, buf);
        if (ret != FLASH_NO_ERROR) {
            break;
        }
        offset += n;
    }
    eflStop(&EFLD1);
    if (n != 0) {
        ret = n;
    }

    ret = file_close(&FSD1, file);
    return ret;
}

bool fw_verify(EFlashDriver *eflp, fw_bank_t bank)
{
    fw_info_t fw_info[2] = {0};
    uint32_t crc = 0;
    flash_offset_t offset;
    size_t len;

    offset = (((SYSCFG->MEMRMP & SYSCFG_MEMRMP_UFB_MODE) >> SYSCFG_MEMRMP_UFB_MODE_Pos) ^ bank ? FLASH_BANK_OFFSET : 0);
    framRead(&FRAMD1, FRAM_FWINFO_ADDR, &fw_info, sizeof(fw_info));
    len = fw_info[bank].len;
    if (len == 0)
        return false;

    eflStart(&EFLD1, NULL);
    while (len) {
        ssize_t n = len;
        if (n > BUF_SIZE) {
            n = BUF_SIZE;
        }

        if (flashRead(eflp, offset, n, buf) != FLASH_NO_ERROR) {
            break;
        }
        crc = crc32(buf, n, crc);
        offset += n;
        len -= n;
    };
    eflStop(&EFLD1);

    return (crc == fw_info[bank].crc);
}

int fw_flash(EFlashDriver *eflp, char *filename, uint32_t expected_crc)
{
    lfs_file_t *file;
    fw_info_t fw_info = {0};
    ssize_t n;
    int ret;

    /* Verify the file matches the expected CRC */
    file = file_open(&FSD1, filename, LFS_O_RDONLY);
    if (file == NULL) {
        return FSD1.err;
    }
    while ((n = file_read(&FSD1, file, buf, BUF_SIZE)) > 0) {
        fw_info.crc = crc32(buf, n, fw_info.crc);
        fw_info.len += n;
    }
    if (n != 0) {
        ret = n;
    }
    ret = file_close(&FSD1, file);
    if (ret)
        return ret;
    if (fw_info.crc != expected_crc) {
        ret = FLASH_ERROR_VERIFY;
        return ret;
    }

    /* Erase the offline flash bank */
    eflStart(&EFLD1, NULL);
    ret = flashStartEraseAll(eflp);
    if (ret != FLASH_NO_ERROR)
        return ret;
    /* Wait for erase operation to complete */
    ret = flashWaitErase((BaseFlash*)eflp);
    if (ret != FLASH_NO_ERROR)
        return ret;
    eflStop(&EFLD1);

    /* Write new firmware image to offline bank */
    ret = fw_write(eflp, filename, FLASH_BANK_OFFSET);
    if (ret != FLASH_NO_ERROR)
        return ret;

    /* Commit new FW info to FRAM */
    uint16_t addr = (SYSCFG->MEMRMP & SYSCFG_MEMRMP_UFB_MODE ? FRAM_FWINFO_ADDR : FRAM_FWINFO_ADDR + sizeof(fw_info_t));
    framWrite(&FRAMD1, addr, &fw_info, sizeof(fw_info_t));

    return fw_verify(eflp, !(SYSCFG->MEMRMP & SYSCFG_MEMRMP_UFB_MODE));
}

int fw_set_bank(EFlashDriver *eflp, fw_bank_t bank)
{
    int ret;

    ret = flashQueryErase(eflp, NULL);
    if (ret != FLASH_NO_ERROR)
        return ret;
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

    return ret;
}
