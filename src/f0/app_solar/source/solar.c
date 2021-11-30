#include "solar.h"
#include "ina226.h"
#include "CANopen.h"
#include "chprintf.h"
#include "OD.h"

#define DEBUG_SD                (BaseSequentialStream *) &SD2

#if 0
#define dbgprintf(str, ...)       chprintf((BaseSequentialStream*) &SD2, str, ##__VA_ARGS__)
#else
#define dbgprintf(str, ...)
#endif


#define MAX(x, y) (((x) > (y)) ? (x) : (y))


/* Defines for INA226 */
#define CURR_LSB                20       /* 20uA/bit */
#define RSENSE                  100      /* 0.1 ohm  */
#define DAC_VDDA_UV             3333000  /* 3.333 V. Change to 3.0 v when powered from debug board */

//Assumes 3.3V Vcc
#define DAC_MININUM_ADJUST_UV   805

#define I_ADJ_FAILSAFE          1450000
#define I_ADJ_INITIAL           1500000
#define I_ADJ_MAX               1500000
#define I_ADJ_MIN               0
#define HISTERESIS_MW           3


//1000 is based on the width of the flat at the top of the curve and the minimum adjustable value of the DAC
#define VREF_STEP_IN_MICROVOLTS_NEGATIVE             1000
#define VREF_STEP_IN_MICROVOLTS_POSITIVE             (VREF_STEP_IN_MICROVOLTS_NEGATIVE * 4)
#define DIAG_REPORT_EVERY_N_LOOP_ITERATIONS          1


#if VREF_STEP_IN_MICROVOLTS_NEGATIVE < DAC_MININUM_ADJUST_UV
#error "VREF_STEP_IN_MICROVOLTS_NEGATIVE must be greater then DAC_MININUM_ADJUSG_UV"
#endif

extern const I2CConfig i2cconfig;

/* Based on INA226 datasheet, page 15, Equation (2)
 * CURR_LSB = Max Current / 2^15
 * So, with CURR_LSB = 20 uA/bit, Max current = 655 mA
 *
 * Based on equation (1),
 * CAL = 0.00512 / (CURR_LSB * Rsense)
 * Since CURR_LSB is in uA and Rsense is in mOhm
 * CAL = 0.00512 / (CURR_LSB * Rsense * 10^-9)
 */
#define NUM_INA226_AVG                                 16
#define INA226_ADC_CONVERSION_TIME_MICROSECONDS        1100

static const INA226Config ina226config = {
    &I2CD2,
    &i2cconfig,
    INA226_SADDR,
    INA226_CONFIG_MODE_SHUNT_VBUS | INA226_CONFIG_MODE_CONT |
    INA226_CONFIG_VSHCT_1100US | INA226_CONFIG_VBUSCT_1100US |
    INA226_CONFIG_AVG_16,
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

typedef enum {
	MPPT_ALGORITHM_PAO = 0
} mppt_algorithm_t;


typedef struct {
	uint32_t iadj_uv;
	bool direction_up_flag;
	uint32_t step_size;

	uint32_t avg_power_initial_mW;
	uint32_t avg_voltage_initial_mV;
	uint32_t avg_current_initial_uA;

	uint32_t max_power_initial_mW;
	uint32_t max_voltage_initial_mV;
	uint32_t max_current_initial_uA;

	uint32_t avg_power_perturbed_mW;
	uint32_t avg_voltage_perturbed_mV;
	uint32_t avg_current_perturbed_uA;

	bool hit_step_size_threshold_flag;
} mppt_pao_state;

mppt_pao_state pao_state;


/**
 * @brief control DAC output in microvolts.
 *
 * @param[in] dacp      DAC driver pointer.
 * @param[in] chan      DAC channel.
 * @param[in] uv        output volts in uv (microVolts).
 */
void dac_put_microvolts(DACDriver *dacp, dacchannel_t chan, uint32_t uv) {
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
 * @param[in|out] *dest_avg_power_mW     Output variable into which to store average power reading
 * @param[in|out] *dest_avg_voltage_uV   Output variable into which to store average voltage reading
 * @param[in|out] *dest_avg_current      Output variable into which to store average current reading
 *
 * @return true upon success, false otherwise
 */
bool read_avg_power_and_voltage(uint32_t *dest_avg_power_mW, uint32_t *dest_avg_voltage_mV, uint32_t *dest_avg_current_uA) {
	chThdSleepMilliseconds((NUM_INA226_AVG * INA226_ADC_CONVERSION_TIME_MICROSECONDS) / 1000);//Compensate for the internal averaging done by the ina chip

	bool ret = true;
	if( ina226ReadPower(&ina226dev, dest_avg_power_mW) != MSG_OK ) {
		ret = false;
	}
	if( ina226ReadVBUS(&ina226dev, dest_avg_voltage_mV) != MSG_OK ) {
		ret = false;
	}
	if( ina226ReadCurrent(&ina226dev, dest_avg_current_uA) != MSG_OK ) {
		ret = false;
	}
	if( ! ret ) {
		//CO_errorReport(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_COMMUNICATION, SOLAR_OD_ERROR_TYPE_INA226_COMM_ERROR);
	}

	return(ret);
}

uint32_t saturate_uint32_t(const int64_t v, const uint32_t min, const uint32_t max) {
	if (v > max)
		return (max);
	else if (v < min)
		return (min);

	return (v);
}

/**
 * Determines step size for iAdj based on current voltage. Allows for faster convergence on MPP.
 */
uint32_t get_iadj_step_size(mppt_pao_state *pao_state) {
	if( (! pao_state->hit_step_size_threshold_flag) && pao_state->max_voltage_initial_mV != 0 ) {
		const uint32_t threshold_low_mV = pao_state->max_voltage_initial_mV / 20; //0.95 threshold
		const uint32_t threshold_mV = pao_state->max_voltage_initial_mV - threshold_low_mV;

		if(  pao_state->avg_voltage_initial_mV > threshold_mV ) {
			//Linear scale of step size based on delta from maximum voltage
		    const int32_t v = (((pao_state->avg_voltage_initial_mV - threshold_mV) * 100) / threshold_low_mV);
			const uint32_t step_size = (((5000 - VREF_STEP_IN_MICROVOLTS_NEGATIVE) * v) / 100) + VREF_STEP_IN_MICROVOLTS_NEGATIVE;

			return(step_size);//up or down is fine
		} else {
			pao_state->hit_step_size_threshold_flag = true;
		}
	}

	if( pao_state->direction_up_flag ) {
		return(VREF_STEP_IN_MICROVOLTS_POSITIVE);
	}
	return(VREF_STEP_IN_MICROVOLTS_NEGATIVE);
}

/**
 * @param *pao_state The current state of the perturb and observe algorithm
 *
 * @return true on success, false otherwise
 */
bool itterate_mppt_perturb_and_observe(mppt_pao_state *pao_state) {

	pao_state->step_size = get_iadj_step_size(pao_state);

	uint32_t iadj_uv_perturbed = pao_state->iadj_uv;
	if( pao_state->direction_up_flag ) {
		iadj_uv_perturbed = saturate_uint32_t(((int64_t) pao_state->iadj_uv) + pao_state->step_size, I_ADJ_MIN, I_ADJ_MAX);
	} else {
		iadj_uv_perturbed = saturate_uint32_t(((int64_t) pao_state->iadj_uv) - pao_state->step_size, I_ADJ_MIN, I_ADJ_MAX);
	}

	if( pao_state->iadj_uv == iadj_uv_perturbed ) {
		//It has saturated to an identical value, flip the search direction and process in the next iteration
		pao_state->direction_up_flag = (! pao_state->direction_up_flag);
	} else {
		dac_put_microvolts(&DACD1, 0, iadj_uv_perturbed);

		if( ! read_avg_power_and_voltage(&pao_state->avg_power_perturbed_mW, &pao_state->avg_voltage_perturbed_mV, &pao_state->avg_current_perturbed_uA) ) {
			//I2C communications error, no data to make a decision on. Fail safe to moving left
			pao_state->direction_up_flag = true;

			pao_state->iadj_uv = iadj_uv_perturbed;
			if( pao_state->iadj_uv > I_ADJ_FAILSAFE ) {
				pao_state->iadj_uv = I_ADJ_FAILSAFE;
			}

			//CO_errorReport(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_COMMUNICATION, SOLAR_OD_ERROR_TYPE_PAO_INVALID_DATA);

			return(false);

		} else {
			if( pao_state->avg_power_perturbed_mW >= (pao_state->avg_power_initial_mW - HISTERESIS_MW) ) {
				//Always move the iadj_value, even if the output power is equal. This will cause it to hunt back and forth between two points that have a detectable difference in their power output.
			} else {
				pao_state->direction_up_flag = (! pao_state->direction_up_flag);
			}

			pao_state->iadj_uv = iadj_uv_perturbed;

			pao_state->avg_current_initial_uA = pao_state->avg_current_perturbed_uA;
			pao_state->avg_power_initial_mW = pao_state->avg_power_perturbed_mW;
			pao_state->avg_voltage_initial_mV = pao_state->avg_voltage_perturbed_mV;
		}
	}

	//These values are published to the CANOpen dictionary objects
	pao_state->max_power_initial_mW = MAX(pao_state->max_power_initial_mW, pao_state->avg_power_initial_mW);
	pao_state->max_voltage_initial_mV = MAX(pao_state->max_voltage_initial_mV, pao_state->avg_voltage_initial_mV);
	pao_state->max_current_initial_uA = MAX(pao_state->max_current_initial_uA, pao_state->avg_current_initial_uA);

	return(true);
}


/* Main solar management thread */
THD_WORKING_AREA(solar_wa, 0x400);
THD_FUNCTION(solar, arg)
{
    (void)arg;

    chprintf(DEBUG_SD, "\r\nRunning solar app...\r\n");
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

    memset(&pao_state, 0, sizeof(pao_state));
    pao_state.iadj_uv = I_ADJ_INITIAL;

    palSetLine(LINE_LT1618_EN);

#if 0
	//Generate CSV output to terminal for plotting in libreoffice
	for(int iadj = 1500000; iadj >= 0; iadj -= 1000 ) {
		dac_put_microvolts(&DACD1, 0, iadj);

		if( ! read_avg_power_and_voltage(&pao_state.avg_power_initial_mW, &pao_state.avg_voltage_initial_mV, &pao_state.avg_current_initial_uA) ) {
			//FIXME handle error
		}
		dbgprintf("iadj_uV,%u,avg_power_initial_mW,%u,avg_voltage_initial_mV,%u,avg_current_initial_uA,%d\r\n",
				iadj, pao_state.avg_power_initial_mW, pao_state.avg_voltage_initial_mV, pao_state.avg_current_initial_uA);
	}
	for(;;) {

	}
#endif

	dac_put_microvolts(&DACD1, 0, pao_state.iadj_uv);

	chprintf(DEBUG_SD, "Done with init INA226, running main loop....\r\n");
    systime_t loop_start_time_ms = TIME_I2MS(chVTGetSystemTime());

	for (uint32_t loop_iteration = 0; !chThdShouldTerminateX(); loop_iteration++) {
        if ((loop_iteration % DIAG_REPORT_EVERY_N_LOOP_ITERATIONS) == 0) {
			dbgprintf("loop,%u,iadj_uv,%u,direction_up_flag,%u,avg_power_initial_mW,%u,avg_voltage_initial_mV,%u,avg_current_initial_uA,%d,step_size,%u,avg_freq,%u\r\n",
					loop_iteration, pao_state.iadj_uv,
					pao_state.direction_up_flag,
					pao_state.avg_power_initial_mW,
					pao_state.avg_voltage_initial_mV,
					pao_state.avg_current_initial_uA,
					pao_state.step_size,
					((loop_iteration / ((TIME_I2MS(chVTGetSystemTime()) - loop_start_time_ms) / 1000))));
        }

    	itterate_mppt_perturb_and_observe(&pao_state);

    	OD_RAM.x6000_PV_Power.voltage = pao_state.avg_voltage_initial_mV;
    	OD_RAM.x6000_PV_Power.voltageAvg = pao_state.avg_voltage_initial_mV;
    	OD_RAM.x6000_PV_Power.current = pao_state.avg_current_initial_uA / 1000;
    	OD_RAM.x6000_PV_Power.currentAvg = pao_state.avg_current_initial_uA / 1000;
    	OD_RAM.x6000_PV_Power.power = pao_state.avg_power_initial_mW;
    	OD_RAM.x6000_PV_Power.powerAvg = pao_state.avg_power_initial_mW;

    	OD_RAM.x6000_PV_Power.voltageMax = pao_state.max_voltage_initial_mV;
    	OD_RAM.x6000_PV_Power.currentMax = pao_state.max_current_initial_uA / 1000;
    	OD_RAM.x6000_PV_Power.powerMax = pao_state.max_power_initial_mW;
    	OD_RAM.x6000_PV_Power.energy = 0;//TODO Accumulate power output from INA226 and track mAh


    	OD_RAM.x6002_MPPT.LT1618_IADJ = pao_state.iadj_uv / 1000;

		//Only PAO implemented for the time being
		OD_RAM.x6002_MPPT.algorithm = MPPT_ALGORITHM_PAO;

    }

    /* Stop drivers */
    dacStop(&DACD1);
    ina226Stop(&ina226dev);

    /* Stop LT1618 */
    palClearLine(LINE_LT1618_EN);

    chThdExit(MSG_OK);
}
