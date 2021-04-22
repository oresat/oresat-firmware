#include "cmd.h"
#include "c3.h"
#include "fw.h"
#include "opd.h"

void cmd_process(cmd_t *cmd, fb_t *resp_fb)
{
    void *ret;

    switch (cmd->cmd) {
    case CMD_TX_CTRL:
        ret = fb_put(resp_fb, 1);
        tx_enable(cmd->arg[0]);
        *((uint8_t*)ret) = tx_enabled();
        break;
    case CMD_C3_FLASH:
        ret = fb_put(resp_fb, sizeof(int));
        *((int*)ret) = fw_flash(&EFLD1, (char*)&cmd->arg[4], *((uint32_t*)cmd->arg));
        break;
    case CMD_C3_BANK:
        ret = fb_put(resp_fb, sizeof(int));
        *((int*)ret) = fw_set_bank(&EFLD1, cmd->arg[0]);
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
    case CMD_OPD_ENABLE:
        ret = fb_put(resp_fb, 1);
        *((int8_t *)ret) = opd_state(cmd->arg[0], true);
        break;
    case CMD_OPD_DISABLE:
        ret = fb_put(resp_fb, 1);
        *((int8_t *)ret) = opd_state(cmd->arg[0], false);
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
