#include "acs.h"

/*
static ACSConfig acscfg = {
	// ACSConfig initializer
};
//*/

extern void acs_init(void){

}

struct{
	uint8_t acs[8];
} ACSdata;

ACSdata data;
// ACS thread
THD_WORKING_AREA(waACSThread,128);
THD_FUNCTION(ACSThread,arg) {

  (void)arg;
  chRegSetThreadName("acsthread");

  while (!chThdShouldTerminateX()) {
    palClearLine(LINE_LED_GREEN);
    chThdSleepMilliseconds(500);
    palSetLine(LINE_LED_GREEN);
    chThdSleepMilliseconds(500);
  }
}
