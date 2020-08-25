#ifndef _CO_MASTER_H_
#define _CO_MASTER_H_

#include "CANopen.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    SDOCLI_ST_IDLE,
    SDOCLI_ST_DOWNLOAD,
    SDOCLI_ST_UPLOAD
} sdocli_state_t;

typedef struct sdocli {
    /* SDO client thread pointer */
    thread_t           *tp;
    /* Semaphore for exclusive control of client object */
    semaphore_t         sem;
    /* Pointer to SDO client object */
    CO_SDOclient_t     *sdo_c;
    /* Client state tracking for thread */
    sdocli_state_t      state;
    size_t              size_transferred;
    size_t              size_indicated;
    /* Buffer IO callback to fill/empty buffer, called by thread */
    bool (*buf_cb)(struct sdocli *sdocli, CO_SDO_return_t ret, CO_SDO_abortCode_t *abort_code, void *arg);
    /* Optional argument to Buffer IO callback */
    void *buf_cb_arg;
} sdocli_t;

thread_t *sdo_transfer(char type, uint8_t node_id, uint16_t index, uint8_t subindex, size_t size, bool (*buf_cb)(struct sdocli *sdocli, CO_SDO_return_t ret, CO_SDO_abortCode_t *abort_code, void *arg), void *buf_cb_arg);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
