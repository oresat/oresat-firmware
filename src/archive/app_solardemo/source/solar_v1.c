/*! \file solar_v1.c
 *
 * API for solar_v1.c
 */

/*!
 * \defgroup solar_v1 Voltage, current  and Temperature Monitor
 *
 * @{
 */

#include <stdint.h>
#include <limits.h>

#include "ch.h"
#include "hal.h"
#include "chprintf.h"

#include "util_numbers.h"

#include "ltc2990.h"

#include "solar_v1.h"

/* Current through Rsense in mA */
signed int solar_v1_calc_current(ltc2990_data * d, ltc2990_error * error)
{
    uint8_t    SIGN           = 0;
    uint16_t   v_bits         = 0;
    double     v_volts_d      = 0.0;
    double     i_amps_d       = 0.0;
    signed int i_milliamps    = INT_MIN;

    *error = LTC2990_DATA_INVALID;
    if((0x80 & d->V1_MSB) != 0)
    {
        SIGN           = ((d->V1_MSB & (1 << 6)) >> 6);
        v_bits         = ((d->V1_MSB << 8) | d->V1_LSB);
        v_volts_d      = (double)(v_bits & 0x3fff) * 0.00001942 ;
        i_amps_d       = v_volts_d / 0.18;
        i_milliamps    = (signed int)incr_rnd(i_amps_d * 1000, 0.1);
        if(SIGN == 1)
        {
            i_milliamps *= -1;
        }
        *error         = LTC2990_OK;
    }
    return i_milliamps;
}

/* External Temp in C */
signed int solar_v1_calc_temp(ltc2990_data * d, ltc2990_error * error)
{
    signed int text_C         = INT_MIN;

    *error = LTC2990_DATA_INVALID;
    if(((0x1 << 6) & d->V3_MSB) != 0)
    {
        *error = LTC2990_SENSOR_SHORT;
    }
    else if (((0x1 << 5) & d->V3_MSB) != 0)
    {
        *error = LTC2990_SENSOR_OPEN;
    }
    else if((0x80 & d->V3_MSB) != 0)
    {
        //clear dv bit
        d->V3_MSB      = ((~(1 << 7)) & d->V3_MSB);
        text_C         = sign_extend_13bit((d->V3_MSB << 8) | d->V3_LSB);
        *error         = LTC2990_OK;
    }
    return(text_C / 16);
}


//! @}
