/*! \file ax5043_driver.h */


/*!
 * \addtogroup ax5043
 *  * @{
 *
 */
#ifndef _AX5043_DRIVER_H_
#define _AX5043_DRIVER_H_

//function declaration starts here
uint8_t ax5043_radio1_chg_config(ax5043_drv_t *ax5043_driver_p, ax5043_config_t config);
uint8_t ax5043_radio2_chg_config(ax5043_drv_t *ax5043_driver_p, ax5043_config_t config);
uint8_t ax5043_radio1_mode(ax5043_drv_t *ax5043_driver_p, ax5043_mode_t mode);
uint8_t ax5043_radio2_mode(ax5043_drv_t *ax5043_driver_p, ax5043_mode_t mode);
uint8_t ax5043_radio1_rx(ax5043_drv_t *ax5043_driver_p);
uint8_t ax5043_radio2_rx(ax5043_drv_t *ax5043_driver_p);
uint8_t ax5043_radio1_packet_tx(ax5043_drv_t *ax5043_driver_p, uint8_t *pkt, uint16_t pktlen);
uint8_t ax5043_radio2_packet_tx(ax5043_drv_t *ax5043_driver_p, uint8_t *pkt, uint16_t pktlen);
uint8_t ax5043_radio1_cw_tx(ax5043_drv_t *ax5043_driver_p, char pkt[], uint16_t pktlen);
uint8_t ax5043_radio2_cw_tx(ax5043_drv_t *ax5043_driver_p, char pkt[], uint16_t pktlen);
uint8_t ax5043_init(ax5043_drv_t *ax5043_driver_p);

#endif
//! @}
