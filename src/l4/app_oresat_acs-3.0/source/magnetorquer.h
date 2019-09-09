#ifndef _MAGNETORQUER_H_
#define _MAGNETORQUER_H_

#include "ch.h"
#include "hal.h"
#include "chprintf.h"

#define MTQR_PWM_TIMER_FREQ  	2e6	/// PWM Timer frequency
#define MTQR_PWM_FREQ 				2e3 /// periods per second

#define FORWARD 0
#define REVERSE 1

#define MTQR_PWM_PERIOD MTQR_PWM_TIMER_FREQ/MTQR_PWM_FREQ

#define PWM_CH_MTQR      			0             /// pwm channel
#define MTQR_STARTING_DC			10000u         /// starting duty cycle
//#define MTQR_STARTING_DC			5000u         /// starting duty cycle
#define PH				 						GPIOC_MAG_PH  /// Phase (motor direction)
#define ENABLE    						GPIOC_EN_MAG	/// Chip enable

#define EXIT_SUCCESS 					0
#define EXIT_FAILURE 					1

/**
 * @brief PWMConfig structure for the magnetorquer
 *
 */
static const PWMConfig pwm_MTQRcfg = 
{
	MTQR_PWM_TIMER_FREQ,    /// Frequency
	MTQR_PWM_PERIOD,        /// period duration 
	NULL,               		/// Callback
	{ /// Channels
		{PWM_OUTPUT_ACTIVE_HIGH,NULL},
		{PWM_OUTPUT_DISABLED,NULL},
		{PWM_OUTPUT_DISABLED,NULL},
		{PWM_OUTPUT_DISABLED,NULL}
	},
	0,
	0,
	0
};

/**
 * @brief MTQR structure for keeping state
 * TODO: this structure is not being used effectively
 * it may or may not be a good design choice
 *
 */
typedef struct
{
	uint8_t direction;
	int started;
	uint16_t pwm_dc; /// duty cycle
}MTQR;

extern void mtqrInit(MTQR *mtqr);
extern void mtqrStart(MTQR *mtqr);
extern void mtqrStop(MTQR *mtqr);
extern void mtqrSetDC(uint16_t dc);
extern void mtqrSetDir(uint8_t dc);
extern void mtqrExit(MTQR *mtqr);
	
#endif
