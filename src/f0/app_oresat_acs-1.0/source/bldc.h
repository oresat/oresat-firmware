#ifndef _BLDC_H_
#define _BLDC_H_

#include "ch.h"
#include "hal.h"

#include <unistd.h>

/// TODO: openloop is going away
#define OPENLOOP /// open loop control (oxymoron)

//#define THREAD_SIZE	(1<<7)
/// TODO had to reduce this to compile with new ADC code
/// We should figure out what an actual good value is
#define THREAD_SIZE	(96)

/// serial debugging
#define DEBUG_SERIAL SD2
#define DEBUG_CHP ((BaseSequentialStream *) &DEBUG_SERIAL)


/**
 * TODO: the definitions of STEP, STRETCH, and SKIP
 * evolved over the course of various experiments. These
 * will completely change in v2.0. Below is their intended and
 * eventual meanings.
 *
 * STEPS: the number of discrete steps in the LUT
 *
 * STRETCH: How many periods the current LUT value is repeated
 *
 * SKIP: How many steps are skipped in the LUT to get the next value
 *
 * SMOOTH: Smoothing out the transition between LUT values by increasing the amount of steps in between 
 *
 * SCALE: Duty cycle scaling factor from 0-100 %
 *
 */
#define SCALE			100
#define STEPS			360 
#define STRETCH		1
#define SKIP      1

/// encoder has 14 bits of precision
#define ENCODER_MAX 1<<14
/// chunk amount is the number of times through
/// the LUT for 1 revolution of the reaction wheel
#define CHUNK_AMOUNT 6
/// chunk size is the number
#define CHUNK_SIZE 2730

#define PWM_TIMER_FREQ	48e6 /// Hz
#define PWM_FREQ				15e3 /// periods per sec
#define PWM_PERIOD			PWM_TIMER_FREQ/PWM_FREQ 

/// PWM signals
#define PWM_U			0U
#define PWM_V			1U
#define PWM_W			2U

#define ADC_GRP_NUM_CHANNELS  1
#define ADC_GRP_BUF_DEPTH     8 

#define sinctrl_t uint16_t 

/**
 * @brief The structure that defines and characterizes
 * a motor and how it's being control
 *
 * steps: Steps in the LUT
 *
 * stretch: How many steps are added in between LUT steps
 *
 * skip: How many steps are skipped in the LUT
 *
 * u, v, and w: The three sin signals, that traverse through the LUT
 * current_sin_u,v,w and next_sin_u,v,w: Used in calculation of values for stretch
 *
 * sin_diff: Difference in LUT steps for stretch
 *
 * position: Position from encode, a value of 0 - 2^14
 *
 * openLoop: Controls whether encoder feedback is used
 *
 * sinctrl: The LUT
 *
 * spi_rxbuff: Where the encoder position is after SPI transmission
 *
 * p_spi_thread: Spi thread for the encoder feedback
 *
 * samples: Samples from the ADC.
 *
 */
typedef struct{
	uint16_t count,		/// period counter
					 scale,		/// scales the duty cycle
					 steps,		/// number of steps in lut 
					 stretch,
					 skip;  
	sinctrl_t u,v,w,/// signals
						phase_shift;		/// should be by 120 degrees 
  uint16_t current_sin_u, next_sin_u,
           current_sin_v, next_sin_v,
           current_sin_w, next_sin_w;
  uint8_t stretch_count;
  uint8_t sin_diff;
	uint16_t position;				// motor position from encoder
  bool openLoop;
					 sinctrl_t const *sinctrl; // pointer to the sin lut
	uint16_t spi_rxbuf[2]; // receive buffer
	thread_t *p_spi_thread;
  adcsample_t samples[ADC_GRP_NUM_CHANNELS * ADC_GRP_BUF_DEPTH]; // ADC conversion storage array
	int started;
} bldc;

/**
 * @brief The low value used to break up the encoder value into regions
 *
 * Allows us to translate the encoder 0 - 2^14 into 6 discrete chunks
 * of 0-360 for use in the LUT.
 *
 */
static const uint16_t chunk_low[6] = {
	0 * CHUNK_SIZE,
	1 * CHUNK_SIZE,
	2 * CHUNK_SIZE,
	3 * CHUNK_SIZE,
	4 * CHUNK_SIZE,
	5 * CHUNK_SIZE
};


/**
 * @brief Control structure used to configure the SPI driver
 *
 * GPIOA_SPI1_NSS is the pin used to initially select the SPI slave.
 * The mask for SPI Control Register 1 sets the frequency of data transfers
 * and sets the clock polarity.
 * The mask for SPI control Register 2 sets the size of the transfer buffer, 16 bits.
 *
 */
static const SPIConfig spicfg = {
	false,                                                  // Not using circular buffer.
	NULL,                                                   // Not using operation complete callback.
	GPIOA,                                                  // Chip select line.
	GPIOA_SPI1_NSS,                                         // Chip select port.
	SPI_CR1_BR_0|SPI_CR1_BR_1|SPI_CR1_BR_2|SPI_CR1_CPHA,    // SPI Control Register 1 mask.
	SPI_CR2_DS_0|SPI_CR2_DS_1|SPI_CR2_DS_2|SPI_CR2_DS_3,    // SPI Control Register 2 mask.
};

extern THD_WORKING_AREA(wa_spiThread,THREAD_SIZE);
/// Prototype for spi thread function.
extern THD_FUNCTION(spiThread,arg);

/// Function prototype with no return type. Takes bldc type as paramater.
extern void bldcInit(bldc *pbldc);
/// Function prototype with no return type. Takes bldc type as paramater.
extern void bldcStart(bldc *pbldc);
/// Function prototype with no return type. Takes bldc type as paramater.
extern void bldcStop(bldc *pbldc);
/// Function prototype with no return type. Takes 8 bit unsigned integer and a 
/// 16 bit unsigned integer as argument.
extern void bldcSetDC(uint8_t channel,uint16_t dc);
/// Function prototype with no return type. Takes bldc type as paramater.
extern void bldcExit(bldc *pbldc);

#endif
