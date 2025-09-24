#include "solar.h"
#include "chthreads.h"
#include "chtime.h"
#include "chvt.h"
#include "ina226.h"
#include "CANopen.h"
#include "OD.h"

#include <sys/param.h>

#ifdef DEBUG_PRINT
#include "chprintf.h"
#define DEBUG_SD (BaseSequentialStream *) &SD2
#define dbgprintf(str, ...) chprintf(DEBUG_SD, str, ##__VA_ARGS__)
#else
#define dbgprintf(str, ...)
#endif


/* DAC1 configuration */
//Assumes 3.3V Vcc
#define DAC_VDDA_uV             3333000  /* 3.333 V. Change to 3.0 v when powered from debug board */
#define DAC_MININUM_ADJUST_uV   805
#define DAC_SETTLE_DELAY_mS     1


/* Corner Cutting configuration */
    //Corner cutting is the feature that looks at the change of the intensity
    // over time to be more aggresive when it rises or conservative when it's
    // falling.
    //This feature should improve tracking and help with crashes on the
    // descent.

#define CC_ENABLE true //enable corner cutting
#define CC_STEP_SCALE 400.0 //how does a trend effect our step size
#define CC_PMAX 0.0045
#define CC_PRATE 0.1
#define CC_NMIN  0.0041
#define CC_NRATE 0.1


/* Dynamic Laziness configuration */
    //Dynamic laziness is trying to allow the processor to sleep for longer
    // when the intensity isn't changing much.
    //This should improve the total output power by reducing
    // the ammount of power consumed by the microcontroller.

#define DL_ENABLE true
#define DL_SLEW_RATE 900 // uA/ms

/* Intensity (Change) Estimation */
    //Intenisty Estimation is required by both CC and DL.
    //Uses a ring buffer of past samples to gauge how intensity has changed
    // over time.
    //Assumes that the power gathered on a sample was close to the maximum.

    //The code required to maintain this datastructure is added when either
    // CC or DL are enabled
#define IE_ENABLE DL_ENABLE || CC_ENABLE //only enabled if either DL or CC are
#define IE_ARRAY_LEN 4 //should be power of 2
#define IE_SAMPLE_SPACING 8 //distance between samples to see more of the trend.


/* MPPT configuration */
#define I_ADJ_FAILSAFE          1450000
#define I_ADJ_INITIAL           1450000
#define I_ADJ_MAX               1450000
#define I_ADJ_MIN               0


/* Slope Calculation Configuration */
#define CRITICAL_SLOPE            0.00425// mW/uA
    //slope of the IP curve that indicates we should turn around when below it
    //seems to be around 0.004 or 0.005

#define IADJ_SAMPLE_OFFSET_uV 25000
    //distance to jump and take another sample for slope calculation

#define SLOPE_CORRECTION_FACTOR 500.0
    //how aggresively to panic when we are below the critical slope

#define FLOAT_DIST_TO_ZERO 0.1
    //used for comparing if a float is small enough that dividing blows up

//TODO: what is the minimum adjustable value of the dac exactly?
//1000 is based on the width of the flat at the top of the curve and the minimum adjustable value of the DAC
#define VREF_STEP_NEGATIVE_uV             -16000
#define VREF_STEP_POSITIVE_uV             (VREF_STEP_NEGATIVE_uV * -4) //ratio of 2
#define MAX_STEP 100000 //cap steps so they aren't too big when dynamic

#define ITERATION_PERIOD 50

#if -VREF_STEP_NEGATIVE_uV < DAC_MININUM_ADJUST_uV
#error "VREF_STEP_NEGATIVE_uV must be greater then DAC_MININUM_ADJUSG_uV"
#endif

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
    float power_mW;
    float voltage_mV;
    float current_uA;
    systime_t time;
};

typedef struct {
    uint32_t iadj_uV;
    struct Sample sample;
    int32_t last_time_mS;
    struct Sample IE_samples[IE_ARRAY_LEN];
    uint32_t index_loop_counter;
} MpptState;

int32_t time_helper(MpptState *state) {
    int32_t time_mS = TIME_I2MS(chVTGetSystemTime());
    int32_t rtn = time_mS - state->last_time_mS;
    state->last_time_mS = time_mS;
    return rtn;
}

void print_state(MpptState *state) {
    dbgprintf("bus mV: %10d | curr uA: %10d | power mW: %10d | iadj uV: %d | cycle time mS: %d\r\n",
      (int32_t) state->sample.voltage_mV,
      (int32_t) state->sample.current_uA,
      (int32_t) state->sample.power_mW,
      state->iadj_uV,
      time_helper(state));
}

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
    //chThdSleepMilliseconds(DAC_SETTLE_DELAY_mS); //TODO: make this shorter
}

//Reads power flow characteristics from the INA226
bool read_avg_power_and_voltage(struct INA226Driver * ina226, struct Sample * sample) {
    bool ret = true;

    if (ina226TriggerOneShotConversion(ina226) != MSG_OK) {
        ret = false;
    }

    chThdSleep(ina226dev.t_conversion);

    bool conversion_ready = false;
    while (!conversion_ready) {
        ina226CheckConversionStatus(ina226, &conversion_ready);
    }
    //time this sample was taken
    sample->time = chVTGetSystemTime();

    int32_t voltage_mV_int = 0;
    if (ina226ReadVBUS(ina226, &voltage_mV_int) != MSG_OK ) {
        ret = false;
    }
    sample->voltage_mV = (float) voltage_mV_int;

    int32_t current_uA_int = 0;
    if (ina226ReadCurrent(ina226, &current_uA_int) != MSG_OK ) {
        ret = false;
    }
    sample->current_uA = (float) current_uA_int;

    // calculate power from bus voltage and current
    sample->power_mW = sample->current_uA / 1000000 * sample->voltage_mV;
        //div to convert output to mW

    if (! ret) {
        //CO_errorReport(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_COMMUNICATION, SOLAR_OD_ERROR_TYPE_INA226_COMM_ERROR);
    }

    return ret;
}

//finds an average of two slopes
float find_ip_slope(MpptState *state, int32_t initial_iadj) {

    struct Sample first;
    struct Sample second;
    struct Sample third;

    int32_t working_iadj = initial_iadj;
    read_avg_power_and_voltage(&ina226dev, &first);
    state->sample = first;

    working_iadj += IADJ_SAMPLE_OFFSET_uV;
    dac_put_microvolts(&DACD1, 0, working_iadj);
    read_avg_power_and_voltage(&ina226dev, &second);

    working_iadj += IADJ_SAMPLE_OFFSET_uV;
    dac_put_microvolts(&DACD1, 0, working_iadj);
    read_avg_power_and_voltage(&ina226dev, &third);

    float delta_power1 = first.power_mW - second.power_mW;
    float delta_current1 = first.current_uA - second.current_uA;

    float delta_power2 = second.power_mW - third.power_mW;
    float delta_current2 = second.current_uA - third.current_uA;

    float slope = (delta_power1 * delta_current2 + delta_power2 * delta_current1) / (2.0 * delta_current1 * delta_current2);

    dbgprintf("calculated slope as %d/10,000 out of %d \n\r", (int32_t) (slope * 10000), (int32_t) (CRITICAL_SLOPE * 10000));
    dac_put_microvolts(&DACD1, 0, initial_iadj);
    return slope;
}

uint32_t saturate_uint32_t(const int64_t v, const uint32_t min, const uint32_t max) {
    if (v > max) {
        return max;
    } else if (v < min) {
        return min;
    }
    return v;
}

//just calculates dP/dT from a sample and the current state sample
float find_pt_slope(struct Sample * newer, struct Sample * older) {
    float dp = (newer->power_mW) - (older->power_mW);
    int32_t dt = chTimeDiffX(newer->time, older->time);

    float dpdt = 0.0;
    if (dt > 0) {
        dpdt = dp / (float) dt;
    }

    return dpdt;
}

int32_t iadj_step_uV(MpptState *state) {

#if IE_ENABLE
    //find the trend from the oldest sample
    //get current time to compare with sample
    //in mW/cycle
    //how much do we change our step based on our velocity
    float pt_slope = 0.0;

    struct Sample newer = state->IE_samples[(state->index_loop_counter - 1) % IE_ARRAY_LEN];
    struct Sample older = state->IE_samples[state->index_loop_counter % IE_ARRAY_LEN];
    pt_slope = find_pt_slope(&newer, &older);

    //average by array len
    pt_slope = pt_slope / ((float) IE_ARRAY_LEN);
    dbgprintf("pt_slope %d/1000 ", (int32_t) (1000*(pt_slope)));

#endif

    int32_t CC_step = 0;
    float CC_critical_adjust = 0.0;

#if CC_ENABLE

    CC_step = pt_slope * CC_STEP_SCALE;
    dbgprintf("CC_step is %d \r\n", CC_step);

    if (pt_slope < 0) {
        CC_critical_adjust = pt_slope * CC_NRATE;
    } else if (pt_slope > 0) {
        CC_critical_adjust = pt_slope * CC_PRATE;
    }

#endif


    float ip_slope = find_ip_slope(state, state->iadj_uV);

    float reference_slope = CRITICAL_SLOPE - CC_critical_adjust;
    dbgprintf("reference_slope is %d/10,000, PMAX is %d/10,000, NMIN is %d/10,00  \r\n", (int32_t) (reference_slope*10000), (int32_t) (CC_PMAX*10000), (int32_t) (CC_NMIN*10000));

    //part of corner cutting
    //shouldn't effect normal operation if left in without corner cutting...
    // but I'm disabling it just in case.
#if CC_ENABLE
    if (reference_slope > CC_PMAX) {
        reference_slope = CC_PMAX;
    } else if (reference_slope < CC_NMIN) {
        reference_slope = CC_NMIN;
    }
    dbgprintf("reference slope bounded to %d/10,000 \r\n", (int32_t) (reference_slope*10000));
#endif


    float slope_error = (ip_slope - reference_slope) * SLOPE_CORRECTION_FACTOR;
//TODO: implement dynamic laziness here
//    float DL_size_factor = 0;
#if DL_ENABLE
//    DL_size_factor = state->pt_slope;
#endif

    int32_t step = 0;
    if (slope_error < 0) {
        step = VREF_STEP_POSITIVE_uV * (slope_error * -1) + CC_step;
    } else if (slope_error > 0) {
        step = VREF_STEP_NEGATIVE_uV + CC_step;
    } else {
        step = VREF_STEP_POSITIVE_uV + CC_step;
    }

    return step > MAX_STEP ? MAX_STEP : step;
}

void iterate(MpptState *state) {
    const int64_t iadj = state->iadj_uV + iadj_step_uV(state);
    const uint32_t iadj_uV_perturbed = saturate_uint32_t(iadj, I_ADJ_MIN, I_ADJ_MAX);

    dac_put_microvolts(&DACD1, 0, iadj_uV_perturbed);

    state->iadj_uV = iadj_uV_perturbed;
}


/* Main solar management thread */
THD_WORKING_AREA(solar_wa, 0x400);
THD_FUNCTION(solar, arg)
{
    I2CDriver * i2c = arg;

    // Based on INA226 datasheet, page 15, Equation (2)
    // CURR_LSB = Max Current / 2^15
    // So, with CURR_LSB = 20 uA/bit, Max current = 655 mA
    const INA226Config ina226config = {
        .i2cp  = i2c,
        .saddr = INA226_SADDR,
        .cfg   = INA226_CONFIG_MODE_SHUNT_VBUS |
                 INA226_CONFIG_VSHCT_204US | INA226_CONFIG_VBUSCT_204US |
                 INA226_CONFIG_AVG_1,
        .rshunt_mOhm = 100, /* 0.1 ohm  */
        .curr_lsb_uA = 20,  /* 20uA/bit */
    };

    dbgprintf("\r\nRunning solar app...\r\n");
    /* Start up drivers */
    ina226ObjectInit(&ina226dev);
    dbgprintf("Initializing DAC....\r\n");
    dacStart(&DACD1, &dac1cfg);

    dbgprintf("Initializing INA226....\r\n");
    ina226Start(&ina226dev, &ina226config);

    if (ina226dev.state != INA226_READY) {
        dbgprintf("Failed to initialize INA226!!!\r\n");
        // FIXME: ??? don't ignore errors
        // EMCY
        // DIE
        chThdSleepMilliseconds(100);
    }

    //Only PAO implemented for the time being
    OD_RAM.x4003_mppt_alg = MPPT_ALGORITHM_PAO;

    MpptState state = {
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

    state.index_loop_counter = 0;
    int32_t spacing_loop_counter = 0;
    int32_t main_iterations = 0;
    while(!chThdShouldTerminateX()) {

#if IE_ENABLE
        //populate the intensity estimation array with every nth sample.
        if (!(spacing_loop_counter % IE_SAMPLE_SPACING)) {
            //dbgprintf("sample with time %d stored in IE_ARRAY", state.sample.time);
            state.IE_samples[state.index_loop_counter % IE_ARRAY_LEN] = state.sample;
            state.index_loop_counter++;
        }
#endif

        iterate(&state);
        //print_state(&state);
        spacing_loop_counter += 1; //must happen after iterate

        chThdSleepUntil(t_start + chTimeMS2I(ITERATION_PERIOD) * ++main_iterations);

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

        OD_RAM.x4000_output.voltage = (uint16_t) state.sample.voltage_mV;
        OD_RAM.x4000_output.voltage_avg = (uint16_t) state.sample.voltage_mV;
        OD_RAM.x4000_output.current = (uint16_t) (state.sample.current_uA / 1000);
        OD_RAM.x4000_output.current_avg = (uint16_t) (state.sample.current_uA / 1000);
        OD_RAM.x4000_output.power = (uint16_t) state.sample.power_mW;
        OD_RAM.x4000_output.power_avg = (uint16_t) state.sample.power_mW;

        OD_RAM.x4000_output.voltage_max = MAX(OD_RAM.x4000_output.voltage_max, (uint16_t) state.sample.voltage_mV);
        OD_RAM.x4000_output.current_max = MAX(OD_RAM.x4000_output.current_max, (uint16_t) (state.sample.current_uA / 1000));
        OD_RAM.x4000_output.power_max = MAX(OD_RAM.x4000_output.power_max, (uint16_t) state.sample.power_mW);

        OD_RAM.x4004_lt1618_iadj = state.iadj_uV / 1000;

    }

    /* Stop drivers */
    dacStop(&DACD1);
    ina226Stop(&ina226dev);

    /* Stop LT1618 */
    palClearLine(LINE_LT1618_EN);

    chThdExit(MSG_OK);
}
