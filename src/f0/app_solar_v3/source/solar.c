#include "solar.h"
#include "ina226.h"
#include "max580x.h"
#include "CANopen.h"

#define CURR_LSB    10  /* 10uA/bit */
#define RSENSE      100 /* 0.1 ohm  */
#define SLEEP_MS    1
#define STEP_SIZE   5

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

static const MAX580XConfig max580xconfig = {
    &I2CD1,
    &i2cconfig,
    MAX5805_SADDR,
    MAX580X_REF_2048 | MAX580X_REF_INT_EN,
    MAX580X_POWER_NORMAL,
    MAX580X_CONFIG_AUX_CLEAR,
    MAX580X_DEFAULT_POR
};

static MAX580XDriver max580xdev;
static INA226Driver ina226dev;

uint32_t calc_iadj(uint32_t i_out)
{
    return ((50520000 - i_out * RSENSE) / 3200);
}

uint32_t calc_mppt(uint16_t volt, int16_t curr, uint16_t pwr, uint32_t *iadj_v)
{
    /* The values from the previous iteration of the loop */
    static uint16_t prev_volt = 0;
    static int16_t  prev_curr = 0;
    static uint16_t prev_pwr = 0;
    int16_t delta_v = volt - prev_volt;
    int16_t delta_i = curr - prev_curr;
    int16_t delta_p = pwr  - prev_pwr;
    prev_volt = volt;
    prev_curr = curr;
    prev_pwr  = pwr;

    /* Start IC MPPT Algorithm */
    if (delta_v == 0) {
        if (delta_i != 0) {
            if (delta_i > 0) {
                *iadj_v += STEP_SIZE;
            } else {
                *iadj_v -= STEP_SIZE;
            }
        }
    } else {
        if (delta_p/delta_v != 0) {
            if (delta_p/delta_v > 0) {
                *iadj_v += STEP_SIZE;
            } else {
                *iadj_v -= STEP_SIZE;
            }
        }
    }
    /* End IC MPPT Algorithm */

    return *iadj_v;
}

/* Main solar management thread */
THD_WORKING_AREA(solar_wa, 0x100);
THD_FUNCTION(solar, arg)
{
    (void)arg;
    uint32_t iadj_v = 15000;

    /* Start up drivers for I2C devices */
    ina226Start(&ina226dev, &ina226config);
    max580xStart(&max580xdev, &max580xconfig);
    palSetLine(LINE_LED_GREEN);

    max580xWriteVoltage(&max580xdev, MAX580X_CODE_LOAD, iadj_v);
    palSetLine(LINE_OUTPUT_EN);
    while (!chThdShouldTerminateX()) {
        chThdSleepMilliseconds(SLEEP_MS);

        /* Get present values */
        OD_solarPanel.voltage = ina226ReadVBUS(&ina226dev);
        OD_solarPanel.current = ina226ReadCurrent(&ina226dev);
        OD_solarPanel.power = ina226ReadPower(&ina226dev);

        /*if (OD_solarPanel.voltage >= 45000) {*/
            /*palClearLine(LINE_CAN_SILENT);*/
        /*} else {*/
            /*palSetLine(LINE_CAN_SILENT);*/
        /*}*/

        /* Calculate iadj */
        calc_mppt(OD_solarPanel.voltage, OD_solarPanel.current, OD_solarPanel.power, &iadj_v);

        /* Write new iadj value */
        max580xWriteVoltage(&max580xdev, MAX580X_CODE_LOAD, iadj_v);
    }

    /* Stop drivers for I2C devices */
    max580xStop(&max580xdev);
    ina226Stop(&ina226dev);

    palClearLine(LINE_LED_GREEN);
    chThdExit(MSG_OK);
}
