#include <stdlib.h>
#include <string.h>
#include "test_radio.h"
#include "comms.h"
#include "radio.h"
#include "ax5043.h"
#include "si41xx.h"
#include "chprintf.h"

extern radio_dev_t radio_devices[];
extern radio_profile_t radio_profiles[];
extern synth_dev_t synth_devices[];

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
        if (devp->state < AX5043_READY) {
            chprintf(chp, "Error: Failed to start driver. Error code %d.\r\n", devp->error);
        } else {
            chprintf(chp, "OK\r\n");
        }
    } else if (!strcmp(argv[0], "stop")) {
        chprintf(chp, "Stopping AX5043 driver...");
        ax5043Stop(devp);
        chprintf(chp, "OK\r\n");
    } else if (!strcmp(argv[0], "idle")) {
        ax5043Idle(devp);
    } else if (!strcmp(argv[0], "rx")) {
        ax5043RX(devp, false, false);
    } else if (!strcmp(argv[0], "dump")) {
        chprintf(chp, "\r\n");
        for (int i = 0; i < 0x1000; i++) {
            if (i % 0x20 == 0) chprintf(chp, "\r\n%03X:", i);
            chprintf(chp, " %02X", ax5043ReadU8(devp, i));
        }
        chprintf(chp, "\r\n");
    } else if (!strcmp(argv[0], "setfreq") && argc > 1) {
        uint32_t freq = strtoul(argv[1], NULL, 0);
        uint8_t vcor = (argc > 2 ? strtoul(argv[2], NULL, 0) : 0);
        bool chan_b = (argc > 3 && !strcmp(argv[3], "true") ? true : false);

        if (devp->state < AX5043_READY) {
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
    } else if (!strcmp(argv[0], "getfreq")) {
        chprintf(chp, "Current frequency is %u\r\n", ax5043GetFreq(devp));
    } else if (!strcmp(argv[0], "profile")) {
        if (argc > 1) {
            uint32_t i, index;
            /* Find max index */
            for (i = 0; radio_profiles[i].profile != NULL; i++);
            index = strtoul(argv[1], NULL, 0);
            if (index >= i) {
                chprintf(chp, "ERROR: Invalid profile\r\n");
                goto radio_usage;
            }
            ax5043SetProfile(devp, radio_profiles[index].profile);
            return;
        } else {
            const ax5043_profile_t *profile;
            profile = ax5043GetProfile(devp);
            for (uint32_t i = 0; radio_profiles[i].profile != NULL; i++) {
                if (radio_profiles[i].profile == profile) {
                    chprintf(chp, "Current profile is %s\r\n", radio_profiles[i].name);
                }
            }
            chprintf(chp, "Available profiles:\r\n");
            for (uint32_t i = 0; radio_profiles[i].profile != NULL; i++) {
                chprintf(chp, "%u:\t%s\r\n", i, radio_profiles[i].name);
            }
            chprintf(chp, "\r\n");
            return;
        }
    } else if (!strcmp(argv[0], "rssi")) {
        chprintf(chp, "RSSI: %u\r\nBackground RSSI: %u\r\n", ax5043GetRSSI(devp), ax5043GetBGNDRSSI(devp));
    } else if (!strcmp(argv[0], "read") && argc > 2) {
        uint16_t reg = strtoul(argv[1], NULL, 0);

        if (devp->state < AX5043_READY) {
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
    } else if (!strcmp(argv[0], "write") && argc > 3) {
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
                  "    getfreq:     Get the current frequency in use\r\n"
                  "    profile [num]:\r\n"
                  "                 Print current profile and list available profiles,\r\n"
                  "                 or set the profile to [num] if provided\r\n"
                  "\r\n"
                  "    rssi:        Get the current RSSI value\r\n"
                  "\r\n"
                  "    read<reg> <type>:\r\n"
                  "                 Read <reg> where <type> is u8|u16|u24|u32\r\n"
                  "\r\n"
                  "    write<reg> <value> <type>:\r\n"
                  "                 Write <reg> with <value> where <type> is u8|u16|u24|u32\r\n"
                  "    dump:        Dump all register values\r\n"
                  "\r\n");
    return;
}

/*===========================================================================*/
/* OreSat Synthesizer Control                                                */
/*===========================================================================*/
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
        for (i = 0; synth_devices[i].devp != NULL; i++);
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

/*===========================================================================*/
/* OreSat RF Path Control                                                    */
/*===========================================================================*/
void cmd_rf(BaseSequentialStream *chp, int argc, char *argv[])
{
    if (argc < 1) {
        goto rf_usage;
    }

    if (!strcmp(argv[0], "pa") && argc > 1) {
        if (!strcmp(argv[1], "enable")) {
            palSetLine(LINE_PA_ENABLE);
        } else if (!strcmp(argv[1], "disable")) {
            palClearLine(LINE_PA_ENABLE);
        }
    } else if (!strcmp(argv[0], "lna") && argc > 1) {
        if (!strcmp(argv[1], "enable")) {
            palSetLine(LINE_LNA_ENABLE);
        } else if (!strcmp(argv[1], "disable")) {
            palClearLine(LINE_LNA_ENABLE);
        }
    } else if (!strcmp(argv[0], "totclear")) {
        palSetLine(LINE_TOT_CLEAR);
        chThdSleepMicroseconds(10);
        palClearLine(LINE_TOT_CLEAR);
    } else if (!strcmp(argv[0], "status")) {
        chprintf(chp, "PA State: %s\r\nLNA State: %s\r\nTOT State: %s\r\n\r\n",
                (palReadLine(LINE_PA_ENABLE) ? "ENABLED" : "DISABLED"),
                (palReadLine(LINE_LNA_ENABLE) ? "ENABLED" : "DISABLED"),
                (palReadLine(LINE_TOT_OUT) ? "ENABLED" : "DISABLED"));
    } else {
        goto rf_usage;
    }

    return;
rf_usage:
    chprintf(chp, "\r\n"
                  "Usage: rf <cmd>\r\n"
                  "    pa <enable/disable>:\r\n"
                  "         Enable or Disable the PA\r\n"
                  "    lna <enable/disable>:\r\n"
                  "         Enable or Disable the LNA\r\n"
                  "    totclear\r\n"
                  "         Clear the Time Out Timer\r\n"
                  "    status\r\n"
                  "         RF path status\r\n"
                  "\r\n");
    return;
}

/*===========================================================================*/
/* OreSat RF System Test                                                     */
/*===========================================================================*/
void cmd_rftest(BaseSequentialStream *chp, int argc, char *argv[])
{
    if (argc < 1) {
        goto rftest_usage;
    }

    palClearLine(LINE_LNA_ENABLE);
    palSetLine(LINE_PA_ENABLE);

    if (!strcmp(argv[0], "test1")) {
    } else if (!strcmp(argv[0], "test2")) {
    } else if (!strcmp(argv[0], "test3")) {
    } else if (!strcmp(argv[0], "test4")) {
    } else {
        palSetLine(LINE_LNA_ENABLE);
        palClearLine(LINE_PA_ENABLE);
        goto rftest_usage;
    }

    palSetLine(LINE_LNA_ENABLE);
    palClearLine(LINE_PA_ENABLE);
    return;
rftest_usage:
    chprintf(chp, "\r\n"
                  "Usage: rftest <cmd>\r\n"
                  "    test1:\r\n"
                  "         Executes RF Test 1\r\n"
                  "    test2:\r\n"
                  "         Executes RF Test 2\r\n"
                  "    test3:\r\n"
                  "         Executes RF Test 3\r\n"
                  "    test4:\r\n"
                  "         Executes RF Test 4\r\n"
                  "\r\n");
    return;
}
