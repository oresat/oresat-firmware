#ifndef _TEST_MMC_H_
#define _TEST_MMC_H_

#include "ch.h"
#include "hal.h"

#ifdef __cplusplus
extern "C" {
#endif

void cmd_mmc(BaseSequentialStream *chp, int argc, char *argv[]);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
