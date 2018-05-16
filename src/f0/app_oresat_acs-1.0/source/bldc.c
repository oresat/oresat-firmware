#include "bldc.h"
#include "sin_lut.h"

bldc *motor;

//TODO move this
extern uint16_t chunk_low[6] = {0 * CHUNK_SIZE,
                                1 * CHUNK_SIZE,
                                2 * CHUNK_SIZE,
                                3 * CHUNK_SIZE,
                                4 * CHUNK_SIZE,
                                5 * CHUNK_SIZE};


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

static uint8_t encoderToLUT(uint16_t position)
{
  uint8_t chunk = (position * CHUNK_AMOUNT) / ENCODER_MAX;
  return ((position - chunk_low[chunk]) * (STEPS)) / CHUNK_SIZE;
}

//TODO probably a better way to handle these
uint32_t step_size = STRETCH;

uint32_t current_sin_u, next_sin_u;
uint32_t current_sin_v, next_sin_v;
uint32_t current_sin_w, next_sin_w;
uint16_t sin_diff;
uint16_t sin_size;
uint16_t sin_step = STRETCH;
uint8_t next_step;

// pwm period callback
static void pwmpcb(PWMDriver *pwmp) {
  (void)pwmp;
	++motor->count;
	
  //TODO Figure out what to do with this stretch
	//if(motor->count==motor->stretch){
#ifdef OPENLOOP

if (sin_step == step_size)
{
    
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
}


#endif
#ifndef OPENLOOP 
if (sin_step == step_size)
{
      next_step = encoderToLUT(motor->position) + motor->skip;

      motor->u = (next_step)%360;
		  motor->v = (motor->u + motor->phase_shift)%360;
		  motor->w = (motor->v + motor->phase_shift)%360;

}
#endif

	//	motor->count=0;
	//}
if (motor->stretch > 1)
{
  if (sin_step == step_size)
  {
    current_sin_u = motor->sinctrl[motor->u];
    current_sin_v = motor->sinctrl[motor->v];
    current_sin_w = motor->sinctrl[motor->w];
    next_sin_u = motor->sinctrl[motor->u + 1];
    next_sin_v = motor->sinctrl[motor->v + 1];
    next_sin_w = motor->sinctrl[motor->w + 1];
  
    if (current_sin_u < next_sin_u)
    {
      sin_diff = next_sin_u - current_sin_u;

      sin_size = sin_diff / step_size;
    }
    else if (current_sin_v < next_sin_v)
    {
      sin_diff = next_sin_v - current_sin_v;
      sin_size = sin_diff / step_size;
    }  
    else
    {
      sin_diff = next_sin_w - current_sin_w;
      sin_size = sin_diff / step_size;
    }
  }

  current_sin_u = current_sin_u + sin_size;
  current_sin_v = current_sin_v + sin_size;
  current_sin_w = current_sin_w + sin_size;

  sin_step = sin_step - 1;

  if (sin_step == 0)
  {
    current_sin_u = next_sin_u;
    current_sin_v = next_sin_v;
    current_sin_w = next_sin_w;
    sin_step = step_size;
  }
}
else
{
  current_sin_u = motor->sinctrl[motor->u];
  current_sin_v = motor->sinctrl[motor->v];
  current_sin_w = motor->sinctrl[motor->w];
}

pwmEnableChannelI(
		&PWMD1,
		PWM_U,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,scale(current_sin_u)));

pwmEnableChannelI(
		&PWMD1,
		PWM_V,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,scale(current_sin_v))
	);

pwmEnableChannelI(
		&PWMD1,
		PWM_W,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,scale(current_sin_w))
	);



}

static void pwmUcb(PWMDriver *pwmp){ // channel 1 callback
  (void)pwmp;
//	pwmCallback(PWM_U,motor->u);
}

static void pwmVcb(PWMDriver *pwmp){ // channel 2 callback
  (void)pwmp;
//	pwmCallback(PWM_V,motor->v);
}

static void pwmWcb(PWMDriver *pwmp){ // channel 3 callback
  (void)pwmp;
//	pwmCallback(PWM_W,motor->w);
}

static PWMConfig pwmRWcfg = {
  PWM_TIMER_FREQ,	
  PWM_PERIOD,	
  pwmpcb,
  {
   {PWM_OUTPUT_ACTIVE_HIGH|PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, pwmUcb},
   {PWM_OUTPUT_ACTIVE_HIGH|PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, pwmVcb},
   {PWM_OUTPUT_ACTIVE_HIGH|PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, pwmWcb},
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
  motor->skip = SKIP;
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
	//palSetLine(LINE_LED_GREEN);
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
