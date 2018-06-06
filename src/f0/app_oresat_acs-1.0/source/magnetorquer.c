#include "magnetorquer.h"

extern void mtqrInit(MTQR *mtqr){
	(void)mtqr;
	mtqr->started = FALSE;
//*
//  palSetPadMode(GPIOA,PH,PAL_MODE_OUTPUT_PUSHPULL); 
	palClearPad(GPIOB,ENABLE); /// for rev3
  //palSetPadMode(GPIOA,PH,PAL_MODE_OUTPUT_PUSHPULL); 
//	palClearPad(GPIOA,PH);
//*/
}

extern void mtqrStart(MTQR *mtqr){
	if(mtqr->started){
		return;
	}
//	palSetPadMode(GPIOA,PH,PAL_MODE_ALTERNATE(0));
//	palClearPad(GPIOA,PH);
	pwmStart(&PWMD1,&pwm_MTQRcfg);
	mtqrSetDC(MTQR_STARTING_DC);
	palSetPad(GPIOB,ENABLE);        // Set Enable high.
	mtqr->started	= TRUE;
}

extern void mtqrStop(MTQR *mtqr){
	if(!mtqr->started){
		return;
	}
 	pwmDisableChannel(&PWMD1,PWM_CH_MTQR);
	palClearPad(GPIOB,ENABLE);
	//palClearPad(GPIOA,PH);
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

extern void mtqrSetDir(uint8_t dc){
	if(dc==FORWARD){	
		palClearPad(GPIOA,PH); /// phase direction 
	}else if(dc==REVERSE){
		palSetPad(GPIOA,PH); /// phase direction 
	}
}

extern void mtqrExit(MTQR *mtqr){
	if(!mtqr->started){	
		return;
	}
//	palSetPadMode(GPIOA,PH,PAL_MODE_ALTERNATE(2));
 // palSetPadMode(GPIOA,PH,PAL_MODE_OUTPUT); 
	mtqrStop(mtqr);
}


