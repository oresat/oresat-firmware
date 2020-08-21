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

static lfs_t lfs;
static lfs_file_t file;

int mmc_read(const struct lfs_config *cfg, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size)
{
    SDCDriver *sdcp = cfg->context;
    uint8_t *buf;

    /* Sanity checks */
    chDbgCheck(off % cfg->read_size == 0);
    chDbgCheck(size % cfg->read_size == 0);
    chDbgCheck(off + size <= cfg->block_size);
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
    chDbgCheck(off + size <= cfg->block_size);
    chDbgCheck(block < cfg->block_count);

    /* Allocate buffer */
    buf = malloc(cfg->block_size);
    if (buf == NULL) {
        return LFS_ERR_NOMEM;
    }

    /* Read the current data from the block */
    mmc_read(cfg, block, 0, buf, cfg->block_size);

    /* Copy new data */
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
    uint8_t *buf;

    /* Sanity checks */
    chDbgCheck(block < cfg->block_count);

    /* Allocate buffer */
    buf = malloc(cfg->block_size);
    memset(buf, 0xFF, cfg->block_size);
    if (buf == NULL) {
        return LFS_ERR_NOMEM;
    }

    /* Write data to block */
    if (blkWrite(sdcp, block, buf, 1) != HAL_SUCCESS) {
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
    static BlockDeviceInfo bdinfo;
    static unpacked_mmc_cid_t cid;
    static unpacked_mmc_csd_t csd;
    systime_t start, end;
    uint32_t n, startblk;

    if (argc != 1) {
        chprintf(chp,  "Usage: mmc <command>\r\n"
                       "    enable:     Enable eMMC subsystem\r\n"
                       "    disable:    Disable eMMC subsystem\r\n"
                       "\r\n"
                       "    mount:      Mount LFS\r\n"
                       "    unmount:    Unmount LFS\r\n"
                       "    format:     Format eMMC for LFS\r\n"
                       "\r\n"
                       "    testread:   Test read functionality\r\n"
                       "    testwrite:  Test write functionality\r\n"
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
        _mmcsd_unpack_mmc_cid((MMCSDBlockDevice*)&SDCD1, &cid);
        _mmcsd_unpack_csd_mmc((MMCSDBlockDevice*)&SDCD1, &csd);

        chprintf(chp, "OK\r\n\r\nDevice Info\r\n");
        chprintf(chp, "CSD      : %08X %8X %08X %08X \r\n",
                SDCD1.csd[3], SDCD1.csd[2], SDCD1.csd[1], SDCD1.csd[0]);
        chprintf(chp, "CID      : %08X %8X %08X %08X \r\n",
                SDCD1.cid[3], SDCD1.cid[2], SDCD1.cid[1], SDCD1.cid[0]);
        chprintf(chp, "Capacity : %DMB\r\n", SDCD1.capacity / 2048);
        chprintf(chp, "BlockSize: %d\r\n", bdinfo.blk_size);
        chprintf(chp, "BlockCnt : %d\r\n", bdinfo.blk_num);

        /* Clear error flags from connecting */
        sdcGetAndClearErrors(&SDCD1);
        return;
    } else if (strcmp(argv[0], "disable") == 0) {
        chprintf(chp, "Disabling eMMC... ");

        /* Disconnect from eMMC device */
        blkDisconnect(&SDCD1);

        /* Stop MMC SDC interface */
        sdcStop(&SDCD1);

        /* Disable power to eMMC */
        palSetLine(LINE_MMC_PWR);

        chprintf(chp, "OK\r\n");
        return;
    }

    if (SDCD1.state != BLK_READY) {
        chprintf(chp, "Error: Please enable eMMC subsystem first\r\n");
        return;
    }

    if (!strcmp(argv[0], "mount")) {
        int err;

        chprintf(chp, "Attempting to mount LFS...\r\n");
        err = lfs_mount(&lfs, &lfscfg);
        if (err) {
            chprintf(chp, "Mount failed: %d\r\n", err);
            return;
        }
        chprintf(chp, "OK\r\n");
    } else if (!strcmp(argv[0], "unmount")) {
        int err;

        chprintf(chp, "Attempting to unmount LFS...\r\n");
        err = lfs_unmount(&lfs);
        if (err) {
            chprintf(chp, "Unmount failed: %d\r\n", err);
            return;
        }
        chprintf(chp, "OK\r\n");
    } else if (!strcmp(argv[0], "format")) {
        int err;

        chprintf(chp, "Attempting to format LFS...\r\n");
        err = lfs_format(&lfs, &lfscfg);
        if (err) {
            chprintf(chp, "Format failed: %d\r\n", err);
            return;
        }
        chprintf(chp, "OK\r\n");
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
        uint8_t backup[MMCSD_BLOCK_SIZE * 2];

        /* Backup data */
        blkRead(&SDCD1, startblk, backup, 2);

        memset(buf, 0xAA, MMCSD_BLOCK_SIZE * 2);
        chprintf(chp, "Writing...");
        if(blkWrite(&SDCD1, startblk, buf, 2)) {
            chprintf(chp, "failed\r\n");
            return;
        }
        chprintf(chp, "OK\r\n");

        memset(buf2, 0x55, MMCSD_BLOCK_SIZE * 2);
        chprintf(chp, "Reading...");
        if (blkRead(&SDCD1, startblk, buf2, 1)) {
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
        if(blkWrite(&SDCD1, startblk, buf, 2)) {
            chprintf(chp, "failed\r\n");
            return;
        }
        chprintf(chp, "OK\r\n");

        memset(buf2, 0, MMCSD_BLOCK_SIZE * 2);
        chprintf(chp, "Reading...");
        if (blkRead(&SDCD1, startblk, buf2, 1)) {
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
        blkWrite(&SDCD1, startblk, backup, 2);
    }
}
