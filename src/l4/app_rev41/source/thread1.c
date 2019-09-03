#include "thread1.h"
#include "chprintf.h"

/* Example blinker thread */
THD_WORKING_AREA(waThread1, 128);
THD_FUNCTION(Thread1, arg)
{
  (void)arg;

  while (!chThdShouldTerminateX()) {
  /*
    palClearLine(LINE_DEBUG_2);
    palClearLine(LINE_DEBUG_1);
  //*/
    palClearPad(GPIOB,1U);
    palClearPad(GPIOB,2U);
    chThdSleepMilliseconds(500);
  /*
    palSetLine(LINE_DEBUG_2);
    palSetLine(LINE_DEBUG_1);
  //*/
    palSetPad(GPIOB,1U);
    palSetPad(GPIOB,2U);
    chThdSleepMilliseconds(500);
  }

/*
  palClearLine(LINE_DEBUG_2);
  palClearLine(LINE_DEBUG_1);
//*/
  palClearPad(GPIOB,1U);
  palClearPad(GPIOB,2U);
  chThdExit(MSG_OK);
}
