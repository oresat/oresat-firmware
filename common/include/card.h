#ifndef _CARD_H_
#define _CARD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ch.h"
#include "hal.h"
#include "opd.h"

typedef enum {
    CARD_OFFLINE,
    CARD_INIT,
    CARD_ONLINE,
    CARD_FAILED
} card_state_t;

typedef struct card {
    card_state_t state;
    opd_addr_t opd_addr;
    uint8_t node_id;
} card_t;

void init_card(card_t *card);
void card_start(card_t *card);
void card_stop(card_t *card);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif /*_CARD_H_*/
