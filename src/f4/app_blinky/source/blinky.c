#include "blinky.h"

// Green LED blinker thread, times are in milliseconds.
THD_WORKING_AREA(waThread1, 128);
THD_FUNCTION(Thread1, arg) {

  (void)arg;
  chRegSetThreadName("blinker");

  palSetLineMode(LINE_LED_GREEN,PAL_MODE_OUTPUT_PUSHPULL);

  while (!chThdShouldTerminateX()) {
    palClearLine(LINE_LED_GREEN);
    chThdSleepMilliseconds(500);
    palSetLine(LINE_LED_GREEN);
    chThdSleepMilliseconds(500);
  }
}
