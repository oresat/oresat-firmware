#include "solar.h"
#include "ina226.h"
#include "CANopen.h"
#include "OD.h"

#include <sys/param.h>

#if 0
#include "chprintf.h"
#define DEBUG_SD (BaseSequentialStream *) &SD2
#define dbgprintf(str, ...) chprintf(DEBUG_SD, str, ##__VA_ARGS__)
#else
#define dbgprintf(str, ...)
#endif


/* Defines for INA226 */
#define CURR_LSB                20       /* 20uA/bit */
#define RSENSE                  100      /* 0.1 ohm  */
#define DAC_VDDA_uV             3333000  /* 3.333 V. Change to 3.0 v when powered from debug board */

//Assumes 3.3V Vcc
#define DAC_MININUM_ADJUST_uV   805

#define I_ADJ_FAILSAFE          1450000
#define I_ADJ_INITIAL           1500000
#define I_ADJ_MAX               1500000
#define I_ADJ_MIN               0
#define HISTERESIS_mW           3


//1000 is based on the width of the flat at the top of the curve and the minimum adjustable value of the DAC
#define VREF_STEP_NEGATIVE_uV             1000
#define VREF_STEP_POSITIVE_uV             (VREF_STEP_NEGATIVE_uV * 4)


#if VREF_STEP_NEGATIVE_uV < DAC_MININUM_ADJUST_uV
#error "VREF_STEP_NEGATIVE_uV must be greater then DAC_MININUM_ADJUSG_uV"
#endif

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
#define INA226_ADC_CONVERSION_uS        1100


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


struct Sample {
    uint32_t power_mW;
    uint32_t voltage_mV;
    uint32_t current_uA;
};


typedef struct {
    bool direction_up_flag;
    bool hit_step_size_threshold_flag;

    uint32_t iadj_uV;
    struct Sample sample;
    uint32_t max_voltage_mV;
} MpptPaoState;


/**
 * @brief control DAC output in microvolts.
 *
 * @param[in] dacp      DAC driver pointer.
 * @param[in] chan      DAC channel.
 * @param[in] uV        output volts in uV (microVolts).
 */
void dac_put_microvolts(DACDriver *dacp, dacchannel_t chan, uint32_t uV) {
    /* Per section 14.5.3 of the STM32F0x1 ref manual,
     * Vout(mV) = VDDA(mV) * (reg_val / 4096)
     * so, reg_val = (Vout * 4096) / VDDA
     */
    dacsample_t val = ((uV/100) << 12) / (DAC_VDDA_uV/100);
    dacPutChannelX(dacp, chan, val);
}

/**
 * Reads power flow characteristics from the INA226
 */
bool read_avg_power_and_voltage(struct INA226Driver * ina226, struct Sample * sample) {

    bool ret = true;
    if( ina226ReadPower(ina226, &sample->power_mW) != MSG_OK ) {
        ret = false;
    }
    if( ina226ReadVBUS(ina226, &sample->voltage_mV) != MSG_OK ) {
        ret = false;
    }
    if( ina226ReadCurrent(ina226, &sample->current_uA) != MSG_OK ) {
        ret = false;
    }
    if( ! ret ) {
        //CO_errorReport(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_COMMUNICATION, SOLAR_OD_ERROR_TYPE_INA226_COMM_ERROR);
    }

    return ret;
}

uint32_t saturate_uint32_t(const int64_t v, const uint32_t min, const uint32_t max) {
    if (v > max)
        return max;
    else if (v < min)
        return min;
    return v;
}

// Determines step size for iAdj based on current voltage. Allows for faster convergence on MPP
uint32_t get_iadj_step_size(MpptPaoState *state) {
    // FIXME: hit_step_size_threshold flag never gets unset
    if(!state->hit_step_size_threshold_flag && state->max_voltage_mV != 0) {
        const uint32_t threshold_05_mV = state->max_voltage_mV / 20; // 0.95 threshold
        const uint32_t threshold_95_mV = state->max_voltage_mV - threshold_05_mV;

        if(state->sample.voltage_mV > threshold_95_mV) {
            //Linear scale of step size based on delta from maximum voltage
            const int32_t v = ((state->sample.voltage_mV - threshold_95_mV) * 100) / threshold_05_mV;
            return (((5000 - VREF_STEP_NEGATIVE_uV) * v) / 100) + VREF_STEP_NEGATIVE_uV;
        } else {
            state->hit_step_size_threshold_flag = true;
        }
    }

    if( state->direction_up_flag ) {
        return VREF_STEP_POSITIVE_uV;
    }
    return VREF_STEP_NEGATIVE_uV;
}

bool itterate_mppt_perturb_and_observe(MpptPaoState *state) {

    uint32_t step = get_iadj_step_size(state);
    // FIXME: why can't get_step_size set the negative value?
    uint64_t iadj = state->iadj_uV + state->direction_up_flag ? step : -step;
    uint32_t iadj_uV_perturbed = saturate_uint32_t(iadj, I_ADJ_MIN, I_ADJ_MAX);

    if( state->iadj_uV == iadj_uV_perturbed ) { // i.e. either I_ADJ_MIN or I_ADJ_MAX
        // It has saturated to an identical value, flip the search direction and process in the
        // next iteration
        state->direction_up_flag = (! state->direction_up_flag);
        return true;
    }

    dac_put_microvolts(&DACD1, 0, iadj_uV_perturbed);
    //Compensate for the internal averaging done by the ina chip
    chThdSleepMilliseconds((NUM_INA226_AVG * INA226_ADC_CONVERSION_uS) / 1000);
    struct Sample perturbed = {};
    if(!read_avg_power_and_voltage(&ina226dev, &perturbed)) {
        //I2C communications error, no data to make a decision on. Fail safe to moving left
        state->direction_up_flag = true;

        state->iadj_uV = iadj_uV_perturbed;
        if( state->iadj_uV > I_ADJ_FAILSAFE ) {
            state->iadj_uV = I_ADJ_FAILSAFE;
        }

        //CO_errorReport(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_COMMUNICATION, SOLAR_OD_ERROR_TYPE_PAO_INVALID_DATA);

        return false;
    }

    if(perturbed.power_mW < (state->sample.power_mW - HISTERESIS_mW)) {
        //Always move the iadj value, even if the output power is equal. This will cause it to hunt
        //back and forth between two points that have a detectable difference in their power output.
        state->direction_up_flag = (! state->direction_up_flag);
    }

    state->iadj_uV = iadj_uV_perturbed;

    state->sample = perturbed;
    state->max_voltage_mV = MAX(state->max_voltage_mV, perturbed.voltage_mV);

    return true;
}


/* Main solar management thread */
THD_WORKING_AREA(solar_wa, 0x400);
THD_FUNCTION(solar, arg)
{
    I2CDriver * i2c = arg;
    const INA226Config ina226config = {
        i2c,
        INA226_SADDR,
        INA226_CONFIG_MODE_SHUNT_VBUS | INA226_CONFIG_MODE_CONT |
        INA226_CONFIG_VSHCT_1100US | INA226_CONFIG_VBUSCT_1100US |
        INA226_CONFIG_AVG_16,
        (5120000/(RSENSE * CURR_LSB)),
        CURR_LSB
    };


    dbgprintf("\r\nRunning solar app...\r\n");
    /* Start up drivers */
    ina226ObjectInit(&ina226dev);
    dbgprintf("Initializing DAC....\r\n");
    dacStart(&DACD1, &dac1cfg);

    dbgprintf("Initializing INA226....\r\n");
    ina226Start(&ina226dev, &ina226config);

    if( ina226dev.state != INA226_READY ) {
        dbgprintf("Failed to initialize INA226!!!\r\n");
        // FIXME: ??? don't ignore errors
        // EMCY
        // DIE
        chThdSleepMilliseconds(100);
    }

    //Only PAO implemented for the time being
    OD_RAM.x4003_mppt_alg = MPPT_ALGORITHM_PAO;

    MpptPaoState state = {
        .iadj_uV = I_ADJ_INITIAL,
    };

    palSetLine(LINE_LT1618_EN);

    dac_put_microvolts(&DACD1, 0, state.iadj_uV);

    dbgprintf("Done with init INA226, running main loop....\r\n");

    systime_t t_start = chVTGetSystemTime();
    systime_t t_last = t_start;
    systime_t t_now = t_start;
    // FIXME: reset energyTrack every n minutes?
    uint32_t energy_mJ = 0;

    while(!chThdShouldTerminateX()) {
        itterate_mppt_perturb_and_observe(&state);

        /*
        Energy Tracking:
        - Approximating energy by taking the tDiff = (t_n - t_n-1) * pSample, pSample being the
          most recently sampled power value in mw
        - Tracking energy in a uint32_t to allow for millijoule precision
        - Approximating the integral by dividing the power into tDiff chunks
        - Converting to joules when we store it in the OD so we don't overflow the uint16_t in a
          90 min interval
        */
        t_last = t_now;
        t_now = chVTGetSystemTime();
        energy_mJ += state.sample.power_mW * TIME_I2S(t_now - t_last);

        // Dividing by 1k to convert to joules and truncate to 16 bits for the OD.
        // FIXME: truncation looks suspicious
        OD_RAM.x4000_output.energy = (uint16_t) energy_mJ / 1000;

        OD_RAM.x4000_output.voltage = state.sample.voltage_mV;
        OD_RAM.x4000_output.voltage_avg = state.sample.voltage_mV;
        OD_RAM.x4000_output.current = state.sample.current_uA / 1000;
        OD_RAM.x4000_output.current_avg = state.sample.current_uA / 1000;
        OD_RAM.x4000_output.power = state.sample.power_mW;
        OD_RAM.x4000_output.power_avg = state.sample.power_mW;

        OD_RAM.x4000_output.voltage_max = state.max_voltage_mV;
        OD_RAM.x4000_output.current_max = MAX(OD_RAM.x4000_output.current_max, state.sample.current_uA / 1000);
        OD_RAM.x4000_output.power_max = MAX(OD_RAM.x4000_output.power_max, state.sample.power_mW);

        OD_RAM.x4004_lt1618_iadj = state.iadj_uV / 1000;
    }

    /* Stop drivers */
    dacStop(&DACD1);
    ina226Stop(&ina226dev);

    /* Stop LT1618 */
    palClearLine(LINE_LT1618_EN);

    chThdExit(MSG_OK);
}
