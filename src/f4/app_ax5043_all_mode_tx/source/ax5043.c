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

#include "ax5043.h"




/**
 * writes  to an AX5043 register.
 * @param spip: SPI Configuration, reg: Register address, value: register value, ret_value: returned data.
 * @return the value of the register.
 */
uint8_t ax5043_write_reg(SPIDriver * spip, uint16_t reg, uint8_t value, uint8_t ret_value[])
{
  uint8_t command_buf[3] = {0,0,0};
  
  if(reg <  0x0070)
  {
    command_buf[0]=0x80|reg;
    command_buf[1]=value;
    spiSelect(spip);
    spiStartExchange(spip, 2, command_buf, ret_value);
    while((*spip).state != SPI_READY) { }
    spiUnselect(spip);
  }
  else
  {
    command_buf[0]=0xF0|(reg>>8);
    command_buf[1]=reg;
    command_buf[2]=value;
    spiSelect(spip);
    spiStartExchange(spip, 3, command_buf, ret_value);
    while((*spip).state != SPI_READY) { }
    spiUnselect(spip);
  }
  return ret_value[0];   //retun status while writting the register

}





/**
 * Reds an AX5043 register. This has retry logic. This calls the the function ax5043_write_reg_spi.
 * @param spip: SPI Configuration, reg: Register address, value: register value, ret_value: returned data.
 * @return the value in the register.
 */
uint8_t ax5043_read_reg(SPIDriver * spip, uint16_t reg, uint8_t value, uint8_t ret_value[])
{
  uint8_t command_buf[3] = {0,0,0 };
  //uint8_t rx_buf[2]={0 ,0 };

  if(reg <  0x0070)
  {
    command_buf[0]=reg;
    command_buf[1]=value;
    spiSelect(spip);
    spiStartExchange(spip, 2, command_buf, ret_value);
    while((*spip).state != SPI_READY) { }
    spiUnselect(spip);
    return ret_value[1];    //return the reg value when reading the register
  }
  else
  {
    command_buf[0]=0x70|(reg>>8);
    command_buf[1]=reg;
    command_buf[2]=value;
    spiSelect(spip);
    spiStartExchange(spip, 3, command_buf, ret_value);
    while((*spip).state != SPI_READY) { }
    spiUnselect(spip);
    return ret_value[2];    //return the reg value when reading the register
  }

}


/**
 * Shutdown after reset the AX5043
 * @param spip: SPI Configuration.
 * @return void 
 * TODO return a -ve return code if there are any errors
 */
void ax5043_shutdown(SPIDriver * spip)
{
  uint8_t ret_value[3]={0,0,0};
  uint8_t value;
  value = ax5043_read_reg(spip, AX5043_REG_PWRMODE, (uint8_t)0x00, ret_value);
  value = value & 0xF0;
  value = value | AX5043_POWERDOWN;
  ax5043_write_reg(spip, AX5043_REG_PWRMODE, value, ret_value);
}


/**
 * Standby the AX5043
 * @param spip: SPI Configuration.
 * @return void 
 * TODO return a -ve return code if there are any errors
 */
void ax5043_standby(SPIDriver * spip)
{
  uint8_t ret_value[3]={0,0,0};
  //ax5043_write_reg(spip, AX5043_REG_PWRMODE, AX5043_OSC_EN_BIT | AX5043_REF_EN_BIT | AX5043_POWERDOWN, ret_value);
  uint8_t value;
  value = ax5043_read_reg(spip, AX5043_REG_PWRMODE, (uint8_t)0x00, ret_value);
  value = value & 0xF0;
  value = value | AX5043_STANDBY;
  ax5043_write_reg(spip, AX5043_REG_PWRMODE, value, ret_value);
}

/**
 * Enable FIFO in AX5043
 * @param spip: SPI Configuration.
 * @return void 
 * TODO return a -ve return code if there are any errors
 */
void ax5043_fifo_en(SPIDriver * spip)
{
  uint8_t ret_value[3]={0,0,0};
  uint8_t value;
  value = ax5043_read_reg(spip, AX5043_REG_PWRMODE, (uint8_t)0x00, ret_value);
  value = value & 0xF0;
  value = value | AX5043_FIFO_ENABLED;
  ax5043_write_reg(spip, AX5043_REG_PWRMODE, value, ret_value);
}

/**
 * put AX5043 in synthesizer RX mode
 * @param spip: SPI Configuration.
 * @return void 
 * TODO return a -ve return code if there are any errors
 */
void ax5043_synth_rx(SPIDriver * spip)
{
  uint8_t ret_value[3]={0,0,0};

  uint8_t value;
  value = ax5043_read_reg(spip, AX5043_REG_PWRMODE, (uint8_t)0x00, ret_value);
  value = value & 0xF0;
  value = value | AX5043_SYNTH_RX;
  ax5043_write_reg(spip, AX5043_REG_PWRMODE, value, ret_value);
}

/**
 * changes AX5043 to full RX mode
 * @param spip: SPI Configuration.
 * @return void 
 * TODO return a -ve return code if there are any errors
 */
void ax5043_full_rx(SPIDriver * spip)
{
  uint8_t ret_value[3]={0,0,0};

  uint8_t value;
  value = ax5043_read_reg(spip, AX5043_REG_PWRMODE, (uint8_t)0x00, ret_value);
  value = value & 0xF0;
  value = value | AX5043_FULL_RX;
  ax5043_write_reg(spip, AX5043_REG_PWRMODE, value, ret_value);
}


/**
 * put AX5043 in synthesizer TX mode
 * @param spip: SPI Configuration.
 * @return void 
 * TODO return a -ve return code if there are any errors
 */
void ax5043_synth_tx(SPIDriver * spip)
{
  uint8_t ret_value[3]={0,0,0};
  uint8_t value;
  value = ax5043_read_reg(spip, AX5043_REG_PWRMODE, (uint8_t)0x00, ret_value);
  value = value & 0xF0;
  value = value | AX5043_SYNTH_TX;
  ax5043_write_reg(spip, AX5043_REG_PWRMODE, value, ret_value);
}


/**
 * changes AX5043 to full TX mode
 * @param spip: SPI Configuration.
 * @return void 
 * TODO return a -ve return code if there are any errors
 */
void ax5043_full_tx(SPIDriver * spip)
{
  uint8_t ret_value[3]={0,0,0};
  uint8_t value;
  value = ax5043_read_reg(spip, AX5043_REG_PWRMODE, (uint8_t)0x00, ret_value);
  value = value & 0xF0;
  value = value | AX5043_FULL_TX;
  ax5043_write_reg(spip, AX5043_REG_PWRMODE, value, ret_value);
}





//!@

