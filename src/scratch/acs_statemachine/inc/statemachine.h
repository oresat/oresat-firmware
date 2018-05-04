#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define ENTRY_STATE RDY 
#define EXIT_STATE OFF

#define UNUSED(x) (void)(x)

int off_state(void);
int ready_state(void);
int rw_state(void);
int mtqr_state(void);

/* array and enum below must be in sync! */
extern int (* state[])(); 
typedef enum {OFF,RDY,RW,MTQR} state_codes;
typedef enum {off,repeat,rdy,rw,mtqr} ret_codes;
typedef struct {
	state_codes src_state;
	ret_codes   ret_code;
	state_codes dst_state;
}transition;

extern transition state_transitions[];

int lookup_transitions(state_codes sc,ret_codes rc);

#endif
