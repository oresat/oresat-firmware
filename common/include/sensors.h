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
