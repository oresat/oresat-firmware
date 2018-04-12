#include "acs.h"
#include "acs_lut.h"

BldcConfig bldc;
uint16_t rxbuf[2] = {0}; // receive buffer

static void adcerrorcallback(ADCDriver *adcp, adcerror_t err) {
    (void)adcp;
    (void)err;
}

/*
 * ADC conversion group.
 * Mode:        Continuous, 16 samples of 1 channel, SW triggered.
 * Channels:    IN10, IN11, Sensor, VRef.
 */
static const ADCConversionGroup adcgrpcfg = {
    TRUE,
    ADC_GRP_NUM_CHANNELS,
    NULL,
    adcerrorcallback,
    ADC_CFGR1_CONT | ADC_CFGR1_RES_12BIT,             /* CFGRR1 */
    ADC_TR(0, 0),                                     /* TR */
    ADC_SMPR_SMP_239P5,                                /* SMPR */
    ADC_CHSELR_CHSEL0                                /* CHSELR */
};

THD_WORKING_AREA(wa_acsThread,THREAD_SIZE);
THD_FUNCTION(acsThread,arg) {
  (void)arg;
  chRegSetThreadName("acsThread");

	bldcStart();

  while (!chThdShouldTerminateX()) {
	//*
		palClearLine(LINE_LED_GREEN);
		chThdSleepMilliseconds(500);
		palSetLine(LINE_LED_GREEN);
		chThdSleepMilliseconds(500);
	//*/
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
		chprintf(DEBUG_CHP,"enc pos: %u \n", bldc.position);        
		chprintf(DEBUG_CHP,"phase 1: %u \n", step);     
		step = (step + bldc.phase_shift)%360;
		chprintf(DEBUG_CHP,"phase 2: %u \n", step);     
		step = (step + bldc.phase_shift)%360;
		chprintf(DEBUG_CHP,"phase 3: %u \n\n", step);     
		//chprintf(DEBUG_CHP,"Decimal: %u \n", encoder_val);        

    chprintf(DEBUG_CHP, "ADC: %d \n\r", (int)bldc.samples[0]);


		chThdSleepMilliseconds(100);
  }

	spiReleaseBus(&SPID1);    // Release ownership of bus.
	spiStop(&SPID1);          // Stop driver.
}

// pwm period callback
static void pwmpcb(PWMDriver *pwmp) {
  (void)pwmp;
 	int step; 
  palClearLine(LINE_LED_GREEN);
	
	++bldc.count;
	
	if(bldc.count==bldc.stretch){
#ifdef BRUTEFORCE
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
#ifndef BRUTEFORCE
//*
//		int step = 360/(1<<14)*bldc.position;
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
  palSetLine(LINE_LED_GREEN);
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

extern void acsInit(void){
	bldcInit();
  adcStart(&ADCD1, NULL);

  /*
  * Starts an ADC continuous conversion.
  */
  adcStartConversion(&ADCD1, &adcgrpcfg, bldc.samples, ADC_GRP_BUF_DEPTH);
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
	pwmStart(&PWMD1, &pwmcfg);
  pwmEnablePeriodicNotification(&PWMD1);

	pwmEnableChannel(&PWMD1,PWM_U,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,bldc.u));
  pwmEnableChannel(&PWMD1,PWM_V,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,bldc.v));
  pwmEnableChannel(&PWMD1,PWM_W,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,bldc.w));

	pwmEnableChannelNotification(&PWMD1,PWM_U);
  pwmEnableChannelNotification(&PWMD1,PWM_V);
  pwmEnableChannelNotification(&PWMD1,PWM_W);
}

extern void bldcStop(){
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
