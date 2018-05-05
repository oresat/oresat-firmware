#include "statemachine.h"

ACS acs;

static int state_off(void){
	printf("off\n");	
	return OFF;
}

static int state_init(void){
	printf("init\n");	
	return OFF;
}

static int state_ready(void){
	printf("ready\n");	
	return RDY;
}

static int state_rw(void){
	printf("rw\n");	
	return RW;
}

static int state_mtqr(void){
	printf("mtqr\n");	
	return MTQR;
}

char *state_name[] = {"OFF","INIT","RDY","RW","MTQR"};

transition state_transitions[] = {
	{RDY, 	RW,			&state_reactionwheel},
	{RDY, 	MTQR,		&state_magnetorquer},
	{RDY, 	OFF,		&state_off},
	{RW, 		RDY,		&state_ready},
	{MTQR, 	RDY,		&state_ready}
};

#define TRANS_COUNT (sizeof(state_transitions)/sizeof(*trans))

int lookup_transitions(acs_state acss,acs_event rc){
	(void)acss;
	(void)rc;

	return EXIT_SUCCESS;
}

acs_event getNextEvent(){
	
	return 
}

int acs_statemachine(){
	acs.cur_state = ENTRY_STATE;
	acs_event event;

	while (acs.cur_state != OFF) {
		event = getNextEvent();
			for (i = 0; i < TRANS_COUNT; i++) {
				if ((acs.cur_state == trans[i].st) || (ST_ANY == trans[i].st)) {
				if ((event == trans[i].ev) || (EV_ANY == trans[i].ev)) {
					state = (trans[i].fn)();
					break;
			}
		}
	}
}
	return EXIT_SUCCESS;
}

/*
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
//*/
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


