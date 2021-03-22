/**
 * @file    fs.h
 * @brief   Filesystem driver.
 *
 * @addtogroup Filesystem
 * @ingroup ORESAT
 * @{
 */
#ifndef _FS_H_
#define _FS_H_

#include "lfs.h"
#include "lfs_util.h"

/*============================================================================*/
/* Driver constants.                                                          */
/*============================================================================*/

/*============================================================================*/
/* Driver pre-compile time settings.                                          */
/*============================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   Filesystem Cache Sizes
 */
#if !defined(FS_CACHE_SIZE) || defined(__DOXYGEN__)
#define FS_CACHE_SIZE                       (512U)
#endif

/**
 * @brief   Filesystem Lookahead buffer size
 */
#if !defined(FS_LOOKAHEAD_SIZE) || defined(__DOXYGEN__)
#define FS_LOOKAHEAD_SIZE                   (16U)
#endif

/**
 * @brief   Maximum number of files open
 */
#if !defined(FS_MAX_HANDLERS) || defined(__DOXYGEN__)
#define FS_MAX_HANDLERS                     (4U)
#endif

/** @} */

/*============================================================================*/
/* Derived constants and error checks.                                        */
/*============================================================================*/

/*============================================================================*/
/* Driver data structures and types.                                          */
/*============================================================================*/

/**
 * @name    Filesystem data structures and types.
 * @{
 */
/**
 * @brief Structure representing a INA226 driver.
 */
typedef struct FSDriver FSDriver;

/**
 * @brief   Driver state machine possible states.
 */
typedef enum {
    FS_UNINIT = 0,                      /**< Not initialized.                 */
    FS_STOP = 1,                        /**< Stopped.                         */
    FS_OFFLINE = 2,                     /**< eMMC is offline.                 */
    FS_ONLINE = 3,                      /**< eMMC is online.                  */
    FS_MOUNTED = 4                      /**< Filesystem is mounted.           */
} fs_state_t;

/**
 * @brief   Filesystem configuration structure.
 */
typedef struct {
    /**
     * @brief SDC driver associated with this filesystem.
     */
    SDCDriver                   *sdcp;
    /**
     * @brief SDC configuration associated with this filesystem.
     */
    const SDCConfig             *sdccfg;
    /**
     * @brief GPIO Line for enabling eMMC
     */
    ioline_t                    mmc_pwr;
} FSConfig;

/**
 * @brief   Filesystem driver object
 */
struct FSDriver {
    /* Driver state */
    fs_state_t                  state;
    /* Current configuration */
    const FSConfig              *config;
    /* Filesystem mutex */
    mutex_t                     mutex;
    /* LFS object */
    lfs_t                       lfs;
    /* LFS configuration */
    struct lfs_config           lfscfg;
    /* Last LFS error */
    int                         err;
    /* MMC CID field */
    unpacked_mmc_cid_t          mmc_cid;
    /* MMC CSD field */
    unpacked_mmc_csd_t          mmc_csd;
    /* Guarded file pool */
    guarded_memory_pool_t       file_pool;
    lfs_file_t                  file[FS_MAX_HANDLERS];
    /* Guarded dir pool */
    guarded_memory_pool_t       dir_pool;
    lfs_file_t                  dir[FS_MAX_HANDLERS];
    /* TODO: Implement static file buffers */
    /* Read buffer */
    uint8_t                     read_buf[FS_CACHE_SIZE];
    /* Program buffer */
    uint8_t                     prog_buf[FS_CACHE_SIZE];
    /* Lookahead buffer */
    uint8_t                     lookahead_buf[FS_LOOKAHEAD_SIZE];
};

/** @} */

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* Default filesystem object */
extern FSDriver FSD1;

/* Driver functions */
void fs_init(FSDriver *fsp);
void fs_start(FSDriver *fsp, const FSConfig *config);
void fs_stop(FSDriver *fsp);

/* Filesystem operations */
int fs_format(FSDriver *fsp);
int fs_mount(FSDriver *fsp, bool format);
int fs_unmount(FSDriver *fsp);
int fs_remove(FSDriver *fsp, const char *path);
int fs_rename(FSDriver *fsp, const char *oldpath, const char *newpath);
int fs_stat(FSDriver *fsp, const char *path, struct lfs_info *info);
lfs_ssize_t fs_getattr(FSDriver *fsp, const char *path, uint8_t type, void *buffer, lfs_size_t size);
int fs_setattr(FSDriver *fsp, const char *path, uint8_t type, const void *buffer, lfs_size_t size);
int fs_removeattr(FSDriver *fsp, const char *path, uint8_t type);

/* File operations */
lfs_file_t *file_open(FSDriver *fsp, const char *path, int flags);
int file_close(FSDriver *fsp, lfs_file_t *file);
int file_sync(FSDriver *fsp, lfs_file_t *file);
lfs_ssize_t file_read(FSDriver *fsp, lfs_file_t *file, void *buffer, lfs_size_t size);
lfs_ssize_t file_write(FSDriver *fsp, lfs_file_t *file, const void *buffer, lfs_size_t size);
lfs_soff_t file_seek(FSDriver *fsp, lfs_file_t *file, lfs_soff_t off, int whence);
int file_truncate(FSDriver *fsp, lfs_file_t *file, lfs_soff_t size);
lfs_soff_t file_tell(FSDriver *fsp, lfs_file_t *file);
int file_rewind(FSDriver *fsp, lfs_file_t *file);
lfs_soff_t file_size(FSDriver *fsp, lfs_file_t *file);

/* Directory operations */
int fs_mkdir(FSDriver *fsp, const char *path);
lfs_dir_t *dir_open(FSDriver *fsp, const char *path);
int dir_close(FSDriver *fsp, lfs_dir_t *dir);
int dir_read(FSDriver *fsp, lfs_dir_t *dir, struct lfs_info *info);
int dir_seek(FSDriver *fsp, lfs_dir_t *dir, lfs_soff_t off);
lfs_soff_t dir_tell(FSDriver *fsp, lfs_dir_t *dir);
int dir_rewind(FSDriver *fsp, lfs_dir_t *dir);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
