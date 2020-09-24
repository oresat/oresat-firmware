#include <stdlib.h>
#include <string.h>
#include "ch.h"
#include "hal.h"
#include "test_radio.h"
#include "chprintf.h"

/*===========================================================================*/
/* OreSat Radio Control                                                      */
/*===========================================================================*/
void cmd_radio(BaseSequentialStream *chp, int argc, char *argv[])
{
    static AX5043Driver *devp = NULL;
    static const AX5043Config *cfgp = NULL;
    if (argc < 1) {
        goto radio_usage;
    }

    if (!strcmp(argv[0], "list")) {
        for (uint32_t i = 0; radio_devices[i].devp != NULL; i++) {
            chprintf(chp, "%u:\t%s\r\n", i, radio_devices[i].name);
        }
        chprintf(chp, "\r\n");
        return;
    } else if (!strcmp(argv[0], "dev") && argc > 1) {
        uint32_t i, index;
        /* Find max index */
        for (i = 0; radio_devices[i].devp != NULL; i++);
        index = strtoul(argv[1], NULL, 0);
        if (index >= i) {
            chprintf(chp, "ERROR: Invalid device\r\n");
            goto radio_usage;
        }
        devp = radio_devices[index].devp;
        cfgp = radio_devices[index].cfgp;
        return;
    }

    if (devp == NULL) {
        chprintf(chp, "Error: Set the device via 'dev' first.\r\n");
        goto radio_usage;
    }

    if (!strcmp(argv[0], "start")) {
        chprintf(chp, "Starting AX5043 driver...");
        ax5043Start(devp, cfgp);
        if (devp->state != AX5043_READY) {
            chprintf(chp, "Error: Failed to start driver. Error code %d.\r\n", devp->error);
        } else {
            chprintf(chp, "OK\r\n");
        }
    } else if (!strcmp(argv[0], "stop")) {
        chprintf(chp, "Stopping AX5043 driver...");
        ax5043Stop(devp);
        chprintf(chp, "OK\r\n");
    } else if (!strcmp(argv[0], "setfreq") && argc > 1) {
        uint32_t freq = strtoul(argv[1], NULL, 0);
        uint8_t vcor = (argc > 2 ? strtoul(argv[2], NULL, 0) : 0);
        bool chan_b = (argc > 3 && !strcmp(argv[3], "true") ? true : false);

        if (devp->state != AX5043_READY) {
            chprintf(chp, "Error: Please start the AX5043 driver first\r\n");
            goto radio_usage;
        }

        chprintf(chp, "Setting Channel %s frequency to %u...", (chan_b ? "B" : "A"), freq);
        ax5043SetFreq(devp, freq, vcor, chan_b);
        if (devp->error != AX5043_ERR_NOERROR) {
            chprintf(chp, "Error: Failed to set frequency. Error code %d.\r\n", devp->error);
        } else {
            chprintf(chp, "OK\r\n");
        }
    } else if (!strcmp(argv[0], "readreg") && argc > 2) {
        uint16_t reg = strtoul(argv[1], NULL, 0);

        if (devp->state != AX5043_READY) {
            chprintf(chp, "Error: Please start the AX5043 driver first\r\n");
            goto radio_usage;
        }

        if (!strcmp(argv[2], "u8")) {
            chprintf(chp, "0x%02X\r\n", ax5043ReadU8(devp, reg));
        } else if (!strcmp(argv[2], "u16")) {
            chprintf(chp, "0x%04X\r\n", ax5043ReadU16(devp, reg));
        } else if (!strcmp(argv[2], "u24")) {
            chprintf(chp, "0x%06X\r\n", ax5043ReadU24(devp, reg));
        } else if (!strcmp(argv[2], "u32")) {
            chprintf(chp, "0x%08X\r\n", ax5043ReadU32(devp, reg));
        } else {
            goto radio_usage;
        }
    } else if (!strcmp(argv[0], "writereg") && argc > 3) {
        uint16_t reg = strtoul(argv[1], NULL, 0);

        if (!strcmp(argv[3], "u8")) {
            uint8_t value = strtoul(argv[2], NULL, 0);
            ax5043WriteU8(devp, reg, value);
        } else if (!strcmp(argv[3], "u16")) {
            uint16_t value = strtoul(argv[2], NULL, 0);
            ax5043WriteU16(devp, reg, value);
        } else if (!strcmp(argv[3], "u24")) {
            uint32_t value = strtoul(argv[2], NULL, 0);
            ax5043WriteU24(devp, reg, value);
        } else if (!strcmp(argv[3], "u32")) {
            uint32_t value = strtoul(argv[2], NULL, 0);
            ax5043WriteU32(devp, reg, value);
        } else {
            goto radio_usage;
        }
    } else {
        goto radio_usage;
    }

    return;

radio_usage:
    chprintf(chp, "\r\n"
                  "Usage: radio <cmd>\r\n"
                  "    list:        List available devices\r\n"
                  "    dev <dev>:   Set the device to <dev> as shown by 'list'\r\n"
                  "\r\n"
                  "    start:       Start AX5043 device\r\n"
                  "    stop:        Stop AX5043 device\r\n"
                  "    setfreq <freq> [vcor] [chan_b]:\r\n"
                  "                 Sets frequency of channel A/B to <freq>\r\n"
                  "                 Optionally provide VCOR. [chan_b] specifies channel B\r\n"
                  "\r\n"
                  "    readreg <reg> <type>:\r\n"
                  "                 Read <reg> where <type> is u8|u16|u24|u32\r\n"
                  "\r\n"
                  "    writereg <reg> <value> <type>:\r\n"
                  "                 Write <reg> with <value> where <type> is u8|u16|u24|u32\r\n"
                  "\r\n");
    return;
}

void cmd_synth(BaseSequentialStream *chp, int argc, char *argv[])
{
    static SI41XXDriver *devp = NULL;
    static SI41XXConfig *cfgp = NULL;
    if (argc < 1) {
        goto synth_usage;
    }

    if (!strcmp(argv[0], "list")) {
        for (uint32_t i = 0; synth_devices[i].devp != NULL; i++) {
            chprintf(chp, "%u:\t%s\r\n", i, synth_devices[i].name);
        }
        chprintf(chp, "\r\n");
        return;
    } else if (!strcmp(argv[0], "dev") && argc > 1) {
        uint32_t i, index;
        /* Find max index */
        for (i = 0; radio_devices[i].devp != NULL; i++);
        index = strtoul(argv[1], NULL, 0);
        if (index >= i) {
            chprintf(chp, "ERROR: Invalid device\r\n");
            goto synth_usage;
        }
        devp = synth_devices[index].devp;
        cfgp = synth_devices[index].cfgp;
        return;
    }

    if (devp == NULL) {
        chprintf(chp, "Error: Set the device via 'dev' first.\r\n");
        goto synth_usage;
    }

    if (!strcmp(argv[0], "start")) {
        si41xxStart(devp, cfgp);
    } else if (!strcmp(argv[0], "stop")) {
        si41xxStop(devp);
    } else if (!strcmp(argv[0], "reg") && argc > 2) {
        uint32_t reg = strtoul(argv[1], NULL, 0);
        uint32_t value = strtoul(argv[2], NULL, 0);
        si41xxWriteRaw(devp, reg, value);
    } else if (!strcmp(argv[0], "freq") && argc > 1) {
        uint32_t freq = strtoul(argv[1], NULL, 0);
        if (!si41xxSetIF(devp, freq)) {
            chprintf(chp, "Failed to set frequency\r\n");
            goto synth_usage;
        }
        chprintf(chp, "N=%u R=%u\r\n", cfgp->if_n, cfgp->if_r);
    } else if (!strcmp(argv[0], "ifdiv") && argc > 1) {
        uint32_t div = strtoul(argv[1], NULL, 0);
        if (!si41xxSetIFDiv(devp, div)) {
            chprintf(chp, "Failed to set IF divider value\r\n");
            goto synth_usage;
        }
        chprintf(chp, "IFDIV=%u\r\n", cfgp->if_div);
    } else if (!strcmp(argv[0], "status")) {
        chprintf(chp, "PLL: %s\r\n", (palReadLine(LINE_LO_PLL) ? "NOT LOCKED" : "LOCKED"));
    } else {
        goto synth_usage;
    }

    return;
synth_usage:
    chprintf(chp, "\r\n"
                  "Usage: synth <cmd>\r\n"
                  "    list:        List available devices\r\n"
                  "    dev <dev>:   Set the device to <dev> as shown by 'list'\r\n"
                  "\r\n"
                  "    start:       Start the device\r\n"
                  "    stop:        Stop the device\r\n"
                  "    reg <reg> <value>:\r\n"
                  "                 Write <reg> with <value>\r\n"
                  "\r\n"
                  "    freq <freq>: Sets frequency of IF output to <freq>\r\n"
                  "    ifdiv <div>: Sets IF output divider to <div> (1,2,4,8)\r\n"
                  "    status:      Print PLL lock status\r\n"
                  "\r\n");
    return;
}
