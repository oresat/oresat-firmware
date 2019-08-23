#include <stdlib.h>
#include <string.h>

#include "nmt.h"
#include "CO_master.h"
#include "chprintf.h"
#include "shell.h"

#ifndef BUF_SIZE
#define BUF_SIZE 0x10000 /* 64k */
#endif

static uint8_t data[BUF_SIZE];

void cmd_nmt(BaseSequentialStream *chp, int argc, char *argv[]) {
    uint8_t node_id = 0;
    if (argc < 2) {
        chprintf(chp, "Usage: nmt start|stop|preop|resetcomm|resetnode <NodeID>\r\n");
        return;
    }
    node_id = strtoul(argv[1], NULL, 0);

    if (!strcmp(argv[0], "start")) {
        CO_sendNMTcommand(CO, CO_NMT_ENTER_OPERATIONAL, node_id);
    } else if (!strcmp(argv[0], "stop")) {
        CO_sendNMTcommand(CO, CO_NMT_ENTER_STOPPED, node_id);
    } else if (!strcmp(argv[0], "preop")) {
        CO_sendNMTcommand(CO, CO_NMT_ENTER_PRE_OPERATIONAL, node_id);
    } else if (!strcmp(argv[0], "resetcomm")) {
        CO_sendNMTcommand(CO, CO_NMT_RESET_COMMUNICATION, node_id);
    } else if (!strcmp(argv[0], "resetnode")) {
        CO_sendNMTcommand(CO, CO_NMT_RESET_NODE, node_id);
    } else {
        chprintf(chp, "Invalid command: %s\r\n", argv[0]);
        return;
    }
}

void cmd_sdo(BaseSequentialStream *chp, int argc, char *argv[]) {
    uint32_t data_len = 0;
    uint32_t abrt_code = 0;
    uint8_t node_id = 0;
    uint16_t index = 0;
    uint8_t subindex = 0;
    bool block = false;

    if (argc < 4) {
        chprintf(chp, "Usage: sdo read|write <NodeID> <index> <subindex> [blockmode]\r\n");
        return;
    }

    node_id = strtoul(argv[1], NULL, 0);
    index = strtoul(argv[2], NULL, 0);
    subindex = strtoul(argv[3], NULL, 0);
    if (argc == 5)
        block = !strcmp(argv[4], "true");

    if (!strcmp(argv[0], "read")) {
        sdo_upload(CO->SDOclient[0], node_id, index, subindex, data, sizeof(data) - 1, &data_len, &abrt_code, 1000, block);
        data[data_len] = '\0';
        if (abrt_code == CO_SDO_AB_NONE) {
            chprintf(chp, "Received %u bytes of data:", data_len);
            for (uint32_t i = 0; i < data_len; i++)
                chprintf(chp, " %02X", data[i]);
            chprintf(chp, "\r\n");
        } else {
            chprintf(chp, "Received abort code: %x\r\n", abrt_code);
        }
    } else if (!strcmp(argv[0], "write")) {
        sdo_download(CO->SDOclient[0], node_id, index, subindex, data, data_len, &abrt_code, 1000, block);
    } else {
        chprintf(chp, "Usage: sdo read|write <NodeID> <index> <subindex> [block_mode]\r\n");
        return;
    }
}

static const ShellCommand commands[] = {
    {"nmt", cmd_nmt},
    {"sdo", cmd_sdo},
    {NULL, NULL}
};

static const ShellConfig shell_cfg = {
    (BaseSequentialStream *)&SD2,
    commands
};

THD_WORKING_AREA(shell_wa, 0x200);
THD_WORKING_AREA(nmt_wa, 0x200);
THD_FUNCTION(nmt, arg)
{
    (void)arg;

    while (!chThdShouldTerminateX()) {
        thread_t *shell_tp = chThdCreateStatic(shell_wa, sizeof(shell_wa), NORMALPRIO, shellThread, (void *)&shell_cfg);
        chThdWait(shell_tp);
        chThdSleepMilliseconds(500);
    }

    chThdExit(MSG_OK);
}
