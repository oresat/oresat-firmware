#ifndef _TEST_PERSIST_H_
#define _TEST_PERSIST_H_

#include "ch.h"
#include "hal.h"

#ifdef __cplusplus
extern "C" {
#endif

void cmd_persist(BaseSequentialStream *chp, int argc, char *argv[]);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
