#include <stdlib.h>
#include <string.h>

#include "ch.h"
#include "hal.h"
#include "mmc.h"

/*
 * SDIO configuration.
 */
static const SDCConfig sdccfg = {
  SDC_MODE_4BIT
};

unpacked_mmc_cid_t mmc_cid;
unpacked_mmc_csd_t mmc_csd;

/*
 * LFS object and configuration.
 */
lfs_t lfs;

struct lfs_config lfscfg = {
    .context = SDC,
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

/*===========================================================================*/
/* eMMC Support Functions                                                    */
/*===========================================================================*/
int mmc_enable(void)
{
    BlockDeviceInfo bdinfo;

    /* Enable power to eMMC */
    palClearLine(LINE_MMC_PWR);

    /* Initializes MMC SDC interface */
    sdcStart(SDC, &sdccfg);

    /* Connect to eMMC device */
    if (blkConnect(SDC)) {
        sdcStop(SDC);
        palSetLine(LINE_MMC_PWR);
        return LFS_ERR_IO;
    }

    /* Clear error flags from connecting */
    sdcGetAndClearErrors(SDC);

    /* Retrieve block information */
    blkGetInfo(SDC, &bdinfo);
    lfscfg.block_size = bdinfo.blk_size;
    lfscfg.block_count = bdinfo.blk_num;

    /* Fetch info about eMMC device */
    _mmcsd_unpack_mmc_cid((MMCSDBlockDevice*)SDC, &mmc_cid);
    _mmcsd_unpack_csd_mmc((MMCSDBlockDevice*)SDC, &mmc_csd);

    /* Mount LFS file system and return status */
    return lfs_mount(&lfs, &lfscfg);
}

void mmc_disable(void)
{
    /* Unmount LFS file system */
    lfs_unmount(&lfs);

    /* Disconnect from eMMC device and stop interface */
    blkDisconnect(SDC);
    sdcStop(SDC);

    /* Disable power to eMMC */
    palSetLine(LINE_MMC_PWR);

    return;
}

/*===========================================================================*/
/* LFS Support Functions                                                     */
/*===========================================================================*/
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

