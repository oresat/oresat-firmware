#include "ch.h"
#include "hal.h"

#include "sensors.h"
#include "CANopen.h"

typedef struct {
    adcsample_t ts;
    adcsample_t vrefint;
} sensors_t;

sensors_t sensors;

static void sensors_cb(ADCDriver *adcp)
{
    sensors_t *sensors = (sensors_t*)adcp->samples;
    int16_t temperature;
    int16_t voltage;

    voltage = VREFINT_CAL_VOLT * VREFINT_CAL / sensors->vrefint;
    temperature = ((sensors->ts * VREFINT_CAL * 10 / sensors->vrefint) - TS_CAL1 * 10);
    temperature = temperature * (TS_CAL2_TEMP - TS_CAL1_TEMP) / (TS_CAL2 - TS_CAL1) + TS_CAL1_TEMP * 10;

    OD_sensors[ODA_sensors_MCU_Temperature] = sensors->ts;
    OD_sensors[ODA_sensors_MCU_VREFINT] = sensors->vrefint;
    OD_temperature[ODA_temperature_MCU_Junction] = temperature;
    OD_voltage[ODA_voltage_MCU_VDDA] = voltage;
}

static void sensors_err_cb(ADCDriver *adcp, adcerror_t err)
{
    (void)adcp;
    (void)err;
}

static ADCConversionGroup adcgrpcfg = {
    FALSE,
    sizeof(sensors_t)/sizeof(adcsample_t),
    sensors_cb,
    sensors_err_cb,
    ADC_REG_CFG
};

void sensors_init(void)
{
    adcStart(&ADCD1, NULL);
    ADC_ENABLE_SENSORS(&ADCD1);
    OD_calibration[ODA_calibration_TS_CAL1] = TS_CAL1;
    OD_calibration[ODA_calibration_TS_CAL2] = TS_CAL2;
    OD_calibration[ODA_calibration_VREFINT_CAL] = VREFINT_CAL;
}

void sensors_trig(void)
{
    adcAcquireBus(&ADCD1);
    adcStartConversion(&ADCD1, &adcgrpcfg, (adcsample_t*)(&sensors), sizeof(sensors)/sizeof(sensors_t));
    adcReleaseBus(&ADCD1);
}
