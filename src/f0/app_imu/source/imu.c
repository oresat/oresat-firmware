#include "imu.h"
#include "bmi088.h"
#include "chprintf.h"

/* TODO: Set this to the correct slave address for the BMI088 device */
//#define BMI088_GYRO_SADDR 0x68U
//#define BMI088_ACC_SADDR 0x18U


#define CHP ((BaseSequentialStream*)&SD2)

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
    .gyro_saddr = BMI088_GYRO_SADDR,
    .acc_saddr = BMI088_ACC_SADDR,
};

static BMI088Driver imudev;

THD_WORKING_AREA(imu_wa, 0x400);
THD_FUNCTION(imu, arg)
{
    (void)arg;

// 2021-03-24 - dev work de TMH:
    uint32_t iterations = 0;
    systime_t current_time = 0;
    uint8_t bmi088_chip_id = 0;
    uint8_t power_status = 0;
    uint8_t interrupt_status = 0;


    /* Initialize and start the BMI088 IMU sensor */
    bmi088ObjectInit(&imudev);
    bmi088Start(&imudev, &imucfg);

    chThdSleepMilliseconds(50);

//    accEnable(&imudev, 0x04);  // start accelerometer, per BMI088 datasheet page 34, covers register 0x7D

    while (!chThdShouldTerminateX()) {
        iterations++;
        current_time = chVTGetSystemTime();

        if ((iterations % 10) == 0) {
            chprintf(CHP, "Test of IMU dev' code, loop iteration %u system time %u\r\n", iterations, (uint32_t)current_time);
        }

        if ((iterations % 10) == 0) {
            bmi088_chip_id = bmi088ReadChipId(&imudev);
            chprintf(CHP, "BMI088 ID is %u\r\n", bmi088_chip_id);
            power_status = readPwrCtrlReg(&imudev);
            chprintf(CHP, "power status is %u\r\n", power_status);

            interrupt_status = bmi088ReadIntStat(&imudev);
            chprintf(CHP, "interrupt status is %u\r\n", interrupt_status);
        }

        chThdSleepMilliseconds(250);
    }

    /* Stop the BMI088 IMU sensor */
    bmi088Stop(&imudev);

    chThdExit(MSG_OK);
}
