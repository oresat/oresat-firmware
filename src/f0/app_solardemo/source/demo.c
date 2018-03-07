#include "demo.h"

const  uint8_t           LTC2990_I2C_ADDR   =    0b1001100;
static ltc2990_data      monitor_data;
static solar_v1_p        params;

// Example blinker thread
THD_WORKING_AREA(demo_measure_wa, 128);
THD_FUNCTION(demo_measure, arg) {

    i2cflags_t           i2c_errors  = 0x0;
    volatile uint8_t     regval      = 0xf;

    (void)arg;
    chRegSetThreadName("demo_measure");

    regval = 0xf;

    /* CONTROL Setup */
    regval = LTC2990_CONTROL_ACQ_SINGLE
             | LTC2990_CONTROL_ALL_MODE_4_3
             | LTC2990_CONTROL_MODE_1_2_0;

    while (!chThdShouldTerminateX()) {
        /* TRIGGER */
        regval = 0xf;
        ltc2990_writereg(LTC2990_TRIGGER, regval, &i2c_errors);
        chThdSleepMilliseconds(LTC2990_TRIGGER_WAIT_MS);

        regval = ltc2990_readreg(LTC2990_CONTROL, &i2c_errors);

        /* CONTROL check status */
        if(!ltc2990_conversion_done(regval))
        {
            chThdSleepS(TIME_S2I(1));
        }
        else
        {
            /* READ ALL */
            ltc2990_read_all(&monitor_data, &i2c_errors);

            /* TINT */
            ltc2990_error derror;
            params.tint = ltc2990_calc_tint(&monitor_data, &derror);
            /* VCC */
            params.vcc = ltc2990_calc_vcc(&monitor_data, &derror );
            /* Current */
            params.current = solar_v1_calc_current(&monitor_data, &derror);
            /* External Temp */
            params.temp_ext    = solar_v1_calc_temp(&monitor_data, &derror) ;
        }

        chThdSleepMilliseconds(1000);
    }
}
