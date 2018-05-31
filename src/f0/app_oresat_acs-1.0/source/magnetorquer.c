#include "magnetorquer.h"

extern void mtqrInit(MTQR *mtqr){
	(void)mtqr;
	mtqr->started = FALSE;
	palSetPadMode(GPIOB,PH,PAL_MODE_OUTPUT_PUSHPULL); // Phase direction
	palClearPad(GPIOB,PH); /// phase direction 
/*
  palSetPadMode(GPIOB,ENABLE,PAL_MODE_OUTPUT_PUSHPULL); 
	palClearPad(GPIOB,ENABLE); /// logic high	
//*/
//*
  palSetPadMode(GPIOA,ENABLE,PAL_MODE_OUTPUT_PUSHPULL); 
	palClearPad(GPIOA,ENABLE); /// logic low	
//*/
}

extern void mtqrStart(MTQR *mtqr){
	if(mtqr->started){
		return;
	}
	pwmStart(&PWMD1,&pwm_MTQRcfg);
	mtqrSetDC(MTQR_STARTING_DC);
//	palSetPad(GPIOB,ENABLE);        // Set Enable high.
	palSetPad(GPIOA,ENABLE);        // Set Enable high.
	mtqr->started	= TRUE;
}

extern void mtqrStop(MTQR *mtqr){
	if(!mtqr->started){
		return;
	}
 	pwmDisableChannel(&PWMD1,PWM_CH_MTQR);
	palClearPad(GPIOA,ENABLE);
//	palClearPad(GPIOB,ENABLE);
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


