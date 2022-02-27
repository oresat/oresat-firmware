#ifndef _CO_MASTER_H_
#define _CO_MASTER_H_

#include "CANopen.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    SDO_CLI_WRITE,
    SDO_CLI_READ
} sdocli_op_t;

typedef struct {
    sdocli_op_t         op;
    uint8_t             node_id;
    uint16_t            index;
    uint8_t             subindex;
    size_t              total_size;
    size_t              buf_size;
    uint8_t            *buf;
    uint16_t            timeout;
    size_t              transferred;
    off_t               offset;
    CO_SDO_abortCode_t  abort_code;
} sdocli_job_t;

extern objects_fifo_t sdocli_fifo;

void sdo_init(void);
void sdo_transfer(sdocli_op_t op, uint8_t node_id, uint16_t index, uint8_t subindex, size_t total_size, size_t buf_size, void *buf);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
