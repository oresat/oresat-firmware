#ifndef _TEST_LFS_H_
#define _TEST_LFS_H_

#include "ch.h"
#include "hal.h"

#ifdef __cplusplus
extern "C" {
#endif

void cmd_lfs(BaseSequentialStream *chp, int argc, char *argv[]);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
