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
  dtc.pfunc[0] = &dtc_dacStart;
  dtc.pfunc[1] = &dtc_dacStop;
  dtc.pfunc[2] = &dtc_dacSet;
  dtc.pfunc[3] = &dtc_gptStart;
  dtc.pfunc[4] = &dtc_gptStop;
  dtc.pfunc[5] = &dtc_adcStart;
  dtc.pfunc[6] = &dtc_adcStop;
  dtc.pfunc[7] = &dtc_muxEnable;
  dtc.pfunc[8] = &dtc_muxDisable;

  dtc.pctrl = &OD_RAM.x4000_dtc.ctrl;
  dtc.pmux_select = &OD_RAM.x4000_dtc.mux_select;
  dtc.pdac = &OD_RAM.x4000_dtc.dac;
  dtc.pstatus = &OD_RAM.x4000_dtc.status;
  dtc.perror = &OD_RAM.x4000_dtc.error;

  dtc.pled_current = &OD_RAM.x4001_adcsample.led_current;
  dtc.pled_swir_pd_current = &OD_RAM.x4001_adcsample.led_swir_pd_current;
  dtc.puv_pd_current = &OD_RAM.x4001_adcsample.uv_pd_current;
  dtc.ptsen = &OD_RAM.x4001_adcsample.tsen;
  
  dtc.padcsample = &OD_RAM.x4001_adcsample.led_current;

  dtc_dacStart();
  dtc_gptStart();
}

/*
 * DAC
 */
static const DACConfig dac1cfg1 = {
  .init         = 0U,
  .datamode     = DAC_DHRM_12BIT_RIGHT,
  .cr           = 0
};

void dtc_dacStart(void)
{
  dacStart(&DACD1, &dac1cfg1);
}

void dtc_dacStop(void)
{
  dacStop(&DACD1);
}

void dtc_dacSet(void)
{
  osalSysLock();
  dacPutChannelX(&DACD1, 0, *dtc.pdac);
  osalSysUnlock();
}

/*
 * ADC streaming callback.
 */
static void adc_callback(ADCDriver *adcp) {
  sample_t *psample = (sample_t*)adcp->samples;
  int i = adcIsBufferComplete(adcp); 
 
  OD_RAM.x4001_adcsample.led_current = psample[i].led_current;
  OD_RAM.x4001_adcsample.led_swir_pd_current = psample[i].led_swir_pd_current;
  OD_RAM.x4001_adcsample.uv_pd_current = psample[i].uv_pd_current;
  OD_RAM.x4001_adcsample.tsen = psample[i].tsen;
}

static void adc_error_callback(ADCDriver *adcp, adcerror_t err) {
  (void)adcp;
  (void)err;

  (*dtc.perror) = (*dtc.perror) | ERROR_ADC_CB;
}

/*
 * ADC conversion group.
 */
static const ADCConversionGroup adcgrpcfg1 = {
  TRUE,
  NUM_CHANNELS,
  adc_callback,
  adc_error_callback,
  ADC_CFGR1_EXTEN_RISING | ADC_CFGR1_RES_12BIT,   /* CFGR1 */
  ADC_TR(0, 0),                                   /* TR */
  ADC_SMPR_SMP_239P5,                               /* SMPR */
  ADC_CHSELR_CHSEL1 | ADC_CHSELR_CHSEL5  |        /* CHSELR */
  ADC_CHSELR_CHSEL6 | ADC_CHSELR_CHSEL17          
};

/**
 * GPT6 configuration.
 */
static const GPTConfig gpt1cfg1 = {
  .frequency    = 1000000U,
  .callback     = NULL,
  .cr2          = TIM_CR2_MMS_1,    // MMS = 010 = TRGO on Update Event.    
  .dier         = 0U
};

void dtc_gptStart(void)
{
  gptStart(&GPTD1, &gpt1cfg1);
  gptStartContinuous(&GPTD1, 100U);
}

void dtc_gptStop(void)
{
  gptStop(&GPTD1);
}

void dtc_adcStart(void)
{
  adcSTM32SetCCR(ADC_CCR_TSEN);
  adcStartConversion(&ADCD1, &adcgrpcfg1, (adcsample_t *)sample, BUFFER_DEPTH);
}

void dtc_adcStop(void)
{
  adcStop(&ADCD1);
}

/**
 * blink thread 
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

  /// give oresat_start time to release the adc bus
  while(ADCD1.state != ADC_READY)
  {
    chThdSleepMilliseconds(200);
  }

  dtc_adcStart();

  while(!chThdShouldTerminateX()) 
  {
//*   
    chprintf(DEBUG_SERIAL, "\r\nctrl:                  %04u \r\n", *dtc.pctrl);
    chprintf(DEBUG_SERIAL,     "mux_select:            %04u \r\n", *dtc.pmux_select);
    chprintf(DEBUG_SERIAL,     "dac:                   %04u \r\n", *dtc.pdac);
    chprintf(DEBUG_SERIAL,     "status:              0x%04X \r\n", *dtc.pstatus);
    chprintf(DEBUG_SERIAL,     "error:               0x%04X \r\n", *dtc.perror);
    chprintf(DEBUG_SERIAL,     "led_current:           %04u \r\n", *dtc.pled_current);
    chprintf(DEBUG_SERIAL,     "led_swir_pd_current:   %04u \r\n", *dtc.pled_swir_pd_current);
    chprintf(DEBUG_SERIAL,     "uv_pd_current:         %04u \r\n", *dtc.puv_pd_current);
    chprintf(DEBUG_SERIAL,     "tsen:                  %04u \r\n", *dtc.ptsen);
//*/

    chThdSleepMilliseconds(500);
  }

  dbgprintf("Terminating adc_watch thread...\r\n");

  chThdExit(MSG_OK);
}

void dtc_muxEnable(void)
{
  palSetPad(GPIOB, DTC_MUX_EN);
  (*dtc.pctrl) |= (1 << CTRL_MUX_EN);
}

void dtc_muxDisable(void)
{
  palClearPad(GPIOB, DTC_MUX_EN);
  (*dtc.pctrl) &= ~(1 << CTRL_MUX_EN);
}

void dtc_muxSelect(void)
{
 if(*dtc.pmux_select < DTC_NUM_DIODES)
  {
    osalSysLock();
    palWriteGroup(
      GPIOB, 
      PAL_PORT_BIT(DTC_MUX_A0) | PAL_PORT_BIT(DTC_MUX_A1) | PAL_PORT_BIT(DTC_MUX_A2), 
      0, 
      (*dtc.pmux_select << DTC_MUX_A0)
    );
    *dtc.pctrl = (*dtc.pstatus & (~CTRL_MUX_MASK)) | (*dtc.pmux_select << CTRL_MUX_A0);
    osalSysUnlock();
  }
}

/**
 *  diode select
*/
THD_WORKING_AREA(diode_select_wa, 0x400);
THD_FUNCTION(diode_select, arg)
{
  (void)arg;

  //dtc_muxEnable(); //PB12 

  while (!chThdShouldTerminateX()) 
  {
    
    if(*dtc.pctrl > 0)
    {
      dtc.pfunc[*dtc.pctrl]();
      *dtc.pctrl = 0;
    }
  
    dtc_muxSelect();
    dtc_dacSet();

    chThdSleepMilliseconds(200);
  }

  dbgprintf("Terminating diode select thread...\r\n");

  chThdExit(MSG_OK);
}

