#include <stdlib.h>
#include <string.h>

#include "nmt.h"
#include "CANopen.h"
#include "chprintf.h"
#include "shell.h"

void usage(BaseSequentialStream *chp) {
    chprintf(chp, "Usage; sdo read|write <NodeID> <index> <subindex> [write_value]\r\n");
}

void cmd_sdo(BaseSequentialStream *chp, int argc, char *argv[]) {
    if (argc < 4) {
        usage(chp);
        return;
    }

    if (!strcmp(argv[0], "read")) {
        CO_SDOclient_return_t ret;
        systime_t prev_time, cur_time, diff_time;
        uint8_t data[31] = {0};
        uint32_t dataSize = 0;
        uint32_t abortCode = 0;

        CO_SDOclient_setup(CO->SDOclient[0], 0, 0, strtoul(argv[1], NULL, 0));
        CO_SDOclientUploadInitiate(CO->SDOclient[0], strtoul(argv[2], NULL, 0), strtoul(argv[3], NULL, 0), data, 30, false);
        prev_time = chVTGetSystemTimeX();
        do {
            diff_time = chTimeDiffX(prev_time, cur_time = chVTGetSystemTimeX());
            prev_time = cur_time;
            ret = CO_SDOclientUpload(CO->SDOclient[0], chTimeI2MS(diff_time), 1000, &dataSize, &abortCode);
            chThdSleepMilliseconds(10);
        } while (ret > 0);
        CO_SDOclientClose(CO->SDOclient[0]);
        data[dataSize] = '\0';
        if (abortCode == CO_SDO_AB_NONE) {
            chprintf(chp, "Received %u byte string: %s\r\n", dataSize, data);
        } else {
            chprintf(chp, "Received abort code: %x\r\n", abortCode);
        }

    } else if (!strcmp(argv[0], "write")) {

    } else {
        chprintf(chp, "Invalid command: %s\r\n", argv[0]);
        usage(chp);
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
