#include "bldc.h"
#include "sin_lut.h"

bldc *motor;

/**
 *
 *
 *
 */
static void adcerrorcallback(ADCDriver *adcp, adcerror_t err) {
    (void)adcp;
    (void)err;
}


// TODO, combine this a timer to not spam interrupts so much?
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
    ADC_CFGR1_CONT | ADC_CFGR1_RES_12BIT,      /* CFGRR1 */
    ADC_TR(0, 0),                              /* TR */
    ADC_SMPR_SMP_239P5,                        /* SMPR */
    ADC_CHSELR_CHSEL0                          /* CHSELR */
};

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

//static void pwmCallback(uint8_t channel,sinctrl_t step){
//	pwmEnableChannelI(
//		&PWMD1,
//		channel,
//		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,scale(motor->sinctrl[step]))
//	);

static sinctrl_t scale(sinctrl_t duty_cycle){
	return ((duty_cycle*motor->scale)/100) + ((10000*(motor->scale/2))/100);	
}

/**
 *
 *
 *
 */

static void pwmpcb(PWMDriver *pwmp) {
  (void)pwmp;
  
	if(motor->openLoop){
		motor->u += motor->skip;
		motor->v += motor->skip;
		motor->w += motor->skip;

		motor->u = motor->u % 360;
		motor->v = motor->v % 360;
		motor->w = motor->w % 360;
				
		motor->current_sin_u = motor->sinctrl[motor->u];
		motor->current_sin_v = motor->sinctrl[motor->v];
		motor->current_sin_w = motor->sinctrl[motor->w];
	}else{
		if (motor->stretch_count == 0){
			motor->u = encoderToLut(motor->position);
			motor->v = (motor->u + motor->phase_shift) % 360;
			motor->w = (motor->v + motor->phase_shift) % 360;
			motor->current_sin_u = motor->sinctrl[motor->u];
			motor->current_sin_v = motor->sinctrl[motor->v];
			motor->current_sin_w = motor->sinctrl[motor->w];
			motor->next_sin_u = motor->sinctrl[motor->u+1];
			motor->next_sin_v = motor->sinctrl[motor->v+1];
			motor->next_sin_w = motor->sinctrl[motor->w+1];

			motor->sin_diff = (motor->current_sin_u > motor->next_sin_u)?
												(motor->current_sin_u - motor->next_sin_u) : 
												(motor->next_sin_u - motor->current_sin_u);
			motor->sin_diff = motor->sin_diff / motor->stretch;
			motor->stretch_count = motor->stretch;
		}

		motor->current_sin_u += motor->sin_diff;
		motor->current_sin_v += motor->sin_diff;
		motor->current_sin_w += motor->sin_diff;

		motor->stretch_count = motor->stretch_count - 1;
	}

	bldcSetDC(PWM_U,motor->current_sin_u);
	bldcSetDC(PWM_V,motor->current_sin_v);
	bldcSetDC(PWM_W,motor->current_sin_w);
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
	motor->started = FALSE;
	
	adcStart(&ADCD1, NULL); 
  adcStartConversion(&ADCD1, &adcgrpcfg, motor->samples, ADC_GRP_BUF_DEPTH);
	
	motor->p_spi_thread=chThdCreateStatic(
		wa_spiThread,
		sizeof(wa_spiThread),
		NORMALPRIO,
		spiThread,
		NULL
	);
}

extern void bldcStart(bldc *pbldc){
	if(pbldc->started){
		return; 
	}
	pwmStart(&PWMD1,&pwmRWcfg);
  pwmEnablePeriodicNotification(&PWMD1);
	
	pwmEnableChannel(&PWMD1,PWM_U,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,motor->u));
  pwmEnableChannel(&PWMD1,PWM_V,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,motor->v));
  pwmEnableChannel(&PWMD1,PWM_W,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,motor->w));
	pbldc->started = TRUE;
}

extern void bldcStop(bldc *pbldc){
	if(!pbldc->started){
		return;
	}
	pwmDisableChannel(&PWMD1,PWM_U);
  pwmDisableChannel(&PWMD1,PWM_V);
  pwmDisableChannel(&PWMD1,PWM_W);
  pwmDisablePeriodicNotification(&PWMD1);
	pwmStop(&PWMD1);
	pbldc->started = FALSE;
}

extern void bldcSetDC(uint8_t channel,uint16_t dc){
	pwmEnableChannelI(
		&PWMD1,
		channel,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,scale(dc))
	);
}

extern void bldcExit(bldc *pbldc){
	if(pbldc->started){
		bldcStop(pbldc);
	}
  adcStopConversion(&ADCD1);
  adcStop(&ADCD1); 
	chThdTerminate(motor->p_spi_thread);
	chThdWait(motor->p_spi_thread);
}
