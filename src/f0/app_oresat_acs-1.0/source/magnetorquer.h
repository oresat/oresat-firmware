#ifndef _MAGNETORQUER_H_
#define _MAGNETORQUER_H_

#include "ch.h"
#include "hal.h"
#include "chprintf.h"

#define MTQR_PWM_TIMER_FREQ  	2e6     // PWM Timer frequency
#define MTQR_PWM_FREQ 		2e3     // periods per second

#define FORWARD 0       
#define REVERSE 1

#define MTQR_PWM_PERIOD MTQR_PWM_TIMER_FREQ/MTQR_PWM_FREQ

#define PWM_CH_MTQR      	0       // pwm channel
#define MTQR_STARTING_DC	5000	// starting duty cycle
#define PH			9u	// Phase (motor direction)
#define ENABLE    		GPIOB_EN_MAG	// Chip enable for motor driver.

#define EXIT_SUCCESS 					0
#define EXIT_FAILURE 					1

/**
 *
 *
 *
 */
static const PWMConfig pwm_MTQRcfg = {
	MTQR_PWM_TIMER_FREQ,                    // Frequency
	MTQR_PWM_PERIOD,                        // period duration 
	NULL,               		        // Callback
	{                                       // Channels
		{PWM_OUTPUT_ACTIVE_HIGH,NULL},  // Using only one channel for the magnetorquer PWM driver.
		{PWM_OUTPUT_DISABLED,NULL},
		{PWM_OUTPUT_DISABLED,NULL},
		{PWM_OUTPUT_DISABLED,NULL}
	},
	0,
	0,
	0
};

/**
 *
 *
 *
 */
typedef struct{
	uint8_t direction;      // Holds current direction of driver.
	int started;            // Holds current state of driver.
	uint16_t pwm_dc;        // Holds current duty cycle.
}MTQR;

// Function prototype with MTQR paramater.
extern void mtqrInit(MTQR *mtqr);
// Function prototype with MTQR paramater.
extern void mtqrStart(MTQR *mtqr);
// Function prototype with MTQR paramater.
extern void mtqrStop(MTQR *mtqr);
// Function prototype with 16 bit unsigned integer as paramater.
extern void mtqrSetDC(uint16_t dc);
// Function prototype with 8 bit unsigned integer as paramater.
extern void mtqrSetDir(uint8_t dc);
// Function prototype with MTQR paramater.
extern void mtqrExit(MTQR *mtqr);
	
#endif
