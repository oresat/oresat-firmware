#include "bldc.h"
#include "sin_lut.h"

bldc *motor;

THD_WORKING_AREA(wa_spiThread,THREAD_SIZE);
THD_FUNCTION(spiThread,arg){
  (void)arg;
	chRegSetThreadName("spiThread");
	int step;

  spiStart(&SPID1,&spicfg);            	// Start driver.
  spiAcquireBus(&SPID1);                // Gain ownership of bus.

  while (!chThdShouldTerminateX()) {
		motor->spi_rxbuf[0] = 0;
		spiSelect(&SPID1);                  // Select slave.

		while(SPID1.state != SPI_READY) {}   
		spiReceive(&SPID1,1,motor->spi_rxbuf); // Receive 1 frame (16 bits).
		spiUnselect(&SPID1);                // Unselect slave.

		motor->position = 0x3FFF & motor->spi_rxbuf[0];
	 
		step = motor->position*360/(1<<14);
		chprintf(DEBUG_CHP,"enc pos: %u \n",motor->position);        
		chprintf(DEBUG_CHP,"phase 1: %u \n", step);     
		step = (step + motor->phase_shift)%360;
		chprintf(DEBUG_CHP,"phase 2: %u \n",step);     
		step = (step + motor->phase_shift)%360;
		chprintf(DEBUG_CHP,"phase 3: %u \n\n",step);     

		chThdSleepMilliseconds(100);
  }

	spiReleaseBus(&SPID1);    // Release ownership of bus.
	spiStop(&SPID1);          // Stop driver.
}

static sinctrl_t scale(sinctrl_t duty_cycle){
	return (duty_cycle*motor->scale)/10;	
}

static void pwmCallback(uint8_t channel,sinctrl_t step){
 // palSetLine(LINE_LED_GREEN);
//*
	pwmEnableChannelI(
		&PWMD1,
		channel,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,scale(motor->sinctrl[step]))
	);
//*/
}

// pwm period callback
static void pwmpcb(PWMDriver *pwmp) {
  (void)pwmp;
//  palClearLine(LINE_LED_GREEN);
	++motor->count;
	
	if(motor->count==motor->stretch){
#ifdef OPENLOOP
		++motor->u;
		++motor->v;
		++motor->w;

		if(motor->u >= motor->steps){
			motor->u = 0;
		}
		if(motor->v >= motor->steps){
			motor->v = 0;
		}
		if(motor->w >= motor->steps){
			motor->w = 0;
		}
#endif
#ifndef OPENLOOP 
//*
 		int step; 
		step = motor->position*360/(1<<14);
		motor->u = (step + 1 + motor->phase_shift)%360;
		motor->v = (motor->u + motor->phase_shift)%360;
		motor->w = (motor->v + motor->phase_shift)%360;
//*/
#endif
		motor->count=0;
	}
}

static void pwmUcb(PWMDriver *pwmp){ // channel 1 callback
  (void)pwmp;
	pwmCallback(PWM_U,motor->u);
}

static void pwmVcb(PWMDriver *pwmp){ // channel 2 callback
  (void)pwmp;
	pwmCallback(PWM_V,motor->v);
}

static void pwmWcb(PWMDriver *pwmp){ // channel 3 callback
  (void)pwmp;
	pwmCallback(PWM_W,motor->w);
}

static PWMConfig pwmRWcfg = {
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

extern void bldcInit(bldc *pbldc){
	motor = pbldc;
	motor->steps = STEPS;
	motor->stretch = STRETCH;
	motor->scale = SCALE;
	motor->sinctrl = sinctrl360;
	motor->count = 0;
	motor->position = 0;
	motor->phase_shift = motor->steps/3;
	motor->u = 0;
	motor->v = motor->u + motor->phase_shift;
	motor->w = motor->v + motor->phase_shift;

//*
	motor->p_spi_thread=chThdCreateStatic(
		wa_spiThread,
		sizeof(wa_spiThread),
		NORMALPRIO + 1,
		spiThread,
		NULL
	);
//*/
}

extern void bldcStart(){
	palSetLine(LINE_LED_GREEN);
	pwmStart(&PWMD1,&pwmRWcfg);
  pwmEnablePeriodicNotification(&PWMD1);
//*
	pwmEnableChannel(&PWMD1,PWM_U,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,motor->u));
  pwmEnableChannel(&PWMD1,PWM_V,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,motor->v));
  pwmEnableChannel(&PWMD1,PWM_W,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,motor->w));
//*/
//*
	pwmEnableChannelNotification(&PWMD1,PWM_U);
  pwmEnableChannelNotification(&PWMD1,PWM_V);
  pwmEnableChannelNotification(&PWMD1,PWM_W);
//*/
}

extern void bldcStop(){
//  palClearLine(LINE_LED_GREEN);
	pwmStop(&PWMD1);
}

extern void bldcExit(){
	chThdTerminate(motor->p_spi_thread);
}
