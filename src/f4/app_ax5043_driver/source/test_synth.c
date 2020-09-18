#include <stdlib.h>
#include <string.h>
#include "ch.h"
#include "hal.h"
#include "test_synth.h"
#include "chprintf.h"

SI41XXDriver synth;

void cmd_synth(BaseSequentialStream *chp, int argc, char *argv[])
{

    if (argc < 2) {
        goto synth_usage;
    }

    if (!strcmp(argv[0], "reg") && argc > 3) {
        uint32_t reg = strtoul(argv[1], NULL, 0);
        uint32_t value = strtoul(argv[2], NULL, 0);
        si41xxWriteRaw(&synth, reg, value);
    } else if (!strcmp(argv[0], "freq")) {
        uint32_t freq = strtoul(argv[1], NULL, 0);
        if (!si41xxSetIF(&synth, freq)) {
            chprintf(chp, "Failed to set frequency\r\n");
            goto synth_usage;
        }
    } else if (!strcmp(argv[0], "ifdiv")) {
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
    chprintf(chp, "Usage: synth <cmd>\r\n");
    return;
}
