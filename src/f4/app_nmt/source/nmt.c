#include <stdlib.h>
#include <string.h>

#include "nmt.h"
#include "CO_master.h"
#include "chprintf.h"
#include "shell.h"

void cmd_sdo(BaseSequentialStream *chp, int argc, char *argv[]) {
    uint8_t data[31] = {0};
    uint32_t data_len = 0;
    uint32_t abrt_code = 0;
    uint8_t node_id = 0;
    uint16_t index = 0;
    uint8_t subindex = 0;

    if (argc < 4) {
        chprintf(chp, "Usage; sdo read|write <NodeID> <index> <subindex> [write_value]\r\n");
        return;
    }

    node_id = strtoul(argv[1], NULL, 0);
    index = strtoul(argv[2], NULL, 0);
    subindex = strtoul(argv[3], NULL, 0);

    if (!strcmp(argv[0], "read")) {
        sdo_upload(CO->SDOclient[0], node_id, index, subindex, data, sizeof(data) - 1, &data_len, &abrt_code, 1000, false);
        data[data_len] = '\0';
        if (abrt_code == CO_SDO_AB_NONE) {
            chprintf(chp, "Received %u byte string: %s\r\n", data_len, data);
        } else {
            chprintf(chp, "Received abort code: %x\r\n", abrt_code);
        }
    } else if (!strcmp(argv[0], "write") && argc < 5) {
        /*sdo_download(CO->SDOclient[0], node_id, index, subindex, data, strlen(data), &abrt_code, 1000, false);*/
    } else {
        chprintf(chp, "Invalid command: %s\r\n", argv[0]);
        return;
    }

}

static const ShellCommand commands[] = {
    {"sdo", cmd_sdo},
    {NULL, NULL}
};

static const ShellConfig shell_cfg = {
    (BaseSequentialStream *)&SD2,
    commands
};

THD_WORKING_AREA(shell_wa, 0x200);

// Example blinker thread
THD_WORKING_AREA(nmt_wa, 0x200);
THD_FUNCTION(nmt, arg) {
    (void)arg;

    while (!chThdShouldTerminateX()) {
        thread_t *shell_tp = chThdCreateStatic(shell_wa, sizeof(shell_wa), NORMALPRIO, shellThread, (void *)&shell_cfg);
        chThdWait(shell_tp);
        chThdSleepMilliseconds(500);
    }

    chThdExit(MSG_OK);
}
