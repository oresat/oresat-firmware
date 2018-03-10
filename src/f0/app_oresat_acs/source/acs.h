#ifndef _ACS_H_
#define _ACS_H_

#include "ch.h"
#include "hal.h"

#define CAN_NODE 0x3F // max 0x7f

typedef struct{
	// o_0
}ACSConfig;

extern void acs_init(void);

extern THD_WORKING_AREA(waACSThread, 128);
extern THD_FUNCTION(ACSThread, arg);

#endif
