/**
 * @file    max580x.c
 * @brief   MAX580X Digital to Analog Converter.
 *
 * @addtogroup MAX580X
 * @ingrup ORESAT
 * @{
 */

#include "hal.h"
#include "max580x.h"

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
        uint8_t cmd;
        union {
            uint8_t data[2];
            uint16_t value;
        };
    };
    uint8_t txbuf[3];
} cmd_t;

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

#if (MAX580X_USE_I2C) || defined(__DOXYGEN__)
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
msg_t max580xI2CReadRegister(I2CDriver *i2cp, i2caddr_t sad, uint8_t reg,
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
 * @param[in] txbuf      buffer containing command in first byte and high
 *                       and low data bytes
 * @param[in] n          size of txbuf
 * @return               the operation status.
 * @notapi
 */
msg_t max580xI2CWriteRegister(I2CDriver *i2cp, i2caddr_t sad, uint8_t *txbuf,
        size_t n) {
    return i2cMasterTransmitTimeout(i2cp, sad, txbuf, n, NULL, 0,
            TIME_INFINITE);
}
#endif /* MAX580X_USE_I2C */

/*==========================================================================*/
/* Interface implementation.                                                */
/*==========================================================================*/

static const struct MAX580XVMT vmt_device = {
    (size_t)0,
};

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Initializes an instance.
 *
 * @param[out] devp     pointer to the @p MAX580XDriver object
 *
 * @init
 */
void max580xObjectInit(MAX580XDriver *devp) {
    devp->vmt = &vmt_device;

    devp->config = NULL;

    devp->state = MAX580X_STOP;
}

/**
 * @brief   Configures and activates MAX580X Complex Driver peripheral.
 *
 * @param[in] devp      pointer to the @p MAX580XDriver object
 * @param[in] config    pointer to the @p MAX580XConfig object
 *
 * @api
 */
void max580xStart(MAX580XDriver *devp, const MAX580XConfig *config) {
    cmd_t command;

    osalDbgCheck((devp != NULL) && (config != NULL));
    osalDbgAssert((devp->state == MAX580X_STOP) ||
            (devp->state == MAX580X_READY),
            "max580xStart(), invalid state");

    devp->config = config;
    command.value = 0;

    /* Configuring common registers.*/
#if MAX580X_USE_I2C
#if MAX580X_SHARED_I2C
    i2cAcquireBus(config->i2cp);
#endif /* MAX580X_SHARED_I2C */

    i2cStart(config->i2cp, config->i2ccfg);
    command.cmd = MAX580X_CMD_SOFTWARE | MAX580X_SOFTWARE_RST;
    max580xI2CWriteRegister(config->i2cp, config->saddr,
            command.txbuf, sizeof(cmd_t));
    command.cmd = MAX580X_CMD_REF | config->ref;
    max580xI2CWriteRegister(config->i2cp, config->saddr,
            command.txbuf, sizeof(cmd_t));
    command.cmd = MAX580X_CMD_POWER;
    command.data[1] = config->power;
    max580xI2CWriteRegister(config->i2cp, config->saddr,
            command.txbuf, sizeof(cmd_t));
    command.cmd = MAX580X_CMD_CONFIG;
    command.data[1] = config->aux;
    max580xI2CWriteRegister(config->i2cp, config->saddr,
            command.txbuf, sizeof(cmd_t));
    command.cmd = MAX580X_CMD_DEFAULT;
    command.data[1] = config->default_cfg;
    max580xI2CWriteRegister(config->i2cp, config->saddr,
            command.txbuf, sizeof(cmd_t));
    max580xI2CReadRegister(config->i2cp, config->saddr, MAX580X_CMD_NOP, command.data, sizeof(command.data));
    switch (command.data[1]) {
        case MAX5805:
            devp->res = MAX5805_RES;
            devp->range = 4096;
            break;
        case MAX5803:
            devp->res = MAX5803_RES;
            devp->range = 256;
            break;
        case MAX5804:
            devp->res = MAX5804_RES;
            devp->range = 1024;
            break;
        default:
            devp->res = 0;
            devp->range = 0;
            break;
    }

#if MAX580X_SHARED_I2C
    i2cReleaseBus(config->i2cp);
#endif /* MAX580X_SHARED_I2C */
#endif /* MAX580X_USE_I2C */
    devp->state = MAX580X_READY;
}

/**
 * @brief   Deactivates the MAX580X Complex Driver peripheral.
 *
 * @param[in] devp       pointer to the @p MAX580XDriver object
 *
 * @api
 */
void max580xStop(MAX580XDriver *devp) {
    cmd_t command;

    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state == MAX580X_STOP) || (devp->state == MAX580X_READY),
            "max580xStop(), invalid state");

    if (devp->state == MAX580X_READY) {
#if MAX580X_USE_I2C
#if MAX580X_SHARED_I2C
        i2cAcquireBus(devp->config->i2cp);
        i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* MAX580X_SHARED_I2C */

        /* Reset to input.*/
        command.cmd = MAX580X_CMD_SOFTWARE | MAX580X_SOFTWARE_RST;
        max580xI2CWriteRegister(devp->config->i2cp, devp->config->saddr,
                command.txbuf, sizeof(cmd_t));

        i2cStop(devp->config->i2cp);
#if MAX580X_SHARED_I2C
        i2cReleaseBus(devp->config->i2cp);
#endif /* MAX580X_SHARED_I2C */
#endif /* MAX580X_USE_I2C */
    }
    devp->state = MAX580X_STOP;
}

/**
 * @brief   Reads MAX580X DAC Register as raw value.
 *
 * @param[in] devp       pointer to the @p MAX580XDriver object
 * @param[in] reg        the DAC register to read from
 *
 * @api
 */
uint16_t max580xReadRaw(MAX580XDriver *devp, max580x_reg_t reg) {
    cmd_t command;

    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == MAX580X_READY,
            "max580xReadRaw(), invalid state");

#if MAX580X_USE_I2C
#if MAX580X_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* MAX580X_SHARED_I2C */

    command.cmd = reg;
    max580xI2CReadRegister(devp->config->i2cp, devp->config->saddr, command.cmd, command.data, sizeof(command.data));

#if MAX580X_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* MAX580X_SHARED_I2C */
#endif /* MAX580X_USE_I2C */
    return MAX580X_DAC2VAL(command.value, devp->res);
}

/**
 * @brief   Writes MAX580X DAC Register as raw value.
 *
 * @param[in] devp       pointer to the @p MAX580XDriver object
 * @param[in] value      the value to write to a DAC register
 * @param[in] reg        the DAC register to write the value into
 *
 * @api
 */
void max580xWriteRaw(MAX580XDriver *devp, uint16_t value, max580x_reg_t reg) {
    cmd_t command;

    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == MAX580X_READY,
            "max580xWriteRaw(), invalid state");

#if MAX580X_USE_I2C
#if MAX580X_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* MAX580X_SHARED_I2C */

    command.cmd = reg;
    command.value = MAX580X_VAL2DAC(value, devp->res);
    max580xI2CWriteRegister(devp->config->i2cp, devp->config->saddr, command.txbuf, 3);

#if MAX580X_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* MAX580X_SHARED_I2C */
#endif /* MAX580X_USE_I2C */
}

/**
 * @brief   Reads MAX580X DAC Register as a voltage.
 * @details This only works when using an internal reference and assumes sufficient supply.
 *
 * @param[in] devp       pointer to the @p MAX580XDriver object
 * @param[in] reg        the DAC register to read from
 *
 * @api
 */
uint32_t max580xReadVoltage(MAX580XDriver *devp, max580x_reg_t reg) {
    uint32_t voltage;

    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->config->ref != MAX580X_REF_EXT,
            "max580xReadVoltage(), REF_EXT not allowed");

    /* TODO: Clean this up, it's terrible */
    voltage = max580xReadRaw(devp, reg) * 10;
    switch (devp->config->ref & 3U) {
        case MAX580X_REF_2500:
            voltage = voltage * 2500;
            break;
        case MAX580X_REF_2048:
            voltage = voltage * 2048;
            break;
        case MAX580X_REF_4096:
            voltage = voltage * 4096;
            break;
    }
    voltage /= devp->range;

    return voltage;
}

/**
 * @brief   Writes MAX580X DAC Register as a voltage.
 * @details This only works when using an internal reference and assumes sufficient supply.
 *
 * @param[in] devp       pointer to the @p MAX580XDriver object
 * @param[in] voltage    the voltage to write to a DAC register
 * @param[in] reg        the DAC register to write the value into
 *
 * @api
 */
void max580xWriteVoltage(MAX580XDriver *devp, uint32_t voltage, max580x_reg_t reg) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->config->ref != MAX580X_REF_EXT,
            "max580xWriteVoltage(), REF_EXT not allowed");

    /* TODO: Clean this up, it's terrible */
    /* TODO: Bounds checking */
    voltage = voltage - (voltage % 5);
    voltage *= devp->range;
    switch (devp->config->ref & 3U) {
        case MAX580X_REF_2500:
            voltage /= 25000;
            break;
        case MAX580X_REF_2048:
            voltage /= 20480;
            break;
        case MAX580X_REF_4096:
            voltage /= 40960;
            break;
    }
    max580xWriteRaw(devp, voltage, reg);
}

/**
 * @brief   Execute MAX580X LOAD instruction.
 *
 * @param[in] devp       pointer to the @p MAX580XDriver object
 *
 * @api
 */
void max580xLoad(MAX580XDriver *devp) {
    cmd_t command;
    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == MAX580X_READY,
            "max580xReadRaw(), invalid state");

#if MAX580X_USE_I2C
#if MAX580X_SHARED_I2C
    i2cAcquireBus(devp->config->i2cp);
    i2cStart(devp->config->i2cp, devp->config->i2ccfg);
#endif /* MAX580X_SHARED_I2C */

    command.cmd = MAX580X_CMD_LOAD;
    command.value = 0;
    max580xI2CWriteRegister(devp->config->i2cp, devp->config->saddr, command.txbuf, sizeof(cmd_t));

#if MAX580X_SHARED_I2C
    i2cReleaseBus(devp->config->i2cp);
#endif /* MAX580X_SHARED_I2C */
#endif /* MAX580X_USE_I2C */
}

/** @} */
