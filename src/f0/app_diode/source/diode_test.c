#include "ch.h"
#include "diode_test.h"
#include "CANopen.h"
#include "chprintf.h"
#include "OD.h"

DTC dtc = { 0 };
sample_t sample[SAMPLES];
#define BUFFER_DEPTH            sizeof(sample)/sizeof(sample_t)

/*
 * dtc_callCtrlThreadFunctions
 * gets called every time the ctrl_thread polls OD dtc_ctrl 
 */
void dtc_callCtrlThreadFunctions(void)
{
  
	// TODO: call these functions based on status object
	dtc_muxSelect();
	dtc_dacSet();
}

/*
 * dtc_init
 * initializes diode test card
 */
void dtc_init(void)
{
	// fill array with function pointers
	// their indeces are used to call from the OD using CANopen
  dtc.pfunc[1] = &dtc_dacStart;
  dtc.pfunc[2] = &dtc_dacStop;
  dtc.pfunc[3] = &dtc_gptStart;
  dtc.pfunc[4] = &dtc_gptStop;
  dtc.pfunc[5] = &dtc_adcStart;
  dtc.pfunc[6] = &dtc_adcStop;
  dtc.pfunc[7] = &dtc_muxEnable;
  dtc.pfunc[8] = &dtc_muxDisable;
  dtc.pfunc[9] = &dtc_clearErrors;
	//        ^  lastFunctionIndex

  int i = 1; // determine last index of functions 
  for(; *dtc.pfunc[i] && i < MAX_FUNCTIONS; ++i){}
  dtc.lastFunctionIndex = i;

	// create pointers to OD objects
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

	// start drivers
  dtc_dacStart();
  dtc_gptStart();
}

/*
 * DAC configuration
 */
static const DACConfig dac1cfg1 = {
  .init         = 0U,
  .datamode     = DAC_DHRM_12BIT_RIGHT,
  .cr           = 0
};

/*
 *	dtc_dacStart 
 *	wrapper that calls the ChibiOS version	
 */
void dtc_dacStart(void)
{
  dacStart(&DACD1, &dac1cfg1);
}

/*
 * dtc_dacStop
 * wrapper that calls the ChibiOS version
 */
void dtc_dacStop(void)
{
  dacStop(&DACD1);
}

/*
 * dtc_dacSet
 * sets the dac with the value contained in the OD dtc_dac object 
 */
void dtc_dacSet(void)
{
	if(*dtc.pdac < 0xFFF)
	{
		osalSysLock();
		dacPutChannelX(&DACD1, 0, *dtc.pdac);
		osalSysUnlock();
	}
	else
	{
		//TODO: set bit in error object
	}
}

/*
 * ADC streaming callback
 * writes to the OD on completion of an adc sample
 */
static void adc_callback(ADCDriver *adcp) {
  sample_t *psample = (sample_t*)adcp->samples;
  int i = adcIsBufferComplete(adcp); 
 
  OD_RAM.x4001_adcsample.led_current = psample[i].led_current;
  OD_RAM.x4001_adcsample.led_swir_pd_current = psample[i].led_swir_pd_current;
  OD_RAM.x4001_adcsample.uv_pd_current = psample[i].uv_pd_current;
  OD_RAM.x4001_adcsample.tsen = psample[i].tsen;
}

/*
 * ADC error callback
 * called by ChibiOS if ADC sample fails
 */
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
	/* SMPR set to long delay because of possible sanmple and hold issue*/
  ADC_SMPR_SMP_239P5,                             /* SMPR */
  ADC_CHSELR_CHSEL1 | ADC_CHSELR_CHSEL5  |        /* CHSELR */
  ADC_CHSELR_CHSEL6 | ADC_CHSELR_CHSEL17          
};

/**
 * GPT6 configuration
 * general purpose timer 6
 */
static const GPTConfig gpt1cfg1 = {
  .frequency    = 1000000U,
  .callback     = NULL,
  .cr2          = TIM_CR2_MMS_1,    // MMS = 010 = TRGO on Update Event.    
  .dier         = 0U
};

/*
 * dtc_gptStart
 * wrapper for ChibiOS gpt driver function calls
 */
void dtc_gptStart(void)
{
  gptStart(&GPTD1, &gpt1cfg1);
  gptStartContinuous(&GPTD1, 100U);
  (*dtc.pstatus) |= (1 << CTRL_GPT_EN); // sets the status bit
}
/*
 * dtc_gptStop
 * wrapper for ChibiOS gpt driver function calls
 */
void dtc_gptStop(void)
{
  gptStop(&GPTD1);
  (*dtc.pstatus) &= ~(1 << CTRL_GPT_EN); // clears the status bit
}

/*
 * dtc_adcStart
 * wrapper for ChibiOS gpt driver function calls
 */
void dtc_adcStart(void)
{
  adcStart(&ADCD1, NULL);
  if(ADCD1.state == ADC_READY)
  {
    (*dtc.pstatus) |= (1 << CTRL_ADC_EN); // sets the status bit
    adcSTM32SetCCR(ADC_CCR_TSEN); // enable temperature sensor
    adcStartConversion(&ADCD1, &adcgrpcfg1, (adcsample_t *)sample, BUFFER_DEPTH);
  }
  else
  {
    (*dtc.perror) = (*dtc.perror) | ERROR_ADC_START;
  }
}

/*
 * dtc_adcStop
 * wrapper for ChibiOS gpt driver function calls
 */
void dtc_adcStop(void)
{
  adcStop(&ADCD1);
  if(ADCD1.state == ADC_STOP)
  {
    (*dtc.pstatus) &= ~(1 << CTRL_ADC_EN);
  }
  else
  {
    (*dtc.perror) = (*dtc.perror) | ERROR_ADC_STOP;
  }
}

/*
 * dtc_clearErrors
 * clears all errors
 */
void dtc_clearErrors(void)
{
  (*dtc.perror) = 0;
}

/*
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

/*
 * diode test card watch thread
 *
 * watches dtc OD objects and dumps them to serial output
 */
THD_WORKING_AREA(dtc_watch_wa, 0x400);
THD_FUNCTION(dtc_watch, arg)
{
  (void)arg; 

  // give oresat_start time to release the adc bus
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

  dbgprintf("Terminating dtc_watch thread...\r\n");

  chThdExit(MSG_OK);
}

/*
 * dtc_muxEnable
 * enables the diode mux (logic low enable)
 */
void dtc_muxEnable(void)
{	
  palClearPad(GPIOB, DTC_MUX_EN); // logic low enable
  (*dtc.pstatus) |= (1 << CTRL_MUX_EN);
}
/*
 * dtc_muxDisable
 * disables the diode mux (logic high disable)
 */
void dtc_muxDisable(void)
{
  palSetPad(GPIOB, DTC_MUX_EN); // logic high disable
  (*dtc.pstatus) &= ~(1 << CTRL_MUX_EN);
}

/*
 * dtc_muxSelect
 * select desired diode (0 -7)
 */
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
    *dtc.pstatus = (*dtc.pstatus & (~CTRL_MUX_MASK)) | (*dtc.pmux_select << CTRL_MUX_A0);
    osalSysUnlock();
  }
}

/*
 * app control thread 
 */
THD_WORKING_AREA(ctrl_thread_wa, 0x400);
THD_FUNCTION(ctrl_thread, arg)
{
  (void)arg;

  dtc_muxEnable();  

  while (!chThdShouldTerminateX()) 
  {
    
    if(*dtc.pctrl > 0) 
    {
			if(*dtc.pctrl <= dtc.lastFunctionIndex)
			{
				dtc.pfunc[*dtc.pctrl]();
			}
			else
			{	
				// TODO: set error bit in OD
			}
			
			*dtc.pctrl = 0;
    }
    
		dtc_callCtrlThreadFunctions();

    chThdSleepMilliseconds(200);
  }

  dbgprintf("Terminating diode select thread...\r\n");

  chThdExit(MSG_OK);
}

