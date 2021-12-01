#ifndef _SENSORS_H_
#define _SENSORS_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(STM32F0xx_MCUCONF)
#define TS_CAL1_BASE            ((uint32_t)0x1FFFF7B8)
#define TS_CAL2_BASE            ((uint32_t)0x1FFFF7C2)
#define VREFINT_CAL_BASE        ((uint32_t)0x1FFFF7BA)
#define TS_CAL1_TEMP            30
#define TS_CAL2_TEMP            110
#define VREFINT_CAL_VOLT        330
#define ADC_REG_CFG             ADC_CFGR1_CONT | ADC_CFGR1_RES_12BIT,               /* CFGR1    */  \
                                ADC_TR(0, 0),                                       /* TR       */  \
                                ADC_SMPR_SMP_239P5,                                 /* SMPR     */  \
                                ADC_CHSELR_CHSEL16 | ADC_CHSELR_CHSEL17             /* CHSELR   */
#define ADC_ENABLE_SENSORS(adc) {adcSTM32SetCCR(ADC_CCR_TSEN | ADC_CCR_VREFEN);}
#elif defined(STM32F4xx_MCUCONF)
#define TS_CAL1_BASE            ((uint32_t)0x1FFF7A2C)
#define TS_CAL2_BASE            ((uint32_t)0x1FFF7A2E)
#define VREFINT_CAL_BASE        ((uint32_t)0x1FFF7A2A)
#define TS_CAL1_TEMP            30
#define TS_CAL2_TEMP            110
#define VREFINT_CAL_VOLT        330
#define ADC_REG_CFG             0,                                                  /* CR1      */  \
                                ADC_CR2_SWSTART,                                    /* CR2      */  \
                                ADC_SMPR1_SMP_SENSOR(ADC_SAMPLE_480)                /* SMPR1    */  \
                                | ADC_SMPR1_SMP_VREF(ADC_SAMPLE_480),                               \
                                0,                                                  /* SMPR2    */  \
                                0,                                                  /* HTR      */  \
                                0,                                                  /* LTR      */  \
                                0,                                                  /* SQR1     */  \
                                0,                                                  /* SQR2     */  \
                                ADC_SQR3_SQ1_N(ADC_CHANNEL_SENSOR)                  /* SQR3     */  \
                                | ADC_SQR3_SQ2_N(ADC_CHANNEL_VREFINT)
#define ADC_ENABLE_SENSORS(adc) {adcSTM32EnableTSVREFE();}
#elif defined(STM32L4xx_MCUCONF)
#define TS_CAL1_BASE            ((uint32_t)0x1FFF75A8)
#define TS_CAL2_BASE            ((uint32_t)0x1FFF75CA)
#define VREFINT_CAL_BASE        ((uint32_t)0x1FFF75AA)
#define TS_CAL1_TEMP            30
#define TS_CAL2_TEMP            130
#define VREFINT_CAL_VOLT        330
#define ADC_REG_CFG             ADC_CFGR_CONT,                                      /* CFGR     */  \
                                0,                                                  /* CFGR2    */  \
                                ADC_TR(0, 4095),                                    /* TR1      */  \
                                0,                                                  /* TR2      */  \
                                0,                                                  /* TR3      */  \
                                0,                                                  /* AWD2CR   */  \
                                0,                                                  /* AWD3CR   */  \
                                {                                                   /* SMPR[2]  */  \
                                    0,                                                              \
                                    ADC_SMPR2_SMP_AN16(ADC_SMPR_SMP_47P5)                           \
                                    | ADC_SMPR2_SMP_AN17(ADC_SMPR_SMP_47P5),                        \
                                },                                                                  \
                                {                                                   /* SQR[4]   */  \
                                    ADC_SQR1_SQ1_N(ADC_CHANNEL_IN16)                                \
                                    | ADC_SQR1_SQ2_N(ADC_CHANNEL_IN17),                             \
                                    0,                                                              \
                                    0,                                                              \
                                    0                                                               \
                                }
#define ADC_ENABLE_SENSORS(adc) {adcSTM32EnableTS(adc); adcSTM32EnableVREF(adc);}
#else
#error "No Sensors Config for this MCU"
#endif

#define TS_CAL1_VAL             (*((uint16_t*)TS_CAL1_BASE))
#define TS_CAL2_VAL             (*((uint16_t*)TS_CAL2_BASE))
#define VREFINT_CAL_VAL         (*((uint16_t*)VREFINT_CAL_BASE))

void sensors_init(void);
void sensors_start(void);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
