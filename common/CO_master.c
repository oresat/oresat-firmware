#include "CO_threads.h"
#include "CO_master.h"

objects_fifo_t sdocli_fifo;
static msg_t sdocli_fifo_msgs[OD_CNT_SDO_CLI];
static sdocli_job_t sdocli_fifo_buf[OD_CNT_SDO_CLI];

void sdo_init(void)
{
    chFifoObjectInit(&sdocli_fifo, sizeof(sdocli_job_t), OD_CNT_SDO_CLI, sdocli_fifo_buf, sdocli_fifo_msgs);
}

void sdo_transfer(sdocli_op_t op, uint8_t node_id, uint16_t index, uint8_t subindex, size_t total_size, size_t buf_size, void *buf)
{
    sdocli_job_t *job = chFifoTakeObjectTimeout(&sdocli_fifo, TIME_INFINITE);

    job->op = op;
    job->node_id = node_id;
    job->index = index;
    job->subindex = subindex;
    if (op == SDO_CLI_WRITE) {
        /* TODO: Remove this DbgCheck when segmented transfer and callbacks are implemented */
        osalDbgCheck(total_size > 0 && total_size == buf_size);
        job->total_size = total_size;
    }
    job->buf_size = buf_size;
    job->buf = buf;
    job->timeout = 1000;
    job->transferred = 0;
    job->offset = 0;

    chFifoSendObject(&sdocli_fifo, job);
}
