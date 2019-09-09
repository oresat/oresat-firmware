#include "acs.h"
#include "ch.h"
#include "hal.h"

/**
 *	event_lister is used for synchronization between 
 *	the ACS and the CAN thread
 */
static event_listener_t el;

/**
 *	@brief ACS initialization function
 */
extern EXIT_STATUS acs_init(ACS *acs)
{
	(void)acs;
	// need to initialize things
  bldcInit(&acs->motor);
  mtqrInit(&acs->mtqr);
	return STATUS_SUCCESS;
}	

/**
 *	@brief updates current CAN_SM_STATE to the value of next_state
 */
inline static EXIT_STATUS entry_helper(ACS *acs, ACS_VALID_STATE next_state)
{
/// ******critical section***********
	chSysLock();
	acs->can_buf.status[CAN_SM_STATE] = next_state;
	chSysUnlock();
/// ******end critical section*******
  
  dbgSerialOut("entry_helper: %u \n\r", next_state, 500);
	
  return STATUS_SUCCESS;
}

/**
 *	@brief updates CAN_SM_PREV_STATE buffer to the value of CAN_SM_STATE
 * 
 *	@brief buffer. this relects the change of the current state to previous
 */
inline static EXIT_STATUS exit_helper(ACS *acs)
{
  dbgSerialOut("exit_helper: %u \n\r", acs->can_buf.status[CAN_SM_STATE], 500);

/// ******critical section***********
	chSysLock();
	acs->can_buf.status[CAN_SM_PREV_STATE] = acs->can_buf.status[CAN_SM_STATE];
	chSysUnlock();
/// ******end critical section*******
	
  return STATUS_SUCCESS;
}

/**
 *	@brief enter state transistion function
 *
 *	@param acs pointer to an ACS struct
 */
static ACS_VALID_STATE entry_rdy(ACS *acs)
{
  entry_helper(acs, ST_RDY);
	
  return ST_RDY;
}

/**
 *	@brief exit state transistion function
 *
 *	@param acs pointer to an ACS struct
 */
static ACS_VALID_STATE exit_rdy(ACS *acs)
{
  exit_helper(acs);
  
  return ST_RDY;
}

/**
 *	@brief enter state transistion function
 *
 *	@param acs pointer to an ACS struct
 */
static ACS_VALID_STATE entry_rw(ACS *acs)
{
  entry_helper(acs, ST_RW);

  return ST_RW;
}

/**
 *	@brief exit state transistion function
 *
 *	@param acs pointer to an ACS struct
 */
static ACS_VALID_STATE exit_rw(ACS *acs)
{
  exit_helper(acs);

  return ST_RW;
}

/**
 *	ST_MTQR state transistion functions
 */

/**
 *	@brief enter state transistion function
 *
 *	@param acs pointer to an ACS struct
 */ 
static ACS_VALID_STATE entry_mtqr(ACS *acs)
{
  entry_helper(acs, ST_MTQR);
	
  return ST_MTQR;
}

/**
 *	@brief exit state transistion function
 *
 *	@param acs pointer to an ACS struct
 */
static ACS_VALID_STATE exit_mtqr(ACS *acs)
{
  exit_helper(acs);
	
  return ST_MTQR;
}

/**
 *	ST_MAX_POWER state transistion functions
 *
 *	TODO: change the name of this to more acurately
 *	reflect it's intent
 */
static ACS_VALID_STATE entry_max_pwr(ACS *acs)
{
  entry_helper(acs, ST_MAX_PWR);
	
  return ST_MAX_PWR;
}

/**
 *	@brief exit state transistion function
 *
 *	@param acs pointer to an ACS struct
 */
static ACS_VALID_STATE exit_max_pwr(ACS *acs)
{
  exit_helper(acs);
	
  return ST_MAX_PWR;
}

/**
 *	Function definitions
 *
 *	These functions are validified using the acs_function_rule 
 *	struct. Functions are represented in the struct by pointers
 *	which are associated with a valid state and valid function 
 *	name to create a rule that allows functions to only be called 
 *	from an allowed state.
 */

/**
 *	Start reaction wheel
 */
static EXIT_STATUS fn_rw_start(ACS *acs)
{
	(void)acs;
  chprintf(DEBUG_CHP, "start bldc\n\r");

//* 
  chSysLock(); 
  acs->can_buf.status[CAN_SEMAPHORE_STATE] = chBSemGetStateI(acs->motor.pBldc_bsem)+1;
  chSysUnlock(); 
//*/

  bldcStart(&acs->motor); 
  return STATUS_SUCCESS;
}
//*/

/**
 *	Stop reaction wheel
 */
static EXIT_STATUS fn_rw_stop(ACS *acs)
{
	(void)acs;
  chprintf(DEBUG_CHP, "stop bldc\n\r");
  bldcStop(&acs->motor);

//* 
  chSysLock(); 
  acs->can_buf.status[CAN_SEMAPHORE_STATE] = chBSemGetStateI(acs->motor.pBldc_bsem)+1;
  chSysUnlock(); 
//*/

	return STATUS_SUCCESS;
}
//*/

/**
 *	Set reaction wheel duty cycle
 */
static EXIT_STATUS fn_rw_setdc(ACS *acs)
{
	(void)acs;
  
	return STATUS_SUCCESS;
}

/**
 *	Start magnetorquer 
 */
static EXIT_STATUS fn_mtqr_start(ACS *acs)
{
	(void)acs;
  chprintf(DEBUG_CHP, "start mtqr\n\r");
  mtqrStart(&acs->mtqr); 
	return STATUS_SUCCESS;
}

/**
 *	Stop magnetorquer 
 */
static EXIT_STATUS fn_mtqr_stop(ACS *acs)
{
	(void)acs;
  chprintf(DEBUG_CHP, "stop mtqr\n\r");
  mtqrStop(&acs->mtqr); 
	return STATUS_SUCCESS;
}

/**
 *	Set magnetorquer duty cycle
 */
static EXIT_STATUS fn_mtqr_setdc(ACS *acs)
{
	(void)acs;

	return STATUS_SUCCESS;
}

/**
 *	Set magnetorquer duty cycle
 *
 *	This table enforces functions being
 *	called from a valid state. 
 *
 *	Match functin with states its allowd to be
 *	called from
 */
static acs_function_rule func[] = 
{
	{ST_RW, 			FN_RW_SETDC,		&fn_rw_setdc},
	{ST_RW, 			FN_RW_START,		&fn_rw_start},
	{ST_RW, 			FN_RW_STOP, 		&fn_rw_stop},
	{ST_MTQR, 		FN_MTQR_SETDC,	&fn_mtqr_setdc},
	{ST_MTQR, 		FN_MTQR_START,	&fn_mtqr_start},
	{ST_MTQR, 		FN_MTQR_STOP,	  &fn_mtqr_stop},
	{ST_MAX_PWR, 	FN_RW_SETDC,		&fn_rw_setdc},
	{ST_MAX_PWR, 	FN_MTQR_SETDC,	&fn_mtqr_setdc}
};

#define FUNC_COUNT (int)(sizeof(func)/sizeof(acs_function_rule))

/**
 *
 */
static EXIT_STATUS callFunction(ACS *acs)
{
	int i;
	EXIT_STATUS status = STATUS_SUCCESS;

  dbgSerialOut("Entering callFunction: %u \n\r", status, 300);
  //*
	for(i = 0;i < FUNC_COUNT;++i)
  {
		if(acs->state.current == func[i].state)
    {
			if(acs->function == func[i].function)
      {
				status = (func[i].fn)(acs);
				if(status != STATUS_SUCCESS)
        {
          dbgSerialOut("funcionCallError: %u \n\r", status, 300);
				}
				break;
			}
		}
	}
//*/
	return status;
}

/**
 *	acs_transition_rule: defines valid state transitions
 *	and associates them with an entry and exit function
 */
static acs_transition_rule valid_transition[] = 
{
/**
 * --------state----------    ----transition functions------
 * this         next          entry func        exit func
 */
  {ST_RDY,			ST_RW,				&entry_rw,				&exit_rdy},
	{ST_RDY,			ST_MTQR,			&entry_mtqr,			&exit_rdy},
	{ST_RDY,			ST_MAX_PWR,		&entry_max_pwr,		&exit_rdy},
	{ST_RW,				ST_MAX_PWR,		&entry_max_pwr,		&exit_rw},
	{ST_MTQR,			ST_MAX_PWR,		&entry_max_pwr,		&exit_mtqr},
	{ST_RW,				ST_RDY,				&entry_rdy,				&exit_rw},
	{ST_MTQR,			ST_RDY,				&entry_rdy,				&exit_mtqr},
	{ST_MAX_PWR,	ST_RDY,				&entry_rdy,				&exit_max_pwr},
	{ST_MAX_PWR,	ST_RW,				&entry_rw,				&exit_max_pwr},
	{ST_MAX_PWR,	ST_MTQR,			&entry_mtqr,			&exit_max_pwr},
};

/// Keep track of the number of transitions in 
#define TRANS_COUNT (int)(sizeof(valid_transition)/sizeof(acs_transition_rule))

/**
 *  @brief
 *
 *  @param 
 */
static EXIT_STATUS requestFunction(ACS *acs)
{
	ACS_VALID_FUNCTION function = acs->cmd[CAN_CMD_ARG];

	if(function <= FN_NOP || function >= FN_END)
  {
    dbgSerialOut("error, invalid function call: %%u\n\r", function, 1000);
		return STATUS_FAILURE; 
	}
  //dbgSerialOut("function request received\n: %%u\n\r", function, 1000);
	acs->function = function;
	callFunction(acs);
	return STATUS_SUCCESS;
}

/**
 *	transitionState
 */
static EXIT_STATUS transitionState(ACS *acs)
{
	ACS_VALID_STATE state = acs->cmd[CAN_CMD_ARG];

  dbgSerialOut("StateRequest: %u\n\r", state, 500);
	
  if(state <= ST_NOP || state >= ST_END)
  {
    dbgSerialOut("InvalidState: %u \n\r", state, 500);
		return STATUS_INVALID_STATE; 
	}

	for (int i = 0;i < TRANS_COUNT;++i)
  {
		if((acs->state.current == valid_transition[i].cur_state) && 
        (state == valid_transition[i].req_state))
    {
      dbgSerialOut("ValidChange: %u\n\r", state, 1000);
      
      acs->fn_exit(acs);
			acs->fn_exit=valid_transition[i].fn_exit;
			acs->state.current = (valid_transition[i].fn_entry)(acs);

			return STATUS_SUCCESS;
		}
    else
    {
      dbgSerialOut("InvalidChange: %u\n\r", state, 1000);
    }
	}

	return STATUS_INVALID_TRANSITION;
}

static EXIT_STATUS changeStatus(ACS *acs, uint8_t can_status, EXIT_STATUS status)
{
  /// ******critical section********
    chSysLock();
    acs->can_buf.status[can_status] = status;
    chSysUnlock();
	/// ******end critical section*******
  
  return STATUS_SUCCESS;
}

static EXIT_STATUS receiveCommand(ACS *acs)
{
  /// ******critical section*******
	chSysLock();
	for(int i = 0;i < CAN_BUF_SIZE; ++i){
		acs->cmd[i] = acs->can_buf.cmd[i];
		acs->can_buf.cmd[i] = 0x00;
	}
	chSysUnlock();
  /// ******end critical section*******
	
  return STATUS_SUCCESS;
}

/**
 *	handles events off the CAN bus
 */
static EXIT_STATUS handleEvent(ACS *acs)
{
	EXIT_STATUS status = STATUS_SUCCESS;

  /// block until there is an event from CAN
  chEvtWaitAny(ALL_EVENTS);	
  receiveCommand(acs); // should probably rename to be more descriptive

  dbgSerialOut("CommandReceived: %u \n\r", acs->cmd[CAN_CMD_0], 1000);
	
  switch(acs->cmd[CAN_CMD_0])
  {
    case CMD_NOP:
      break;
		case CMD_CHANGE_STATE:
			status = transitionState(acs);
      changeStatus(acs, CAN_SM_STATUS, status);
			break;
		case CMD_CALL_FUNCTION:
			status = requestFunction(acs);
			break;
		default:
			return STATUS_INVALID_CMD;
	}

	return status;
}

/**
 *	ACS statemachine entry
 */
static EXIT_STATUS acs_statemachine(ACS *acs)
{
	acs->state.current = entry_rdy(acs);
	acs->fn_exit = exit_rdy;
  
  dbgSerialOut("Entering acs_statemachine...\n\r", 0, 500);

  while(!chThdShouldTerminateX())
  {
		handleEvent(acs); // TODO: add error checking
    chThdSleepMilliseconds(100);
	}
	
	return STATUS_SUCCESS;
} 

/**
 *	ACS thread working area and thread *	function.
 */
THD_WORKING_AREA(waACS_Thread,ACS_THREAD_SIZE);
THD_FUNCTION(ACS_Thread,acs)
{
  chRegSetThreadName("acs_thread");
  
  chEvtRegister(&rpdo_event,&el,0);

	acs_statemachine(acs);
}

/**
 *	ACS debug loop
 */
#ifdef DEBUG_LOOP
THD_WORKING_AREA(waCANDBG_Thread,ACS_THREAD_SIZE);
THD_FUNCTION(CANDBG_Thread,acs)
{
  chRegSetThreadName("can_dbg_thread");
  
  uint8_t ping = 0u;
  
  while(1)
  {
    chSysLock();
    ((ACS *)acs)->can_buf.status[CAN_STATUS_PING] = ++ping;
    chSysUnlock();

    chThdSleepMilliseconds(5*1000);
  }
}
#endif


