#ifndef _ACS_H_
#define _ACS_H_

#include "ch.h"
#include "hal.h"
#include "bldc.h"
#include "magnetorquer.h"
#include "chprintf.h"
#include "oresat.h"

/**
 * TODO: Thread sizes cause continual problems for managing memory
 * if the threads are too small it breaks, if the thread working
 * areas are too large then you run out of memory. One solution 
 * is to move to a mcu with more memory.
 */
#define WA_ACS_THD_SIZE (1<<7)
#define CAN_NODE 				0x3F // max 0x7f
#define CAN_BUF_SIZE 		8

#define DEBUG_SERIAL SD2
#define DEBUG_CHP ((BaseSequentialStream *) &DEBUG_SERIAL)

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

/**
 *	@brief can_msg enumeraton
 *
 *	TODO: This is going to change in v2.0 once a protocol
 *	is decided for communication with the ACS
 *
 * 	Byte		Name				Use
 * 	0 			MSG_TYPE		CHG_STATE is the only current implementation
 *	1				ARG_BYTE		used for passing arguments
 *	2				ARG_BYTE1		used for passing arguments
 *	3				ARG_BYTE2		used for passing arguments
 *	4				unimplemented
 *	5				unimplemented
 *	6				unimplemented
 *	7				unimplemented
 *
 */
typedef enum{
	MSG_TYPE=0,
	ARG_BYTE,
	ARG_BYTE1,
	ARG_BYTE2
}can_msg;

/**
 * @brief enumeration for the recv buffer
 *
 *	TODO: This is going to change in v2.0 once a protocol
 *	is decided for communication with the ACS
 *
 *	Byte		Name				Use
 * 	0 			unimplemented
 *	1				STATE				current state
 *	2				LAST_EVENT	last event received
 *	3				unimplemented
 *	4				unimplemented
 *	5				unimplemented
 *	6				unimplemented
 *	7				unimplemented
 *
 */
typedef enum{
	ERROR_CODE = 0,
	ACS_STATE,
	LAST_EVENT,
	LAST_TRAP,
}can_recv;

/**
 * @brief enumeration for CAN message types
 *
 *	TODO: This is going to change in v2.0 once a protocol
 *	is decided for communication with the ACS
 *
 */
typedef enum{
	NOP=0,
	CHG_STATE,
	CALL_TRAP,
}can_msg_type;

/**
 * @brief enumeration for ACS states
 *
 *	TODO: This is going to change in v2.0 to more
 *	accurately reflect how the ACS will operate
 *
 */
typedef enum{
	ST_ANY=-1,
	ST_OFF,
	ST_INIT,
	ST_RDY,
	ST_RW,
	ST_MTQR
}acs_state;

/**
 * @brief enumeration for all the possible events
 *
 *	TODO: This is going to change in v2.0 to more
 *	accurately reflect how the ACS will operate
 *
 * hexidecimal values are passed to the ACS via 
 * the bus.
 */
typedef enum {
	EV_ANY=-1,      ///< -1
	EV_OFF,					///< 0
	EV_INIT,				///< 1
	EV_RDY,					///< 2
	EV_RW,					///< 3
	EV_MTQR,				///< 4
	EV_RW_START,		///< 5
	EV_RW_STOP,			///< 6
  EV_RW_STRETCH,  ///< 7
  EV_RW_CONTROL,  ///< 8
  EV_RW_SKIP,     ///< 9
  EV_RW_SCALE,    ///< a
	EV_MTQR_START,  ///< b
	EV_MTQR_STOP,   ///< c
	EV_MTQR_DC,			///< d
	EV_MTQR_DIR,		///< e
	EV_END /// this must be the last event
}acs_event;

/**
 * @brief can_buffer structure holds the send and recv
 * buffers that are registered with the CAN bus
 *
 */
typedef struct{
	uint8_t send[CAN_BUF_SIZE];
	uint8_t recv[CAN_BUF_SIZE];	
}can_buffer;

/**
 * @brief ACS structure for maintaining the ACS state
 *
 * TODO: This structure is likely to change for v2.0
 */
typedef struct{
	acs_state cur_state;
	acs_event event; /// the most recent event
	can_buffer can_buf;
	bldc motor;
	MTQR mtqr;
  /// TODO find a better way to handle it
	/// data was a bandaid
  uint8_t data;
	uint8_t recv[CAN_BUF_SIZE];
}ACS;

/**
 * @brief structure for manipulating state transistions
 * and trap functions
 *
 */
typedef struct{
	acs_state state;
	acs_event event;
	int (*fn)(ACS *acs);
}acs_transition,acs_trap;

extern int acsInit(ACS *acs);

extern THD_WORKING_AREA(wa_acsThread,WA_ACS_THD_SIZE);
extern THD_FUNCTION(acsThread,acs);

#endif
