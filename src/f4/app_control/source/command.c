#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "CO_master.h"
#include "opd.h"
#include "max7310.h"
#include "chprintf.h"
#include "shell.h"

#ifndef BUF_SIZE
#define BUF_SIZE 0x10000 /* 64k */
#endif

#define SDC_BURST_SIZE      16

static uint8_t data[BUF_SIZE];
/* Buffer for block read/write operations, note that extra bytes are
   allocated in order to support unaligned operations.*/
static uint8_t buf[MMCSD_BLOCK_SIZE * SDC_BURST_SIZE + 4];

/* Additional buffer for sdcErase() test */
static uint8_t buf2[MMCSD_BLOCK_SIZE * SDC_BURST_SIZE ];

/*===========================================================================*/
/* CAN Network Management                                                    */
/*===========================================================================*/
void nmt_usage(BaseSequentialStream *chp)
{
    chprintf(chp, "Usage: nmt start|stop|preop|resetcomm|resetnode <NodeID>\r\n");
}

void cmd_nmt(BaseSequentialStream *chp, int argc, char *argv[])
{
    uint8_t node_id = 0;
    if (argc < 2) {
        nmt_usage(chp);
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
        nmt_usage(chp);
        return;
    }
}

/*===========================================================================*/
/* CAN SDO Master                                                            */
/*===========================================================================*/
void sdo_usage(BaseSequentialStream *chp)
{
    chprintf(chp, "Usage: sdo read|write <NodeID> <index> <subindex> [blockmode]\r\n");
}

void cmd_sdo(BaseSequentialStream *chp, int argc, char *argv[])
{
    uint32_t data_len = 0;
    uint32_t abrt_code = 0;
    uint8_t node_id = 0;
    uint16_t index = 0;
    uint8_t subindex = 0;
    bool block = false;

    if (argc < 4) {
        sdo_usage(chp);
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
        chprintf(chp, "Disabled for now\r\n");
        /*sdo_download(CO->SDOclient[0], node_id, index, subindex, data, data_len, &abrt_code, 1000, block);*/
    } else {
        sdo_usage(chp);
        return;
    }
}

/*===========================================================================*/
/* OreSat Power Domain Control                                               */
/*===========================================================================*/
void opd_usage(BaseSequentialStream *chp)
{
    chprintf(chp, "Usage: opd enable|disable|reset|reinit|status <opd_addr>\r\n");
}

void cmd_opd(BaseSequentialStream *chp, int argc, char *argv[])
{
    static opd_addr_t opd_addr = 0;
    opd_status_t status = {0};

    if (argc < 1) {
        opd_usage(chp);
        return;
    } else if (argc > 1) {
        opd_addr = strtoul(argv[1], NULL, 0);
        chprintf(chp, "Setting persistent board address to 0x%02X\r\n", opd_addr);
    } else if (opd_addr == 0) {
        chprintf(chp, "Please specify an OPD address at least once (it will persist)\r\n");
        opd_usage(chp);
        return;
    }

    if (!strcmp(argv[0], "enable")) {
        chprintf(chp, "Enabling board 0x%02X\r\n", opd_addr);
        opd_enable(opd_addr);
    } else if (!strcmp(argv[0], "disable")) {
        chprintf(chp, "Disabling board 0x%02X\r\n", opd_addr);
        opd_disable(opd_addr);
    } else if (!strcmp(argv[0], "reset")) {
        chprintf(chp, "Resetting board 0x%02X\r\n", opd_addr);
        opd_reset(opd_addr);
    } else if (!strcmp(argv[0], "reinit")) {
        chprintf(chp, "Reinitializing OPD\r\n", opd_addr);
        opd_stop();
        opd_init();
        opd_start();
    } else if (!strcmp(argv[0], "status")) {
        chprintf(chp, "Status of board 0x%02X: ", opd_addr);
        if (!opd_status(opd_addr, &status)) {
            chprintf(chp, "CONNECTED\r\n");
            chprintf(chp, "State: %s-%s\r\n",
                    (status.odr & MAX7310_PIN_MASK(OPD_LED) ? "ENABLED" : "DISABLED"),
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
    } else {
        opd_usage(chp);
        return;
    }
}

/*===========================================================================*/
/* SD Card Control                                                           */
/*===========================================================================*/
void cmd_sdc(BaseSequentialStream *chp, int argc, char *argv[]) {
  static const char *mode[] = {"SDV11", "SDV20", "MMC", NULL};
  systime_t start, end;
  uint32_t n, startblk;

  if (argc != 1) {
    chprintf(chp, "Usage: sdc read|write|erase|all\r\n");
    return;
  }

  /* Card presence check.*/
  if (!blkIsInserted(&SDCD1)) {
    chprintf(chp, "Card not inserted, aborting.\r\n");
    return;
  }

  /* Connection to the card.*/
  chprintf(chp, "Connecting... ");
  if (sdcConnect(&SDCD1)) {
    chprintf(chp, "failed\r\n");
    return;
  }

  chprintf(chp, "OK\r\n\r\nCard Info\r\n");
  chprintf(chp, "CSD      : %08X %8X %08X %08X \r\n",
           SDCD1.csd[3], SDCD1.csd[2], SDCD1.csd[1], SDCD1.csd[0]);
  chprintf(chp, "CID      : %08X %8X %08X %08X \r\n",
           SDCD1.cid[3], SDCD1.cid[2], SDCD1.cid[1], SDCD1.cid[0]);
  chprintf(chp, "Mode     : %s\r\n", mode[SDCD1.cardmode & 3U]);
  chprintf(chp, "Capacity : %DMB\r\n", SDCD1.capacity / 2048);

  /* The test is performed in the middle of the flash area.*/
  startblk = (SDCD1.capacity / MMCSD_BLOCK_SIZE) / 2;

  if ((strcmp(argv[0], "read") == 0) ||
      (strcmp(argv[0], "all") == 0)) {

    /* Single block read performance, aligned.*/
    chprintf(chp, "Single block aligned read performance:           ");
    start = chVTGetSystemTime();
    end = chTimeAddX(start, TIME_MS2I(1000));
    n = 0;
    do {
      if (blkRead(&SDCD1, startblk, buf, 1)) {
        chprintf(chp, "failed\r\n");
        goto exittest;
      }
      n++;
    } while (chVTIsSystemTimeWithin(start, end));
    chprintf(chp, "%D blocks/S, %D bytes/S\r\n", n, n * MMCSD_BLOCK_SIZE);

    /* Multiple sequential blocks read performance, aligned.*/
    chprintf(chp, "16 sequential blocks aligned read performance:   ");
    start = chVTGetSystemTime();
    end = chTimeAddX(start, TIME_MS2I(1000));
    n = 0;
    do {
      if (blkRead(&SDCD1, startblk, buf, SDC_BURST_SIZE)) {
        chprintf(chp, "failed\r\n");
        goto exittest;
      }
      n += SDC_BURST_SIZE;
    } while (chVTIsSystemTimeWithin(start, end));
    chprintf(chp, "%D blocks/S, %D bytes/S\r\n", n, n * MMCSD_BLOCK_SIZE);

#if STM32_SDC_SDIO_UNALIGNED_SUPPORT
    /* Single block read performance, unaligned.*/
    chprintf(chp, "Single block unaligned read performance:         ");
    start = chVTGetSystemTime();
    end = chTimeAddX(start, TIME_MS2I(1000));
    n = 0;
    do {
      if (blkRead(&SDCD1, startblk, buf + 1, 1)) {
        chprintf(chp, "failed\r\n");
        goto exittest;
      }
      n++;
    } while (chVTIsSystemTimeWithin(start, end));
    chprintf(chp, "%D blocks/S, %D bytes/S\r\n", n, n * MMCSD_BLOCK_SIZE);

    /* Multiple sequential blocks read performance, unaligned.*/
    chprintf(chp, "16 sequential blocks unaligned read performance: ");
    start = chVTGetSystemTime();
    end = chTimeAddX(start, TIME_MS2I(1000));
    n = 0;
    do {
      if (blkRead(&SDCD1, startblk, buf + 1, SDC_BURST_SIZE)) {
        chprintf(chp, "failed\r\n");
        goto exittest;
      }
      n += SDC_BURST_SIZE;
    } while (chVTIsSystemTimeWithin(start, end));
    chprintf(chp, "%D blocks/S, %D bytes/S\r\n", n, n * MMCSD_BLOCK_SIZE);
#endif /* STM32_SDC_SDIO_UNALIGNED_SUPPORT */
  }

  if ((strcmp(argv[0], "write") == 0) ||
      (strcmp(argv[0], "all") == 0)) {
    unsigned i;

    memset(buf, 0xAA, MMCSD_BLOCK_SIZE * 2);
    chprintf(chp, "Writing...");
    if(sdcWrite(&SDCD1, startblk, buf, 2)) {
      chprintf(chp, "failed\r\n");
      goto exittest;
    }
    chprintf(chp, "OK\r\n");

    memset(buf, 0x55, MMCSD_BLOCK_SIZE * 2);
    chprintf(chp, "Reading...");
    if (blkRead(&SDCD1, startblk, buf, 1)) {
      chprintf(chp, "failed\r\n");
      goto exittest;
    }
    chprintf(chp, "OK\r\n");

    for (i = 0; i < MMCSD_BLOCK_SIZE; i++)
      buf[i] = i + 8;
    chprintf(chp, "Writing...");
    if(sdcWrite(&SDCD1, startblk, buf, 2)) {
      chprintf(chp, "failed\r\n");
      goto exittest;
    }
    chprintf(chp, "OK\r\n");

    memset(buf, 0, MMCSD_BLOCK_SIZE * 2);
    chprintf(chp, "Reading...");
    if (blkRead(&SDCD1, startblk, buf, 1)) {
      chprintf(chp, "failed\r\n");
      goto exittest;
    }
    chprintf(chp, "OK\r\n");
  }

  if ((strcmp(argv[0], "erase") == 0) ||
      (strcmp(argv[0], "all") == 0)) {
    /**
     * Test sdcErase()
     * Strategy:
     *   1. Fill two blocks with non-constant data
     *   2. Write two blocks starting at startblk
     *   3. Erase the second of the two blocks
     *      3.1. First block should be equal to the data written
     *      3.2. Second block should NOT be equal too the data written (i.e. erased).
     *   4. Erase both first and second block
     *      4.1 Both blocks should not be equal to the data initially written
     * Precondition: SDC_BURST_SIZE >= 2
     */
    memset(buf, 0, MMCSD_BLOCK_SIZE * 2);
    memset(buf2, 0, MMCSD_BLOCK_SIZE * 2);
    /* 1. */
    unsigned int i = 0;
    for (; i < MMCSD_BLOCK_SIZE * 2; ++i) {
      buf[i] = (i + 7) % 'T'; //Ensure block 1/2 are not equal
    }
    /* 2. */
    if(sdcWrite(&SDCD1, startblk, buf, 2)) {
      chprintf(chp, "sdcErase() test write failed\r\n");
      goto exittest;
    }
    /* 3. (erase) */
    if(sdcErase(&SDCD1, startblk + 1, startblk + 2)) {
      chprintf(chp, "sdcErase() failed\r\n");
      goto exittest;
    }
    sdcflags_t errflags = sdcGetAndClearErrors(&SDCD1);
    if(errflags) {
      chprintf(chp, "sdcErase() yielded error flags: %d\r\n", errflags);
      goto exittest;
    }
    if(sdcRead(&SDCD1, startblk, buf2, 2)) {
      chprintf(chp, "single-block sdcErase() failed\r\n");
      goto exittest;
    }
    /* 3.1. */
    if(memcmp(buf, buf2, MMCSD_BLOCK_SIZE) != 0) {
      chprintf(chp, "sdcErase() non-erased block compare failed\r\n");
      goto exittest;
    }
    /* 3.2. */
    if(memcmp(buf + MMCSD_BLOCK_SIZE,
              buf2 + MMCSD_BLOCK_SIZE, MMCSD_BLOCK_SIZE) == 0) {
      chprintf(chp, "sdcErase() erased block compare failed\r\n");
      goto exittest;
    }
    /* 4. */
    if(sdcErase(&SDCD1, startblk, startblk + 2)) {
      chprintf(chp, "multi-block sdcErase() failed\r\n");
      goto exittest;
    }
    if(sdcRead(&SDCD1, startblk, buf2, 2)) {
      chprintf(chp, "single-block sdcErase() failed\r\n");
      goto exittest;
    }
    /* 4.1 */
    if(memcmp(buf, buf2, MMCSD_BLOCK_SIZE) == 0) {
      chprintf(chp, "multi-block sdcErase() erased block compare failed\r\n");
      goto exittest;
    }
    if(memcmp(buf + MMCSD_BLOCK_SIZE,
              buf2 + MMCSD_BLOCK_SIZE, MMCSD_BLOCK_SIZE) == 0) {
      chprintf(chp, "multi-block sdcErase() erased block compare failed\r\n");
      goto exittest;
    }
    /* END of sdcErase() test */
  }

  /* Card disconnect and command end.*/
exittest:
  sdcDisconnect(&SDCD1);
}


static const ShellCommand commands[] = {
    {"nmt", cmd_nmt},
    {"sdo", cmd_sdo},
    {"opd", cmd_opd},
    {"sdc", cmd_sdc},
    {NULL, NULL}
};

static const ShellConfig shell_cfg = {
    (BaseSequentialStream *)&SD2,
    commands
};

THD_WORKING_AREA(shell_wa, 0x200);
THD_WORKING_AREA(cmd_wa, 0x200);
THD_FUNCTION(cmd, arg)
{
    (void)arg;

    while (!chThdShouldTerminateX()) {
        thread_t *shell_tp = chThdCreateStatic(shell_wa, sizeof(shell_wa), NORMALPRIO, shellThread, (void *)&shell_cfg);
        chThdWait(shell_tp);
        chThdSleepMilliseconds(500);
    }

    chThdExit(MSG_OK);
}
