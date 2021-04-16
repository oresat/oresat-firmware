#include "solar.h"
#include "ina226.h"
#include "CANopen.h"
#include "chprintf.h"

#define DEBUG_SD                  (BaseSequentialStream *) &SD2

// #define PAO_VERSION_1
//#define PAO_VERSION_2
#define PAO_VERSION_3


/* Defines for INA226 */
#define CURR_LSB                20       /* 20uA/bit */
#define RSENSE                  100      /* 0.1 ohm  */
#define DAC_VDDA_UV             3333000  /* 3.333 V. Change to 3.0 v when powered from debug board */


#ifdef PAO_VERSION_2
#define READINGS_RING_BUFFER_SIZE (10)
#define AVERAGES_RING_BUFFER_SIZE (10)
/* Defines for MPPT algorithm iteration speed */
#define SLEEP_MS                2
#define DEBUG_ITERATIONS        500
#define DIAG_REPORT_EVERY_N_LOOP_ITERATIONS          800
#endif

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
//1600000 indicates zero current, 0 indicates no current limit
//FIXME what should I_ADJ_MIN be
#define I_ADJ_MAX               1600000
#define I_ADJ_MIN               (I_ADJ_MAX / 10)



// Used in Perturb And Observe (PAO) algorithm:
//#define VREF_STEP_IN_MICROVOLTS_POSITIVE             20
#define VREF_STEP_IN_MICROVOLTS_POSITIVE             ((I_ADJ_MAX - I_ADJ_MIN) / 200)
#define VREF_STEP_IN_MICROVOLTS_NEGATIVE             VREF_STEP_IN_MICROVOLTS_POSITIVE
#define DIAG_REPORT_EVERY_N_LOOP_ITERATIONS          1
#define SMALLEST_UW_MEASUREMENT_UNIT                 50




/* Based on INA226 datasheet, page 15, Equation (2)
 * CURR_LSB = Max Current / 2^15
 * So, with CURR_LSB = 20 uA/bit, Max current = 655 mA
 *
 * Based on equation (1),
 * CAL = 0.00512 / (CURR_LSB * Rsense)
 * Since CURR_LSB is in uA and Rsense is in mOhm
 * CAL = 0.00512 / (CURR_LSB * Rsense * 10^-9)
 */
static const INA226Config ina226config = {
    &I2CD2,
    &i2cconfig,
    INA226_SADDR,
    INA226_CONFIG_MODE_SHUNT_VBUS | INA226_CONFIG_MODE_CONT |
    INA226_CONFIG_VSHCT_140US | INA226_CONFIG_VBUSCT_140US |
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


#ifdef PAO_VERSION_3

typedef struct {
	uint32_t iadj_uv;
	bool direction_up_flag;

	uint32_t avg_power_initial_uW;
	uint32_t avg_voltage_initial_uV;

	uint32_t avg_power_perterbed_uW;
	uint32_t avg_voltage_perterbed_uV;
} mppt_pao_state;

bool read_avg_power_and_voltage(uint32_t *dest_avg_power_uW, uint32_t *dest_avg_voltage_uV) {
	const uint32_t num_to_average = 10;
	uint64_t power_sum = 0;
	uint64_t voltage_sum = 0;

	for(uint32_t i = 0; i < num_to_average; i++ ) {
		chThdSleepMilliseconds(INA226_MEASUREMENT_CONVERSION_TIME_MS);
		//FIXME refactor ina226ReadPower and ina226ReadVBUS to return errors if/when i2c comm issues happen
		power_sum += ina226ReadPower(&ina226dev);  /* Power in increments of uW */
		voltage_sum += ina226ReadVBUS(&ina226dev); /* VBUS voltage in uV */
	}

	*dest_avg_power_uW = power_sum / num_to_average;
	*dest_avg_voltage_uV = voltage_sum / num_to_average;

	//Remove some of the noise
	*dest_avg_power_uW -= ((*dest_avg_power_uW) % (SMALLEST_UW_MEASUREMENT_UNIT * 4));

	return(true);
}

uint32_t saturate_uint32_t(const uint32_t v, const uint32_t min, const uint32_t max) {
	if (v > max)
		return (max);
	else if (v < min)
		return (min);

	return (v);
}

bool itterate_mppt_perturb_and_observe(mppt_pao_state *pao_state) {
	if( ! read_avg_power_and_voltage(&pao_state->avg_power_initial_uW, &pao_state->avg_voltage_initial_uV) ) {
		//FIXME handle error
	}

	//FIXME consider step size being too small to actually perturbe the read back. This implementation would get stuck and fail to converge on the proper value
	uint32_t iadj_uv_perterbed = pao_state->iadj_uv;
	if( pao_state->direction_up_flag ) {
		iadj_uv_perterbed = saturate_uint32_t(pao_state->iadj_uv + VREF_STEP_IN_MICROVOLTS_POSITIVE, I_ADJ_MIN, I_ADJ_MAX);
	} else {
		iadj_uv_perterbed = saturate_uint32_t(pao_state->iadj_uv - VREF_STEP_IN_MICROVOLTS_NEGATIVE, I_ADJ_MIN, I_ADJ_MAX);
	}

	if( pao_state->iadj_uv == iadj_uv_perterbed ) {
		//It has saturated, flip the search direction
		pao_state->direction_up_flag = (! pao_state->direction_up_flag);
	} else {
		dacPutMicrovolts(&DACD1, 0, iadj_uv_perterbed);

		if( ! read_avg_power_and_voltage(&pao_state->avg_power_perterbed_uW, &pao_state->avg_voltage_perterbed_uV) ) {
			//FIXME handle error
		}

		if( pao_state->avg_power_perterbed_uW >= pao_state->avg_power_initial_uW ) {
			//Always move the iadj_value, even if the output power is equal. This will cause it to hunt back and forth between two points that have a detectable difference in their power output.
			pao_state->iadj_uv = iadj_uv_perterbed;
		} else {
			pao_state->direction_up_flag = (! pao_state->direction_up_flag);
			dacPutMicrovolts(&DACD1, 0, pao_state->iadj_uv);
		}
	}


	return(true);
}

#endif


#if 0
/**
 * @brief Calculates Iadj_v required for a particular max current for LT1618
 *
 * @param[in] i_out     Current in uA.
 *
 * @return              Iadj_v value in microvolts.
 */
uint32_t calc_iadj(uint32_t i_out)
{
    /* Per page 7 of LT1618 datasheet
     * V_Isense = (1.263 - 0.8* v_iadj)/25
     * => 25 * i_out * Rsense  = 1.263 - 0.8 * V_iadj
     * Multiplying 4000 on both sides
     * 100000 * i_out * Rsense = 5052 - 3200 * V_iadj
     * Now i_out is in uA, Rsense is in mOhm and V_iadj is in uV
     * => 100000 * i_out/1000000 * Rsense/1000 = 5052 - 3200 * V_iadj/1000000
     * => 100 * i_out * Rsense = 5052000000 - 3200 * V_iadj
     * => i_out * Rsense = 50520000 - 32 * V_iadj
     * => V_adj = (5052000 - i_out * Rsense * 100)/3200
     */
    return ((50520000 - i_out * RSENSE) / 32);
}

/**
 * @brief Maximum power point tracking algorithm for Solar cells
 *
 * @param[in] volt      Solar cell bus voltage in uV.
 * @param[in] curr      Solar cell current in uA.
 * @param[in] pwr       Power output from solar cells in microWatts.
 *
 * @return              Maximum current to be drawn from solar cells in uA
 * TODO: Find min/max limits of step size. Also check the units that work the best
 *       Average a few samples to reduce noise
 *       reduce max current limit immediatly if current is lower that the allowed current.(brownout condition)
 *       increase max current limit immediatly if voltage is higher that expected.(shutdown condition)
 */
int32_t calc_mppt(uint32_t volt, int32_t curr, uint32_t pwr)
{
    /* The values from the previous iteration of the loop */
    static uint32_t prev_volt = 0;
    static int32_t prev_curr = 0;
    static uint32_t prev_pwr = 0;

    /* Programmed max allowed current from current and previous iteration */
    static int32_t i_in;
    static int32_t prev_i_in;

    int32_t delta_v = volt - prev_volt;
    int32_t delta_i = curr - prev_curr;
    int32_t delta_p = pwr  - prev_pwr;

    int32_t dp_di;
    int32_t step_size;

    /* Start VSIC MPPT Algorithm */
    /* Handles sudden decrease in illumination */
    if ((curr < (8 * i_in)/10) && (pwr < MIN_PV_POWER)) {
        i_in = (8*curr)/10;
        if (i_in < MIN_PV_CURRENT) {
            i_in = MIN_PV_CURRENT;
        }
        return i_in;
    }

    /* Handles sudden decrease in load*/
    if (curr > (12 * i_in)/10)  {
        i_in = curr;
        return i_in;
    }

    /* Variable Step IC MPPT Algorithm */
    if ((prev_i_in-i_in) == 0 && (delta_p < 0 || delta_i <0 || delta_v<0)) {
        /* Decrease current if power/current decreases without being specified.
         * Closed loop control.
         */
        prev_i_in = i_in;
        i_in -= NVE_STEP_SIZE;
    } else {
        prev_i_in = i_in;
        if (delta_i > CURR_THRES_SENS || delta_i < -CURR_THRES_SENS) {
            dp_di = (delta_p*1000)/delta_i;
            step_size = (dp_di * STEP_SIZE_FACTOR)/(volt/1000);

            if (dp_di > MIN_DP_DI) {
                if(step_size > MAX_STEP_SIZE) {
                    i_in += MAX_STEP_SIZE;
                }else{
                    i_in += step_size;
                }
            } else {
                i_in -= NVE_STEP_SIZE;
                if (dp_di < 0) {
                    if(step_size < (-1)*MAX_STEP_SIZE) {
                        i_in -= MAX_STEP_SIZE;
                    }else{
                        i_in += NVE_STEP_SIZE_FACTOR*step_size;
                    }
                }
            }
        }
    }
    /* End VSIC MPPT Algorithm */

    prev_volt = volt;
    prev_curr = curr;
    prev_pwr  = pwr;

    /* Bounds checks for current and power*/
    if (i_in > MAX_PV_CURRENT) {
        i_in = MAX_PV_CURRENT;
    }
    if (pwr < MIN_PV_POWER) {
      i_in += MAX_STEP_SIZE;
    }
    return i_in;
}
#endif


#ifdef PAO_VERSION_2
uint32_t average_of_n_readings(uint32_t readings[], uint32_t count_of_readings)
{
    uint32_t i = 0;
    uint32_t sum = 0;

    for (i = 0; i < count_of_readings; i++) {
        sum += readings[i];
    }
    return (sum / count_of_readings);
}



uint32_t adjust_vref(const int32_t delta_power_uW, const int32_t delta_voltage, uint32_t iadj_uv) {
	if (delta_power_uW == 0) {
		// make no change
	} else {
		if (delta_power_uW > 0) {
			if (delta_voltage > 0) {
				// chprintf(DEBUG_SD, "pos delta power, pos delta voltage - iadj ^^^\r\n");
				// increase vref
				iadj_uv += VREF_STEP_IN_MICROVOLTS;
			} else {
				// chprintf(DEBUG_SD, "pos delta power, neg delta voltage - iadj vvv,\r\n");
				// decrease vref
				iadj_uv -= VREF_STEP_IN_MICROVOLTS;
			}
		} else {
			if (delta_voltage > 0) {
				// chprintf(DEBUG_SD, "neg delta power, pos delta voltage - iadj vvv\r\n");
				// decrease vref
				iadj_uv -= VREF_STEP_IN_MICROVOLTS;
			} else {
				// chprintf(DEBUG_SD, "neg delta power, neg delta voltage - iadj ^^^\r\n");
				// increase vref
				iadj_uv += VREF_STEP_IN_MICROVOLTS;
			}
		}
	}

	// Bound current adjusting voltage to 1.6V per solar board schematic:
	if (iadj_uv > 1600000) {
		iadj_uv = 1600000;
	}

	dacPutMicrovolts(&DACD1, 0, iadj_uv);

	return iadj_uv;
}
#endif


/* Main solar management thread */
THD_WORKING_AREA(solar_wa, 0x400);
THD_FUNCTION(solar, arg)
{
    (void)arg;
#ifdef PAO_VERSION_2
    uint32_t loop_iteration = 0;
    uint32_t power_reading_index = 0;
    int32_t delta_power = 0;
    int32_t delta_voltage = 0;
#endif

#ifdef PAO_VERSION_1
    uint32_t power_previous_read = 0;
    uint32_t voltage_previous_read = 0;
#endif

#ifdef PAO_VERSION_2
    uint32_t power_reading_sub_[READINGS_RING_BUFFER_SIZE] = {0};
//    uint32_t delta_power_sub_[READINGS_RING_BUFFER_SIZE] = {0};
    uint32_t voltage_reading_sub_[READINGS_RING_BUFFER_SIZE] = {0};
//    uint32_t delta_voltage_sub_[READINGS_RING_BUFFER_SIZE] = {0};
    uint32_t average_power_sub_[AVERAGES_RING_BUFFER_SIZE] = {0};
    uint32_t average_voltage_sub_[AVERAGES_RING_BUFFER_SIZE] = {0};

    memset (power_reading_sub_, 0, sizeof(power_reading_sub_));
//    memset (delta_power_sub_, 0, sizeof(delta_power_sub_);
    memset (voltage_reading_sub_, 0, sizeof(voltage_reading_sub_));
//    memset (delta_voltage_sub_, 0, sizeof(delta_voltage_sub_);
    memset (average_power_sub_, 0, sizeof(average_power_sub_));
    memset (average_voltage_sub_, 0, sizeof(average_voltage_sub_));

    uint8_t reading_sets_taken = 0;  // allows us to skip a test on first loop iteration

    uint32_t avg_pwr_idx = 0;  // index to averaged power values
    uint32_t running_count_average_powers_stored = 0;

    uint32_t average_power_present = 0;
    uint32_t average_voltage_present = 0;

    uint32_t highest_power_reading = 0;
    uint32_t highest_power_control_voltage = 0;
    uint32_t highest_average_power_reading = 0;

    uint32_t iadj_uv = 1500000;
#endif 


#ifdef PAO_VERSION_3
	mppt_pao_state pao_state;
    memset(&pao_state, 0, sizeof(pao_state));
    pao_state.iadj_uv = I_ADJ_INITIAL;
#endif

    /* Start up drivers */
    ina226ObjectInit(&ina226dev);
    chprintf(DEBUG_SD, "Initializing DAC....\r\n");
    dacStart(&DACD1, &dac1cfg);
    chprintf(DEBUG_SD, "Initializing INA226....\r\n");
    ina226Start(&ina226dev, &ina226config);
    chprintf(DEBUG_SD, "Done with init....\r\n");

    /* Start up LT1618 */
    palSetLine(LINE_LT1618_EN);

	for (uint32_t loop_iteration = 0; !chThdShouldTerminateX(); loop_iteration++) {
#ifdef PAO_VERSION_3
    	itterate_mppt_perturb_and_observe(&pao_state);
    	chThdSleepMilliseconds(50);
#endif

#if 0
        chThdSleepMilliseconds(SLEEP_MS);

        /* Get present values */
        voltage = ina226ReadVBUS(&ina226dev);    /* VBUS voltage in uV */
        current = ina226ReadCurrent(&ina226dev); /* Current in uA */
        power   = ina226ReadPower(&ina226dev);   /* Power in increments of uW */

        /* Set OD entries to raw values */
        OD_PV_Power.voltage = ina226ReadRaw(&ina226dev, INA226_AD_VBUS);
        OD_PV_Power.current = (int16_t)ina226ReadRaw(&ina226dev, INA226_AD_CURRENT);
        OD_PV_Power.power   = ina226ReadRaw(&ina226dev, INA226_AD_POWER);

        /* Calculate max input current drawn from solar cells.
         * This is used to calculate iadj.
         */
        i_in = calc_mppt(voltage, current, power);
        iadj_uv = calc_iadj(i_in);
        dacPutMicrovolts(&DACD1, 0, iadj_uv);
        if ((++i % 200) == 0){
          chprintf(DEBUG_SD, "Iteration: %d, Volt: %d uv, Current: %d uA, Power: %d uW, \r\n", i, voltage, current, power);
          chprintf(DEBUG_SD, "Input curr: %d ua, Bias Volt: %d uv, \r\n", i_in, iadj_uv);
        }
#else

#ifdef PAO_VERSION_2
        const uint32_t power = ina226ReadPower(&ina226dev);  /* Power in increments of uW */
        const uint32_t voltage = ina226ReadVBUS(&ina226dev); /* VBUS voltage in uV */
#endif

// Perturb and Observe algorithm draft 1:
#ifdef PAO_VERSION_1
        delta_power = (power - power_previous_read);
        delta_voltage = (voltage - voltage_previous_read);

        if ( delta_power == 0 ) {
            // make no change
        }
        else
        {
            if ( delta_power > 0 )
            {
                if ( delta_voltage > 0 )
                {
                    // increase vref
                    iadj_uv += VREF_STEP_IN_MICROVOLTS;
                }
                else
                {
                    // decrease vref
                    iadj_uv -= VREF_STEP_IN_MICROVOLTS;
                }
            }
            else
            {
                if ( delta_voltage > 0 )
                {
                    // decrease vref
                    iadj_uv -= VREF_STEP_IN_MICROVOLTS;
                }
                else
                {
                    // increase vref
                    iadj_uv += VREF_STEP_IN_MICROVOLTS;
                }
            }
        }

        dacPutMicrovolts(&DACD1, 0, iadj_uv);

        voltage_previous_read = voltage;
        power_previous_read = power;
        loop_iteration++;
#endif // end if compiling PAO first draft implementation

#ifdef PAO_VERSION_2
// We've just read power and voltage of the solar circuit from the INA226 part,
// so let's store those readings:

        power_reading_sub_[power_reading_index] = power;
        voltage_reading_sub_[power_reading_index] = voltage;
        power_reading_index++;
        loop_iteration++;

// Track maximum power observed, to use in case power drops a lot suddenly (see note 2 below):
//        chprintf(DEBUG_SD, "power = %u uV, highest power = %u uV\r\n",
//          power, highest_power_reading);
        if ( power > highest_power_reading ) {
            highest_power_reading = power;
            highest_power_control_voltage = iadj_uv;
        }

        if ( power_reading_index > READINGS_RING_BUFFER_SIZE ) {
            power_reading_index = 0;
// find average power of latest n readings:
            average_power_present = average_of_n_readings(power_reading_sub_, READINGS_RING_BUFFER_SIZE); 
            average_power_sub_[avg_pwr_idx] = average_power_present;

            average_voltage_present = average_of_n_readings(voltage_reading_sub_, READINGS_RING_BUFFER_SIZE);
            average_voltage_sub_[avg_pwr_idx] = average_voltage_present;

// (2) We may instead prefer to track highest averaged power from given set of n power readings:
            if ( average_power_present > highest_average_power_reading ) {
                highest_average_power_reading = average_power_present;
                chprintf(DEBUG_SD, "latest averaged power = %u uV, highest averaged power = %u uV\r\n",
                  average_power_present, highest_average_power_reading);
            }

            avg_pwr_idx++;
            running_count_average_powers_stored++;
            if ( avg_pwr_idx > AVERAGES_RING_BUFFER_SIZE ) {
                avg_pwr_idx = 0;
//                chprintf(DEBUG_SD, "average power ring buffer just wrapped around to zero,\r\n");
            }

// - STEP - determine change in power
// If we have only one set of power readings, skip the normal tests comparing past and present
// average power:
            if ( reading_sets_taken == 0 ) {
                reading_sets_taken++;
            } else {
                ( avg_pwr_idx > 0 ) ?
                ( delta_power = average_power_sub_[avg_pwr_idx] - average_power_sub_[avg_pwr_idx - 1] ) :
                ( delta_power = average_power_sub_[avg_pwr_idx] - average_power_sub_[AVERAGES_RING_BUFFER_SIZE] );

                ( avg_pwr_idx > 0 ) ?
                ( delta_voltage = average_voltage_sub_[avg_pwr_idx] - average_voltage_sub_[avg_pwr_idx - 1] ) :
                ( delta_voltage = average_voltage_sub_[avg_pwr_idx] - average_voltage_sub_[AVERAGES_RING_BUFFER_SIZE] );

// find count of positive power deltas, count of negative power deltas:
// --- NOT YET IMPLEMENTED - TMH ---

// - STEP - adjust controlling voltage to switching supply based solar array load
//                chprintf(DEBUG_SD, "delta power = %d, delta voltage - %d\r\n", delta_power, delta_voltage);
                iadj_uv = adjust_vref(delta_power, delta_voltage, iadj_uv);

//                power = average_power_sub_[l];
            }
        }
#endif // end if compiling PAO second draft implementation


        if ((loop_iteration % DIAG_REPORT_EVERY_N_LOOP_ITERATIONS) == 0) {
#ifdef PAO_VERSION_1
            chprintf(DEBUG_SD, "- MARK -\r\n");
            chprintf(DEBUG_SD, "at loop iteration %u iadj_uv now = %u, power = %u\r\n",
              loop_iteration, iadj_uv, power);
#endif

#ifdef PAO_VERSION_2
//            chprintf(DEBUG_SD, "loop %u:  iadj_uv = %u, power = %u, high power = %u, high averaged power = %u\r\n",
//              loop_iteration, iadj_uv, average_power_present, highest_power_reading, highest_average_power_reading);
            chprintf(DEBUG_SD, "loop %u:  avg powers stored = %u, iadj_uv = %u, power = %u, high power = %u, high averaged power = %u\r\n",
              loop_iteration, running_count_average_powers_stored,
              iadj_uv, average_power_present, highest_power_reading, highest_average_power_reading);
#endif

#ifdef PAO_VERSION_3
            chprintf(DEBUG_SD, "loop %u: iadj_uv = %u, direction_up_flag = %u, avg_power_initial_uW = %u, avg_voltage_initial_uV = %u\r\n",
            		loop_iteration, pao_state.iadj_uv, pao_state.direction_up_flag, pao_state.avg_power_initial_uW, pao_state.avg_voltage_initial_uV);
#endif
        }
#endif

    } // end while thread should run loop

    /* Stop drivers */
    dacStop(&DACD1);
    ina226Stop(&ina226dev);

    /* Stop LT1618 */
    palClearLine(LINE_LT1618_EN);

    chThdExit(MSG_OK);
}




//----------------------------------------------------------------------
// 
// 2021-03-14 Sunday
// Some observations on Perturb And Observe algorithm, first draft:
//   *  there seems to be jitter in the power readings, though we're only dumping every 200th reading
//   *  power measured in micro-watts, with resolution or step of 500 microwatts, 1/2 mW
//   *  power behavior over time with first draft alorithm rises to ~0.3 watts then drops suddenly, does not recover
//
// Some thoughts on Perturb And Observer:
//   *  we can take multiple power readings and store them in a ring buffer before adjusting control voltage 'Vref'
//   *  we can store Vref and associated highest power reading, to use to recover from drop off
//   *  we can look for successive rises and falls in power over n readings
//   *  we can look for average rise and fall of power over n readings
//   *  we can keep a ring buffer of avarage power delta over m sets of n readings
// 
//----------------------------------------------------------------------
