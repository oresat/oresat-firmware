#ifndef _TEST_RADIO_H_
#define _TEST_RADIO_H_

#include "ax5043.h"
#include "si41xx.h"

#ifdef __cplusplus
extern "C" {
#endif

void radio_init(void);

void cmd_radio(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_synth(BaseSequentialStream *chp, int argc, char *argv[]);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
