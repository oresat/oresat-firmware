#ifndef _CO_MASTER_H_
#define _CO_MASTER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "CANopen.h"

int sdo_upload(
        CO_SDOclient_t *SDOclient,
        uint8_t         node_id,
        uint16_t        index,
        uint8_t         subindex,
        void           *data,
        uint32_t        max_len,
        uint32_t       *ret_len,
        uint32_t       *abrt_code,
        uint16_t        timeout,
        bool            block);

int sdo_download(
        CO_SDOclient_t *SDOclient,
        uint8_t         node_id,
        uint16_t        index,
        uint8_t         subindex,
        void           *data,
        uint32_t        len,
        uint32_t       *abrt_code,
        uint16_t        timeout,
        bool            block);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
