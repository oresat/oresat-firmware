#include "acs.h" 

event_listener_t el;

/*
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
	"EV_RW_START",
	"EV_RW_STOP",
  "EV_RW_STRETCH",
  "EV_RW_CONTROL",
  "EV_RW_SKIP",     
  "EV_RW_SCALE",    
	"EV_MTQR_START",
	"EV_MTQR_STOP",
	"EV_END"
};
//*/

//#define STATE_STRING "*Calling transition -> " 
//#define TRAP_STRING "*Calling trap -> " 

static void trans_cleanup(ACS *acs){
	switch(acs->cur_state){
		case ST_OFF:
			
			break;
		case ST_INIT:

			break;
		case ST_RDY:

			break;

		case ST_RW:
			bldcExit(&acs->motor);
			break;

		case ST_MTQR:
			mtqrExit(&acs->mtqr);
			break;
		default:

			break;
	}
}

static void update_recv(ACS *acs,int recv_byte){
	switch(recv_byte){
		case ERROR_CODE:
			break;
		case ACS_STATE:
// *******critical section**********
			chSysLock();
			acs->can_buf.send[recv_byte]=acs->cur_state;
			chSysUnlock();
// *******end critical section**********
			break;
		default:
			break;
	}
}

static int state_off(ACS *acs){
	(void)acs;
	return ST_OFF;
}

static int state_init(ACS *acs){
	(void)acs;
	return ST_INIT;
}

static int state_rdy(ACS *acs){
	(void)acs;
	trans_cleanup(acs);
	return ST_RDY;
}

static int state_rw(ACS *acs){
	(void)acs;
	trans_cleanup(acs);
	bldcInit(&acs->motor);
	return ST_RW;
}

static int state_mtqr(ACS *acs){
	(void)acs;
	trans_cleanup(acs);
//	mtqrInit(&acs->mtqr);
	return ST_MTQR;
}

static int trap_rw_start(ACS *acs){
	// *******critical section**********
	chSysLock();
	acs->can_buf.send[LAST_TRAP]=EV_RW_START;
	chSysUnlock();
	// *******end critical section**********
	bldcStart(&acs->motor);
	return EXIT_SUCCESS;
}

static int trap_rw_stop(ACS *acs){
	// *******critical section**********
	chSysLock();
	acs->can_buf.send[LAST_TRAP]=EV_RW_STOP;
	chSysUnlock();
	// *******end critical section**********
	bldcStop(&acs->motor);
	return EXIT_SUCCESS;
}

//*
static int trap_mtqr_start(ACS *acs){
	// *******critical section**********
	chSysLock();
	acs->can_buf.send[LAST_TRAP]=EV_MTQR_START;
	chSysUnlock();
	// *******end critical section**********
	mtqrStart(&acs->mtqr);
	return EXIT_SUCCESS;
}

static int trap_mtqr_stop(ACS *acs){
	(void)acs;
	// *******critical section**********
	chSysLock();
	acs->can_buf.send[LAST_TRAP]=EV_MTQR_STOP;
	chSysUnlock();
	// *******end critical section**********
	mtqrStop(&acs->mtqr);
	return EXIT_SUCCESS;
}
//*/

static int trap_rw_stretch(ACS *acs)
{
  (void)acs;
  // TODO have a better data system.
  acs->motor.stretch = acs->data;
  return EXIT_SUCCESS;
}

static int trap_rw_control(ACS *acs)
{
  (void)acs;
  // TODO have a better data system.
  acs->motor.openLoop = (bool) acs->data;
  return EXIT_SUCCESS;
}

static int trap_rw_skip(ACS *acs)
{
  (void)acs;
  // TODO have a better data system.
  acs->motor.skip = acs->data;
  return EXIT_SUCCESS;
}

static int trap_rw_scale(ACS *acs)
{
  (void)acs;
  // TODO have a better data system.
  acs->motor.scale = acs->data;
  return EXIT_SUCCESS;
}

const acs_trap trap[] = {
	{ST_RW, 	EV_RW_START,		&trap_rw_start},
	{ST_RW, 	EV_RW_STOP,			&trap_rw_stop},
  {ST_RW,   EV_RW_STRETCH,	&trap_rw_stretch},
  {ST_RW,   EV_RW_CONTROL,	&trap_rw_control},
  {ST_RW,   EV_RW_SKIP,			&trap_rw_skip},
  {ST_RW,   EV_RW_SCALE,   	&trap_rw_scale},
	{ST_MTQR,	EV_MTQR_START,	&trap_mtqr_start},
	{ST_MTQR,	EV_MTQR_STOP,		&trap_mtqr_stop},
};

#define EVENT_COUNT (int)(sizeof(trap)/sizeof(acs_trap))

static int fsm_trap(ACS *acs){
	int i,trap_status;

	for(i = 0;i < EVENT_COUNT;++i){
		if(acs->event == trap[i].event){
			if(trap[i].state == ST_ANY || acs->cur_state == trap[i].state){
				trap_status = (trap[i].fn)(acs);
				if(trap_status){
					// *******critical section**********
					chSysLock();
					acs->can_buf.send[ERROR_CODE]=77;
					chSysUnlock();
					chThdSleepMilliseconds(500);
					// *******end critical section**********
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

// synchronized with the CAN thread
	chEvtWaitAny(ALL_EVENTS);	
// ******critical section*******
	chSysLock();
	for(int i=0;i<CAN_BUF_SIZE;++i){
		recv[i]=acs->can_buf.recv[i];
		acs->can_buf.recv[i]=0;
	}
	chSysUnlock();
// ******end critical section*******

	switch(recv[MSG_TYPE]){
		case NOP:
			break;
		case CHG_STATE:
			event = recv[ARG_BYTE];
      acs->data = recv[ARG_BYTE+1];			
			break;
		case CALL_TRAP:
			//	event = EV_STATUS;
			// TODO: we should seperate the trap from the change
			// state command
			break;
		default:
			break;
	}

	if(event < EV_ANY || event >= EV_END){
	//	printf("error, event out of range\n");
		return (acs_event)acs->cur_state; 
	}

	return event;
}

static int acs_statemachine(ACS *acs){
	int i;
	//palSetLine(LINE_LED_GREEN);
	
	acs->cur_state = state_init(acs);
	update_recv(acs,ACS_STATE);
	
	while (!chThdShouldTerminateX() && acs->cur_state != ST_OFF) {
		acs->event = getNextEvent(acs);
	
		// *******critical section**********
		chSysLock();
		acs->can_buf.send[LAST_EVENT]=acs->event;
		chSysUnlock();
		// *******end critical section**********
		
		for (i = 0;i < TRANS_COUNT;++i) {
			if((acs->cur_state == trans[i].state)||(ST_ANY == trans[i].state)){
				if((acs->event == trans[i].event)||(EV_ANY == trans[i].event)){
					acs->cur_state = (trans[i].fn)(acs);
					update_recv(acs,ACS_STATE);
				}
			}
		}
    chThdSleepMilliseconds(500);
    chprintf(DEBUG_CHP, "motor stretch: %d\r\n", acs->motor.stretch);
    chprintf(DEBUG_CHP, "motor openLoop: %d\r\n", acs->motor.openLoop);
    chprintf(DEBUG_CHP, "motor skip: %d\r\n\n", acs->motor.skip);
    chprintf(DEBUG_CHP, "motor scale: %d\r\n\n", acs->motor.scale);
    chprintf(DEBUG_CHP, "motor samples: %d\r\n\n", acs->motor.samples[0]);

	}
	
	return EXIT_SUCCESS;
}

extern int acsInit(ACS *acs){
	(void)acs;
	mtqrInit(&acs->mtqr);
	return EXIT_SUCCESS;
}

THD_WORKING_AREA(wa_acsThread,WA_ACS_THD_SIZE);
THD_FUNCTION(acsThread,acs){
  chRegSetThreadName("acsThread");
	chEvtRegister(&rpdo_event,&el,0);

	acs_statemachine(acs);
}

