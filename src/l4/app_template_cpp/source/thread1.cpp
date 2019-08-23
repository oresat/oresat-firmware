#include "thread1.h"

/// Example blinker thread
THD_WORKING_AREA(waThread1, 128);
THD_FUNCTION(Thread1, arg) 
{
  (void)arg;
  chRegSetThreadName("thread1");

  while(!chThdShouldTerminateX()) 
  {
    palClearLine(LINE_LED_GREEN);
    chThdSleepMilliseconds(500);
    palSetLine(LINE_LED_GREEN);
    chThdSleepMilliseconds(500);
  }
}
