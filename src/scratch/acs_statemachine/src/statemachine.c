#include "statemachine.h"

int off_state(void){
	printf("off\n");	
	return OFF;
}

int ready_state(void){
	printf("ready\n");	
	return RDY;
}

int rw_state(void){
	printf("rw\n");	
	return RW;
}

int mtqr_state(void){
	printf("mtqr\n");	
	return MTQR;
}

int (* state[])() = {off_state,ready_state,rw_state,mtqr_state};
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

int lookup_transitions(state_codes sc,ret_codes rc){
	(void)sc;
	(void)rc;

	return EXIT_SUCCESS;
}

int acs_statemachine(){
	state_codes cur_state = ENTRY_STATE;
	ret_codes rc;
	int (* state_fun)(void);
	int i=0;
	char input[10];

	for(i=0;i<100;++i){
		printf("current state: %s\n",state_name[cur_state]);
		printf("desired state? ");
		fgets(input,1,stdin);		
		state_fun = state[input]; 
		if(EXIT_STATE == cur_state)
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

	printf("interations: %d\n",i);

	return EXIT_SUCCESS;
}


