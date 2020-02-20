#include <stdlib.h>
#include <string.h>

#include "mmc.h"
#include "chprintf.h"

#define SDC_BURST_SIZE      16

/* Buffer for block read/write operations, note that extra bytes are
   allocated in order to support unaligned operations.*/
static uint8_t buf[MMCSD_BLOCK_SIZE * SDC_BURST_SIZE + 4];

/* Additional buffer for sdcErase() test */
static uint8_t buf2[MMCSD_BLOCK_SIZE * SDC_BURST_SIZE ];

/*===========================================================================*/
/* SD Card Control                                                           */
/*===========================================================================*/
void cmd_mmc(BaseSequentialStream *chp, int argc, char *argv[]) {
    static const char *mode[] = {"SDV11", "SDV20", "MMC", NULL};
    systime_t start, end;
    uint32_t n, startblk;

    if (argc != 1) {
        chprintf(chp, "Usage: mmc read|write|erase|all\r\n");
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
            chprintf(chp, "single-block mmcErase() failed\r\n");
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
