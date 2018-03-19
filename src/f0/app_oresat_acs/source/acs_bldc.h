#ifndef _ACS_BLDC_H_
#define _ACS_BLDC_H_

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

/*
#define PWM_TIMER_FREQ	40000U
#define PWM_FREQ				360U // periods per sec
//*/
//*
#define PWM_TIMER_FREQ	1e6  // Hz
#define PWM_FREQ				10000 // periods per sec
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

extern THD_WORKING_AREA(wa_bldcThread,128);
extern THD_FUNCTION(bldcThread,arg);

#endif
