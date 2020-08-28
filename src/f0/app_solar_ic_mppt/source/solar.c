#include "solar.h"
#include "ina226.h"
#include "CANopen.h"
#include "chprintf.h"

#define CURR_LSB    10  /* 10uA/bit */
#define RSENSE      100 /* 0.1 ohm  */
#define SLEEP_MS    500
#define STEP_SIZE   5
#define DAC_VDDA_MV 3000 /* 3.3 mV and 3.0 mv when powered from debug board */

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
 * @param[in] dacp      DAC driver pointer.
 * @param[in] chan      DAC channel.
 * @param[in] mv        output volts in mv.
 * @param[in] busv      bus volts in mv.
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
 * @param[in] i_out      current in mA.
 * @return    Iadj_v     DAC output in millivolts.
 */    
uint32_t calc_iadj(uint32_t i_out)
{
  /* Per page 7 of LT1618 datasheet
   * V_Isense = (1.263 - 0.8* v_iadj)/25
   * => 25 * i_out * Rsense  = 1.263 - 0.8 * V_iadj
   * Multiplying 4000 on both sides
   * 100000 * i_out * Rsense = 5052 - 3200 * V_iadj
   * Now i_out is in mA, Rsense is in mOhm and V_iadj is in mV
   * => 100000 * i_out/1000 * Rsense/1000 = 5052 - 3200 * V_iadj/1000
   * => 100 * i_out * Rsense = 5052000 - 3200 * V_iadj
   * => V_adj = (5052000 - i_out * Rsense * 100)/3200
   */
  return ((5052000 - i_out * RSENSE * 100) / 3200);
}

/**
 * @brief Maximum power point tracking algorithm for Solar cells
 * @param[in] volt      Solar cell bus voltage in mV.
 * @param[in] curr      Solar cell current in mA.
 * @param[in] pwr       Power output from solar cells. 
 * @return Maximum current to be drawn from solar cells in mA
 * TODO: Find min/max limits of step size. Also check the units that work the best
 *       Average a few samples to reduce noise
 *       reduce max current limit immediatly if current is lower that the allowed current.(brownout condition)
 *       increase max current limit immediatly if voltage is higher that expected.(shutdown condition)
 *       
 */
int32_t calc_mppt(uint16_t volt, int16_t curr, uint16_t pwr)
{

    /* The values from the previous iteration of the loop */
    static uint16_t prev_volt = 0;
    static uint16_t prev_curr = 0;
    static uint16_t prev_pwr = 0;
    /* programmed max current from previous iteration*/
    /* TODO: Update algorithm to use it to save from high to low illumination*/
    static int32_t i_in;
    
    /* Simple IC MPPT Algorithm */
    /* This should be run first to check step size and confirm other DAC and other working */
    int16_t delta_v = volt - prev_volt;
    int16_t delta_i = curr - prev_curr;
    int16_t delta_p = pwr  - prev_pwr;
    
    if (delta_i == 0) {
        if (delta_i != 0) {
            if (delta_v > 0) {
                i_in += STEP_SIZE;
            } else {
                i_in -= STEP_SIZE;
            }
        }
    } else {
        if (delta_p/delta_i != 0) {
            if (delta_p/delta_i > 0) {
                i_in += STEP_SIZE;
            } else {
                i_in -= STEP_SIZE;
            }
        }
    } 
       
    prev_volt = volt;
    prev_curr = curr;
    prev_pwr  = pwr;
    /* End IC MPPT Algorithm */
    
 
    /* Hybrid IC MPPT Algorithm */
    /* Better noise handling and should work with changing illumination without reset*/
    /* This should be run after previous algorithm runs successfully */
    //static uint16_t count, sum_volt, sum_curr, sum_pwr;
    //uint16_t avg_volt, avg_curr, avg_pwr, delta_v, delta_i, delta_p;
    //
    // /* We have lower current than allowed means lower illumination and chances of brownout */
    //if (curr < THRESHOLD_CURR * i_in){
    //  i_in = PCT_MAX_CURR*curr;
    //  count = 0;
    //  sum_volt = 0;
    //  sum_curr = 0;
    //  sum_pwr  = 0;   
    //}  
    //
    //if ( count < CNT_FOR_AVG) {
    //  count++;
    //  sum_volt += volt;
    //  sum_curr += curr;
    //  sum_pwr  += pwr ;
    //} else {
    //  count = 0;
    //  avg_volt = sum_volt/CNT_FOR_AVG;
    //  avg_curr = sum_curr/CNT_FOR_AVG;
    //  avg_pwr  = sum_pwr /CNT_FOR_AVG;
    //  sum_volt = 0;
    //  sum_curr = 0;
    //  sum_pwr  = 0;
    //  delta_v = avg_volt - prev_volt;
    //  delta_i = avg_curr - prev_curr;
    //  delta_p = avg_pwr  - prev_pwr; 
    //       
    //  if (delta_i == 0) {
    //    if (delta_i != 0) {
    //        if (delta_v > 0) {
    //            i_in += STEP_SIZE;
    //        } else {
    //            i_in -= STEP_SIZE;
    //        }
    //    }
    //  } else {
    //    if (delta_p/delta_i != 0) {
    //        if (delta_p/delta_i > 0) {
    //            i_in += 4*STEP_SIZE;
    //        } else {
    //            i_in -= STEP_SIZE/2;
    //        }
    //    }
    //  }
    //}   
    //
    //prev_volt = avg_volt;
    //prev_curr = avg_curr;
    //prev_pwr  = avg_pwr; 
    /* End Hybrid IC MPPT Algorithm */   
    
    
    
    
    /* bounds checks for current */
    if (i_in < 0) {
      i_in = 0;
    }
    if (i_in > 500) {
      i_in = 500;
    } 
    return i_in;
}

/* Main solar management thread */
THD_WORKING_AREA(solar_wa, 0x400);
THD_FUNCTION(solar, arg)
{
    (void)arg;
    uint32_t iadj_v = 1500;
    uint32_t i_in=0;
    
    
    /* Start up drivers */
    ina226ObjectInit(&ina226dev);
    dacStart(&DACD1, &dac1cfg);
    ina226Start(&ina226dev, &ina226config);

    palSetLine(LINE_LED);
    
    
    chprintf((BaseSequentialStream *) &SD2, "\r\n ****** Max inoput curr: %d, Bias Volt: %d mv \r\n", i_in, iadj_v);
    while(!chThdShouldTerminateX()){
      chThdSleepMilliseconds(SLEEP_MS);
      //chprintf((BaseSequentialStream *) &SD2, "\r\n%d\r\n", i++);
      //palToggleLine(LINE_LED);
      
      /* Get present values */
      OD_solarPanel.voltage = ina226ReadVBUS(&ina226dev); //VBUS voltage in 0.01mV increments (10uV)
      OD_solarPanel.current = ina226ReadCurrent(&ina226dev); //Current in increments of 10uA
      OD_solarPanel.power = ina226ReadPower(&ina226dev); //Power in increments of 10uA * 25V
      //chprintf((BaseSequentialStream *) &SD2, "\r\nVolt: 0x%X, Current: 0x%X, Power: 0x%X, \r\n", OD_solarPanel.voltage, OD_solarPanel.current, OD_solarPanel.power);
      chprintf((BaseSequentialStream *) &SD2, "Volt: %u, Current: %u, Power: %u, \r\n", OD_solarPanel.voltage/100, OD_solarPanel.current/100, OD_solarPanel.power);
      
      
      /* Calculate iadj. Volt and curr are converted to mV and mA */
      i_in = calc_mppt(OD_solarPanel.voltage/100, OD_solarPanel.current/100, OD_solarPanel.power);
      iadj_v = calc_iadj(i_in);
      dacPutMillivolts(&DACD1, 0, iadj_v) ;
      chprintf((BaseSequentialStream *) &SD2, "Max input curr: %d, Bias Volt: %d mv \r\n", i_in, iadj_v);
      
      
    }


    /* Stop drivers */
    dacStop(&DACD1);
    ina226Stop(&ina226dev);

    chThdExit(MSG_OK);
}
