/*! \file ax5043.h */


/*!
 * \addtogroup ax5043
 *  * @{
 *
 */
#ifndef _AX5043_ENGR_F2_H
#define _AX5043_ENGR_F2_H

#define DEBUG_SERIAL  SD2
#define DEBUG_CHP     ((BaseSequentialStream *) &DEBUG_SERIAL)

#include <stdbool.h>
#include <stdint.h>


void ax5043_f2_set_regs(SPIDriver * spip);
void ax5043_f2_set_regs_tx(SPIDriver * spip);
void ax5043_f2_set_regs_rx(SPIDriver * spip);
void ax5043_f2_set_regs_rxcont(SPIDriver * spip);
void ax5043_f2_set_regs_rxcont_singleparamset(SPIDriver * spip);
void ax5043_f2_prepare_tx(SPIDriver * spip);
void ax5043_f2_prepare_rx(SPIDriver * spip);
uint8_t axradio_f2_get_pllvcoi(SPIDriver * spip);
void ax5043_f2_init(SPIDriver * spip);
void transmit_f2_loop(SPIDriver * spip, axradio_trxstate_t axradio_trxstate, uint16_t axradio_txbuffer_len,uint8_t axradio_txbuffer[], uint16_t axradio_txbuffer_cnt);
uint8_t transmit_f2_packet(SPIDriver * spip, const struct axradio_address *addr, const uint8_t *pkt, uint16_t pktlen);
uint8_t receive_f2_loop(SPIDriver * spip, uint8_t axradio_rxbuffer[]);

#endif
//! @}
