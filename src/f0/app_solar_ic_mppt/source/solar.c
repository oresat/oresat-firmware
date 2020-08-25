#include "solar.h"
#include "ina226.h"
#include "CANopen.h"
#include "chprintf.h"

#define CURR_LSB    10  /* 10uA/bit */
#define RSENSE      100 /* 0.1 ohm  */
#define SLEEP_MS    500
#define STEP_SIZE   5
#define DAC_VDDA_MV 3300 /* 3.3 mV */

static const I2CConfig i2cconfig = {
    STM32_TIMINGR_PRESC(0xBU) |
    STM32_TIMINGR_SCLDEL(0x4U) | STM32_TIMINGR_SDADEL(0x2U) |
    STM32_TIMINGR_SCLH(0xFU)  | STM32_TIMINGR_SCLL(0x13U),
    0,
    0
};

static const INA226Config ina226config = {
    &I2CD2,
    &i2cconfig,
    INA226_SADDR,
    INA226_CONFIG_MODE_SHUNT_VBUS | INA226_CONFIG_MODE_CONT |
    INA226_CONFIG_VSHCT_1100US | INA226_CONFIG_VBUSCT_1100US |
    INA226_CONFIG_AVG_1,
    (5120000/(RSENSE*CURR_LSB)),
    CURR_LSB
};

/* DAC1 configuration */
static const DACConfig dac1cfg = {
  .init         = 1861U,                /* Initialize DAC to 1.5V (1500*4096)/3300 */
  .datamode     = DAC_DHRM_12BIT_RIGHT, /* 12 bit, right aligned */
  .cr           = 0                     /* No control reg options */
};

static INA226Driver ina226dev;

/**
 * @brief control DAC output in millivolts.
 *
 */
void dacPutMillivolts(DACDriver *dacp, dacchannel_t chan, uint32_t mv) {
    /* Per section 14.5.3 of the STM32F0x1 ref manual,
     * Vout(mV) = VDDA(mV) * (reg_val / 4096)
     * so, reg_val = (Vout * 4096) / VDDA
     */
    dacsample_t val = (mv << 12) / DAC_VDDA_MV;
    dacPutChannelX(dacp, chan, val);
}

/**
 * @brief Calculates Iadj_v required for a particular max current.
 *
 * @return Iadj_v in millivolts.
 */
uint32_t calc_iadj(uint32_t i_out)
{
    return ((5052000 - i_out * RSENSE) / 3200);
}

int32_t calc_mppt(uint16_t volt, int16_t curr, uint16_t pwr)
{
    /* Amount to adjust iadj_v */
    int32_t adjust=0;

    /* The values from the previous iteration of the loop */
    static uint16_t prev_volt = 0;
    static int16_t  prev_curr = 0;
    static uint16_t prev_pwr = 0;
    int16_t delta_v = volt - prev_volt;
    int16_t delta_i = curr - prev_curr;
    int16_t delta_p = pwr  - prev_pwr;
    prev_volt = volt;
    prev_curr = curr;
    prev_pwr  = pwr;

    /* Start IC MPPT Algorithm */

    /* End IC MPPT Algorithm */

    return adjust;
}

/* Main solar management thread */
THD_WORKING_AREA(solar_wa, 0x400);
THD_FUNCTION(solar, arg)
{
    (void)arg;
    uint32_t iadj_v = 1500;
    uint8_t reg[1]={0x00};
    uint8_t data[2]={5,5};
    uint8_t i=0;
    
    msg_t msg;
    i2cflags_t  flags;
    
    /* Start up drivers */
    ina226ObjectInit(&ina226dev);
    dacStart(&DACD1, &dac1cfg);
    ina226Start(&ina226dev, &ina226config);

    //dacPutMillivolts(&DACD1, 0, iadj_v) ;
    
    
    
    chprintf((BaseSequentialStream *) &SD2, "00 Config Reg: %X\r\n", ina226ReadRaw(&ina226dev, (uint8_t)0x00));
    chprintf((BaseSequentialStream *) &SD2, "01 Shunt Volt Reg: %X\r\n", ina226ReadRaw(&ina226dev, (uint8_t)0x01));
    chprintf((BaseSequentialStream *) &SD2, "02 Bus Volt Re: %X\r\n", ina226ReadRaw(&ina226dev, (uint8_t)0x02));
    chprintf((BaseSequentialStream *) &SD2, "03 Power Reg: %X\r\n", ina226ReadRaw(&ina226dev, (uint8_t)0x03));
    chprintf((BaseSequentialStream *) &SD2, "04 Current Reg: %X\r\n", ina226ReadRaw(&ina226dev, (uint8_t)0x04));
    chprintf((BaseSequentialStream *) &SD2, "05 Calib Reg: %X\r\n", ina226ReadRaw(&ina226dev, (uint8_t)0x05));
    chprintf((BaseSequentialStream *) &SD2, "06 Mask Reg: %X\r\n", ina226ReadRaw(&ina226dev, (uint8_t)0x06));
    chprintf((BaseSequentialStream *) &SD2, "07 Alert Reg: %X\r\n", ina226ReadRaw(&ina226dev, (uint8_t)0x07));
    
    chprintf((BaseSequentialStream *) &SD2, "FE Mfg ID: %X\r\n", ina226ReadRaw(&ina226dev, (uint8_t)0xFE));
    chprintf((BaseSequentialStream *) &SD2, "FF Die ID: %X\r\n", ina226ReadRaw(&ina226dev, (uint8_t)0xFF));
    
    
    /*
    chprintf((BaseSequentialStream *) &SD2, "\r\n=====\r\n");
    
    i2cAcquireBus(&I2CD1);
    msg = i2cMasterTransmitTimeout(&I2CD1, 0x44, reg, 1, data, 2, TIME_INFINITE);
    i2cReleaseBus(&I2CD1);
    flags = i2cGetErrors 	( 	&I2CD1	);    
    chprintf((BaseSequentialStream *) &SD2, "Reg: 0x%X Mfg ID: 0x%X, msg: %d, flags: %d\r\n", *reg, data[1], msg, flags);
    
    
    chprintf((BaseSequentialStream *) &SD2, "\r\n#\r\n");
    i2cInit();
    i2cStart(&I2CD2, &i2cconfig);
    //i2cAcquireBus(&I2CD1);
    while(i<244){
      msg = i2cMasterTransmitTimeout(&I2CD2, i, reg, 1, data, 2, TIME_INFINITE);
      flags = i2cGetErrors 	( 	&I2CD2	);    
      chprintf((BaseSequentialStream *) &SD2, "i2cAddress: 0x%X Reg: 0x%X Mfg ID: 0x%X, msg: %d, flags: %d\r\n",i, *reg, *data, msg, flags);
      flags = 0;
      i++;
      chThdSleepMilliseconds(100);
    }
    //i2cReleaseBus(&I2CD1);
    */
    
    
    while(!chThdShouldTerminateX()){
      chThdSleepMilliseconds(SLEEP_MS);
      //chprintf((BaseSequentialStream *) &SD2, "\r\n%d\r\n", i++);
      palToggleLine(LINE_LED);
      
      /* Get present values */
      OD_solarPanel.voltage = ina226ReadVBUS(&ina226dev);
      OD_solarPanel.current = ina226ReadCurrent(&ina226dev);
      OD_solarPanel.power = ina226ReadPower(&ina226dev);
      //chprintf((BaseSequentialStream *) &SD2, "\r\nVolt: 0x%X, Current: 0x%X, Power: 0x%X, \r\n", OD_solarPanel.voltage, OD_solarPanel.current, OD_solarPanel.power);
      //chprintf((BaseSequentialStream *) &SD2, "Volt: %u, Current: %u, Power: %u, \r\n", OD_solarPanel.voltage, OD_solarPanel.current, OD_solarPanel.power);
      
      
    }


    //while (!chThdShouldTerminateX()) {
    while (1) {
        //chThdSleepMilliseconds(SLEEP_MS);
        chThdSleepMilliseconds(500);

        /* Get present values */
        //OD_solarPanel.voltage = ina226ReadVBUS(&ina226dev);
        //OD_solarPanel.current = ina226ReadCurrent(&ina226dev);
        //OD_solarPanel.power = ina226ReadPower(&ina226dev);
        //chprintf((BaseSequentialStream *) &SD2, "\r\n%d\r\n", i++);

        /* Calculate iadj */
        //iadj_v += calc_mppt(OD_solarPanel.voltage, OD_solarPanel.current, OD_solarPanel.power);

        /* Write new iadj value */
        //dacPutMillivolts(&DACD1, 0, iadj_v) ;
        //palToggleLine(LINE_LED);
    }

    /* Stop drivers */
    //dacStop(&DACD1);
    //ina226Stop(&ina226dev);

    chThdExit(MSG_OK);
}
