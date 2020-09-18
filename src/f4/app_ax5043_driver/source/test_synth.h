#ifndef _TEST_SYNTH_H_
#define _TEST_SYNTH_H_

#include "si41xx.h"

#ifdef __cplusplus
extern "C" {
#endif

extern SI41XXDriver synth;

void cmd_synth(BaseSequentialStream *chp, int argc, char *argv[]);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
