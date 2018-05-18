#include "magnetorquer.h"

extern void mtqrInit(MTQR *mtqr){
	(void)mtqr;
	palSetPadMode(GPIOB,PH,PAL_MODE_OUTPUT_PUSHPULL); // Phase direction
  palSetPadMode(GPIOB,ENABLE,PAL_MODE_OUTPUT_PUSHPULL); 
	palClearPad(GPIOB,ENABLE); /// logic low	
	palClearPad(GPIOB,PH); /// phase direction 
}

extern void mtqrStart(){
	pwmStart(&PWMD1,&pwm_MTQRcfg);
	palSetPad(GPIOB,ENABLE);        // Set Enable high.
	mtqrSetDC(MTQR_STARTING_DC);
/*
	pwmEnableChannel(
		&PWMD1,
		PWM_CH_MTQR,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,MTQR_STARTING_DC)
	);
//*/
}

extern void mtqrStop(){
 	pwmDisableChannel(&PWMD1,PWM_CH_MTQR);
	palClearPad(GPIOB,ENABLE);
	palClearPad(GPIOB,PH);
	pwmStop(&PWMD1);
}

extern void mtqrSetDC(uint16_t dc){
	pwmEnableChannel(
		&PWMD1,
		PWM_CH_MTQR,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,dc)
	);
}

extern void mtqrExit(){
	mtqrStop();
}


