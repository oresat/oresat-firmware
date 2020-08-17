#include "solar.h"
#include "ina226.h"
#include "max580x.h"
#include "CANopen.h"

#define CURR_LSB    10  /* 10uA/bit */
#define RSENSE      100 /* 0.1 ohm  */
#define SLEEP_MS    1
#define STEP_SIZE   0.01
#define DAC_VDDA_MV 3300 /* 3.3 mV */

static const I2CConfig i2cconfig = {
    STM32_TIMINGR_PRESC(0xBU) |
    STM32_TIMINGR_SCLDEL(0x4U) | STM32_TIMINGR_SDADEL(0x2U) |
    STM32_TIMINGR_SCLH(0xFU)  | STM32_TIMINGR_SCLL(0x13U),
    0,
    0
};

static const INA226Config ina226config = {
    &I2CD1,
    &i2cconfig,
    INA226_SADDR,
    INA226_CONFIG_MODE_SHUNT_VBUS | INA226_CONFIG_MODE_CONT |
    INA226_CONFIG_VSHCT_1100US | INA226_CONFIG_VBUSCT_1100US |
    INA226_CONFIG_AVG_1,
    (5120000/(RSENSE*CURR_LSB)),
    CURR_LSB
};

/*
static const MAX580XConfig max580xconfig = {
    &I2CD1,
    &i2cconfig,
    MAX5805_SADDR,
    MAX580X_REF_2048 | MAX580X_REF_INT_EN,
    MAX580X_POWER_NORMAL,
    MAX580X_CONFIG_AUX_CLEAR,
    MAX580X_DEFAULT_POR
};
* */

// DAC1 config
static const DACConfig dac1cfg1 = {
  .init         = 1861U,                // initialize DAC to 1.5V (1500*4096)/3300
  .datamode     = DAC_DHRM_12BIT_RIGHT, // 12 bit, right aligned
  .cr           = 0                     // no control reg options
};

static MAX580XDriver max580xdev;
static INA226Driver ina226dev;

/**
 * @brief control DAC output in millivolts.
 *       
 */
void dacPutMillivolts(DACDriver *dacp, dacchannel_t chan, uint32_t mv) {
    // per section 14.5.3 of the STM32F0x1 ref manual,  
    // Vout(mV) = VDDA(mV) * (reg_val / 4096)
    // so, reg_val = (Vout * 4096) / VDDA 
    dacsample_t val = (mv <<12) / DAC_VDDA_MV;
    dacPutChannelX(dacp, chan, val);
}

/**
 * @brief Calculates Iadj_v required for a particular max current.
 * @return Iadj_v in millivolts.
 * NOTE: Earlier version had one more decimal.
 */    
uint32_t calc_iadj(uint32_t i_out)
{
    return ((5052000 - i_out * RSENSE) / 3200);
}

/**
 * @brief Maximum power point tracking algorithm for Solar cells
 * @return Maximum current to be drawn from solar cells
 * TODO: Find min/max limits of step size
 *       Average a few samples to reduce noise
 *       reduce max current limit immediatly if current is lower that the allowed current.(brownout condition)
 *       increase max current limit immediatly if voltage is higher that expected.(shutdown condition)
 *       
 */
int32_t calc_mppt(uint16_t volt, int16_t curr, uint16_t pwr)
{

    /* The values from the previous iteration of the loop */
    static uint16_t prev_volt = 0;
    static uint16_t prev_curr = 0;
    static uint16_t prev_pwr = 0;
    /* programmed max current from previous iteration*/
    /* TODO: Update algorithm to use it to save from high to low illumination*/
    static uint16_t i_in;
    
    int16_t delta_v = volt - prev_volt;
    int16_t delta_i = curr - prev_curr;
    int16_t delta_p = pwr  - prev_pwr;
    prev_volt = volt;
    prev_curr = curr;
    prev_pwr  = pwr;

    /* Start IC MPPT Algorithm */
    if (delta_i == 0) {
        if (delta_i != 0) {
            if (delta_v > 0) {
                i_in += STEP_SIZE;
            } else {
                i_in -= STEP_SIZE;
            }
        }
    } else {
        if (delta_p/delta_i != 0) {
            if (delta_p/delta_i > 0) {
                i_in += STEP_SIZE;
            } else {
                i_in -= STEP_SIZE;
            }
        }
    }
    /* End IC MPPT Algorithm */

    return i_in;
}

/* Main solar management thread */
THD_WORKING_AREA(solar_wa, 0x100);
THD_FUNCTION(solar, arg)
{
    (void)arg;
    uint32_t iadj_v = 15000;
    uint32_t i_in;

    /* Start up drivers for I2C devices */
    ina226Start(&ina226dev, &ina226config);
    //max580xStart(&max580xdev, &max580xconfig);
    dacStart(&DACD1, &dac1cfg1);
    palSetLine(LINE_LED);

    max580xWriteVoltage(&max580xdev, MAX580X_CODE_LOAD, iadj_v);
    while (!chThdShouldTerminateX()) {
        chThdSleepMilliseconds(SLEEP_MS);

        /* Get present values */
        OD_solarPanel.voltage = ina226ReadVBUS(&ina226dev);
        OD_solarPanel.current = ina226ReadCurrent(&ina226dev);
        OD_solarPanel.power = ina226ReadPower(&ina226dev);

        /* Calculate iadj */
        i_in = calc_mppt(OD_solarPanel.voltage, OD_solarPanel.current, OD_solarPanel.power);
        iadj_v = calc_iadj(i_in);

        /* Write new iadj value */
        //max580xWriteVoltage(&max580xdev, MAX580X_CODE_LOAD, iadj_v);
        dacPutMillivolts(&DACD1, 0, iadj_v) ;
    }

    /* Stop drivers for I2C devices */
    //max580xStop(&max580xdev);
    dacStop(&DACD1);
    ina226Stop(&ina226dev);

    palClearLine(LINE_LED);
    chThdExit(MSG_OK);
}
