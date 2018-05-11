#ifndef _ACS_H_
#define _ACS_H_

#include "ch.h"
#include "hal.h"
#include "chprintf.h"

//#define BRUTEFORCE
//#define CONFIGURE

#define CH_DBG_SYSTEM_STATE_CHECK TRUE

#define THREAD_SIZE	(120) 
#define CAN_NODE 0x3F // max 0x7f

#define DEBUG_SERIAL SD2
#define DEBUG_CHP ((BaseSequentialStream *) &DEBUG_SERIAL)

#define SCALE			2
#define STEPS			360 
#define STRETCH	  1
#define STEP_SIZE 1
#define SKIP      1

#define COIL_NUM 6

#define ENCODER_MAX 2^14
#define ENCODER_MIN 0
#define ENCODER_CHUNK_SIZE 2730

#define PWM_TIMER_FREQ	48e6 // Hz

//**************************************************************
//
// TODO: we need to do math ASAP
//
#define PWM_FREQ				20e3 // periods per sec
//#define PWM_FREQ				30e3 // periods per sec
#define PWM_PERIOD			PWM_TIMER_FREQ/PWM_FREQ 
//**************************************************************

#define PWM_U					0U
#define PWM_V					1U
#define PWM_W					2U

#define sinctrl_t uint16_t 

#define ADC_GRP_NUM_CHANNELS   1
#define ADC_GRP_BUF_DEPTH      8

typedef struct{
	int count,		// period counter
			scale,		// scales the duty cycle
			steps,		// number of steps in lut 
			stretch;  
	sinctrl_t u,v,w,					// signals
						phase_shift;		// 
  uint16_t position;				// motor position from encoder
	sinctrl_t const *sinctrl; // pointer to the sin lut
   adcsample_t samples[ADC_GRP_NUM_CHANNELS * ADC_GRP_BUF_DEPTH]; // ADC conversion storage array

} BldcConfig;

static const SPIConfig spicfg = {
	false,              // Enables circular buffer if == 1
	NULL,               // Operation complete call back.
	GPIOA,              // Chip select line
	GPIOA_SPI1_NSS,     // Chip select port
	SPI_CR1_BR_0|SPI_CR1_CPHA,//reg 1 mask
	SPI_CR2_DS_0|SPI_CR2_DS_1|SPI_CR2_DS_2|SPI_CR2_DS_3,//reg 2 mask
};

typedef struct{
	// o_0
}ACSConfig;

typedef struct{
	uint8_t acs[8];
} ACSdata;

extern THD_WORKING_AREA(wa_acsThread,THREAD_SIZE);
extern THD_FUNCTION(acsThread,arg);

extern THD_WORKING_AREA(wa_spiThread,THREAD_SIZE);
extern THD_FUNCTION(spiThread,arg);

extern THD_WORKING_AREA(wa_debugThread,THREAD_SIZE);
extern THD_FUNCTION(debugThread,arg);



extern void acsInit(void);
extern void bldcInit(void);
extern void bldcStart(void);
extern void bldcStop(void);

#endif
