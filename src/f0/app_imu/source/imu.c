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

    /* Initialize and start the BMI088 IMU sensor */
    bmi088ObjectInit(&imudev);
    bmi088Start(&imudev, &imucfg);

	uint8_t bmi088_chip_id = 0;
#if 0
    if( (r = bmi088ReadChipId(&imudev, &bmi088_chip_id)) == MSG_OK ) {
		chprintf(CHP, "BMI088 accelerometer chip ID is 0x%X, expected to be 0x1E\r\n", bmi088_chip_id);
	} else {
		chprintf(CHP, "Failed to read chip ID from BMI088, r = %d\r\n", r);
	}
#endif

    //chprintf(CHP, "powering on acc . . .\r\n");
    //BMI088AccelerometerPowerOnOrOff(&imudev, BMI088_ON);
    //chThdSleepMilliseconds(50);
#if 0
    uint8_t power_status = readPowerCtrlReg(&imudev);
    chprintf(CHP, "power status is %u\r\n", power_status);


    chprintf(CHP, "setting acc mode to active . . .\r\n");
    BMI088AccelerometerEnableOrSuspend(&imudev, BMI088_MODE_ACTIVE);
#endif
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

#if 0
#if 1
		int32_t acc_x_mG = 0;
		int32_t acc_y_mG = 0;
		int32_t acc_z_mG = 0;
		if( bmi088ReadAccXYZ(&imudev, &acc_x_mG, &acc_y_mG, &acc_z_mG) == MSG_OK ) {
			chprintf(CHP, "Acc readings X = %d, Y = %d, Z = %d\r\n", acc_x_mG, acc_y_mG, acc_z_mG);
		} else {
			//FIXME handle error
			chprintf(CHP, "Failed to read accelerometer readings\r\n");
		}
#else

		int16_t acc_inx = bmi088ReadAccInX(&imudev);
		int16_t acc_iny = bmi088ReadAccInY(&imudev);
		int16_t acc_inz = bmi088ReadAccInZ(&imudev);
		chprintf(CHP, "Acc readings X = %d, Y = %d, Z = %d\r\n", acc_inx, acc_iny, acc_inz);
#endif
		chThdSleepMilliseconds(5);
#endif


#if 0
#if 1
		int32_t gyro_x = 0;
		int32_t gyro_y = 0;
		int32_t gyro_z = 0;
		if( bmi088ReadGyroXYZ(&imudev, &gyro_x, &gyro_y, &gyro_z) == MSG_OK ) {
			chprintf(CHP, "Gyro readings X = %d, Y = %d, Z = %d\r\n", gyro_x, gyro_y, gyro_z);

		} else {
			//FIXME handle error
			chprintf(CHP, "Failed to read gyro readings\r\n");
		}

#else
		uint8_t gyroscope_readings_byte_array[6];
		bmi088ObtainGyroscopesReadings(&imudev, gyroscope_readings_byte_array);
		chprintf(CHP, "gyro X rate %d\r\n", (int16_t)(gyroscope_readings_byte_array[0] + (gyroscope_readings_byte_array[1] << 8)));
		chprintf(CHP, "gyro Y rate %d\r\n", (int16_t)(gyroscope_readings_byte_array[2] + (gyroscope_readings_byte_array[3] << 8)));
		chprintf(CHP, "gyro Z rate %d\r\n", (int16_t)(gyroscope_readings_byte_array[4] + (gyroscope_readings_byte_array[5] << 8)));
#endif
#endif

#if 0
		int16_t acc_temperature = bmi088ReadTemp(&imudev);
		chprintf(CHP, "Accelerator temperature holds %d C\r\n", acc_temperature);
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

        //FIXME set all these CANOpen values to real numbers
        OD_gyroscope.pitchRate = 0;
        OD_gyroscope.yawRate = 0;
        OD_gyroscope.rollRate = 0;
        OD_gyroscope.pitchRateRaw = 0;
        OD_gyroscope.yawRateRaw = 0;
        OD_gyroscope.rollRateRaw = 0;

        OD_acceleration.x = 0;
        OD_acceleration.y = 0;
        OD_acceleration.z = 0;
        OD_acceleration.XRaw = 0;
        OD_acceleration.YRaw = 0;
        OD_acceleration.ZRaw = 0;

        OD_IMU_Temperature = 0;

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
