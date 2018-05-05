#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_

#include <stdio.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define ENTRY_STATE RDY 
#define EXIT_STATE OFF

int off_state(void);
int ready_state(void);
int rw_state(void);
int mtqr_state(void);

extern int (* state[])(); 
typedef enum {OFF,RDY,RW,MTQR} state_codes;
typedef enum {off,repeat,rdy,rw,mtqr} ret_codes;
extern char *state_name[];
typedef struct {
	state_codes src_state;
	ret_codes   ret_code;
	state_codes dst_state;
}transition;

extern transition state_transitions[];

int lookup_transitions(state_codes sc,ret_codes rc);

int acs_statemachine();

#endif
