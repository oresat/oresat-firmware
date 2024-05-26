#include "ch.h"
#include "diode_test.h"
#include "CANopen.h"
#include "chprintf.h"
#include "OD.h"

DTC dtc = { 0 };
sample_t sample[SAMPLES];
#define BUFFER_DEPTH            sizeof(sample)/sizeof(sample_t)

void dtc_init(void)
{
  dtc.padcsample = &OD_RAM.x4000_adcsample.ch1;
  dtc.pdiode_select = &OD_RAM.x4001_diode.select;
  dtc.pdac = &OD_RAM.x4001_diode.dac;
  dtc.perrors = &OD_RAM.x4001_diode.errors;
  dac_start();
  adc_start();
}

/*
 * DAC error callback.
 */
static void dac_error_callback(DACDriver *dacp, dacerror_t err) 
{
  (void)dacp;
  (void)err;

  ++(*dtc.perrors);
}

static const DACConfig dac1cfg1 = {
  .init         = 0U,
  .datamode     = DAC_DHRM_12BIT_RIGHT,
  .cr           = 0
};

static const DACConversionGroup dacgrpcfg1 = {
  .num_channels = 1U,
  .end_cb       = NULL,
  .error_cb     = dac_error_callback,
  .trigger      = DAC_TRG(0)
};

void dac_start(void)
{
  palSetPadMode(GPIOA, 4, PAL_MODE_INPUT_ANALOG);
  dacStart(&DACD1, &dac1cfg1);
}

/*
 * ADC streaming callback.
 */
static int cb = 0;
static void adc_callback(ADCDriver *adcp) {
  sample_t *psample = (sample_t*)adcp->samples;
  int i = adcIsBufferComplete(adcp); 
  //adcStopConversionI(&ADCD1);
  OD_RAM.x4000_adcsample.ch1 = psample[i].ch1;
  OD_RAM.x4000_adcsample.ch2 = psample[i].ch2;
  OD_RAM.x4000_adcsample.ts = psample[i].ts;
  OD_RAM.x4000_adcsample.vrefint = psample[i].vrefint;
}

static void adc_error_callback(ADCDriver *adcp, adcerror_t err) {
  (void)adcp;
  (void)err;

  ++(*dtc.perrors);
}

/*
 * ADC conversion group.
 */
static const ADCConversionGroup adcgrpcfg1 = {
  //TRUE,
  FALSE,
  NUM_CHANNELS,
  adc_callback,
  adc_error_callback,
  ADC_CFGR1_RES_12BIT,            /* CFGR1 */
  ADC_TR(0, 0),                                    /* TR */
  ADC_SMPR_SMP_28P5,                              /* SMPR */
  ADC_CHSELR_CHSEL11 | ADC_CHSELR_CHSEL15  |       /* CHSELR */
  ADC_CHSELR_CHSEL16 | ADC_CHSELR_CHSEL17          
};

static void gpt_adc_trigger_cb(GPTDriver *gptp)
{
  (void)gptp;
  adcStartConversionI(&ADCD1, &adcgrpcfg1, (adcsample_t *)sample, BUFFER_DEPTH);
  OD_RAM.x4001_diode.errors = ++(*dtc.perrors);
}

/*
  * GPT6 configuration.
  */
 static const GPTConfig gpt6cfg1 = {
   .frequency    = 1000000U,
   .callback     = gpt_adc_trigger_cb,
   .cr2          = TIM_CR2_MMS_1,    /* MMS = 010 = TRGO on Update Event.    */
   .dier         = 0U
 };

void adc_start(void)
{
  gptStart(&GPTD6, &gpt6cfg1);
  //adcAcquireBus(&ADCD1);
  adcStart(&ADCD1, NULL);
  adcSTM32SetCCR(ADC_CCR_TSEN | ADC_CCR_VREFEN);
  gptStartContinuous(&GPTD6, 1000U);
  //adcStartConversion(&ADCD1, &adcgrpcfg1, (adcsample_t *)sample, BUFFER_DEPTH);
  //adcReleaseBus(&ADCD1);
}

/**
 * blinking example thread definition 
*/
THD_WORKING_AREA(blink_wa, 0x400);
THD_FUNCTION(blink, arg)
{
  (void)arg;

  while (!chThdShouldTerminateX()) 
  {
    palClearLine(LINE_LED);
    chThdSleepMilliseconds(500);
    palSetLine(LINE_LED);
    chThdSleepMilliseconds(500);
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
    chprintf(DEBUG_SERIAL,   "\r\n%04u ",    dtc.padcsample[0]);
    chprintf(DEBUG_SERIAL,       "%04u ",    dtc.padcsample[1]);
    chprintf(DEBUG_SERIAL,       "%04u ",    dtc.padcsample[2]);
    chprintf(DEBUG_SERIAL,       "%04u\r\n", dtc.padcsample[3]);
    chprintf(DEBUG_SERIAL,       "%04u ",    *dtc.pdiode_select);
    chprintf(DEBUG_SERIAL,       "%04u ",    *dtc.pdac);
    chprintf(DEBUG_SERIAL,       "%04u ",    *dtc.perrors);
//*/

    chThdSleepMilliseconds(1000);
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
   if(*dtc.pdiode_select < DTC_NUM_DIODES)
    {
      osalSysLock();
      palWriteGroup(
        GPIOB, 
        PAL_PORT_BIT(DTC_MUX_A0) | PAL_PORT_BIT(DTC_MUX_A1) | PAL_PORT_BIT(DTC_MUX_A2), 
        0, 
        (*dtc.pdiode_select << DTC_MUX_A0)
      );
      osalSysUnlock();
    }

    osalSysLock();
    dacPutChannelX(&DACD1, 0, OD_RAM.x4001_diode.dac);
    osalSysUnlock();

    chThdSleepMilliseconds(200);
  }

  dbgprintf("Terminating diode select thread...\r\n");

  chThdExit(MSG_OK);
}

