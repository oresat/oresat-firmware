#include "acs_bldc.h"

int sinctrl[] = {
	4980,5068,5155,5242,5329,5416,5503,5590,5676,5763,5849,5934,6020,6105,6190,6274,
	6359,6442,6525,6608,6690,6772,6853,6934,7014,7093,7172,7250,7328,7404,7480,7556,
	7630,7704,7776,7848,7919,7989,8059,8127,8194,8261,8326,8390,8454,8516,8577,8637,
	8696,8754,8811,8866,8920,8974,9025,9076,9126,9174,9221,9266,9311,9353,9395,9435,
	9474,9512,9548,9583,9616,9648,9679,9708,9736,9762,9787,9810,9832,9852,9871,9889,
	9904,9919,9932,9943,9953,9961,9968,9974,9977,9980,9980,9980,9977,9974,9968,9961,
	9953,9943,9932,9919,9904,9889,9871,9852,9832,9810,9787,9762,9736,9708,9679,9648,
	9616,9583,9548,9512,9474,9435,9395,9353,9311,9266,9221,9174,9126,9076,9025,8974,
	8920,8866,8811,8754,8696,8637,8577,8516,8454,8390,8326,8261,8194,8127,8059,7989,
	7919,7848,7776,7704,7630,7556,7480,7404,7328,7250,7172,7093,7014,6934,6853,6772,
	6690,6608,6525,6442,6359,6274,6190,6105,6020,5934,5849,5763,5676,5590,5503,5416,
	5329,5242,5155,5068,4980,4893,4806,4719,4632,4545,4458,4371,4285,4198,4112,4026,
	3941,3856,3771,3686,3602,3519,3435,3353,3270,3189,3107,3027,2947,2867,2789,2710,
	2633,2556,2480,2405,2331,2257,2184,2113,2041,1971,1902,1834,1766,1700,1635,1570,
	1507,1445,1384,1324,1265,1207,1150,1095,1040,987,935,885,835,787,740,695,650,
	607,566,525,486,449,413,378,344,312,282,253,225,199,174,151,129,109,90,72,56,
	42,29,18,8,0,0,0,0,0,0,0,0,0,0,0,8,18,29,42,56,72,90,109,129,151,174,199,225,
	253,282,312,344,378,413,449,486,525,566,607,650,695,740,787,835,885,935,987,1040,
	1095,1150,1207,1265,1324,1384,1445,1507,1570,1635,1700,1766,1834,1902,1971,2041,
	2113,2184,2257,2331,2405,2480,2556,2633,2710,2789,2867,2947,3027,3107,3189,3270,
	3353,3435,3519,3602,3686,3771,3856,3941,4026,4112,4198,4285,4371,4458,4545,4632,
	4719,4806,4893,4980
};

BldcConfig bldc;

// pwm period callback
static void pwmpcb(PWMDriver *pwmp) {
  (void)pwmp;
  
  palClearLine(LINE_LED_GREEN);

//	if(bldc.count==0){
		++bldc.u;
		++bldc.v;
		++bldc.w;

		if(bldc.u >= 360){
			bldc.u = 0;
		}
		if(bldc.v >= 360){
			bldc.v = 0;
		}
		if(bldc.w >= 360){
			bldc.w = 0;
		}
		bldc.count=0;
//	}
//	++bldc.count;
}

int scale(int duty_cycle){
	return duty_cycle;//*5/10+2000;	
}

static void pwmc1cb(PWMDriver *pwmp){ // channel 1 callback
  (void)pwmp;
  palSetLine(LINE_LED_GREEN);
  pwmEnableChannelI(
		&PWMD1,
		PWM_CH1,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,scale(sinctrl[bldc.u]))
	);
}

static void pwmc2cb(PWMDriver *pwmp){ // channel 2 callback
  (void)pwmp;
 	palSetLine(LINE_LED_GREEN);
  pwmEnableChannelI(
		&PWMD1,
		PWM_CH2,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,scale(sinctrl[bldc.v]))
	);
}

static void pwmc3cb(PWMDriver *pwmp){ // channel 3 callback
  (void)pwmp;
  palSetLine(LINE_LED_GREEN);
  pwmEnableChannelI(
		&PWMD1,
		PWM_CH3,
		PWM_PERCENTAGE_TO_WIDTH(&PWMD1,scale(sinctrl[bldc.w]))
	);
}

static PWMConfig pwmcfg = {
  PWM_TIMER_FREQ,	
  PWM_PERIOD,	
  pwmpcb,
  {
   {PWM_OUTPUT_ACTIVE_HIGH|PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH,pwmc1cb},
   {PWM_OUTPUT_ACTIVE_HIGH|PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH,pwmc2cb},
   {PWM_OUTPUT_ACTIVE_HIGH|PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH,pwmc3cb},
   {PWM_OUTPUT_DISABLED, NULL}
  },
  0,
	0,
  0
};

extern void bldcInit(){
	bldc.sinctrl_size = sizeof(sinctrl)/sizeof(int);
  bldc.phase_shift = bldc.sinctrl_size/3;
  bldc.u = 0;
  bldc.v = bldc.u + bldc.phase_shift;
  bldc.w = bldc.v + bldc.phase_shift;
	bldc.count=0;

	pwmStart(&PWMD1, &pwmcfg);
  pwmEnablePeriodicNotification(&PWMD1);

	palSetPadMode(GPIOPort, ACH1, PAL_MODE_ALTERNATE(1));
	palSetPadMode(GPIOPort, ACH2, PAL_MODE_ALTERNATE(1));
	palSetPadMode(GPIOPort, ACH3, PAL_MODE_ALTERNATE(1));

	palSetPadMode(GPIOComp, BCH1, PAL_MODE_ALTERNATE(1));
	palSetPadMode(GPIOComp, BCH2, PAL_MODE_ALTERNATE(1));
	palSetPadMode(GPIOComp, BCH3, PAL_MODE_ALTERNATE(1));


//*
	pwmEnableChannel(&PWMD1,PWM_CH1,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,bldc.u));
  pwmEnableChannel(&PWMD1,PWM_CH2,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,bldc.v));
  pwmEnableChannel(&PWMD1,PWM_CH3,PWM_PERCENTAGE_TO_WIDTH(&PWMD1,bldc.w));
//*/

	// enable pwm center aligned mode
//	PWMD1.tim->CR1 |= STM32_TIM_CR1_CMS(0x01);

	pwmEnableChannelNotification(&PWMD1,PWM_CH1);
  pwmEnableChannelNotification(&PWMD1,PWM_CH2);
  pwmEnableChannelNotification(&PWMD1,PWM_CH3);
}

extern void bldcStart(){

}

extern void bldcStop(){

}

extern void bldcSinStart(){

}

