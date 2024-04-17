#include "ch.h"
#include "heartmon.h"
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

/* heartmon monitoring thread */
THD_WORKING_AREA(heartmon_wa, 0x400);
THD_FUNCTION(heartmon, arg)
{
  
  (void)arg;
  uint16_t blinkcount = 0;

  //TODO: Count heartbeats instead of blinks:
  
  while (!chThdShouldTerminateX()) 
  {
    palClearLine(LINE_LED);
    chThdSleepMilliseconds(500);
    palSetLine(LINE_LED);
    chThdSleepMilliseconds(500);
    OD_RAM.x4000_blinks.blinkcount = ++blinkcount;
  }

  dbgprintf("Terminating heartmon thread...\r\n");

  palClearLine(LINE_LED);
  chThdExit(MSG_OK);
}
