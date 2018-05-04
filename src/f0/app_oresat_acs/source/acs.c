#include "acs.h"
#include "acs_lut.h"

BldcConfig bldc;
uint16_t rxbuf[2] = {0}; // receive buffer

THD_WORKING_AREA(wa_acsThread,THREAD_SIZE);
THD_FUNCTION(acsThread,arg) {
  (void)arg;
  chRegSetThreadName("acsThread");

  while(!chThdShouldTerminateX()){
		switch(bldc.data->recv[0]){
			case 0:
				break;
			case 1:
				bldcStart();
				break;
			case 2:
				bldcStop();
				break;
			default:
				break;
		}
		memcpy(bldc.data->send,bldc.data->recv,CAN_BUF);	
		chThdSleepMilliseconds(100);
  }
}

THD_WORKING_AREA(wa_spiThread,THREAD_SIZE);
THD_FUNCTION(spiThread,arg){
  (void)arg;
  chRegSetThreadName("spiThread");
	int step;

  spiStart(&SPID1, &spicfg);            // Start driver.
  spiAcquireBus(&SPID1);                // Gain ownership of bus.

  while (!chThdShouldTerminateX()) {
		rxbuf[0] = 0;
		spiSelect(&SPID1);                  // Select slave.

		while(SPID1.state != SPI_READY) {}   
		spiReceive(&SPID1,1,rxbuf);     		// Receive 1 frame (16 bits).
		spiUnselect(&SPID1);                // Unselect slave.

		bldc.position = 0x3FFF & rxbuf[0];
	 
		step = bldc.position*360/(1<<14);
		chprintf(DEBUG_CHP,"enc pos: %u \n",bldc.position);        
		chprintf(DEBUG_CHP,"phase 1: %u \n", step);     
		step = (step + bldc.phase_shift)%360;
		chprintf(DEBUG_CHP,"phase 2: %u \n",step);     
		step = (step + bldc.phase_shift)%360;
		chprintf(DEBUG_CHP,"phase 3: %u \n\n",step);     

		chThdSleepMilliseconds(100);
  }

	spiReleaseBus(&SPID1);    // Release ownership of bus.
	spiStop(&SPID1);          // Stop driver.
}

// pwm period callback
static void pwmpcb(PWMDriver *pwmp) {
  (void)pwmp;
 	int step; 
//  palClearLine(LINE_LED_GREEN);
	
	++bldc.count;
	
	if(bldc.count==bldc.stretch){
#ifdef OPENLOOP
		++bldc.u;
		++bldc.v;
		++bldc.w;

		if(bldc.u >= bldc.steps){
			bldc.u = 0;
		}
		if(bldc.v >= bldc.steps){
			bldc.v = 0;
		}
		if(bldc.w >= bldc.steps){
			bldc.w = 0;
		}
#endif
#ifndef OPENLOOP 
//*
		step = bldc.position*360/(1<<14);
		bldc.u = (step + 1 + bldc.phase_shift)%360;
		bldc.v = (bldc.u + bldc.phase_shift)%360;
		bldc.w = (bldc.v + bldc.phase_shift)%360;
//*/
#endif
		bldc.count=0;
	}
}

static sinctrl_t scale(sinctrl_t duty_cycle){
	return (duty_cycle*bldc.scale)/10;	
}

static void pwmCallback(uint8_t channel,sinctrl_t step){
 // palSetLine(LINE_LED_GREEN);
  pwmEnableChannelI(
		&PWMD1,
		channel,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,scale(bldc.sinctrl[step]))
	);
}

static void pwmUcb(PWMDriver *pwmp){ // channel 1 callback
  (void)pwmp;
	pwmCallback(PWM_U,bldc.u);
}

static void pwmVcb(PWMDriver *pwmp){ // channel 2 callback
  (void)pwmp;
	pwmCallback(PWM_V,bldc.v);
}

static void pwmWcb(PWMDriver *pwmp){ // channel 3 callback
  (void)pwmp;
	pwmCallback(PWM_W,bldc.w);
}

static PWMConfig pwmcfg = {
  PWM_TIMER_FREQ,	
  PWM_PERIOD,	
  pwmpcb,
  {
   {PWM_OUTPUT_ACTIVE_HIGH|PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH,pwmUcb},
   {PWM_OUTPUT_ACTIVE_HIGH|PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH,pwmVcb},
   {PWM_OUTPUT_ACTIVE_HIGH|PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH,pwmWcb},
   {PWM_OUTPUT_DISABLED, NULL}
  },
  0,
	0,
  0
};

extern void acsInit(ACSdata *data){
	bldc.data = data;
	bldcInit();
}

extern void bldcInit(){
	bldc.steps = STEPS;
	bldc.stretch = STRETCH;
	bldc.scale = SCALE;
	bldc.sinctrl = sinctrl360;
	bldc.count = 0;
  bldc.position = 0;
  bldc.phase_shift = bldc.steps/3;
  bldc.u = 0;
  bldc.v = bldc.u + bldc.phase_shift;
  bldc.w = bldc.v + bldc.phase_shift;

//	bldcStart();
}

extern void bldcStart(){
	palSetLine(LINE_LED_GREEN);
	pwmStart(&PWMD1,&pwmcfg);
  pwmEnablePeriodicNotification(&PWMD1);

	pwmEnableChannel(&PWMD1,PWM_U,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,bldc.u));
  pwmEnableChannel(&PWMD1,PWM_V,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,bldc.v));
  pwmEnableChannel(&PWMD1,PWM_W,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,bldc.w));

	pwmEnableChannelNotification(&PWMD1,PWM_U);
  pwmEnableChannelNotification(&PWMD1,PWM_V);
  pwmEnableChannelNotification(&PWMD1,PWM_W);
}

extern void bldcStop(){
  palClearLine(LINE_LED_GREEN);
	pwmStop(&PWMD1);
/*
  pwmEnablePeriodicNotification(&PWMD1);

	pwmEnableChannel(&PWMD1,PWM_U,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,bldc.u));
  pwmEnableChannel(&PWMD1,PWM_V,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,bldc.v));
  pwmEnableChannel(&PWMD1,PWM_W,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,bldc.w));

	pwmEnableChannelNotification(&PWMD1,PWM_U);
  pwmEnableChannelNotification(&PWMD1,PWM_V);
  pwmEnableChannelNotification(&PWMD1,PWM_W);
*/
}
