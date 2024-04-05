#include "ch.h"
#include "heartbeat.h"
#include "CANopen.h"
#include "chprintf.h"
#include "OD.h"

#define ENABLE_NV_MEMORY_UPDATE_CODE      0
#define ENABLE_SERIAL_DEBUG_OUTPUT        0

#if ENABLE_SERIAL_DEBUG_OUTPUT || ENABLE_NV_MEMORY_UPDATE_CODE
#define DEBUG_SERIAL    (BaseSequentialStream*) &SD2

#define dbgprintf(str, ...) chprintf((BaseSequentialStream*) &SD2, str, ##__VA_ARGS__)
#else
#define dbgprintf(str, ...)
#endif

/* heartbeat monitoring thread */
THD_WORKING_AREA(heartbeat_wa, 0x400);
THD_FUNCTION(heartbeat, arg)
{
  (void)arg;
  
  while (!chThdShouldTerminateX()) 
  {
     palClearLine(LINE_LED);
     chThdSleepMilliseconds(500);
     palSetLine(LINE_LED);
     chThdSleepMilliseconds(500);
  }

  dbgprintf("Terminating heartbeat thread...\r\n");

  palClearLine(LINE_LED);
  chThdExit(MSG_OK);
}
