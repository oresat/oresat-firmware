/*! \file ax5043_init.h */


/*!
 * \addtogroup ax5043
 *  * @{
 *
 */
#ifndef _AX5043_INIT_H_
#define _AX5043_INIT_H_

#include "ax5043.h"

void ax5043_set_regs(SPIDriver * spip);
void ax5043_set_regs_tx(SPIDriver * spip);
void ax5043_set_regs_rx(SPIDriver * spip);
void ax5043_set_regs_rxcont(SPIDriver * spip);
void ax5043_set_regs_rxcont_singleparamset(SPIDriver * spip);
void ax5043_prepare_tx(SPIDriver * spip);
void ax5043_prepare_rx(SPIDriver * spip);
uint8_t ax5043_get_pllvcoi(SPIDriver * spip);
void ax5043_init_registers_common(SPIDriver * spip);
void ax5043_init(SPIDriver * spip);
void transmit_loop(SPIDriver * spip, ax5043_trxstate_t ax5043_trxstate, uint16_t ax5043_txbuffer_len,uint8_t ax5043_txbuffer[], uint16_t ax5043_txbuffer_cnt);
uint8_t transmit_packet(SPIDriver * spip, ax5043_address_t *addr, ax5043_address_mask_t *ax5043_localaddr, uint8_t *pkt, uint16_t pktlen);
uint8_t receive_loop(SPIDriver * spip, uint8_t ax5043_rxbuffer[]);

#endif
//! @}
