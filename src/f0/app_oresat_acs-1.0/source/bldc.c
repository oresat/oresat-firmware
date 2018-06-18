#include "bldc.h"
#include "sin_lut.h"

bldc *motor;

/**
 * @brief Currently not used.
 *
 *
 */
static void adcerrorcallback(ADCDriver *adcp, adcerror_t err) {
    (void)adcp;
    (void)err;
}


/**
 * TODO: combine this with a timer to not spam interrupts so much?
 * @brief ADC conversion group, used to configure the ADC driver
 * Mode:        Continuous, 1 sample of 1 channel, SW triggered.
 * Channels:    A0 
 * Slowest sample rate possible, as putting it too high can lock other systems out.
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

/**
 * @brief Translates encoder position into a useable LUT value
 *
 * Since it takes 6 passes through the LUT to get one physical
 * revolution of the motor, we need a way to index a value
 * of 0 - 2^14 into a value of 0 - 360, in 6 separate ranges
 *
 */
static uint16_t encoderToLut(uint16_t position){
  uint16_t step = 0;
  uint8_t chunk = (position * CHUNK_AMOUNT) / ENCODER_MAX;
  step = ((position - chunk_low[chunk]) * (STEPS)) / CHUNK_SIZE;

  return step;
}

/**
 * @brief Handles the SPI transaction, getting the position from the encoder
 *
 */
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

/**
 * @brief Scales the duty ccycle value from LUT 0 - 100%
 *
 */
static sinctrl_t scale(sinctrl_t duty_cycle){
	return ((duty_cycle*motor->scale)/100) + ((10000*(motor->scale/2))/100);	
}

/**
 * @brief Periodic callback of the PWM driver
 *
 * At the end of each period, we call this, and go to the next 
 * step in the LUT, which changes absed off of closed or open
 * loop control. Holds the logic for stretching, skipping, and
 * repeating, to modify the LUT values on the fly.
 *
 */
static void pwmpcb(PWMDriver *pwmp) {
  (void)pwmp;
  
  /// If open loop, ignore encoder feedback.
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

			/// Calculate the difference between the current step in the LUT
			/// and the next step in the LUT, and break it up
			/// into the desired amount of steps in between the two
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

/**
 * @brief Pwm driver configuration structure.
 * 
 * PWM_TIMER_FREQ is our timer clock in Hz
 *
 * PWM_PERIOD period in ticks
 *
 * Configured with pwmpcb as the periodic callback
 * PWM channels 0,1,2 are all active high, with a complementary output
 * and no channel callback
 *
 */
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

/**
 * @brief Sets up initial values for the BLDC object
 *
 */
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
  motor->openLoop = true;
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

/**
 * @brief Enables the three PWM channels, starting to go through the LUT
 *
 */
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

/**
 * @brief Stops BLDC control
 *
 */
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

/**
 * @brief Changes duty cycle for a given channel
 *
 */
extern void bldcSetDC(uint8_t channel,uint16_t dc){
	pwmEnableChannelI(
		&PWMD1,
		channel,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,scale(dc))
	);
}

/**
 * @ brief Tear down drivers in a sane way.
 *
 */
extern void bldcExit(bldc *pbldc){
	if(pbldc->started){
		bldcStop(pbldc);
	}
  adcStopConversion(&ADCD1);
  adcStop(&ADCD1); 
	chThdTerminate(motor->p_spi_thread);
	chThdWait(motor->p_spi_thread);
}
