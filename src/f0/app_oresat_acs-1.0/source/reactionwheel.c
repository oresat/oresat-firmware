#include "reactionwheel.h"
#include "plut.h"

//bldc pbldc;

THD_WORKING_AREA(wa_spiEncoderThread,THREAD_SIZE);
THD_FUNCTION(spispiEncoderThread,pbldc){
  (void)arg;
  chRegSetThreadName("spiEncoderThread");
	int step;

  spiStart(&SPID1, &spicfg);            // Start driver.
  spiAcquireBus(&SPID1);                // Gain ownership of bus.

  while (!chThdShouldTerminateX()) {
		pbldc.rxbuf[0] = 0;
		spiSelect(&SPID1);                  // Select slave.

		while(SPID1.state != SPI_READY) {}   
		spiReceive(&SPID1,1,bldc.rxbuf);     		// Receive 1 frame (16 bits).
		spiUnselect(&SPID1);                // Unselect slave.

		pbldc.position = 0x3FFF & pbldc.rxbuf[0];
	 
		step = pbldc.position*360/(1<<14);
		chprintf(DEBUG_CHP,"enc pos: %u \n",pbldc.position);        
		chprintf(DEBUG_CHP,"phase 1: %u \n", step);     
		step = (step + pbldc.phase_shift)%360;
		chprintf(DEBUG_CHP,"phase 2: %u \n",step);     
		step = (step + pbldc.phase_shift)%360;
		chprintf(DEBUG_CHP,"phase 3: %u \n\n",step);     

		chThdSleepMilliseconds(100);
  }

	spiReleaseBus(&SPID1);    // Release ownership of bus.
	spiStop(&SPID1);          // Stop driver.
}

// pwm period callback
static void pwmpcb(PWMDriver *pwmp,bldc *pbldc) {
  (void)pwmp;
 	int step; 
//  palClearLine(LINE_LED_GREEN);
	
	++pbldc.count;
	
	if(pbldc.count==pbldc.stretch){
#ifdef OPENLOOP
		++pbldc.u;
		++pbldc.v;
		++pbldc.w;

		if(pbldc.u >= pbldc.steps){
			pbldc.u = 0;
		}
		if(pbldc.v >= pbldc.steps){
			pbldc.v = 0;
		}
		if(pbldc.w >= pbldc.steps){
			pbldc.w = 0;
		}
#endif
#ifndef OPENLOOP 
//*
		step = pbldc.position*360/(1<<14);
		pbldc.u = (step + 1 + pbldc.phase_shift)%360;
		pbldc.v = (pbldc.u + pbldc.phase_shift)%360;
		pbldc.w = (pbldc.v + pbldc.phase_shift)%360;
//*/
#endif
		pbldc.count=0;
	}
}

static sinctrl_t scale(sinctrl_t duty_cycle,bldc *pbldc){
	return (duty_cycle*pbldc.scale)/10;	
}

static void pwmCallback(uint8_t channel,sinctrl_t step,bldc *pbldc){
 // palSetLine(LINE_LED_GREEN);
  pwmEnableChannelI(
		&PWMD1,
		channel,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,scale(pbldc.sinctrl[step]))
	);
}

static void pwmUcb(PWMDriver *pwmp,bldc *pbldc){ // channel 1 callback
  (void)pwmp;
	pwmCallback(PWM_U,pbldc.u);
}

static void pwmVcb(PWMDriver *pwmp,bldc *pbldc){ // channel 2 callback
  (void)pwmp;
	pwmCallback(PWM_V,pbldc.v);
}

static void pwmWcb(PWMDriver *pwmp){ // channel 3 callback
  (void)pwmp;
	pwmCallback(PWM_W,pbldc.w);
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

extern void pbldcInit(bldc *pbldc){
	pbldc.steps = STEPS;
	pbldc.stretch = STRETCH;
	pbldc.scale = SCALE;
	pbldc.sinctrl = sinctrl360;
	pbldc.count = 0;
	pbldc.position = 0;
	pbldc.phase_shift = pbldc.steps/3;
	pbldc.u = 0;
	pbldc.v = pbldc.u + pbldc.phase_shift;
	pbldc.w = pbldc.v + pbldc.phase_shift;

//	pbldcStart();
}

extern void pbldcStart(bldc *pbldc){
	palSetLine(LINE_LED_GREEN);
	pwmStart(&PWMD1,&pwmcfg);
  pwmEnablePeriodicNotification(&PWMD1);

	pwmEnableChannel(&PWMD1,PWM_U,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,pbldc.u));
  pwmEnableChannel(&PWMD1,PWM_V,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,pbldc.v));
  pwmEnableChannel(&PWMD1,PWM_W,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,pbldc.w));

	pwmEnableChannelNotification(&PWMD1,PWM_U);
  pwmEnableChannelNotification(&PWMD1,PWM_V);
  pwmEnableChannelNotification(&PWMD1,PWM_W);
}

extern void pbldcStop(bldc *pbldc){
  palClearLine(LINE_LED_GREEN);
	pwmStop(&PWMD1);
/*
  pwmEnablePeriodicNotification(&PWMD1);

	pwmEnableChannel(&PWMD1,PWM_U,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,pbldc.u));
  pwmEnableChannel(&PWMD1,PWM_V,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,pbldc.v));
  pwmEnableChannel(&PWMD1,PWM_W,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,pbldc.w));

	pwmEnableChannelNotification(&PWMD1,PWM_U);
  pwmEnableChannelNotification(&PWMD1,PWM_V);
  pwmEnableChannelNotification(&PWMD1,PWM_W);
*/
}
