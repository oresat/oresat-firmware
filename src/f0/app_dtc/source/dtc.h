#ifndef _DTC_H_
#define _DTC_H_

#include "ch.h"
#include "hal.h"

//#define STM32F0xx_MCUCONF

#define ENABLE_NV_MEMORY_UPDATE_CODE      0
#define ENABLE_SERIAL_DEBUG_OUTPUT        1

#if ENABLE_SERIAL_DEBUG_OUTPUT || ENABLE_NV_MEMORY_UPDATE_CODE
#define DEBUG_SERIAL    (BaseSequentialStream*) &SD2

#define dbgprintf(str, ...) chprintf((BaseSequentialStream*) &SD2, str, ##__VA_ARGS__)
#else
#define dbgprintf(str, ...)
#endif

#define SAMPLES                 2
#define DTC_NODE_ID             0x64

#define DAC_BUFFER_SIZE         360
//#define DAC_BUFFER_SIZE 2

#define DTC_MUX_EN              GPIOB_LED_MUX_EN
#define DTC_MUX_A0              GPIOB_LED_MUX_A0
#define DTC_MUX_A1              GPIOB_LED_MUX_A1
#define DTC_MUX_A2              GPIOB_LED_MUX_A2

#define DTC_NUM_DIODES          8

typedef struct 
{
  adcsample_t ch1;
  adcsample_t ch2;
  adcsample_t ts;
  adcsample_t vrefint;
} sample_t;

#define NUM_CHANNELS            sizeof(sample_t)/sizeof(adcsample_t)

typedef struct 
{
  uint16_t *pdiode_select;
  uint16_t *padcsample;
  uint16_t *perrors;
  uint16_t adc_callback_count;
  sample_t *psample;
} DTC; 

/*
 * DAC test buffer (sine wave).
 */
/*
static const dacsample_t dac_buffer[DAC_BUFFER_SIZE] = {
  0, 3200 
};
//*/
//*
static const dacsample_t dac_buffer[DAC_BUFFER_SIZE] = {
  2047, 2082, 2118, 2154, 2189, 2225, 2260, 2296, 2331, 2367, 2402, 2437,
  2472, 2507, 2542, 2576, 2611, 2645, 2679, 2713, 2747, 2780, 2813, 2846,
  2879, 2912, 2944, 2976, 3008, 3039, 3070, 3101, 3131, 3161, 3191, 3221,
  3250, 3278, 3307, 3335, 3362, 3389, 3416, 3443, 3468, 3494, 3519, 3544,
  3568, 3591, 3615, 3637, 3660, 3681, 3703, 3723, 3744, 3763, 3782, 3801,
  3819, 3837, 3854, 3870, 3886, 3902, 3917, 3931, 3944, 3958, 3970, 3982,
  3993, 4004, 4014, 4024, 4033, 4041, 4049, 4056, 4062, 4068, 4074, 4078,
  4082, 4086, 4089, 4091, 4092, 4093, 4094, 4093, 4092, 4091, 4089, 4086,
  4082, 4078, 4074, 4068, 4062, 4056, 4049, 4041, 4033, 4024, 4014, 4004,
  3993, 3982, 3970, 3958, 3944, 3931, 3917, 3902, 3886, 3870, 3854, 3837,
  3819, 3801, 3782, 3763, 3744, 3723, 3703, 3681, 3660, 3637, 3615, 3591,
  3568, 3544, 3519, 3494, 3468, 3443, 3416, 3389, 3362, 3335, 3307, 3278,
  3250, 3221, 3191, 3161, 3131, 3101, 3070, 3039, 3008, 2976, 2944, 2912,
  2879, 2846, 2813, 2780, 2747, 2713, 2679, 2645, 2611, 2576, 2542, 2507,
  2472, 2437, 2402, 2367, 2331, 2296, 2260, 2225, 2189, 2154, 2118, 2082,
  2047, 2012, 1976, 1940, 1905, 1869, 1834, 1798, 1763, 1727, 1692, 1657,
  1622, 1587, 1552, 1518, 1483, 1449, 1415, 1381, 1347, 1314, 1281, 1248,
  1215, 1182, 1150, 1118, 1086, 1055, 1024,  993,  963,  933,  903,  873,
   844,  816,  787,  759,  732,  705,  678,  651,  626,  600,  575,  550,
   526,  503,  479,  457,  434,  413,  391,  371,  350,  331,  312,  293,
   275,  257,  240,  224,  208,  192,  177,  163,  150,  136,  124,  112,
   101,   90,   80,   70,   61,   53,   45,   38,   32,   26,   20,   16,
    12,    8,    5,    3,    2,    1,    0,    1,    2,    3,    5,    8,
    12,   16,   20,   26,   32,   38,   45,   53,   61,   70,   80,   90,
   101,  112,  124,  136,  150,  163,  177,  192,  208,  224,  240,  257,
   275,  293,  312,  331,  350,  371,  391,  413,  434,  457,  479,  503,
   526,  550,  575,  600,  626,  651,  678,  705,  732,  759,  787,  816,
   844,  873,  903,  933,  963,  993, 1024, 1055, 1086, 1118, 1150, 1182,
  1215, 1248, 1281, 1314, 1347, 1381, 1415, 1449, 1483, 1518, 1552, 1587,
  1622, 1657, 1692, 1727, 1763, 1798, 1834, 1869, 1905, 1940, 1976, 2012
};
//*/

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
