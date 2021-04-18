#include "solar.h"
#include "ina226.h"
#include "CANopen.h"
#include "chprintf.h"

#define DEBUG_SD                  (BaseSequentialStream *) &SD2

#define PAO_VERSION_3

//FIXME I beleive MAX() is defined in some common C library???
#define MAX(x, y) (((x) > (y)) ? (x) : (y))


/* Defines for INA226 */
#define CURR_LSB                20       /* 20uA/bit */
#define RSENSE                  100      /* 0.1 ohm  */
#define DAC_VDDA_UV             3333000  /* 3.333 V. Change to 3.0 v when powered from debug board */


/* Defines for MPPT algorithm that changes with each solar cell variant
 * Things to note
 * Negative step size needs to be greater as the curve falls quickly.
 * Make sure to account for noise. Lower value will cause curve to crash. Higher value will not let the system reach its potential.
 */
#ifdef PAO_VERSION_1
#define MIN_DP_DI               0        /* The most important piece. This keeps the point to the left of MPP. */
#define NVE_STEP_SIZE           3500     /* Fixed -ve step size */
#define CURR_THRES_SENS         0        /* Current Threshold Sensitivity. Reduces sensitivity to noise in current. */
#define MAX_STEP_SIZE           10000    /* Maximum step size for variable step IC. */
#define STEP_SIZE_FACTOR        2000     /* Posive step factor. */
#define NVE_STEP_SIZE_FACTOR    4        /* Negative step factor. This is multipled with Positive step factor */
#define MIN_PV_CURRENT          0        /* Minimum current drawn from PV cells */
#define MAX_PV_CURRENT          500000   /* Maximum current drawn from PV cells */
#define MIN_PV_POWER            50000    /* Minimum power drawn from PV cells */
#endif


#define INA226_MEASUREMENT_CONVERSION_TIME_MS        2
#define I_ADJ_INITIAL           1500000
#define I_ADJ_MAX               1600000
#define I_ADJ_MIN               0


// Used in Perturb And Observe (PAO) algorithm:
//#define VREF_STEP_IN_MICROVOLTS_POSITIVE             20
//#define VREF_STEP_IN_MICROVOLTS_POSITIVE             10000
#define VREF_STEP_IN_MICROVOLTS_POSITIVE             5000
//#define VREF_STEP_IN_MICROVOLTS_POSITIVE             1000

#define VREF_STEP_IN_MICROVOLTS_NEGATIVE             VREF_STEP_IN_MICROVOLTS_POSITIVE
#define DIAG_REPORT_EVERY_N_LOOP_ITERATIONS          1
#define SMALLEST_UW_MEASUREMENT_UNIT                 50
//#define TOTAL_NUMBER_OF_STEPS                        ((I_ADJ_MAX - I_ADJ_MIN) / VREF_STEP_IN_MICROVOLTS_POSITIVE)


/* Based on INA226 datasheet, page 15, Equation (2)
 * CURR_LSB = Max Current / 2^15
 * So, with CURR_LSB = 20 uA/bit, Max current = 655 mA
 *
 * Based on equation (1),
 * CAL = 0.00512 / (CURR_LSB * Rsense)
 * Since CURR_LSB is in uA and Rsense is in mOhm
 * CAL = 0.00512 / (CURR_LSB * Rsense * 10^-9)
 */
#define NUM_INA226_AVG      512

static const INA226Config ina226config = {
    &I2CD2,
    &i2cconfig,
    INA226_SADDR,
    INA226_CONFIG_MODE_SHUNT_VBUS | INA226_CONFIG_MODE_CONT |
    INA226_CONFIG_VSHCT_140US | INA226_CONFIG_VBUSCT_140US |
    INA226_CONFIG_AVG_512,
    (5120000/(RSENSE * CURR_LSB)),
    CURR_LSB
};

/* DAC1 configuration */
static const DACConfig dac1cfg = {
    .init         = 1861U,                /* Initialize DAC to 1.5V (1500*4096)/3300 */
    .datamode     = DAC_DHRM_12BIT_RIGHT, /* 12 bit, right aligned */
    .cr           = 0                     /* No control reg options */
};

static INA226Driver ina226dev;

typedef struct {
	uint32_t iadj_uv;
	bool direction_up_flag;

	uint32_t avg_power_initial_uW;
	uint32_t avg_voltage_initial_uV;
	uint32_t avg_current_initial;

	uint32_t max_power_initial_uW;
	uint32_t max_voltage_initial_uV;
	uint32_t max_current_initial;

	uint32_t avg_power_perterbed_uW;
	uint32_t avg_voltage_perterbed_uV;
	uint32_t avg_current_perterbed;

} mppt_pao_state;


/**
 * @brief control DAC output in microvolts.
 *
 * @param[in] dacp      DAC driver pointer.
 * @param[in] chan      DAC channel.
 * @param[in] uv        output volts in uv (microVolts).
 */
void dacPutMicrovolts(DACDriver *dacp, dacchannel_t chan, uint32_t uv) {
    /* Per section 14.5.3 of the STM32F0x1 ref manual,
     * Vout(mV) = VDDA(mV) * (reg_val / 4096)
     * so, reg_val = (Vout * 4096) / VDDA
     */
    dacsample_t val = ((uv/100) << 12) / (DAC_VDDA_UV/100);
    dacPutChannelX(dacp, chan, val);
}

/**
 * @brief Reads power flow characteristics from the INA226
 *
 * @param[in|out] *dest_avg_power_uW     Output variable into which to store average power reading
 * @param[in|out] *dest_avg_voltage_uV   Output variable into which to store average voltage reading
 * @param[in|out] *dest_avg_current      Output variable into which to store average current reading
 *
 * @return true upon success, false otherwise
 */
bool read_avg_power_and_voltage(uint32_t *dest_avg_power_uW, uint32_t *dest_avg_voltage_uV, uint32_t *dest_avg_current) {
	const uint32_t num_to_average = 1;
	uint64_t power_sum = 0;
	uint64_t voltage_sum = 0;
	int64_t current_sum;

	const uint32_t ina266_measurement_conversion_time_us = 1100;
	chThdSleepMilliseconds((NUM_INA226_AVG * ina266_measurement_conversion_time_us) / 1000);//Compensate for the internal averaging done by the ina chip

	for(uint32_t i = 0; i < num_to_average; i++ ) {
		chThdSleepMilliseconds(INA226_MEASUREMENT_CONVERSION_TIME_MS);
		//FIXME refactor ina226ReadPower and ina226ReadVBUS to return errors if/when i2c comm issues happen
		power_sum += ina226ReadPower(&ina226dev);  /* Power in increments of uW */
		voltage_sum += ina226ReadVBUS(&ina226dev); /* VBUS voltage in uV */
		current_sum += ina226ReadCurrent(&ina226dev);
	}

	*dest_avg_power_uW = power_sum / num_to_average;
	*dest_avg_current = current_sum / num_to_average;
	*dest_avg_voltage_uV = voltage_sum / num_to_average;

	//Remove some of the noise
	*dest_avg_power_uW -= ((*dest_avg_power_uW) % (SMALLEST_UW_MEASUREMENT_UNIT * 2));

	return(true);
}

uint32_t saturate_uint32_t(const int64_t v, const uint32_t min, const uint32_t max) {
	if (v > max)
		return (max);
	else if (v < min)
		return (min);

	return (v);
}



/**
 * @param *pao_state The current state of the perturb and observe algorithm
 *
 * @return true on success, false otherwise
 */
bool itterate_mppt_perturb_and_observe(mppt_pao_state *pao_state) {
	if( ! read_avg_power_and_voltage(&pao_state->avg_power_initial_uW, &pao_state->avg_voltage_initial_uV, &pao_state->avg_current_initial) ) {
		//FIXME handle error
	}

	pao_state->max_power_initial_uW = MAX(pao_state->max_power_initial_uW, pao_state->avg_power_initial_uW);
	pao_state->max_voltage_initial_uV = MAX(pao_state->max_voltage_initial_uV, pao_state->avg_voltage_initial_uV);
	pao_state->max_current_initial = MAX(pao_state->max_current_initial, pao_state->avg_current_initial);


	//FIXME consider step size being too small to actually perturb the read back. This implementation would get stuck and fail to converge on the proper value
	uint32_t iadj_uv_perterbed = pao_state->iadj_uv;
	if( pao_state->direction_up_flag ) {
		iadj_uv_perterbed = saturate_uint32_t(((int64_t) pao_state->iadj_uv) + VREF_STEP_IN_MICROVOLTS_POSITIVE, I_ADJ_MIN, I_ADJ_MAX);
	} else {
		iadj_uv_perterbed = saturate_uint32_t(((int64_t) pao_state->iadj_uv) - VREF_STEP_IN_MICROVOLTS_NEGATIVE, I_ADJ_MIN, I_ADJ_MAX);
	}

	if( pao_state->iadj_uv == iadj_uv_perterbed ) {
		//It has saturated, flip the search direction
		pao_state->direction_up_flag = (! pao_state->direction_up_flag);
	} else {
		dacPutMicrovolts(&DACD1, 0, iadj_uv_perterbed);

		if( ! read_avg_power_and_voltage(&pao_state->avg_power_perterbed_uW, &pao_state->avg_voltage_perterbed_uV, &pao_state->avg_current_perterbed) ) {
			//FIXME handle error
		}

		const int32_t histeresis_uW = 4000;

		if( pao_state->avg_power_perterbed_uW >= (pao_state->avg_power_initial_uW - histeresis_uW) ) {
			//Always move the iadj_value, even if the output power is equal. This will cause it to hunt back and forth between two points that have a detectable difference in their power output.
			pao_state->iadj_uv = iadj_uv_perterbed;
		} else {
			pao_state->direction_up_flag = (! pao_state->direction_up_flag);
			dacPutMicrovolts(&DACD1, 0, pao_state->iadj_uv);
		}
	}

	return(true);
}


/* Main solar management thread */
THD_WORKING_AREA(solar_wa, 0x400);
THD_FUNCTION(solar, arg)
{
    (void)arg;
    /* Start up drivers */
    ina226ObjectInit(&ina226dev);
    chprintf(DEBUG_SD, "Initializing DAC....\r\n");
    dacStart(&DACD1, &dac1cfg);

    chprintf(DEBUG_SD, "Initializing INA226....\r\n");
    ina226Start(&ina226dev, &ina226config);

    if( ina226dev.state != INA226_READY ) {
    	chprintf(DEBUG_SD, "Failed to initialize INA226!!!\r\n");
    	chThdSleepMilliseconds(100);
    }


	mppt_pao_state pao_state;
    memset(&pao_state, 0, sizeof(pao_state));
    pao_state.iadj_uv = I_ADJ_INITIAL;

    palSetLine(LINE_LT1618_EN);

#if 0
	chprintf(DEBUG_SD, "Inducing brown out...\r\n");
	chThdSleepMilliseconds(1000);

	dacPutMicrovolts(&DACD1, 0, 1000000);
	while(1) {
		chprintf(DEBUG_SD, "Waiting for brown out...\r\n");
		chThdSleepMilliseconds(200);
	}
#endif

#if 0
	for(int iadj = 1500000; iadj >= 0; iadj -= 100 ) {
		dacPutMicrovolts(&DACD1, 0, iadj);

		if( ! read_avg_power_and_voltage(&pao_state.avg_power_initial_uW, &pao_state.avg_voltage_initial_uV, &pao_state.avg_current_initial) ) {
			//FIXME handle error
		}
		chprintf(DEBUG_SD, "iadj_uV,%u,avg_power_initial_uW,%u,avg_voltage_initial_uV,%u,avg_current_initial,%d\r\n",
				iadj, pao_state.avg_power_initial_uW, pao_state.avg_voltage_initial_uV, pao_state.avg_current_initial);
	}
	for(;;) {

	}
#endif

	dacPutMicrovolts(&DACD1, 0, pao_state.iadj_uv);

    if( ! read_avg_power_and_voltage(&pao_state.avg_power_initial_uW, &pao_state.avg_voltage_initial_uV, &pao_state.avg_current_initial) ) {
		//FIXME handle error
	}

    //chprintf(DEBUG_SD, "Done with init INA226....\r\n");
    systime_t loop_start_time_ms = TIME_I2MS(chVTGetSystemTime());

	for (uint32_t loop_iteration = 0; !chThdShouldTerminateX(); loop_iteration++) {
        if ((loop_iteration % DIAG_REPORT_EVERY_N_LOOP_ITERATIONS) == 0) {
        	const uint32_t avg_freq = (loop_iteration / ((TIME_I2MS(chVTGetSystemTime()) - loop_start_time_ms) / 1000));

			chprintf(DEBUG_SD, "loop %u: iadj_uv = %u, direction_up_flag = %u, avg_power_initial_uW = %u, avg_voltage_initial_uV = %u, avg_current_initial = %d, avg_freq = %u\r\n",
					loop_iteration, pao_state.iadj_uv,
					pao_state.direction_up_flag,
					pao_state.avg_power_initial_uW,
					pao_state.avg_voltage_initial_uV,
					pao_state.avg_current_initial,
					avg_freq);
        }

    	itterate_mppt_perturb_and_observe(&pao_state);

    	OD_PV_Power.voltage = pao_state.avg_voltage_initial_uV;
    	OD_PV_Power.voltageAvg = pao_state.avg_voltage_initial_uV;
    	OD_PV_Power.current = pao_state.avg_current_initial;
    	OD_PV_Power.currentAvg = pao_state.avg_current_initial;
    	OD_PV_Power.power = pao_state.avg_power_initial_uW;
    	OD_PV_Power.powerAvg = pao_state.avg_power_initial_uW;

    	OD_PV_Power.voltageMax = pao_state.max_voltage_initial_uV;
    	OD_PV_Power.currentMax = pao_state.max_current_initial;
    	OD_PV_Power.powerAvg = pao_state.max_power_initial_uW;
    	OD_PV_Power.energy = 0;

    } // end while thread should run loop

    /* Stop drivers */
    dacStop(&DACD1);
    ina226Stop(&ina226dev);

    /* Stop LT1618 */
    palClearLine(LINE_LT1618_EN);

    chThdExit(MSG_OK);
}

