#ifndef ACS_BLDC_H
#define ACS_BLDC_H

#include "ch.h"
#include "hal.h"

#define SADDLE

#define PERIOD 360

#ifdef SADDLE
#undef PERIOD
#define PERIOD 384
#endif


typedef struct{
	int u,v,w, // motor phases
			sinctrl_size,
			phase_shift;
} BldcConfig;

/*
#define PWM_TIMER_FREQ	40000U
#define PWM_FREQ				360U // periods per sec
//*/
//*
//#define PWM_TIMER_FREQ	40000 // Hz
#define PWM_TIMER_FREQ	1e6  // Hz
#define PWM_FREQ				50000// periods per sec
//*/
#define PWM_PERIOD			PWM_TIMER_FREQ/PWM_FREQ 

#define PWM_U					0U
#define PWM_V					1U
#define PWM_W					2U

extern void bldcInit(void);
extern void bldcStart(void);
extern void bldcStop(void);

extern void bldcSinStart(void);

#endif
