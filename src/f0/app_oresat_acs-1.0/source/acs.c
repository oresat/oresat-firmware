#include "acs.h"

//static mutex_t mtx;

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
	"EV_MTQR",
	"EV_REP",
	"EV_STATUS",
	"EV_END"
};

#define STATE_STRING "*Calling transition -> " 
#define TRAP_STRING "*Calling trap -> " 

static void print_state(int state){
//	(void)state;
	chprintf(DEBUG_CHP,"%s%s\n\r",STATE_STRING,state_name[state+1]); 
}

/*
static void print_event(int event){
	(void)event;
//	printf("%s",event_name[event+1]);	
}
/*/

static int state_off(ACS *acs){
	(void)acs;
	print_state(ST_OFF);
	return ST_OFF;
}

static int state_init(ACS *acs){
	(void)acs;
	print_state(ST_INIT);
	return ST_INIT;
}

static int state_rdy(ACS *acs){
	(void)acs;
	print_state(ST_RDY);
	return ST_RDY;
}

static int state_rw(ACS *acs){
	(void)acs;
	print_state(ST_RW);
	return ST_RW;
}

static int state_mtqr(ACS *acs){
	(void)acs;
	print_state(ST_MTQR);
	return ST_MTQR;
}

static int trap_fsm_status(ACS *acs){
	(void)acs;
	//palClearLine(LINE_LED_GREEN);
//	printf("%strap_fsm_report, keeping state!\n",TRAP_STRING);	
// **********critical section************
// TODO: needs to synchronize with the CAN thred
//	chMtxLock(&mtx);
	chSysLock();
	acs->can_buf.send[MSG_TYPE]=REPORT_STATUS;
	acs->can_buf.send[ARG_BYTE]=acs->cur_state;
	chSysUnlock();
// TODO: The buffer should not be overwritten with zeros
// 			 until the message is placed on the bus.
    chThdSleepMilliseconds(1000); // *************
//  ^^^^^ this should not be implemented with sleep

	chSysLock();
	for(int i=0;i<CAN_BUF_SIZE;++i){
		acs->can_buf.send[i]=0;
	}
	chSysUnlock();
//	chMtxUnlock(&mtx);
// *********end critical section*********
	return EXIT_SUCCESS;
}

/*
static int trap_rw_status(ACS *acs){
	(void)acs;
//	printf("%strap_rw_status, keeping state!\n",TRAP_STRING);	
	return EXIT_SUCCESS;
}

static int trap_mtqr_status(ACS *acs){
	(void)acs;
//	printf("%strap_mtqr_status, keeping state!\n",TRAP_STRING);	
	return EXIT_SUCCESS;
}
//*/

const acs_trap trap[] = {
//	{ST_RW, 	EV_STATUS,	&trap_rw_status},
//	{ST_MTQR, EV_STATUS,	&trap_mtqr_status},
	{ST_ANY, 	EV_STATUS,		&trap_fsm_status}
};

#define EVENT_COUNT (int)(sizeof(trap)/sizeof(acs_trap))

static int fsm_trap(ACS *acs){
//	printf("%sfsm_trap, keeping state!\n",TRAP_STRING);	
	int i,trap_status;

	for(i = 0;i < EVENT_COUNT;++i){
		//palClearLine(LINE_LED_GREEN);
		if(acs->event == trap[i].event){
			if(trap[i].state == ST_ANY || acs->cur_state == trap[i].state){
				trap_status = (trap[i].fn)(acs);
				if(trap_status){
					// something bad happened
				}
			}
		}
	}

	return acs->cur_state;
}

const acs_transition trans[] = {
	{ST_INIT, 	EV_RDY,		&state_rdy},
	{ST_INIT, 	EV_OFF,		&state_off},
	{ST_RDY, 		EV_RW,		&state_rw},
	{ST_RDY, 		EV_MTQR,	&state_mtqr},
	{ST_RDY, 		EV_OFF,		&state_off},
	{ST_RW, 		EV_RDY,		&state_rdy},
	{ST_MTQR, 	EV_RDY,		&state_rdy},
	{ST_ANY, 		EV_ANY,		&fsm_trap}
};

#define TRANS_COUNT (int)(sizeof(trans)/sizeof(acs_transition))

static acs_event getNextEvent(ACS *acs){
	acs_event event = EV_ANY;
	uint8_t recv[CAN_BUF_SIZE]={0};

// *******critical section**********
// TODO: This needs to be synchronized with the CAN thread
//	chMtxLock(&mtx);
	chSysLock();
	for(int i=0;i<CAN_BUF_SIZE;++i){
		recv[i]=acs->can_buf.recv[i];
		acs->can_buf.recv[i]=0;
	}
	chSysUnlock();
//	chMtxUnlock(&mtx);
// ******end critical section*******

	switch(recv[MSG_TYPE]){
		case NOP:
			break;
		case CHG_STATE:
			event = recv[ARG_BYTE];			
			break;
		case REPORT_STATUS:
	//		palClearLine(LINE_LED_GREEN);
			event = EV_STATUS;			
			break;
		case BLINK:
			// TODO: implement
			break;
		default:
	//		palClearLine(LINE_LED_GREEN);
			//event = EV_REP;			
			break;
	}

	if(event < EV_ANY || event >= EV_END){
	//	printf("error, event out of range\n");
		return (acs_event)acs->cur_state; 
	}

//	printf("event %s received\n", event_name[event+1]);
	return event;
}

static int acs_statemachine(ACS *acs){
	int i;
	palSetLine(LINE_LED_GREEN);
	acs->cur_state = state_init(acs);
	
	while (!chThdShouldTerminateX() && acs->cur_state != ST_OFF) {
		acs->event = getNextEvent(acs);
		for (i = 0;i < TRANS_COUNT;++i) {
			if((acs->cur_state == trans[i].state)||(ST_ANY == trans[i].state)){
				if((acs->event == trans[i].event)||(EV_ANY == trans[i].event)){
					acs->cur_state = (trans[i].fn)(acs);
					break;
				}
			}
		}
    chThdSleepMilliseconds(500);
	}
	
	return EXIT_SUCCESS;
}

extern int acsInit(ACS *acs){
	(void)acs;

	return EXIT_SUCCESS;
}

THD_WORKING_AREA(wa_acsThread,WA_ACS_THD_SIZE);
THD_FUNCTION(acsThread,acs){
//  (void)arg;
  chRegSetThreadName("acsThread");

	acs_statemachine(acs);
  
//	while (!chThdShouldTerminateX()) {
//    chThdSleepMilliseconds(500);
//  }
}
