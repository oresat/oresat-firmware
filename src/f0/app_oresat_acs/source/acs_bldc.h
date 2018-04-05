#ifndef _ACS_BLDC_H_
#define _ACS_BLDC_H_

#include "ch.h"
#include "hal.h"
#include "acs.h"

#define SCALE		9
#define PERIOD 	360
#define STRETCH 100

#define PWM_TIMER_FREQ	48e6 // Hz
#define PWM_FREQ				30e3 // periods per sec
#define PWM_PERIOD			PWM_TIMER_FREQ/PWM_FREQ 

#define PWM_U					0U
#define PWM_V					1U
#define PWM_W					2U

//#define sinctrl_t int
#define sinctrl_t uint16_t // in testing

//extern const sinctrl_t sinctrl360[360];

typedef struct{
	int count,		// period counter
			scale,		// scales the duty cycle
			period,		// steps in lut TODO: rname this
			stretch;  
	sinctrl_t u,v,w,
						phase_shift;
	
	sinctrl_t const	*sinctrl;
} BldcConfig;

extern void bldcInit(void);
extern void bldcStart(void);
extern void bldcStop(void);

extern void bldcSinStart(void);

extern THD_WORKING_AREA(wa_bldcThread,THREAD_SIZE);
extern THD_FUNCTION(bldcThread,arg);

#endif
