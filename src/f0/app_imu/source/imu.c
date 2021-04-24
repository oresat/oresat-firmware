#include "imu.h"
#include "bmi088.h"
#include "chprintf.h"
#include "CANopen.h"

#define BMI088_GYRO_SADDR 0x68U
#define BMI088_ACC_SADDR 0x18U

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


void update_imu_data(void) {
	if( imudev.state != BMI088_READY ) {
		return;
	}

	//TODO Power up out of suspend
	//BMI088AccelerometerEnableOrSuspend(&imudev, BMI088_MODE_ACTIVE);
	//chThdSleepMilliseconds(10);


	bmi088_accelerometer_sample_t accl_data;
	if( bmi088ReadAccelerometerXYZmG(&imudev, &accl_data ) == MSG_OK ) {
		chprintf(CHP, "Acc readings mG X = %d, Y = %d, Z = %d\r\n", accl_data.accl_x, accl_data.accl_y, accl_data.accl_z);
	} else {
		//FIXME handle error
		chprintf(CHP, "Failed to read accelerometer readings\r\n");
	}

	bmi088_gyro_sample_t gyro_sample;

	if( bmi088ReadGyroXYZ(&imudev, &gyro_sample) == MSG_OK ) {
		chprintf(CHP, "Gyro readings X = %d, Y = %d, Z = %d\r\n", gyro_sample.gyro_x, gyro_sample.gyro_y, gyro_sample.gyro_z);

	} else {
		//FIXME handle error
		chprintf(CHP, "Failed to read gyro readings\r\n");
	}

	int16_t temp_c = 0;
	if( bmi088ReadTemp(&imudev, &temp_c) == MSG_OK ) {
		chprintf(CHP, "Accelerator temp_c = %d C\r\n", temp_c);
	} else {
		chprintf(CHP, "Failed to read temperature data...\r\n");
	}

	chprintf(CHP, "\r\n");

	//TODO re-suspend to save power
	//BMI088AccelerometerEnableOrSuspend(&imudev, BMI088_MODE_SUSPEND);


	OD_gyroscope.pitchRate = gyro_sample.gyro_x;
	OD_gyroscope.yawRate = gyro_sample.gyro_y;
	OD_gyroscope.rollRate = gyro_sample.gyro_z;
	OD_gyroscope.pitchRateRaw = gyro_sample.gyro_x_raw;
	OD_gyroscope.yawRateRaw = gyro_sample.gyro_y_raw;
	OD_gyroscope.rollRateRaw = gyro_sample.gyro_z_raw;

	OD_acceleration.x = accl_data.accl_x;
	OD_acceleration.y = accl_data.accl_y;
	OD_acceleration.z = accl_data.accl_z;
	OD_acceleration.XRaw = accl_data.accl_x_raw;
	OD_acceleration.YRaw = accl_data.accl_y_raw;
	OD_acceleration.ZRaw = accl_data.accl_z_raw;

	OD_IMU_Temperature = temp_c;

	//TODO Implement magnetometer driver and populate this info
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
}



THD_WORKING_AREA(imu_wa, 0x400);
THD_FUNCTION(imu, arg)
{
    (void) arg;
    msg_t r;

    chprintf(CHP, "Starting IMU thread...\r\n");
    chThdSleepMilliseconds(50);

    /* Initialize and start the BMI088 IMU sensor */
    bmi088ObjectInit(&imudev);

    bmi088Start(&imudev, &imucfg);
    chprintf(CHP, "state = %u\r\n", imudev.state);
    if( imudev.state != BMI088_READY ) {
    	chprintf(CHP, "Failed to start IMU driver...\r\n");
    } else {
		uint8_t bmi088_chip_id = 0;
		if( (r = bmi088ReadAccelerometerChipId(&imudev, &bmi088_chip_id)) == MSG_OK ) {
			chprintf(CHP, "BMI088 accelerometer chip ID is 0x%X, expected to be 0x%X\r\n", bmi088_chip_id, BMI088_ACC_CHIP_ID_EXPECTED);
		} else {
			chprintf(CHP, "Failed to read accl chip ID from BMI088, r = %d\r\n", r);
		}

		uint8_t bmi088_gyro_chip_id = 0;
		msg_t r = bmi088ReadGyroChipId(&imudev, &bmi088_gyro_chip_id);
		if( r == MSG_OK ) {
			chprintf(CHP, "BMI088 gyroscope ID is 0x%X, expected to be 0x%X\r\n", bmi088_gyro_chip_id, BMI088_GYR_CHIP_ID_EXPECTED);
		} else {
			chprintf(CHP, "Failed to read gyro chip ID from BMI088, r = %d\r\n", r);

		}
    }

    for (uint32_t iterations = 0; !chThdShouldTerminateX(); iterations++) {
    	chprintf(CHP, "====================================\r\n");
        chprintf(CHP, "IMU loop iteration %u system time %u\r\n", iterations, (uint32_t)chVTGetSystemTime());
        update_imu_data();
        chThdSleepMilliseconds(1000);
    }

    /* Stop the BMI088 IMU sensor */
    bmi088Stop(&imudev);

    chThdExit(MSG_OK);
}
