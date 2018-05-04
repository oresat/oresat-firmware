#ifndef _ACS_H_
#define _ACS_H_

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "string.h"

#define OPENLOOP

#define CH_DBG_SYSTEM_STATE_CHECK TRUE

#define THREAD_SIZE	(1<<7) 
#define CAN_NODE 0x3F // max 0x7f
#define CAN_BUF 8

#define DEBUG_SERIAL SD2
#define DEBUG_CHP ((BaseSequentialStream *) &DEBUG_SERIAL)

#define SCALE			9
#define STEPS			360 
#define STRETCH		1

#define PWM_TIMER_FREQ	48e6 // Hz

#define PWM_FREQ				15e3 // periods per sec
#define PWM_PERIOD			PWM_TIMER_FREQ/PWM_FREQ 

#define PWM_U					0U
#define PWM_V					1U
#define PWM_W					2U
#define PWM_MTQR			3u

#define sinctrl_t uint16_t 

typedef struct{
	uint8_t send[CAN_BUF];
	uint8_t recv[CAN_BUF];
} ACSdata;

typedef struct{
	int count,		// period counter
			scale,		// scales the duty cycle
			steps,		// number of steps in lut 
			stretch;  
	sinctrl_t u,v,w,					// signals
						phase_shift;		// 
  uint16_t position;				// motor position from encoder
	sinctrl_t const *sinctrl; // pointer to the sin lut
	ACSdata *data;
} BldcConfig;

static const SPIConfig spicfg = {
	false,              // Enables circular buffer if == 1
	NULL,               // Operation complete call back.
	GPIOA,              // Chip select line
	GPIOA_SPI1_NSS,     // Chip select port
	SPI_CR1_BR_0|SPI_CR1_BR_1|SPI_CR1_BR_2|SPI_CR1_CPHA,//reg 1 mask
	SPI_CR2_DS_0|SPI_CR2_DS_1|SPI_CR2_DS_2|SPI_CR2_DS_3,//reg 2 mask
};

typedef struct{
	// o_0
}ACSConfig;

extern THD_WORKING_AREA(wa_acsThread,THREAD_SIZE);
extern THD_FUNCTION(acsThread,arg);

extern THD_WORKING_AREA(wa_spiThread,THREAD_SIZE);
extern THD_FUNCTION(spiThread,arg);

extern void acsInit(ACSdata *data);
extern void bldcInit(void);
extern void bldcStart(void);
extern void bldcStop(void);

#endif
