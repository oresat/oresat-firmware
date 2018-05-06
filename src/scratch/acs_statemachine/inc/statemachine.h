#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

extern char *state_name[];
extern char *event_name[];

typedef enum {
	ST_ANY=-1,
	ST_OFF,
	ST_INIT,
	ST_RDY,
	ST_RW,
	ST_MTQR
}acs_state;

typedef enum {
	EV_ANY=-1,
	EV_OFF,
	EV_INIT,
	EV_RDY,
	EV_RW,
	EV_MTQR,
	EV_REP,
	EV_STATUS,
	EV_END // this must be the last event
}acs_event;


typedef struct{
	acs_state cur_state;
	acs_event event;
}ACS;

typedef struct{
	acs_state state;
	acs_event event;
	int (*fn)(ACS *acs);
}acs_transition,acs_trap;

extern acs_transition trans[];
extern acs_trap trap[];

int acs_statemachine();

#endif
