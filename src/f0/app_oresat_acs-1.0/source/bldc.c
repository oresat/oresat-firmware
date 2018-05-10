#include "bldc.h"
#include "sin_lut.h"

bldc *_bldc;

THD_WORKING_AREA(wa_spiThread,THREAD_SIZE);
THD_FUNCTION(spiThread,arg){
  (void)arg;
	chRegSetThreadName("spiThread");
	int step;

  spiStart(&SPID1,&spicfg);            // Start driver.
  spiAcquireBus(&SPID1);                // Gain ownership of bus.

  while (!chThdShouldTerminateX()) {
		_bldc->spi_rxbuf[0] = 0;
		spiSelect(&SPID1);                  // Select slave.

		while(SPID1.state != SPI_READY) {}   
		spiReceive(&SPID1,1,_bldc->spi_rxbuf);     		// Receive 1 frame (16 bits).
		spiUnselect(&SPID1);                // Unselect slave.

		_bldc->position = 0x3FFF & _bldc->spi_rxbuf[0];
	 
		step = _bldc->position*360/(1<<14);
		chprintf(DEBUG_CHP,"enc pos: %u \n",_bldc->position);        
		chprintf(DEBUG_CHP,"phase 1: %u \n", step);     
		step = (step + _bldc->phase_shift)%360;
		chprintf(DEBUG_CHP,"phase 2: %u \n",step);     
		step = (step + _bldc->phase_shift)%360;
		chprintf(DEBUG_CHP,"phase 3: %u \n\n",step);     

		chThdSleepMilliseconds(100);
  }

	spiReleaseBus(&SPID1);    // Release ownership of bus.
	spiStop(&SPID1);          // Stop driver.
}

static sinctrl_t scale(sinctrl_t duty_cycle){
	return (duty_cycle*_bldc->scale)/10;	
}

static void pwmCallback(uint8_t channel,sinctrl_t step){
 // palSetLine(LINE_LED_GREEN);
  pwmEnableChannel(
		&PWMD1,
		channel,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,scale(_bldc->sinctrl[step]))
	);
}

// pwm period callback
static void pwmpcb(PWMDriver *pwmp) {
  (void)pwmp;
 	int step; 
//  palClearLine(LINE_LED_GREEN);
	
	++_bldc->count;
	
	if(_bldc->count==_bldc->stretch){
#ifdef OPENLOOP
		++_bldc->u;
		++_bldc->v;
		++_bldc->w;

		if(_bldc->u >= _bldc->steps){
			_bldc->u = 0;
		}
		if(_bldc->v >= _bldc->steps){
			_bldc->v = 0;
		}
		if(_bldc->w >= _bldc->steps){
			_bldc->w = 0;
		}
#endif
#ifndef OPENLOOP 
//*
		step = _bldc->position*360/(1<<14);
		_bldc->u = (step + 1 + _bldc->phase_shift)%360;
		_bldc->v = (_bldc->u + _bldc->phase_shift)%360;
		_bldc->w = (_bldc->v + _bldc->phase_shift)%360;
//*/
#endif
		_bldc->count=0;
	}
	pwmCallback(PWM_U,_bldc->u);
	pwmCallback(PWM_V,_bldc->v);
	pwmCallback(PWM_W,_bldc->w);
}

static void pwmUcb(PWMDriver *pwmp){ // channel 1 callback
  (void)pwmp;
//	pwmCallback(PWM_U,_bldc->u,_bldc);
}

static void pwmVcb(PWMDriver *pwmp){ // channel 2 callback
  (void)pwmp;
//	pwmCallback(PWM_V,_bldc->v,_bldc);
}

static void pwmWcb(PWMDriver *pwmp){ // channel 3 callback
  (void)pwmp;
//	pwmCallback(PWM_W,_bldc->w,_bldc);
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

extern void _bldcInit(bldc *pbldc){
	_bldc=pbldc;
	_bldc->steps = STEPS;
	_bldc->stretch = STRETCH;
	_bldc->scale = SCALE;
	_bldc->sinctrl = sinctrl360;
	_bldc->count = 0;
	_bldc->position = 0;
	_bldc->phase_shift = _bldc->steps/3;
	_bldc->u = 0;
	_bldc->v = _bldc->u + _bldc->phase_shift;
	_bldc->w = _bldc->v + _bldc->phase_shift;

//	_bldcStart();
}

extern void _bldcStart(bldc *_bldc){
	palSetLine(LINE_LED_GREEN);
	pwmStart(&PWMD1,&pwmcfg);
  pwmEnablePeriodicNotification(&PWMD1);

	pwmEnableChannel(&PWMD1,PWM_U,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,_bldc->u));
  pwmEnableChannel(&PWMD1,PWM_V,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,_bldc->v));
  pwmEnableChannel(&PWMD1,PWM_W,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,_bldc->w));

	pwmEnableChannelNotification(&PWMD1,PWM_U);
  pwmEnableChannelNotification(&PWMD1,PWM_V);
  pwmEnableChannelNotification(&PWMD1,PWM_W);
}

extern void _bldcStop(bldc *_bldc){
	(void) _bldc;
  palClearLine(LINE_LED_GREEN);
	pwmStop(&PWMD1);
/*
  pwmEnablePeriodicNotification(&PWMD1);

	pwmEnableChannel(&PWMD1,PWM_U,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,_bldc->u));
  pwmEnableChannel(&PWMD1,PWM_V,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,_bldc->v));
  pwmEnableChannel(&PWMD1,PWM_W,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,_bldc->w));

	pwmEnableChannelNotification(&PWMD1,PWM_U);
  pwmEnableChannelNotification(&PWMD1,PWM_V);
  pwmEnableChannelNotification(&PWMD1,PWM_W);
*/
}
