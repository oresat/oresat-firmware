#include "magnetorquer.h"

extern void mtqrInit(MTQR *mtqr){
	(void)mtqr;
	mtqr->started = FALSE;
	palSetPadMode(GPIOB,PH,PAL_MODE_OUTPUT_PUSHPULL); // Phase direction
  palSetPadMode(GPIOA,ENABLE,PAL_MODE_OUTPUT_PUSHPULL); 
	palClearPad(GPIOA,ENABLE); /// logic low	
	//palSetPad(GPIOA,ENABLE); /// logic high	
	palClearPad(GPIOB,PH); /// phase direction 
}

extern void mtqrStart(MTQR *mtqr){
	if(mtqr->started){
		return;
	}
	pwmStart(&PWMD1,&pwm_MTQRcfg);
	//palSetPad(GPIOB,ENABLE);        // Set Enable high.
	palSetPad(GPIOA,ENABLE);        // Set Enable high.
	mtqrSetDC(MTQR_STARTING_DC);
	mtqr->started	= TRUE;
/*
	pwmEnableChannel(
		&PWMD1,
		PWM_CH_MTQR,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,MTQR_STARTING_DC)
	);
//*/
}

extern void mtqrStop(MTQR *mtqr){
 	pwmDisableChannel(&PWMD1,PWM_CH_MTQR);
	palClearPad(GPIOA,ENABLE);
	//palClearPad(GPIOB,ENABLE);
	palClearPad(GPIOB,PH);
	pwmStop(&PWMD1);
	mtqr->started	= FALSE;
}

extern void mtqrSetDC(uint16_t dc){
	pwmEnableChannel(
		&PWMD1,
		PWM_CH_MTQR,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,dc)
	);
}

extern void mtqrExit(MTQR *mtqr){
	if(!mtqr->started){	
		return;
	}
	mtqrStop(mtqr);
}


