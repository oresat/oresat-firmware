/*! \file ax5043_driver.h */


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

#include "ax5043_common.h"
#include "ax5043_engr_f1.h"
#include "ax5043_engr_f2.h"
#include "ax5043_driver.h"



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


static THD_WORKING_AREA(waAx5043_radio1, 1024);
static THD_FUNCTION(ax5043_radio1, ax5043_driver) 
{
  (ax5043_drv_t)ax5043_driver;
  uint8_t packet_len=0;
  uint8_t ret_value[3]={0,0,0};

  ax5043_f2_init(&ax5043_driver.ax5043_spip1);
  ax5043_set_addr(&ax5043_driver.ax5043_spip1, localaddr_tx);
  chprintf(DEBUG_CHP, "done reseting AX5043 rx \r\n");
  ax5043_f2_prepare_rx(&ax5043_driver.ax5043_spip1);


  palEnableLineEvent(LINE_SX_INT0, PAL_EVENT_MODE_RISING_EDGE);



  while(true)
  {
    palWaitLineTimeout(LINE_SX_INT0, TIME_MS2I(5000));
    
    packet_len=receive_f2_loop(&ax5043_driver.ax5043_spip1, axradio_rxbuffer);

    if(packet_len > 0)
      chprintf(DEBUG_CHP,"INFO: Received packet %d\r\n",axradio_rxbuffer[3]);
  }


}


static THD_WORKING_AREA(waAx5043_radio2, 1024);
static THD_FUNCTION(ax5043_radio2, ax5043_driver)
{
  (ax5043_drv_t)ax5043_driver;
  uint16_t pkt_counter = 0;

  chThdSleepMilliseconds(500);
  ax5043_f1_init(&ax5043_driver.ax5043_spip2);
  ax5043_set_addr(&ax5043_driver.ax5043_spip2, localaddr_tx);
  ax5043_f1_prepare_tx(&ax5043_driver.ax5043_spip2);
  chprintf(DEBUG_CHP, "done reseting AX5043 tx\r\n");


}


/**
 * Reds an AX5043 register. This has retry logic. This calls the the function ax5043_write_reg_spi.
 * @param spip: SPI Configuration, reg: Register address, value: register value, ret_value: returned data.
 * @return the value in the register.
 */
uint8_t ax5043_init(ax5043_drv_t ax5043_driver)
{

    chThdCreateStatic(waAx5043_radio1, sizeof(waAx5043_radio1), NORMALPRIO, ax5043_radio1, ax5043_driver);
    chThdSleepMilliseconds(5000);
    chThdCreateStatic(waAx5043_radio2, sizeof(waAx5043_radio2), NORMALPRIO, ax5043_radio2, ax5043_driver);
}


//!@

