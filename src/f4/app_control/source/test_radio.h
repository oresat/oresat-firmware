#ifndef _TEST_RADIO_H_
#define _TEST_RADIO_H_

#include "ch.h"
#include "hal.h"

#ifdef __cplusplus
extern "C" {
#endif

void cmd_radio(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_synth(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_rf(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_rftest(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_beacon(BaseSequentialStream *chp, int argc, char *argv[]);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
