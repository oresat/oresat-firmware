#include "ch.h"
#include "hal.h"
#include "acs_bldc.h"

static THD_WORKING_AREA(wa_bldcThread, 128);
static THD_FUNCTION(bldcThread, arg) {
  (void)arg;
  chRegSetThreadName("bldc");

//	bldcStart();
	bldcSinStart();	
	// Changes PWM period to half second the duty cycle becomes 50%
  // implicitly.
 // pwmChangePeriod(&PWMD1, 5000);
 // chThdSleepMilliseconds(5000);


}

static void app_init(void){
 	bldcInit();

}

static void app_main(void){
	chThdCreateStatic(
			wa_bldcThread,
			sizeof(wa_bldcThread), 
			NORMALPRIO, 
			bldcThread, 
			NULL
	);
	
	while(true){
  	chThdSleepMilliseconds(500);
	}
}

int main(void) {
  halInit();
  chSysInit();

	app_init();
	app_main();

	while (true) {
    chThdSleepMilliseconds(500);
  }
  return 0;
}
