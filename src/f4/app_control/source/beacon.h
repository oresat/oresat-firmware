#ifndef _BEACON_H_
#define _BEACON_H_

#include "ch.h"
#include "hal.h"
#include "radio.h"

typedef enum {
    TLM_MSG,
    TLM_VAL,
    TLM_PTR,
    TLM_OD
} tlm_type_t;

typedef struct tlm_item {
    tlm_type_t          type;
    size_t              len;
    union {
        char            *msg;
        uint32_t        val;
        void            *ptr;
        struct {
            uint32_t    index   : 16;
            uint32_t    subindex: 8;
        };
    };
} tlm_item_t;

typedef struct tlm_pkt {
    size_t              item_cnt;
    const tlm_item_t    *item;
} tlm_pkt_t;

#ifdef __cplusplus
extern "C" {
#endif

void beacon_send(const radio_cfg_t *cfg);
THD_FUNCTION(beacon, arg);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
