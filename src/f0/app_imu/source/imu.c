#include "imu.h"
#include "bmi088.h"

/* TODO: Set this to the correct slave address for the BMI088 device */
#define BMI088_SADDR 0x00U

static const I2CConfig i2ccfg = {
    STM32_TIMINGR_PRESC(0xBU) |
    STM32_TIMINGR_SCLDEL(0x4U) | STM32_TIMINGR_SDADEL(0x2U) |
    STM32_TIMINGR_SCLH(0xFU)  | STM32_TIMINGR_SCLL(0x13U),
    0,
    0
};

static const BMI088Config imucfg = {
    .i2cp = &I2CD1,
    .i2ccfg = &i2ccfg,
    .saddr = BMI088_SADDR,
};

static BMI088Driver imudev;

THD_WORKING_AREA(imu_wa, 0x400);
THD_FUNCTION(imu, arg)
{
    (void)arg;

    /* Initialize and start the BMI088 IMU sensor */
    bmi088ObjectInit(&imudev);
    bmi088Start(&imudev, &imucfg);

    while (!chThdShouldTerminateX()) {

        chThdSleepMilliseconds(250);
    }

    /* Stop the BMI088 IMU sensor */
    bmi088Stop(&imudev);

    chThdExit(MSG_OK);
}
