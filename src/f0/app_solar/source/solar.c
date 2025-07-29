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

#define ABS(a) (((a) < 0) ? -(a) : (a))
/* DAC1 configuration */
//Assumes 3.3V Vcc
#define DAC_VDDA_uV             3333000  /* 3.333 V. Change to 3.0 v when powered from debug board */
#define DAC_MININUM_ADJUST_uV   805
#define DAC_SETTLE_DELAY_mS     1

/* MPPT configuration */
#define I_ADJ_FAILSAFE          1450000
#define I_ADJ_INITIAL           1500000
#define I_ADJ_MAX               1500000
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
#define MAX_STEP 200000 //cap steps so they aren't too big when dynamic

#define SLEEP_CYCLE 50

#if -VREF_STEP_NEGATIVE_uV < DAC_MININUM_ADJUST_uV
#error "VREF_STEP_NEGATIVE_uV must be greater then DAC_MININUM_ADJUSG_uV"
#endif

enum NextDirection{
    Up,
    Down,
    Toggle,
    Unchanged
};

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
    int32_t power_mW;
    int32_t voltage_mV;
    int32_t current_uA;
    int32_t shunt_uV;
};

typedef struct {
    bool direction_up_flag;
    bool voltage_threshold_flag;

    uint32_t iadj_uV;
    struct Sample sample;
    int32_t max_voltage_mV;
    int32_t last_time_mS;
} MpptPaoState;

int32_t time_helper(MpptPaoState *state);

/**
 * @brief control DAC output in microvolts.
 *
 * @param[in] dacp      DAC driver pointer.
 * @param[in] chan      DAC channel.
 * @param[in] uV        output volts in uV (microVolts).
 */

void print_state(MpptPaoState *state) {
    dbgprintf("shunt uV: %10d | bus mV: %10d | curr uA: %10d | power mW: %10d | iadj uV: %d | direction flag: %d | threshold flag: %d | cycle time mS: %d\r\n",
      state->sample.shunt_uV,
      state->sample.voltage_mV,
      state->sample.current_uA,
      state->sample.power_mW,
      state->iadj_uV,
      state->direction_up_flag,
      state->voltage_threshold_flag,
      time_helper(state));
}

int32_t time_helper(MpptPaoState *state) {
    int32_t time_mS = TIME_I2MS(chVTGetSystemTime());
    int32_t rtn = time_mS - state->last_time_mS;
    state->last_time_mS = time_mS;
    return rtn;
}

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

    if (ina226ReadShunt(ina226, &sample->shunt_uV) != MSG_OK) {
        ret = false;
    }
    if (ina226ReadPower(ina226, &sample->power_mW) != MSG_OK ) {
        ret = false;
    }
    if (ina226ReadVBUS(ina226, &sample->voltage_mV) != MSG_OK ) {
        ret = false;
    }
    if (ina226ReadCurrent(ina226, &sample->current_uA) != MSG_OK ) {
        ret = false;
    }
    if (! ret) {
        //CO_errorReport(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_COMMUNICATION, SOLAR_OD_ERROR_TYPE_INA226_COMM_ERROR);
    }

    return ret;
}



//takes two samples, one is assumed to be where we are. the second will be
//moved to after writing iadj+IADJ_SAMPLE_OFFSET_uV. where iadj is an outparemter
//which is allows this function to be called multiple times to get n samples at constant distances
float32_t find_slope(struct Sample *sample_init, struct Sample *sample_adjusted, int32_t* iadj) {
    *iadj = *iadj + IADJ_SAMPLE_OFFSET_uV;
    float32_t delta_power = 0;
    float32_t delta_current = 0;
    float32_t slope = 0;

    dac_put_microvolts(&DACD1, 0, *iadj);
    read_avg_power_and_voltage(&ina226dev, sample_adjusted);

    delta_power = ((float32_t) sample_init->power_mW - (float32_t) sample_adjusted->power_mW); //W
    delta_current = ((float32_t) sample_init->current_uA - (float32_t) sample_adjusted->current_uA); //uA

    if (!(delta_current > -FLOAT_DIST_TO_ZERO && delta_current < FLOAT_DIST_TO_ZERO)) { //TODO: make these ABS more efficient at runtime
        slope = (delta_power / delta_current); //mW/uA
    }
    return slope;
}


float32_t find_compound_slope(struct Sample *current, int32_t old_iadj) {
    float32_t slope1 = 0;
    float32_t slope2 = 0;
    float32_t slope3 = 0;
    int32_t this_iadj = old_iadj;
    struct Sample second;
    struct Sample third;
    struct Sample fourth;

    //int32_t* adjust = &old_iadj;
    slope1 = find_slope(current, &second, &this_iadj);
    slope2 = find_slope(&second, &third, &this_iadj);
    //slope3 = find_slope(&third, &fourth, &this_iadj);

    float32_t slope = (slope1 + slope2 + slope3) / 2.0;
//    float32_t slope = slope1;

    //   dbgprintf("detlap: %d, deltai %d, slope %d, out of %d", (int) (deltap), (int) (deltai), (int) (slope*10000), (int) (CRITICAL_SLOPE*10000));
    dbgprintf("calculated slope as %d/10,000 out of %d \n\r", (int32_t) (slope * 10000), (int32_t) (CRITICAL_SLOPE * 10000));
    dac_put_microvolts(&DACD1, 0, old_iadj);
//   dbgprintf("returned to old iadj\n");
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

// Determines step size for iAdj based on current voltage. Allows for faster convergence on MPP
int32_t iadj_step_uV(MpptPaoState *state) {
    enum NextDirection next_direction = Unchanged;

    float32_t slope = find_compound_slope(&state->sample, state->iadj_uV);
    float32_t slope_error = (slope - CRITICAL_SLOPE) * SLOPE_CORRECTION_FACTOR;

    if (slope_error <= 0) {
        //dbgprintf("LESS THAN");
        next_direction = Up;
    } else if (slope_error > 0) {
        //dbgprintf("GREATER THAN");
        next_direction = Down;
    }
    slope_error = slope_error < 0 ? -slope_error : slope_error;

   //dbgprintf("slope_error as %d/10,000\n", (int32_t) (slope_error * 10000));
    switch (next_direction) {
        case Up:
            state->direction_up_flag = 1;
            break;
        case Down:
            state->direction_up_flag = 0;
            break;
        case Toggle:
            state->direction_up_flag = !state->direction_up_flag;
            break;
        case Unchanged:
            break;
    }

    int32_t toRet = 0;

    if (state->direction_up_flag) {
        toRet = VREF_STEP_POSITIVE_uV * slope_error;
    } else {
        toRet = VREF_STEP_NEGATIVE_uV;
    }
    //dbgprintf("returning: %d\n\r", toRet);
    return toRet > MAX_STEP ? MAX_STEP: toRet;
}

bool iterate_mppt_perturb_and_observe(MpptPaoState *state) {
    int32_t step = iadj_step_uV(state);
//    dbgprintf("step size uV: %5d | ", step);
    const int64_t iadj = state->iadj_uV + step; //iadj_step_uV(state);
    const uint32_t iadj_uV_perturbed = saturate_uint32_t(iadj, I_ADJ_MIN, I_ADJ_MAX);

    //print_state(state);

    dac_put_microvolts(&DACD1, 0, iadj_uV_perturbed);

    struct Sample perturbed = {};
    if (!read_avg_power_and_voltage(&ina226dev, &perturbed)) {
        //I2C communications error, no data to make a decision on. Fail safe to moving left
        state->direction_up_flag = true;

        state->iadj_uV = iadj_uV_perturbed;
        if (state->iadj_uV > I_ADJ_FAILSAFE) {
            state->iadj_uV = I_ADJ_FAILSAFE;
        }

        //CO_errorReport(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_COMMUNICATION, SOLAR_OD_ERROR_TYPE_PAO_INVALID_DATA);

        return false;
    }

    state->iadj_uV = iadj_uV_perturbed;

    state->sample = perturbed;
    state->max_voltage_mV = MAX(state->max_voltage_mV, perturbed.voltage_mV);

    return true;
}

bool generateCSV(INA226Driver *devp, MpptPaoState state) {
    //Generate CSV output to terminal for plotting
    dbgprintf("iadj_uV,power_mW,voltage_mV,current_uA\r\n");

    for (int iadj = 1500000; iadj >= 0; iadj -= 1000) {
        dac_put_microvolts(&DACD1, 0, iadj);
        if (!read_avg_power_and_voltage(devp, &state.sample)) {
            dbgprintf("Failed to read INA226!\r\n");
            return false;
        }
        dbgprintf("%d,%d,%d,%d\r\n", iadj, state.sample.power_mW, state.sample.voltage_mV, state.sample.current_uA );
    };

    return true;
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

    MpptPaoState state = {
        .iadj_uV = I_ADJ_INITIAL,
        .max_voltage_mV = 0,
        .direction_up_flag = true,
        .voltage_threshold_flag = false,
    };

    palSetLine(LINE_LT1618_EN);

    dac_put_microvolts(&DACD1, 0, state.iadj_uV);

    dbgprintf("Done with init INA226, running main loop....\r\n");

    systime_t last_print = chVTGetSystemTime();


    systime_t t_start = chVTGetSystemTime();
    systime_t t_last = t_start;
    systime_t t_now = t_start;
    // FIXME: reset energyTrack every n minutes?
    uint32_t energy_mJ = 0;

    int loop = 0;
    while(!chThdShouldTerminateX()) {
        iterate_mppt_perturb_and_observe(&state);
        chThdSleepMilliseconds(SLEEP_CYCLE);
        /* generateCSV(&ina226dev, state); */

        /*
        Energy Tracking:
        - Approximating energy by taking the tDiff = (t_n - t_n-1) * pSample, pSample being the
          most recently sampled power value in mw
        - Tracking energy in a uint32_t to allow for millijoule precision
        - Approximating the integral by dividing the power into tDiff chunks
        - Converting to joules when we store it in the OD so we don't overflow the uint16_t in a
          90 min interval
        */
//        t_last = t_now;
//        t_now = chVTGetSystemTime();
//        energy_mJ += state.sample.power_mW * TIME_I2S(t_now - t_last);
//
//        // Dividing by 1k to convert to joules and truncate to 16 bits for the OD.
//        // FIXME: truncation looks suspicious
//        OD_RAM.x4000_output.energy = (uint16_t) energy_mJ / 1000;
//
//        OD_RAM.x4000_output.voltage = state.sample.voltage_mV;
//        OD_RAM.x4000_output.voltage_avg = state.sample.voltage_mV;
//        OD_RAM.x4000_output.current = state.sample.current_uA / 1000;
//        OD_RAM.x4000_output.current_avg = state.sample.current_uA / 1000;
//        OD_RAM.x4000_output.power = state.sample.power_mW;
//        OD_RAM.x4000_output.power_avg = state.sample.power_mW;
//
//        OD_RAM.x4000_output.voltage_max = state.max_voltage_mV;
//        OD_RAM.x4000_output.current_max = MAX(OD_RAM.x4000_output.current_max, state.sample.current_uA / 1000);
//        OD_RAM.x4000_output.power_max = MAX(OD_RAM.x4000_output.power_max, state.sample.power_mW);
//
//        OD_RAM.x4004_lt1618_iadj = state.iadj_uV / 1000;

        //FIXME: remove once canopen util is avaliable
        if (!(loop % 50)) {
 //           dbgprintf("shunt uV: %d\r\nbus   mV: %d\r\ncurr  uA: %d\r\npower mW: %d\r\n\r\n",
 //               state.sample.shunt_uV, state.sample.voltage_mV, state.sample.current_uA, state.sample.power_mW);
            loop = 0;
            systime_t current_time = chVTGetSystemTime();
            dbgprintf("cycling at %d ms\n", (int) (chTimeI2MS(current_time - last_print)/50));
            last_print = current_time;
        }
        loop += 1;
    }

    /* Stop drivers */
    dacStop(&DACD1);
    ina226Stop(&ina226dev);

    /* Stop LT1618 */
    palClearLine(LINE_LT1618_EN);

    chThdExit(MSG_OK);
}
