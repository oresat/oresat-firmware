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


#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(a,b) (((a)<(b))?(a):(b))

#ifndef ABS
/// Returns the absolute value of <b>a</b>.
#define ABS(a) ((a) < 0 ? -(a) : (a))
#endif


#define ADC_NUM_CHANNELS           4
#define MY_SAMPLING_NUMBER         32
#define ADC_BUFF_SIZE              (ADC_NUM_CHANNELS * MY_SAMPLING_NUMBER)
static adcsample_t                 adc_sample_buff[ADC_BUFF_SIZE];

static float measured_i_sense_voltage[ADC_NUM_CHANNELS];;

/*
 * Context references for ADC conversion triggered by TIM1
 * http://forum.chibios.org/viewtopic.php?t=2254
 * https://forum.chibios.org/viewtopic.php?t=6036
 * https://forum.chibios.org/viewtopic.php?t=2093
 */


//ADC_SMPR_SMP_1P5
//ADC_SMPR_SMP_7P5
//ADC_SMPR_SMP_13P5
//ADC_SMPR_SMP_71P5
//ADC_SMPR_SMP_239P5


//volatile uint32_t adc_conversion_complete_callback_count = 0;
//void adc_conversion_complete_callback(ADCDriver *adcp) {
//	adc_conversion_complete_callback_count++;
//}


/**
 * This ADC is configured to trigger a single batch of ADC conversions based on the risigion edge of TRIGO from TIM1
 */
static const ADCConversionGroup adcgrpcfg_tim1_trigo = {
  .circular = FALSE,                                             /* Enables the circular buffer mode for the group.  */
  .num_channels = ADC_NUM_CHANNELS,
  .end_cb = NULL,
  .error_cb = NULL,
  .cfgr1 = ADC_CFGR1_RES_12BIT | ADC_CFGR1_EXTEN_RISING, /* CFGR1 */
  .tr = ADC_TR(0, 0),                                    /* TR */
  .smpr = ADC_SMPR_SMP_1P5,                             /* SMPR */
  .chselr = ADC_CHSELR_CHSEL0 | ADC_CHSELR_CHSEL5 | ADC_CHSELR_CHSEL6 | ADC_CHSELR_CHSEL7     /* CHSELR, note, for continuous conversion mode you must configure 1 or an even number of channels */
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

/**
 * This PWM block is configured to enable the TRIGO output to start an ADC conversion batch when the PWM edge goes high.
 */
static PWMConfig pwmcfg_1_trigo = {
  .frequency = PWM_TIMER_FREQ,
  .period = PWM_PERIOD,
  .callback = NULL,
  .channels = {
   {PWM_OUTPUT_ACTIVE_LOW | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_LOW, NULL},
   {PWM_OUTPUT_ACTIVE_LOW | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_LOW, NULL},
   {PWM_OUTPUT_ACTIVE_LOW | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_LOW, NULL},
   {PWM_OUTPUT_ACTIVE_HIGH, NULL}
  },
  .cr2 = TIM_CR2_MMS_1,//CR2
 #if STM32_PWM_USE_ADVANCED
   .bdtr = 0, //BDTR
 #endif
   .dier = 0,//DIER
};



typedef enum {
    ADCS_OD_ERROR_INFO_CODE_NONE = 0,
    ADCS_OD_ERROR_INFO_CODE_IMU_COMM_FAILURE,
    ADCS_OD_ERROR_INFO_CODE_ACCL_CHIP_ID_MISMATCH,
    ADCS_OD_ERROR_INFO_CODE_GYRO_CHIP_ID_MISMATCH,
	ADCS_OD_ERROR_INFO_CODE_IMU_INIT_FAILURE,
	ADCS_OD_ERROR_INFO_CODE_IMU_DATA_UPDATE_FAILURE,
	ADCS_OD_ERROR_INFO_CODE_MAGNETOMETER_0_INIT_FAILURE,
	ADCS_OD_ERROR_INFO_CODE_MAGNETOMETER_1_INIT_FAILURE,
	ADCS_OD_ERROR_INFO_CODE_MAGNETOMETER_2_INIT_FAILURE,
	ADCS_OD_ERROR_INFO_CODE_MAGNETOMETER_3_INIT_FAILURE,
	ADCS_OD_ERROR_INFO_CODE_LTZ_PLUS_Z_ENDCAP_FAILURE,
	ADCS_OD_ERROR_INFO_CODE_LTZ_MINUS_Z_ENDCAP_FAILURE,
	ADCS_OD_ERROR_INFO_CODE_MAGNETOMETER_0_COMM_FAILURE,
	ADCS_OD_ERROR_INFO_CODE_MAGNETOMETER_1_COMM_FAILURE,
	ADCS_OD_ERROR_INFO_CODE_MAGNETOMETER_2_COMM_FAILURE,
	ADCS_OD_ERROR_INFO_CODE_MAGNETOMETER_3_COMM_FAILURE,
} adcs_od_error_info_code_t;


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
	volatile bool is_working;
} magnetometer_data_struct_t;

typedef struct  {
	bmi088_accelerometer_sample_t accl_data;
	bmi088_gyro_sample_t gyro_sample;
	int16_t temp_c;

	mt_pwm_phase_data_t mt_pwm_data[3];

	magnetometer_data_struct_t magetometer_data[4];
} adcs_data_t;


adcs_data_t g_adcs_data;
extern CO_t *CO;


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


void CO_errorReportRateLimited(CO_EM_t *em, const uint8_t errorBit, uint16_t errorCode, uint32_t infoCode, systime_t *last_error_time) {

	const systime_t now_time = chVTGetSystemTime();
	if( chTimeDiffX(*last_error_time, now_time) < 10000 ) {
		return;
	}
	*last_error_time = now_time;

	CO_errorReport(em, errorBit, errorCode, infoCode);
}


const char* end_card_magnetometoer_t_to_str(const end_card_magnetometoer_t ecm) {
	switch (ecm) {
	case EC_MAG_0_MZ_1:
		return ("EC_MAG_0_MZ_1");
	case EC_MAG_1_MZ_2:
		return ("EC_MAG_1_MZ_2");
	case EC_MAG_2_PZ_1:
		return ("EC_MAG_2_PZ_1");
	case EC_MAG_3_PZ_2:
		return ("EC_MAG_3_PZ_2");
	case EC_MAG_NONE:
		return ("EC_MAG_NONE");
	}
	return ("???");

}

int32_t saturate_int32_t(const int32_t v, const int32_t min, const int32_t max) {
	if (v >= max)
		return (max);

	else if (v <= min)
		return (min);

	return (v);
}
//
//int16_t saturate_int16_t(const int32_t v) {
//	if (v >= INT16_MAX)
//		return (INT16_MAX);
//
//	else if (v <= INT16_MIN)
//		return (INT16_MIN);
//
//	return (v);
//}


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

void handle_can_open_data(void) {
	g_adcs_data.mt_pwm_data[0].target_pwm_percent = map_current_uA_to_pwm_duty_cycle(OD_RAM.x6007_magnetorquer.setMagnetorquerXCurrent * 100, 0);
	g_adcs_data.mt_pwm_data[1].target_pwm_percent = map_current_uA_to_pwm_duty_cycle(OD_RAM.x6007_magnetorquer.setMagnetorquerYCurrent * 100, 1);
	g_adcs_data.mt_pwm_data[2].target_pwm_percent = map_current_uA_to_pwm_duty_cycle(OD_RAM.x6007_magnetorquer.setMagnetorquerZCurrent * 100, 2);



    OD_RAM.x6000_gyroscope.pitchRate = g_adcs_data.gyro_sample.gyro_x;
    OD_RAM.x6000_gyroscope.yawRate = g_adcs_data.gyro_sample.gyro_y;
    OD_RAM.x6000_gyroscope.rollRate = g_adcs_data.gyro_sample.gyro_z;
    OD_RAM.x6000_gyroscope.pitchRateRaw = g_adcs_data.gyro_sample.gyro_x_raw;
    OD_RAM.x6000_gyroscope.yawRateRaw = g_adcs_data.gyro_sample.gyro_y_raw;
    OD_RAM.x6000_gyroscope.rollRateRaw = g_adcs_data.gyro_sample.gyro_z_raw;

    OD_RAM.x6001_acceleration.accx = g_adcs_data.accl_data.accl_x;
    OD_RAM.x6001_acceleration.accy = g_adcs_data.accl_data.accl_y;
    OD_RAM.x6001_acceleration.accz = g_adcs_data.accl_data.accl_z;
    OD_RAM.x6001_acceleration.accXRaw = g_adcs_data.accl_data.accl_x_raw;
    OD_RAM.x6001_acceleration.accyRaw = g_adcs_data.accl_data.accl_y_raw;
    OD_RAM.x6001_acceleration.acczRaw = g_adcs_data.accl_data.accl_z_raw;

    OD_RAM.x6002_IMU_Temperature = g_adcs_data.temp_c;


    OD_RAM.x6007_magnetorquer.magnetorquerXCurrent = g_adcs_data.mt_pwm_data[0].current_feedback_measurement_uA;
    OD_RAM.x6007_magnetorquer.magnetorquerYCurrent = g_adcs_data.mt_pwm_data[1].current_feedback_measurement_uA;
    OD_RAM.x6007_magnetorquer.magnetorquerZCurrent = g_adcs_data.mt_pwm_data[2].current_feedback_measurement_uA;

    OD_RAM.x6007_magnetorquer.magnetorquerXPWM_DutyCycle = g_adcs_data.mt_pwm_data[0].current_pwm_percent;
    OD_RAM.x6007_magnetorquer.magnetorquerYPWM_DutyCycle = g_adcs_data.mt_pwm_data[1].current_pwm_percent;
    OD_RAM.x6007_magnetorquer.magnetorquerZPWM_DutyCycle = g_adcs_data.mt_pwm_data[2].current_pwm_percent;


    if (g_adcs_data.magetometer_data[EC_MAG_2_PZ_1].is_working) {
		OD_RAM.x6003_magnetometerPZ1.magx = g_adcs_data.magetometer_data[EC_MAG_2_PZ_1].data.mx;
		OD_RAM.x6003_magnetometerPZ1.magy = g_adcs_data.magetometer_data[EC_MAG_2_PZ_1].data.my;
		OD_RAM.x6003_magnetometerPZ1.magz = g_adcs_data.magetometer_data[EC_MAG_2_PZ_1].data.mz;
    } else {
    	OD_RAM.x6003_magnetometerPZ1.magx = INT16_MAX;
    	OD_RAM.x6003_magnetometerPZ1.magy = INT16_MAX;
    	OD_RAM.x6003_magnetometerPZ1.magz = INT16_MAX;
    }

    if (g_adcs_data.magetometer_data[EC_MAG_3_PZ_2].is_working) {
		OD_RAM.x6004_magnetometerPZ2.magx = g_adcs_data.magetometer_data[EC_MAG_3_PZ_2].data.mx;
		OD_RAM.x6004_magnetometerPZ2.magy = g_adcs_data.magetometer_data[EC_MAG_3_PZ_2].data.my;
		OD_RAM.x6004_magnetometerPZ2.magz = g_adcs_data.magetometer_data[EC_MAG_3_PZ_2].data.mz;
	} else {
    	OD_RAM.x6004_magnetometerPZ2.magx = INT16_MAX;
    	OD_RAM.x6004_magnetometerPZ2.magy = INT16_MAX;
    	OD_RAM.x6004_magnetometerPZ2.magz = INT16_MAX;
    }


    if (g_adcs_data.magetometer_data[EC_MAG_0_MZ_1].is_working) {
		OD_RAM.x6005_magnetometerMZ1.magx = g_adcs_data.magetometer_data[EC_MAG_0_MZ_1].data.mx;
		OD_RAM.x6005_magnetometerMZ1.magy = g_adcs_data.magetometer_data[EC_MAG_0_MZ_1].data.my;
		OD_RAM.x6005_magnetometerMZ1.magz = g_adcs_data.magetometer_data[EC_MAG_0_MZ_1].data.mz;
    } else {
    	OD_RAM.x6005_magnetometerMZ1.magx = INT16_MAX;
    	OD_RAM.x6005_magnetometerMZ1.magy = INT16_MAX;
    	OD_RAM.x6005_magnetometerMZ1.magz = INT16_MAX;
    }


    if (g_adcs_data.magetometer_data[EC_MAG_1_MZ_2].is_working) {
		OD_RAM.x6006_magnetometerMZ2.magx = g_adcs_data.magetometer_data[EC_MAG_1_MZ_2].data.mx;
		OD_RAM.x6006_magnetometerMZ2.magy = g_adcs_data.magetometer_data[EC_MAG_1_MZ_2].data.my;
		OD_RAM.x6006_magnetometerMZ2.magz = g_adcs_data.magetometer_data[EC_MAG_1_MZ_2].data.mz;
    } else {
    	OD_RAM.x6006_magnetometerMZ2.magx = INT16_MAX;
    	OD_RAM.x6006_magnetometerMZ2.magy = INT16_MAX;
    	OD_RAM.x6006_magnetometerMZ2.magz = INT16_MAX;
    }

}

/**
 * TODO more documentation
 * @return true if update process successful, false otherwise
 */
bool update_imu_data(void) {
	static systime_t last_imu_update_time = 0;

	const systime_t now_time = chVTGetSystemTime();
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

    if( bmi088ReadAccelerometerXYZmG(&imudev, &g_adcs_data.accl_data ) == MSG_OK ) {
        dbgprintf("Acc readings mG X = %d, Y = %d, Z = %d\r\n", accl_data.accl_x, accl_data.accl_y, accl_data.accl_z);
    } else {
        ret = false;
        dbgprintf("Failed to read accelerometer readings\r\n");
    }

    if( bmi088ReadGyroXYZ(&imudev, &g_adcs_data.gyro_sample) == MSG_OK ) {
        dbgprintf("Gyro readings X = %d, Y = %d, Z = %d\r\n", gyro_sample.gyro_x, gyro_sample.gyro_y, gyro_sample.gyro_z);
    } else {
        ret = false;
        dbgprintf("Failed to read gyro readings\r\n");
    }

    if( bmi088ReadTemp(&imudev, &g_adcs_data.temp_c) == MSG_OK ) {
        dbgprintf("Accelerator temp_c = %d C\r\n", temp_c);
    } else {
        ret = false;
        dbgprintf("Failed to read temperature data...\r\n");
    }

    dbgprintf("\r\n");

    //TODO re-suspend to save power
    //BMI088AccelerometerEnableOrSuspend(&imudev, BMI088_MODE_SUSPEND);


    return ret;
}

bool connect_endcard_ltc4305_geneic(const uint8_t ltc4304_i2c_address, const bool conn_1_enable, const bool conn_2_enable) {
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
		chprintf(DEBUG_SD, "ERROR: Failed to set LTC4305 connections! i2c_addr=0x%X\r\n", (ltc4304_i2c_address << 1));
	} else {
		chprintf(DEBUG_SD, "SUCCESS: set LTC4305 connections! i2c_addr=0x%X\r\n", (ltc4304_i2c_address << 1));
	}

	return(ret);
}

bool connect_endcard_ltc4305_plus_z(const bool conn_1_enable, const bool conn_2_enable) {
	bool ret = connect_endcard_ltc4305_geneic(LTC_4035_PLUSZ_CARD_I2C_ADDRESS_WRITE, conn_1_enable, conn_2_enable);
	if( ! ret ) {
		static systime_t last_report_time = 0;
		CO_errorReportRateLimited(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_COMMUNICATION, ADCS_OD_ERROR_INFO_CODE_LTZ_PLUS_Z_ENDCAP_FAILURE, &last_report_time);
	} //FIXME should this error be cleard if/when comms works again on a subsequent call?

	return(ret);
}

bool connect_endcard_ltc4305_minus_z(const bool conn_1_enable, const bool conn_2_enable) {
	bool ret = connect_endcard_ltc4305_geneic(LTC_4035_MINUSZ_CARD_I2C_ADDRESS_WRITE, conn_1_enable, conn_2_enable);
	if( ! ret ) {
		static systime_t last_report_time = 0;
		CO_errorReportRateLimited(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_COMMUNICATION, ADCS_OD_ERROR_INFO_CODE_LTZ_MINUS_Z_ENDCAP_FAILURE, &last_report_time);
	} //FIXME should this error be cleard if/when comms works again on a subsequent call?

	return(ret);
}


bool select_magnetometer(const end_card_magnetometoer_t ecm) {
//	chprintf(DEBUG_SD, "Selecting magnetometer %u\r\n", ecm);
	chThdSleepMilliseconds(10);

	bool ret1 = false;
	bool ret2 = false;

//	if( ecm != EC_MAG_NONE ) {
//		//FIXME delete this block
//		ret2 = connect_endcard_ltc4305_plus_z(false, true);
//		return(ret2);
//	}

//	if( ecm == EC_MAG_0_MZ_1 || ecm == EC_MAG_1_MZ_2 ) {
//		ret2 = connect_endcard_ltc4305_plus_z(false, true);
//		return(ret2);
//	}

	switch(ecm) {
	case EC_MAG_0_MZ_1:
		ret1 = connect_endcard_ltc4305_minus_z(true, false);
		ret2 = connect_endcard_ltc4305_plus_z(false, false);
		break;
	case EC_MAG_1_MZ_2:
		ret1 = connect_endcard_ltc4305_minus_z(false, true);
		ret2 = connect_endcard_ltc4305_plus_z(false, false);
		break;
	case EC_MAG_2_PZ_1:
		ret1 = connect_endcard_ltc4305_minus_z(false, false);
		ret2 = connect_endcard_ltc4305_plus_z(true, false);
		break;
	case EC_MAG_3_PZ_2:
		ret1 = connect_endcard_ltc4305_minus_z(false, false);
		ret2 = connect_endcard_ltc4305_plus_z(false, true);
		break;
	case EC_MAG_NONE:
		ret1 = true;
		ret1 = connect_endcard_ltc4305_minus_z(false, false); //FIXME uncomment this
		ret2 = connect_endcard_ltc4305_plus_z(false, false);
		break;
	}

//	return(ret1); //fixme remove this
	return(ret2); //FIXME remove this

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
		chprintf(DEBUG_SD, "Magnetometer %d %s not initialized.\r\n", ecm, end_card_magnetometoer_t_to_str(ecm));
		return(false);
	}

	if( ! select_magnetometer(ecm) ) {
		return(false);
	}


	chprintf(DEBUG_SD, "Reading from magnetometer %d %s: ", ecm, end_card_magnetometoer_t_to_str(ecm));
	chThdSleepMilliseconds(5);

	if( mmc5883maReadData(&g_adcs_data.magetometer_data[ecm].driver, &g_adcs_data.magetometer_data[ecm].data) ) {
		chprintf(DEBUG_SD, " mx=%d, my=%d, mz=%d\r\n", g_adcs_data.magetometer_data[ecm].data.mx,
				g_adcs_data.magetometer_data[ecm].data.my,
				g_adcs_data.magetometer_data[ecm].data.mz);
		r = true;
	} else {
		//FIXME should this error be cleard if/when comms works again on a subsequent call?
		static systime_t last_report_time = 0;
		CO_errorReportRateLimited(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_COMMUNICATION, ADCS_OD_ERROR_INFO_CODE_MAGNETOMETER_0_COMM_FAILURE + ecm, &last_report_time);
	}


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
		if( ! select_and_read_magnetometer(ecm) ) {
			ret = false;
			//Note: if for some reason the LTC or MMC's stop responding after initialization, the CANOpen output data will saturate as it inspects the is_working flag.
			g_adcs_data.magetometer_data[ecm].is_working = false;
		} else {
			g_adcs_data.magetometer_data[ecm].is_working = true;
		}
	}

	select_magnetometer(EC_MAG_NONE);

	return(ret);
}

void stop_end_cap_magnetometers(void) {
	//Disable power to the end cap magnetometers
	palSetLine(LINE_MAG_N_EN);
}

bool init_end_cap_magnetometers(void) {
	palClearLine(LINE_MAG_N_EN);
	chThdSleepMilliseconds(5);

	bool ret = true;

	//FIXME ecm start
	for(end_card_magnetometoer_t ecm = EC_MAG_0_MZ_1; ecm < EC_MAG_NONE; ecm++ ) {
		chprintf(DEBUG_SD, "Initing MMC %u\r\n", ecm);
		chThdSleepMilliseconds(5);

		mmc5883maObjectInit(&g_adcs_data.magetometer_data[ecm].driver);

		if( ! select_magnetometer(ecm) ) {
			ret = false;
			chprintf(DEBUG_SD, "Failed to start MMC4883MA number %u %s due to LTC selection error\r\n", ecm, end_card_magnetometoer_t_to_str(ecm));
		} else {
			if( mmc5883maStart(&g_adcs_data.magetometer_data[ecm].driver, &mmc5883ma_generic_config) ) {
				chprintf(DEBUG_SD, "Successfully started MMC4883MA number %u %s\r\n", ecm, end_card_magnetometoer_t_to_str(ecm));
				g_adcs_data.magetometer_data[ecm].is_initialized = true;
			} else {
				chprintf(DEBUG_SD, "Failed to start MMC4883MA number %u %s\r\n", ecm, end_card_magnetometoer_t_to_str(ecm));
				ret = false;
				//FIXME should this error be cleard if/when comms works again on a subsequent call?
				static systime_t last_report_time = 0;
				CO_errorReportRateLimited(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_HARDWARE, ADCS_OD_ERROR_INFO_CODE_MAGNETOMETER_0_INIT_FAILURE + ecm, &last_report_time);
			}
		}
	}

	select_magnetometer(EC_MAG_NONE);

	return(ret);
}



void set_pwm_output(void) {
	if( PWMD1.state == PWM_STOP ) {
		pwmStart(&PWMD1, &pwmcfg_1_trigo);
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

				pwmDisableChannel(&PWMD1, g_adcs_data.mt_pwm_data[i].pwm_channel_number);

				if( g_adcs_data.mt_pwm_data[i].target_pwm_percent < 0 ) {
					palSetPad(GPIOB, g_adcs_data.mt_pwm_data[i].phase_gpio_pin_number);
				} else {
					palClearPad(GPIOB, g_adcs_data.mt_pwm_data[i].phase_gpio_pin_number);
				}

				const int32_t pwm_val = ABS(g_adcs_data.mt_pwm_data[i].target_pwm_percent);
				pwmEnableChannel(&PWMD1, g_adcs_data.mt_pwm_data[i].pwm_channel_number, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, pwm_val));

				g_adcs_data.mt_pwm_data[i].current_pwm_percent = g_adcs_data.mt_pwm_data[i].target_pwm_percent;
				g_adcs_data.mt_pwm_data[i].last_update_time = now_time;
			}
		}
	}
#endif
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
			chprintf(DEBUG_SD, "  measured_i_sense_voltage[%d] = %d uA, %u mV\r\n",
							i,
							data->current_feedback_measurement_uA,
							(uint32_t) (data->current_feedback_measurement_V * 1000));
		}


		chprintf(DEBUG_SD, "  CO_EM_GENERIC_ERROR:  %u\r\n", CO_isError(CO->em, CO_EM_GENERIC_ERROR));

	}
}


void process_magnetorquer(void) {
//	chprintf(DEBUG_SD, "ADCD1.state = %u\r\n", ADCD1.state);

	if( ADCD1.state == ADC_STOP || ADCD1.state == ADC_UNINIT ) {
		adcStart(&ADCD1, NULL);
	}

	if( ADCD1.state == ADC_COMPLETE ) {
		adcStopConversion(&ADCD1);
	}

	if( ADCD1.state == ADC_READY ) {
		uint32_t channel_sums[MY_SAMPLING_NUMBER];
		memset(channel_sums, 0, sizeof(channel_sums));

		for(int s = 0; s < MY_SAMPLING_NUMBER; s++) {
//			chprintf(DEBUG_SD, "  adc_sample_buff[%d] = [", s);

			for (int adc_chan_idx = 1; adc_chan_idx < ADC_NUM_CHANNELS; adc_chan_idx++) {
				const int idx = (s * ADC_NUM_CHANNELS) + adc_chan_idx;
				channel_sums[adc_chan_idx] += adc_sample_buff[idx];
//				chprintf(DEBUG_SD, "%d, ", adc_sample_buff[idx]);
			}
//			chprintf(DEBUG_SD, "]\r\n");
		}

		for (int adc_chan_idx = 1; adc_chan_idx < ADC_NUM_CHANNELS; adc_chan_idx++) {
			const uint32_t channel_avg = channel_sums[adc_chan_idx] / MY_SAMPLING_NUMBER;
			measured_i_sense_voltage[adc_chan_idx] = (((float) channel_avg) / 4096.0) * 3.3;
//			chprintf(DEBUG_SD, "avg = %u, voltage[%d] = %u mV\r\n", channel_avg, adc_chan_idx, ((uint32_t) (measured_i_sense_voltage[adc_chan_idx] * 1000.0)));

			uint8_t dest_mt_idx = 0;
			if( adc_chan_idx == 1 ) {
				dest_mt_idx = 2;
			} else if( adc_chan_idx == 2 ) {
				dest_mt_idx = 1;
			} else if( adc_chan_idx == 3 ) {
				dest_mt_idx = 0;
			}

			g_adcs_data.mt_pwm_data[dest_mt_idx].current_feedback_measurement_V = measured_i_sense_voltage[adc_chan_idx];
			g_adcs_data.mt_pwm_data[dest_mt_idx].current_feedback_measurement_uA = current_feedback_convert_volts_to_microamps(measured_i_sense_voltage[adc_chan_idx]);
			if( g_adcs_data.mt_pwm_data[dest_mt_idx].current_pwm_percent < 0 ) {
				g_adcs_data.mt_pwm_data[dest_mt_idx].current_feedback_measurement_uA *= -1;
			}

		}

//		chprintf(DEBUG_SD, "Staring conversion...\r\n"); chThdSleepMilliseconds(10);
		adcStartConversion(&ADCD1, &adcgrpcfg_tim1_trigo, adc_sample_buff, ADC_BUFF_SIZE);//Starts an ADC conversion.
	}

//	chprintf(DEBUG_SD, "adc_conv_cb#=%u, ", adc_conversion_complete_callback_count);
//	chprintf(DEBUG_SD, "adc_error_cb#=%u\r\n", adc_conversion_error_callback_count);

	set_pwm_output();
	print_debug_output();
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

//
//    palClearLine(LINE_MAG_N_EN);
//    end_card_magnetometoer_t ecm = EC_MAG_2_PZ_1;
////    ecm = EC_MAG_3_PZ_2;
//    mmc5883maObjectInit(&g_adcs_data.magetometer_data[ecm].driver);
//    select_magnetometer(ecm);
//    while(1) {
//		if( mmc5883maStart(&g_adcs_data.magetometer_data[ecm].driver, &mmc5883ma_generic_config) ) {
//			chprintf(DEBUG_SD, "Successfully started MMC4883MA number %u %s\r\n", ecm, end_card_magnetometoer_t_to_str(ecm));
//			g_adcs_data.magetometer_data[ecm].is_initialized = true;
//		} else {
//			chprintf(DEBUG_SD, "Failed to start MMC4883MA number %u %s\r\n", ecm, end_card_magnetometoer_t_to_str(ecm));
////			ret = false;
//			//FIXME should this error be cleard if/when comms works again on a subsequent call?
//			CO_errorReport(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_HARDWARE, ADCS_OD_ERROR_INFO_CODE_MAGNETOMETER_0_INIT_FAILURE + ecm);
//		}
//    	chThdSleepMilliseconds(1000);
//    }



	init_end_cap_magnetometers();
    init_magnetorquer();


//    OD_RAM.x6007_magnetorquer.setMagnetorquerXCurrent = 300;//FIXME remove this, this is just for testing
//    OD_RAM.x6007_magnetorquer.setMagnetorquerYCurrent = 400;
//    OD_RAM.x6007_magnetorquer.setMagnetorquerZCurrent = 500;


    bmi088ObjectInit(&imudev);

    chprintf(DEBUG_SD, "Starting BMI088...\r\n");
    chThdSleepMilliseconds(50);
    bmi088Start(&imudev, &imucfg);



    chprintf(DEBUG_SD, "BMI088 state = %u, error_flags=0x%X\r\n", imudev.state, imudev.error_flags);
    if( imudev.state != BMI088_READY ) {
        chprintf(DEBUG_SD, "Failed to start IMU driver...\r\n");
        static systime_t last_report_time = 0;
        CO_errorReportRateLimited(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_HARDWARE, ADCS_OD_ERROR_INFO_CODE_IMU_INIT_FAILURE, &last_report_time);
    } else {
        uint8_t bmi088_chip_id = 0;
        if( (r = bmi088ReadAccelerometerChipId(&imudev, &bmi088_chip_id)) == MSG_OK ) {
            chprintf(DEBUG_SD, "BMI088 accelerometer chip ID is 0x%X, expected to be (0x%X or 0x%X)\r\n", bmi088_chip_id, BMI088_ACC_CHIP_ID_EXPECTED, BMI090L_ACC_CHIP_ID_EXPECTED);
        } else {
            chprintf(DEBUG_SD, "Failed to read accel chip ID from BMI088 ACCEL, r = %d\r\n", r);
        }

        if( bmi088_chip_id != BMI088_ACC_CHIP_ID_EXPECTED && bmi088_chip_id != BMI090L_ACC_CHIP_ID_EXPECTED ) {
        	chprintf(DEBUG_SD, "ERROR: BMI088 ACCEL FAIL: didn't find BMI088!\r\n");
        	static systime_t last_report_time = 0;
            CO_errorReportRateLimited(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_HARDWARE, ADCS_OD_ERROR_INFO_CODE_ACCL_CHIP_ID_MISMATCH, &last_report_time);
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
        	static systime_t last_report_time = 0;
            CO_errorReportRateLimited(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_HARDWARE, ADCS_OD_ERROR_INFO_CODE_GYRO_CHIP_ID_MISMATCH, &last_report_time);
        } else {
        	chprintf(DEBUG_SD, "BMI088 GYRO SUCCESS: found BMI088!\r\n");
        }

    }
    chprintf(DEBUG_SD, "Done initializing, starting loop...\r\n");

    for (uint32_t iterations = 0; !chThdShouldTerminateX(); iterations++) {
        dbgprintf("IMU loop iteration %u system time %u\r\n", iterations, (uint32_t)chVTGetSystemTime());

        if( update_imu_data() ) {
        	//FIXME re-enable this??? with rate limits???
//			CO_errorReset(CO->em, CO_EM_GENERIC_ERROR, ADCS_OD_ERROR_INFO_CODE_IMU_DATA_UPDATE_FAILURE);
        } else {
        	static systime_t last_report_time = 0;
        	CO_errorReportRateLimited(CO->em, CO_EM_GENERIC_ERROR, CO_EMC_COMMUNICATION, ADCS_OD_ERROR_INFO_CODE_IMU_DATA_UPDATE_FAILURE, &last_report_time);
        }
        update_endcard_magnetometer_readings();
        process_magnetorquer();
        handle_can_open_data();

        chThdSleepMilliseconds(5);
    }

    /* Stop the BMI088 IMU sensor */
    bmi088Stop(&imudev);
    stop_end_cap_magnetometers();

    chThdExit(MSG_OK);
}
