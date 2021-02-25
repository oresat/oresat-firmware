/**
 * @file    tmp101.c
 * @brief   TMP101 Digital to Analog Converter.
 *
 * @addtogroup TMP101
 * @ingrup ORESAT
 * @{
 */

#include "hal.h"
#include "tmp101an.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

#define DIAG_ON__TMP101AN



/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/
typedef union {
    struct __attribute__((packed)) {
        uint8_t reg;
        union {
            uint8_t data[2];
            uint16_t value;
        };
    };
    uint8_t buf[3];
} i2cbuf_t;

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

#if (TMP101_USE_I2C) || defined(__DOXYGEN__)
/**
 * @brief   Reads registers value using I2C.
 * @pre     The I2C interface must be initialized and the driver started.
 *
 * @param[in]  i2cp      pointer to the I2C interface
 * @param[in]  sad       slave address without R bit
 * @param[in]  reg       first sub-register address
 * @param[out] rxbuf     pointer to an output buffer
 * @param[in]  n         number of consecutive register to read
 * @return               the operation status.
 * @notapi
 */
msg_t tmp101I2CReadRegister(I2CDriver *i2cp, i2caddr_t sad, uint8_t reg,
        uint8_t* rxbuf, size_t n) {
    return i2cMasterTransmitTimeout(i2cp, sad, &reg, 1, rxbuf, n,
            TIME_INFINITE);
}

/**
 * @brief   Writes a value into a register using I2C.
 * @pre     The I2C interface must be initialized and the driver started.
 *
 * @param[in] i2cp       pointer to the I2C interface
 * @param[in] sad        slave address without R bit
 * @param[in] txbuf      buffer containing reg in first byte and high
 *                       and low data bytes
 * @param[in] n          size of txbuf
 * @return               the operation status.
 * @notapi
 */
msg_t tmp101I2CWriteRegister(I2CDriver *i2cp, i2caddr_t sad, uint8_t *txbuf,
        size_t n) {
    return i2cMasterTransmitTimeout(i2cp, sad, txbuf, n, NULL, 0,
            TIME_INFINITE);
}
#endif /* TMP101_USE_I2C */

/*==========================================================================*/
/* Interface implementation.                                                */
/*==========================================================================*/

static const struct TMP101VMT vmt_device = {
    (size_t)0,
};

/*===========================================================================*/
/* - SECTION - Driver exported functions.                                    */
/*===========================================================================*/

/**
 * @brief   Initializes an instance.
 *
 * @param[out] devp     pointer to the @p TMP101Driver object
 *
 * @init
 */
void tmp101ObjectInit(TMP101Driver *devp) {
    devp->vmt = &vmt_device;

    devp->config = NULL;

    devp->state = TMP101_STOP;
}




/**
 * @brief   Configures and activates TMP101 Complex Driver peripheral.
 *
 * @param[in] devp      pointer to the @p TMP101Driver object
 * @param[in] config    pointer to the @p TMP101Config object
 *
 * @api
 */
void tmp101Start(TMP101Driver *devp, const TMP101Config *config) {
//    i2cbuf_t buf;

    osalDbgCheck((devp != NULL) && (config != NULL));
    osalDbgAssert((devp->state == TMP101_STOP) ||
            (devp->state == TMP101_READY),
            "tmp101Start(), invalid state");

    devp->config = config;

    /* Configuring common registers.*/

// 2020-02-24 Note - as of this date no common registers to configure
//  for TMP101AN sensors.

    devp->state = TMP101_READY;

}

/**
 * @brief   Deactivates the TMP101 Complex Driver peripheral.
 *
 * @param[in] devp       pointer to the @p TMP101Driver object
 *
 * @api
 */
void tmp101Stop(TMP101Driver *devp) {
//    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state == TMP101_STOP) || (devp->state == TMP101_READY),
            "tmp101Stop(), invalid state");

//    if (devp->state == TMP101_READY) {
//    }
    devp->state = TMP101_STOP;
}



// 2021-02-07 - first draft read temperature routine

bool read_tmp101an_temperature_v1(TMP101Driver *devp, unsigned int option)
{
// 2021-02-07 - these two byte arrays will be passed to a development
//  routine, to confirm we can talk with the TMP101AN sensors of the
//  solar board.  When that's working we'll move these and the dev'
//  code over to the TMP101AN driver source file.  That will be the
//  first step to honor and conform to the object oritented device
//  driver encapsulation that's already expressed in the Oresat firmware
//  project - TMH
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    uint8_t buffer_tx[2] = {0};
    uint8_t buffer_rx[5] = {0};

    msg_t i2c_result = MSG_OK;
    i2cflags_t i2c_flags = 0;

    uint8_t sensor_addr = devp->config->saddr;

    if (option == 2)
    {
        // option parameter not yet used - TMH
    }

// Values chosen per TMP101AN datasheet:
    buffer_tx[0] = TMP101_REG_TEMPERATURE_READING;
    buffer_tx[1] = 0;

// Clear first two bytes of receive buffer, as temperature reading has 12 bits spanning two bytes:
    buffer_rx[0] = 0;
    buffer_rx[1] = 0;


#ifdef DIAG_ON__TMP101AN
    chprintf((BaseSequentialStream *) &SD2, "reading temperature sensor %02X . . .\r\n", sensor_addr);
#endif

    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);

    i2c_result = i2cMasterTransmitTimeout(devp->config->i2cp, sensor_addr, buffer_tx, 1, buffer_rx, 2, TIME_INFINITE);
    i2c_flags = i2cGetErrors(devp->config->i2cp);
    i2cReleaseBus(devp->config->i2cp);

#ifdef DIAG_ON__TMP101AN
    chprintf((BaseSequentialStream *) &SD2, "temperature reg bytes back hold %u and %u.\r\n\r\n",
      buffer_rx[0], buffer_rx[1]);
#endif

    if ( i2c_result != 0 )
        { chprintf((BaseSequentialStream *) &SD2, "i2c_result holds %ld.\r\n", i2c_result); }
    if ( i2c_flags != 0 )
        { chprintf((BaseSequentialStream *) &SD2, "i2c_flags holds %ld.\r\n\r\n", i2c_flags); }

// Compiler error:  cannot write to instantiating code's memory, as on next line - TMH:
//    devp->config->temperature_present_in_C = (( buffer_rx[0] << 4 ) | ( buffer_rx[0] >> 4 ));

    if ( i2c_result == MSG_OK )
        return true;
    else
        return true;

}



//----------------------------------------------------------------------
// @brief   routine to read TMP101AN temperature sensor, and return two-
//          two-byte reading
//----------------------------------------------------------------------
msg_t read_tmp101an_temperature_v2(TMP101Driver *devp, uint8_t* byte_array)
{
    msg_t i2c_result = MSG_OK;
    i2cflags_t i2c_flags = 0;
    uint8_t sensor_addr = devp->config->saddr;
    uint8_t buffer_tx[2] = {0};

// Values chosen per TMP101AN datasheet:
    buffer_tx[0] = TMP101_REG_TEMPERATURE_READING;
    buffer_tx[1] = 0;

// Prepare for I2C transaction:
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);

    i2c_result = i2cMasterTransmitTimeout(devp->config->i2cp, sensor_addr, buffer_tx, 1, byte_array, 2, TIME_INFINITE);

    i2c_flags = i2cGetErrors(devp->config->i2cp);
    i2cReleaseBus(devp->config->i2cp);

// TO BE optional warning code to report I2C bus errors:
    if ( i2c_result != 0 )
        { chprintf((BaseSequentialStream *) &SD2, "i2c_result holds %ld.\r\n", i2c_result); }
    if ( i2c_flags != 0 )
        { chprintf((BaseSequentialStream *) &SD2, "i2c_flags holds %ld.\r\n\r\n", i2c_flags); }

    return i2c_result;
}



/** @} */
