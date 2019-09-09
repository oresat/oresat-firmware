#include "bldc.h"
#include "acs_common.h"
#include "math.h"

BLDCMotor *gpMotor = NULL;

/**
 * @brief Currently not used.
 *
 */
/*
static void adcerrorcallback(ADCDriver *adcp, adcerror_t err)
{
  (void)adcp;
  (void)err;
}
//*/

/**
 * TODO: combine this with a timer to not spam interrupts so much?
 * @brief ADC conversion group, used to configure the ADC driver
 * Mode:        Continuous, 1 sample of 1 channel, SW triggered.
 * Channels:    A0 
 * Slowest sample rate possible, as putting it too high can lock other systems out.
 */
/*
static const ADCConversionGroup adcgrpcfg = {
  TRUE,
  ADC_GRP_NUM_CHANNELS,
  NULL,
  adcerrorcallback,
  ADC_CFGR1_CONT | ADC_CFGR1_RES_12BIT,      // CFGRR1 
  ADC_TR(0, 0),                              // TR 
  ADC_SMPR_SMP_239P5,                        // SMPR 
  ADC_CHSELR_CHSEL0                          // CHSELR 
};
//*/

/*
static const ADCConversionGroup adcgrpcfg = 
{
  TRUE,
  ADC_GRP_NUM_CHANNELS,
  NULL,
  adcerrorcallback,
  0,                        // CR1
  ADC_CR2_SWSTART,          // CR2
  ADC_SMPR1_SMP_AN11(ADC_SAMPLE_3),
  0,                        // SMPR2 
  0,                        // SQR1 
  0,                        // SQR2
  ADC_SQR3_SQ1_N(ADC_CHANNEL_IN11)
};
//*/

float normalizePosition(uint16_t encoderValue)
{
  float encoderFloatValue = encoderValue;
  return (encoderFloatValue / (1<<14));
}

/**
 * @brief Handles the SPI transaction, getting the position from the encoder
 *
 */
//*
THD_WORKING_AREA(wa_spiThread,THREAD_SIZE);
THD_FUNCTION(spiThread,arg)
{
  chRegSetThreadName("spiThread");
  
  BLDCMotor *pMotor = (BLDCMotor *)arg;
  uint16_t position = 0;
  spiStart(&SPID1,&spicfg);            	// Start driver.
  spiAcquireBus(&SPID1);                // Gain ownership of bus.
  while(!chThdShouldTerminateX()) 
  {
//		pMotor->spiRxBuffer[0] = 0;
		spiSelect(&SPID1);                  // Select slave.

		while(SPID1.state != SPI_READY) 
    { 
      // do nothing 
    }   
		
    spiReceive(&SPID1, 1, pMotor->spiRxBuffer); // Receive 1 frame (16 bits).
		spiUnselect(&SPID1);                // Unselect slave.

		//pMotor->position = 0x3FFF & pMotor->spiRxBuffer[0];
		position = 0x3FFF & pMotor->spiRxBuffer[0];
    /// ******critical section***********
    chSysLock();  
    pMotor->normalPosition = normalizePosition(position);
    chSysUnlock();  
    /// ******end critical section***********
    //chprintf(DEBUG_CHP, "%f\n\r",pMotor->normalPosition);
  }

	spiReleaseBus(&SPID1);    // Release ownership of bus.
	spiStop(&SPID1);          // Stop driver.
  chThdExit((msg_t)0);
}
//*/

static float electricMotorAngle(float normalPosition)
{
  return (normalPosition * gpMotor->motorConst + gpMotor->calOffset);
}

static int lookupPosition(float motorAngle, int phase)
{
  static const float k_onethird = 1.0 / 3;

//*
  float x = 0;

  if(phase == 0)
  {
    x = motorAngle;
  }
  else if (phase == 1)
  {
    x = motorAngle + k_onethird; 
  }
  else if (phase == 2)
  {
    x = motorAngle - k_onethird;
  }
//*/
/*
  float x = motorAngle; // phase == 0

  if (phase == 1)
  {
    x += k_onethird; 
  }
  else if (phase == 2)
  {
    x -= k_onethird;
  }
//*/

  return (x - floor(x)) * kLUTSize;
}

void commutateMotor(float normalPosition)
{
  float motorAngle;
  int indexU;
  int indexV;
  int indexW;
  float sinValU;
  float sinValV;
  float sinValW;
  uint16_t input;

  motorAngle = electricMotorAngle(normalPosition);
 // motorAngle = 0;
//  gpMotor->magnitude = 1.0;

  indexU = lookupPosition(motorAngle, 0);
  indexV = lookupPosition(motorAngle, 1);
  indexW = lookupPosition(motorAngle, 2);
  //chprintf(DEBUG_CHP, "%d\n\r",indexU);
  //chThdSleepMilliseconds(100);
  sinValU = sin_lut[indexU];
  sinValV = sin_lut[indexV];
  sinValW = sin_lut[indexW];
  //*
  input = sinValU * gpMotor->magnitude * 5000 + 5000;
  bldcSetDutyCycle(PWM_U, input);
  input = sinValV * gpMotor->magnitude * 5000 + 5000;
	bldcSetDutyCycle(PWM_V, input);
  input = sinValW * gpMotor->magnitude * 5000 + 5000;
	bldcSetDutyCycle(PWM_W, input);
  //chprintf(DEBUG_CHP, "%f\n\r",gpMotor->normalPosition);
  //*/
}

binary_semaphore_t bldc_bsem;

static void handleCommunicationTimeout(void)
{
  chprintf(DEBUG_CHP, "timeout\n\r");
  chThdSleepMilliseconds(200); 
}

THD_WORKING_AREA(waCommutationThread,THREAD_SIZE);
THD_FUNCTION(commutationThread,arg)
{
  (void)arg;
  chRegSetThreadName("commutationThread");
  
  //BLDCMotor *pMotor = (BLDCMotor *)arg;
  
  msg_t msg = 0;
  
  while(!chThdShouldTerminateX()) 
  {
   /* 
    * Waiting for an interrupt. If the interrupt has already occurred 
    * then the thread will not stop into chBSemWaitTimeout() because
    * the binary semaphore would be in the "not taken" state. 
    * A 500mS timeout is programmed.
    */

    /* 
     * If a communication timeout occurred then some special handling
     * is required.
     */

    chBSemWait(&bldc_bsem);

    /*
    msg = chBSemWaitTimeout(&bldc_bsem, TIME_MS2I(100));
    if(msg == MSG_TIMEOUT) 
    {
      handleCommunicationTimeout();
      continue;
    }
    //*/

    commutateMotor(gpMotor->normalPosition);
    //chprintf(DEBUG_CHP, "%f\n\r",pMotor->normalPosition);
  }
  chThdExit(msg);
}

static void pwmPeriodCallback(PWMDriver *pwmp) 
{
  (void)pwmp;

  chSysLockFromISR();
  chBSemSignalI(&bldc_bsem);
  chSysUnlockFromISR();
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
static PWMConfig pwmRwConfig = 
{
  PWM_TIMER_FREQ,	
  PWM_PERIOD,	
  pwmPeriodCallback,
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
 * @brief Sets up initial values for the BLDCMotor object
 *
 */
extern void bldcInit(BLDCMotor *pMotor)
{
  gpMotor = pMotor;
  pMotor->pSinLut = sin_lut;
  pMotor->periodCount = 0;
  pMotor->position = 0;
  pMotor->normalPosition = 0.0;
  pMotor->motorConst = 6; /// motor characteristic constant
  //pMotor->calOffset = 0;  /// calibration offset
  pMotor->calOffset = 0.25 - 0.145;  /// calibration offset
  pMotor->magnitude = 0.30;  /// calibration offset
  pMotor->isStarted = false;
  pMotor->pBldc_bsem = &bldc_bsem; 
  
  chBSemObjectInit(&bldc_bsem, false);	
	
  //adcStart(&ADCD1, NULL); 
  //adcStartConversion(&ADCD1, &adcgrpcfg, pMotor->samples, ADC_GRP_BUF_DEPTH);
}

/**
 * @brief Enables the three PWM channels, starting to go through the LUT
 *
 */
extern void bldcStart(BLDCMotor *pMotor)
{
	if(pMotor->isStarted)
  {
		return; 
	}

//*
	pMotor->pSpiThread = chThdCreateStatic(
		wa_spiThread,
		sizeof(wa_spiThread),
		NORMALPRIO,
		spiThread,
		pMotor
	);
//*/

//*
  pMotor->pCommutationThread = chThdCreateStatic(
		waCommutationThread,
		sizeof(waCommutationThread),
		NORMALPRIO + 1,
		commutationThread,
		pMotor
	);
//*/

//*
	pwmStart(&PWMD1,&pwmRwConfig);
  pwmEnablePeriodicNotification(&PWMD1);
	pwmEnableChannel(&PWMD1,PWM_U,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,0));
  pwmEnableChannel(&PWMD1,PWM_V,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,0));
  pwmEnableChannel(&PWMD1,PWM_W,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,0));
//*/

  pMotor->isStarted = TRUE;
}

/**
 * @brief Stops BLDCMotor control
 *
 */
extern void bldcStop(BLDCMotor *pMotor)
{
	if(!pMotor->isStarted)
  {
		return;
	}

  pwmDisableChannel(&PWMD1,PWM_U);
  pwmDisableChannel(&PWMD1,PWM_V);
  pwmDisableChannel(&PWMD1,PWM_W);
  pwmDisablePeriodicNotification(&PWMD1);
	pwmStop(&PWMD1);

  chBSemReset(&bldc_bsem, false);

  chThdTerminate(pMotor->pCommutationThread);
  chThdWait(pMotor->pCommutationThread);
  
  chThdTerminate(pMotor->pSpiThread);
  chThdWait(pMotor->pSpiThread);
 
 	pMotor->isStarted = FALSE;
}

/**
 * @brief Changes duty cycle for a given channel
 *
 */
extern void bldcSetDutyCycle(uint8_t channel, dutycycle_t dc)
{
	pwmEnableChannelI(
		&PWMD1,
		channel,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,dc)
	);
}

/**
 * @brief Tear down drivers in a sane way.
 *
 */
extern void bldcExit(BLDCMotor *pMotor)
{
	if(pMotor->isStarted)
  {
		bldcStop(pMotor);
	}

  //adcStopConversion(&ADCD1);
  //adcStop(&ADCD1); 
}
