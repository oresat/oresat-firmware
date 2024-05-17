#include "ch.h"
#include "dtc.h"
#include "CANopen.h"
#include "chprintf.h"
#include "OD.h"

DTC dtc = { 0 };

/*
 * DAC streaming callback.
 */
static void end_cb1(DACDriver *dacp) {
  (void)dacp;
  
  if (dacIsBufferComplete(dacp)) {
  
  }
  else {
  
  }
}

/*
 * DAC error callback.
 */
static void error_cb1(DACDriver *dacp, dacerror_t err) {

  (void)dacp;
  (void)err;

  chSysHalt("DAC failure");
}

static const DACConfig dac1cfg1 = {
  //.init         = 0U,
  .init         = 2047U,
  .datamode     = DAC_DHRM_12BIT_RIGHT,
  .cr           = 0
};

static const DACConversionGroup dacgrpcfg1 = {
  .num_channels = 1U,
  .end_cb       = end_cb1,
  .error_cb     = error_cb1,
  .trigger      = DAC_TRG(0)
};

/*
 * GPT6 configuration.
 */
static const GPTConfig gpt6cfg1 = {
  .frequency    = 1000000U,
  //.frequency    = 1000U,
  .callback     = NULL,
  .cr2          = TIM_CR2_MMS_1,    /* MMS = 010 = TRGO on Update Event.    */
  .dier         = 0U
};

void dac_start(void)
{
  palSetPadMode(GPIOA, 4, PAL_MODE_INPUT_ANALOG);
  dacStart(&DACD1, &dac1cfg1);
  
  // Starting GPT6 driver, it is used for triggering the DAC.
  gptStart(&GPTD6, &gpt6cfg1);

  // Starting a continuous conversion.
  dacStartConversion(&DACD1, &dacgrpcfg1,(dacsample_t *)dac_buffer, DAC_BUFFER_SIZE);            
  gptStartContinuous(&GPTD6, 10000U);

}

static adcsample_t samples1[ADC_NUM_CHANNELS * ADC_BUF_DEPTH];

/*
 * ADC streaming callback.
 */
static void adccallback(ADCDriver *adcp) {
  if(adcIsBufferComplete(adcp)) 
  {
    osalSysLock();
    memcpy(&OD_RAM.x4000_adcsample, samples1, sizeof(adcsample_t) * ADC_BUF_DEPTH);
    osalSysUnlock();
  }
}

static void adcerrorcallback(ADCDriver *adcp, adcerror_t err) {
  (void)adcp;
  (void)err;

  osalSysLock();
  ++dtc.errors;
  osalSysUnlock();
}

/*
 * ADC conversion group.
 * Mode:        Continuous buffer, 8 samples of 1 channel, SW triggered.
 * Channels:    IN10.
 */
static const ADCConversionGroup adcgrpcfg1 = {
  TRUE,
  ADC_NUM_CHANNELS,
  adccallback,
  adcerrorcallback,
  ADC_CFGR1_CONT | ADC_CFGR1_RES_12BIT,             /* CFGR1 */
  ADC_TR(0, 0),                                     /* TR */
  ADC_SMPR_SMP_28P5,                                /* SMPR */
  ADC_CHSELR_CHSEL10 | ADC_CHSELR_CHSEL11 |
  ADC_CHSELR_CHSEL16 | ADC_CHSELR_CHSEL17           /* CHSELR */
};

void adc_start(void)
{
  //TODO: add pin setup to board file
  palSetGroupMode(GPIOA, PAL_PORT_BIT(0) | PAL_PORT_BIT(1), 0, PAL_MODE_INPUT_ANALOG);

  adcStart(&ADCD1, NULL);

  chThdSleepMilliseconds(1000);

  adcStartConversion(&ADCD1, &adcgrpcfg1, samples1, ADC_BUF_DEPTH);
}

void dtc_init(void)
{
  dtc.pdiode_select = &OD_RAM.x4001_diode.select;
  dtc.padcsample = &OD_RAM.x4000_adcsample.buf0;
  dac_start();
  adc_start();
}

/**
 *
 * blinking example thread definition 
 * counts blinks and saves to tpdo
*/
THD_WORKING_AREA(blink_wa, 0x400);
THD_FUNCTION(blink, arg)
{
  
  (void)arg;
  uint16_t blinkcount = 0;

  while (!chThdShouldTerminateX()) 
  {
    if(blinkcount % 10 == 0)
    {
      chprintf(DEBUG_SERIAL, "%u\r\n",blinkcount);
    }
    palClearLine(LINE_LED);
    chThdSleepMilliseconds(500);
    palSetLine(LINE_LED);
    chThdSleepMilliseconds(500);
    ++blinkcount;
  }

  dbgprintf("Terminating blink thread...\r\n");

  palClearLine(LINE_LED);
  chThdExit(MSG_OK);
}

/**
 * adc watch 
*/
THD_WORKING_AREA(adc_watch_wa, 0x400);
THD_FUNCTION(adc_watch, arg)
{
  (void)arg; 

  while (!chThdShouldTerminateX()) 
  {
//*   
    chprintf(DEBUG_SERIAL, "\r\n%04X ",    dtc.padcsample[0]);
    chprintf(DEBUG_SERIAL,     "%04X ",    dtc.padcsample[1]);
    chprintf(DEBUG_SERIAL,     "%04X ",    dtc.padcsample[2]);
    chprintf(DEBUG_SERIAL,     "%04X\r\n", dtc.padcsample[3]);
    chprintf(DEBUG_SERIAL,     "%04X ",    dtc.padcsample[4]);
    chprintf(DEBUG_SERIAL,     "%04X ",    dtc.padcsample[5]);
    chprintf(DEBUG_SERIAL,     "%04X ",    dtc.padcsample[6]);
    chprintf(DEBUG_SERIAL,     "%04X\r\n", dtc.padcsample[7]);
//*/
    chThdSleepMilliseconds(10*1000);
  }

  dbgprintf("Terminating adc_watch thread...\r\n");

  chThdExit(MSG_OK);
}

/**
 *  diode select
*/
THD_WORKING_AREA(diode_select_wa, 0x400);
THD_FUNCTION(diode_select, arg)
{
  (void)arg; 

  while (!chThdShouldTerminateX()) 
  {
    //if(diode_select < NUM_DIODES)
   // {
      osalSysLock();
      palWriteGroup(
        GPIOB, 
        PAL_PORT_BIT(DIODE_MUX_A0) | PAL_PORT_BIT(DIODE_MUX_A1) | PAL_PORT_BIT(DIODE_MUX_A2), 
        0, 
        (*dtc.pdiode_select << DIODE_MUX_A0)
      );
      osalSysUnlock();
    //}
    if(*dtc.pdiode_select < NUM_DIODES)
    {
      ++(*dtc.pdiode_select); 
    }
    else 
    {
      *dtc.pdiode_select = 0;
    }
    chThdSleepMilliseconds(1000);
  }

  dbgprintf("Terminating diode select thread...\r\n");

  chThdExit(MSG_OK);
}
