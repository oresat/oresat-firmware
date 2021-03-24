#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "cmd.h"
#include "c3.h"
#include "fw.h"
#include "comms.h"
#include "opd.h"
#include "CO_master.h"
#include "rtc.h"
#include "fs.h"
#include "test_mmc.h"
#include "test_radio.h"
#include "deployer.h"
#include "test_deploy.h"
#include "chprintf.h"
#include "shell.h"

#define BUF_SIZE 256

struct cb_arg {
    lfs_file_t *file;
    uint8_t buf[BUF_SIZE];
};

static thread_t *shell_tp;
extern thread_t *c3_tp;

/*===========================================================================*/
/* Support functions                                                         */
/*===========================================================================*/
/*
bool sdo_file_cb(sdocli_t *sdocli, CO_SDO_return_t ret, CO_SDO_abortCode_t *abort_code, void *arg)
{
    struct cb_arg *data = arg;
    ssize_t size, space;

    if (ret < 0) {
        chprintf((BaseSequentialStream*)&SD3, "Error in SDO transfer. Ret: %d Abort: %X", ret, *abort_code);
        return true;
    }

    if (sdocli->state == SDOCLI_ST_DOWNLOAD) {
        space = CO_fifo_getSpace(&sdocli->sdo_c->bufFifo);
        do {
            size = file_read(&FSD1, data->file, data->buf, lfs_min(space, BUF_SIZE));
            if (size < 0) {
                *abort_code = CO_SDO_AB_NO_DATA;
                return true;
            }
            CO_SDOclientDownloadBufWrite(sdocli->sdo_c, data->buf, size);
        } while (size && (space -= size));
    } else if (sdocli->state == SDOCLI_ST_UPLOAD) {
        if (ret == CO_SDO_RT_uploadDataBufferFull || ret == CO_SDO_RT_ok_communicationEnd) {
            do {
                size = CO_SDOclientUploadBufRead(sdocli->sdo_c, data->buf, BUF_SIZE);
                file_write(&FSD1, data->file, data->buf, size);
            } while (size);
        }
    }

    return false;
}
*/

/*===========================================================================*/
/* OreSat CAN Bus NMT                                                        */
/*===========================================================================*/
void cmd_nmt(BaseSequentialStream *chp, int argc, char *argv[])
{
    CO_ReturnError_t err;
    uint8_t node_id = 0;

    if (argc < 1) {
        goto nmt_usage;
    }

    if (argc > 1) {
        node_id = strtoul(argv[1], NULL, 0);
    }

    if (!strcmp(argv[0], "op")) {
        err = CO_NMT_sendCommand(CO->NMT, CO_NMT_ENTER_OPERATIONAL, node_id);
    } else if (!strcmp(argv[0], "preop")) {
        err = CO_NMT_sendCommand(CO->NMT, CO_NMT_ENTER_PRE_OPERATIONAL, node_id);
    } else if (!strcmp(argv[0], "stop")) {
        err = CO_NMT_sendCommand(CO->NMT, CO_NMT_ENTER_STOPPED, node_id);
    } else if (!strcmp(argv[0], "resetcomms")) {
        err = CO_NMT_sendCommand(CO->NMT, CO_NMT_RESET_COMMUNICATION, node_id);
    } else if (!strcmp(argv[0], "resetnode")) {
        err = CO_NMT_sendCommand(CO->NMT, CO_NMT_RESET_NODE, node_id);
    } else {
        goto nmt_usage;
    }
    if (err != CO_ERROR_NO) {
        chprintf(chp, "Error executing NMT command: %d\r\n", err);
    }
    return;

nmt_usage:
    chprintf(chp,  "Usage: nmt <command> <node_id>\r\n"
                   "    op:         Set device operational\r\n"
                   "    preop:      Set device pre-operational\r\n"
                   "    stop:       Stop device\r\n"
                   "    resetcomms: Reset CAN communications on device\r\n"
                   "    resetnode:  Reset device\r\n"
                   "\r\n");
    return;
}

/*===========================================================================*/
/* OreSat CAN Bus SDO Client                                                 */
/*===========================================================================*/
/*
void cmd_sdo(BaseSequentialStream *chp, int argc, char *argv[])
{
    struct cb_arg data;
    thread_t *tp;
    int err = 0;
    uint16_t index = 0;
    uint8_t node_id = 0, subindex = 0;
    size_t size = 0;

    if (argc < 5 || (argv[0][0] != 'r' && argv[0][0] != 'w')) {
        goto sdo_usage;
    }

    node_id = strtoul(argv[1], NULL, 0);
    index = strtoul(argv[2], NULL, 0);
    subindex = strtoul(argv[3], NULL, 0);

    data.file = file_open(&FSD1, argv[4], LFS_O_RDWR | LFS_O_CREAT);
    if (data.file == NULL) {
        chprintf(chp, "Error in file open: %d\r\n", err);
        goto sdo_usage;
    }
    if (argv[0][0] == 'w') {
        size = file_size(&FSD1, data.file);
    }

    chprintf(chp, "Initiating transfer... ");
    tp = sdo_transfer(argv[0][0], node_id, index, subindex, size, sdo_file_cb, &data);
    if (tp == NULL) {
        chprintf(chp, "Failed to initiate transfer\r\n");
        return;
    }
    chThdWait(tp);
    file_close(&FSD1, data.file);
    chprintf(chp, "Done!\r\n");
    return;

sdo_usage:
    chprintf(chp, "Usage: sdo (r)ead|(w)rite <node_id> <index> <subindex> <filename>\r\n");
    return;
}
*/

/*===========================================================================*/
/* OreSat Power Domain Control                                               */
/*===========================================================================*/
void cmd_opd(BaseSequentialStream *chp, int argc, char *argv[])
{
    static uint8_t opd_addr = 0;
    opd_status_t status = {0};

    if (argc < 1) {
        goto opd_usage;
    } else if (argc > 1) {
        opd_addr = strtoul(argv[1], NULL, 0);
        chprintf(chp, "Setting persistent board address to 0x%02X\r\n", opd_addr);
    }

    if (!strcmp(argv[0], "sysenable")) {
        chprintf(chp, "Enabling OPD subsystem\r\n");
        opd_start();
    } else if (!strcmp(argv[0], "sysdisable")) {
        chprintf(chp, "Disabling OPD subsystem\r\n");
        opd_stop();
    } else if (!strcmp(argv[0], "sysrestart")) {
        chprintf(chp, "Restarting OPD subsystem\r\n");
        opd_stop();
        opd_start();
    } else if (!strcmp(argv[0], "rescan")) {
        chprintf(chp, "Re-scanning OPD devices\r\n");
        opd_scan(false);
    } else if (!strcmp(argv[0], "summary")) {
        chprintf(chp, "Board summary:\r\n");
        for (i2caddr_t i = OPD_MIN_ADDR; i <= OPD_MAX_ADDR; i++) {
            if (!opd_status(i, &status)) {
                chprintf(chp, "0x%02X: CONNECTED - %s - %s\r\n", i,
                        (status.odr & OPD_PIN_MASK(OPD_EN) ? "ENABLED" : "DISABLED"),
                        (status.input & OPD_PIN_MASK(OPD_FAULT) ? "TRIPPED" : "NOT TRIPPED"));
            } else {
                chprintf(chp, "0x%02X: NOT CONNECTED\r\n", i);
            }
        }
    } else {
        if (opd_addr == 0) {
            chprintf(chp, "Please specify an OPD address at least once (it will persist)\r\n");
            goto opd_usage;
        }
        if (!strcmp(argv[0], "enable")) {
            chprintf(chp, "Enabling board 0x%02X: ", opd_addr);
            if (!opd_enable(opd_addr)) {
                chprintf(chp, "ENABLED\r\n");
            } else {
                chprintf(chp, "NOT CONNECTED\r\n");
            }
        } else if (!strcmp(argv[0], "disable")) {
            chprintf(chp, "Disabling board 0x%02X: ", opd_addr);
            if (!opd_disable(opd_addr)) {
                chprintf(chp, "DISABLED\r\n");
            } else {
                chprintf(chp, "NOT CONNECTED\r\n");
            }
        } else if (!strcmp(argv[0], "reset")) {
            chprintf(chp, "Resetting board 0x%02X: ", opd_addr);
            if (!opd_reset(opd_addr)) {
                chprintf(chp, "RESET\r\n");
            } else {
                chprintf(chp, "NOT CONNECTED\r\n");
            }
        } else if (!strcmp(argv[0], "reinit")) {
            chprintf(chp, "Attempting to reinitialize 0x%02X: ", opd_addr);
            if (opd_probe(opd_addr, true)) {
                chprintf(chp, "CONNECTED\r\n");
            } else {
                chprintf(chp, "NOT CONNECTED\r\n");
            }
        } else if (!strcmp(argv[0], "probe")) {
            chprintf(chp, "Probing board 0x%02X: ", opd_addr);
            if (opd_probe(opd_addr, false)) {
                chprintf(chp, "CONNECTED\r\n");
            } else {
                chprintf(chp, "NOT CONNECTED\r\n");
            }
        } else if (!strcmp(argv[0], "status")) {
            chprintf(chp, "Status of board 0x%02X: ", opd_addr);
            if (!opd_status(opd_addr, &status)) {
                chprintf(chp, "CONNECTED\r\n");
                chprintf(chp, "State: %s-%s\r\n",
                        (status.odr & OPD_PIN_MASK(OPD_EN) ? "ENABLED" : "DISABLED"),
                        (status.input & OPD_PIN_MASK(OPD_FAULT) ? "TRIPPED" : "NOT TRIPPED"));
                chprintf(chp, "Raw register values:\r\n");
                chprintf(chp, "Input:       %02X\r\n", status.input);
                chprintf(chp, "Output:      %02X\r\n", status.odr);
                chprintf(chp, "Polarity:    %02X\r\n", status.pol);
                chprintf(chp, "Mode:        %02X\r\n", status.mode);
                chprintf(chp, "Timeout:     %02X\r\n", status.timeout);
            } else {
                chprintf(chp, "NOT CONNECTED\r\n");
            }
        } else if (!strcmp(argv[0], "boot")) {
            int retval = opd_boot(opd_addr);
            chprintf(chp, "Boot returned 0x%02X\r\n", retval);
        } else {
            goto opd_usage;
        }
    }

    return;

opd_usage:
    chprintf(chp, "Usage: opd <cmd> <opd_addr>\r\n"
                  "    sysenable:  Enable OPD subsystem (Power On)\r\n"
                  "    sysdisable: Disable OPD subsystem (Power Off)\r\n"
                  "    sysrestart: Cycle power on OPD subsystem\r\n"
                  "    rescan:     Rescans devices on OPD\r\n"
                  "    enable:     Enable an OPD attached card\r\n"
                  "    disable:    Disable an OPD attached card\r\n"
                  "    reset:      Reset the circuit breaker of a card\r\n"
                  "    reinit:     Reinitialize a device\r\n"
                  "    probe:      Probe an address to see if a card responds\r\n"
                  "    status:     Report the status of a card\r\n"
                  "    summary:    Report the status of all cards\r\n"
                  "    boot:       Attempt to bootstrap a card\r\n");
    return;
}

/*===========================================================================*/
/* Time                                                                      */
/*===========================================================================*/
void cmd_time(BaseSequentialStream *chp, int argc, char *argv[])
{
    RTCDateTime timespec;
    time_t unix_time;
    uint32_t msec;
    time_scet_t scet;
    time_utc_t utc;
    if (argc < 1) {
        goto time_usage;
    }
    if (!strcmp(argv[0], "unix")) {
        if (!strcmp(argv[1], "get")) {
            unix_time = rtcGetTimeUnix(&msec);
            chprintf(chp, "UNIX Time: %d\r\n"
                          "Date:      %s\r\n",
                          unix_time, ctime(&unix_time));
        } else if (!strcmp(argv[1], "set") && argc > 2) {
            rtcSetTimeUnix(strtoul(argv[2], NULL, 0), 0);
        } else {
            goto time_usage;
        }
    } else if (!strcmp(argv[0], "scet")) {
        if (!strcmp(argv[1], "get")) {
            rtcGetTimeSCET(&scet);
            chprintf(chp, "SCET Time: %u.%u\r\n", scet.coarse, scet.fine);
        } else if (!strcmp(argv[1], "set") && argc > 3) {
            scet.coarse = strtoul(argv[2], NULL, 0);
            scet.fine = strtoul(argv[3], NULL, 0);
            rtcSetTimeSCET(&scet);
        } else {
            goto time_usage;
        }
    } else if (!strcmp(argv[0], "utc")) {
        if (!strcmp(argv[1], "get")) {
            rtcGetTimeUTC(&utc);
            chprintf(chp, "UTC Time: Day: %u ms: %u us: %u\r\n", utc.day, utc.ms, utc.us);
        } else if (!strcmp(argv[1], "set") && argc > 4) {
            utc.day = strtoul(argv[2], NULL, 0);
            utc.ms = strtoul(argv[3], NULL, 0);
            utc.us = strtoul(argv[4], NULL, 0);
            rtcSetTimeUTC(&utc);
        } else {
            goto time_usage;
        }
    } else if (!strcmp(argv[0], "raw")) {
        rtcGetTime(&RTCD1, &timespec);
        chprintf(chp, "Year: %u Month: %u DST: %u DoW: %u Day: %u ms: %u\r\n",
                      timespec.year, timespec.month, timespec.dstflag, timespec.dayofweek, timespec.day, timespec.millisecond);
    } else if (!strcmp(argv[0], "status")) {
        chprintf(chp, "Date:    %08X\r\n"
                      "Time:    %08X\r\n"
                      "Wakeup:  %08X\r\n"
                      "Alarm A: %08X (%s)\r\n"
                      "Alarm B: %08X (%s)\r\n",
                      RTCD1.rtc->DR, RTCD1.rtc->TR, RTCD1.rtc->WUTR,
                      RTCD1.rtc->ALRMAR, (RTCD1.rtc->CR & RTC_CR_ALRAE ? "ENABLED" : "DISABLED"),
                      RTCD1.rtc->ALRMBR, (RTCD1.rtc->CR & RTC_CR_ALRBE ? "ENABLED" : "DISABLED"));
    } else {
        goto time_usage;
    }

    return;

time_usage:
    chprintf(chp, "Usage: time unix|scet|utc|raw get|set <values>\r\n");
    return;
}

/*===========================================================================*/
/* OreSat LFS Operations                                                     */
/*===========================================================================*/
void cmd_lfs(BaseSequentialStream *chp, int argc, char *argv[])
{
    int err;
    lfs_file_t *file;
    lfs_dir_t *dir;
    struct lfs_info info;
    char buf[BUF_SIZE];

    if (!strcmp(argv[0], "ls") && argc > 1) {
        dir = dir_open(&FSD1, argv[1]);
        if (dir == NULL) {
            chprintf(chp, "Error in dir_open: %d\r\n", FSD1.err);
            return;
        }
        do {
            err = dir_read(&FSD1, dir, &info);
            if (err <= 0) {
                if (err < 0) {
                    chprintf(chp, "Error in dir_read: %d\r\n", err);
                }
                continue;
            }
            if (info.type == LFS_TYPE_REG) {
                chprintf(chp, "reg  ");
            } else if (info.type == LFS_TYPE_DIR) {
                chprintf(chp, "dir  ");
            } else {
                chprintf(chp, "?    ");
            }
            chprintf(chp, "%8u %s\r\n", info.size, info.name);
        } while (err > 0);
        err = dir_close(&FSD1, dir);
        if (err < 0) {
            chprintf(chp, "Error in dir_close: %d\r\n", err);
            return;
        }
        chprintf(chp, "\r\n");
    } else if (!strcmp(argv[0], "mkdir") && argc > 1) {
        err = fs_mkdir(&FSD1, argv[1]);
        if (err < 0) {
            chprintf(chp, "Error in fs_mkdir: %d\r\n");
            return;
        }
    } else if (!strcmp(argv[0], "rm") && argc > 1) {
        err = fs_remove(&FSD1, argv[1]);
        if (err < 0) {
            chprintf(chp, "Error in fs_remove: %d\r\n");
            return;
        }
    } else if (!strcmp(argv[0], "cat") && argc > 1) {
        file = file_open(&FSD1, argv[1], LFS_O_RDONLY);
        if (file == NULL) {
            chprintf(chp, "Error in file_open: %d\r\n", FSD1.err);
            return;
        }

        err = file_read(&FSD1, file, buf, BUF_SIZE - 1);
        if (err < 0) {
            chprintf(chp, "Error in file_read: %d\r\n", err);
            file_close(&FSD1, file);
            return;
        }
        buf[err] = '\0';
        chprintf(chp, "%s\r\n", buf);

        err = file_close(&FSD1, file);
        if (err < 0) {
            chprintf(chp, "Error in file_close: %d\r\n", err);
            return;
        }
    } else if (!strcmp(argv[0], "hexdump") && argc > 1) {
        file = file_open(&FSD1, argv[1], LFS_O_RDONLY);
        if (file == NULL) {
            chprintf(chp, "Error in file_open: %d\r\n", FSD1.err);
            return;
        }

        err = file_read(&FSD1, file, buf, BUF_SIZE - 1);
        if (err < 0) {
            chprintf(chp, "Error in file_read: %d\r\n", err);
            file_close(&FSD1, file);
            return;
        }
        buf[err] = '\0';
        for (uint32_t i = 0; i < BUF_SIZE; i++) {
            if (i % 0x10 == 0) chprintf(chp, "\r\n%04X:", i);
            chprintf(chp, " %02X", buf[i]);
        }
        chprintf(chp, "\r\n");

        err = file_close(&FSD1, file);
        if (err < 0) {
            chprintf(chp, "Error in file_close: %d\r\n", err);
            return;
        }
    } else if (!strcmp(argv[0], "mount")) {
        int err;

        chprintf(chp, "Attempting to mount LFS...\r\n");
        err = fs_mount(&FSD1, false);
        if (err < 0) {
            chprintf(chp, "Mount failed: %d\r\n", err);
            return;
        }
        chprintf(chp, "OK\r\n");
    } else if (!strcmp(argv[0], "unmount")) {
        int err;

        chprintf(chp, "Attempting to unmount LFS...\r\n");
        err = fs_unmount(&FSD1);
        if (err < 0) {
            chprintf(chp, "Unmount failed: %d\r\n", err);
            return;
        }
        chprintf(chp, "OK\r\n");
    } else if (!strcmp(argv[0], "format")) {
        int err;

        chprintf(chp, "Attempting to format LFS...\r\n");
        err = fs_format(&FSD1);
        if (err < 0) {
            chprintf(chp, "Format failed: %d\r\n", err);
            return;
        }
        chprintf(chp, "OK\r\n");
    } else {
        goto lfs_usage;
    }

    return;

lfs_usage:
    chprintf(chp,  "Usage: lfs <command> <path>\r\n"
                   "    ls:         List directories\r\n"
                   "    mkdir:      Make a directory\r\n"
                   "    rm:         Delete file or directory\r\n"
                   "    cat:        Dump 255 bytes of file as string\r\n"
                   "    hexdump:    Dump 255 bytes of file as hex\r\n"
                   "\r\n"
                   "    mount:      Mount LFS\r\n"
                   "    unmount:    Unmount LFS\r\n"
                   "    format:     Format eMMC for LFS\r\n"
                   "\r\n");
    return;
}

/*===========================================================================*/
/* OreSat C3 State Control                                                   */
/*===========================================================================*/
void cmd_state(BaseSequentialStream *chp, int argc, char *argv[])
{
    if (argc < 1) {
        goto state_usage;
    }
    if (!strcmp(argv[0], "status")) {
        chprintf(chp, "C3 State:  %c\r\n", OD_C3State[0]);
        chprintf(chp, "TX Enable: %s\r\n", (OD_TX_Control.enabled ? "TRUE" : "FALSE"));
        chprintf(chp, "Bat Good:  %s\r\n", (bat_good ? "TRUE" : "FALSE"));
        chprintf(chp, "EDL Mode:  %s\r\n", (edl ? "TRUE" : "FALSE"));
    } else if (!strcmp(argv[0], "tx") && argc > 1) {
        OD_TX_Control.enabled = (argv[1][0] == 't');
        chEvtSignal(c3_tp, C3_EVENT_TX);
    } else if (!strcmp(argv[0], "bat") && argc > 1) {
        bat_good = (argv[1][0] == 't');
        chEvtSignal(c3_tp, C3_EVENT_BAT);
    } else if (!strcmp(argv[0], "edl") && argc > 1) {
        edl = (argv[1][0] == 't');
        chEvtSignal(c3_tp, C3_EVENT_EDL);
    } else if (!strcmp(argv[0], "reset")) {
        NVIC_SystemReset();
    } else {
        goto state_usage;
    }

    return;

state_usage:
    chprintf(chp,  "Usage: state <command>\r\n"
                   "    status:         Get current system state\r\n"
                   "    tx <t/f>:       Override TX enable state\r\n"
                   "    bat <t/f>:      Override battery good state\r\n"
                   "    edl <t/f>:      Override EDL state\r\n"
                   "    reset:          Reset C3\r\n"
                   "\r\n");
    return;
}

/*===========================================================================*/
/* OreSat C3 FRAM                                                            */
/*===========================================================================*/
void cmd_fram(BaseSequentialStream *chp, int argc, char *argv[])
{
    if (argc < 1) {
        goto fram_usage;
    }
    if (!strcmp(argv[0], "read") && argc > 2) {
        uint16_t offset = strtoul(argv[1], NULL, 0);
        size_t len = strtoul(argv[2], NULL, 0);
        uint8_t *buf = calloc(len, sizeof(uint8_t));
        I2CConfig i2cconfig = {
            OPMODE_I2C,
            100000,
            STD_DUTY_CYCLE,
        };
        i2cStart(&I2CD2, &i2cconfig);
        i2cAcquireBus(&I2CD2);
        i2cMasterTransmit(&I2CD2, 0x50, (uint8_t*)(&offset), sizeof(offset), buf, len);
        i2cReleaseBus(&I2CD2);
        i2cStop(&I2CD2);

        for (uint32_t i = 0; i < len; i++) {
            if (i % 0x10 == 0) chprintf(chp, "\r\n%04X:", i);
            chprintf(chp, " %02X", buf[i]);
        }
        chprintf(chp, "\r\n");

        free(buf);
    } else if (!strcmp(argv[0], "write") && argc > 3) {
        chprintf(chp, "Unimplemented\r\n");
    } else {
        goto fram_usage;
    }

    return;

fram_usage:
    chprintf(chp,  "Usage: fram <command>\r\n"
                   "    read <offset> <len>:\r\n"
                   "        Read starting at <offset> for <len> bytes\r\n"
                   "\r\n");
    return;
}

/*===========================================================================*/
/* Shell                                                                     */
/*===========================================================================*/
static const ShellCommand commands[] = {
    {"fw", cmd_fw},
    {"nmt", cmd_nmt},
    /*{"sdo", cmd_sdo},*/
    {"opd", cmd_opd},
    {"mmc", cmd_mmc},
    {"time", cmd_time},
    {"lfs", cmd_lfs},
    {"radio", cmd_radio},
    {"synth", cmd_synth},
    {"rf", cmd_rf},
    {"rftest", cmd_rftest},
    {"state", cmd_state},
    {"fram", cmd_fram},
    {"deploy", cmd_deploy},
    {NULL, NULL}
};

static char histbuf[SHELL_MAX_HIST_BUFF];

static const ShellConfig shell_cfg = {
    (BaseSequentialStream *)&SD3,
    commands,
    histbuf,
    sizeof(histbuf),
};

THD_WORKING_AREA(shell_wa, 0x1000);
THD_WORKING_AREA(cmd_wa, 0x100);
THD_FUNCTION(cmd, arg)
{
    (void)arg;

    /* Start a shell */
    while (!chThdShouldTerminateX()) {
        shell_tp = chThdCreateStatic(shell_wa, sizeof(shell_wa), NORMALPRIO, shellThread, (void *)&shell_cfg);
        chThdWait(shell_tp);
        chThdSleepMilliseconds(500);
    }

    chThdExit(MSG_OK);
}
