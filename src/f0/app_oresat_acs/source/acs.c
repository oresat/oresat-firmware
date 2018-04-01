#include "acs.h"

/*
static ACSConfig acscfg = {
	// ACSConfig initializer
};
//*/

extern void acs_init(void){

}

// ACS thread
THD_WORKING_AREA(wa_acsThread,THREAD_SIZE);
THD_FUNCTION(acsThread,arg) {

  (void)arg;
  chRegSetThreadName("acsThread");

  while (!chThdShouldTerminateX()) {
//  palClearLine(LINE_LED_GREEN);
//  chThdSleepMilliseconds(500);
//  palSetLine(LINE_LED_GREEN);
//  chThdSleepMilliseconds(500);
  }
}
