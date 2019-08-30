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

#include "si4123.h"



/**
 * writes  to an SI4123 register.
 * @param address: register address, data: Register data.
 * @return void.
 */
void write_reg(uint8_t address, uint32_t data)
{
  int i;
  bool sdata;
  uint32_t mask = 1 << 31;
  data = (data << 14) | (address << 10);
  
  palClearLine(LINE_SI_SENB);
  for(i=0; i<22;i++)
  {
    palClearLine(LINE_SI_SCLK);
    sdata = data & mask;
    if(sdata)
      palSetLine(LINE_SI_SDATA);
    else
      palClearLine(LINE_SI_SDATA);
    palSetLine(LINE_SI_SCLK);
    data = data <<1;
    
  }
}



//!@

