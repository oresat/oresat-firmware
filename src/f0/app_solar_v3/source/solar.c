#include "solar.h"
#include "max580x.h"
#include "CANopen.h"

static const I2CConfig i2cconfig = {
    STM32_TIMINGR_PRESC(0xBU) |
    STM32_TIMINGR_SCLDEL(0x4U) | STM32_TIMINGR_SDADEL(0x2U) |
    STM32_TIMINGR_SCLH(0xFU)  | STM32_TIMINGR_SCLL(0x13U),
    0,
    0
};

static MAX580XConfig devconfig = {
    &I2CD1,
    &i2cconfig,
    MAX5805_SADDR,
    MAX580X_REF_2048 | MAX580X_REF_INT_EN,
    MAX580X_POWER_NORMAL,
    MAX580X_CONFIG_AUX_CLEAR,
    MAX580X_DEFAULT_POR
};

static MAX580XDriver dev;

/* Example blinker thread */
THD_WORKING_AREA(solar_wa, 0x100);
THD_FUNCTION(solar, arg)
{
    (void)arg;

    max580xStart(&dev, &devconfig);

    while (!chThdShouldTerminateX()) {
        palToggleLine(LINE_LED_GREEN);
        chThdSleepMilliseconds(1000);
    }

    max580xStop(&dev);

    palClearLine(LINE_LED_GREEN);
    chThdExit(MSG_OK);
}
