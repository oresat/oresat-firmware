#ifndef _DIODE_TEST_H_
#define _DIODE_TEST_H_

#include "ch.h"
#include "hal.h"

#define ENABLE_NV_MEMORY_UPDATE_CODE      0
#define ENABLE_SERIAL_DEBUG_OUTPUT        1

#if ENABLE_SERIAL_DEBUG_OUTPUT || ENABLE_NV_MEMORY_UPDATE_CODE
#define DEBUG_SERIAL    (BaseSequentialStream*) &SD2

#define dbgprintf(str, ...) chprintf((BaseSequentialStream*) &SD2, str, ##__VA_ARGS__)
#else
#define dbgprintf(str, ...)
#endif

#define DTC_NODE_ID             0x54

#define DTC_MUX_EN              GPIOB_LED_MUX_EN
#define DTC_MUX_A0              GPIOB_LED_MUX_A0
#define DTC_MUX_A1              GPIOB_LED_MUX_A1
#define DTC_MUX_A2              GPIOB_LED_MUX_A2

#define DTC_NUM_DIODES          8

#define SAMPLES                 2

#define ERROR_ADC_CB            (1 << 0)
#define ERROR_1                 (1 << 1)
#define ERROR_2                 (1 << 2)
#define ERROR_3                 (1 << 3)
#define ERROR_4                 (1 << 4)
#define ERROR_5                 (1 << 5)

typedef struct 
{
  adcsample_t led_current;          // PA1
  adcsample_t led_swir_pd_current;  // PA5
  adcsample_t uv_pd_current;        // PA6
  adcsample_t tsen;                 // PA7
} sample_t;

#define NUM_CHANNELS            sizeof(sample_t)/sizeof(adcsample_t)

typedef struct 
{
  uint16_t *padcsample;
  uint16_t *pdiode_select;
  uint16_t *pdac;
  uint16_t *perror;
  uint16_t adc_callback_count;
  sample_t *psample;
} DTC; 

/**
 * blinking example thread declaration 
*/
extern THD_WORKING_AREA(blink_wa, 0x400);
extern THD_FUNCTION(blink, arg);
extern THD_WORKING_AREA(adc_watch_wa, 0x400);
extern THD_FUNCTION(adc_watch, arg);
extern THD_WORKING_AREA(diode_select_wa, 0x400);
extern THD_FUNCTION(diode_select, arg);
void dtc_init(void);
void dac_start(void);
void adc_start(void);

#endif
