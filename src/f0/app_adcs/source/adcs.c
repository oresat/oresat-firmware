#include "adcs.h"

#include "bmi088.h"
#include "mmc5883ma.h"
#include "ltc4305.h"
#include "chprintf.h"
#include "CANopen.h"
#include "OD.h"

#include "hal.h"
#include "hal_pal.h"

#include "stdint.h"
#include "inttypes.h"


#define BMI088_GYRO_SADDR     0x68U
#define BMI088_ACC_SADDR      0x18U

#define DEBUG_SD    (BaseSequentialStream*) &SD2

#if 0
#define dbgprintf(str, ...)       chprintf((BaseSequentialStream*) &SD2, str, ##__VA_ARGS__)
#else
#define dbgprintf(str, ...)
#endif


//FIXME I believe MAX() is defined in some common C library???
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(a,b) (((a)<(b))?(a):(b))

#ifndef ABS
/// Returns the absolute value of <b>a</b>.
#define ABS(a) ((a) < 0 ? -(a) : (a))
#endif


#define ADC_NUM_CHANNELS           4
#define MY_SAMPLING_NUMBER         100
#define ADC_BUFF_SIZE              (ADC_NUM_CHANNELS * MY_SAMPLING_NUMBER)
static adcsample_t                 adc_sample_buff[ADC_BUFF_SIZE];
static adcsample_t                 adc_temp_sample_buff[ADC_BUFF_SIZE];

static float measured_i_sense_voltage[ADC_NUM_CHANNELS];;

//ADC_SMPR_SMP_1P5
//ADC_SMPR_SMP_7P5
//ADC_SMPR_SMP_13P5
//ADC_SMPR_SMP_71P5
//ADC_SMPR_SMP_239P5

static const ADCConversionGroup adcgrpcfg = {
  TRUE,                                             /* Enables the circular buffer mode for the group.  */
  ADC_NUM_CHANNELS,
  NULL,
  NULL,
  ADC_CFGR1_CONT | ADC_CFGR1_RES_12BIT,             /* CFGR1 */
  ADC_TR(0, 0),                                     /* TR */
  ADC_SMPR_SMP_71P5,                                /* SMPR */
  ADC_CHSELR_CHSEL0 | ADC_CHSELR_CHSEL5 | ADC_CHSELR_CHSEL6 | ADC_CHSELR_CHSEL7     /* CHSELR, note, for continuous conversion mode you must configure 1 or an even number of channels */
};


static const DACConfig dac_config = {
  .init         = 2047u,
  .datamode     = DAC_DHRM_12BIT_RIGHT,
  .cr           = 0
};



#define PWM_TIMER_FREQ	1000000 // Hz
#define PWM_FREQ		2500// periods per sec
#define PWM_PERIOD		PWM_TIMER_FREQ/PWM_FREQ


//FIXME these PWM channel mappings may be wrong? or the mod-wires on the dev board may be wrong. Either way, Z-axis in the firmware is controling X-axis magnetorquer in the hardware on the dev ADCS board
//PB13
#define MT_X_PWM_PWM_CHANNEL     (1 - 1)
//PB14
#define MT_Y_PWM_PWM_CHANNEL     (2 - 1)
//PB15
#define MT_Z_PWM_PWM_CHANNEL     (3 - 1)


static PWMConfig pwmcfg_1 = {
  PWM_TIMER_FREQ,
  PWM_PERIOD,
  NULL,
  {
   {PWM_OUTPUT_ACTIVE_LOW | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_LOW, NULL},
   {PWM_OUTPUT_ACTIVE_LOW | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_LOW, NULL},
   {PWM_OUTPUT_ACTIVE_LOW | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_LOW, NULL},
   {PWM_OUTPUT_ACTIVE_HIGH, NULL}
  },
  0,//CR2
 #if STM32_PWM_USE_ADVANCED
   0, //BDTR
 #endif
   0,//DIER
};



typedef enum {
    IMU_OD_ERROR_INFO_CODE_NONE = 0,
    IMU_OD_ERROR_INFO_CODE_IMU_COMM_FAILURE,
    IMU_OD_ERROR_INFO_CODE_ACCL_CHIP_ID_MISMATCH,
    IMU_OD_ERROR_INFO_CODE_GYRO_CHIP_ID_MISMATCH,
} imu_od_error_info_code_t;


typedef enum {
	EC_MAG_0_MZ_1 = 0,
	EC_MAG_1_MZ_2,
	EC_MAG_2_PZ_1,
	EC_MAG_3_PZ_2,
	EC_MAG_NONE,
} end_card_magnetometoer_t;



static const I2CConfig mmc5883ma_i2ccfg = {
    STM32_TIMINGR_PRESC(0xBU) |
    STM32_TIMINGR_SCLDEL(0x4U) | STM32_TIMINGR_SDADEL(0x2U) |
    STM32_TIMINGR_SCLH(0xFU)  | STM32_TIMINGR_SCLL(0x13U),
    0,
    0
};

static const MMC5883MAConfig mmc5883ma_generic_config = {
	.i2cp = &I2CD1,
	.i2ccfg = &mmc5883ma_i2ccfg
};



typedef struct {
	int32_t current_pwm_percent; //0-10000
	int32_t target_pwm_percent; //Negative values indicate the phase should be inverted
//	int32_t target_pwm_current_uA;  //Negative values indicate the phase should be inverted

	float current_feedback_min_V;
	float current_feedback_max_V;
	float current_feedback_measurement_V; //Volts, Note: this is the average voltage while the PWM output is high.
	int32_t current_feedback_measurement_uA; //uA. Note: this is the average current flowing while the PWM output is high. It does not represent overall average current.

	uint8_t phase_gpio_pin_number;
	uint8_t pwm_channel_number;

	systime_t last_update_time;
} mt_pwm_phase_data_t;

typedef struct {
	MMC5883MADriver driver;
	mmc5883ma_data_t data;
	volatile bool is_initialized;
} magnetometer_data_struct_t;

typedef struct  {
	mt_pwm_phase_data_t mt_pwm_data[3];

	magnetometer_data_struct_t magetometer_data[4];
} adcs_data_t;


adcs_data_t g_adcs_data;


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


int32_t saturate_int32_t(const int32_t v, const int32_t min, const int32_t max) {
	if (v >= max)
		return (max);

	else if (v <= min)
		return (min);

	return (v);
}

int16_t saturate_int16_t(const int32_t v) {
	if (v >= INT16_MAX)
		return (INT16_MAX);

	else if (v <= INT16_MIN)
		return (INT16_MIN);

	return (v);
}

/**
 * TODO more documentation
 * @return true if update process successful, false otherwise
 */
bool update_imu_data(void) {
	static systime_t last_imu_update_time = 0;

	systime_t now_time = chVTGetSystemTime();
	if( chTimeDiffX(last_imu_update_time, now_time) < 1000 ) {
		return(true);
	}
	last_imu_update_time = now_time;


    bool ret = true;
    if( imudev.state != BMI088_READY ) {
        return false;
    }

    //TODO Power up out of suspend
    //BMI088AccelerometerEnableOrSuspend(&imudev, BMI088_MODE_ACTIVE);
    //chThdSleepMilliseconds(10);


    bmi088_accelerometer_sample_t accl_data;
    if( bmi088ReadAccelerometerXYZmG(&imudev, &accl_data ) == MSG_OK ) {
        dbgprintf("Acc readings mG X = %d, Y = %d, Z = %d\r\n", accl_data.accl_x, accl_data.accl_y, accl_data.accl_z);
    } else {
        ret = false;
        dbgprintf("Failed to read accelerometer readings\r\n");
    }

    bmi088_gyro_sample_t gyro_sample;

    if( bmi088ReadGyroXYZ(&imudev, &gyro_sample) == MSG_OK ) {
        dbgprintf("Gyro readings X = %d, Y = %d, Z = %d\r\n", gyro_sample.gyro_x, gyro_sample.gyro_y, gyro_sample.gyro_z);
    } else {
        ret = false;
        dbgprintf("Failed to read gyro readings\r\n");
    }

    int16_t temp_c = 0;
    if( bmi088ReadTemp(&imudev, &temp_c) == MSG_OK ) {
        dbgprintf("Accelerator temp_c = %d C\r\n", temp_c);
    } else {
        ret = false;
        dbgprintf("Failed to read temperature data...\r\n");
    }

    dbgprintf("\r\n");

    //TODO re-suspend to save power
    //BMI088AccelerometerEnableOrSuspend(&imudev, BMI088_MODE_SUSPEND);


    OD_RAM.x6000_gyroscope.pitchRate = gyro_sample.gyro_x;
    OD_RAM.x6000_gyroscope.yawRate = gyro_sample.gyro_y;
    OD_RAM.x6000_gyroscope.rollRate = gyro_sample.gyro_z;
    OD_RAM.x6000_gyroscope.pitchRateRaw = gyro_sample.gyro_x_raw;
    OD_RAM.x6000_gyroscope.yawRateRaw = gyro_sample.gyro_y_raw;
    OD_RAM.x6000_gyroscope.rollRateRaw = gyro_sample.gyro_z_raw;

    OD_RAM.x6001_acceleration.accx = accl_data.accl_x;
    OD_RAM.x6001_acceleration.accy = accl_data.accl_y;
    OD_RAM.x6001_acceleration.accz = accl_data.accl_z;
    OD_RAM.x6001_acceleration.accXRaw = accl_data.accl_x_raw;
    OD_RAM.x6001_acceleration.accyRaw = accl_data.accl_y_raw;
    OD_RAM.x6001_acceleration.acczRaw = accl_data.accl_z_raw;

    OD_RAM.x6002_IMU_Temperature = temp_c;


    //FIXME confirm these units are usable and reasonable for higher level applications
    //Output current units are 100uA per LSB. int16 is +/- 32768. Yields a min/max representation of +/- 3.2 amps
    OD_RAM.x6007_magnetorquer.magnetorquerXCurrent = saturate_int16_t(g_adcs_data.mt_pwm_data[0].current_feedback_measurement_uA / 100);
    OD_RAM.x6007_magnetorquer.magnetorquerYCurrent = saturate_int16_t(g_adcs_data.mt_pwm_data[1].current_feedback_measurement_uA / 100);
    OD_RAM.x6007_magnetorquer.magnetorquerZCurrent = saturate_int16_t(g_adcs_data.mt_pwm_data[2].current_feedback_measurement_uA / 100);

    OD_RAM.x6007_magnetorquer.magnetorquerXPWM_DutyCycle = g_adcs_data.mt_pwm_data[0].current_pwm_percent;
    OD_RAM.x6007_magnetorquer.magnetorquerYPWM_DutyCycle = g_adcs_data.mt_pwm_data[1].current_pwm_percent;
    OD_RAM.x6007_magnetorquer.magnetorquerZPWM_DutyCycle = g_adcs_data.mt_pwm_data[2].current_pwm_percent;


    OD_RAM.x6003_magnetometerPZ1.magx = g_adcs_data.magetometer_data[EC_MAG_2_PZ_1].data.mx;
    OD_RAM.x6003_magnetometerPZ1.magy = g_adcs_data.magetometer_data[EC_MAG_2_PZ_1].data.my;
    OD_RAM.x6003_magnetometerPZ1.magz = g_adcs_data.magetometer_data[EC_MAG_2_PZ_1].data.mz;

    OD_RAM.x6004_magnetometerPZ2.magx = g_adcs_data.magetometer_data[EC_MAG_3_PZ_2].data.mx;
    OD_RAM.x6004_magnetometerPZ2.magy = g_adcs_data.magetometer_data[EC_MAG_3_PZ_2].data.my;
    OD_RAM.x6004_magnetometerPZ2.magz = g_adcs_data.magetometer_data[EC_MAG_3_PZ_2].data.mz;

    OD_RAM.x6005_magnetometerMZ1.magx = g_adcs_data.magetometer_data[EC_MAG_0_MZ_1].data.mx;
    OD_RAM.x6005_magnetometerMZ1.magy = g_adcs_data.magetometer_data[EC_MAG_0_MZ_1].data.my;
    OD_RAM.x6005_magnetometerMZ1.magz = g_adcs_data.magetometer_data[EC_MAG_0_MZ_1].data.mz;

    OD_RAM.x6006_magnetometerMZ2.magx = g_adcs_data.magetometer_data[EC_MAG_1_MZ_2].data.mx;
    OD_RAM.x6006_magnetometerMZ2.magy = g_adcs_data.magetometer_data[EC_MAG_1_MZ_2].data.my;
    OD_RAM.x6006_magnetometerMZ2.magz = g_adcs_data.magetometer_data[EC_MAG_1_MZ_2].data.mz;

    //FIXME add some kind of publication of eroror codes/states etc

    return ret;
}

bool connect_endcard_mmc5883ma(const uint8_t ltc4304_i2c_address, const bool conn_1_enable, const bool conn_2_enable) {
	bool ret = true;

	I2CDriver *i2cp = &I2CD1;

	i2cStart(i2cp, &i2ccfg);
	if( conn_1_enable ) {
		ret = ltc4305_set_connections(i2cp, ltc4304_i2c_address, true, false);
	} else if( conn_2_enable ) {
		ret = ltc4305_set_connections(i2cp, ltc4304_i2c_address, false, true);
	} else {
		ret = ltc4305_set_connections(i2cp, ltc4304_i2c_address, false, false);
	}

	i2cStop(i2cp);

	if( ! ret ) {
		chprintf(DEBUG_SD, "ERROR: Failed to set LTC4305 connections!\r\n");
	} else {
//		chprintf(DEBUG_SD, "SUCCESS: set LTC4305 connections!\r\n");
	}

	return(ret);
}



bool select_magnetometer(const end_card_magnetometoer_t ecm) {
//	chprintf(DEBUG_SD, "Selecting magnetometer %u\r\n", ecm);
	chThdSleepMilliseconds(10);

	bool ret1 = false;
	bool ret2 = false;

	if( ecm != EC_MAG_NONE ) {
		ret2 = connect_endcard_mmc5883ma(LTC_4035_PLUSZ_CARD_I2C_ADDRESS_WRITE, false, true);
		return(ret2);
	}

	switch(ecm) {
	case EC_MAG_0_MZ_1:
		ret1 = connect_endcard_mmc5883ma(LTC_4035_MINUSZ_CARD_I2C_ADDRESS_WRITE, true, false);
		ret2 = connect_endcard_mmc5883ma(LTC_4035_PLUSZ_CARD_I2C_ADDRESS_WRITE, false, false);
		break;
	case EC_MAG_1_MZ_2:
		ret1 = connect_endcard_mmc5883ma(LTC_4035_MINUSZ_CARD_I2C_ADDRESS_WRITE, false, true);
		ret2 = connect_endcard_mmc5883ma(LTC_4035_PLUSZ_CARD_I2C_ADDRESS_WRITE, false, false);
		break;
	case EC_MAG_2_PZ_1:
		ret1 = connect_endcard_mmc5883ma(LTC_4035_MINUSZ_CARD_I2C_ADDRESS_WRITE, false, false);
		ret2 = connect_endcard_mmc5883ma(LTC_4035_PLUSZ_CARD_I2C_ADDRESS_WRITE, true, false);
		break;
	case EC_MAG_3_PZ_2:
		ret1 = connect_endcard_mmc5883ma(LTC_4035_MINUSZ_CARD_I2C_ADDRESS_WRITE, false, false);
		ret2 = connect_endcard_mmc5883ma(LTC_4035_PLUSZ_CARD_I2C_ADDRESS_WRITE, false, true);
		break;
	case EC_MAG_NONE:
		ret1 = true;
		//ret1 = connect_endcard_mmc5883ma(LTC_4035_MINUSZ_CARD_I2C_ADDRESS_WRITE, false, false); FIXME uncomment this
		ret2 = connect_endcard_mmc5883ma(LTC_4035_PLUSZ_CARD_I2C_ADDRESS_WRITE, false, false);
		break;
	}


	if( ! (ret1 && ret2) ) {
		chprintf(DEBUG_SD, "ERROR: Failed to select magnetometers ret1=%d, ret2=%d\r\n", ret1, ret2);
	}

	return(ret1 && ret2);
}


bool select_and_read_magnetometer(const end_card_magnetometoer_t ecm) {
	bool r = false;

	if( ecm >= EC_MAG_NONE ) {
		return(false);
	}

	if( ! (g_adcs_data.magetometer_data[ecm].is_initialized) ) {
		chprintf(DEBUG_SD, "Magnetometer %d not initialized.\r\n", ecm);
		return(false);
	}

	if( ! select_magnetometer(ecm) ) {
		return(false);
	}


	chprintf(DEBUG_SD, "Reading from magnetometer %d: ", ecm);chThdSleepMilliseconds(5);

	r = mmc5883maReadData(&g_adcs_data.magetometer_data[ecm].driver, &g_adcs_data.magetometer_data[ecm].data);

	chprintf(DEBUG_SD, " mx=%d, my=%d, mz=%d\r\n", g_adcs_data.magetometer_data[ecm].data.mx,
			g_adcs_data.magetometer_data[ecm].data.my,
			g_adcs_data.magetometer_data[ecm].data.mz);

	select_magnetometer(EC_MAG_NONE);

	return(r);
}

bool update_endcard_magnetometer_readings(void) {
	static systime_t last_mag_update_time = 0;

	systime_t now_time = chVTGetSystemTime();
	if( chTimeDiffX(last_mag_update_time, now_time) < 500 ) { //Note: Default output rate for the MMC driver is 1hz, sample at 2X that
		return(true);
	}
	last_mag_update_time = now_time;


	bool ret = true;

	for(end_card_magnetometoer_t ecm = 0; ecm < EC_MAG_NONE; ecm++ ) {
//		chprintf(DEBUG_SD, "Reading EMC %u\r\n", ecm);
		select_and_read_magnetometer(ecm);
	}

	select_magnetometer(EC_MAG_NONE);

	return(ret);
}


bool init_end_cap_magnetometers(void) {
	palClearLine(LINE_MAG_N_EN);

	chThdSleepMilliseconds(5);

	bool ret = true;

	for(end_card_magnetometoer_t ecm = EC_MAG_0_MZ_1; ecm < EC_MAG_NONE; ecm++ ) {
		chprintf(DEBUG_SD, "Initing MMC %u\r\n", ecm);
		chThdSleepMilliseconds(5);

		mmc5883maObjectInit(&g_adcs_data.magetometer_data[ecm].driver);

		if( ! select_magnetometer(ecm) ) {
			ret = false;
			chprintf(DEBUG_SD, "Failed to start MMC4883MA number %u due to LTC selection error\r\n");
		} else {
			if( mmc5883maStart(&g_adcs_data.magetometer_data[ecm].driver, &mmc5883ma_generic_config) ) {
				chprintf(DEBUG_SD, "Successfully started MMC4883MA number %u\r\n", ecm);
				g_adcs_data.magetometer_data[ecm].is_initialized = true;
			} else {
				chprintf(DEBUG_SD, "Failed to start MMC4883MA number %u\r\n", ecm);
				ret = false;
			}
		}
	}

	select_magnetometer(EC_MAG_NONE);

	return(ret);
}



void set_pwm_output(void) {
	if( PWMD1.state == PWM_STOP ) {
		pwmStart(&PWMD1, &pwmcfg_1);
#if 0
		chprintf(DEBUG_SD, "Turning on PWM output...\r\n");
		pwmEnableChannel(&PWMD1, MT_X_PWM_PWM_CHANNEL, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 1000));
		pwmEnableChannel(&PWMD1, MT_Y_PWM_PWM_CHANNEL, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 1000));
		pwmEnableChannel(&PWMD1, MT_Z_PWM_PWM_CHANNEL, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 1000));
#endif
	}

#if 1
	for(int i = 0; i < 3; i++ ) {
		const systime_t now_time = chVTGetSystemTime();

		//Updates will come in periodically via CANOpen, this will apply those updates to the PWM outputs.
		if( g_adcs_data.mt_pwm_data[i].last_update_time == 0 || chTimeDiffX(g_adcs_data.mt_pwm_data[i].last_update_time, now_time) > 10 ) {
			if( g_adcs_data.mt_pwm_data[i].current_pwm_percent != g_adcs_data.mt_pwm_data[i].target_pwm_percent ) {
				chprintf(DEBUG_SD, "target_pwm_percent = %u\r\n", g_adcs_data.mt_pwm_data[i].target_pwm_percent);

				const int32_t pwm_val = ABS(g_adcs_data.mt_pwm_data[i].target_pwm_percent);
				pwmEnableChannel(&PWMD1, g_adcs_data.mt_pwm_data[i].pwm_channel_number, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, pwm_val));

				if( g_adcs_data.mt_pwm_data[i].target_pwm_percent < 0 ) {
					palSetPad(GPIOB, g_adcs_data.mt_pwm_data[i].phase_gpio_pin_number);
				} else {
					palClearPad(GPIOB, g_adcs_data.mt_pwm_data[i].phase_gpio_pin_number);
				}

				g_adcs_data.mt_pwm_data[i].current_pwm_percent = g_adcs_data.mt_pwm_data[i].target_pwm_percent;
				g_adcs_data.mt_pwm_data[i].last_update_time = now_time;
			}
		}
	}
#endif
}

int32_t map_current_uA_to_pwm_duty_cycle(const int32_t current_uA, const uint8_t axis) {
	int32_t ret = 0;
	if( axis <= 1 ) {
		//X and Y axes
		//1700 => 1000000 uA
		//500 => 295000 uA (this is hard/impossible to measure using the ADC
		ret = current_uA / (988000.0 / 1700.0);
		const int32_t pwm_duty_max_value = 1700;
		ret = saturate_int32_t(ret, -pwm_duty_max_value, pwm_duty_max_value);
	} else {
		//Z axis
		//1700 => 344000 uA
		//500 => 102000 uA  (this is hard/impossible to measure using the ADC
		ret = current_uA / (344000.0 / 1700.0);
		const int32_t pwm_duty_max_value = 4940;
		ret = saturate_int32_t(ret, -pwm_duty_max_value, pwm_duty_max_value);
	}

	return(ret);
}

void magnetorquer_handle_canopen(void) {
	g_adcs_data.mt_pwm_data[0].target_pwm_percent = map_current_uA_to_pwm_duty_cycle(OD_RAM.x6007_magnetorquer.setMagnetorquerXCurrent * 100, 0);
	g_adcs_data.mt_pwm_data[1].target_pwm_percent = map_current_uA_to_pwm_duty_cycle(OD_RAM.x6007_magnetorquer.setMagnetorquerYCurrent * 100, 1);
	g_adcs_data.mt_pwm_data[2].target_pwm_percent = map_current_uA_to_pwm_duty_cycle(OD_RAM.x6007_magnetorquer.setMagnetorquerZCurrent * 100, 2);
}


int32_t current_feedback_convert_volts_to_microamps(const float volts) {
	//Based on the circuit design, this should nominally be 3V/amp.
	//This calculation seems to be within 5%-10% accurate when compared to in line bench DMM readings.
	float microamps = (volts / 3.0) * 1000000.0;

	return(microamps);
}

void print_debug_output(void) {
	static systime_t last_print_time = 0;
	systime_t now_time = TIME_I2MS(chVTGetSystemTime());
	if (chTimeDiffX(last_print_time, now_time) > 750) {
		last_print_time = now_time;

		chprintf(DEBUG_SD, "================\r\n");
		chprintf(DEBUG_SD, "CANOpen Data:\r\n");
		chprintf(DEBUG_SD, "  OD_RAM.x6000_gyroscope.pitchRate = %d\r\n", OD_RAM.x6000_gyroscope.pitchRate);
		chprintf(DEBUG_SD, "  OD_RAM.x6000_gyroscope.yawRate = %d\r\n", OD_RAM.x6000_gyroscope.yawRate);
		chprintf(DEBUG_SD, "  OD_RAM.x6000_gyroscope.rollRate = %d\r\n", OD_RAM.x6000_gyroscope.rollRate);
		chprintf(DEBUG_SD, "  OD_RAM.x6000_gyroscope.pitchRateRaw = %d\r\n", OD_RAM.x6000_gyroscope.pitchRateRaw);
		chprintf(DEBUG_SD, "  OD_RAM.x6000_gyroscope.yawRateRaw = %d\r\n", OD_RAM.x6000_gyroscope.yawRateRaw);
		chprintf(DEBUG_SD, "  OD_RAM.x6000_gyroscope.rollRateRaw = %d\r\n", OD_RAM.x6000_gyroscope.rollRateRaw);

		chprintf(DEBUG_SD, "  OD_RAM.x6001_acceleration.accx = %d\r\n", OD_RAM.x6001_acceleration.accx);
		chprintf(DEBUG_SD, "  OD_RAM.x6001_acceleration.accy = %d\r\n", OD_RAM.x6001_acceleration.accy);
		chprintf(DEBUG_SD, "  OD_RAM.x6001_acceleration.accz = %d\r\n", OD_RAM.x6001_acceleration.accz);
		chprintf(DEBUG_SD, "  OD_RAM.x6001_acceleration.accXRaw = %d\r\n", OD_RAM.x6001_acceleration.accXRaw);
		chprintf(DEBUG_SD, "  OD_RAM.x6001_acceleration.accyRaw = %d\r\n", OD_RAM.x6001_acceleration.accyRaw);
		chprintf(DEBUG_SD, "  OD_RAM.x6001_acceleration.acczRaw = %d\r\n", OD_RAM.x6001_acceleration.acczRaw);

		chprintf(DEBUG_SD, "  OD_RAM.x6002_IMU_Temperature = %d\r\n", OD_RAM.x6002_IMU_Temperature);

		chprintf(DEBUG_SD, "  OD_RAM.x6007_magnetorquer.setMagnetorquerXCurrent = %d\r\n", OD_RAM.x6007_magnetorquer.setMagnetorquerXCurrent);
		chprintf(DEBUG_SD, "  OD_RAM.x6007_magnetorquer.setMagnetorquerYCurrent = %d\r\n", OD_RAM.x6007_magnetorquer.setMagnetorquerYCurrent);
		chprintf(DEBUG_SD, "  OD_RAM.x6007_magnetorquer.setMagnetorquerZCurrent = %d\r\n", OD_RAM.x6007_magnetorquer.setMagnetorquerZCurrent);

		chprintf(DEBUG_SD, "  OD_RAM.x6007_magnetorquer.magnetorquerXPWM_DutyCycle = %d\r\n", OD_RAM.x6007_magnetorquer.magnetorquerXPWM_DutyCycle);
		chprintf(DEBUG_SD, "  OD_RAM.x6007_magnetorquer.magnetorquerYPWM_DutyCycle = %d\r\n", OD_RAM.x6007_magnetorquer.magnetorquerYPWM_DutyCycle);
		chprintf(DEBUG_SD, "  OD_RAM.x6007_magnetorquer.magnetorquerZPWM_DutyCycle = %d\r\n", OD_RAM.x6007_magnetorquer.magnetorquerZPWM_DutyCycle);

		chprintf(DEBUG_SD, "  OD_RAM.x6007_magnetorquer.magnetorquerXCurrent = %d\r\n", OD_RAM.x6007_magnetorquer.magnetorquerXCurrent);
		chprintf(DEBUG_SD, "  OD_RAM.x6007_magnetorquer.magnetorquerYCurrent = %d\r\n", OD_RAM.x6007_magnetorquer.magnetorquerYCurrent);
		chprintf(DEBUG_SD, "  OD_RAM.x6007_magnetorquer.magnetorquerZCurrent = %d\r\n", OD_RAM.x6007_magnetorquer.magnetorquerZCurrent);

		chprintf(DEBUG_SD, "  OD_RAM.x6003_magnetometerPZ1.magx = %d\r\n", OD_RAM.x6003_magnetometerPZ1.magx);
		chprintf(DEBUG_SD, "  OD_RAM.x6003_magnetometerPZ1.magy = %d\r\n", OD_RAM.x6003_magnetometerPZ1.magy);
		chprintf(DEBUG_SD, "  OD_RAM.x6003_magnetometerPZ1.magz = %d\r\n", OD_RAM.x6003_magnetometerPZ1.magz);

		chprintf(DEBUG_SD, "  OD_RAM.x6004_magnetometerPZ2.magx = %d\r\n", OD_RAM.x6004_magnetometerPZ2.magx);
		chprintf(DEBUG_SD, "  OD_RAM.x6004_magnetometerPZ2.magy = %d\r\n", OD_RAM.x6004_magnetometerPZ2.magy);
		chprintf(DEBUG_SD, "  OD_RAM.x6004_magnetometerPZ2.magz = %d\r\n", OD_RAM.x6004_magnetometerPZ2.magz);

		chprintf(DEBUG_SD, "  OD_RAM.x6005_magnetometerMZ1.magx = %d\r\n", OD_RAM.x6005_magnetometerMZ1.magx);
		chprintf(DEBUG_SD, "  OD_RAM.x6005_magnetometerMZ1.magy = %d\r\n", OD_RAM.x6005_magnetometerMZ1.magy);
		chprintf(DEBUG_SD, "  OD_RAM.x6005_magnetometerMZ1.magz = %d\r\n", OD_RAM.x6005_magnetometerMZ1.magz);

		chprintf(DEBUG_SD, "  OD_RAM.x6006_magnetometerMZ2.magx = %d\r\n", OD_RAM.x6006_magnetometerMZ2.magx);
		chprintf(DEBUG_SD, "  OD_RAM.x6006_magnetometerMZ2.magy = %d\r\n", OD_RAM.x6006_magnetometerMZ2.magy);
		chprintf(DEBUG_SD, "  OD_RAM.x6006_magnetometerMZ2.magz = %d\r\n", OD_RAM.x6006_magnetometerMZ2.magz);



		for(int i = 0; i < 3; i++ ) {
			mt_pwm_phase_data_t *data = &g_adcs_data.mt_pwm_data[i];
			chprintf(DEBUG_SD, "  measured_i_sense_voltage[%d] = %d uA, %u mV, [%u - %u mV]\r\n",
							i,
							data->current_feedback_measurement_uA,
							(uint32_t) (data->current_feedback_measurement_V * 1000),
							(uint32_t) (data->current_feedback_min_V * 1000),
							(uint32_t) (data->current_feedback_max_V * 1000));
		}

	}
}

void read_adc_current(void) {
	/**
	 * 12 bit ADC readings from 0-4096
	 * Input voltage calculated as (<adc reading>/4096)*3.3
	 */

	/* Making mean of sampled values.*/
	memcpy(adc_temp_sample_buff, adc_sample_buff, sizeof(adc_sample_buff));

//	for(int s = 0; s < MY_SAMPLING_NUMBER; s++) {
//		chprintf(DEBUG_SD, "  adc_sample_buff[%d] = [", s);
//		for (int i = 0; i < ADC_NUM_CHANNELS; i++) {
//			chprintf(DEBUG_SD, "%d, ", adc_temp_sample_buff[i]);
//		}
//		chprintf(DEBUG_SD, "]\r\n");
//	}




#if ADC_NUM_CHANNELS == 4
	//Skip the first channel cuz we don't care about the data, just need 4 channels so the underlying ADC driver would actually work.
	int start_chan_idx = 1;
#else
#error "Handle this"
#endif

	for (int adc_chan_idx = start_chan_idx; adc_chan_idx < ADC_NUM_CHANNELS; adc_chan_idx++) {
		const float low_threshold_volts = 0.08;
		const uint32_t low_threshold_adc_reading = (4096.0 * low_threshold_volts);

		uint32_t number_samples_over_threshold = 0;
		uint32_t adc_reading_sum = 0;
		uint32_t min_adc_value = 4096;
		uint32_t max_adc_value = 0;
		for(int sample_num = 0; sample_num < MY_SAMPLING_NUMBER; sample_num++) {
			const uint32_t array_index = (sample_num * ADC_NUM_CHANNELS) + adc_chan_idx;
			const uint16_t adc_reading_value = adc_temp_sample_buff[array_index];

			if( adc_reading_value > low_threshold_adc_reading ) {
				number_samples_over_threshold++;
				adc_reading_sum += adc_reading_value;

				min_adc_value = MIN(min_adc_value, adc_reading_value);
				max_adc_value = MAX(max_adc_value, adc_reading_value);
			}
		}

		if( number_samples_over_threshold == 0 ) {
			min_adc_value = 0;
		}

		float adc_reading_mean_voltage = 0;
		if( number_samples_over_threshold > 5 ) {
			adc_reading_mean_voltage = 3.3 * ((float) adc_reading_sum / ((float) number_samples_over_threshold)) / 4096.0;
		}

		const uint32_t min_mV = (1000.0 * 3.3 * ((float) min_adc_value) / 4096.0);
		const uint32_t max_mV = (1000.0 * 3.3 * ((float) max_adc_value) / 4096.0);

		measured_i_sense_voltage[adc_chan_idx] = adc_reading_mean_voltage;
//		const uint32_t millivolts = adc_reading_mean_voltage * 1000.0;

//		if( do_print ) {
//			chprintf(DEBUG_SD, "  measured_i_sense_voltage[%d] = %u mV, %u, [%u - %u mV]\r\n",
//				adc_chan_idx, millivolts, number_samples_over_threshold, min_mV, max_mV);
//		}

		if( adc_chan_idx >= 1 && adc_chan_idx <= 3 ) {
			g_adcs_data.mt_pwm_data[adc_chan_idx - 1].current_feedback_measurement_V = measured_i_sense_voltage[adc_chan_idx];
			g_adcs_data.mt_pwm_data[adc_chan_idx - 1].current_feedback_measurement_uA = current_feedback_convert_volts_to_microamps(measured_i_sense_voltage[adc_chan_idx]);
			g_adcs_data.mt_pwm_data[adc_chan_idx - 1].current_feedback_min_V = min_mV / 1000.0;
			g_adcs_data.mt_pwm_data[adc_chan_idx - 1].current_feedback_max_V = max_mV / 1000.0;
		}
	}


	//Compute current sense data
	print_debug_output();

}

void process_magnetorquer(void) {
	magnetorquer_handle_canopen();
	set_pwm_output();
	read_adc_current();
}


void init_magnetorquer(void) {
	memset(&g_adcs_data.mt_pwm_data, 0, sizeof(g_adcs_data.mt_pwm_data));

	g_adcs_data.mt_pwm_data[0].phase_gpio_pin_number = GPIOB_MT_X_PHASE;
	g_adcs_data.mt_pwm_data[0].pwm_channel_number = MT_X_PWM_PWM_CHANNEL;

	g_adcs_data.mt_pwm_data[1].phase_gpio_pin_number = GPIOB_MT_Y_PHASE;
	g_adcs_data.mt_pwm_data[1].pwm_channel_number = MT_Y_PWM_PWM_CHANNEL;

	g_adcs_data.mt_pwm_data[2].phase_gpio_pin_number = GPIOB_MT_Z_PHASE;
	g_adcs_data.mt_pwm_data[2].pwm_channel_number = MT_Z_PWM_PWM_CHANNEL;

	for(int i = 0; i < 3; i++ ) {
		palSetPad(GPIOB, g_adcs_data.mt_pwm_data[i].phase_gpio_pin_number);
	}



	palSetPadMode(GPIOA, GPIOA_MT_ILIM, PAL_MODE_INPUT_ANALOG);
	dacStart(&DACD1, &dac_config);
//	dacPutChannelX(&DACD1, 0, 650); //0.44V
	dacPutChannelX(&DACD1, 0, 3600); //3V

//	palSetPad(GPIOA, GPIOA_MT_STBY_RST);
//	palSetPad(GPIOB, GPIOB_MT_EN);



	palClearPad(GPIOB, GPIOB_MT_EN);
	palSetPad(GPIOA, GPIOA_MT_STBY_RST);

	palClearPad(GPIOB, GPIOB_MT_X_PWM);
	palClearPad(GPIOB, GPIOB_MT_Y_PWM);
	palClearPad(GPIOB, GPIOB_MT_Z_PWM);

	palClearPad(GPIOB, GPIOB_MT_X_PHASE);
	palClearPad(GPIOB, GPIOB_MT_Y_PHASE);
	palClearPad(GPIOB, GPIOB_MT_Z_PHASE);


	palClearPad(GPIOA, GPIOA_MT_STBY_RST);
	chThdSleepMilliseconds(5);
	palSetPad(GPIOB, GPIOB_MT_EN);
	chThdSleepMilliseconds(5);
	palSetPad(GPIOA, GPIOA_MT_STBY_RST);
	chThdSleepMilliseconds(5);
}


THD_WORKING_AREA(adcs_wa, 0x800);
THD_FUNCTION(adcs, arg)
{
    (void) arg;
    msg_t r;

    chprintf(DEBUG_SD, "Starting ADCS thread...\r\n");
    chThdSleepMilliseconds(50);


	init_end_cap_magnetometers();
    init_magnetorquer();

    /* Activates the ADC1 driver. */
    adcStart(&ADCD1, NULL);
    adcStartConversion(&ADCD1, &adcgrpcfg, adc_sample_buff, ADC_BUFF_SIZE);//Starts an ADC continuous conversion.
    chprintf(DEBUG_SD, "done with adcStartConversion()...\r\n");


    OD_RAM.x6007_magnetorquer.setMagnetorquerXCurrent = 3000;//FIXME remove this, this is just for testing
    OD_RAM.x6007_magnetorquer.setMagnetorquerYCurrent = 4000;
    OD_RAM.x6007_magnetorquer.setMagnetorquerZCurrent = 5000;


    bmi088ObjectInit(&imudev);

    chprintf(DEBUG_SD, "Starting BMI088...\r\n");
    chThdSleepMilliseconds(50);
    bmi088Start(&imudev, &imucfg);



    chprintf(DEBUG_SD, "BMI088 state = %u, error_flags=0x%X\r\n", imudev.state, imudev.error_flags);
    if( imudev.state != BMI088_READY ) {
        chprintf(DEBUG_SD, "Failed to start IMU driver...\r\n");
    } else {
        uint8_t bmi088_chip_id = 0;
        if( (r = bmi088ReadAccelerometerChipId(&imudev, &bmi088_chip_id)) == MSG_OK ) {
            chprintf(DEBUG_SD, "BMI088 accelerometer chip ID is 0x%X, expected to be 0x%X\r\n", bmi088_chip_id, BMI088_ACC_CHIP_ID_EXPECTED);
        } else {
            chprintf(DEBUG_SD, "Failed to read accl chip ID from BMI088 ACCEL, r = %d\r\n", r);
        }

        if( bmi088_chip_id != BMI088_ACC_CHIP_ID_EXPECTED ) {
        	chprintf(DEBUG_SD, "BMI088 ACCEL FAIL: didnt find BMI088!\r\n");
            //CO_errorReport(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_HARDWARE, IMU_OD_ERROR_INFO_CODE_ACCL_CHIP_ID_MISMATCH);
        } else {
        	chprintf(DEBUG_SD, "BMI088 ACCEL SUCCESS: found BMI088!\r\n");
        }


        int16_t temp_c = 0;
        bmi088ReadTemp(&imudev, &temp_c);
        chprintf(DEBUG_SD, "Read temperature as %u\r\n", temp_c);



        uint8_t bmi088_gyro_chip_id = 0;
        msg_t r = bmi088ReadGyroChipId(&imudev, &bmi088_gyro_chip_id);
        if( r == MSG_OK ) {
            chprintf(DEBUG_SD, "BMI088 gyroscope ID is 0x%X, expected to be 0x%X\r\n", bmi088_gyro_chip_id, BMI088_GYR_CHIP_ID_EXPECTED);
        } else {
            chprintf(DEBUG_SD, "Failed to read gyro chip ID from BMI088 GYRO, r = %d\r\n", r);
        }

        if( bmi088_gyro_chip_id != BMI088_GYR_CHIP_ID_EXPECTED ) {
        	chprintf(DEBUG_SD, "BMI088 GYRO FAIL: didnt find BMI088!\r\n");
            //CO_errorReport(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_HARDWARE, IMU_OD_ERROR_INFO_CODE_GYRO_CHIP_ID_MISMATCH);
        } else {
        	chprintf(DEBUG_SD, "BMI088 GYRO SUCCESS: found BMI088!\r\n");
        }

    }
    chprintf(DEBUG_SD, "Done initializing, starting loop...\r\n");

    for (uint32_t iterations = 0; !chThdShouldTerminateX(); iterations++) {
        dbgprintf("IMU loop iteration %u system time %u\r\n", iterations, (uint32_t)chVTGetSystemTime());

        update_imu_data();//FIXME add error handling
        update_endcard_magnetometer_readings();//FIXME add error handling
        process_magnetorquer();//FIXME add error handling

/*
        if( update_imu_data() ) {

            if( CO_isError(CO->em, CO_EM_GENERIC_ERROR) ) {
                dbgprintf("Clearing CO error state...\r\n");
                //CO_errorReset(CO->em, CO_EM_GENERIC_ERROR, IMU_OD_ERROR_INFO_CODE_NONE);

            }
        } else {
            dbgprintf("Setting CO error state...\r\n");
            //CO_errorReport(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_COMMUNICATION, IMU_OD_ERROR_INFO_CODE_IMU_COMM_FAILURE);

	}
*/
        chThdSleepMilliseconds(5);
    }

    /* Stop the BMI088 IMU sensor */
    bmi088Stop(&imudev);

    chThdExit(MSG_OK);
}
