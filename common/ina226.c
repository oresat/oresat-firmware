/* INA226 Digital to Analog Converter */

#include "hal.h"
#include "ina226.h"

// INA226 Register Addresses
#define INA226_AD_CONFIG                    0x00U
#define INA226_AD_SHUNT                     0x01U
#define INA226_AD_VBUS                      0x02U
#define INA226_AD_POWER                     0x03U
#define INA226_AD_CURRENT                   0x04U
#define INA226_AD_CAL                       0x05U
#define INA226_AD_ME                        0x06U
#define INA226_AD_LIM                       0x07U
#define INA226_AD_MFG_ID                    0xFEU
#define INA226_AD_DIE_ID                    0xFFU


#define INA226_CONFIG_RST_Pos               (15U)
#define INA226_CONFIG_RST_Msk               (0x1U << INA226_CONFIG_RST_Pos)
#define INA226_CONFIG_RST                   INA226_CONFIG_RST_Msk


/**
 * @name    INA226 Shunt Voltage register fields
 * @{
 */
#define INA226_SHUNT_Pos                    (0U)
#define INA226_SHUNT_Msk                    (0xFFFFU << INA226_SHUNT_Pos)
#define INA226_SHUNT                        INA226_SHUNT_Msk
/** @} */

/**
 * @name    INA226 VBUS Voltage register fields
 * @{
 */
#define INA226_VBUS_Pos                     (0U)
#define INA226_VBUS_Msk                     (0x7FFFU << INA226_VBUS_Pos)
#define INA226_VBUS                         INA226_VBUS_Msk
/** @} */

/**
 * @name    INA226 Power register fields
 * @{
 */
#define INA226_POWER_Pos                    (0U)
#define INA226_POWER_Msk                    (0xFFFFU << INA226_POWER_Pos)
#define INA226_POWER                        INA226_POWER_Msk
/** @} */

/**
 * @name    INA226 Current register fields
 * @{
 */
#define INA226_CURRENT_Pos                  (0U)
#define INA226_CURRENT_Msk                  (0xFFFFU << INA226_CURRENT_Pos)
#define INA226_CURRENT                      INA226_CURRENT_Msk
/** @} */

/**
 * @name    INA226 Calibration register fields
 * @{
 */
#define INA226_CAL_Pos                      (0U)
#define INA226_CAL_Msk                      (0x7FFFU << INA226_CAL_Pos)
#define INA226_CAL                          INA226_CAL_Msk
/** @} */

/**
 * @name    INA226 Alert Mask/Enable register fields
 * @{
 */
#define INA226_ME_LEN_Pos                   (0U)
#define INA226_ME_LEN_Msk                   (0x1U << INA226_ME_LEN_Pos)
#define INA226_ME_LEN                       INA226_ME_LEN_Msk
#define INA226_ME_APOL_Pos                  (1U)
#define INA226_ME_APOL_Msk                  (0x1U << INA226_ME_APOL_Pos)
#define INA226_ME_APOL                      INA226_ME_APOL_Msk
#define INA226_ME_OVF_Pos                   (2U)
#define INA226_ME_OVF_Msk                   (0x1U << INA226_ME_OVF_Pos)
#define INA226_ME_OVF                       INA226_ME_OVF_Msk
#define INA226_ME_CVRF_Pos                  (3U)
#define INA226_ME_CVRF_Msk                  (0x1U << INA226_ME_CVRF_Pos)
#define INA226_ME_CVRF                      INA226_ME_CVRF_Msk
#define INA226_ME_AFF_Pos                   (4U)
#define INA226_ME_AFF_Msk                   (0x1U << INA226_ME_AFF_Pos)
#define INA226_ME_AFF                       INA226_ME_AFF_Msk
#define INA226_ME_CNVR_Pos                  (10U)
#define INA226_ME_CNVR_Msk                  (0x1U << INA226_ME_CNVR_Pos)
#define INA226_ME_CNVR                      INA226_ME_CNVR_Msk
#define INA226_ME_POL_Pos                   (11U)
#define INA226_ME_POL_Msk                   (0x1U << INA226_ME_POL_Pos)
#define INA226_ME_POL                       INA226_ME_POL_Msk
#define INA226_ME_BUL_Pos                   (12U)
#define INA226_ME_BUL_Msk                   (0x1U << INA226_ME_BUL_Pos)
#define INA226_ME_BUL                       INA226_ME_BUL_Msk
#define INA226_ME_BOL_Pos                   (13U)
#define INA226_ME_BOL_Msk                   (0x1U << INA226_ME_BOL_Pos)
#define INA226_ME_BOL                       INA226_ME_BOL_Msk
#define INA226_ME_SUL_Pos                   (14U)
#define INA226_ME_SUL_Msk                   (0x1U << INA226_ME_SUL_Pos)
#define INA226_ME_SUL                       INA226_ME_SUL_Msk
#define INA226_ME_SOL_Pos                   (15U)
#define INA226_ME_SOL_Msk                   (0x1U << INA226_ME_SOL_Pos)
#define INA226_ME_SOL                       INA226_ME_SOL_Msk
/** @} */

/**
 * @name    INA226 Alert Limit register fields
 * @{
 */
#define INA226_LIM_Pos                      (0U)
#define INA226_LIM_Msk                      (0xFFFFU << INA226_LIM_Pos)
#define INA226_LIM                          INA226_LIM_Msk
/** @} */

/**
 * @name    INA226 Manufacturer ID register fields
 * @{
 */
#define INA226_MFG_ID_Pos                   (0U)
#define INA226_MFG_ID_Msk                   (0xFFFFU << INA226_MFG_ID_Pos)
#define INA226_MFG_ID                       INA226_MFG_ID_Msk
/** @} */

/**
 * @name    INA226 Die ID register fields
 * @{
 */
#define INA226_DIE_ID_RID_Pos               (0U)
#define INA226_DIE_ID_RID_Msk               (0xFU << INA226_DIE_ID_RID_Pos)
#define INA226_DIE_ID_RID                   INA226_DIE_ID_RID_Msk
#define INA226_DIE_ID_DID_Pos               (4U)
#define INA226_DIE_ID_DID_Msk               (0xFFFU << INA226_DIE_ID_DID_Pos)
#define INA226_DIE_ID_DID                   INA226_DIE_ID_DID_Msk
/** @} */


static msg_t read_register(INA226Driver *devp, uint8_t reg, uint16_t * val) {
    I2CDriver *i2cp = devp->config->i2cp;
    i2caddr_t sad = devp->config->saddr;

    uint8_t buf[2] = {};
    i2cAcquireBus(i2cp);
    msg_t r = i2cMasterTransmitTimeout(i2cp, sad, &reg, 1, buf, sizeof(buf), TIME_MS2I(50));
    i2cReleaseBus(i2cp);
    *val = buf[1] | buf[0] << 8;
    return r;
}

static msg_t write_register(INA226Driver *devp, uint8_t reg, uint16_t val) {
    I2CDriver *i2cp = devp->config->i2cp;
    i2caddr_t sad = devp->config->saddr;

    uint8_t buf[3] = {reg, (val >> 8) & 0xFF, val & 0xFF};
    i2cAcquireBus(i2cp);
    msg_t r = i2cMasterTransmitTimeout(i2cp, sad, buf, sizeof(buf), NULL, 0, TIME_MS2I(50));
    i2cReleaseBus(i2cp);
    return r;
}

void ina226ObjectInit(INA226Driver *devp) {
    devp->config = NULL;
    devp->state = INA226_STOP;
}

msg_t ina226Start(INA226Driver *devp, const INA226Config *config) {
    osalDbgCheck((devp != NULL) && (config != NULL));
    osalDbgAssert((devp->state == INA226_STOP) ||
            (devp->state == INA226_READY),
            "ina226Start(), invalid state");
    osalDbgCheck(config->i2cp->state > I2C_STOP);

    devp->state = INA226_STOP;
    devp->config = config;

    msg_t ret = MSG_OK;

    // Reset chip
    ret = write_register(devp, INA226_AD_CONFIG, INA226_CONFIG_RST);
    if(ret != MSG_OK) {
        return ret;
    }

    int loop_count = 0;
    for(; loop_count < 10; ++loop_count) {
        uint16_t buf;
        ret = read_register(devp, INA226_AD_CONFIG, &buf);
        if(ret != MSG_OK) {
            return ret;
        }
        if(!(buf & INA226_CONFIG_RST)) {
            break;
        }

    }
    if(loop_count >= 10) {
        return MSG_RESET;
    }

    // Table 7-3, in samples
    uint16_t AVG[8] = {1, 4, 16, 64, 128, 256, 512, 1024};
    // Tables 7-4 and 7-5, in uS
    uint16_t VCT[8] = {140, 204, 332, 558, 1100, 2116, 4156, 8244};


    uint16_t avg    = AVG[(config->cfg & INA226_CONFIG_AVG_Msk) >> INA226_CONFIG_AVG_Pos];
    uint16_t vbusct = VCT[(config->cfg & INA226_CONFIG_VBUSCT_Msk) >> INA226_CONFIG_VBUSCT_Pos];
    uint16_t vshct  = VCT[(config->cfg & INA226_CONFIG_VSHCT_Msk) >> INA226_CONFIG_VSHCT_Pos];

    devp->t_conversion = TIME_US2I(avg * (vbusct + vshct));
    // Configure common registers
    ret = write_register(devp, INA226_AD_CONFIG, config->cfg);
    if(ret != MSG_OK) {
        return ret;
    }

    // Based on datasheet equation (1),
    // CAL = 0.00512 / (CURR_LSB * Rshunt)
    // Since CURR_LSB is in uA and Rshunt is in mOhm
    // CAL = 0.00512 / (CURR_LSB * Rshunt * 10^-9)
    uint16_t cal = 5120000 / (config->curr_lsb_uA * config->rshunt_mOhm);
    ret = write_register(devp, INA226_AD_CAL, cal);
    if(ret != MSG_OK) {
        return ret;
    }

    devp->state = INA226_READY;
    return MSG_OK;
}

msg_t ina226Stop(INA226Driver *devp) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert((devp->state == INA226_STOP) || (devp->state == INA226_READY),
            "ina226Stop(), invalid state");

    msg_t ret = MSG_OK;
    if (devp->state == INA226_READY) {
        ret = write_register(devp, INA226_AD_CONFIG, INA226_CONFIG_RST);
    }
    devp->state = INA226_STOP;
    return ret;
}

msg_t ina226ReadShunt(INA226Driver *devp, int32_t *voltage_uV) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == INA226_READY,
            "ina226ReadShunt(), invalid state");

    uint16_t val = 0;
    const msg_t ret = read_register(devp, INA226_AD_SHUNT, &val);

    // Datasheet 7.1.2: Shunt reg value is twos complement, LSB 2.5uV.
    if( ret == MSG_OK ) {
        *voltage_uV = ((int32_t) ((int16_t) val) * 25)/10;
    }

    return ret;
}

msg_t ina226ReadVBUS(INA226Driver *devp, int32_t *voltage_mV) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == INA226_READY,
            "ina226ReadVBUS(), invalid state");

    uint16_t val = 0;
    const msg_t ret = read_register(devp, INA226_AD_VBUS, &val);

    // Datasheet 7.1.3: Bus voltage is always positive, LSB 1.25mV
    if( ret == MSG_OK ) {
        // Double type cast to preserve sign, going straight from uint16_t ->
        // int32_t doesn't set sign bits.
        *voltage_mV = (((int32_t)(int16_t) val) * 1250) / 1000;
    }

    return ret;
}

msg_t ina226ReadCurrent(INA226Driver *devp, int32_t *current_uA) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == INA226_READY,
            "ina226ReadCurrent(), invalid state");
    osalDbgAssert(devp->config->curr_lsb_uA,
            "ina226ReadCurrent(): invalid curr_lsb_uA value");

    uint16_t val = 0;
    const msg_t ret = read_register(devp, INA226_AD_CURRENT, &val);

    if( ret == MSG_OK ) {
        *current_uA = ((int16_t)val) * devp->config->curr_lsb_uA;
    }

    return ret;
}

msg_t ina226ReadPower(INA226Driver *devp, int32_t *power_mW) {
    osalDbgCheck(devp != NULL);
    osalDbgAssert(devp->state == INA226_READY,
            "ina226ReadPower(), invalid state");
    osalDbgAssert(devp->config->curr_lsb_uA,
            "ina226ReadPower(): invalid curr_lsb_uA value");


    uint16_t val = 0;
    const msg_t ret = read_register(devp, INA226_AD_POWER, &val);

    // Datasheet 7.1.4: LSB is 25 * (Current_LSB as watts). See also the
    // paragraph above equation 4 for a worked example.
    if(ret == MSG_OK) {
        *power_mW = (((int16_t)val) * 25 * devp->config->curr_lsb_uA) / 1000;
    }

    return ret;
}

msg_t ina226TriggerOneShotConversion(INA226Driver *devp) {
    // Datasheet 6.3.1: In triggered mode, writing any of the triggered convert
    // modes into the Configuration Register (00h) triggers a single-shot conversion
    osalDbgCheck(devp != NULL);
    uint16_t val = devp->config->cfg | INA226_CONFIG_MODE_SHUNT_VBUS;
    const msg_t ret = write_register(devp, INA226_AD_CONFIG, val);
    return ret;
};

msg_t ina226CheckConversionStatus(INA226Driver *devp, bool *conversion_ready) {
    // Datasheet 7.1.7: The Conversion Ready Flag bit is set after all
    // conversions, averaging, and multiplications are complete
    osalDbgCheck(devp != NULL);
    uint16_t val = 0;
    msg_t ret = read_register(devp, INA226_AD_ME, &val);
    bool ready = (val & INA226_ME_CVRF_Msk) >> INA226_ME_CVRF_Pos;
    if (ret == MSG_OK) {
        *conversion_ready = ready;
    }
    return ret;
}
