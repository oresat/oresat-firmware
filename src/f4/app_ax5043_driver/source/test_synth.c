#include <stdlib.h>
#include <string.h>
#include "ch.h"
#include "hal.h"
#include "test_synth.h"
#include "chprintf.h"

static SI41XXConfig synth_cfg = {
    .sen = LINE_LO_SEN,
    .sclk = LINE_LO_SCLK,
    .sdata = LINE_LO_SDATA,
    .ref_freq = 16000000,
    .if_div = 2,
    .if_n = 873,
    .if_r = 16,
};

SI41XXDriver synth;

void cmd_synth(BaseSequentialStream *chp, int argc, char *argv[])
{

    if (argc < 1) {
        goto synth_usage;
    }

    if (!strcmp(argv[0], "start")) {
        si41xxStart(&synth, &synth_cfg);
    } else if (!strcmp(argv[0], "stop")) {
        si41xxStop(&synth);
    } else if (!strcmp(argv[0], "reg") && argc > 3) {
        uint32_t reg = strtoul(argv[1], NULL, 0);
        uint32_t value = strtoul(argv[2], NULL, 0);
        si41xxWriteRaw(&synth, reg, value);
    } else if (!strcmp(argv[0], "freq") && argc > 2) {
        uint32_t freq = strtoul(argv[1], NULL, 0);
        if (!si41xxSetIF(&synth, freq)) {
            chprintf(chp, "Failed to set frequency\r\n");
            goto synth_usage;
        }
    } else if (!strcmp(argv[0], "ifdiv") && argc > 2) {
        uint32_t div = strtoul(argv[1], NULL, 0);
        if (!si41xxSetIFDiv(&synth, div)) {
            chprintf(chp, "Failed to set IF divider value\r\n");
            goto synth_usage;
        }
    } else {
        goto synth_usage;
    }

    return;
synth_usage:
    chprintf(chp, "\r\n"
                  "Usage: synth <cmd>\r\n"
                  "    start:       Start the device\r\n"
                  "    stop:        Stop the device\r\n"
                  "    reg <reg> <value>:\r\n"
                  "                 Write <reg> with <value>\r\n"
                  "\r\n"
                  "    freq <freq>: Sets frequency of IF output to <freq>\r\n"
                  "    ifdiv <div>: Sets IF output divider to <div>\r\n"
                  "\r\n");
    return;
}
