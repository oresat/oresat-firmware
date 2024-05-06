#include "ch.h"
#include "nucleo.h"
#include "CANopen.h"
#include "chprintf.h"
#include "OD.h"

/*
 * DAC streaming callback.
 */
size_t nx = 0, ny = 0, nz = 0;
static void end_cb1(DACDriver *dacp) {

  nz++;
  if (dacIsBufferComplete(dacp)) {
    nx += DAC_BUFFER_SIZE / 2;
  }
  else {
    ny += DAC_BUFFER_SIZE / 2;
  }

  if ((nz % 1000) == 0) {
    palTogglePad(GPIOA, GPIOA_DAC_OUT1);
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
  //.frequency    = 10U,
  .frequency    = 1000000U,
  .callback     = NULL,
  .cr2          = TIM_CR2_MMS_1,    /* MMS = 010 = TRGO on Update Event.    */
  .dier         = 0U
};

void dac_start(void)
{
  palSetPadMode(GPIOA, 4, PAL_MODE_INPUT_ANALOG);
  dacStart(&DACD1, &dac1cfg1);
  /*                                                                            
   * Starting GPT6 driver, it is used for triggering the DAC.
   */                       
  gptStart(&GPTD6, &gpt6cfg1);

  /*
   * Starting a continuous conversion.
   */
  dacStartConversion(&DACD1, &dacgrpcfg1,
                     (dacsample_t *)dac_buffer, DAC_BUFFER_SIZE);               
  gptStartContinuous(&GPTD6, 2U);

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
    OD_RAM.x4000_blinks.blinkcount = ++blinkcount;
  }

  dbgprintf("Terminating blink thread...\r\n");

  palClearLine(LINE_LED);
  chThdExit(MSG_OK);
}
