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

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
