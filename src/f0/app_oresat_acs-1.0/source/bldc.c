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


static uint16_t encoderToLut(uint16_t position)
{
  uint16_t step = 0;
  uint8_t chunk = (position * CHUNK_AMOUNT) / ENCODER_MAX;
  step = ((position - chunk_low[chunk]) * (STEPS)) / CHUNK_SIZE;

  return step;
}


THD_WORKING_AREA(wa_spiThread,THREAD_SIZE);
THD_FUNCTION(spiThread,arg){
  (void)arg;
	chRegSetThreadName("spiThread");

  spiStart(&SPID1,&spicfg);            	// Start driver.
  spiAcquireBus(&SPID1);                // Gain ownership of bus.

  while (!chThdShouldTerminateX()) {
		motor->spi_rxbuf[0] = 0;
		spiSelect(&SPID1);                  // Select slave.

		while(SPID1.state != SPI_READY) {}   
		spiReceive(&SPID1,1,motor->spi_rxbuf); // Receive 1 frame (16 bits).
		spiUnselect(&SPID1);                // Unselect slave.

		motor->position = 0x3FFF & motor->spi_rxbuf[0];
	 
  }

	spiReleaseBus(&SPID1);    // Release ownership of bus.
	spiStop(&SPID1);          // Stop driver.
}

static sinctrl_t scale(sinctrl_t duty_cycle){
	return ((duty_cycle*motor->scale)/100) + ((10000*(motor->scale/2))/100);	
}

// pwm period callback
static void pwmpcb(PWMDriver *pwmp) {
  (void)pwmp;
  
if (motor->openLoop)
{
  motor->u += motor->skip;
	motor->v += motor->skip;
	motor->w += motor->skip;

	motor->u = motor->u % 360;
	motor->v = motor->v % 360;
	motor->w = motor->w % 360;
		  
  motor->current_sin_u = motor->sinctrl[motor->u];
  motor->current_sin_v = motor->sinctrl[motor->v];
  motor->current_sin_w = motor->sinctrl[motor->w];

}
else
{
  if (motor->stretch_count == 0)
  {
    motor->u = encoderToLut(motor->position);
    motor->v = (motor->u + motor->phase_shift) % 360;
    motor->w = (motor->v + motor->phase_shift) % 360;
    motor->current_sin_u = motor->sinctrl[motor->u];
    motor->current_sin_v = motor->sinctrl[motor->v];
    motor->current_sin_w = motor->sinctrl[motor->w];
    motor->next_sin_u = motor->sinctrl[motor->u+1];
    motor->next_sin_v = motor->sinctrl[motor->v+1];
    motor->next_sin_w = motor->sinctrl[motor->w+1];

    motor->sin_diff = (motor->current_sin_u > motor->next_sin_u) ? (motor->current_sin_u - motor->next_sin_u) : (motor->next_sin_u - motor->current_sin_u);
    motor->sin_diff = motor->sin_diff / motor->stretch;
    motor->stretch_count = motor->stretch;
}

  motor->current_sin_u += motor->sin_diff;
  motor->current_sin_v += motor->sin_diff;
  motor->current_sin_w += motor->sin_diff;

  motor->stretch_count = motor->stretch_count - 1;
}


pwmEnableChannelI(
		&PWMD1,
		PWM_U,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,scale(motor->current_sin_u)));


pwmEnableChannelI(
		&PWMD1,
		PWM_V,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,scale(motor->current_sin_v))
	);


pwmEnableChannelI(
		&PWMD1,
		PWM_W,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,scale(motor->current_sin_w))
	);
}

static PWMConfig pwmRWcfg = {
  PWM_TIMER_FREQ,	
  PWM_PERIOD,	
  pwmpcb,
  {
   {PWM_OUTPUT_ACTIVE_HIGH|PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, NULL},
   {PWM_OUTPUT_ACTIVE_HIGH|PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, NULL},
   {PWM_OUTPUT_ACTIVE_HIGH|PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, NULL},
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
  motor->stretch_count = 0;
	motor->scale = SCALE;
  motor->skip = SKIP;
	motor->sinctrl = sinctrl360;
	motor->count = 0;
	motor->position = 0;
	motor->phase_shift = motor->steps/3;
	motor->u = 0;
	motor->v = motor->u + motor->phase_shift;
	motor->w = motor->v + motor->phase_shift;
  motor->openLoop = false;

//*
	motor->p_spi_thread=chThdCreateStatic(
		wa_spiThread,
		sizeof(wa_spiThread),
		NORMALPRIO,
		spiThread,
		NULL
	);
//*/
}

extern void bldcStart(){
	pwmStart(&PWMD1,&pwmRWcfg);
  pwmEnablePeriodicNotification(&PWMD1);
//*
	pwmEnableChannel(&PWMD1,PWM_U,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,motor->u));
  pwmEnableChannel(&PWMD1,PWM_V,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,motor->v));
  pwmEnableChannel(&PWMD1,PWM_W,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,motor->w));
}

extern void bldcStop(){
	pwmStop(&PWMD1);
}

extern void bldcExit(){
	chThdTerminate(motor->p_spi_thread);
}
