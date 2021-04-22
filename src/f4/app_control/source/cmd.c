#include "cmd.h"
#include "c3.h"
#include "opd.h"

void cmd_process(cmd_t *cmd, fb_t *resp_fb)
{
    void *ret;

    switch (cmd->cmd) {
    case CMD_TX_CTRL:
        ret = fb_put(resp_fb, sizeof(int));
        tx_enable(cmd->arg);
        *((int*)ret) = tx_enabled();
        break;
    case CMD_OPD_SYSENABLE:
        ret = fb_put(resp_fb, sizeof(int));
        opd_start();
        *((int*)ret) = 0;
        break;
    case CMD_OPD_SYSDISABLE:
        ret = fb_put(resp_fb, sizeof(int));
        opd_stop();
        *((int*)ret) = 0;
        break;
    case CMD_OPD_SCAN:
        ret = fb_put(resp_fb, sizeof(int));
        opd_scan(cmd->arg[0]);
        *((int*)ret) = 0;
        break;
    case CMD_OPD_REINIT:
        ret = fb_put(resp_fb, sizeof(int));
        *((int *)ret) = opd_probe(cmd->arg[0], true);
        break;
    case CMD_OPD_ENABLE:
        ret = fb_put(resp_fb, sizeof(int));
        *((int *)ret) = opd_state(cmd->arg[0], true);
        break;
    case CMD_OPD_DISABLE:
        ret = fb_put(resp_fb, sizeof(int));
        *((int *)ret) = opd_state(cmd->arg[0], false);
        break;
    case CMD_OPD_RESET:
        ret = fb_put(resp_fb, sizeof(int));
        *((int *)ret) = opd_reset(cmd->arg[0]);
        break;
    case CMD_OPD_STATUS:
        ret = fb_put(resp_fb, sizeof(opd_status_t));
        opd_status(cmd->arg[0], ret);
        break;
    default:
        break;
    }
}
