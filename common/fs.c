/**
 * @file    fs.c
 * @brief   Filesystem driver.
 *
 * @addtogroup Filesystem
 * @ingrup ORESAT
 * @{
 */

#include <stdlib.h>
#include <string.h>

#include "ch.h"
#include "hal.h"
#include "fs.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

FSDriver FSD1;

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/**
 * @brief   Locks a block device.
 *
 * @param[in]  cfg      Pointer to the LFS configuration
 *
 * @return              The operation status
 * @notapi
 */
int mmc_lock(const struct lfs_config *cfg)
{
    /* Sanity checks */
    osalDbgCheck(cfg != NULL);

    FSDriver *fsp = cfg->context;

    chMtxLock(&fsp->mutex);

    return LFS_ERR_OK;
}

/**
 * @brief   Unlocks a block device.
 *
 * @param[in]  cfg      Pointer to the LFS configuration
 *
 * @return              The operation status
 * @notapi
 */
int mmc_unlock(const struct lfs_config *cfg)
{
    /* Sanity checks */
    osalDbgCheck(cfg != NULL);

    FSDriver *fsp = cfg->context;

    chMtxUnlock(&fsp->mutex);

    return LFS_ERR_OK;
}

/**
 * @brief   Reads a block from SDC device.
 * @pre     The SDC interface must be initialized and the driver started.
 *
 * @param[in]  cfg      Pointer to the LFS configuration
 * @param[in]  block    The block to read from
 * @param[in]  off      The offset within the block
 * @param[out] buffer   Pointer to an output buffer
 * @param[in]  size     Number of consecutive bytes to read
 *
 * @return              The operation status
 * @notapi
 */
int mmc_read(const struct lfs_config *cfg, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size)
{
    /* Sanity checks */
    osalDbgCheck(cfg != NULL && buffer != NULL);

    FSDriver *fsp = cfg->context;
    SDCDriver *sdcp = fsp->config->sdcp;
    uint8_t buf[cfg->block_size];

    /* Sanity checks */
    chDbgCheck(off % cfg->read_size == 0);
    chDbgCheck(size % cfg->read_size == 0);
    chDbgCheck(off + size <= cfg->block_size);
    chDbgCheck(block < cfg->block_count);

    /* Read data from block */
    if (blkRead(sdcp, block, buf, 1) != HAL_SUCCESS) {
        return LFS_ERR_IO;
    }

    /* Copy the requested data to the buffer */
    memcpy(buffer, &buf[off], size);

    return LFS_ERR_OK;
}

/**
 * @brief   Programs a block of an SDC device.
 * @pre     The SDC interface must be initialized and the driver started.
 *
 * @param[in]  cfg      Pointer to the LFS configuration
 * @param[in]  block    The block to program
 * @param[in]  off      The offset within the block
 * @param[in]  buffer   Pointer to an input buffer
 * @param[in]  size     Number of consecutive bytes to program
 *
 * @return              The operation status
 * @notapi
 */
int mmc_prog(const struct lfs_config *cfg, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size)
{
    /* Sanity checks */
    osalDbgCheck(cfg != NULL && buffer != NULL);

    FSDriver *fsp = cfg->context;
    SDCDriver *sdcp = fsp->config->sdcp;
    uint8_t buf[cfg->block_size];

    /* Sanity checks */
    chDbgCheck(off % cfg->read_size == 0);
    chDbgCheck(size % cfg->read_size == 0);
    chDbgCheck(off + size <= cfg->block_size);
    chDbgCheck(block < cfg->block_count);

    /* Read the current data from the block */
    mmc_read(cfg, block, 0, buf, cfg->block_size);

    /* Copy new data */
    memcpy(&buf[off], buffer, size);

    /* Write data to block */
    if (blkWrite(sdcp, block, buf, 1) != HAL_SUCCESS) {
        return LFS_ERR_IO;
    }

    return LFS_ERR_OK;
}

/**
 * @brief   Erase a block of an SDC device.
 * @pre     The SDC interface must be initialized and the driver started.
 *
 * @param[in]  cfg      Pointer to the LFS configuration
 * @param[in]  block    The block to read from
 *
 * @return              The operation status
 * @notapi
 */
int mmc_erase(const struct lfs_config *cfg, lfs_block_t block)
{
    /* Sanity checks */
    osalDbgCheck(cfg != NULL);

    FSDriver *fsp = cfg->context;
    SDCDriver *sdcp = fsp->config->sdcp;
    uint8_t buf[cfg->block_size];

    /* Sanity checks */
    chDbgCheck(block < cfg->block_count);

    memset(buf, 0xFF, cfg->block_size);

    /* Write data to block */
    if (blkWrite(sdcp, block, buf, 1) != HAL_SUCCESS) {
        return LFS_ERR_IO;
    }

    return LFS_ERR_OK;
}

/**
 * @brief   Sync an SDC device.
 * @pre     The SDC interface must be initialized and the driver started.
 *
 * @param[in]  cfg      Pointer to the LFS configuration
 *
 * @return              The operation status
 * @notapi
 */
int mmc_sync(const struct lfs_config *cfg)
{
    /* Sanity checks */
    osalDbgCheck(cfg != NULL);

    FSDriver *fsp = cfg->context;
    SDCDriver *sdcp = fsp->config->sdcp;

    if (blkSync(sdcp) != HAL_SUCCESS) {
        return LFS_ERR_IO;
    }

    return LFS_ERR_OK;
}

/**
 * @brief   Enable eMMC and connect.
 *
 * @param[in]  fsp      Pointer to the @p FSDriver object
 *
 * @return              The operation status
 * @notapi
 */
int mmc_enable(FSDriver *fsp)
{
    /* Sanity checks */
    osalDbgCheck(fsp != NULL);
    osalDbgAssert((fsp->state == FS_ONLINE) || (fsp->state == FS_OFFLINE),
            "mmc_enable(), invalid state");

    BlockDeviceInfo bdinfo;
    SDCDriver *sdcp = fsp->config->sdcp;
    const SDCConfig *sdccfg = fsp->config->sdccfg;

    if (fsp->state == FS_OFFLINE) {
        /* Enable power to eMMC */
        palClearLine(fsp->config->mmc_pwr);

        /* Initializes MMC SDC interface */
        sdcStart(sdcp, sdccfg);

        /* Connect to eMMC device */
        if (sdcConnect(sdcp)) {
            sdcStop(sdcp);
            palSetLine(fsp->config->mmc_pwr);
            return LFS_ERR_IO;
        }

        /* Clear error flags from connecting */
        sdcGetAndClearErrors(sdcp);

        /* Retrieve block information */
        blkGetInfo(sdcp, &bdinfo);
        fsp->lfscfg.block_size = bdinfo.blk_size;
        fsp->lfscfg.block_count = bdinfo.blk_num;

        /* Fetch info about eMMC device */
        _mmcsd_unpack_mmc_cid((MMCSDBlockDevice*)sdcp, &fsp->mmc_cid);
        _mmcsd_unpack_csd_mmc((MMCSDBlockDevice*)sdcp, &fsp->mmc_csd);

        fsp->state = FS_ONLINE;
    }

    return LFS_ERR_OK;
}

/**
 * @brief   Disconnect and disable eMMC.
 *
 * @param[in]  fsp      Pointer to the @p FSDriver object
 *
 * @return              The operation status
 * @notapi
 */
int mmc_disable(FSDriver *fsp)
{
    /* Sanity checks */
    osalDbgCheck(fsp != NULL);
    osalDbgAssert((fsp->state == FS_ONLINE) || (fsp->state == FS_OFFLINE),
            "mmc_disable(), invalid state");

    SDCDriver *sdcp = fsp->config->sdcp;

    if (fsp->state == FS_ONLINE) {
        /* Disconnect from eMMC device and stop interface */
        sdcDisconnect(sdcp);
        sdcStop(sdcp);

        /* Disable power to eMMC */
        palSetLine(fsp->config->mmc_pwr);

        fsp->state = FS_OFFLINE;
    }

    return LFS_ERR_OK;
}

/**
 * @brief   Operations to perform before accessing filesystem.
 *
 * @param[in]  fsp      Pointer to the @p FSDriver object
 *
 * @return              The operation status
 * @notapi
 */
static inline int fs_access_start(FSDriver *fsp)
{
    if (fsp->state != FS_MOUNTED) {
        return fs_mount(fsp, false);
    }
    return LFS_ERR_OK;
}

/**
 * @brief   Operations to perform when done accessing filesystem.
 *
 * @param[in]  fsp      Pointer to the @p FSDriver object
 *
 * @return              The operation status
 * @notapi
 */
static inline int fs_access_end(FSDriver *fsp)
{
    /* TODO: unmount if okay */
    (void)fsp;
    return LFS_ERR_OK;
}

/* TODO: Implement static buffers for files */
void *fs_alloc_file(FSDriver *fsp)
{
    /* Sanity checks */
    osalDbgCheck(fsp != NULL);

    void *fp = NULL;
    fsp->err = LFS_ERR_OK;

    fp = chGuardedPoolAllocTimeout(&fsp->file_pool, TIME_IMMEDIATE);
    if (fp == NULL) {
        fsp->err = LFS_ERR_NOMEM;
    }

    return fp;
}

void fs_free_file(FSDriver *fsp, void *fp)
{
    /* Sanity checks */
    osalDbgCheck(fsp != NULL && fp != NULL);

    chGuardedPoolFree(&fsp->file_pool, fp);
}

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Initializes an instance.
 *
 * @param[out] fsp      Pointer to the @p FSDriver object
 *
 * @init
 */
void fs_init(FSDriver *fsp)
{
    fsp->config                 = NULL;
    fsp->err                    = LFS_ERR_OK;

    /* Initialize lfscfg */
    fsp->lfscfg.context         = NULL;
    fsp->lfscfg.read            = mmc_read;     /* Read operation             */
    fsp->lfscfg.prog            = mmc_prog;     /* Program oepration          */
    fsp->lfscfg.erase           = mmc_erase;    /* Erase operation            */
    fsp->lfscfg.sync            = mmc_sync;     /* Sync operation             */
    fsp->lfscfg.lock            = mmc_lock;     /* Lock block device          */
    fsp->lfscfg.unlock          = mmc_unlock;   /* Unlock block device        */
    fsp->lfscfg.block_size      = 0;
    fsp->lfscfg.block_count     = 0;
    fsp->lfscfg.read_size       = 16;           /* TODO: Check these values   */
    fsp->lfscfg.prog_size       = 16;           /* TODO: Check these values   */
    fsp->lfscfg.block_cycles    = -1;           /* Disable LFS wear leveling  */
    fsp->lfscfg.cache_size      = FS_CACHE_SIZE;
    fsp->lfscfg.lookahead_size  = FS_LOOKAHEAD_SIZE;
    fsp->lfscfg.read_buffer     = fsp->read_buf;
    fsp->lfscfg.prog_buffer     = fsp->prog_buf;
    fsp->lfscfg.lookahead_buffer= fsp->lookahead_buf;
    fsp->lfscfg.name_max        = 0;            /* Default to LFS_NAME_MAX    */
    fsp->lfscfg.file_max        = 0;            /* Default to LFS_FILE_MAX    */
    fsp->lfscfg.attr_max        = 0;            /* Default to LFS_ATTR_MAX    */
    fsp->lfscfg.metadata_max    = 0;            /* Default to block_size      */

    chMtxObjectInit(&fsp->mutex);
    chGuardedPoolObjectInitAligned(&fsp->file_pool, sizeof(lfs_file_t), PORT_NATURAL_ALIGN);
    chGuardedPoolLoadArray(&fsp->file_pool, fsp->file, FS_MAX_FILES);

    fsp->state                  = FS_STOP;
}

/**
 * @brief   Configures and activates Filesystem Driver.
 *
 * @param[in]  fsp      Pointer to the @p FSDriver object
 * @param[in]  config   Pointer to the @p FSConfig object
 *
 * @api
 */
void fs_start(FSDriver *fsp, const FSConfig *config)
{
    /* Sanity checks */
    osalDbgCheck((fsp != NULL) && (config != NULL));
    osalDbgAssert((fsp->state == FS_STOP) || (fsp->state == FS_OFFLINE),
            "fs_start(), invalid state");

    fsp->config = config;
    fsp->lfscfg.context = fsp;
    fsp->state = FS_OFFLINE;
}

/**
 * @brief   Deactivates the Filesystem Driver.
 *
 * @param[in]  fsp      Pointer to the @p FSDriver object
 *
 * @api
 */
void fs_stop(FSDriver *fsp)
{
    /* Sanity checks */
    osalDbgCheck(fsp != NULL);
    osalDbgAssert((fsp->state == FS_STOP) || (fsp->state == FS_OFFLINE),
            "fs_stop(), invalid state");

    fsp->state = FS_STOP;
}

/**
 * @brief   Formats the filesystem.
 *
 * @param[in]  fsp      Pointer to the @p FSDriver object
 *
 * @return              The operation status
 * @api
 */
int fs_format(FSDriver *fsp)
{
    /* Sanity checks */
    osalDbgCheck(fsp != NULL);
    osalDbgAssert((fsp->state != FS_UNINIT) && (fsp->state != FS_STOP),
            "fs_format(), invalid state");

    fs_state_t last_state;
    fsp->err = LFS_ERR_OK;
    last_state = fsp->state;

    /* Unmount volume if currently mounted */
    if (fsp->state == FS_MOUNTED) {
        fsp->err = fs_unmount(fsp);
        if (fsp->err != LFS_ERR_OK) {
            return fsp->err;
        }
    }

    /* Enable eMMC if not already enabled */
    if (fsp->state == FS_OFFLINE) {
        fsp->err = mmc_enable(fsp);
        if (fsp->err != LFS_ERR_OK) {
            return fsp->err;
        }
    }

    /* Format LFS file system */
    fsp->err = lfs_format(&fsp->lfs, &fsp->lfscfg);
    if (fsp->err == LFS_ERR_OK) {
        /* Restore state */
        if (last_state == FS_OFFLINE) {
            fsp->err = mmc_disable(fsp);
        } else if (last_state == FS_MOUNTED) {
            fsp->err = fs_mount(fsp, false);
        }
    }

    return fsp->err;
}

/**
 * @brief   Mounts the filesystem.
 *
 * @param[in]  fsp      Pointer to the @p FSDriver object
 * @param[in]  format   Format the volume if unable to mount
 *
 * @return              The operation status
 * @api
 */
int fs_mount(FSDriver *fsp, bool format)
{
    /* Sanity checks */
    osalDbgCheck(fsp != NULL);
    osalDbgAssert((fsp->state != FS_UNINIT) && (fsp->state != FS_STOP),
            "fs_mount(), invalid state");

    fsp->err = LFS_ERR_OK;

    /* Start eMMC if not already online */
    if (fsp->state == FS_OFFLINE) {
        fsp->err = mmc_enable(fsp);
        if (fsp->err != LFS_ERR_OK) {
            return fsp->err;
        }
    }

    /* Mount LFS file system if not yet mounted */
    if (fsp->state == FS_ONLINE) {
        fsp->err = lfs_mount(&fsp->lfs, &fsp->lfscfg);
        if (fsp->err != LFS_ERR_OK && format == true) {
            /* On failure, attempt format if allowed */
            fsp->err = lfs_format(&fsp->lfs, &fsp->lfscfg);
            if (fsp->err == LFS_ERR_OK) {
                fsp->err = lfs_mount(&fsp->lfs, &fsp->lfscfg);
            }
        }
        fsp->state = FS_MOUNTED;
    }

    return fsp->err;
}

/**
 * @brief   Unmounts the filesystem.
 *
 * @param[in]  fsp      Pointer to the @p FSDriver object
 *
 * @return              The operation status
 * @api
 */
int fs_unmount(FSDriver *fsp)
{
    /* Sanity checks */
    osalDbgCheck(fsp != NULL);
    osalDbgAssert((fsp->state != FS_UNINIT) && (fsp->state != FS_STOP),
            "fs_unmount(), invalid state");

    fsp->err = LFS_ERR_OK;

    /* Unmount LFS file system if mounted */
    if (fsp->state == FS_MOUNTED) {
        fsp->err = lfs_unmount(&fsp->lfs);
        fsp->state = FS_ONLINE;
        if (fsp->err != LFS_ERR_OK) {
            return fsp->err;
        }
    }

    if (fsp->state == FS_ONLINE) {
        fsp->err = mmc_disable(fsp);
    }

    return fsp->err;
}

/**
 * @brief   Removes a file or directory.
 *
 * @param[in]  fsp      Pointer to the @p FSDriver object
 * @param[in]  path     Pathname
 *
 * @return              The operation status
 * @api
 */
int fs_remove(FSDriver *fsp, const char *path)
{
    /* Sanity checks */
    osalDbgCheck(fsp != NULL);
    osalDbgAssert((fsp->state != FS_UNINIT) && (fsp->state != FS_STOP),
            "fs_remove(), invalid state");

    fsp->err = fs_access_start(fsp);
    if (fsp->err != LFS_ERR_OK) {
        return fsp->err;
    }

    fsp->err = lfs_remove(&fsp->lfs, path);
    if (fsp->err != LFS_ERR_OK) {
        return fsp->err;
    }

    fsp->err = fs_access_end(fsp);
    return fsp->err;
}

/**
 * @brief   Renames a file or directory.
 *
 * @param[in]  fsp      Pointer to the @p FSDriver object
 * @param[in]  oldpath  Old pathname
 * @param[in]  newpath  New pathname
 *
 * @return              The operation status
 * @api
 */
int fs_rename(FSDriver *fsp, const char *oldpath, const char *newpath)
{
    /* Sanity checks */
    osalDbgCheck(fsp != NULL);
    osalDbgAssert((fsp->state != FS_UNINIT) && (fsp->state != FS_STOP),
            "fs_remove(), invalid state");

    fsp->err = fs_access_start(fsp);
    if (fsp->err != LFS_ERR_OK) {
        return fsp->err;
    }

    fsp->err = lfs_rename(&fsp->lfs, oldpath, newpath);
    if (fsp->err != LFS_ERR_OK) {
        return fsp->err;
    }

    fsp->err = fs_access_end(fsp);
    return fsp->err;
}

/**
 * @brief   Get info about a file or directory.
 *
 * @param[in]  fsp      Pointer to the @p FSDriver object
 * @param[in]  path     Pathname
 * @param[out] info     Info structure to fill out
 *
 * @return              The operation status
 * @api
 */
int fs_stat(FSDriver *fsp, const char *path, struct lfs_info *info)
{
    /* Sanity checks */
    osalDbgCheck(fsp != NULL);
    osalDbgAssert((fsp->state != FS_UNINIT) && (fsp->state != FS_STOP),
            "fs_remove(), invalid state");

    fsp->err = fs_access_start(fsp);
    if (fsp->err != LFS_ERR_OK) {
        return fsp->err;
    }

    fsp->err = lfs_stat(&fsp->lfs, path, info);
    if (fsp->err != LFS_ERR_OK) {
        return fsp->err;
    }

    fsp->err = fs_access_end(fsp);
    return fsp->err;
}

/**
 * @brief   Get attribute from file.
 *
 * @param[in]  fsp      Pointer to the @p FSDriver object
 * @param[in]  path     Pathname
 * @param[in]  type     Attribute type
 * @param[out] buffer   The buffer to write the attribute to
 * @param[in]  size     Maximum size of buffer
 *
 * @return              The size of the attribute in the filesyste
 *                      or negative error code
 * @api
 */
lfs_ssize_t fs_getattr(FSDriver *fsp, const char *path, uint8_t type, void *buffer, lfs_size_t size)
{
    lfs_ssize_t ret_size;
    /* Sanity checks */
    osalDbgCheck(fsp != NULL && buffer != NULL);
    osalDbgAssert((fsp->state != FS_UNINIT) && (fsp->state != FS_STOP),
            "fs_getattr(), invalid state");

    fsp->err = fs_access_start(fsp);
    if (fsp->err != LFS_ERR_OK) {
        return fsp->err;
    }

    ret_size = lfs_getattr(&fsp->lfs, path, type, buffer, size);
    if (ret_size < 0) {
        fsp->err = ret_size;
        return fsp->err;
    }

    fsp->err = fs_access_end(fsp);
    if (fsp->err != LFS_ERR_OK) {
        return fsp->err;
    }

    return ret_size;
}

/**
 * @brief   Set attribute on file.
 *
 * @param[in]  fsp      Pointer to the @p FSDriver object
 * @param[in]  path     Pathname
 * @param[in]  type     Attribute type
 * @param[out] buffer   The buffer to write the attribute to
 * @param[in]  size     Maximum size of buffer
 *
 * @return              The operation status
 * @api
 */
int fs_setattr(FSDriver *fsp, const char *path, uint8_t type, const void *buffer, lfs_size_t size)
{
    /* Sanity checks */
    osalDbgCheck(fsp != NULL && buffer != NULL);
    osalDbgAssert((fsp->state != FS_UNINIT) && (fsp->state != FS_STOP),
            "fs_getattr(), invalid state");

    fsp->err = fs_access_start(fsp);
    if (fsp->err != LFS_ERR_OK) {
        return fsp->err;
    }

    fsp->err = lfs_setattr(&fsp->lfs, path, type, buffer, size);
    if (fsp->err != LFS_ERR_OK) {
        return fsp->err;
    }

    fsp->err = fs_access_end(fsp);
    return fsp->err;
}

/**
 * @brief   Remove attribute from file.
 *
 * @param[in]  fsp      Pointer to the @p FSDriver object
 * @param[in]  path     Pathname
 * @param[in]  type     Attribute type
 *
 * @return              The operation status
 * @api
 */
int fs_removeattr(FSDriver *fsp, const char *path, uint8_t type)
{
    /* Sanity checks */
    osalDbgCheck(fsp != NULL);
    osalDbgAssert((fsp->state != FS_UNINIT) && (fsp->state != FS_STOP),
            "fs_getattr(), invalid state");

    fsp->err = fs_access_start(fsp);
    if (fsp->err != LFS_ERR_OK) {
        return fsp->err;
    }

    fsp->err = lfs_removeattr(&fsp->lfs, path, type);
    if (fsp->err != LFS_ERR_OK) {
        return fsp->err;
    }

    fsp->err = fs_access_end(fsp);
    return fsp->err;
}

/**
 * @brief   Opens a file.
 *
 * @param[in]  fsp      Pointer to the @p FSDriver object
 * @param[in]  path     Pathname of the file
 * @param[in]  flags    Flags for opening the file
 *
 * @return              File handler pointer
 * @api
 */
lfs_file_t *file_open(FSDriver *fsp, const char *path, int flags)
{
    /* Sanity checks */
    osalDbgCheck(fsp != NULL);
    osalDbgAssert((fsp->state != FS_UNINIT) && (fsp->state != FS_STOP),
            "file_open(), invalid state");

    lfs_file_t *file = NULL;

    fsp->err = fs_access_start(fsp);
    if (fsp->err != LFS_ERR_OK) {
        return NULL;
    }

    file = fs_alloc_file(fsp);

    if (file != NULL) {
        fsp->err = lfs_file_open(&fsp->lfs, file, path, flags);
    }

    return file;
}

/**
 * @brief   Closes a file.
 *
 * @param[in]  fsp      Pointer to the @p FSDriver object
 * @param[in]  file     Open file pointer to close
 *
 * @return              The operation status
 * @api
 */
int file_close(FSDriver *fsp, lfs_file_t *file)
{
    /* Sanity checks */
    osalDbgCheck(fsp != NULL && file != NULL);
    osalDbgAssert(fsp->state == FS_MOUNTED,
            "file_close(), invalid state");

    fsp->err = LFS_ERR_OK;

    fsp->err = lfs_file_close(&fsp->lfs, file);
    if (fsp->err != LFS_ERR_OK) {
        return fsp->err;
    }

    fs_free_file(fsp, file);

    fsp->err = fs_access_end(fsp);
    return fsp->err;
}

/**
 * @brief   Syncs a file.
 *
 * @param[in]  fsp      Pointer to the @p FSDriver object
 * @param[in]  file     Open file pointer
 *
 * @return              Offset position or negative error code
 * @api
 */
int file_sync(FSDriver *fsp, lfs_file_t *file)
{
    /* Sanity checks */
    osalDbgCheck(fsp != NULL && file != NULL);
    osalDbgAssert(fsp->state == FS_MOUNTED,
            "file_read(), invalid state");

    fsp->err = lfs_file_sync(&fsp->lfs, file);

    return fsp->err;
}

/**
 * @brief   Reads from a file.
 *
 * @param[in]  fsp      Pointer to the @p FSDriver object
 * @param[in]  file     Open file pointer
 * @param[out] buffer   Buffer to read into
 * @param[in]  size     Maximum number of bytes to read
 *
 * @return              Offset position or negative error code
 * @api
 */
lfs_ssize_t file_read(FSDriver *fsp, lfs_file_t *file, void *buffer, lfs_size_t size)
{
    /* Sanity checks */
    osalDbgCheck(fsp != NULL && file != NULL && buffer != NULL);
    osalDbgAssert(fsp->state == FS_MOUNTED,
            "file_read(), invalid state");

    lfs_ssize_t ret_size;
    fsp->err = LFS_ERR_OK;

    ret_size = lfs_file_read(&fsp->lfs, file, buffer, size);
    if (ret_size < 0) {
        fsp->err = ret_size;
    }

    return ret_size;
}

/**
 * @brief   Writes to a file.
 *
 * @param[in]  fsp      Pointer to the @p FSDriver object
 * @param[in]  file     Open file pointer
 * @param[in]  buffer   Buffer to write from
 * @param[in]  size     Maximum number of bytes to write
 *
 * @return              Offset position or negative error code
 * @api
 */
lfs_ssize_t file_write(FSDriver *fsp, lfs_file_t *file, const void *buffer, lfs_size_t size)
{
    /* Sanity checks */
    osalDbgCheck(fsp != NULL && file != NULL && buffer != NULL);
    osalDbgAssert(fsp->state == FS_MOUNTED,
            "file_read(), invalid state");

    lfs_ssize_t ret_size;
    fsp->err = LFS_ERR_OK;

    ret_size = lfs_file_write(&fsp->lfs, file, buffer, size);
    if (ret_size < 0) {
        fsp->err = ret_size;
    }

    return ret_size;
}

/**
 * @brief   Seeks in a file.
 *
 * @param[in]  fsp      Pointer to the @p FSDriver object
 * @param[in]  file     Open file pointer
 * @param[in]  off      Offset to seek to
 * @param[in]  whence   Where to start offset at
 *
 * @return              Offset position or negative error code
 * @api
 */
lfs_soff_t file_seek(FSDriver *fsp, lfs_file_t *file, lfs_soff_t off, int whence)
{
    /* Sanity checks */
    osalDbgCheck(fsp != NULL && file != NULL);
    osalDbgAssert(fsp->state == FS_MOUNTED,
            "file_seek(), invalid state");

    lfs_soff_t ret_off;
    fsp->err = LFS_ERR_OK;

    ret_off = lfs_file_seek(&fsp->lfs, file, off, whence);
    if (ret_off < 0) {
        fsp->err = ret_off;
    }

    return ret_off;
}

/**
 * @brief   Truncate a file.
 *
 * @param[in]  fsp      Pointer to the @p FSDriver object
 * @param[in]  file     Open file pointer
 * @param[in]  size     Size to truncate to
 *
 * @return              The operation status
 * @api
 */
int file_truncate(FSDriver *fsp, lfs_file_t *file, lfs_soff_t size)
{
    /* Sanity checks */
    osalDbgCheck(fsp != NULL && file != NULL);
    osalDbgAssert(fsp->state == FS_MOUNTED,
            "file_truncate(), invalid state");

    fsp->err = lfs_file_truncate(&fsp->lfs, file, size);

    return fsp->err;
}

/**
 * @brief   Return position in a file.
 *
 * @param[in]  fsp      Pointer to the @p FSDriver object
 * @param[in]  file     Open file pointer
 *
 * @return              Offset position or negative error code
 * @api
 */
lfs_soff_t file_tell(FSDriver *fsp, lfs_file_t *file)
{
    /* Sanity checks */
    osalDbgCheck(fsp != NULL && file != NULL);
    osalDbgAssert(fsp->state == FS_MOUNTED,
            "file_tell(), invalid state");

    lfs_soff_t off;
    fsp->err = LFS_ERR_OK;

    off = lfs_file_tell(&fsp->lfs, file);
    if (off < 0) {
        fsp->err = off;
    }

    return off;
}

/**
 * @brief   Set position to start of file.
 *
 * @param[in]  fsp      Pointer to the @p FSDriver object
 * @param[in]  file     Open file pointer
 *
 * @return              Offset position or negative error code
 * @api
 */
int file_rewind(FSDriver *fsp, lfs_file_t *file)
{
    /* Sanity checks */
    osalDbgCheck(fsp != NULL && file != NULL);
    osalDbgAssert(fsp->state == FS_MOUNTED,
            "file_rewind(), invalid state");

    fsp->err = lfs_file_rewind(&fsp->lfs, file);

    return fsp->err;
}

/**
 * @brief   Return size of a file.
 *
 * @param[in]  fsp      Pointer to the @p FSDriver object
 * @param[in]  file     Open file pointer
 *
 * @return              Offset position or negative error code
 * @api
 */
lfs_soff_t file_size(FSDriver *fsp, lfs_file_t *file)
{
    /* Sanity checks */
    osalDbgCheck(fsp != NULL && file != NULL);
    osalDbgAssert(fsp->state == FS_MOUNTED,
            "file_size(), invalid state");

    lfs_soff_t off;
    fsp->err = LFS_ERR_OK;

    off = lfs_file_size(&fsp->lfs, file);
    if (off < 0) {
        fsp->err = off;
    }

    return off;
}

/** @} */
