/*! \file ax5043.h */


/*!
 * \addtogroup ax5043
 *  * @{
 *
 */
#ifndef _AX5043_ENG_H
#define _AX5043_ENG_H

#define DEBUG_SERIAL  SD2
#define DEBUG_CHP     ((BaseSequentialStream *) &DEBUG_SERIAL)

#include <stdbool.h>
#include <stdint.h>





//function declaration starts here
void ax5043_set_regs(SPIDriver * spip);
void ax5043_set_regs_tx(SPIDriver * spip);
void ax5043_set_regs_rx(SPIDriver * spip);
void ax5043_set_regs_rxcont(SPIDriver * spip);
void ax5043_set_regs_rxcont_singleparamset(SPIDriver * spip);

void ax5043_reset(SPIDriver * spip);
void ax5043_prepare_tx(SPIDriver * spip);
void ax5043_prepare_tx(SPIDriver * spip);
void ax5043_prepare_rx(SPIDriver * spip);
void ax5043_init_registers_common(SPIDriver * spip);
uint8_t axradio_get_pllvcoi(SPIDriver * spip);

void ax5043_init(SPIDriver * spip);
void ax5043_transmit(SPIDriver * spip);
void ax5043_receive(SPIDriver * spip);


//functions added from bradenburg's code.
uint8_t transmit_packet(SPIDriver * spip, const struct axradio_address *addr, const uint8_t *pkt, uint16_t pktlen);
void transmit_loop(SPIDriver * spip, axradio_trxstate_t axradio_trxstate, uint16_t axradio_txbuffer_len,uint8_t axradio_txbuffer[], uint16_t axradio_txbuffer_cnt);
void ax5043_writefifo(SPIDriver * spip,const uint8_t *ptr, uint8_t len);
uint8_t ax5043_readfifo(SPIDriver * spip, uint8_t axradio_rxbuffer[], uint8_t len) ;
uint8_t receive_loop(SPIDriver * spip);

#endif
//! @}
