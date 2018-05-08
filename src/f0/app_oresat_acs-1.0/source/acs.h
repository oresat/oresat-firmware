#ifndef _ACS_H_
#define _ACS_H_

#include "ch.h"
#include "hal.h"
#include "chmtx.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define WA_ACS_THD_SIZE (1<<7)
#define CAN_NODE 				0x3F // max 0x7f
#define CAN_BUF_SIZE 		8

/*
 *	can_message
 *
 * 	Byte		Name		Use
 * 	0				
 *	1
 *	2
 *	3
 *	4
 *	5
 *
 *	CMD
 *
 *
 *
 *
 *
 */

typedef enum{
	MSG_TYPE=0,
	ARG_BYTE
}can_msg;

typedef enum{
	NOP=0,
	CHG_STATE,
	REP_STATE,
	BLINK
}can_msg_type;

extern char *state_name[];
extern char *event_name[];

typedef enum{
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
	uint8_t send[CAN_BUF_SIZE];
	uint8_t recv[CAN_BUF_SIZE];	
}can_buffer;

typedef struct{
	acs_state cur_state;
	acs_event event; // the most recent event
	can_buffer can_buf;
}ACS;

typedef struct{
	acs_state state;
	acs_event event;
	int (*fn)(ACS *acs);
}acs_transition,acs_trap;

//extern int acs_statemachine(ACS *acs);

extern int acsInit(ACS *acs);

extern THD_WORKING_AREA(wa_acsThread,WA_ACS_THD_SIZE);
extern THD_FUNCTION(acsThread,acs);

#endif
