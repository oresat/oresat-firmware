#include "solar.h"
#include "ina226.h"
#include "CANopen.h"
#include "chprintf.h"

/* Defines for INA226 */
#define CURR_LSB               20       /* 20uA/bit */
#define RSENSE                 100      /* 0.1 ohm  */
#define DAC_VDDA_UV            3333000  /* 3.333 V. Chgange to 3.0 v when powered from debug board */

/* Defines for MPPT algorithm iteration speed */
#define SLEEP_MS               2

/* Defines for MPPT algorithm that changes with each solar cell variant
 * Things to note
 * Negative step size needs to be greater as the curve falls quickly.
 * Make sure to account for noise. Lower value will cause curve to crash. Higher value will not let the system reach its potential.
 */
#define MIN_DP_DI              0000     /* The most important piece. This keeps the point to the left of MPP. */
#define NVE_STEP_SIZE          3500     /* Fixed -ve step size */
#define CURR_THRES_SENS        0        /* Current Threshold Sensitivity. Reduces sensitivity to noise in current. */
#define MAX_STEP_SIZE          10000    /* Maximum step size for variable step IC. */
#define STEP_SIZE_FACTOR       2000     /* Posive step factor. */
#define NVE_STEP_SIZE_FACTOR   4        /* Negative step factor. This is multipled with Positive step factor */
#define MIN_PV_CURRENT         00000    /* Minimum current drawn from PV cells */
#define MAX_PV_CURRENT         500000   /* Maximum current drawn from PV cells */
#define MIN_PV_POWER           50000    /* Minimum power drawn from PV cells */



static const I2CConfig i2cconfig = {
    STM32_TIMINGR_PRESC(0xBU) |
    STM32_TIMINGR_SCLDEL(0x4U) | STM32_TIMINGR_SDADEL(0x2U) |
    STM32_TIMINGR_SCLH(0xFU)  | STM32_TIMINGR_SCLL(0x13U),
    0,
    0
};

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
    (5120000/(RSENSE*CURR_LSB)),
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

// 2021-02-07 - first draft read temperature routine
bool read_tmp101an_temperature_v1(uint8_t* buffer_tx, uint8_t* buffer_rx)
{

}



/* Main solar management thread */
THD_WORKING_AREA(solar_wa, 0x400);
THD_FUNCTION(solar, arg)
{
    (void)arg;
    uint32_t voltage, power;
    int32_t current;
    uint32_t iadj_uv = 1500000;
    uint32_t i_in=0;
    int i, j;

// 2021-02-07 - these two byte arrays will be passed to a development
//  routine, to confirm we can talk with the TMP101AN sensors of the
//  solar board.  When that's working we'll move these and the dev'
//  code over to the TMP101AN driver source file.  That will be the
//  first step to honor and conform to the object oritented device
//  driver encapsulation that's already expressed in the Oresat firmware
//  project - TMH
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    uint8_t tmp101an_buf_tx[2] = {0};
    uint8_t tmp101an_buf_rx[5] = {0};


    /* Start up drivers */
    ina226ObjectInit(&ina226dev);
    dacStart(&DACD1, &dac1cfg);
    ina226Start(&ina226dev, &ina226config);

    /* Start up LT1618 */
    palSetLine(LINE_LT1618_EN);

    while(!chThdShouldTerminateX()){
        chThdSleepMilliseconds(SLEEP_MS);

        /* Get present values */
        voltage = ina226ReadVBUS(&ina226dev);    /* VBUS voltage in uV */
        current = ina226ReadCurrent(&ina226dev); /* Current in uA */
        power   = ina226ReadPower(&ina226dev);   /* Power in increments of uW */

        /* Set OD entries to raw values */
        OD_solarPanel.voltage = ina226ReadRaw(&ina226dev, INA226_AD_VBUS);
        OD_solarPanel.current = (int16_t)ina226ReadRaw(&ina226dev, INA226_AD_CURRENT);
        OD_solarPanel.power   = ina226ReadRaw(&ina226dev, INA226_AD_POWER);

        /* Calculate max input current drawn from solar cells.
         * This is used to calculate iadj.
         */
        i_in = calc_mppt(voltage, current, power);
        iadj_uv = calc_iadj(i_in);
        dacPutMicrovolts(&DACD1, 0, iadj_uv);
        if (j >= 500){
          chprintf((BaseSequentialStream *) &SD2, "Iteration: %d, Volt: %d uv, Current: %d uA, Power: %d uW, \r\n",i, voltage, current, power);
          chprintf((BaseSequentialStream *) &SD2, "Input curr: %d ua, Bias Volt: %d uv, \r\n", i_in, iadj_uv);
          j=0;
        }
        j++;
        i++;
    }

    /* Stop drivers */
    dacStop(&DACD1);
    ina226Stop(&ina226dev);

    /* Stop LT1618 */
    palClearLine(LINE_LT1618_EN);

    chThdExit(MSG_OK);
}
