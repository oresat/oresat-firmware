#include "batt.h"
#include "max17205.h"
#include "CANopen.h"

#define NCELLS          2U          /* Number of cells */
#define FASTCHG_THRSH   250U        /* Threshold below VBUS to enable Fast Charge (mV) */
#define SLOWCHG_THRSH   500U        /* Threshold below VBUS to enable Slow Charge (mV) */

static const I2CConfig i2cconfig = {
    STM32_TIMINGR_PRESC(0xBU) |
    STM32_TIMINGR_SCLDEL(0x4U) | STM32_TIMINGR_SDADEL(0x2U) |
    STM32_TIMINGR_SCLH(0xFU)  | STM32_TIMINGR_SCLL(0x13U),
    0,
    0
};

static const max17205_regval_t batt_cfg[] = {
    {MAX17205_AD_PACKCFG, MAX17205_SETVAL(MAX17205_AD_PACKCFG,
                                          _VAL2FLD(MAX17205_PACKCFG_NCELLS, NCELLS) |
                                          MAX17205_PACKCFG_BALCFG_40 |
                                          MAX17205_PACKCFG_CHEN)},
    {MAX17205_AD_NRSENSE, MAX17205_RSENSE2REG(10000U)},
    {0,0}
};

static const MAX17205Config max17205config = {
    &I2CD1,
    &i2cconfig,
    batt_cfg
};

static MAX17205Driver max17205dev;

/* Battery monitoring thread */
THD_WORKING_AREA(batt_wa, 0x400);
THD_FUNCTION(batt, arg)
{
    (void)arg;

    max17205ObjectInit(&max17205dev);
    max17205Start(&max17205dev, &max17205config);

    while (!chThdShouldTerminateX()) {
        chThdSleepMilliseconds(1000);

        /* Record pack and cell voltages to object dictionary */
        OD_battery.cell1 = max17205ReadVoltage(&max17205dev, MAX17205_AD_AVGCELL1);
        OD_battery.cell2 = max17205ReadVoltage(&max17205dev, MAX17205_AD_AVGCELL2);
        OD_battery.VCell = max17205ReadVoltage(&max17205dev, MAX17205_AD_AVGVCELL);

        /* TODO: Fast charge removed from Battery v2? */
        if (OD_battery.VCell >= OD_battery.VBUS - FASTCHG_THRSH) {
            /*palSetLine(LINE_FASTCHG);*/
        } else if (OD_battery.VCell >= OD_battery.VBUS - SLOWCHG_THRSH) {
            /*palClearLine(LINE_FASTCHG);*/
        } else {
            /*palClearLine(LINE_FASTCHG);*/
        }

        /* capacity */
        OD_battery.fullCapacity = max17205ReadCapacity(&max17205dev, MAX17205_AD_FULLCAP);
        OD_battery.availableCapacity = max17205ReadCapacity(&max17205dev, MAX17205_AD_AVCAP);
        OD_battery.mixCapacity = max17205ReadCapacity(&max17205dev, MAX17205_AD_MIXCAP);

        /* state of charge */
        OD_battery.timeToEmpty = max17205ReadTime(&max17205dev, MAX17205_AD_TTE);
        OD_battery.timeToFull = max17205ReadTime(&max17205dev, MAX17205_AD_TTF);
        OD_battery.availableStateOfCharge = max17205ReadPercentage(&max17205dev, MAX17205_AD_AVSOC);
        OD_battery.presentStateOfCharge = max17205ReadPercentage(&max17205dev, MAX17205_AD_VFSOC);

        /* other info */
        OD_battery.cycles = max17205ReadRaw(&max17205dev, MAX17205_AD_CYCLES);

        /* Toggle LED */
        palToggleLine(LINE_LED);
    }

    max17205Stop(&max17205dev);

    palClearLine(LINE_LED);
    chThdExit(MSG_OK);
}
