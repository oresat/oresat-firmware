/*! \file ax5043.h */


/*!
 * \addtogroup ax5043
 *  * @{
 *
 */
#ifndef _AX5043_ENGR_f3_H
#define _AX5043_ENGR_f3_H

#define DEBUG_SERIAL  SD2
#define DEBUG_CHP     ((BaseSequentialStream *) &DEBUG_SERIAL)

#include <stdbool.h>
#include <stdint.h>
#include "ax5043_common.h"

void ax5043_f3_set_regs(SPIDriver * spip);
void ax5043_f3_set_regs_tx(SPIDriver * spip);
void ax5043_f3_set_regs_rx(SPIDriver * spip);
void ax5043_f3_set_regs_rxcont(SPIDriver * spip);
void ax5043_f3_set_regs_rxcont_singleparamset(SPIDriver * spip);
void ax5043_f3_prepare_tx(SPIDriver * spip);
void ax5043_f3_prepare_rx(SPIDriver * spip);
uint8_t axradio_f3_get_pllvcoi(SPIDriver * spip);
void ax5043_f3_init_registers_common(SPIDriver * spip);
void ax5043_f3_init(SPIDriver * spip);
void transmit_f3_loop(SPIDriver * spip, axradio_trxstate_t axradio_trxstate, uint16_t axradio_txbuffer_len,uint8_t axradio_txbuffer[], uint16_t axradio_txbuffer_cnt);
uint8_t transmit_f3_packet(SPIDriver * spip, axradio_address_t *addr, axradio_address_mask_t *axradio_localaddr, uint8_t *pkt, uint16_t pktlen);
uint8_t receive_f3_loop(SPIDriver * spip, uint8_t axradio_rxbuffer[]);

#endif
//! @}
