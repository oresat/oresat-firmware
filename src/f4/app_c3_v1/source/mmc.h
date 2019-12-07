#ifndef _MMC_H_
#define _MMC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ch.h"
#include "hal.h"

void cmd_mmc(BaseSequentialStream *chp, int argc, char *argv[]);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
