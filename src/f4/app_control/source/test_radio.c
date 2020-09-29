#include <stdlib.h>
#include <string.h>
#include "ch.h"
#include "hal.h"
#include "test_radio.h"
#include "chprintf.h"

static char str[] = "KJ7SAT - Test transmission from AX5043 driver.";
static bool tx_once = false;

size_t tx_cb(uint8_t *buf, size_t max_len) {
    struct __attribute__((packed)) {
        ax5043_chunk_t preamble;
        ax5043_chunk_t data;
    } txbuf;

    size_t len = sizeof(txbuf) + sizeof(str);

    if (!tx_once && len < max_len) {
        txbuf.preamble.header = AX5043_CHUNKCMD_REPEATDATA | _VAL2FLD(AX5043_FIFOCHUNK_SIZE, 3);
        txbuf.preamble.repeatdata.flags = AX5043_CHUNK_REPEATDATA_UNENC | AX5043_CHUNK_REPEATDATA_NOCRC;
        txbuf.preamble.repeatdata.repeatcnt = 20;
        txbuf.preamble.repeatdata.data = 0x55;
        txbuf.data.header = AX5043_CHUNKCMD_DATA | _VAL2FLD(AX5043_FIFOCHUNK_SIZE, AX5043_CHUNKSIZE_VAR);
        txbuf.data.length = sizeof(str) + 1;
        txbuf.data.data.flags = AX5043_CHUNK_DATATX_PKTSTART | AX5043_CHUNK_DATATX_PKTEND;
        memcpy(buf, &txbuf, sizeof(txbuf));
        memcpy(&buf[sizeof(txbuf)], str, sizeof(str));
        tx_once = true;
    } else {
        return 0;
    }
    return len;
}

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
    } else if (!strcmp(argv[0], "rx")) {
        ax5043_mailbox_t *mb = NULL;
        chprintf(chp, "Entering receive mode and waiting 10 seconds for message...");
        ax5043RX(devp, false);
        if (devp->error != AX5043_ERR_NOERROR) {
            chprintf(chp, "Error: Failed to enter mode. Error code %d.\r\n", devp->error);
        }
        chMBFetchTimeout(&devp->mb_filled, (msg_t*)&mb, TIME_S2I(10));
        ax5043Idle(devp);
        if (mb == NULL) {
            chprintf(chp, "No message received\r\n");
        } else {
            chprintf(chp, "Message received:");
            for (uint32_t i = 0; i < mb->index; i++) {
                if (i % 0x10 == 0) {
                    chprintf(chp, "\r\n%02X:", i);
                }
                chprintf(chp, " %02X", mb->data[i]);
            }
            chprintf(chp, "\r\n");

            chSysLock();
            chMBPostI(&devp->mb_free, (msg_t)mb);
            chSysUnlock();
        }
    } else if (!strcmp(argv[0], "wor")) {
        ax5043_mailbox_t *mb = NULL;
        chprintf(chp, "Entering WOR mode and waiting for 10 seconds for message...");
        ax5043WOR(devp, false);
        if (devp->error != AX5043_ERR_NOERROR) {
            chprintf(chp, "Error: Failed to enter mode. Error code %d.\r\n", devp->error);
        }
        chMBFetchTimeout(&devp->mb_filled, (msg_t*)&mb, TIME_S2I(10));
        ax5043Idle(devp);
        if (mb == NULL) {
            chprintf(chp, "No message received\r\n");
        } else {
            chprintf(chp, "Message received\r\n");

            chSysLock();
            chMBPostI(&devp->mb_free, (msg_t)mb);
            chSysUnlock();
        }
    } else if (!strcmp(argv[0], "tx")) {
        tx_once = false;
        ax5043TX(devp, tx_cb, false);
        if (devp->error != AX5043_ERR_NOERROR) {
            chprintf(chp, "Error: Failed to enter mode. Error code %d.\r\n", devp->error);
        }
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
    } else if (!strcmp(argv[0], "read") && argc > 2) {
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
                  "    rx:          Puts device into RX mode\r\n"
                  "    wor:         Puts device into WOR mode\r\n"
                  "    tx:          Puts device into TX mode\r\n"
                  "    setfreq <freq> [vcor] [chan_b]:\r\n"
                  "                 Sets frequency of channel A/B to <freq>\r\n"
                  "                 Optionally provide VCOR. [chan_b] specifies channel B\r\n"
                  "\r\n"
                  "    read<reg> <type>:\r\n"
                  "                 Read <reg> where <type> is u8|u16|u24|u32\r\n"
                  "\r\n"
                  "    write<reg> <value> <type>:\r\n"
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
