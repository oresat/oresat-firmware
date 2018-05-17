#include "bldc.h"
#include "sin_lut.h"

bldc *motor;

//TODO temp test
uint32_t step_size = STRETCH;

uint32_t current_sin_u, next_sin_u;
uint32_t current_sin_v, next_sin_v;
uint32_t current_sin_w, next_sin_w;
uint16_t sin_diff;
uint16_t sin_size;
uint16_t sin_step = STRETCH;


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



/*
//TODO move this
extern uint16_t chunk_low[6] = {0 * CHUNK_SIZE,
                                1 * CHUNK_SIZE,
                                2 * CHUNK_SIZE,
                                3 * CHUNK_SIZE,
                                4 * CHUNK_SIZE,
                                5 * CHUNK_SIZE};

*/
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



uint16_t count = 0;

bool down = false;

// pwm period callback
static void pwmpcb(PWMDriver *pwmp) {
  (void)pwmp;
 	uint16_t step; 
  uint16_t next_step;
  palClearLine(LINE_LED_GREEN);
	//configure = true;
  
  if (count > 100)
  {
    if (!down)
    {
      step_size++;
      //sin_step++;
    }
    else
    {
      step_size = step_size - 1;
      //sin_step = sin_step - 1;
    }
    count = 0;
  }

  if (step_size >= 100)
  {
    down = true;
    //step_size = 1;
    //sin_step = 1;
    //count = 5001;
  }
  else if (step_size < 2)
  {
    down = false;
    //count = 5001;
  }
#ifdef CONFIGURE

      //bldc.u = 0;
      //bldc.v = 120;
      //bldc.w = 240;
 
    if (LUTrevCount < 6 * 360)
    {
      if (motor->count == motor->stretch){
      motor->u += STEP_SIZE;
      motor->v += STEP_SIZE;
      motor->w += STEP_SIZE;

      LUTrevCount++;

      if(motor->u >= motor->steps){
			  motor->u = 0 + motor->u - motor->steps;
		  }
		  if(motor->v >= motor->steps){
			  motor->v = 0 + motor->v - motor->steps;
		  }
		  if(motor->w >= motor->steps){
			  motor->w = 0 + motor->w - motor->steps;
		  }
      motor->count = 0;
     }
     ++motor->count;
    }
    else
    {
      motor->u = 0;
      motor->v = 120;
      motor->w = 240;
    }
    
  
#endif

#ifndef CONFIGURE    
	  //++bldc.count;

	  //if(bldc.count==bldc.stretch){
#ifdef BRUTEFORCE
		  motor->u += step_size;
		  motor->v += step_size;
		  motor->w += step_size;

		  if(motor->u >= motor->steps){
			  motor->u = 0 + motor->u - motor->steps;
		  }
		  if(motor->v >= motor->steps){
			  motor->v = 0 + motor->v - motor->steps;
		  }
		  if(motor->w >= motor->steps){
			  motor->w = 0 + motor->w - motor->steps;
		  }
#endif
#ifndef BRUTEFORCE

//		int step = 360/(1<<14)*bldc.position;
if (sin_step == step_size)
{
      step = encoderToLUT(motor->position);
		  next_step = step + SKIP;



      motor->u = (next_step)%360;
		  motor->v = (motor->u + motor->phase_shift)%360;
		  motor->w = (motor->v + motor->phase_shift)%360;

/*
    if (motor->u > 360)
    {
      motor->u = 0 + (motor->u - 360);
    }
    if (motor->v > 360)
    {
      motor->v = 0 + (motor->v - 360);
    }
    if (motor->w > 360)
    {
      motor->w = 0 + (motor->w - 360);
    }
*/
}
#endif
	//	  motor->count=0;
	 // }
#endif
if (SKIP)
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
    //sin_diff_v = next_sin_v - current_sin_v;
    //sin_diff_w = next_sin_w - current_sin_w;

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

		//chThdSleepSeconds(1);
  count++;
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
