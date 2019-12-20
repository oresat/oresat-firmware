#ifndef _CARD_H_
#define _CARD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ch.h"
#include "hal.h"

typedef struct card {
    uint8_t node_id;
    uint16_t opd_id;
} card_t;

void init_card(card_t *card);
void card_start(card_t *card);
void card_stop(card_t *card);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif /*_CARD_H_*/
