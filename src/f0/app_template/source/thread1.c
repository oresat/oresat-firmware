#include "thread1.h"

// Example blinker thread
THD_WORKING_AREA(waThread1, 64);
THD_FUNCTION(Thread1, arg) {
  (void)arg;

  while (!chThdShouldTerminateX()) {
    palClearLine(LINE_LED_GREEN);
    chThdSleepMilliseconds(500);
    palSetLine(LINE_LED_GREEN);
    chThdSleepMilliseconds(500);
  }

  palClearLine(LINE_LED_GREEN);
  chThdExit(MSG_OK);
}
