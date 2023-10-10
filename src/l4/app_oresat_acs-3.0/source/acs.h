#ifndef _ACS_H_
#define _ACS_H_

#include "bldc.h"
#include "magnetorquer.h"
#include "acs_common.h"

#define ACS_THREAD_SIZE	(1<<7)

/**
 *	CAN definitions
 */
#define CAN_BUF_SIZE		8			/// bytes in buffer
#define CAN_NODE_ID			0x3F	/// max 0x7F

//#define DEBUG_OUT
//#define DEBUG_LOOP

/**
 *	Valid ACS states
 *
 *	TODO: states are going to be very different based on
 *	which MCU we use. Determine a base set of states for
 *	the F4 and then add appropriate low power states when
 *	the L4 becomes available
 */
typedef enum
{
	ST_NOP = 0,   /// 0
	ST_RDY,       /// 1
	ST_RW,        /// 2
	ST_MTQR,      /// 3
	ST_MAX_PWR,   /// 4
  /// do not add any states after ST_END
  ST_END      /// not an actual state
} ACS_VALID_STATE;

/**
 *	Valid Functions
 */
typedef enum
{
  FN_NOP = 0,     /// 0
  FN_RW_START,    /// 1
  FN_RW_STOP,     /// 2
  FN_RW_SETDC,    /// 3
	FN_MTQR_START,  /// 4
	FN_MTQR_STOP,   /// 5
	FN_MTQR_SETDC,  /// 6
  /// do not add any functions after FN_END
  FN_END /// not an actual function name
} ACS_VALID_FUNCTION;

/**
 *	ACS_VALID_COMMAND: Exhaustive list of valid commands
 *	received off the CAN bus
 */
typedef enum
{
	CMD_NOP = 0,
	CMD_CHANGE_STATE,
	CMD_CALL_FUNCTION,
  /// do not add any commands after CMD_END
  CMD_END
} ACS_VALID_COMMAND;

/**
 *	CAN buffer structure for command
 *	and status 
 */
typedef struct
{
	uint8_t cmd[CAN_BUF_SIZE];
	uint8_t status[CAN_BUF_SIZE];
} CAN_BUFFER;

/**
 *	State information struct
 */
typedef struct
{
	uint8_t last;
  uint8_t current;
  uint8_t next;
} ACS_STATE;

/**
 *	ACS: State and control information struct
 *  
 *  ACS predefinition to make the compiler happy
 *  when self referencing.
 */
typedef struct ACS ACS;

struct ACS
{
	ACS_STATE state;
	CAN_BUFFER can_buf;
	uint8_t cmd[CAN_BUF_SIZE];
	ACS_VALID_FUNCTION function;
	ACS_VALID_STATE (*fn_exit)(ACS *acs);
  BLDCMotor motor;
  MTQR mtqr;
};

/**
 *	acs_transition_rule: defines the structure of a valid
 *	transition.
 */
typedef struct
{
	ACS_VALID_STATE cur_state;
	ACS_VALID_STATE req_state;
	ACS_VALID_STATE (*fn_entry)(ACS *acs);
	ACS_VALID_STATE (*fn_exit)(ACS *acs);
} acs_transition_rule;

/**
 *	acs_function_rule: rule structure for the valid rule
 *	table
 */
typedef struct
{
	ACS_VALID_STATE state;
	ACS_VALID_FUNCTION function;
	EXIT_STATUS (*fn)(ACS *acs);
} acs_function_rule;

/**
 * Buffer for receiving commands off the CAN bus
 * TODO: These fields need to be defined and
 * adherred to 
 */
typedef enum
{
	CAN_CMD_0=0,
	CAN_CMD_ARG,	// CAN_CMD_1,
	CAN_CMD_2,    // not being used
	CAN_CMD_3,    // nbu atm
	CAN_CMD_4,    // nbu atm
	CAN_CMD_5,    // nbu atm
	CAN_CMD_6,    // nbu atm
	CAN_CMD_7,    // nbu atm
  CAN_CMD_END
} CAN_COMMAND_BUF;

/**
 * Buffer for maintaining and reporting both
 * state and ACS status information
 * TODO: These fields need to be defined and
 * adherred to 
 */
typedef enum
{
	CAN_SM_STATE = 0,     //
	CAN_SM_PREV_STATE,    //
	CAN_SM_STATUS,        //
	CAN_FN_CALLED,        //
	CAN_FN_STATUS,        //
	CAN_SEMAPHORE_STATE,  // nbu
	CAN_STATUS_6,         // nbu
	CAN_STATUS_PING,      // CAN_STATUS_7 // for CAN dbg
  CAN_STATUS_END
} CAN_STATUS_BUF;

extern THD_WORKING_AREA(waACS_Thread,ACS_THREAD_SIZE);
extern THD_FUNCTION(ACS_Thread, arg);

#ifdef DEBUG_LOOP
THD_WORKING_AREA(waCANDBG_Thread,ACS_THREAD_SIZE);
THD_FUNCTION(CANDBG_Thread, arg);
#endif

EXIT_STATUS acs_init(ACS *acs);

#endif // end _ACS_H_
