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




typedef struct
{
  SPIDriver * ax5043_spip1;
  SPIDriver * ax5043_spip2;
  ax5043_frequency_t ax5043_freq1;
  ax5043_frequency_t ax5043_freq2;
  ax5043_mode_t ax5043_mode1;
  ax5043_mode_t ax5043_mode2;
  ioline_t ax5043_int1;
  ioline_t ax5043_int2;
} ax5043_drv_t;


typedef enum {
    ax5043_f1,
    ax5043_f2,
    ax5043_f3,
    ax5043_f4
} ax5043_frequency_t;


typedef enum {
    ax5043_rx,
    ax5043_tx,
    ax5043_off,
} ax5043_mode_t;




//function declaration starts here
uint8_t ax5043_write_reg(SPIDriver * spip, uint16_t reg, uint8_t value, uint8_t ret_value[]);
uint8_t ax5043_read_reg(SPIDriver * spip, uint16_t reg, uint8_t value, uint8_t ret_value[]);
void ax5043_shutdown(SPIDriver * spip);
void ax5043_standby(SPIDriver * spip);
void ax5043_fifo_en(SPIDriver * spip);
void ax5043_full_rx(SPIDriver * spip);
void ax5043_synth_tx(SPIDriver * spip);
void ax5043_full_tx(SPIDriver * spip);
void ax5043_set_addr(SPIDriver * spip, const struct axradio_address_mask local_addr);
void ax5043_reset(SPIDriver * spip);
void ax5043_writefifo(SPIDriver * spip,const uint8_t *ptr, uint8_t len);
uint8_t ax5043_readfifo(SPIDriver * spip, uint8_t axradio_rxbuffer[], uint8_t len);
void ax5043_writefifo(SPIDriver * spip,const uint8_t *ptr, uint8_t len);
uint8_t ax5043_readfifo(SPIDriver * spip, uint8_t axradio_rxbuffer[], uint8_t len) ;

#endif
//! @}
