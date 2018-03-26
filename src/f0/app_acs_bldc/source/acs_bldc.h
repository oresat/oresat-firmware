#ifndef ACS_BLDC_H
#define ACS_BLDC_H

#include "ch.h"
#include "hal.h"

//#define SADDLE
#define SCALE		10/10
#define PERIOD 	360
#define STRETCH 1

#ifdef SADDLE
#undef PERIOD
#undef SCALE		
#define PERIOD 	384
#define SCALE		2/10
#endif

#define sinctrl_t int
//#define sinctrl_t uint32_t // in testing

typedef struct{
	sinctrl_t u,v,w,phase_shift;
	int	sinctrl_size;
	int count;
} BldcConfig;

//*
#define PWM_TIMER_FREQ	100000 // Hz
#define PWM_FREQ				10000// periods per sec
//*/
//#define PWM_PERIOD			100 
#define PWM_PERIOD			PWM_TIMER_FREQ/PWM_FREQ 

#define PWM_U					0U
#define PWM_V					1U
#define PWM_W					2U

extern void bldcInit(void);
extern void bldcStart(void);
extern void bldcStop(void);

extern void bldcSinStart(void);

#endif
