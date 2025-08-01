#ifndef _SOLAR_H_
#define _SOLAR_H_

#include "ch.h"
#include "hal.h"

#define INA226_SADDR            (0x40)

/* Solar application thread prototypes */
extern THD_WORKING_AREA(solar_wa, 0x400);
extern THD_FUNCTION(solar, arg);
extern THD_WORKING_AREA(sensor_mon_wa, 0x200);
extern THD_FUNCTION(sensor_mon, arg);

typedef enum {
	SOLAR_OD_ERROR_TYPE_NONE = 0,
	SOLAR_OD_ERROR_TYPE_TMP101_1_COMM_ERROR,
	SOLAR_OD_ERROR_TYPE_TMP101_2_COMM_ERROR,
	SOLAR_OD_ERROR_TYPE_INA226_COMM_ERROR,
	SOLAR_OD_ERROR_TYPE_PAO_INVALID_DATA,
} solar_od_error_type_t;

typedef enum {
    MPPT_ALGORITHM_PAO = 0
} mppt_algorithm_t;

struct Sample {
    int32_t power_mW;
    int32_t voltage_mV;
    int32_t current_uA;
    int32_t shunt_uV;
};

typedef struct {
    uint32_t iadj_uV;
    struct Sample sample;
    int32_t last_time_mS;
} MpptPaoState;

int32_t time_helper(MpptPaoState *state);

#if !HAL_USE_I2C
#error "TMP101 requires HAL_USE_I2C"
#endif

#if !I2C_USE_MUTUAL_EXCLUSION
#error "TMP101 requires I2C_USE_MUTUAL_EXCLUSION"
#endif

#endif
