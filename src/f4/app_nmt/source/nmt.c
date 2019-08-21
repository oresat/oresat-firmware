#include "nmt.h"

// Example blinker thread
THD_WORKING_AREA(nmt_wa, 128);
THD_FUNCTION(nmt, arg) {
  (void)arg;

  palSetLineMode(LINE_LED_GREEN,PAL_MODE_OUTPUT_PUSHPULL);

  while (!chThdShouldTerminateX()) {
    palClearLine(LINE_LED_GREEN);
    chThdSleepMilliseconds(500);
    palSetLine(LINE_LED_GREEN);
    chThdSleepMilliseconds(500);
  }

  palClearLine(LINE_LED_GREEN);
  chThdExit(MSG_OK);
}
