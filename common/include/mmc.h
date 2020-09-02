#ifndef _MMC_H_
#define _MMC_H_

#include "lfs.h"
#include "lfs_util.h"

#define SDC (&SDCD1)

#ifdef __cplusplus
extern "C" {
#endif

/* LFS objects */
extern lfs_t lfs;
extern struct lfs_config lfscfg;

/* eMMC support functions */
int mmc_enable(void);
void mmc_disable(void);

/* LFS support functions */
int mmc_read(const struct lfs_config *cfg, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size);
int mmc_prog(const struct lfs_config *cfg, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size);
int mmc_erase(const struct lfs_config *cfg, lfs_block_t block);
int mmc_sync(const struct lfs_config *cfg);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
