/*! \file ax5043_driver.c */


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
#include "ax5043_setup.h"
#include "ax5043_driver.h"
#include "morse.h"


/**
 * Change AX5043 radio1 configuraion.
 * @param ax5043_driver_p: Radio driver, config: The set-up file details.
 * @return Success or error code.
 */
uint8_t ax5043_radio1_chg_config(ax5043_drv_t *ax5043_driver_p, ax5043_config_t * config_p)
{
  msg_t msg = chBSemWaitTimeout(ax5043_driver_p->ax5043_bsem1, TIME_MS2I(120));
  ax5043_init(ax5043_driver_p->ax5043_spip1, config_p);

    switch(ax5043_driver_p->ax5043_mode1) {
    case ax5043_rx:
      ax5043_prepare_rx(ax5043_driver_p->ax5043_spip1, config_p);
      break;
    case ax5043_tx:
      ax5043_prepare_tx(ax5043_driver_p->ax5043_spip1, config_p);
      break;
    case ax5043_off:
      ax5043_shutdown(ax5043_driver_p->ax5043_spip1);
    default:
      ax5043_prepare_rx(ax5043_driver_p->ax5043_spip1, config_p);
    }
  ax5043_set_addr(ax5043_driver_p->ax5043_spip1, config_p->localaddr);
  ax5043_driver_p->ax5043_config1 = config_p;
  chBSemSignal(ax5043_driver_p->ax5043_bsem1);
  return 0;

}

/**
 * Change AX5043 radio2 configuraion.
 * @param ax5043_driver_p: Radio driver, config: The set-up file details.
 * @return Success or error code.
 */
uint8_t ax5043_radio2_chg_config(ax5043_drv_t *ax5043_driver_p, ax5043_config_t config)
{
  msg_t msg = chBSemWaitTimeout(ax5043_driver_p->ax5043_bsem2, TIME_MS2I(120));
  ax5043_init(ax5043_driver_p->ax5043_spip2, config);

    switch(ax5043_driver_p->ax5043_mode2) {
    case ax5043_rx:
      ax5043_prepare_rx(ax5043_driver_p->ax5043_spip2, config_p);
      break;
    case ax5043_tx:
      ax5043_prepare_tx(ax5043_driver_p->ax5043_spip2, config_p);
      break;
    case ax5043_off:
      ax5043_shutdown(ax5043_driver_p->ax5043_spip2);
    default:
      ax5043_prepare_rx(ax5043_driver_p->ax5043_spip2, config_p);
    }
  ax5043_set_addr(ax5043_driver_p->ax5043_spip2, config_p->localaddr);
  ax5043_driver_p->ax5043_config2 = config_p;
  chBSemSignal(ax5043_driver_p->ax5043_bsem2);
  return 0;

}



/**
 * Change AX5043 radio1 mode (rx, tx, off).
 * @param ax5043_driver_p: Radio driver, mode: rx, tx, off.
 * @return Success or error code.
 */
uint8_t ax5043_radio1_mode(ax5043_drv_t *ax5043_driver_p, ax5043_mode_t mode)
{
  msg_t msg = chBSemWaitTimeout(ax5043_driver_p->ax5043_bsem1, TIME_MS2I(120));
  switch(mode) {
  case ax5043_rx:
    ax5043_prepare_rx(ax5043_driver_p->ax5043_spip1, ax5043_driver_p->ax5043_config1);
    break;
  case ax5043_tx:
    ax5043_prepare_tx(ax5043_driver_p->ax5043_spip1, ax5043_driver_p->ax5043_config1);
    break;
  case ax5043_off:
    ax5043_shutdown(ax5043_driver_p->ax5043_spip1);
  default:
    ax5043_prepare_rx(ax5043_driver_p->ax5043_spip1, ax5043_driver_p->ax5043_config1);
  }
  ax5043_driver_p->ax5043_mode1 = mode;
  chBSemSignal(ax5043_driver_p->ax5043_bsem1);
  return 0;

}



/**
 * Change AX5043 radio2 mode (rx, tx, off).
 * @param ax5043_driver_p: Radio driver, mode: rx, tx, off.
 * @return Success or error code.
 */
uint8_t ax5043_radio2_mode(ax5043_drv_t *ax5043_driver_p, ax5043_mode_t mode)
{
  msg_t msg = chBSemWaitTimeout(ax5043_driver_p->ax5043_bsem2, TIME_MS2I(120));
  switch(mode) {
    case ax5043_rx:
      ax5043_prepare_rx(ax5043_driver_p->ax5043_spip2, ax5043_driver_p->ax5043_config2);
      break;
    case ax5043_tx:
      ax5043_prepare_tx(ax5043_driver_p->ax5043_spip2, ax5043_driver_p->ax5043_config2);
      break;
    case ax5043_off:
      ax5043_shutdown(ax5043_driver_p->ax5043_spip2);
    default:
      ax5043_prepare_rx(ax5043_driver_p->ax5043_spip2, ax5043_driver_p->ax5043_config2);
    }
  ax5043_driver_p->ax5043_mode2 = mode;
  chBSemSignal(ax5043_driver_p->ax5043_bsem2);
  return 0;

}


/**
 * Receive packets from AX5043 radio1.
 * @param ax5043_driver_p: Radio driver.
 * @return The function is an infinite loop waiting to receive data from radio.
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
      msg_t msg = chBSemWaitTimeout(ax5043_driver_p->ax5043_bsem1, TIME_MS2I(120));
      packet_len=receive_loop(ax5043_driver_p->ax5043_spip1, axradio_rxbuffer);
      if(packet_len > 0)
      {
        chprintf(DEBUG_CHP,"INFO:R1 Received packet %d\r\n",axradio_rxbuffer[3]);
        (void)chMBPostTimeout(ax5043_driver_p->ax5043_rx_mb1, (msg_t)axradio_rxbuffer, TIME_MS2I(10000));
      }
      chBSemSignal(ax5043_driver_p->ax5043_bsem1);
    }
  }
  return 0;
}


/**
 * Receive packets from AX5043 radio2.
 * @param ax5043_driver_p: Radio driver.
 * @return The function is an infinite loop waiting to receive data from radio.
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
      msg_t msg = chBSemWaitTimeout(ax5043_driver_p->ax5043_bsem2, TIME_MS2I(120));
      packet_len=receive_loop(ax5043_driver_p->ax5043_spip2, axradio_rxbuffer);

      if(packet_len > 0)
      {
        chprintf(DEBUG_CHP,"INFO:R2 Received packet %d\r\n",axradio_rxbuffer[3]);
        (void)chMBPostTimeout(ax5043_driver_p->ax5043_rx_mb2, (msg_t)axradio_rxbuffer, TIME_MS2I(10000));
      }
      chBSemSignal(ax5043_driver_p->ax5043_bsem2);
    }
  }
  return 0;
}


/**
 * Send packets via AX5043 radio1.
 * @param ax5043_driver_p: Radio driver, pkt: address of the packet, pktlen: length of packet
 * @return the value of the register.
 */
uint8_t ax5043_radio1_packet_tx(ax5043_drv_t *ax5043_driver_p, uint8_t *pkt, uint16_t pktlen)
{
  msg_t msg = chBSemWaitTimeout(ax5043_driver_p->ax5043_bsem1, TIME_MS2I(120));
  transmit_packet(ax5043_driver_p->ax5043_spip1, ax5043_driver_p->ax5043_config1->remoteaddr, ax5043_driver_p->ax5043_config1->localaddr, pkt, pktlen);
  chBSemSignal(ax5043_driver_p->ax5043_bsem1);
  return 0;
}



/**
 * Send packets via AX5043 radio2.
 * @param ax5043_driver_p: Radio driver, pkt: address of the packet, pktlen: length of packet
 * @return the value of the register.
 */
uint8_t ax5043_radio2_packet_tx(ax5043_drv_t *ax5043_driver_p, uint8_t *pkt, uint16_t pktlen)
{
  msg_t msg = chBSemWaitTimeout(ax5043_driver_p->ax5043_bsem2, TIME_MS2I(120));
  transmit_packet(ax5043_driver_p->ax5043_spip1, ax5043_driver_p->ax5043_config2->remoteaddr, ax5043_driver_p->ax5043_config2->localaddr, pkt, pktlen);
  chBSemSignal(ax5043_driver_p->ax5043_bsem2);
  return 0;
}

/**
 * send CW/morse via AX5043 radio.
 * @param spip: SPI Configuration
 * @return error code
 */
uint8_t ax5043_radio_prepare_cw(SPIDriver * spip)
{
  uint8_t ret_value[3]={0,0,0};
  ax5043_full_tx(spip);

/**
 * This is not mentioned in datasheet or programming manual but is required.
 * Removing this will make the transmission to transmit in low power for a few seconds
 * before it reaches peak power.
 */
  ax5043_write_reg(spip, AX5043_REG_FIFOSTAT, (uint8_t)0x03, ret_value);//FIFO reset
  ax5043_write_reg(spip, AX5043_REG_FIFODATA, (uint8_t)(AX5043_REPEATDATA_CMD|0x00), ret_value);
  ax5043_write_reg(spip, AX5043_REG_FIFODATA, (uint8_t)0x38, ret_value);//preamble flag
  ax5043_write_reg(spip, AX5043_REG_FIFODATA, (uint8_t)0xff, ret_value);
  ax5043_write_reg(spip, AX5043_REG_FIFODATA, (uint8_t)0x55, ret_value);//preamble
  ax5043_write_reg(spip, AX5043_REG_FIFOSTAT, (uint8_t)0x04, ret_value);//FIFO Commit

  ax5043_standby(spip);
  return 0;

}


/**
 * send CW/morse via AX5043 radio1.
 * @param ax5043_driver_p: Radio driver, pkt: address of the packet, pktlen: length of packet
 * @return error code
 */
uint8_t ax5043_radio1_cw_tx(ax5043_drv_t *ax5043_driver_p, char pkt[], uint16_t pktlen)
{
  msg_t msg = chBSemWaitTimeout(ax5043_driver_p->ax5043_bsem1, TIME_MS2I(120));
  ax5043_radio_prepare_cw(ax5043_driver_p->ax5043_spip1);
  SetWpm(5);
  SendMessage(ax5043_driver_p->ax5043_spip1, pkt, pktlen);
  chBSemSignal(ax5043_driver_p->ax5043_bsem1);
  return 0;

}



/**
 * send CW/morse via AX5043 radio2.
 * @param ax5043_driver_p: Radio driver, pkt: address of the packet, pktlen: length of packet
 * @return error code
 */
uint8_t ax5043_radio2_cw_tx(ax5043_drv_t *ax5043_driver_p, char pkt[], uint16_t pktlen)
{
  msg_t msg = chBSemWaitTimeout(ax5043_driver_p->ax5043_bsem1, TIME_MS2I(120));
  ax5043_radio_prepare_cw(ax5043_driver_p->ax5043_spip2);
  SetWpm(5);
  SendMessage(ax5043_driver_p->ax5043_spip2, pkt, pktlen);
  chBSemSignal(ax5043_driver_p->ax5043_bsem2);
  return 0;

}

THD_WORKING_AREA(waAx5043_radio1, 1024);
THD_FUNCTION(ax5043_radio1, ax5043_driver_ptr)
{
  ax5043_drv_t* ax5043_driver_p=(ax5043_drv_t*)ax5043_driver_ptr;

  chBSemObjectInit(ax5043_driver_p->ax5043_bsem1, true);
  ax5043_init(ax5043_driver_p->ax5043_spip1, ax5043_driver_p->ax5043_config1);

    switch(ax5043_driver_p->ax5043_mode1) {
    case ax5043_rx:
      ax5043_prepare_rx(ax5043_driver_p->ax5043_spip1, ax5043_driver_p->ax5043_config1);
      break;
    case ax5043_tx:
      ax5043_prepare_tx(ax5043_driver_p->ax5043_spip1, ax5043_driver_p->ax5043_config1);
      break;
    case ax5043_off:
      ax5043_shutdown(ax5043_driver_p->ax5043_spip1);
    default:
      ax5043_prepare_rx(ax5043_driver_p->ax5043_spip1, ax5043_driver_p->ax5043_config1);
    }
  ax5043_set_addr(ax5043_driver_p->ax5043_spip1, ax5043_driver_p->ax5043_config1->localaddr);
  chBSemSignal(ax5043_driver_p->ax5043_bsem1);
  chprintf(DEBUG_CHP, "done reseting AX5043 radio1 \r\n");
  ax5043_radio1_rx(ax5043_driver_p);

}


THD_WORKING_AREA(waAx5043_radio2, 1024);
THD_FUNCTION(ax5043_radio2, ax5043_driver_ptr)
{
  ax5043_drv_t* ax5043_driver_p=(ax5043_drv_t*)ax5043_driver_ptr;

  chBSemObjectInit(ax5043_driver_p->ax5043_bsem2, true);
  ax5043_init(ax5043_driver_p->ax5043_spip2, ax5043_driver_p->ax5043_config2);

    switch(ax5043_driver_p->ax5043_mode2) {
    case ax5043_rx:
      ax5043_prepare_rx(ax5043_driver_p->ax5043_spip2, ax5043_driver_p->ax5043_config2);
      break;
    case ax5043_tx:
      ax5043_prepare_tx(ax5043_driver_p->ax5043_spip2, ax5043_driver_p->ax5043_config2);
      break;
    case ax5043_off:
      ax5043_shutdown(ax5043_driver_p->ax5043_spip2);
    default:
      ax5043_prepare_rx(ax5043_driver_p->ax5043_spip2, ax5043_driver_p->ax5043_config2);
    }
  ax5043_set_addr(ax5043_driver_p->ax5043_spip2, ax5043_driver_p->ax5043_config2->localaddr);
  chBSemSignal(ax5043_driver_p->ax5043_bsem2);
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
