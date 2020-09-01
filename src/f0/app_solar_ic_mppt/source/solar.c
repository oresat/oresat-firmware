#include "solar.h"
#include "ina226.h"
#include "CANopen.h"
#include "chprintf.h"

/* Defines for INA226 */
#define CURR_LSB           30  /* 20uA/bit */
#define RSENSE             100 /* 0.1 ohm  */
#define DAC_VDDA_UV        3333000 /* 3.333 V. Chgange to 3.0 v when powered from debug board */

/*Defines for MPPT algorithm speed*/
#define SLEEP_MS           10                

/*Defines for MPPT algorithm that changes with each solar cell variant */
/*Things to note
 * Negative step size needs to be greater as the curve falls quickly.
 * Make sure to account for noise. Lower value will cause curve to crash. Higher value will not let the system reach its potential.
 */ 
#define MIN_DP_DI              4000     /* The most important piece. This keeps the point to the left of MPPT. */ 
#define NVE_STEP_SIZE          5000     /* -ve step size for constant current condition */
#define CURR_THRES_SENS        80       /* Current Threshold Sensitivity. Reduces sensitivity to noise in current. */
#define MAX_STEP_SIZE          5000     /* Maximum step size for variable step IC.*/
#define STEP_SIZE_FACTOR       1000     /* Posive step factor.*/
#define NVE_STEP_SIZE_FACTOR   5        /* Negative step factor. This is multipled with Positive step factor*/
#define MIN_PV_CURRENT         5000     /* 5000 uA or 5 mA */
#define MAX_PV_CURRENT         500000   /* 500000 uA or 500 mA */



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
    INA226_CONFIG_VSHCT_140US | INA226_CONFIG_VBUSCT_140US |
    INA226_CONFIG_AVG_16,                   
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
 * @brief control DAC output in microvolts.
 * @param[in] dacp      DAC driver pointer.
 * @param[in] chan      DAC channel.
 * @param[in] uv        output volts in uv (microVolts).
 */
 
void dacPutMillivolts(DACDriver *dacp, dacchannel_t chan, uint32_t uv) {
    /* Per section 14.5.3 of the STM32F0x1 ref manual,
     * Vout(mV) = VDDA(mV) * (reg_val / 4096)
     * so, reg_val = (Vout * 4096) / VDDA
     */
    dacsample_t val = ((uv/100) << 12) / (DAC_VDDA_UV/100);
    dacPutChannelX(dacp, chan, val);
}


/**
 * @brief Calculates Iadj_v required for a particular max current.
 * @param[in] i_out      current in uA.
 * @return    Iadj_v     DAC output in microvolts.
 */    
uint32_t calc_iadj(uint32_t i_out)
{
  /* Per page 7 of LT1618 datasheet
   * V_Isense = (1.263 - 0.8* v_iadj)/25
   * => 25 * i_out * Rsense  = 1.263 - 0.8 * V_iadj
   * Multiplying 4000 on both sides
   * 100000 * i_out * Rsense = 5052 - 3200 * V_iadj
   * Now i_out is in uA, Rsense is in mOhm and V_iadj is in uV
   * => 100000 * i_out/1000000 * Rsense/1000 = 5052 - 3200 * V_iadj/1000000
   * => 100 * i_out * Rsense = 5052000000 - 3200 * V_iadj
   * => i_out * Rsense = 50520000 - 32 * V_iadj
   * => V_adj = (5052000 - i_out * Rsense * 100)/3200
   */
  return ((50520000 - i_out * RSENSE) / 32);
}

/**
 * @brief Maximum power point tracking algorithm for Solar cells
 * @param[in] volt      Solar cell bus voltage in mV.
 * @param[in] curr      Solar cell current in uA.
 * @param[in] pwr       Power output from solar cells in microWatts. 
 * @return Maximum current to be drawn from solar cells in uA
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
    
    /* programmed max allowed current from current and previous iteration*/
    static int32_t i_in;
    static int32_t prev_i_in;
    //static int32_t prev_dp_di;
    
    static int k=0;   //remove after debuging
    
    int32_t delta_v = volt - prev_volt;
    int32_t delta_i = curr - prev_curr;
    int32_t delta_p = pwr  - prev_pwr;
    
    int32_t dp_di;
    int32_t step_size;
    
    /*Handles sudden decrease in illumination */ 
    if (curr < 0.8 * i_in)  {                 
      i_in = 0.8*curr;
      return i_in;
    }
    
    /*Handles sudden decrease in load*/
    if (curr > 1.2 * i_in)  {               
      i_in = curr;
      return i_in;
    }
    
    /* Variable Step IC MPPT Algorithm */
    if ((prev_i_in-i_in) == 0 && (delta_p < 0 || delta_i <0 || delta_v<0)) {
      /* decrease current if power/current decreases without being specified. 
       * closed loop control.
       */ 
      prev_i_in = i_in;                                
      i_in -= NVE_STEP_SIZE;  
    } else {
      prev_i_in = i_in;
      if (delta_i > CURR_THRES_SENS || delta_i < -CURR_THRES_SENS) {        
		    dp_di = (delta_p*1000)/delta_i;
        step_size = (dp_di * STEP_SIZE_FACTOR)/volt;   
                
        if (dp_di > MIN_DP_DI) {  
          if(step_size > MAX_STEP_SIZE) {
            i_in += MAX_STEP_SIZE;
          }else{
            i_in += step_size;
          }
        } else {
          i_in -= 2000;
          if (dp_di < 0) {
            if(step_size < (-1)*MAX_STEP_SIZE) {
              i_in -= MAX_STEP_SIZE;
            }else{
              i_in += NVE_STEP_SIZE_FACTOR*step_size;
            }
          }
        }
      }
    } 

    //if(k>50){
    //  chprintf((BaseSequentialStream *) &SD2, "\r\n dp_di: %d, step: %d, dp: %d, di: %d, volt: %d, pwr: %d, i_in: %d, prev_i_in: %d,\r\n", dp_di, step_size,delta_p, delta_i, volt, pwr, i_in, prev_i_in );
    //  k=0;
    //}
    //k++;
       
    prev_volt = volt;
    prev_curr = curr;
    prev_pwr  = pwr;
    /* End IC MPPT Algorithm */

    /* bounds checks for current */
    if (i_in < MIN_PV_CURRENT) {
      i_in = MIN_PV_CURRENT;
    }
    if (i_in > MAX_PV_CURRENT) {
      i_in = MAX_PV_CURRENT;
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
    int i=0, j=0;                          //TODO: Delete this. For finding number of iterations until steady state.
    
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

      
      
      /* Calculate max input current drawn from solar cells. This is used to calculate iadj. */
      i_in = calc_mppt(voltage, current, power);
      iadj_v = calc_iadj(i_in);
      dacPutMillivolts(&DACD1, 0, iadj_v) ;
      
      if (j >= 500){
        chprintf((BaseSequentialStream *) &SD2, "Iteration: %d, Volt: %d mv, Current: %d uA, Power: %d uW, \r\n",i, voltage, current, power);
        chprintf((BaseSequentialStream *) &SD2, "Max input curr: %d ua, Bias Volt: %d uv, \r\n", i_in, iadj_v);
        j=0;
      }
      j++;
      
      i++;
      
      
    }


    /* Stop drivers */
    dacStop(&DACD1);
    ina226Stop(&ina226dev);

    chThdExit(MSG_OK);
}
