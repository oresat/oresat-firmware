#ifndef _TEST_RADIO_H_
#define _TEST_RADIO_H_

#include "ax5043.h"

extern AX5043Driver lband;
extern AX5043Driver uhf;

void cmd_radio(BaseSequentialStream *chp, int argc, char *argv[]);

#endif
