#include "magnetorquer.h"

extern void mtqrInit(MTQR *mtqr){
	(void)mtqr;
//	palSetPad(GPIOB,PH);    // Phase selection (direction of motor).
	palSetPadMode(GPIOB,PH,PAL_MODE_OUTPUT_PUSHPULL); // Phase direction
  palSetPadMode(GPIOB,ENABLE,PAL_MODE_OUTPUT_PUSHPULL); 
	palClearPad(GPIOB,ENABLE);	
	palClearPad(GPIOB,PH);
}

extern void mtqrStart(){
	pwmStart(&PWMD1,&pwm_MTQRcfg);
	palSetPad(GPIOB,ENABLE);        // Set Enable high.
	palSetPad(GPIOB,PH);
	pwmEnableChannel(
		&PWMD1,
		PWM_CH_MTQR,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,10000)
	);
/*
	while(true){
		palSetPad(GPIOB,DIRECTION);    // Phase selection (direction of motor).
		pwmEnableChannel(
			&PWMD1,
			PWM_CH_MTQR,
			PWM_PERCENTAGE_TO_WIDTH(&PWMD1,4000)
		);

		chThdSleepMilliseconds(5000);
		pwmDisableChannel(&PWMD1,PWM_CH_MTQR);

		palClearPad(GPIOB,DIRECTION);    // Phase selection (direction of motor).
		pwmEnableChannel(
			&PWMD1,
			PWM_CH_MTQR,
			PWM_PERCENTAGE_TO_WIDTH(&PWMD1,8000)
		);

		chThdSleepMilliseconds(5000);
		pwmDisableChannel(&PWMD1,PWM_CH_MTQR);
	}
//*/
}

extern void mtqrStop(){
 	pwmDisableChannel(&PWMD1,PWM_CH_MTQR);
	palClearPad(GPIOB,ENABLE);
	palClearPad(GPIOB,PH);
	pwmStop(&PWMD1);
}

extern void mtqrExit(){
	mtqrStop();
}


