/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/* ChibiOS header files */
#include "ch.h"
#include "hal.h"
#include "chprintf.h"

/* Project header files */
#include "oresat.h"
#include "nucleo.h"

//#define DEBUG_SERIAL    (BaseSequentialStream*) &SD2

#define ADC_GRP1_NUM_CHANNELS   1
#define ADC_GRP1_BUF_DEPTH      8

#define ADC_GRP2_NUM_CHANNELS   4
#define ADC_GRP2_BUF_DEPTH      16

static adcsample_t samples1[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];
static adcsample_t samples2[ADC_GRP2_NUM_CHANNELS * ADC_GRP2_BUF_DEPTH];

adcsample_t *psamples1 = samples1;
/*
 * ADC streaming callback.
 */
size_t nx = 0, ny = 0;
static void adccallback(ADCDriver *adcp) {

  if (adcIsBufferComplete(adcp)) {
    nx += 1;
  }
  else {
    ny += 1;
  }
}

static void adcerrorcallback(ADCDriver *adcp, adcerror_t err) {

  (void)adcp;
  (void)err;
}

/*
 * ADC conversion group.
 * Mode:        Linear buffer, 8 samples of 1 channel, SW triggered.
 * Channels:    IN10.
 */
static const ADCConversionGroup adcgrpcfg1 = {
  FALSE,
  ADC_GRP1_NUM_CHANNELS,
  NULL,
  adcerrorcallback,
  ADC_CFGR1_CONT | ADC_CFGR1_RES_12BIT,             /* CFGR1 */
  ADC_TR(0, 0),                                     /* TR */
  ADC_SMPR_SMP_1P5,                                 /* SMPR */
  ADC_CHSELR_CHSEL10                                /* CHSELR */
};

/*
 * ADC conversion group.
 * Mode:        Continuous, 16 samples of 8 channels, SW triggered.
 * Channels:    IN10, IN11, Sensor, VRef.
 */
static const ADCConversionGroup adcgrpcfg2 = {
  TRUE,
  ADC_GRP2_NUM_CHANNELS,
  adccallback,
  adcerrorcallback,
  ADC_CFGR1_CONT | ADC_CFGR1_RES_12BIT,             /* CFGR1 */
  ADC_TR(0, 0),                                     /* TR */
  ADC_SMPR_SMP_28P5,                                /* SMPR */
  ADC_CHSELR_CHSEL10 | ADC_CHSELR_CHSEL11 |
  ADC_CHSELR_CHSEL16 | ADC_CHSELR_CHSEL17           /* CHSELR */
};

static worker_t blink_worker;
static thread_descriptor_t blink_worker_desc = {
  .name = "blink count tpdo thread",
  .wbase = THD_WORKING_AREA_BASE(blink_wa),
  .wend = THD_WORKING_AREA_END(blink_wa),
  .prio = NORMALPRIO,
  .funcp = blink,
  .arg = NULL
};

//*
static worker_t adc_watch_worker;
static thread_descriptor_t adc_watch_worker_desc = {
  .name = "adc watcher thread",
  .wbase = THD_WORKING_AREA_BASE(adc_watch_wa),
  .wend = THD_WORKING_AREA_END(adc_watch_wa),
  .prio = NORMALPRIO,
  .funcp = adc_watch,
  .arg = &samples1 
  //.arg = NULL 
};
//*/

static oresat_config_t oresat_conf = {
  .cand = &CAND1,
  .node_id = DTC_NODE_ID,
  .bitrate = ORESAT_DEFAULT_BITRATE,
};

/**
 * @brief App Initialization
 */
static void app_init(void)
{
  /* App initialization */
  reg_worker(&blink_worker, &blink_worker_desc, true, true);
  //test_dac_start(); 
  reg_worker(&adc_watch_worker, &adc_watch_worker_desc, true, true);
  
  /* Start up debug output */
  sdStart(&SD2, NULL);
}

/**
 * @brief Main Application
 */
int main(void)
{
  // Initialize and start
  oresat_init(&oresat_conf);
  app_init();
  chprintf(DEBUG_SERIAL, "\r\nStarting app_diode...\r\n");
  palSetPad(GPIOA, GPIOA_DAC_OUT1);
  example_dac_start();
  
  /*
   * Setting up analog inputs used by the demo.
   */
  palSetGroupMode(GPIOA, PAL_PORT_BIT(0) | PAL_PORT_BIT(1),
                  0, PAL_MODE_INPUT_ANALOG);

    /*
   * Activates the ADC1 driver and the temperature sensor.
   */
  adcStart(&ADCD1, NULL);
  adcSTM32SetCCR(ADC_CCR_VBATEN | ADC_CCR_TSEN | ADC_CCR_VREFEN);

  /*
   * Linear conversion.
   */
  adcConvert(&ADCD1, &adcgrpcfg1, samples1, ADC_GRP1_BUF_DEPTH);
  chThdSleepMilliseconds(1000);

  /*
   * Starts an ADC continuous conversion.
   */
  adcStartConversion(&ADCD1, &adcgrpcfg2, samples2, ADC_GRP2_BUF_DEPTH);
 
  oresat_start();

  return 0;
}
