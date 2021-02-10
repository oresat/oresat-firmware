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
    i2cbuf_t buf;

    osalDbgCheck((devp != NULL) && (config != NULL));
    osalDbgAssert((devp->state == TMP101_STOP) ||
            (devp->state == TMP101_READY),
            "tmp101Start(), invalid state");

    devp->config = config;

    /* Configuring common registers.*/
#if (0)
#if TMP101_USE_I2C
#if TMP101_SHARED_I2C
    i2cAcquireBus(config->i2cp);
#endif /* TMP101_SHARED_I2C */

    i2cStart(config->i2cp, config->i2ccfg);

    buf.reg = TMP101_AD_CONFIG;
    buf.value = __REVSH(TMP101_CONFIG_RST);
    tmp101I2CWriteRegister(config->i2cp, config->saddr, buf.buf, sizeof(buf));
    do {
        tmp101I2CReadRegister(config->i2cp, config->saddr, TMP101_AD_CONFIG,
                                                buf.data, sizeof(buf.data));
    } while (buf.data[0] & 0x80U); /* While still resetting */
    buf.reg = TMP101_AD_CONFIG;
    buf.value = __REVSH(config->cfg);
    tmp101I2CWriteRegister(config->i2cp, config->saddr, buf.buf, sizeof(buf));
    buf.reg = TMP101_AD_CAL;
    buf.value = __REVSH(config->cal);
    tmp101I2CWriteRegister(config->i2cp, config->saddr, buf.buf, sizeof(buf));

#if TMP101_SHARED_I2C
    i2cReleaseBus(config->i2cp);
#endif /* TMP101_SHARED_I2C */
#endif /* TMP101_USE_I2C */
#endif // (0)
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
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state == TMP101_STOP) || (devp->state == TMP101_READY),
            "tmp101Stop(), invalid state");

    if (devp->state == TMP101_READY) {
#if (0) // ORESAT_TASK_001
#if TMP101_USE_I2C
#if TMP101_SHARED_I2C
        i2cAcquireBus(devp->config->i2cp);
        i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* TMP101_SHARED_I2C */

        /* Reset to input.*/
        buf.reg = TMP101_AD_CONFIG;
        buf.value = __REVSH(TMP101_CONFIG_RST);
        tmp101I2CWriteRegister(devp->config->i2cp, devp->config->saddr, buf.buf, sizeof(buf));

        i2cStop(devp->config->i2cp);
#if TMP101_SHARED_I2C
        i2cReleaseBus(devp->config->i2cp);
#endif /* TMP101_SHARED_I2C */
#endif /* TMP101_USE_I2C */
#endif // ORESAT_TASK_001
    }
    devp->state = TMP101_STOP;
}


#if (0) // 2021-02-07, not ready to use any of these and some need to be removed for TMP101AN driver class:

/**
 * @brief   Sets TMP101 Alert type and value
 *
 * @param[in] devp       pointer to the @p TMP101Driver object
 * @param[in] alert_me   the value to write to Mask/Enable register (0 to disable)
 * @param[in] alert_lim  the value to write to Alert Limit register
 *
 * @api
 */
void tmp101SetAlert(TMP101Driver *devp, uint16_t alert_me, uint16_t alert_lim) {
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == TMP101_READY,
            "tmp101SetAlert(), invalid state");

#if TMP101_USE_I2C
#if TMP101_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* TMP101_SHARED_I2C */

    buf.reg = TMP101_AD_LIM;
    buf.value = __REVSH(alert_lim);
    tmp101I2CWriteRegister(devp->config->i2cp, devp->config->saddr, buf.buf, sizeof(buf));
    buf.reg = TMP101_AD_ME;
    buf.value = __REVSH(alert_me);
    tmp101I2CWriteRegister(devp->config->i2cp, devp->config->saddr, buf.buf, sizeof(buf));

#if TMP101_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* TMP101_SHARED_I2C */
#endif /* TMP101_USE_I2C */
}

/**
 * @brief   Reads TMP101 Register as raw value.
 *
 * @param[in] devp       pointer to the @p TMP101Driver object
 * @param[in] reg        the register to read from
 *
 * @api
 */
uint16_t tmp101ReadRaw(TMP101Driver *devp, uint8_t reg) {
    i2cbuf_t buf;

    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == TMP101_READY,
            "tmp101ReadRaw(), invalid state");

#if TMP101_USE_I2C
#if TMP101_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* TMP101_SHARED_I2C */

    buf.reg = reg;
    tmp101I2CReadRegister(devp->config->i2cp, devp->config->saddr, buf.reg, buf.data, sizeof(buf.data));

#if TMP101_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* TMP101_SHARED_I2C */
#endif /* TMP101_USE_I2C */
    return __REVSH(buf.value);
}

/**
 * @brief   Reads TMP101 Shunt voltage.
 *
 * @param[in] devp       Pointer to the @p TMP101Driver object
 * @return               Shunt voltage in 1uV increments
 *
 * @api
 */
int32_t tmp101ReadShunt(TMP101Driver *devp) {
    int32_t voltage;

    osalDbgCheck(devp != NULL);

    voltage = ((int16_t)tmp101ReadRaw(devp, TMP101_AD_SHUNT) * 25)/10;

    return voltage;
}

/**
 * @brief   Reads TMP101 VBUS voltage.
 *
 * @param[in] devp       pointer to the @p TMP101Driver object
 * @return               VBUS voltage in 1uV increments
 *
 * @api
 */
uint32_t tmp101ReadVBUS(TMP101Driver *devp) {
    uint32_t voltage;

    osalDbgCheck(devp != NULL);

    voltage = tmp101ReadRaw(devp, TMP101_AD_VBUS) * 1250;

    return voltage;
}

/**
 * @brief   Reads TMP101 Current.
 * @note    Requires curr_lsb to be set in config
 *
 * @param[in] devp       pointer to the @p TMP101Driver object
 * @return               Current in increments of @p curr_lsb
 *
 * @api
 */
int32_t tmp101ReadCurrent(TMP101Driver *devp) {
    int32_t current;

    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->config->curr_lsb,
            "tmp101ReadCurrent(): invalid curr_lsb value");

    current = (int16_t)tmp101ReadRaw(devp, TMP101_AD_CURRENT) * devp->config->curr_lsb;

    return current;
}

/**
 * @brief   Reads TMP101 Power.
 * @note    Requires curr_lsb to be set in config
 *
 * @param[in] devp       pointer to the @p TMP101Driver object
 * @return               Power in increments of @p curr_lsb * 25V
 *
 * @api
 */
uint32_t tmp101ReadPower(TMP101Driver *devp) {
    uint32_t power;

    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->config->curr_lsb,
            "tmp101ReadCurrent(): invalid curr_lsb value");

    power = tmp101ReadRaw(devp, TMP101_AD_POWER) * devp->config->curr_lsb * 25;

    return power;
}

#endif // 2021-02-07



// 2021-02-07 - first draft read temperature routine

// bool read_tmp101an_temperature_v1(uint32_t option)
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

//    uint8_t sensor_addr = I2C_ADDR_SENSOR_01;
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


//    chprintf((BaseSequentialStream *) &SD2, "stub temperature reading routine:\r\n");
    chprintf((BaseSequentialStream *) &SD2, "reading temperature sensor %02X . . .\r\n", sensor_addr);

    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);

    i2c_result = i2cMasterTransmitTimeout(devp->config->i2cp, sensor_addr, buffer_tx, 1, buffer_rx, 2, TIME_INFINITE);
    i2c_flags = i2cGetErrors(devp->config->i2cp);
    i2cReleaseBus(devp->config->i2cp);

    chprintf((BaseSequentialStream *) &SD2, "temperature reg bytes back hold %u and %u.\r\n\r\n",
      buffer_rx[0], buffer_rx[1]);

    if ( i2c_result != 0 )
        { chprintf((BaseSequentialStream *) &SD2, "i2c_result holds %ld.\r\n", i2c_result); }
    if ( i2c_flags != 0 )
        { chprintf((BaseSequentialStream *) &SD2, "i2c_flags holds %ld.\r\n\r\n", i2c_flags); }


    if ( i2c_result == MSG_OK )
        return true;
    else
        return true;

}




/** @} */
