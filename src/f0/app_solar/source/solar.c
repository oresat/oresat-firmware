#include "solar.h"
#include "ina226.h"
#include "CANopen.h"
#include "OD.h"

#include <stdint.h>
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

/* MPPT configuration */
#define I_ADJ_FAILSAFE          1450000
#define I_ADJ_INITIAL           1600000
#define I_ADJ_MAX               1600000
#define I_ADJ_MIN               0
#define HISTERESIS_mW           3

//1000 is based on the width of the flat at the top of the curve and the minimum adjustable value of the DAC
#define VREF_STEP_NEGATIVE_uV             -805
#define VREF_STEP_POSITIVE_uV              4000

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
    int32_t power_mW;
    int32_t voltage_mV;
    int32_t current_uA;
    int32_t shunt_uV;
};

typedef struct {
    int32_t prev_pow;
    int32_t prev_curr;
    uint32_t iadj_uV;
    struct Sample sample;
    struct SharedTempSample* temp_sample;
    int32_t init_voc_read;
    int32_t init_temp_read;
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
bool read_avg_power_and_current(struct INA226Driver * ina226, struct Sample * sample) {
    bool ret = true;

    if (ina226TriggerOneShotConversion(ina226) != MSG_OK) {
        ret = false;
    }

    chThdSleep(ina226dev.t_conversion);

    bool conversion_ready = false;
    while (!conversion_ready) {
       ina226CheckConversionStatus(ina226, &conversion_ready);
    }

    if(ina226ReadShunt(ina226, &sample->shunt_uV) != MSG_OK) {
        ret = false;
    }
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

int32_t read_temp(struct SharedTempSample *temp_sample) {
    chMtxLock(&temp_sample->guard);
    int32_t temp = temp_sample->value;
    chMtxUnlock(&temp_sample->guard);
    return temp;
}

int32_t iadj_step_uV(MpptPaoState *state) {
    int32_t temp = read_temp(state->temp_sample);
    int32_t voc = 2*(2750 + (-56 * (temp - 28) / 10));
    int32_t v1 = voc * 80 / 100;
    int32_t v2 = voc * 95 / 100;
    int32_t d_pow = state->sample.power_mW - state->prev_pow;
    int32_t d_curr = state->sample.current_uA - state->prev_curr;

    dbgprintf("temp: %d ; voc: %d ; v1: %d ; v2: %d ;\r\n", temp, voc, v1, v2);

    if (state->sample.voltage_mV < v1) {
        dbgprintf("in area a\r\n");
        return 10000;
    } else if (state->sample.voltage_mV > v2) {
        dbgprintf("in area d\r\n");
        return -5000;
    } else if (d_curr > 0) {
        // if increasing current
        if (d_pow < 0) {
            // lowered power, then were on the right side of the curve = bad!
            return VREF_STEP_POSITIVE_uV;
        } else {
            // raised power, keep going.
            return VREF_STEP_NEGATIVE_uV;
        }
    } else if (d_curr < 0) {
        // if reducing current
        if (d_pow < 0) {
            // lowered power, then were on the left side, go forward now.
            return VREF_STEP_NEGATIVE_uV;
        } else {
            // raised power, go back again, still on right side.
            return VREF_STEP_POSITIVE_uV;
        }
    } else {
        return 0;
    }
}

bool iterate_mppt_perturb_and_observe(MpptPaoState *state) {
    const int64_t iadj = state->iadj_uV + iadj_step_uV(state);
    const uint32_t iadj_uV_perturbed = saturate_uint32_t(iadj, I_ADJ_MIN, I_ADJ_MAX);

    dac_put_microvolts(&DACD1, 0, iadj_uV_perturbed);

    struct Sample perturbed = {};

    if(!read_avg_power_and_current(&ina226dev, &perturbed)) {
        //I2C communications error, no data to make a decision on. Fail safe to moving left

        state->iadj_uV = iadj_uV_perturbed;
        if( state->iadj_uV > I_ADJ_FAILSAFE ) {
            state->iadj_uV = I_ADJ_FAILSAFE;
        }

        //CO_errorReport(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_COMMUNICATION, SOLAR_OD_ERROR_TYPE_PAO_INVALID_DATA);

        return false;
    }

    // save previous state to compare it to perturbed state
    state->prev_pow = state->sample.power_mW;
    state->prev_curr = state->sample.current_uA;

    state->iadj_uV = iadj_uV_perturbed;
    state->sample = perturbed;

    return true;
}

/* Main solar management thread */
THD_WORKING_AREA(solar_wa, 0x400);
THD_FUNCTION(solar, arg)
{
    struct SolarArgs *args = arg;
    I2CDriver *i2c = args->i2c;

    // Based on INA226 datasheet, page 15, Equation (2)
    // CURR_LSB = Max Current / 2^15
    // So, with CURR_LSB = 20 uA/bit, Max current = 655 mA
    const INA226Config ina226config = {
        .i2cp  = i2c,
        .saddr = INA226_SADDR,
        .cfg   = INA226_CONFIG_MODE_SHUNT_VBUS |
                 INA226_CONFIG_VSHCT_1100US | INA226_CONFIG_VBUSCT_1100US |
                 INA226_CONFIG_AVG_16,
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
        .temp_sample = args->sample,
    };

    read_avg_power_and_current(&ina226dev, &state.sample); 
    read_temp(args->sample);

    state.init_voc_read = state.sample.voltage_mV;
    state.init_temp_read = state.init_temp_read;

    palSetLine(LINE_LT1618_EN);

    dac_put_microvolts(&DACD1, 0, state.iadj_uV);

    dbgprintf("Done with init INA226, running main loop....\r\n");

    systime_t t_start = chVTGetSystemTime();
    systime_t t_last = t_start;
    systime_t t_now = t_start;
    // FIXME: reset energyTrack every n minutes?
    uint32_t energy_mJ = 0;

    while(!chThdShouldTerminateX()) {
        iterate_mppt_perturb_and_observe(&state);

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
