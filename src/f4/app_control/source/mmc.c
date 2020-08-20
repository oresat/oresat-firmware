#include <stdlib.h>
#include <string.h>

#include "mmc.h"
#include "lfs.h"
#include "chprintf.h"

#define SDC_BURST_SIZE      16

/*
 * SDIO configuration.
 */
static const SDCConfig sdccfg = {
  SDC_MODE_4BIT
};

int mmc_read(const struct lfs_config *cfg, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size)
{
    SDCDriver *sdcp = cfg->context;
    uint8_t *buf;

    /* Sanity checks */
    chDbgCheck(off % cfg->read_size == 0);
    chDbgCheck(size % cfg->read_size == 0);
    chDbgCheck(off + size < cfg->block_size);
    chDbgCheck(block < cfg->block_count);

    /* Allocate buffer */
    buf = calloc(cfg->block_size, sizeof(uint8_t));
    if (buf == NULL) {
        return LFS_ERR_NOMEM;
    }

    /* Read data from block */
    if (blkRead(sdcp, block, buf, 1) != HAL_SUCCESS) {
        return LFS_ERR_IO;
    }

    /* Copy the requested data to the buffer */
    memcpy(buffer, &buf[off], size);

    /* Free temporary buffer */
    free(buf);

    return LFS_ERR_OK;
}

int mmc_prog(const struct lfs_config *cfg, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size)
{
    SDCDriver *sdcp = cfg->context;
    uint8_t *buf;

    /* Sanity checks */
    chDbgCheck(off % cfg->read_size == 0);
    chDbgCheck(size % cfg->read_size == 0);
    chDbgCheck(off + size < cfg->block_size);
    chDbgCheck(block < cfg->block_count);

    /* Allocate buffer */
    buf = calloc(cfg->block_size, sizeof(uint8_t));
    if (buf == NULL) {
        return LFS_ERR_NOMEM;
    }

    /* Copy data to temp buffer */
    memcpy(&buf[off], buffer, size);

    /* Write data to block */
    if (blkWrite(sdcp, block, buf, 1) != HAL_SUCCESS) {
        return LFS_ERR_IO;
    }

    /* Free temporary buffer */
    free(buf);

    return LFS_ERR_OK;
}

int mmc_erase(const struct lfs_config *cfg, lfs_block_t block)
{
    SDCDriver *sdcp = cfg->context;

    if (sdcErase(sdcp, block, block) != HAL_SUCCESS) {
        return LFS_ERR_IO;
    }

    return LFS_ERR_OK;
}

int mmc_sync(const struct lfs_config *cfg)
{
    SDCDriver *sdcp = cfg->context;

    if (blkSync(sdcp) != HAL_SUCCESS) {
        return LFS_ERR_IO;
    }

    return LFS_ERR_OK;
}

/*
 * LFS configuration.
 */
static struct lfs_config lfscfg = {
    .context = &SDCD1,
    /* Block device operations */
    .read  = mmc_read,
    .prog  = mmc_prog,
    .erase = mmc_erase,
    .sync  = mmc_sync,

    /* Block device configuration */
    .read_size = 16,                /* TODO: Check these values */
    .prog_size = 16,                /* TODO: Check these values */
    .block_cycles = -1,             /* Disable wear leveling by LFS */
    .cache_size = 16,               /* TODO: Check these values */
    .lookahead_size = 16,           /* TODO: Check these values */
};

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
    static BlockDeviceInfo bdinfo;
    systime_t start, end;
    uint32_t n, startblk;

    if (argc != 1) {
        chprintf(chp, "Usage: mmc <command>\r\n"
                      "    enable:     Enable eMMC subsystem\r\n"
                      "    disable:    Disable eMMC subsystem\r\n"
                      "\r\n"
                      "    testread:   Test read functionality\r\n"
                      "    testwrite:  Test write functionality\r\n"
                      "    testerase:  Test erase functionality\r\n"
                      "    testall:    Test all functionality\r\n");
        return;
    }

    if (strcmp(argv[0], "enable") == 0) {
        chprintf(chp, "Enabling eMMC... ");

        /* Enable power to eMMC */
        palClearLine(LINE_MMC_PWR);

        /* Initializes MMC SDC interface */
        sdcStart(&SDCD1, &sdccfg);

        /* Connect to eMMC device */
        if (blkConnect(&SDCD1)) {
            chprintf(chp, "failed\r\n");
            return;
        }

        /* Fetch info about eMMC device */
        blkGetInfo(&SDCD1, &bdinfo);
        lfscfg.block_size = bdinfo.blk_size;
        lfscfg.block_count = bdinfo.blk_num;

        chprintf(chp, "OK\r\n\r\nCard Info\r\n");
        chprintf(chp, "CSD      : %08X %8X %08X %08X \r\n",
                SDCD1.csd[3], SDCD1.csd[2], SDCD1.csd[1], SDCD1.csd[0]);
        chprintf(chp, "CID      : %08X %8X %08X %08X \r\n",
                SDCD1.cid[3], SDCD1.cid[2], SDCD1.cid[1], SDCD1.cid[0]);
        chprintf(chp, "Mode     : %s\r\n", mode[SDCD1.cardmode & 3U]);
        chprintf(chp, "Capacity : %DMB\r\n", SDCD1.capacity / 2048);
        chprintf(chp, "BlockSize: %d\r\n", bdinfo.blk_size);
        chprintf(chp, "BlockCnt : %d\r\n", bdinfo.blk_num);


        chprintf(chp, "done!\r\n");
        return;
    } else if (strcmp(argv[0], "disable") == 0) {
        chprintf(chp, "Disabling eMMC... ");

        /* Disconnect from eMMC device */
        blkDisconnect(&SDCD1);

        /* Stop MMC SDC interface */
        sdcStop(&SDCD1);

        /* Disable power to eMMC */
        palSetLine(LINE_MMC_PWR);

        chprintf(chp, "done!\r\n");
        return;
    }

    if (SDCD1.state != BLK_READY) {
        chprintf(chp, "Error: Please enable eMMC subsystem first\r\n");
        return;
    }

    /* The test is performed in the middle of the flash area.*/
    startblk = (SDCD1.capacity / MMCSD_BLOCK_SIZE) / 2;

    if ((strcmp(argv[0], "testread") == 0) ||
        (strcmp(argv[0], "testall") == 0)) {

        /* Single block read performance, aligned.*/
        chprintf(chp, "Single block aligned read performance:           ");
        start = chVTGetSystemTime();
        end = chTimeAddX(start, TIME_MS2I(1000));
        n = 0;
        do {
            if (blkRead(&SDCD1, startblk, buf, 1)) {
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
            if (blkRead(&SDCD1, startblk, buf, SDC_BURST_SIZE)) {
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
            if (blkRead(&SDCD1, startblk, buf + 1, 1)) {
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
            if (blkRead(&SDCD1, startblk, buf + 1, SDC_BURST_SIZE)) {
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
        unsigned i;

        memset(buf, 0xAA, MMCSD_BLOCK_SIZE * 2);
        chprintf(chp, "Writing...");
        if(blkWrite(&SDCD1, startblk, buf, 2)) {
            chprintf(chp, "failed\r\n");
            return;
        }
        chprintf(chp, "OK\r\n");

        memset(buf, 0x55, MMCSD_BLOCK_SIZE * 2);
        chprintf(chp, "Reading...");
        if (blkRead(&SDCD1, startblk, buf, 1)) {
            chprintf(chp, "failed\r\n");
            return;
        }
        chprintf(chp, "OK\r\n");

        for (i = 0; i < MMCSD_BLOCK_SIZE; i++)
            buf[i] = i + 8;
        chprintf(chp, "Writing...");
        if(blkWrite(&SDCD1, startblk, buf, 2)) {
            chprintf(chp, "failed\r\n");
            return;
        }
        chprintf(chp, "OK\r\n");

        memset(buf, 0, MMCSD_BLOCK_SIZE * 2);
        chprintf(chp, "Reading...");
        if (blkRead(&SDCD1, startblk, buf, 1)) {
            chprintf(chp, "failed\r\n");
            return;
        }
        chprintf(chp, "OK\r\n");
    }

    if ((strcmp(argv[0], "testerase") == 0) ||
        (strcmp(argv[0], "testall") == 0)) {
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
        if(blkWrite(&SDCD1, startblk, buf, 2)) {
            chprintf(chp, "sdcErase() test write failed\r\n");
            return;
        }
        /* 3. (erase) */
        if(sdcErase(&SDCD1, startblk + 1, startblk + 2)) {
            chprintf(chp, "sdcErase() failed\r\n");
            return;
        }
        sdcflags_t errflags = sdcGetAndClearErrors(&SDCD1);
        if(errflags) {
            chprintf(chp, "sdcErase() yielded error flags: %d\r\n", errflags);
            return;
        }
        if(blkRead(&SDCD1, startblk, buf2, 2)) {
            chprintf(chp, "single-block mmcErase() failed\r\n");
            return;
        }
        /* 3.1. */
        if(memcmp(buf, buf2, MMCSD_BLOCK_SIZE) != 0) {
            chprintf(chp, "sdcErase() non-erased block compare failed\r\n");
            return;
        }
        /* 3.2. */
        if(memcmp(buf + MMCSD_BLOCK_SIZE,
                    buf2 + MMCSD_BLOCK_SIZE, MMCSD_BLOCK_SIZE) == 0) {
            chprintf(chp, "sdcErase() erased block compare failed\r\n");
            return;
        }
        /* 4. */
        if(sdcErase(&SDCD1, startblk, startblk + 2)) {
            chprintf(chp, "multi-block sdcErase() failed\r\n");
            return;
        }
        if(blkRead(&SDCD1, startblk, buf2, 2)) {
            chprintf(chp, "single-block sdcErase() failed\r\n");
            return;
        }
        /* 4.1 */
        if(memcmp(buf, buf2, MMCSD_BLOCK_SIZE) == 0) {
            chprintf(chp, "multi-block sdcErase() erased block compare failed\r\n");
            return;
        }
        if(memcmp(buf + MMCSD_BLOCK_SIZE,
                  buf2 + MMCSD_BLOCK_SIZE, MMCSD_BLOCK_SIZE) == 0) {
            chprintf(chp, "multi-block sdcErase() erased block compare failed\r\n");
            return;
        }
        /* END of sdcErase() test */
    }
}
