#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_

#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define ENTRY_STATE RDY 
#define EXIT_STATE OFF

int state_off(void);
int state_ready(void);
int state_rw(void);
int state_mtqr(void);

extern int (* state[])(); 
extern char *state_name[];

typedef enum {OFF,RDY,RW,MTQR} acs_state;
typedef enum {off,repeat,rdy,rw,mtqr} acs_event;

typedef struct{
	acs_state src_state;
	acs_event event;
	acs_state dst_state;
}transition;

typedef struct{
	acs_state cur_state;
	acs_event event;
	int (* active_state)(void);
}ACS;

extern transition state_transitions[];

int lookup_transitions(acs_state _state,acs_event _event);

int acs_statemachine();

#endif
