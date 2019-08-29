#ifndef ACS_BLDC_H
#define ACS_BLDC_H

#include "ch.h"
#include "hal.h"
//#include "acs_sinlut.h"

#define SCALE		9
#define PERIOD 	360
#define STRETCH 1

#define sinctrl_t int
//#define sinctrl_t uint32_t // in testing

typedef struct{
	sinctrl_t u,v,w,phase_shift;
	int	sinctrl_size;
	int count;
	int scale;
	int period;
	int stretch;
	sinctrl_t *sinctrl;
} BldcConfig;

//*
#define PWM_TIMER_FREQ	48e6 // Hz
#define PWM_FREQ				30000// periods per sec
//*/

#define PWM_PERIOD			PWM_TIMER_FREQ/PWM_FREQ 

#define PWM_U					0U
#define PWM_V					1U
#define PWM_W					2U
#define PWM_D 				3U

extern void bldcInit(void);
extern void bldcStart(void);
extern void bldcStop(void);

extern void bldcSinStart(void);

#endif
