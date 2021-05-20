#include "cmd.h"
#include "c3.h"
#include "fw.h"
#include "fs.h"
#include "opd.h"
#include "node_mgr.h"

void cmd_process(cmd_t *cmd, fb_t *resp_fb)
{
    lfs_file_t *file;
    cmd_flash_t *flash_arg;
    uint32_t *key;
    void *ret;

    switch (cmd->cmd) {
    case CMD_TX_CTRL:
        ret = fb_put(resp_fb, 1);
        tx_enable(cmd->arg[0]);
        *((uint8_t*)ret) = tx_enabled();
        break;
    case CMD_FW_FLASH:
        ret = fb_put(resp_fb, sizeof(int));
        flash_arg = (cmd_flash_t*)cmd->arg;
        *((int*)ret) = fw_flash(&EFLD1, flash_arg->filename, flash_arg->crc);
        break;
    case CMD_FW_BANK:
        ret = fb_put(resp_fb, sizeof(int));
        *((int*)ret) = fw_set_bank(&EFLD1, cmd->arg[0]);
        break;
    case CMD_FW_VERIFY:
        ret = fb_put(resp_fb, sizeof(uint32_t));
        *((uint32_t*)ret) = fw_verify(&EFLD1, cmd->arg[0]);
        break;
    case CMD_C3_SOFTRESET:
        key = (uint32_t*)cmd->arg;
        if (key[0] == 0x01234567U && key[1] == 0x89ABCDEFU)
            NVIC_SystemReset();
        break;
    case CMD_C3_HARDRESET:
        key = (uint32_t*)cmd->arg;
        if (key[0] == 0x01234567U && key[1] == 0x89ABCDEFU)
            chSysHalt("HARD RESET");
        break;
    case CMD_C3_FACTORYRESET:
        key = (uint32_t*)cmd->arg;
        if (key[0] == 0x01234567U && key[1] == 0x89ABCDEFU)
            factory_reset();
        break;
    case CMD_I2C_RESET:
        ret = fb_put(resp_fb, 1);
        palSetLine(LINE_I2C_PWROFF);
        chThdSleepMilliseconds(10);
        palClearLine(LINE_I2C_PWROFF);
        *((uint8_t*)ret) = 0;
        break;
    case CMD_FS_FORMAT:
        ret = fb_put(resp_fb, sizeof(int));
        *((int*)ret) = fs_format(&FSD1);
        break;
    case CMD_FS_UNMOUNT:
        ret = fb_put(resp_fb, sizeof(int));
        *((int*)ret) = fs_unmount(&FSD1);
        break;
    case CMD_FS_REMOVE:
        ret = fb_put(resp_fb, sizeof(int));
        *((int*)ret) = fs_remove(&FSD1, (char*)cmd->arg);
        break;
    case CMD_FS_CRC:
        ret = fb_put(resp_fb, sizeof(uint32_t));
        file = file_open(&FSD1, (char*)cmd->arg, LFS_O_RDONLY);
        if (file == NULL)
            return;
        *((uint32_t*)ret) = file_crc(&FSD1, file);
        file_close(&FSD1, file);
        break;
    case CMD_NODE_ENABLE:
        ret = fb_put(resp_fb, 1);
        *((int8_t *)ret) = node_enable(cmd->arg[0], cmd->arg[1]);
        break;
    case CMD_NODE_STATUS:
        ret = fb_put(resp_fb, sizeof(CO_NMT_internalState_t));
        node_status(cmd->arg[0], ret);
        break;
    case CMD_OPD_SYSENABLE:
        ret = fb_put(resp_fb, 1);
        opd_start();
        *((uint8_t*)ret) = 0;
        break;
    case CMD_OPD_SYSDISABLE:
        ret = fb_put(resp_fb, 1);
        opd_stop();
        *((uint8_t*)ret) = 0;
        break;
    case CMD_OPD_SCAN:
        ret = fb_put(resp_fb, 1);
        opd_scan(cmd->arg[0]);
        *((uint8_t*)ret) = 0;
        break;
    case CMD_OPD_ENABLE:
        ret = fb_put(resp_fb, 1);
        *((int8_t *)ret) = opd_enable(cmd->arg[0], cmd->arg[1]);
        break;
    case CMD_OPD_RESET:
        ret = fb_put(resp_fb, 1);
        *((int8_t *)ret) = opd_reset(cmd->arg[0]);
        break;
    case CMD_OPD_STATUS:
        ret = fb_put(resp_fb, sizeof(opd_status_t));
        opd_status(cmd->arg[0], ret);
        break;
    default:
        break;
    }
}
