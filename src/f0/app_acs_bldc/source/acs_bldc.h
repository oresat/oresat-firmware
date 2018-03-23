#ifndef ACS_BLDC_H
#define ACS_BLDC_H

#include "ch.h"
#include "hal.h"

#define SADDLE
#define SCALE		6/10+2000;
#define PERIOD 	360

#ifdef SADDLE
#undef PERIOD
#define PERIOD 	384
#endif

#define sinctrl_t int
//#define sinctrl_t uint32_t // in testing

typedef struct{
	sinctrl_t u,v,w,phase_shift;
	int	sinctrl_size;
} BldcConfig;

//*
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
