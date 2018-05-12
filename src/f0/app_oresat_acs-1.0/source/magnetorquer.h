#ifndef _MAGNETORQUER_H_
#define _MAGNETORQUER_H_

#include "ch.h"
#include "hal.h"
#include "chprintf.h"

#define MTQR_PWM_TIMER_FREQ  	2e6
#define MTQR_PWM_FREQ 				2e3  // periods per second

#define MTQR_PWM_PERIOD MTQR_PWM_TIMER_FREQ/MTQR_PWM_FREQ

#define PWM_CH_MTQR      			0    // pwm channel

#define PH				 						6u
#define ENABLE    						7u

#define EXIT_SUCCESS 					0
#define EXIT_FAILURE 					1

static const PWMConfig pwm_MTQRcfg = {
	MTQR_PWM_TIMER_FREQ,     // Frequency
	MTQR_PWM_PERIOD,         // period duration 
	NULL,               // Callback
	{                   // Channels
		{PWM_OUTPUT_ACTIVE_HIGH,NULL},
		{PWM_OUTPUT_DISABLED,NULL},
		{PWM_OUTPUT_DISABLED,NULL},
		{PWM_OUTPUT_DISABLED,NULL}
	},
	0,
	0,
	0
};

typedef struct{
	uint8_t direction;
}MTQR;

extern void mtqrInit(MTQR *mtqr);
extern void mtqrStart(void);
extern void mtqrStop(void);
extern void mtqrExit(void);
	
#endif
