#include "statemachine.h"

ACS acs;

char *state_name[] = {
	"ST_ANY",
	"ST_OFF",
	"ST_INIT",
	"ST_RDY",
	"ST_RW",
	"ST_MTQR"
};

char *event_name[] = {
	"EV_ANY",
	"EV_OFF",
	"EV_INIT",
	"EV_RDY",
	"EV_RW",
	"EV_MTQR"
};

static void print_state(int state){
	printf("%s",state_name[state+1]);	
}

static int state_off(void){
	printf("***call to state_off: ");	
	print_state(ST_OFF);
	printf("\n");
	return ST_OFF;
}

static int state_init(void){
	printf("***call to state_init: ");	
	print_state(ST_INIT);
	printf("\n");
	return ST_INIT;
}

static int state_rdy(void){
	printf("***call to state_rdy: ");	
	print_state(ST_RDY);
	printf("\n");
	return ST_RDY;
}

static int state_rw(void){
	printf("***call to state_rw: ");	
	print_state(ST_RW);
	printf("\n");
	return ST_RW;
}

static int state_mtqr(void){
	printf("***call to state_mtqr: ");	
	print_state(ST_MTQR);
	printf("\n");
	return ST_MTQR;
}

static int fsm_error(void){
	printf("***call to fsm_error, keeping state\n");	
	return acs.cur_state;
}

transition trans[] = {
	{ST_INIT, 	ST_RDY,		&state_rdy},
	{ST_INIT, 	ST_OFF,		&state_off},
	{ST_RDY, 		ST_RW,		&state_rw},
	{ST_RDY, 		ST_MTQR,	&state_mtqr},
	{ST_RDY, 		ST_OFF,		&state_off},
	{ST_RW, 		ST_RDY,		&state_rdy},
	{ST_MTQR, 	ST_RDY,		&state_rdy},
	{ST_ANY, 		EV_ANY,		&fsm_error}
};

#define TRANS_COUNT (int)(sizeof(trans)/sizeof(transition))

acs_state getNextEvent(){
	acs_event event;
	char input[2];;

	printf("current state: %d ",acs.cur_state);
	print_state(acs.cur_state);
	printf("\n");
	printf("desired state? ");
	scanf(" %s", input);
	event = atoi(input);
	input[0]=input[1]=0;
//	if(evet < EV_ANY || event > EV){
//		printf("error, state out of range\n");
//		return 
//	}
	printf("attemping transitioning to state: "); print_state(event);
	printf("\n");
	return event;
}

int acs_statemachine(){
	acs_event event;
	int i;

	acs.cur_state = state_init();
	printf("entry state: %s\n",state_name[acs.cur_state+1]);
	
	printf("state enum: "); 
	printf("%d, %d, %d, %d, %d, %d\n",
			ST_ANY,ST_OFF,ST_INIT,ST_RDY,ST_RW,ST_MTQR);
	
	printf("state names: "); 
	print_state(ST_ANY); printf(", ");
	print_state(ST_OFF); printf(", ");
	print_state(ST_INIT); printf(", ");
	print_state(ST_RDY); printf(", ");
	print_state(ST_RW); printf(", ");
	print_state(ST_MTQR); printf("\n");
	printf("TRANS_CNT: %d\n",TRANS_COUNT);
	
	while (acs.cur_state != ST_OFF) {
		event = getNextEvent();
		for (i = 0;i < TRANS_COUNT;++i) {
		//	if((int)acs.cur_state != (int)event){
				if((acs.cur_state == trans[i].state)||(ST_ANY == trans[i].state)){
					if((event == trans[i].event)||(EV_ANY == trans[i].event)){
						acs.cur_state = (trans[i].trans_fn)();
						break;
					}
				}
		//	}
		}
	}
	return EXIT_SUCCESS;
}

