/*! \file ax5043_driver.h */


/*!
 * \addtogroup ax5043
 *  * @{
 *
 */
#ifndef _AX5043_DRIVER_H
#define _AX5043_DRIVER_H

#define DEBUG_SERIAL  SD2
#define DEBUG_CHP     ((BaseSequentialStream *) &DEBUG_SERIAL)

#include <stdbool.h>
#include <stdint.h>
//#include <ax5043_common.h>


#define AX5043_F1       0
#define AX5043_F2       1
#define AX5043_F3       2
#define AX5043_F4       3


#define AX5043_RX       0
#define AX5043_TX       1
#define AX5043_OFF      2


#define AX5043_BUSY     0
#define AX5043_IDLE     1


typedef enum {
    ax5043_f1,
    ax5043_f2,
    ax5043_f3,
    ax5043_f4
} ax5043_config_t;


typedef enum {
    ax5043_rx,
    ax5043_tx,
    ax5043_off,
} ax5043_mode_t;


typedef enum {
    ax5043_busy,
    ax5043_idle,
} ax5043_state_t;


typedef struct
{
  SPIDriver * ax5043_spip1;
  SPIDriver * ax5043_spip2;
  ax5043_config_t ax5043_config1;
  ax5043_config_t ax5043_config2;
  ax5043_mode_t ax5043_mode1;
  ax5043_mode_t ax5043_mode2;
  ioline_t ax5043_int1;
  ioline_t ax5043_int2;
  binary_semaphore_t *ax5043_bsem1;
  binary_semaphore_t *ax5043_bsem2;
  axradio_address_t *remoteaddr;
  axradio_address_mask_t *localaddr;
  mailbox_t * ax5043_rx_mb1;
  mailbox_t * ax5043_rx_mb2;
} ax5043_drv_t;



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
