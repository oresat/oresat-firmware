#include "imu.h"
#include "bmi088.h"
#include "chprintf.h"
#include "CANopen.h"

#define CHP ((BaseSequentialStream*) &SD2)

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
    (void) arg;
    msg_t r;

    chprintf(CHP, "Starting IMU thread...\r\n");
    chThdSleepMilliseconds(50);

    /* Initialize and start the BMI088 IMU sensor */
    bmi088ObjectInit(&imudev);
    chprintf(CHP, "%s(%u)\r\n", __FILE__, __LINE__);

    bmi088Start(&imudev, &imucfg);
    chprintf(CHP, "%s(%u)\r\n", __FILE__, __LINE__);
    chprintf(CHP, "state = %u\r\n", imudev.state);

	uint8_t bmi088_chip_id = 0;
#if 0
    if( (r = bmi088ReadChipId(&imudev, &bmi088_chip_id)) == MSG_OK ) {
		chprintf(CHP, "BMI088 accelerometer chip ID is 0x%X, expected to be 0x1E\r\n", bmi088_chip_id);
	} else {
		chprintf(CHP, "Failed to read chip ID from BMI088, r = %d\r\n", r);
	}
#endif

    chprintf(CHP, "%s(%u)\r\n", __FILE__, __LINE__);

    //chprintf(CHP, "powering on acc . . .\r\n");
    //BMI088AccelerometerPowerOnOrOff(&imudev, BMI088_ON);
    //chThdSleepMilliseconds(50);
#if 0
    uint8_t power_status = readPowerCtrlReg(&imudev);
    chprintf(CHP, "power status is %u\r\n", power_status);


    chprintf(CHP, "setting acc mode to active . . .\r\n");
    BMI088AccelerometerEnableOrSuspend(&imudev, BMI088_MODE_ACTIVE);
#endif

    chprintf(CHP, "%s(%u)\r\n", __FILE__, __LINE__);

    //chprintf(CHP, "setting filter and output data rate . . .\r\n");
    //BMI088AccelerometerSetFilterAndODR(&imudev, 0x88); // Per datasheet, 0x88 = 4-fold oversampling and 100Hz output data rate

    //chprintf(CHP, "enabling positive acc' self test . . .\r\n");
    //BMI088AccelerometerSetSelfTestMode(&imudev, 0x0D);

    for (uint32_t iterations = 0; !chThdShouldTerminateX(); iterations++) {
        chprintf(CHP, "Test of IMU dev' code, loop iteration %u system time %u\r\n", iterations, (uint32_t)chVTGetSystemTime());

#if 0
//            chprintf(CHP, "powering on accelerometer again . . .\r\n");
//            BMI088AccelerometerPowerOnOrOff(&imudev, BMI088_ON);
//            chThdSleepMilliseconds(5);

		power_status = readPowerCtrlReg(&imudev);
		chprintf(CHP, "power control register = 0X%X\r\n", power_status);
		chThdSleepMilliseconds(5);

		uint8_t acc_mode_conf = readPowerConfReg(&imudev);
		chprintf(CHP, "mode config register = 0x%X\r\n", acc_mode_conf);
		chThdSleepMilliseconds(5);
#endif

#if 1
		if( (r = bmi088ReadChipId(&imudev, &bmi088_chip_id)) == MSG_OK ) {
			chprintf(CHP, "BMI088 accelerometer chip ID is 0x%X, expected to be 0x%X\r\n", bmi088_chip_id, BMI088_ACCL_EXPECTED_CHIP_ID);
		} else {
			chprintf(CHP, "Failed to read accl chip ID from BMI088, r = %d\r\n", r);
		}
		chThdSleepMilliseconds(10);
#endif

#if 1
		// 11010000
		uint8_t bmi088_gyro_chip_id = 0;
		msg_t r = bmi088ReadGyrosChipId(&imudev, &bmi088_gyro_chip_id);
		if( r == MSG_OK ) {
			chprintf(CHP, "BMI088 gyroscope ID is 0x%X, expected to be 0x%X\r\n", bmi088_gyro_chip_id, BMI088_GYRO_EXPECTED_CHIP_ID);
		} else {
			chprintf(CHP, "Failed to read gyro chip ID from BMI088, r = %d\r\n", r);

		}
		chThdSleepMilliseconds(10);
#endif

//            interrupt_status = bmi088ReadIntStat(&imudev);
//            chprintf(CHP, "interrupt status is %u\r\n", interrupt_status);
//            chThdSleepMilliseconds(5);

//            error_acc = bmi088ReadErrCode(&imudev);
//            chprintf(CHP, "error code from BMI088 = %u\r\n", error_acc);
//            chThdSleepMilliseconds(10);

		int32_t acc_x_mS2 = 0;
		int32_t acc_y_mS2 = 0;
		int32_t acc_z_mS2 = 0;
		uint16_t acc_x_raw = 0;
		uint16_t acc_y_raw = 0;
		uint16_t acc_z_raw = 0;

#if 0
		if( bmi088ReadAccXYZmS2(&imudev, &acc_x_mS2, &acc_y_mS2, &acc_z_mS2, &acc_x_raw, &acc_y_raw, &acc_z_raw) == MSG_OK ) {
			chprintf(CHP, "Acc readings m/s^2 X = %d, Y = %d, Z = %d\r\n", acc_x_mS2, acc_y_mS2, acc_z_mS2);
		} else {
			//FIXME handle error
			chprintf(CHP, "Failed to read accelerometer readings\r\n");
		}

		int32_t acc_x_mG = 0;
		int32_t acc_y_mG = 0;
		int32_t acc_z_mG = 0;
		if( bmi088ReadAccXYZmG(&imudev, &acc_x_mG, &acc_y_mG, &acc_z_mG) == MSG_OK ) {
			chprintf(CHP, "Acc readings mG X = %d, Y = %d, Z = %d\r\n", acc_x_mG, acc_y_mG, acc_z_mG);
		} else {
			//FIXME handle error
			chprintf(CHP, "Failed to read accelerometer readings\r\n");
		}
		chThdSleepMilliseconds(5);
#endif


		int32_t gyro_x = 0;
		int32_t gyro_y = 0;
		int32_t gyro_z = 0;
		uint16_t gyro_x_raw = 0;
		uint16_t gyro_y_raw = 0;
		uint16_t gyro_z_raw = 0;
#if 0
		if( bmi088ReadGyroXYZ(&imudev, &gyro_x, &gyro_y, &gyro_z, &gyro_x_raw, &gyro_y_raw, &gyro_z_raw) == MSG_OK ) {
			chprintf(CHP, "Gyro readings X = %d, Y = %d, Z = %d\r\n", gyro_x, gyro_y, gyro_z);

		} else {
			//FIXME handle error
			chprintf(CHP, "Failed to read gyro readings\r\n");
		}
#endif

		int16_t temp_c = 0;
#if 0
		if( bmi088ReadTemp(&imudev, &temp_c) == MSG_OK ) {
			chprintf(CHP, "Accelerator temp_c = %d C\r\n", temp_c);
		} else {
			chprintf(CHP, "Failed to read temperature data...\r\n");
		}
		chThdSleepMilliseconds(5);
#endif


//            chprintf(CHP, "powering on accelerometer again . . .\r\n");
//            BMI088AccelerometerPowerOnOrOff(&imudev, BMI088_ON);
//
//            power_status = readPowerCtrlReg(&imudev);
//            chprintf(CHP, "power status is %u\r\n", power_status);
//            chThdSleepMilliseconds(5);

#if 0
		uint8_t acc_mode_conf = readPowerConfReg(&imudev);
		if ( acc_mode_conf == BMI088_MODE_SUSPEND )
		{
			chprintf(CHP, "---- setting accelerator mode active . . .\r\n");
			BMI088AccelerometerEnableOrSuspend(&imudev, BMI088_MODE_ACTIVE);
		}
		else
		{
			chprintf(CHP, "---- setting accelerator mode to suspend . . .\r\n");
			BMI088AccelerometerEnableOrSuspend(&imudev, BMI088_MODE_SUSPEND);
		}
#endif

        chprintf(CHP, "\r\n");

        OD_gyroscope.pitchRate = gyro_x;
        OD_gyroscope.yawRate = gyro_y;
        OD_gyroscope.rollRate = gyro_z;
        OD_gyroscope.pitchRateRaw = gyro_x_raw;
        OD_gyroscope.yawRateRaw = gyro_y_raw;
        OD_gyroscope.rollRateRaw = gyro_z_raw;

        OD_acceleration.x = acc_x_mS2;
        OD_acceleration.y = acc_y_mS2;
        OD_acceleration.z = acc_z_mS2;
        OD_acceleration.XRaw = acc_x_raw;
        OD_acceleration.YRaw = acc_y_raw;
        OD_acceleration.ZRaw = acc_z_raw;

        OD_IMU_Temperature = temp_c;

        //TODO Impliment magnetometer driver and populate this info
        OD_magnetometerPZ1.x = 0;
        OD_magnetometerPZ1.y = 0;
        OD_magnetometerPZ1.z = 0;

        OD_magnetometerPZ2.x = 0;
        OD_magnetometerPZ2.y = 0;
        OD_magnetometerPZ2.z = 0;

        OD_magnetometerMZ1.x = 0;
        OD_magnetometerMZ1.y = 0;
        OD_magnetometerMZ1.z = 0;

        OD_magnetometerMZ2.x = 0;
        OD_magnetometerMZ2.y = 0;
        OD_magnetometerMZ2.z = 0;


        chThdSleepMilliseconds(1000);
    }

    /* Stop the BMI088 IMU sensor */
    bmi088Stop(&imudev);

    chThdExit(MSG_OK);
}
