#include "magnetorquer.h"

/**
 * @brief Magnetorquer initialization function.
 *
 * This function will initialize the driver state to off.
 *
 */
extern void mtqrInit(MTQR *mtqr)
{
	(void)mtqr;
	mtqr->started = FALSE;          // Initializing state of magnetorquer driver.
	palClearPad(GPIOC,ENABLE);      // Initializing motor driver state to off.
}

/**
 * @brief Magnetorquer start function.
 *
 * This function will start the PWM driver and enable
 * the STSPIN250 motor driver while providing a 
 * starting duty cycle. At this point, the state of 
 * the magnetorquer will be set to true to indicate on
 * state.
 *
 */
extern void mtqrStart(MTQR *mtqr)
{
	if(mtqr->started) // Checking if state is already on.
  {              
		return;
	}
	pwmStart(&PWMD3,&pwm_MTQRcfg);  // Starting pwm driver.
	mtqrSetDC(MTQR_STARTING_DC);    // Setting duty cycle of output.
	palSetPad(GPIOC,ENABLE);        // Turning on motor driver.
	mtqr->started	= TRUE;         	// Setting to on state.
}

/**
 * @brief Magnetorquer stop function.
 *
 * This function will disable the active
 * PWM driver and disable the STSPIN250 motor
 * driver. 
 *
 */
extern void mtqrStop(MTQR *mtqr)
{
	if(!mtqr->started)// Checking if state is already off.
  {     
		return;
	}
 	pwmDisableChannel(&PWMD3,PWM_CH_MTQR);  // Disabling channel output.
	palClearPad(GPIOC,ENABLE);              // Shutting off STSPIN250 driver.
	pwmStop(&PWMD3);                        // Stopping PWM driver.
	mtqr->started	= FALSE;                	// Changing state to off.
}

/**
 * @brief Magnetorquer set duty cycle function.
 *
 * This function takes a 16 bit value as parameter and 
 * sets the duty cycle of the magnetorquer driver using the 
 * paramater. 
 *
 */
extern void mtqrSetDC(uint16_t dc)
{
	pwmEnableChannel(                       // Setting duty cycle output using paramater.
		&PWMD3,
		PWM_CH_MTQR,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD3,dc)
	);
}

/**
 * @brief Magnetorquer set direction function. 
 *
 * This function sets the phase pin for the STSPIN250
 * motor driver. The phase is set based on the value
 * of the paramater given to the function.
 *
 */
extern void mtqrSetDir(uint8_t dc)
{
	if(dc==FORWARD)// Set phase selection pin based on requested direction.
  {                	
		palClearPad(GPIOC,PH); 
	}
  else if(dc==REVERSE)
  {
		palSetPad(GPIOC,PH);  
	}
}

/**
 * @brief Magnetorquer exit function.
 *
 * Function to initialize shutdown of driver.
 *
 */
extern void mtqrExit(MTQR *mtqr)
{
	if(!mtqr->started)// Checking if magnetorquer state is off.
  {     	
		return;
	}
	mtqrStop(mtqr);         // If the state isn't already off, shut down the driver.
}


