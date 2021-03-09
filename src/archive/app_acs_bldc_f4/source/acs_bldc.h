#ifndef ACS_BLDC_H
#define ACS_BLDC_H

#include "ch.h"
#include "hal.h"

typedef struct{
	int u;
	int v;
	int w;
	int count;
	int sinctrl_size;
	int phase_shift;
} BldcConfig;

#define GPIOPort GPIOA
// Pin number
#define ACH1 8U
#define ACH2 9U
#define ACH3 10U

#define GPIOComp GPIOB
#define BCH1 13U
#define BCH2 14U
#define BCH3 15U


/*
#define PWM_TIMER_FREQ	40000U
#define PWM_FREQ				360U // periods per sec
//*/
//*
//#define PWM_TIMER_FREQ	40000 // Hz
#define PWM_TIMER_FREQ	1e6  // Hz
#define PWM_FREQ				20000// periods per sec
//*/
#define PWM_PERIOD			PWM_TIMER_FREQ/PWM_FREQ 

#define PWM_CH1					0U
#define PWM_CH2					1U
#define PWM_CH3					2U

#define PWM_DC_CH1			2000U
#define PWM_DC_CH2			4000U
#define PWM_DC_CH3			8000U

extern void bldcInit(void);
extern void bldcStart(void);
extern void bldcStop(void);

extern void bldcSinStart(void);

#endif
