/*! \file ltc2990.c
 *
 * API for ltc2990.c
 */

/*!
 * \defgroup ltc2990 Voltage, current  and Temperature Monitor
 *
 * @{
 */

#include <stdint.h>
#include "ch.h"
#include "hal.h"
#include "chprintf.h"

#include "util_numbers.h"
#include "ltc2990.h"

extern const  uint8_t    LTC2990_I2C_ADDR;

static        uint8_t    i2c_txbuf[LTC2990_I2C_TX_BUFSIZE];
static        uint8_t    i2c_rxbuf[LTC2990_I2C_RX_BUFSIZE];

uint8_t ltc2990_readreg(uint8_t reg, i2cflags_t * i2c_errors)
{
    msg_t status   = MSG_OK;
    systime_t tmo  = TIME_MS2I(4);

    i2c_txbuf[0] = reg;
    i2c_rxbuf[0] = 0xff;
    i2cAcquireBus(&I2CD1);
    status       = i2cMasterTransmitTimeout(&I2CD1, LTC2990_I2C_ADDR, i2c_txbuf, 1, i2c_rxbuf, 1, tmo);
    i2cReleaseBus(&I2CD1);

    if (status != MSG_OK)
    {
        *i2c_errors = i2cGetErrors(&I2CD1);
    }

    return(i2c_rxbuf[0]);
}

void ltc2990_writereg(uint8_t reg, uint8_t val, i2cflags_t * i2c_errors)
{
    msg_t status   = MSG_OK;
    systime_t tmo  = TIME_MS2I(4);

    i2c_txbuf[0] = reg;
    i2c_txbuf[1] = val;
    i2cAcquireBus(&I2CD1);
    status       = i2cMasterTransmitTimeout(&I2CD1, LTC2990_I2C_ADDR, i2c_txbuf, 2, i2c_rxbuf, 0, tmo);
    i2cReleaseBus(&I2CD1);

    if (status != MSG_OK)
    {
        *i2c_errors = i2cGetErrors(&I2CD1);
    }
}

void ltc2990_read_all(ltc2990_data * d, i2cflags_t * i2c_errors)
{
    msg_t status   = MSG_OK;
    systime_t tmo  = TIME_MS2I(4);

    i2c_txbuf[0]   = LTC2990_STATUS;
    i2cAcquireBus(&I2CD1);
    status         = i2cMasterTransmitTimeout(&I2CD1, LTC2990_I2C_ADDR, i2c_txbuf, 1, i2c_rxbuf, 0x10, tmo);
    i2cReleaseBus(&I2CD1);

    if (status != MSG_OK)
    {
        *i2c_errors = i2cGetErrors(&I2CD1);
    }
    else
    {
        d->STATUS    = i2c_rxbuf[0];
        d->CONTROL   = i2c_rxbuf[1];
        d->TRIGGER   = i2c_rxbuf[2];
        d->NA        = i2c_rxbuf[3];
        d->T_INT_MSB = i2c_rxbuf[4];
        d->T_INT_LSB = i2c_rxbuf[5];
        d->V1_MSB    = i2c_rxbuf[6];
        d->V1_LSB    = i2c_rxbuf[7];
        d->V2_MSB    = i2c_rxbuf[8];
        d->V2_LSB    = i2c_rxbuf[9];
        d->V3_MSB    = i2c_rxbuf[10];
        d->V3_LSB    = i2c_rxbuf[11];
        d->V4_MSB    = i2c_rxbuf[12];
        d->V4_LSB    = i2c_rxbuf[13];
        d->VCC_MSB   = i2c_rxbuf[14];
        d->VCC_LSB   = i2c_rxbuf[15];
    }
}

inline bool ltc2990_conversion_done(uint8_t statusreg)
{
    if( ((statusreg & 0xfe) & 0x1) == 0x1)
    {
        return false;
    }
    return true;
}

/* T Internal in C */
signed int ltc2990_calc_tint(ltc2990_data * d, ltc2990_error * error)
{
    signed int tint_C           = 0;

    *error = LTC2990_DATA_INVALID;
    if((0x80 & d->T_INT_MSB) != 0)
    {
        //clear dv bit
        d->T_INT_MSB      = ((~(1 << 7)) & d->T_INT_MSB);
        tint_C            = sign_extend_13bit((d->T_INT_MSB << 8) | d->T_INT_LSB);
        *error            = LTC2990_OK;
    }
    return(tint_C / 16);
}

/* VCC in millivolts */
signed int ltc2990_calc_vcc(ltc2990_data * d, ltc2990_error * error)
{
    uint16_t   vcc_bits         = 0;
    double     vcc_volts_d      = 0.0;
    signed int vcc_millivolts   = 0;

    *error = LTC2990_DATA_INVALID;
    if((0x80 & d->VCC_MSB) != 0)
    {
        vcc_bits          = ((d->VCC_MSB << 8) | d->VCC_LSB);
        vcc_volts_d       = 2.5 + ((double)(vcc_bits & 0x3fff) * 0.00030518 ) ;
        vcc_millivolts    = (signed int)incr_rnd(vcc_volts_d * 1000, 0.1);
        *error            = LTC2990_OK;
    }
    return vcc_millivolts;
}

//! @}
