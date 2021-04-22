#ifndef _CMD_H_
#define _CMD_H_

#include "comms.h"

typedef enum {
    CMD_TX_CTRL,
    CMD_C3_FLASH,
    CMD_C3_BANK,
    CMD_OPD_SYSENABLE,
    CMD_OPD_SYSDISABLE,
    CMD_OPD_ENABLE,
    CMD_OPD_DISABLE,
    CMD_OPD_RESET,
    CMD_OPD_STATUS,
} cmd_code_t;

typedef struct {
    cmd_code_t cmd;
    uint8_t arg[];
} cmd_t;

typedef enum {
    CMD_TXCTRL_DISABLE = 0,
    CMD_TXCTRL_ENABLE
} cmd_txctrl_t;

typedef enum {
    CMD_OPD_SCAN_NORESET = 0,
    CMD_OPD_SCAN_RESET
} cmd_opd_scan_t;

#ifdef __cplusplus
extern "C" {
#endif

void cmd_process(cmd_t *cmd, fb_t *resp_fb);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif

