#include "acs.h"
#include "acs_lut.h"

//#define ST2US(n) (((n) * 1000000UL + CH_CFG_ST_FREQUENCY - 1UL) /    \
//                  CH_CFG_ST_FREQUENCY)

static virtual_timer_t speed_vt;
static int step_size = 1;

//static bool configure = true;


static sysinterval_t interval = 0;
static uint32_t angleDelta = 0;
static uint32_t rps = 0;
static uint32_t time = 0;

static  systime_t now;
static  systime_t prv;

static void speed_cb(void * arg)
{
  chVTSetI(&speed_vt, TIME_MS2I(100), speed_cb, NULL);
  rps = angleDelta * 10;
}


BldcConfig bldc;
uint16_t rxbuf[2] = {0}; // receive buffer

static void adcerrorcallback(ADCDriver *adcp, adcerror_t err) {
    (void)adcp;
    (void)err;
}

/*
 * ADC conversion group.
 * Mode:        Continuous, 8 samples of 1 channel, SW triggered.
 * Channels:    A0 
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


//static sysinterval_t interval = 0;
//static uint32_t angleDelta = 0;
//static uint32_t rp_ = 0;
//static uint32_t time = 0;

//static  systime_t now;
//static  systime_t prv;

THD_WORKING_AREA(wa_acsThread,THREAD_SIZE);
THD_FUNCTION(acsThread,arg) {
  (void)arg;
  chRegSetThreadName("acsThread");

	bldcStart();

  chVTObjectInit(&speed_vt);
  //chVTSet(&speed_vt, TIME_MS2I(100), speed_cb, NULL);

    bool up = true;
    bool down = false;
  while (!chThdShouldTerminateX()) {
	/*
		palClearLine(LINE_LED_GREEN);
		chThdSleepMilliseconds(500);
		palSetLine(LINE_LED_GREEN);
		chThdSleepMilliseconds(500);
	*/
    
    ///*
		chprintf(DEBUG_CHP,"enc pos: %u \n\r", bldc.position);
 	  chprintf(DEBUG_CHP,"phase 1: %u \n\r", bldc.u);     
		chprintf(DEBUG_CHP,"phase 2: %u \n\r", bldc.v);     
		chprintf(DEBUG_CHP,"phase 3: %u \n\n\r", bldc.w);     
    chThdSleepMilliseconds(500); 
    //*/

    //chprintf(DEBUG_CHP, "ADC: %u \n\r", (int)bldc.samples[0]);
    
    //chprintf(DEBUG_CHP, "now: %u \n\r", now);
    //chprintf(DEBUG_CHP, "prv: %u \n\r", prv);
    //chprintf(DEBUG_CHP, "TimeDelta : %u \n\n\r", time);
    //chprintf(DEBUG_CHP, "AngleDelta : %u \n\r", angleDelta); 
    //chprintf(DEBUG_CHP, "rp? : %u \n\n\r", rp_); 
    
    /*
		chThdSleepMilliseconds(1000);
    if (step_size >= 7)
    {
      up = false;
      down = true;
    }

    if (step_size == 1)
    {
      up = true;
      down = false;
    }

    if (up)
      step_size++;
    else
      step_size--;

 		chprintf(DEBUG_CHP,"Step size: %u \n\n\r", step_size);
    */
    
  }
}

THD_WORKING_AREA(wa_spiThread,THREAD_SIZE);
THD_FUNCTION(spiThread,arg){
  (void)arg;
  chRegSetThreadName("spiThread");
	int step;

		//chprintf(DEBUG_CHP,"enc pos: %u \n\r", bldc.position);
  //systime_t now;
  //systime_t prv;

  uint32_t angleNow = 0;
  uint32_t anglePrv = 0;

  spiStart(&SPID1, &spicfg);            // Start driver.
  spiAcquireBus(&SPID1);                // Gain ownership of bus.

  // TODO MAX add time grabbing here for speed
  // systime_t now = chVTGetSystemTime();
  // Use this twice, compute the difference. Need to configure
  // CH_CFG_ST_* stuff

  while (!chThdShouldTerminateX()) {
		rxbuf[0] = 0; 
    now = chVTGetSystemTime(); 
		spiSelect(&SPID1);                  // Select slave.

		//while(SPID1.state != SPI_READY) {}   
		spiReceive(&SPID1,1,rxbuf);     		// Receive 1 frame (16 bits).
    /*chprintf(DEBUG_CHP, "IntervalNow : %u \n\r", (int) now);
    chprintf(DEBUG_CHP, "IntervalPrv : %u \n\r", (int) prv);
    chprintf(DEBUG_CHP, "IntervalNowUs : %u \n\r", ST2US(now));
    chprintf(DEBUG_CHP, "IntervalPrvUs : %u \n\r", ST2US(prv));*/
    // In microseconds
    //interval = chTimeDiffX(prv, now);
    //prv = now;
    //time = TIME_I2US(interval);
		spiUnselect(&SPID1);                // Unselect slave.
       
    //angleNow = (0x3FFF & rxbuf[0]) * 360/(1<<14);
    
    //angleDelta = angleNow - anglePrv;
    //chprintf(DEBUG_CHP, "AngleNow: %u \n\r", angleNow);
    //chprintf(DEBUG_CHP, "AnglePrv: %u \n\r", anglePrv);
    
    // TODO MAX interval changes, I may need to find
    // a way to have a defined time interval to measure across
    // maybe a health thread or info thread?
    //rp_ = (angleDelta / 360) / interval;
    //anglePrv = angleNow;

		bldc.position = 0x3FFF & rxbuf[0];
	 
    prv = chVTGetSystemTime();
    interval = chTimeDiffX(now, prv);
    
    time = TIME_I2US(interval);
    

		chThdSleepMicroseconds(1);
  }

	spiReleaseBus(&SPID1);    // Release ownership of bus.
	spiStop(&SPID1);          // Stop driver.
}


THD_WORKING_AREA(wa_debugThread,THREAD_SIZE);
THD_FUNCTION(debugThread,arg) {
  (void)arg;
  chRegSetThreadName("debugThread");

		chprintf(DEBUG_CHP,"enc pos: %u \n\r", bldc.position);
 	  chprintf(DEBUG_CHP,"phase 1: %u \n\r", bldc.u);     
		chprintf(DEBUG_CHP,"phase 2: %u \n\r", bldc.v);     
		chprintf(DEBUG_CHP,"phase 3: %u \n\r", bldc.w);     
 
    chprintf(DEBUG_CHP, "ADC: %u \n\r", (int)bldc.samples[0]);
    
    chprintf(DEBUG_CHP, "TimeDelta : %u \n\r", interval);
    chprintf(DEBUG_CHP, "AngleDelta : %u \n\r", angleDelta); 
    chprintf(DEBUG_CHP, "rp? : %u \n\n\r", rps); 


 //chThdSleepMilliseconds(100);
}

static uint16_t chunk0L = 0 * ENCODER_CHUNK_SIZE;
static uint16_t chunk0H = 1 * ENCODER_CHUNK_SIZE;

static uint16_t chunk1L = 1 * ENCODER_CHUNK_SIZE;
static uint16_t chunk1H = 2 * ENCODER_CHUNK_SIZE;

static uint16_t chunk2L = 2 * ENCODER_CHUNK_SIZE;
static uint16_t chunk2H = 3 * ENCODER_CHUNK_SIZE;

static uint16_t chunk3L = 3 * ENCODER_CHUNK_SIZE;
static uint16_t chunk3H = 4 * ENCODER_CHUNK_SIZE;

static uint16_t chunk4L = 4 * ENCODER_CHUNK_SIZE;
static uint16_t chunk4H = 5 * ENCODER_CHUNK_SIZE;

static uint16_t chunk5L = 5 * ENCODER_CHUNK_SIZE;
static uint16_t chunk5H = 6 * ENCODER_CHUNK_SIZE;


static uint16_t encoderToLUT(uint16_t position)
{
  uint16_t step = 0;
  if (position > chunk0L && position < chunk0H)
  {
    step = position * STEPS / (ENCODER_CHUNK_SIZE);
  }
  else if (position > chunk1L && position < chunk1H)
  {
    position = position - (ENCODER_CHUNK_SIZE*1);
    step = position * STEPS / (ENCODER_CHUNK_SIZE);
  }
  else if (position > chunk2L && position < chunk2H)
  {

    position = position - (ENCODER_CHUNK_SIZE*2); 
    step = position * STEPS / (ENCODER_CHUNK_SIZE);
  }
  else if (position > chunk3L && position < chunk3H)
  {

    position = position - (ENCODER_CHUNK_SIZE*3);
    step = position * STEPS / (ENCODER_CHUNK_SIZE);
  }
  else if (position > chunk4L && position < chunk4H)
  {

    position = position - (ENCODER_CHUNK_SIZE*4);
    step = position * STEPS / (ENCODER_CHUNK_SIZE);
  }
  else if (position > chunk5L && position < chunk5H)
  {

    position = position - (ENCODER_CHUNK_SIZE*5);
    step = position * STEPS / (ENCODER_CHUNK_SIZE);
  }

  return step;
}

static uint32_t LUTrevCount = 0;

static sinctrl_t scale(sinctrl_t duty_cycle){
	return (duty_cycle*bldc.scale)/10;	
}


// pwm period callback
static void pwmpcb(PWMDriver *pwmp) {
  (void)pwmp;
 	uint16_t step; 
  palClearLine(LINE_LED_GREEN);
	//configure = true;
#ifdef CONFIGURE

      //bldc.u = 0;
      //bldc.v = 120;
      //bldc.w = 240;
 
    if (LUTrevCount < 6 * 360)
    {
      if (bldc.count == bldc.stretch){
      bldc.u += STEP_SIZE;
      bldc.v += STEP_SIZE;
      bldc.w += STEP_SIZE;

      LUTrevCount++;

      if(bldc.u >= bldc.steps){
			  bldc.u = 0 + bldc.u - bldc.steps;
		  }
		  if(bldc.v >= bldc.steps){
			  bldc.v = 0 + bldc.v - bldc.steps;
		  }
		  if(bldc.w >= bldc.steps){
			  bldc.w = 0 + bldc.w - bldc.steps;
		  }
      bldc.count = 0;
     }
     ++bldc.count;
    }
    else
    {
      bldc.u = 0;
      bldc.v = 120;
      bldc.w = 240;
    }
    
  
#endif

#ifndef CONFIGURE    
	  ++bldc.count;

	  if(bldc.count==bldc.stretch){
#ifdef BRUTEFORCE
		  bldc.u += step_size;
		  bldc.v += step_size;
		  bldc.w += step_size;

		  if(bldc.u >= bldc.steps){
			  bldc.u = 0 + bldc.u - bldc.steps;
		  }
		  if(bldc.v >= bldc.steps){
			  bldc.v = 0 + bldc.v - bldc.steps;
		  }
		  if(bldc.w >= bldc.steps){
			  bldc.w = 0 + bldc.w - bldc.steps;
		  }
#endif
#ifndef BRUTEFORCE

//		int step = 360/(1<<14)*bldc.position;
		  step = encoderToLUT(bldc.position);
		  bldc.u = (step + STEP_SIZE)%360;
		  bldc.v = (bldc.u + bldc.phase_shift)%360;
		  bldc.w = (bldc.v + bldc.phase_shift)%360;

/*
    if (bldc.u > 360)
    {
      bldc.u = 0 + (bldc.u - 360);
    }
    if (bldc.v > 360)
    {
      bldc.v = 0 + (bldc.v - 360);
    }
    if (bldc.w > 360)
    {
      bldc.w = 0 + (bldc.w - 360);
    }
*/

#endif
		  bldc.count=0;
	  }
#endif

/*
pwmEnableChannelI(
		&PWMD1,
		PWM_U,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,scale(bldc.sinctrl[bldc.u]))
	);


pwmEnableChannelI(
		&PWMD1,
		PWM_V,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,scale(bldc.sinctrl[bldc.v]))
	);


pwmEnableChannelI(
		&PWMD1,
		PWM_U,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,scale(bldc.sinctrl[bldc.w]))
	);
*/
		//chThdSleepSeconds(1);
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
  // TODO MAX wrap up into adcInit
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
