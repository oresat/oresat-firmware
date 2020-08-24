#include <string.h>

#include "ch.h"
#include "hal.h"
#include "test_mmc.h"
#include "chprintf.h"
#include "mmc.h"

#define SDC_BURST_SIZE      16

/* Buffer for block read/write operations, note that extra bytes are
   allocated in order to support unaligned operations.*/
static uint8_t buf[MMCSD_BLOCK_SIZE * SDC_BURST_SIZE + 4];

/* Additional buffer for sdcErase() test */
static uint8_t buf2[MMCSD_BLOCK_SIZE * SDC_BURST_SIZE ];

/*===========================================================================*/
/* eMMC Testing                                                              */
/*===========================================================================*/
void cmd_mmc(BaseSequentialStream *chp, int argc, char *argv[]) {
    systime_t start, end;
    uint32_t n, startblk;

    if (argc < 1) {
        chprintf(chp,  "Usage: mmc <command>\r\n"
                       "    enable:             Enable eMMC subsystem\r\n"
                       "    disable:            Disable eMMC subsystem\r\n"
                       "\r\n"
                       "    mount:              Mount LFS\r\n"
                       "    unmount:            Unmount LFS\r\n"
                       "    format:             Format eMMC for LFS\r\n"
                       "\r\n"
                       "    testread:           Test read functionality\r\n"
                       "    testwrite:          Test write functionality\r\n"
                       "    testall:            Test all functionality\r\n");
        return;
    }

    if (strcmp(argv[0], "enable") == 0) {
        int err;
        chprintf(chp, "Enabling eMMC... ");

        /* Attempt to enable eMMC subsystem */
        err = mmc_enable();
        if (err) {
            if (SDC->state != BLK_STOP) {
                chprintf(chp, "LFS mount failed: %d\r\n", err);
            } else {
                chprintf(chp, "failed\r\n");
                return;
            }
        }

        /* Print details of the device */
        chprintf(chp, "OK\r\n\r\nDevice Info\r\n");
        chprintf(chp, "CSD      : %08X %8X %08X %08X \r\n",
                SDC->csd[3], SDC->csd[2], SDC->csd[1], SDC->csd[0]);
        chprintf(chp, "CID      : %08X %8X %08X %08X \r\n",
                SDC->cid[3], SDC->cid[2], SDC->cid[1], SDC->cid[0]);
        chprintf(chp, "Capacity : %DMB\r\n", SDC->capacity / 2048);
        chprintf(chp, "\r\n");

        return;
    } else if (strcmp(argv[0], "disable") == 0) {
        chprintf(chp, "Disabling eMMC... ");

        /* Disable eMMC subsystem */
        mmc_disable();

        chprintf(chp, "OK\r\n");
        return;
    }

    if (SDC->state != BLK_READY) {
        chprintf(chp, "Error: Please enable eMMC subsystem first\r\n");
        return;
    }

    if (!strcmp(argv[0], "mount")) {
        int err;

        chprintf(chp, "Attempting to mount LFS...\r\n");
        err = lfs_mount(&lfs, &lfscfg);
        if (err < 0) {
            chprintf(chp, "Mount failed: %d\r\n", err);
            return;
        }
        chprintf(chp, "OK\r\n");
    } else if (!strcmp(argv[0], "unmount")) {
        int err;

        chprintf(chp, "Attempting to unmount LFS...\r\n");
        err = lfs_unmount(&lfs);
        if (err < 0) {
            chprintf(chp, "Unmount failed: %d\r\n", err);
            return;
        }
        chprintf(chp, "OK\r\n");
    } else if (!strcmp(argv[0], "format")) {
        int err;

        chprintf(chp, "Attempting to format LFS...\r\n");
        err = lfs_format(&lfs, &lfscfg);
        if (err < 0) {
            chprintf(chp, "Format failed: %d\r\n", err);
            return;
        }
        chprintf(chp, "OK\r\n");
    }

    /* The test is performed in the middle of the flash area.*/
    startblk = (SDC->capacity / MMCSD_BLOCK_SIZE) / 2;
    if ((strcmp(argv[0], "testread") == 0) ||
        (strcmp(argv[0], "testall") == 0)) {

        /* Single block read performance, aligned.*/
        chprintf(chp, "Single block aligned read performance:           ");
        start = chVTGetSystemTime();
        end = chTimeAddX(start, TIME_MS2I(1000));
        n = 0;
        do {
            if (blkRead(SDC, startblk, buf, 1)) {
                chprintf(chp, "failed\r\n");
                return;
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
            if (blkRead(SDC, startblk, buf, SDC_BURST_SIZE)) {
                chprintf(chp, "failed\r\n");
                return;
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
            if (blkRead(SDC, startblk, buf + 1, 1)) {
                chprintf(chp, "failed\r\n");
                return;
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
            if (blkRead(SDC, startblk, buf + 1, SDC_BURST_SIZE)) {
                chprintf(chp, "failed\r\n");
                return;
            }
            n += SDC_BURST_SIZE;
        } while (chVTIsSystemTimeWithin(start, end));
        chprintf(chp, "%D blocks/S, %D bytes/S\r\n", n, n * MMCSD_BLOCK_SIZE);
#endif /* STM32_SDC_SDIO_UNALIGNED_SUPPORT */
    }

    if ((strcmp(argv[0], "testwrite") == 0) ||
        (strcmp(argv[0], "testall") == 0)) {
        uint8_t backup[MMCSD_BLOCK_SIZE * 2];

        /* Backup data */
        blkRead(SDC, startblk, backup, 2);

        memset(buf, 0xAA, MMCSD_BLOCK_SIZE * 2);
        chprintf(chp, "Writing...");
        if(blkWrite(SDC, startblk, buf, 2)) {
            chprintf(chp, "failed\r\n");
            return;
        }
        chprintf(chp, "OK\r\n");

        memset(buf2, 0x55, MMCSD_BLOCK_SIZE * 2);
        chprintf(chp, "Reading...");
        if (blkRead(SDC, startblk, buf2, 1)) {
            chprintf(chp, "failed\r\n");
            return;
        }
        chprintf(chp, "OK\r\n");

        chprintf(chp, "Comparing...");
        if(memcmp(buf, buf2, MMCSD_BLOCK_SIZE) != 0) {
            chprintf(chp, "Compare failed\r\n");
            return;
        }
        chprintf(chp, "OK\r\n");

        for (unsigned int i = 0; i < MMCSD_BLOCK_SIZE; i++) {
            buf[i] = i + 8;
        }
        chprintf(chp, "Writing...");
        if(blkWrite(SDC, startblk, buf, 2)) {
            chprintf(chp, "failed\r\n");
            return;
        }
        chprintf(chp, "OK\r\n");

        memset(buf2, 0, MMCSD_BLOCK_SIZE * 2);
        chprintf(chp, "Reading...");
        if (blkRead(SDC, startblk, buf2, 1)) {
            chprintf(chp, "failed\r\n");
            return;
        }
        chprintf(chp, "OK\r\n");

        chprintf(chp, "Comparing...");
        if(memcmp(buf, buf2, MMCSD_BLOCK_SIZE) != 0) {
            chprintf(chp, "Compare failed\r\n");
            return;
        }
        chprintf(chp, "OK\r\n");

        /* Restore data */
        blkWrite(SDC, startblk, backup, 2);
    }
}
