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
#include "ax5043_ax25_f3.h"
#include "ax5043_driver.h"




/**
 * Change AX5043 radio1 receive.
 * @param spip: SPI Configuration, reg: Register address, value: register value, ret_value: returned data.
 * @return the value of the register.
 */
uint8_t ax5043_radio_startup(SPIDriver * spip, ax5043_config_t config, ax5043_mode_t mode)
{
  switch(config) {
  case ax5043_f1:
    ax5043_f1_init(spip);
    
    switch(mode) {
    case ax5043_rx:
      ax5043_f1_prepare_rx(spip);
      break;
    case ax5043_tx:
      ax5043_f1_prepare_tx(spip);
      break;
    default:  
      ax5043_f1_prepare_rx(spip);
    }
    break;
    
  case ax5043_f2:
    ax5043_f2_init(spip);
    
    switch(mode) {
    case ax5043_rx:
      ax5043_f2_prepare_rx(spip);
      break;
    case ax5043_tx:
      ax5043_f2_prepare_tx(spip);
      break;
    default:  
      ax5043_f2_prepare_rx(spip);
    }
    break;
    
  case ax5043_f3:
    ax5043_f3_init(spip);
    
    switch(mode) {
    case ax5043_rx:
      ax5043_f3_prepare_rx(spip);
      break;
    case ax5043_tx:
      ax5043_f3_prepare_tx(spip);
      break;
    default:  
      ax5043_f3_prepare_rx(spip);
    }
    break;
    
  default:
    ax5043_f1_init(spip);
    
    switch(mode) {
    case ax5043_rx:
      ax5043_f1_prepare_rx(spip);
      break;
    case ax5043_tx:
      ax5043_f1_prepare_tx(spip);
      break;
    default:  
      ax5043_f1_prepare_rx(spip);
    }  
  }
  
  if (mode == ax5043_off){
    ax5043_shutdown(spip);
  }
  return 0; 

}



/**
 * Change AX5043 radio1 frequency.
 * @param spip: SPI Configuration, reg: Register address, value: register value, ret_value: returned data.
 * @return the value of the register.
 */
uint8_t ax5043_radio1_chg_config(ax5043_drv_t *ax5043_driver_p, ax5043_config_t config)
{
  ax5043_radio_startup(ax5043_driver_p->ax5043_spip1, config, ax5043_driver_p->ax5043_mode1);
  ax5043_set_addr(ax5043_driver_p->ax5043_spip1, ax5043_driver_p->localaddr);
  ax5043_driver_p->ax5043_config1 = config;
  return 0;

}

/**
 * Change AX5043 radio2 frequency.
 * @param spip: SPI Configuration, reg: Register address, value: register value, ret_value: returned data.
 * @return the value of the register.
 */
uint8_t ax5043_radio2_chg_config(ax5043_drv_t *ax5043_driver_p, ax5043_config_t config)
{
  ax5043_radio_startup(ax5043_driver_p->ax5043_spip2, config, ax5043_driver_p->ax5043_mode2);
  ax5043_set_addr(ax5043_driver_p->ax5043_spip2, ax5043_driver_p->localaddr);
  ax5043_driver_p->ax5043_config2 = config;
  return 0;  

}



/**
 * Change AX5043 radio1 mode.
 * @param spip: SPI Configuration, reg: Register address, value: register value, ret_value: returned data.
 * @return the value of the register.
 */
uint8_t ax5043_radio_mode(SPIDriver * spip, ax5043_config_t config, ax5043_mode_t mode)
{
  switch(config) {
  case ax5043_f1:    
    switch(mode) {
    case ax5043_rx:
      ax5043_f1_prepare_rx(spip);
      break;
    case ax5043_tx:
      ax5043_f1_prepare_tx(spip);
      break;
    default:  
      ax5043_f1_prepare_rx(spip);
    }
    break;
    
  case ax5043_f2:
    switch(mode) {
    case ax5043_rx:
      ax5043_f2_prepare_rx(spip);
      break;
    case ax5043_tx:
      ax5043_f2_prepare_tx(spip);
      break;
    default:  
      ax5043_f2_prepare_rx(spip);
    }
    break;
    
  case ax5043_f3:
    switch(mode) {
    case ax5043_rx:
      ax5043_f3_prepare_rx(spip);
      break;
    case ax5043_tx:
      ax5043_f3_prepare_tx(spip);
      break;
    default:  
      ax5043_f3_prepare_rx(spip);
    }
    break;
        
  default:
    switch(mode) {
    case ax5043_rx:
      ax5043_f1_prepare_rx(spip);
      break;
    case ax5043_tx:
      ax5043_f1_prepare_tx(spip);
      break;
    default:  
      ax5043_f1_prepare_rx(spip);
    }  
  }
  
  if (mode == ax5043_off){
    ax5043_shutdown(spip);
  }

  return 0;  

}


/**
 * Change AX5043 radio1 mode.
 * @param spip: SPI Configuration, reg: Register address, value: register value, ret_value: returned data.
 * @return the value of the register.
 */
uint8_t ax5043_radio1_mode(ax5043_drv_t *ax5043_driver_p, ax5043_mode_t mode)
{
  ax5043_radio_mode(ax5043_driver_p->ax5043_spip1, ax5043_driver_p->ax5043_config1, mode);
  ax5043_driver_p->ax5043_mode1 = mode;
  return 0;  

}



/**
 * Change AX5043 radio2 mode.
 * @param spip: SPI Configuration, reg: Register address, value: register value, ret_value: returned data.
 * @return the value of the register.
 */
uint8_t ax5043_radio2_mode(ax5043_drv_t *ax5043_driver_p, ax5043_mode_t mode)
{
  ax5043_radio_mode(ax5043_driver_p->ax5043_spip2, ax5043_driver_p->ax5043_config2, mode);
  ax5043_driver_p->ax5043_mode2 = mode;
  return 0;  

}


/**
 * Change AX5043 radio2 receive.
 * @param spip: SPI Configuration, reg: Register address, value: register value, ret_value: returned data.
 * @return the value of the register.
 */
uint8_t ax5043_radio_rx(SPIDriver * spip, ax5043_config_t config, uint8_t axradio_rxbuffer[])
{
  uint8_t packet_len=0; 
  
  switch(config) {
  case ax5043_f1: 
    packet_len=receive_f1_loop(spip, axradio_rxbuffer);
    break;
  case ax5043_f2: 
    packet_len=receive_f2_loop(spip, axradio_rxbuffer);
    break;
  case ax5043_f3: 
    packet_len=receive_f3_loop(spip, axradio_rxbuffer);
    break;
  default:
    return 0;
  }
  return packet_len;
}


/**
 * Change AX5043 radio1 receive.
 * @param spip: SPI Configuration, reg: Register address, value: register value, ret_value: returned data.
 * @return the value of the register.
 */
uint8_t ax5043_radio1_rx(ax5043_drv_t *ax5043_driver_p)
{
  uint8_t axradio_rxbuffer[256];  //buffer to receive radio data
  uint8_t packet_len=0;  
  palEnableLineEvent(ax5043_driver_p->ax5043_int1, PAL_EVENT_MODE_RISING_EDGE);



  while(true)
  {
    palWaitLineTimeout(ax5043_driver_p->ax5043_int1, TIME_MS2I(5000));
    
    if (ax5043_driver_p->ax5043_mode1 == AX5043_RX)
    {
      packet_len=ax5043_radio_rx(ax5043_driver_p->ax5043_spip1, ax5043_driver_p->ax5043_config1, axradio_rxbuffer);

      if(packet_len > 0)
        chprintf(DEBUG_CHP,"INFO:R1 Received packet %d\r\n",axradio_rxbuffer[3]);
    }
  }
  return 0; 
}


/**
 * Change AX5043 radio2 receive.
 * @param spip: SPI Configuration, reg: Register address, value: register value, ret_value: returned data.
 * @return the value of the register.
 */
uint8_t ax5043_radio2_rx(ax5043_drv_t *ax5043_driver_p)
{
  uint8_t axradio_rxbuffer[256];  //buffer to receive radio data
  uint8_t packet_len=0;
  palEnableLineEvent(ax5043_driver_p->ax5043_int2, PAL_EVENT_MODE_RISING_EDGE);



  while(true)
  {
    palWaitLineTimeout(ax5043_driver_p->ax5043_int2, TIME_MS2I(5000));
    
    if (ax5043_driver_p->ax5043_mode2 == AX5043_RX)
    {
      packet_len=ax5043_radio_rx(ax5043_driver_p->ax5043_spip2, ax5043_driver_p->ax5043_config2, axradio_rxbuffer);

      if(packet_len > 0)
        chprintf(DEBUG_CHP,"INFO:R2 Received packet %d\r\n",axradio_rxbuffer[3]);
    }
  }  
  return 0; 
}


/**
 * Change AX5043 radio1 mode.
 * @param spip: SPI Configuration, reg: Register address, value: register value, ret_value: returned data.
 * @return the value of the register.
 */
uint8_t ax5043_radio_packet_tx(SPIDriver * spip, ax5043_config_t config, ax5043_drv_t *ax5043_driver_p, uint8_t *pkt, uint16_t pktlen)
{
  switch(config) {
  case ax5043_f1: 
    transmit_f1_packet(spip, ax5043_driver_p->remoteaddr, ax5043_driver_p->localaddr, pkt, pktlen);
    break;
  case ax5043_f2: 
    transmit_f2_packet(spip, ax5043_driver_p->remoteaddr, ax5043_driver_p->localaddr, pkt, pktlen);
    break;
  case ax5043_f3: 
    transmit_f3_packet(spip, ax5043_driver_p->remoteaddr, ax5043_driver_p->localaddr, pkt, pktlen);
    break;
  default: 
    return 1;
  }
  return 0; 
}


/**
 * Change AX5043 radio1 receive.
 * @param spip: SPI Configuration, reg: Register address, value: register value, ret_value: returned data.
 * @return the value of the register.
 */
uint8_t ax5043_radio1_packet_tx(ax5043_drv_t *ax5043_driver_p, uint8_t *pkt, uint16_t pktlen)
{
  ax5043_radio_packet_tx(ax5043_driver_p->ax5043_spip1, ax5043_driver_p->ax5043_config1, ax5043_driver_p, pkt, pktlen);
  return 0; 
}



/**
 * Change AX5043 radio2 receive.
 * @param spip: SPI Configuration, reg: Register address, value: register value, ret_value: returned data.
 * @return the value of the register.
 */
uint8_t ax5043_radio2_packet_tx(ax5043_drv_t *ax5043_driver_p, uint8_t *pkt, uint16_t pktlen)
{
  ax5043_radio_packet_tx(ax5043_driver_p->ax5043_spip2, ax5043_driver_p->ax5043_config2, ax5043_driver_p, pkt, pktlen);
  return 0; 
}




/**
 * Change AX5043 radio1 receive.
 * @param spip: SPI Configuration, reg: Register address, value: register value, ret_value: returned data.
 * @return the value of the register.
 */
uint8_t ax5043_radio1_cw_tx(ax5043_drv_t *ax5043_driver_p, uint8_t *pkt, uint16_t pktlen)
{
    return 0; 

}



/**
 * Change AX5043 radio1 receive.
 * @param spip: SPI Configuration, reg: Register address, value: register value, ret_value: returned data.
 * @return the value of the register.
 */
uint8_t ax5043_radio2_cw_tx(ax5043_drv_t *ax5043_driver_p, uint8_t *pkt, uint16_t pktlen)
{
  return 0; 

}

THD_WORKING_AREA(waAx5043_radio1, 1024);
THD_FUNCTION(ax5043_radio1, ax5043_driver_ptr) 
{
  ax5043_drv_t* ax5043_driver_p=(ax5043_drv_t*)ax5043_driver_ptr;
  
  ax5043_radio_startup(ax5043_driver_p->ax5043_spip1, ax5043_driver_p->ax5043_config1, ax5043_driver_p->ax5043_mode1);
  ax5043_set_addr(ax5043_driver_p->ax5043_spip1, ax5043_driver_p->localaddr);
  chprintf(DEBUG_CHP, "done reseting AX5043 radio1 \r\n");
  ax5043_radio1_rx(ax5043_driver_p);

}


THD_WORKING_AREA(waAx5043_radio2, 1024);
THD_FUNCTION(ax5043_radio2, ax5043_driver_ptr)
{
  ax5043_drv_t* ax5043_driver_p=(ax5043_drv_t*)ax5043_driver_ptr;
  ax5043_radio_startup(ax5043_driver_p->ax5043_spip2, ax5043_driver_p->ax5043_config2, ax5043_driver_p->ax5043_mode2);
  ax5043_set_addr(ax5043_driver_p->ax5043_spip2, ax5043_driver_p->localaddr);
  chprintf(DEBUG_CHP, "done reseting AX5043 radio2 \r\n");

  ax5043_radio2_rx(ax5043_driver_p);
}


/**
 * Reds an AX5043 register. This has retry logic. This calls the the function ax5043_write_reg_spi.
 * @param spip: SPI Configuration, reg: Register address, value: register value, ret_value: returned data.
 * @return the value in the register.
 */
uint8_t ax5043_init(ax5043_drv_t *ax5043_driver_p)
{

    chThdCreateStatic(waAx5043_radio1, sizeof(waAx5043_radio1), NORMALPRIO, ax5043_radio1, ax5043_driver_p);
    chThdSleepMilliseconds(5000);
    chThdCreateStatic(waAx5043_radio2, sizeof(waAx5043_radio2), NORMALPRIO, ax5043_radio2, ax5043_driver_p);
    return 0; 
}


//!@

