#include "acs_bldc.h"

BldcConfig bldc;

//*
sinctrl_t sinctrl360[] = {
	5000,5087,5174,5262,5349,5436,5523,5609,
	5696,5782,5868,5954,6040,6125,6210,6294,
	6378,6462,6545,6628,6710,6792,6873,6954,
	7034,7113,7192,7270,7347,7424,7500,7575,
	7650,7723,7796,7868,7939,8009,8078,8147,
	8214,8280,8346,8410,8473,8536,8597,8657,
	8716,8774,8830,8886,8940,8993,9045,9096,
	9145,9193,9240,9286,9330,9373,9415,9455,
	9494,9532,9568,9603,9636,9668,9698,9728,
	9755,9782,9806,9830,9851,9872,9891,9908,
	9924,9938,9951,9963,9973,9981,9988,9993,
	9997,9999,10000,9999,9997,9993,9988,9981,
	9973,9963,9951,9938,9924,9908,9891,9872,
	9851,9830,9806,9782,9755,9728,9698,9668,
	9636,9603,9568,9532,9494,9455,9415,9373,
	9330,9286,9240,9193,9145,9096,9045,8993,
	8940,8886,8830,8774,8716,8657,8597,8536,
	8473,8410,8346,8280,8214,8147,8078,8009,
	7939,7868,7796,7723,7650,7575,7500,7424,
	7347,7270,7192,7113,7034,6954,6873,6792,
	6710,6628,6545,6462,6378,6294,6210,6125,
	6040,5954,5868,5782,5696,5609,5523,5436,
	5349,5262,5174,5087,5000,4913,4826,4738,
	4651,4564,4477,4391,4304,4218,4132,4046,
	3960,3875,3790,3706,3622,3538,3455,3372,
	3290,3208,3127,3046,2966,2887,2808,2730,
	2653,2576,2500,2425,2350,2277,2204,2132,
	2061,1991,1922,1853,1786,1720,1654,1590,
	1527,1464,1403,1343,1284,1226,1170,1114,
	1060,1007,955,904,855,807,760,714,
	670,627,585,545,506,468,432,397,
	364,332,302,272,245,218,194,170,
	149,128,109,92,76,62,49,37,
	27,19,12,7,3,1,0,1,
	3,7,12,19,27,37,49,62,
	76,92,109,128,149,170,194,218,
	245,272,302,332,364,397,432,468,
	506,545,585,627,670,714,760,807,
	855,904,955,1007,1060,1114,1170,1226,
	1284,1343,1403,1464,1527,1590,1654,1720,
	1786,1853,1922,1991,2061,2132,2204,2277,
	2350,2425,2500,2576,2653,2730,2808,2887,
	2966,3046,3127,3208,3290,3372,3455,3538,
	3622,3706,3790,3875,3960,4046,4132,4218,
	4304,4391,4477,4564,4651,4738,4826,4913
};
//*/

//*
static sinctrl_t sinctrlSaddle[PERIOD] = {
 127,131,135,138,142,145,149,152,155,159,162,165,168,171,174,177,180,183,186,189,192,194,197,200,
  202,205,207,210, 212,214,217,219,221,223,225,227,229,231,232,234,236,237,239,240,242,243,244,245,
	 247,248,249,250,250,251,252,253,253,254,254,255,255,255,255,255,255,255,255,255,255,255,254,254,
	  253,253,252,252,251,250,249,248,247,246,245,244,242,241,240,238,237,235,233,232,230,228,226,224,
		 222,222,225,226,228,230,232,234,235,237,238,240,241,243,244,245,246,247,248,249,250,251,252,252,
		  253,254,254,254,255,255,255,255,255,255,255,255,255,255,254,254,254,253,252,252,251,250,249,248,
			 247,246,245,244,243,241,240,238,237,235,234,232,230,228,227,225,223,220,218,216,214,212,209,207,
			  204,202,199,197,194,191,188,185,183,180,177,174,171,167,164,161,158,154,151,148,144,141,137,134,
				 130,127,123,119,116,112,108,104,101, 97, 93, 89, 85, 81, 77, 73, 69, 65, 61, 57, 53, 49, 45, 41,
				  36, 32, 28, 24, 20, 16, 12, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
							 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 6, 10, 15, 19, 23, 27, 31,
							  35, 39, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96, 99,103,107,111,115,118,121,124
};
//*/


// pwm period callback
static void pwmpcb(PWMDriver *pwmp) {
  (void)pwmp;
  
  palClearLine(LINE_LED_GREEN);
	
	++bldc.count;
	
	if(bldc.count==STRETCH){
		++bldc.u;
		++bldc.v;
		++bldc.w;

		if(bldc.u >= PERIOD){
			bldc.u = 0;
		}
		if(bldc.v >= PERIOD){
			bldc.v = 0;
		}
		if(bldc.w >= PERIOD){
			bldc.w = 0;
		}

		bldc.count=0;
	}
}

static sinctrl_t scale(sinctrl_t duty_cycle){
	return duty_cycle*SCALE + 10;	
}

static void pwmCallback(uint8_t channel,sinctrl_t step){
  palSetLine(LINE_LED_GREEN);
  pwmEnableChannelI(
		&PWMD1,
		channel,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,scale(sinctrlSaddle[step]))
		//PWM_PERCENTAGE_TO_WIDTH(&PWMD1,scale(sinctrl360[step]))
	);
}

static void pwmUcb(PWMDriver *pwmp){ // channel 1 callback
  (void)pwmp;
	pwmCallback(PWM_U,bldc.u);
}

static void pwmVcb(PWMDriver *pwmp){ // channel 2 callback
  (void)pwmp;
	pwmCallback(PWM_V,bldc.v);
}

static void pwmWcb(PWMDriver *pwmp){ // channel 3 callback
  (void)pwmp;
	pwmCallback(PWM_W,bldc.w);
}

static PWMConfig pwmcfg = {
  PWM_TIMER_FREQ,	
  PWM_PERIOD,	
  pwmpcb,
  {
   {PWM_OUTPUT_ACTIVE_HIGH|PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH,pwmUcb},
   {PWM_OUTPUT_ACTIVE_HIGH|PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH,pwmVcb},
   {PWM_OUTPUT_ACTIVE_HIGH|PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH,pwmWcb},
   {PWM_OUTPUT_ACTIVE_HIGH,NULL}
   //{PWM_OUTPUT_DISABLED, NULL}
  },
  0,
	0,
  0
};


extern void bldcInit(){
	bldc.sinctrl_size = PERIOD;
//	sinctrl_t *psinctrl;
//	psinctrl=sinctrl360;
//	bldc.sinctrl=sinctrl360;
//	sinctrl_t *s;
//	s = sinctrl360;
//	bldc.sinctrl=s;
//	bldc.sinctrl=sinctrl360;
	//bldc.sinctrl_size = sizeof(sinctrl)/sizeof(sinctrl_t);
  bldc.phase_shift = bldc.sinctrl_size/3;
	bldc.count=0;
  bldc.u = 0;
  bldc.v = bldc.u + bldc.phase_shift;
  bldc.w = bldc.v + bldc.phase_shift;

	pwmStart(&PWMD1, &pwmcfg);
  pwmEnablePeriodicNotification(&PWMD1);

//	palSetPadMode(GPIOA, 11, PAL_MODE_ALTERNATE(0));

//*
	pwmEnableChannel(&PWMD1,PWM_U,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,bldc.u));
  pwmEnableChannel(&PWMD1,PWM_V,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,bldc.v));
  pwmEnableChannel(&PWMD1,PWM_W,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,bldc.w));
 // pwmEnableChannel(&PWMD1,PWM_D,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,5000));
//*/

	// enable pwm center aligned mode
	// TODO: This is not working. needs more research
	//
	//PWMD1.tim->CR1 |= STM32_TIM_CR1_CMS(0x01);
	
	pwmEnableChannelNotification(&PWMD1,PWM_U);
  pwmEnableChannelNotification(&PWMD1,PWM_V);
  pwmEnableChannelNotification(&PWMD1,PWM_W);
 // pwmEnableChannelNotification(&PWMD1,PWM_D);
}

extern void bldcStart(){

}

extern void bldcStop(){

}

extern void bldcSinStart(){

}

