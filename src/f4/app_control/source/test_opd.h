#ifndef _TEST_OPD_H_
#define _TEST_OPD_H_

#include "ch.h"
#include "hal.h"

#ifdef __cplusplus
extern "C" {
#endif

void cmd_node(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_opd(BaseSequentialStream *chp, int argc, char *argv[]);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
