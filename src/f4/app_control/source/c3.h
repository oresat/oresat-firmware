#ifndef _C3_H_
#define _C3_H_

#include "ch.h"
#include "hal.h"

typedef enum {
    PRE_DEPLOY = 'B',
    DEPLOY = 'C',
    STANDBY = 'D',
    BEACON = 'E',
    EDL = 'F'
} c3_state_t;

extern c3_state_t c3_state;

/* Main Command, Communications, and Control Thread Prototypes */
extern THD_WORKING_AREA(c3_wa, 0x400);
extern THD_FUNCTION(c3, arg);

#endif
