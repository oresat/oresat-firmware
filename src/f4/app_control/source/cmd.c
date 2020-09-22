#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "cmd.h"
#include "opd.h"
#include "CO_master.h"
#include "time_sync.h"
#include "max7310.h"
#include "mmc.h"
#include "test_mmc.h"
#include "test_radio.h"
#include "chprintf.h"
#include "shell.h"

#define BUF_SIZE 256

struct cb_arg {
    lfs_file_t file;
    char buf[BUF_SIZE];
};

static thread_t *shell_tp;

/*===========================================================================*/
/* Support functions                                                         */
/*===========================================================================*/
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
            size = lfs_file_read(&lfs, &data->file, data->buf, lfs_min(space, BUF_SIZE));
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
                lfs_file_write(&lfs, &data->file, data->buf, size);
            } while (size);
        }
    }

    return false;
}

/*===========================================================================*/
/* OreSat CAN Bus SDO Client                                                 */
/*===========================================================================*/
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
    if (SDC->state != BLK_READY) {
        chprintf(chp, "Error: Please enable eMMC first\r\n");
        return;
    }

    /* Set variables from provided values */
    node_id = strtoul(argv[1], NULL, 0);
    index = strtoul(argv[2], NULL, 0);
    subindex = strtoul(argv[3], NULL, 0);

    err = lfs_file_open(&lfs, &data.file, argv[4], LFS_O_RDWR | LFS_O_CREAT);
    if (err) {
        chprintf(chp, "Error in file open: %d\r\n", err);
        goto sdo_usage;
    }
    if (argv[0][0] == 'w') {
        size = lfs_file_size(&lfs, &data.file);
    }

    chprintf(chp, "Initiating transfer... ");
    tp = sdo_transfer(argv[0][0], node_id, index, subindex, size, sdo_file_cb, &data);
    if (tp == NULL) {
        chprintf(chp, "Failed to initiate transfer\r\n");
        return;
    }
    chThdWait(tp);
    lfs_file_close(&lfs, &data.file);
    chprintf(chp, "Done!\r\n");
    return;

sdo_usage:
    chprintf(chp, "Usage: sdo (r)ead|(w)rite <node_id> <index> <subindex> <filename>\r\n");
    return;
}

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
        } else if (!strcmp(argv[0], "probe")) {
            chprintf(chp, "Probing board 0x%02X: ", opd_addr);
            if (opd_probe(opd_addr)) {
                chprintf(chp, "CONNECTED\r\n");
            } else {
                chprintf(chp, "NOT CONNECTED\r\n");
            }
        } else if (!strcmp(argv[0], "status")) {
            chprintf(chp, "Status of board 0x%02X: ", opd_addr);
            if (!opd_status(opd_addr, &status)) {
                chprintf(chp, "CONNECTED\r\n");
                chprintf(chp, "State: %s-%s\r\n",
                        (status.odr & MAX7310_PIN_MASK(OPD_EN) ? "ENABLED" : "DISABLED"),
                        (status.input & MAX7310_PIN_MASK(OPD_FAULT) ? "TRIPPED" : "NOT TRIPPED"));
                chprintf(chp, "Raw register values:\r\n");
                chprintf(chp, "Input:       %02X\r\n", status.input);
                chprintf(chp, "Output:      %02X\r\n", status.odr);
                chprintf(chp, "Polarity:    %02X\r\n", status.pol);
                chprintf(chp, "Mode:        %02X\r\n", status.mode);
                chprintf(chp, "Timeout:     %02X\r\n", status.timeout);
            } else {
                chprintf(chp, "NOT CONNECTED\r\n");
            }
        } else if (!strcmp(argv[0], "summary")) {
            chprintf(chp, "Board summary:\r\n");
            for (i2caddr_t i = MAX7310_MIN_ADDR; i <= MAX7310_MAX_ADDR; i++) {
                if (!opd_status(i, &status)) {
                    chprintf(chp, "0x%02X: CONNECTED - %s - %s\r\n", i,
                            (status.odr & MAX7310_PIN_MASK(OPD_EN) ? "ENABLED" : "DISABLED"),
                            (status.input & MAX7310_PIN_MASK(OPD_FAULT) ? "TRIPPED" : "NOT TRIPPED"));
                } else {
                    chprintf(chp, "0x%02X: NOT CONNECTED\r\n", i);
                }
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
                  "    enable:     Enable an OPD attached card\r\n"
                  "    disable:    Disable an OPD attached card\r\n"
                  "    reset:      Reset the circuit breaker of a card\r\n"
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
            unix_time = get_time_unix(&msec);
            chprintf(chp, "UNIX Time: %s\r\n", ctime(&unix_time));
        } else if (!strcmp(argv[1], "set") && argc > 2) {
            set_time_unix(strtoul(argv[2], NULL, 0), 0);
        } else {
            goto time_usage;
        }
    } else if (!strcmp(argv[0], "scet")) {
        if (!strcmp(argv[1], "get")) {
            get_time_scet(&scet);
            chprintf(chp, "SCET Time: %u.%u\r\n", scet.coarse, scet.fine);
        } else if (!strcmp(argv[1], "set") && argc > 3) {
            scet.coarse = strtoul(argv[2], NULL, 0);
            scet.fine = strtoul(argv[3], NULL, 0);
            set_time_scet(&scet);
        } else {
            goto time_usage;
        }
    } else if (!strcmp(argv[0], "utc")) {
        if (!strcmp(argv[1], "get")) {
            get_time_utc(&utc);
            chprintf(chp, "UTC Time: Day: %u ms: %u us: %u\r\n", utc.day, utc.ms, utc.us);
        } else if (!strcmp(argv[1], "set") && argc > 4) {
            utc.day = strtoul(argv[2], NULL, 0);
            utc.ms = strtoul(argv[3], NULL, 0);
            utc.us = strtoul(argv[4], NULL, 0);
            set_time_utc(&utc);
        } else {
            goto time_usage;
        }
    } else if (!strcmp(argv[0], "raw")) {
        rtcGetTime(&RTCD1, &timespec);
        chprintf(chp, "Year: %u Month: %u DST: %u DoW: %u Day: %u ms: %u\r\n", timespec.year, timespec.month, timespec.dstflag, timespec.dayofweek, timespec.day, timespec.millisecond);
    } else {
        goto time_usage;
    }

    return;

time_usage:
    chprintf(chp, "Usage: time unix|scet|utc|raw get|set <values>\r\n");
    return;
}

/*===========================================================================*/
/* OreSat CAN Bus SDO Client                                                 */
/*===========================================================================*/
void cmd_lfs(BaseSequentialStream *chp, int argc, char *argv[])
{
    int err;
    lfs_file_t file;
    lfs_dir_t dir;
    struct lfs_info info;
    char buf[BUF_SIZE];

    if (argc < 2) {
        goto lfs_usage;
    }
    if (SDC->state != BLK_READY) {
        chprintf(chp, "Error: Please enable eMMC first\r\n");
        return;
    }

    if (!strcmp(argv[0], "ls")) {
        err = lfs_dir_open(&lfs, &dir, argv[1]);
        if (err < 0) {
            chprintf(chp, "Error in lfs_dir_open: %d\r\n", err);
            return;
        }
        do {
            err = lfs_dir_read(&lfs, &dir, &info);
            if (err <= 0) {
                if (err < 0) {
                    chprintf(chp, "Error in lfs_dir_read: %d\r\n", err);
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
            chprintf(chp, "%s\r\n", info.name);
        } while (err > 0);
        err = lfs_dir_close(&lfs, &dir);
        if (err < 0) {
            chprintf(chp, "Error in lfs_dir_close: %d\r\n", err);
            return;
        }
    } else if (!strcmp(argv[0], "mkdir")) {
        err = lfs_mkdir(&lfs, argv[1]);
        if (err < 0) {
            chprintf(chp, "Error in lfs_mkdir: %d\r\n");
            return;
        }
    } else if (!strcmp(argv[0], "rm")) {
        err = lfs_remove(&lfs, argv[1]);
        if (err < 0) {
            chprintf(chp, "Error in lfs_remove: %d\r\n");
            return;
        }
    } else if (!strcmp(argv[0], "cat")) {
        err = lfs_file_open(&lfs, &file, argv[1], LFS_O_RDONLY);
        if (err < 0) {
            chprintf(chp, "Error in lfs_file_open: %d\r\n", err);
            return;
        }

        err = lfs_file_read(&lfs, &file, buf, BUF_SIZE - 1);
        if (err < 0) {
            chprintf(chp, "Error in lfs_file_read: %d\r\n", err);
            return;
        }
        buf[err] = '\0';
        chprintf(chp, "%s\r\n", buf);

        err = lfs_file_close(&lfs, &file);
        if (err < 0) {
            chprintf(chp, "Error in lfs_file_close: %d\r\n", err);
            return;
        }
    } else {
        goto lfs_usage;
    }

    return;

lfs_usage:
    chprintf(chp,  "Usage: lfs <command>\r\n");
    return;
}

/*===========================================================================*/
/* Shell                                                                     */
/*===========================================================================*/
static const ShellCommand commands[] = {
    {"radio", cmd_radio},
    {"sdo", cmd_sdo},
    {"opd", cmd_opd},
    {"mmc", cmd_mmc},
    {"time", cmd_time},
    {"lfs", cmd_lfs},
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
THD_WORKING_AREA(cmd_wa, 0x200);
THD_FUNCTION(cmd, arg)
{
    (void)arg;

    radio_init();

    /* Start a shell */
    while (!chThdShouldTerminateX()) {
        shell_tp = chThdCreateStatic(shell_wa, sizeof(shell_wa), NORMALPRIO, shellThread, (void *)&shell_cfg);
        chThdWait(shell_tp);
        chThdSleepMilliseconds(500);
    }

    chThdExit(MSG_OK);
}
