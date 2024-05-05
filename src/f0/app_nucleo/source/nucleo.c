#include "ch.h"
#include "nucleo.h"
#include "CANopen.h"
#include "chprintf.h"
#include "OD.h"

#define ENABLE_NV_MEMORY_UPDATE_CODE      0
#define ENABLE_SERIAL_DEBUG_OUTPUT        1

#if ENABLE_SERIAL_DEBUG_OUTPUT || ENABLE_NV_MEMORY_UPDATE_CODE
#define DEBUG_SERIAL    (BaseSequentialStream*) &SD2

#define dbgprintf(str, ...) chprintf((BaseSequentialStream*) &SD2, str, ##__VA_ARGS__)
#else
#define dbgprintf(str, ...)
#endif

/**
 *
 * blinking example thread definition 
 * counts blinks and saves to tpdo
*/
THD_WORKING_AREA(blink_wa, 0x400);
THD_FUNCTION(blink, arg)
{
  
  (void)arg;
  uint16_t blinkcount = 0;

  while (!chThdShouldTerminateX()) 
  {
    if(blinkcount % 10 == 0)
    {
      chprintf(DEBUG_SERIAL, "%u\r\n",blinkcount);
    }
    palClearLine(LINE_LED);
    chThdSleepMilliseconds(500);
    palSetLine(LINE_LED);
    chThdSleepMilliseconds(500);
    OD_RAM.x4000_blinks.blinkcount = ++blinkcount;
  }

  dbgprintf("Terminating blink thread...\r\n");

  palClearLine(LINE_LED);
  chThdExit(MSG_OK);
}
