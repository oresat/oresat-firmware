#include "nmt.h"

// Example blinker thread
THD_WORKING_AREA(nmt_wa, 128);
THD_FUNCTION(nmt, arg) {
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
