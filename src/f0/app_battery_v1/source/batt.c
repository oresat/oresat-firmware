#include "batt.h"
#include "max17205.h"

#define NCELLS          2U  /* Number of cells */
#define BALCFG          3U  /* 10mV difference */

static const I2CConfig i2cconfig = {
    STM32_TIMINGR_PRESC(0xBU) |
    STM32_TIMINGR_SCLDEL(0x4U) | STM32_TIMINGR_SDADEL(0x2U) |
    STM32_TIMINGR_SCLH(0xFU)  | STM32_TIMINGR_SCLL(0x13U),
    0,
    0
};

static const MAX17205Config max17205config = {
    &I2CD1,
    &i2cconfig
};

static MAX17205Driver max17205dev;

/* Battery monitoring thread */
THD_WORKING_AREA(batt_wa, 0x40);
THD_FUNCTION(batt, arg)
{
    (void)arg;

    max17205Start(&max17205dev, &max17205config);
    max17205WriteRaw(&max17205dev, MAX17205_AD_PACKCFG, MAX17205_PACKCFG_PERM_BITS(
                _VAL2FLD(MAX17205_PACKCFG_NCELLS, NCELLS) |
                _VAL2FLD(MAX17205_PACKCFG_BALCFG, BALCFG) |
                MAX17205_PACKCFG_CHEN));

    while (!chThdShouldTerminateX()) {
        palToggleLine(LINE_LED_GREEN);
        chThdSleepMilliseconds(500);
    }

    max17205Stop(&max17205dev);

    palClearLine(LINE_LED_GREEN);
    chThdExit(MSG_OK);
}
