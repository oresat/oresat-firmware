#include "solar.h"
#include "ina226.h"
#include "CANopen.h"
#include "chprintf.h"

#define CURR_LSB           20  /* 20uA/bit */
#define RSENSE             100 /* 0.1 ohm  */
#define SLEEP_MS           500                //TODO: decrese the value. This is for testing.
#define STEP_SIZE          1
#define CURR_THRES_SENS    20  /* 20 uA. Current Threshold Sensitivity */
#define MIN_STEP_SIZE      1
#define MAX_STEP_SIZE      25
#define STEP_SIZE_FACTOR   10
#define DAC_VDDA_MV        3333 /* 3.333 mV and 3.0 mv when powered from debug board */

static const I2CConfig i2cconfig = {
    STM32_TIMINGR_PRESC(0xBU) |
    STM32_TIMINGR_SCLDEL(0x4U) | STM32_TIMINGR_SDADEL(0x2U) |
    STM32_TIMINGR_SCLH(0xFU)  | STM32_TIMINGR_SCLL(0x13U),
    0,
    0
};

/* Based on INA226 datasheet, page 15, Equation (2)
 * CURR_LSB = Max Current / 2^15
 * So, with CURR_LSB = 20 uA/bit, Max current = 655 mA 
 * 
 * Based on equation (1), 
 * CAL = 0.00512 / (CURR_LSB * Rsense)
 * Since CURR_LSB is in uA and Rsense is in mOhm
 * CAL = 0.00512 / (CURR_LSB * Rsense * 10^-9)
 */ 
static const INA226Config ina226config = {
    &I2CD2,
    &i2cconfig,
    INA226_SADDR,
    INA226_CONFIG_MODE_SHUNT_VBUS | INA226_CONFIG_MODE_CONT |
    INA226_CONFIG_VSHCT_1100US | INA226_CONFIG_VBUSCT_1100US |
    INA226_CONFIG_AVG_16,                   //MUST change it to 16.
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
 * @param[in] curr      Solar cell current in uA.
 * @param[in] pwr       Power output from solar cells in microWatts. 
 * @return Maximum current to be drawn from solar cells in mA
 * TODO: Find min/max limits of step size. Also check the units that work the best
 *       Average a few samples to reduce noise
 *       reduce max current limit immediatly if current is lower that the allowed current.(brownout condition)
 *       increase max current limit immediatly if voltage is higher that expected.(shutdown condition)
 *       
 */
int32_t calc_mppt(int32_t volt, int32_t curr, int32_t pwr)
{

    /* The values from the previous iteration of the loop */
    static int32_t prev_volt = 0;
    static int32_t prev_curr = 0;
    static int32_t prev_pwr = 0;
    /* programmed max current from previous iteration*/
    /* TODO: Update algorithm to use it to save from high to low illumination*/
    static int32_t i_in;
    
    /* Simple IC MPPT Algorithm */
    /* This should be run first to check step size and confirm other DAC and other working */
    int32_t delta_v = volt - prev_volt;
    int32_t delta_i = curr - prev_curr;
    int32_t delta_p = pwr  - prev_pwr;
    
    int32_t dp_di;
    int32_t step_size;
    
    
    if (delta_i < CURR_THRES_SENS && delta_i > -CURR_THRES_SENS) {                                // We may need to comment this portion if algorithm is unstable.
        if (delta_i != 0) {
            if (delta_v > 0) {
                i_in += STEP_SIZE;
            } else {
                i_in -= STEP_SIZE;
            }
        }     
    } else {
		dp_di = (delta_p*1000)/delta_i;
		chprintf((BaseSequentialStream *) &SD2, "dp_di: %d , \r\n", dp_di);
        if (dp_di != 0) {
            if (dp_di > 1000) {
                i_in += STEP_SIZE;   
            } 
            if (dp_di < 1000) {
                i_in -= 4*STEP_SIZE;    
            }
        }
        
        /* Variable step algorithm. Comment above line if using below logic. */ 
        
        step_size = (dp_di*1000*STEP_SIZE_FACTOR)/volt;
        //chprintf((BaseSequentialStream *) &SD2, "dp_di: %d, step size: %d , \r\n", dp_di, step_size);
        /*
        if (dp_di != 0) {
            if (dp_di > 0) {
              if(step_size < MIN_STEP_SIZE) {
                i_in += MIN_STEP_SIZE;   
              } else {
                if(step_size > MAX_STEP_SIZE) {
                  i_in += MAX_STEP_SIZE;
                }else{
                  i_in += step_size;
                }
              }
            } else {
              if(step_size > (-1)*MIN_STEP_SIZE) {
                i_in -= MIN_STEP_SIZE;   
              } else {
                if(step_size < (-1)*MAX_STEP_SIZE) {
                  i_in -= MAX_STEP_SIZE;
                }else{
                  i_in += step_size;
                }
              }
            }
        }
        */ 
        
    } 
       
    prev_volt = volt;
    prev_curr = curr;
    prev_pwr  = pwr;
    /* End IC MPPT Algorithm */
    

    
    /* Compare the actual vs the allowed current */
    /* Below is if the actual current is much lower that allowed current*/
    
    if (curr/1000 < 0.8 * i_in)  {                 //Uncomment it after algorithm test.
      //i_in = 0.8*curr/1000;
    }
    
    
    /* Below is if the actual current is much higher than allowed current*/
    
    if (curr/1000 > 1.5 * i_in)  {                 //Uncomment it after algorithm test.
      //i_in = 1.25 * i_in;
      //i_in = curr/1000;
    }
     
    
    /* bounds checks for current */
    if (i_in < 5) {
      i_in = 5;
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
    int32_t voltage, current, power;
    uint32_t iadj_v = 1500;
    uint32_t i_in=0;
    int i=0;                          //TODO: Delete this. For finding number of iterations until steady state.
    
    
    /* Start up drivers */
    ina226ObjectInit(&ina226dev);
    dacStart(&DACD1, &dac1cfg);
    ina226Start(&ina226dev, &ina226config);

    palSetLine(LINE_LED);
    palSetLine(LINE_SHDN_LT1618);
    
    
    chprintf((BaseSequentialStream *) &SD2, "\r\n ****** Max input curr: %d, Bias Volt: %d mv \r\n", i_in, iadj_v);
    while(!chThdShouldTerminateX()){
      chThdSleepMilliseconds(SLEEP_MS);
      //chprintf((BaseSequentialStream *) &SD2, "\r\n%d\r\n", i++);
      //palToggleLine(LINE_LED);
      
      /* Get present values */
      voltage = ina226ReadVBUS(&ina226dev); //VBUS voltage in mV 
      current = ina226ReadCurrent(&ina226dev); //Current in uA
      power   = ina226ReadPower(&ina226dev); //Power in increments of uW
      
      OD_solarPanel.voltage = voltage;
      OD_solarPanel.current = current;
      OD_solarPanel.power   = power  ;
      
      //chprintf((BaseSequentialStream *) &SD2, "\r\nVolt: 0x%X, Current: 0x%X, Power: 0x%X, \r\n", OD_solarPanel.voltage, OD_solarPanel.current, OD_solarPanel.power);
      chprintf((BaseSequentialStream *) &SD2, "\r\nIteration: %d, Volt: %d mv, Current: %d uA, Power: %d uW, \r\n",i, voltage, current, power);
      
      
      /* Calculate max input current drawn from solar cells. This is used to calculate iadj. */
      i_in = calc_mppt(voltage, current, power);
      //i_in = 30;
      iadj_v = calc_iadj(i_in);
      dacPutMillivolts(&DACD1, 0, iadj_v) ;
      chprintf((BaseSequentialStream *) &SD2, "Max input curr: %d ma, Bias Volt: %d mv, \r\n", i_in, iadj_v);
      i++;
      
      
    }


    /* Stop drivers */
    dacStop(&DACD1);
    ina226Stop(&ina226dev);

    chThdExit(MSG_OK);
}
