#ifndef _CMD_H_
#define _CMD_H_

#include "frame_buf.h"

typedef enum {
    CMD_TX_CTRL = 0,
    CMD_FW_FLASH,
    CMD_FW_BANK,
    CMD_FW_VERIFY,
    CMD_C3_SOFTRESET,
    CMD_C3_HARDRESET,
    CMD_C3_FACTORYRESET,
    CMD_I2C_RESET,
    CMD_FS_FORMAT,
    CMD_FS_UNMOUNT,
    CMD_FS_REMOVE,
    CMD_FS_CRC,
    CMD_NODE_ENABLE,
    CMD_NODE_STATUS,
    CMD_OPD_SYSENABLE,
    CMD_OPD_SYSDISABLE,
    CMD_OPD_SCAN,
    CMD_OPD_ENABLE,
    CMD_OPD_RESET,
    CMD_OPD_STATUS,
    CMD_RTC_SETTIME,
} cmd_code_t;

typedef struct {
    uint32_t crc;
    char filename[];
} cmd_flash_t;

typedef struct {
    cmd_code_t cmd;
    uint8_t arg[];
} cmd_t;

#ifdef __cplusplus
extern "C" {
#endif

void cmd_process(cmd_t *cmd, fb_t *resp_fb);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
