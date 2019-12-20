#include "card.h"
#include "opd.h"

void init_card(card_t *card, opd_addr_t opd_addr, uint8_t node_id)
{
    card->state = CARD_OFFLINE;
    card->opd_addr = opd_addr;
    card->node_id = node_id;
}

void card_start(card_t *card)
{

}

void card_stop(card_t *card)
{

}
