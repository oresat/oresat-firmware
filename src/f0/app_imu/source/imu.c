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
    uint8_t bmi088_gyro_chip_id = 0;
    uint8_t power_status = 0;
    uint8_t interrupt_status = 0;
    uint8_t acc_inx = 0;

    uint8_t gyroscope_readings_byte_array[6];

    /* Initialize and start the BMI088 IMU sensor */
    bmi088ObjectInit(&imudev);
    bmi088Start(&imudev, &imucfg);

// 2021-03-28 -
//    chThdSleepMilliseconds(50);
    bmi088_chip_id = bmi088ReadChipId(&imudev);
    chprintf(CHP, "BMI088 first read, accelerometer ID is %u\r\n", bmi088_chip_id);
    chThdSleepMilliseconds(10);

    chprintf(CHP, "powering on acc . . .\r\n");
    BMI088AccelerometerPowerOnOrOff(&imudev, BMI088_ON);

    chprintf(CHP, "setting acc mode to active . . .\r\n");
    BMI088AccelerometerEnableOrSuspend(&imudev, BMI088_MODE_ACTIVE);

    chprintf(CHP, "setting filter and output data rate . . .\r\n");
    BMI088AccelerometerSetFilterAndODR(&imudev, 0x88); // Per datasheet, 0x88 = 4-fold oversampling and 100Hz output data rate

    while (!chThdShouldTerminateX()) {
        iterations++;
        current_time = chVTGetSystemTime();

        if ((iterations % 10) == 0) {
            chprintf(CHP, "Test of IMU dev' code, loop iteration %u system time %u\r\n", iterations, (uint32_t)current_time);
        }

        if ((iterations % 10) == 0) {
#if ( 1 )
            bmi088_chip_id = bmi088ReadChipId(&imudev);
            chprintf(CHP, "BMI088 accelerometer ID is %u\r\n", bmi088_chip_id);
            chThdSleepMilliseconds(1);

            bmi088_gyro_chip_id = bmi088ReadGyrosChipId(&imudev);
            chprintf(CHP, "BMI088 gyroscope ID is %u\r\n", bmi088_gyro_chip_id);
            chThdSleepMilliseconds(1);

//            power_status = readPowerCtrlReg(&imudev);
//            chprintf(CHP, "power status is %u\r\n", power_status);
//            chThdSleepMilliseconds(5);

            interrupt_status = bmi088ReadIntStat(&imudev);
            chprintf(CHP, "interrupt status is %u\r\n", interrupt_status);
            chThdSleepMilliseconds(5);

            acc_inx = bmi088ReadAccInX(&imudev);
            chprintf(CHP, "InX reading is %u\r\n", acc_inx);
            chThdSleepMilliseconds(10);
#endif
            bmi088ObtainGyroscopesReadings(&imudev, gyroscope_readings_byte_array);
            chprintf(CHP, "gyro X rate %d\r\n", (gyroscope_readings_byte_array[0] + (gyroscope_readings_byte_array[1] << 8)));
            chprintf(CHP, "gyro Y rate %d\r\n", (gyroscope_readings_byte_array[2] + (gyroscope_readings_byte_array[3] << 8)));
            chprintf(CHP, "gyro Z rate %d\r\n", (gyroscope_readings_byte_array[4] + (gyroscope_readings_byte_array[5] << 8)));

            chprintf(CHP, "\r\n");
        }

        chThdSleepMilliseconds(250);
    }

    /* Stop the BMI088 IMU sensor */
    bmi088Stop(&imudev);

    chThdExit(MSG_OK);
}
