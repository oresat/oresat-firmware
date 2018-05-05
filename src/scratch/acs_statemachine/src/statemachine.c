#include "statemachine.h"

ACS acs;

int state_off(void){
	printf("off\n");	
	return OFF;
}

int state_ready(void){
	printf("ready\n");	
	return RDY;
}

int state_rw(void){
	printf("rw\n");	
	return RW;
}

int state_mtqr(void){
	printf("mtqr\n");	
	return MTQR;
}

int (* state[])() = {state_off,state_ready,state_rw,state_mtqr};
char *state_name[] = {"OFF","RDY","RW","MTQR"};

transition state_transitions[] = {
	{RDY,		repeat,		RDY},
	{RDY, 	rw,				RW},
	{RDY, 	mtqr,			MTQR},
	{RDY, 	off,			OFF},
	{RW, 		repeat,		RW},
	{RW, 		rdy,			RDY},
	{MTQR, 	repeat,		MTQR},
	{MTQR, 	rdy,			RDY}
};

int lookup_transitions(acs_state acss,acs_event rc){
	(void)acss;
	(void)rc;

	return EXIT_SUCCESS;
}

int acs_statemachine(){
	acs.cur_state = ENTRY_STATE;
	acs_event event;
	int i=0;
	char input;

	for(i=0;i<100;++i){
		printf("current state: %s\n",state_name[acs.cur_state]);
		printf("desired state? ");
		scanf(" %c", &input);
		event = atoi(&input);
		printf("%d\n",event);
		acs.active_state = state[event];
		acs.ac
		if(EXIT_STATE == acs.cur_state)
				break;
	}

/*
	for(i=0;i<100;++i){
		state_fun = state[cur_state];
		rc = state_fun();
		if(EXIT_STATE == cur_state)
				break;
		cur_state = lookup_transitions(cur_state, rc);
	}
//*/

	printf("iterations: %d\n",i);

	return EXIT_SUCCESS;
}


