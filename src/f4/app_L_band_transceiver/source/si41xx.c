/*! \file ax5043.h */


/*!
 * \addtogroup ax5043
 *  * @{
 *
 */
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "ch.h"
#include "hal.h"
#include "chprintf.h"

#include "si41xx.h"



/**
 * writes  to an SI4123 register.
 * @param address: register address, data: Register data.
 * @return void.
 */
void si_write_reg(uint8_t address, uint32_t data)
{
  int i;
  uint32_t sdata;
  uint32_t mask = 1 << 31;
  data = (data << 14) | (address << 10);
  
  palClearLine(LINE_SI_SENB);
  
  for(i=0; i<22;i++)
  {
    palClearLine(LINE_SI_SCLK);
    chThdSleepMicroseconds(1);
    sdata = data & mask;
    if(sdata > 0){
      //chprintf(DEBUG_CHP, "1");
      palSetLine(LINE_SI_SDATA);
      }
    else{
      //chprintf(DEBUG_CHP, "0");
      palClearLine(LINE_SI_SDATA);
      }
    chThdSleepMicroseconds(1);
    palSetLine(LINE_SI_SCLK);
    chThdSleepMicroseconds(1);
    data = data <<1;    
    chThdSleepMicroseconds(1);
  }
  //chprintf(DEBUG_CHP, " \r\n");
  palSetLine(LINE_SI_SENB);
  
}



//!@

