#include "solar.h"
#include "ina226.h"
#include "max580x.h"
#include "CANopen.h"

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

/* Example blinker thread */
THD_WORKING_AREA(solar_wa, 0x100);
THD_FUNCTION(solar, arg)
{
    (void)arg;
    uint32_t pwr, iadj_v;

    /* Start up drivers for I2C devices */
    ina226Start(&ina226dev, &ina226config);
    max580xStart(&max580xdev, &max580xconfig);

    while (!chThdShouldTerminateX()) {
        /* Get current values for power and iadj voltage */
        pwr = ina226ReadPower(&ina226dev);
        iadj_v = max580xReadVoltage(&max580xdev, MAX580X_CODE_LOAD);

        /* Calculate perterbation of iadj */

        /* Write new iadj value */
        max580xWriteVoltage(&max580xdev, MAX580X_CODE_LOAD, iadj_v);

        /* Toggle LED and sleep */
        palToggleLine(LINE_LED_GREEN);
        chThdSleepMilliseconds(100);
    }

    /* Stop drivers for I2C devices */
    max580xStop(&max580xdev);
    ina226Stop(&ina226dev);

    palClearLine(LINE_LED_GREEN);
    chThdExit(MSG_OK);
}
