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

#define DTC_LED                 GPIOA_LED
#define DTC_MUX_EN              GPIOB_LED_MUX_EN
#define DTC_MUX_A0              GPIOB_LED_MUX_A0
#define DTC_MUX_A1              GPIOB_LED_MUX_A1
#define DTC_MUX_A2              GPIOB_LED_MUX_A2
#define DTC_POUT                GPIOB_POUTPROT  //PB0

#define DTC_NUM_DIODES          8

#define SAMPLES                 2

#define ERROR_DAC               (1 << 0)
#define ERROR_ADC_CB            (1 << 1)
#define ERROR_ADC_START         (1 << 2)
#define ERROR_ADC_STOP          (1 << 3)
#define ERROR_4                 (1 << 4)
#define ERROR_5                 (1 << 5)


/// status OD definitions
#define CTRL_DAC_EN             0x0
#define CTRL_GPT_EN             0x1
#define CTRL_ADC_EN             0x2
#define CTRL_MUX_EN             0x3
#define CTRL_MUX_A0             0x4
#define CTRL_MUX_A1             0x5
#define CTRL_MUX_A2             0x6
#define CTRL_7                  0x7
#define CTRL_8                  0x8
#define CTRL_9                  0x9
#define CTRL_A                  0xA
#define CTRL_B                  0xB
#define CTRL_C                  0xC
#define CTRL_D                  0xD
#define CTRL_E                  0xE
#define CTRL_F                  0xFa

// bit masks
#define CTRL_MUX_MASK           (0x7 << CTRL_MUX_A0)

typedef struct 
{
  adcsample_t led_current;          // PA1
  adcsample_t led_swir_pd_current;  // PA5
  adcsample_t uv_pd_current;        // PA6
  adcsample_t tsen;                 // PA17
} sample_t;

#define NUM_CHANNELS            sizeof(sample_t)/sizeof(adcsample_t)

#define MAX_FUNCTIONS           64

typedef struct 
{
  uint8_t *pctrl;
  uint8_t *pmux_select;
  uint16_t *pdac;
  uint16_t *pstatus;
  uint16_t *perror;
  void (*pfunc[MAX_FUNCTIONS])(void);
  adcsample_t *pled_current;
  adcsample_t *pled_swir_pd_current;
  adcsample_t *puv_pd_current;
  adcsample_t *ptsen;
  adcsample_t *padcsample;
  int functionCount;
  ADCDriver *padc;
  GPTDriver *pgpt;
  
} DTC; 

/**
 * thread declaration 
*/
extern THD_WORKING_AREA(blink_wa, 0x400);
extern THD_FUNCTION(blink, arg);
extern THD_WORKING_AREA(adc_watch_wa, 0x400);
extern THD_FUNCTION(adc_watch, arg);
extern THD_WORKING_AREA(ctrl_thread_wa, 0x400);
extern THD_FUNCTION(ctrl_thread, arg);
/**
 * function declaration 
*/
void dtc_init(void);
void dtc_callCtrlThreadFunctions(void);
void dtc_dacStart(void);
void dtc_dacStop(void);
void dtc_dacSet(void);
void dtc_gptStart(void);
void dtc_gptStop(void);
void dtc_adcStart(void);
void dtc_adcStop(void);
void dtc_muxEnable(void);
void dtc_muxDisable(void);
void dtc_muxSelect(void);

#endif
