#ifndef ACS_BLDC_H
#define ACS_BLDC_H

#include "ch.h"
#include "hal.h"

typedef struct{
	int stepU;
	int stepV;
	int stepW;
	int sinctrl_size;
	int phase_shift;
} BldcConfig;

#define PWM_CLOCK_FREQ	40000
#define PWM_FREQ				1
#define PWM_PERIOD			PWM_CLOCK_FREQ/PWM_FREQ

#define PWM_CH1					0
#define PWM_CH2					1
#define PWM_CH3					2

#define PWM_DC_CH1			2000
#define PWM_DC_CH2			4000
#define PWM_DC_CH3			8000

extern void bldcInit(void);
extern void bldcStart(void);
extern void bldcStop(void);

extern void bldcSinStart(void);

#endif
