#include "ch.h"
#include "hal.h"

#include "CANopen.h"
#include "OD.h"
#include "sensors.h"

typedef struct {
    adcsample_t ts;
    adcsample_t vrefint;
} sensors_t;

sensors_t sensors[2];

static void sensors_cb(ADCDriver *adcp)
{
    sensors_t *sensors = (sensors_t*)adcp->samples;
    int16_t temperature;
    int16_t vdda;
    int i = adcIsBufferComplete(adcp);

    vdda = VREFINT_CAL_VOLT * VREFINT_CAL_VAL / sensors[i].vrefint;
    temperature = ((sensors[i].ts * VREFINT_CAL_VAL * 10 / sensors[i].vrefint) - TS_CAL1_VAL * 10);
    temperature = temperature * (TS_CAL2_TEMP - TS_CAL1_TEMP) / (TS_CAL2_VAL - TS_CAL1_VAL) + TS_CAL1_TEMP * 10;

    /* TODO: Use proper OD interface */
    OD_RAM.x2022_MCU_Sensors.temperatureRaw = sensors[i].ts;
    OD_RAM.x2022_MCU_Sensors.VREFINT_Raw = sensors[i].vrefint;
    OD_RAM.x2022_MCU_Sensors.temperature= temperature;
    OD_RAM.x2022_MCU_Sensors.VREFINT= vdda;
}

static void sensors_err_cb(ADCDriver *adcp, adcerror_t err)
{
    (void)adcp;
    (void)err;
}

static ADCConversionGroup adcgrpcfg = {
    true,
    sizeof(sensors_t)/sizeof(adcsample_t),
    sensors_cb,
    sensors_err_cb,
    ADC_REG_CFG
};

void sensors_init(void)
{
    ADC_ENABLE_SENSORS(&ADCD1);
    /* TODO: Use proper OD interface */
    OD_RAM.x2021_MCU_Calibration.TS_CAL1 = TS_CAL1_VAL;
    OD_RAM.x2021_MCU_Calibration.TS_CAL2 = TS_CAL2_VAL;
    OD_RAM.x2021_MCU_Calibration.VREFINT_CAL = VREFINT_CAL_VAL;
}

void sensors_start(void)
{
    adcAcquireBus(&ADCD1);
    adcStart(&ADCD1, NULL);
    /*adcStartConversion(&ADCD1, &adcgrpcfg, (adcsample_t*)sensors, sizeof(sensors)/sizeof(sensors_t));*/
    adcReleaseBus(&ADCD1);
}
