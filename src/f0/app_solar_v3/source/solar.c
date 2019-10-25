#include "solar.h"
#include "ina226.h"
#include "max580x.h"
#include "CANopen.h"

#define SLEEP_MS 1
#define STEP_SIZE 5

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
    5120,       /* 10uA/bit with 0.1mOhm shunt */
    10          /* 10uA/bit */
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

uint32_t calc_iadj(uint32_t pwr, uint32_t volt, int32_t curr, uint32_t iadj_v)
{
    /* Stores the the last perturbation of the VI curve */
    static int32_t perturb = STEP_SIZE;
    /* The values from the previous iteration of the loop */
    static uint32_t prev_pwr = 0;
    static uint32_t prev_volt = 0;
    static int32_t  prev_curr = 0;
    uint32_t delta_pwr  = pwr  - prev_pwr;
    uint32_t delta_volt = volt - prev_volt;
    int32_t  delta_curr = curr - prev_curr;

    /* If the power decreased, flip perturb direction */
    if (pwr < prev_pwr) {
        perturb *= -1;
    }

    iadj_v += perturb;

    prev_pwr  = pwr;
    prev_volt = volt;
    prev_curr = curr;
    return iadj_v;
}

/* Main solar management thread */
THD_WORKING_AREA(solar_wa, 0x100);
THD_FUNCTION(solar, arg)
{
    (void)arg;
    static uint32_t iadj_v = 15000;
    uint32_t pwr, volt;
    int32_t curr;

    /* Start up drivers for I2C devices */
    ina226Start(&ina226dev, &ina226config);
    max580xStart(&max580xdev, &max580xconfig);
    palSetLine(LINE_LED_GREEN);

    max580xWriteVoltage(&max580xdev, MAX580X_CODE_LOAD, iadj_v);
    while (!chThdShouldTerminateX()) {
        /* Get current values for power */
        if (ina226ReadVBUS(&ina226dev) < 400000) {
            palClearLine(LINE_OUTPUT_EN);
        } else {
            palSetLine(LINE_OUTPUT_EN);
        }
        pwr = ina226ReadPower(&ina226dev);
        volt = ina226ReadVBUS(&ina226dev);
        curr = ina226ReadCurrent(&ina226dev);

        /* Calculate perterbation of iadj */
        iadj_v = calc_iadj(pwr, volt, curr, iadj_v);

        /* Write new iadj value */
        max580xWriteVoltage(&max580xdev, MAX580X_CODE_LOAD, iadj_v);

        chThdSleepMilliseconds(SLEEP_MS);
    }

    /* Stop drivers for I2C devices */
    max580xStop(&max580xdev);
    ina226Stop(&ina226dev);

    palClearLine(LINE_LED_GREEN);
    chThdExit(MSG_OK);
}
