/* Stitched together the Zephyr CANopenNode v2 module and the CANopenNode v4 example app
 * to make this interface code between Zephyr and CANopenNode v4.
 *
 * Zephyr CANopenNode v2 module:
 * https://github.com/zephyrproject-rtos/zephyr/tree/main/modules/canopennode
 *
 * CANopenNode v4 example app:
 * https://github.com/CANopenNode/CANopenNode/tree/master/example
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/can.h>
#include <zephyr/init.h>
#include <zephyr/sys/util.h>

#include "CANopen.h"
#include <OD.h>
#include <CO_driver_target.h>
#include <canopennode.h>

#define OD_CNT_RX_MSG (OD_CNT_NMT + OD_CNT_SYNC + OD_CNT_SDO_SRV)

struct can_filter_user_data {
	void *object;                 /* a CANopenNode object (first arg to func) */
	void (*func)(void *, void *); /* object, can_frame */
};

static struct can_filter filters[OD_CNT_RX_MSG];
static struct can_filter_user_data filters_user_data[OD_CNT_RX_MSG];

K_KERNEL_STACK_DEFINE(canopen_tx_workq_stack, CONFIG_CANOPENNODE_TX_WORKQUEUE_STACK_SIZE);

struct k_work_q canopen_tx_workq;

struct canopen_tx_work_container {
	struct k_work work;
	CO_CANmodule_t *CANmodule;
};

struct canopen_tx_work_container canopen_tx_queue;

/* Get error counters from the module. If necessary, function may use different way to determine
 * errors. */
static uint16_t rxErrors = 0, txErrors = 0, overflow = 0;

K_MUTEX_DEFINE(canopen_send_mutex);
K_MUTEX_DEFINE(canopen_emcy_mutex);
K_MUTEX_DEFINE(canopen_co_mutex);

inline void canopen_send_lock(CO_CANmodule_t *CANmodule)
{
	(void)CANmodule;
	k_mutex_lock(&canopen_send_mutex, K_FOREVER);
}

inline void canopen_send_unlock(CO_CANmodule_t *CANmodule)
{
	(void)CANmodule;
	k_mutex_unlock(&canopen_send_mutex);
}

inline void canopen_emcy_lock(CO_CANmodule_t *CANmodule)
{
	(void)CANmodule;
	k_mutex_lock(&canopen_emcy_mutex, K_FOREVER);
}

inline void canopen_emcy_unlock(CO_CANmodule_t *CANmodule)
{
	(void)CANmodule;
	k_mutex_unlock(&canopen_emcy_mutex);
}

inline void canopen_od_lock(CO_CANmodule_t *CANmodule)
{
	(void)CANmodule;
	k_mutex_lock(&canopen_co_mutex, K_FOREVER);
}

inline void canopen_od_unlock(CO_CANmodule_t *CANmodule)
{
	(void)CANmodule;
	k_mutex_unlock(&canopen_co_mutex);
}

static void canopen_tx_callback(const struct device *dev, int error, void *arg)
{
	CO_CANmodule_t *CANmodule = arg;

	ARG_UNUSED(dev);

	if (!CANmodule) {
		printf("failed to process CAN tx callback");
		return;
	}

	if (error == 0) {
		CANmodule->firstCANtxMessage = false;
	}

	k_work_submit_to_queue(&canopen_tx_workq, &canopen_tx_queue.work);
}

static void canopen_tx_retry(struct k_work *item)
{
	struct canopen_tx_work_container *container =
		CONTAINER_OF(item, struct canopen_tx_work_container, work);
	CO_CANmodule_t *CANmodule = container->CANmodule;
	struct can_frame frame;
	CO_CANtx_t *buffer;
	int err;
	uint16_t i;

	memset(&frame, 0, sizeof(frame));

	CO_LOCK_CAN_SEND(CANmodule);

	for (i = 0; i < CANmodule->txSize; i++) {
		buffer = &CANmodule->txArray[i];
		if (buffer->bufferFull) {
			frame.id = buffer->ident;
			frame.dlc = buffer->DLC;
			memcpy(frame.data, buffer->data, buffer->DLC);

			err = can_send(CANmodule->CANptr, &frame, K_NO_WAIT, canopen_tx_callback,
				       CANmodule);
			if (err == -EAGAIN) {
				break;
			} else if (err != 0) {
				CO_errorReport(CO->em, CO_EM_GENERIC_SOFTWARE_ERROR,
					       CO_EMC_COMMUNICATION, 0);
			}

			buffer->bufferFull = false;
		}
	}

	CO_UNLOCK_CAN_SEND(CANmodule);
}

void CO_CANsetConfigurationMode(void *CANptr)
{
	int err = can_stop(CANptr);
	if (err != 0 && err != -EALREADY) {
		printf("failed to disable CAN interface (err %d)\n", err);
	}
}

void CO_CANsetNormalMode(CO_CANmodule_t *CANmodule)
{
	int err;

	err = can_set_mode(CANmodule->CANptr, CAN_MODE_NORMAL);
	if (err) {
		printf("failed to configure CAN interface (err %d)\n", err);
		return;
	}

	err = can_start(CANmodule->CANptr);
	if (err != 0 && err != -EALREADY) {
		printf("failed to start CAN interface (err %d)\n", err);
		return;
	}

	CANmodule->CANnormal = true;
}

CO_ReturnError_t CO_CANmodule_init(CO_CANmodule_t *CANmodule, void *CANptr, CO_CANrx_t rxArray[],
				   uint16_t rxSize, CO_CANtx_t txArray[], uint16_t txSize,
				   uint16_t CANbitRate)
{
	uint16_t i;
	int err;

	printf("rxSize = %d, txSize = %d\n", rxSize, txSize);

	if (!CANmodule || !rxArray || !txArray || !CANptr) {
		printf("failed to initialize CAN module\n");
		return CO_ERROR_ILLEGAL_ARGUMENT;
	}

	int max_filters = can_get_max_filters(CANptr, false);
	if (max_filters != -ENOSYS) {
		if (max_filters < 0) {
			printf("unable to determine number of CAN RX filters");
			return CO_ERROR_SYSCALL;
		} else if (rxSize > max_filters) {
			printf("insufficient number of concurrent CAN RX filters"
			       " (needs %d, %d available)\n",
			       rxSize, max_filters);
			return CO_ERROR_OUT_OF_MEMORY;
		}
	}

	canopen_tx_queue.CANmodule = CANmodule;

	CANmodule->CANptr = CANptr;
	CANmodule->rxArray = rxArray;
	CANmodule->rxSize = rxSize;
	CANmodule->txArray = txArray;
	CANmodule->txSize = txSize;
	CANmodule->CANerrorStatus = 0;
	CANmodule->CANnormal = false;
	CANmodule->useCANrxFilters = rxSize <= max_filters;
	CANmodule->bufferInhibitFlag = false;
	CANmodule->firstCANtxMessage = false;
	CANmodule->CANtxCount = 0U;
	CANmodule->errOld = 0U;

	for (i = 0U; i < rxSize; i++) {
		rxArray[i].ident = 0U;
		rxArray[i].mask = 0xFFFFU;
		rxArray[i].object = NULL;
		rxArray[i].CANrx_callback = NULL;
	}

	for (i = 0U; i < txSize; i++) {
		txArray[i].bufferFull = false;
	}

	/* Configure CAN module registers */

	/* Configure CAN timing */

	/* Configure CAN module hardware filters */
	if (CANmodule->useCANrxFilters) {
		/* CAN module filters are used, they will be configured with */
		/* CO_CANrxBufferInit() functions, called by separate CANopen */
		/* init functions. */
		/* Configure all maks so, that received message must match filter */
	} else {
		/* CAN module filters are not used, all messages with standard 11-bit */
		/* identifier will be received */
		/* Configure mask 0 so, that all messages with standard identifier are accepted */
	}

	err = can_set_bitrate(CANptr, KHZ(CANbitRate));
	if (err) {
		printf("failed to configure CAN bitrate (err %d)\n", err);
		return CO_ERROR_ILLEGAL_ARGUMENT;
	}

	/* Configure CAN interrupt registers */

	return CO_ERROR_NO;
}

void CO_CANmodule_disable(CO_CANmodule_t *CANmodule)
{
	if (!CANmodule || !CANmodule->CANptr) {
		return;
	}

	int err = can_stop(CANmodule->CANptr);
	if (err != 0 && err != -EALREADY) {
		printf("failed to disable CAN interface (err %d)\n", err);
	}
}

static void rx_callback(const struct device *dev, struct can_frame *frame, void *user_data)
{
	if (user_data) {
		struct can_filter_user_data *filter_user_data =
			(struct can_filter_user_data *)user_data;
		filter_user_data->func(filter_user_data->object, (void *)frame);
	}
}

CO_ReturnError_t CO_CANrxBufferInit(CO_CANmodule_t *CANmodule, uint16_t index, uint16_t ident,
				    uint16_t mask, bool_t rtr, void *object,
				    void (*CANrx_callback)(void *object, void *message))
{

	CO_ReturnError_t ret = CO_ERROR_NO;
	if ((CANmodule != NULL) && (object != NULL) && (CANrx_callback != NULL) &&
	    (index < OD_CNT_RX_MSG)) {
		/* buffer, which will be configured */
		CO_CANrx_t *buffer = &CANmodule->rxArray[index];

		/* Configure object variables */
		buffer->object = object;
		buffer->CANrx_callback = CANrx_callback;

		buffer->ident = ident & 0x07FFU;
		if (rtr) {
			printf("request for RTR frames, but RTR frames are rejected");
			CO_errorReport(CO->em, CO_EM_GENERIC_SOFTWARE_ERROR,
				       CO_EMC_SOFTWARE_INTERNAL, 0);
			return CO_ERROR_ILLEGAL_ARGUMENT;
		}
		buffer->mask = (mask & 0x07FFU) | 0x0800U;

		/* Set CAN hardware module filter and mask. */
		if (CANmodule->useCANrxFilters) {
			filters[index].mask = mask;
			filters[index].id = ident;
			filters[index].flags = 0;
			filters_user_data[index].func = CANrx_callback;
			filters_user_data[index].object = object;
			can_add_rx_filter(CANmodule->CANptr, rx_callback,
					  (void *)&filters_user_data[index], &filters[index]);
		}
	} else {
		printf("failed to initialize CAN rx buffer, illegal argument");
		ret = CO_ERROR_ILLEGAL_ARGUMENT;
	}

	return ret;
}

CO_CANtx_t *CO_CANtxBufferInit(CO_CANmodule_t *CANmodule, uint16_t index, uint16_t ident,
			       bool_t rtr, uint8_t noOfBytes, bool_t syncFlag)
{
	CO_CANtx_t *buffer = NULL;

	if (CANmodule == NULL) {
		return NULL;
	}

	if (index >= CANmodule->txSize) {
		printf("failed to initialize CAN rx buffer, illegal argument");
		CO_errorReport(CO->em, CO_EM_GENERIC_SOFTWARE_ERROR, CO_EMC_SOFTWARE_INTERNAL, 0);
		return NULL;
	}

	/* get sepcific buffer */
	buffer = &CANmodule->txArray[index];
	buffer->ident = ident;
	buffer->DLC = noOfBytes;
	buffer->bufferFull = false;
	buffer->syncFlag = syncFlag;

	return buffer;
}

CO_ReturnError_t CO_CANsend(CO_CANmodule_t *CANmodule, CO_CANtx_t *buffer)
{
	CO_ReturnError_t ret = CO_ERROR_NO;
	struct can_frame frame;
	int err;

	if (!CANmodule || !CANmodule->CANptr || !buffer) {
		return CO_ERROR_ILLEGAL_ARGUMENT;
	}

	memset(&frame, 0, sizeof(frame));

	CO_LOCK_CAN_SEND(CANmodule);

	if (buffer->bufferFull) {
		if (!CANmodule->firstCANtxMessage) {
			CO_errorReport(CO->em, CO_EM_CAN_TX_OVERFLOW, CO_EMC_CAN_OVERRUN,
				       buffer->ident);
		}
		buffer->bufferFull = false;
		ret = CO_ERROR_TX_OVERFLOW;
	}

	frame.id = buffer->ident;
	frame.dlc = buffer->DLC;
	frame.flags = 0;
	memcpy(frame.data, buffer->data, buffer->DLC);

	err = can_send(CANmodule->CANptr, &frame, K_NO_WAIT, canopen_tx_callback, CANmodule);
	if (err == -EAGAIN) {
		buffer->bufferFull = true;
	} else if (err != 0) {
		CO_errorReport(CO->em, CO_EM_GENERIC_SOFTWARE_ERROR, CO_EMC_COMMUNICATION, 0);
		ret = CO_ERROR_TX_UNCONFIGURED;
	}

	CO_UNLOCK_CAN_SEND(CANmodule);

	return ret;
}

void CO_CANclearPendingSyncPDOs(CO_CANmodule_t *CANmodule)
{
	bool_t tpdoDeleted = false;
	CO_CANtx_t *buffer;
	uint16_t i;

	if (!CANmodule) {
		return;
	}

	CO_LOCK_CAN_SEND(CANmodule);

	for (i = 0; i < CANmodule->txSize; i++) {
		buffer = &CANmodule->txArray[i];
		if (buffer->bufferFull && buffer->syncFlag) {
			buffer->bufferFull = false;
			tpdoDeleted = true;
		}
	}

	CO_UNLOCK_CAN_SEND(CANmodule);

	if (tpdoDeleted) {
		CO_errorReport(CO->em, CO_EM_TPDO_OUTSIDE_WINDOW, CO_EMC_COMMUNICATION, 0);
	}
}

void CO_CANmodule_process(CO_CANmodule_t *CANmodule)
{
	uint32_t err;

	err = ((uint32_t)txErrors << 16) | ((uint32_t)rxErrors << 8) | overflow;

	if (CANmodule->errOld != err) {
		uint16_t status = CANmodule->CANerrorStatus;

		CANmodule->errOld = err;

		if (txErrors >= 256U) {
			/* bus off */
			status |= CO_CAN_ERRTX_BUS_OFF;
		} else {
			/* recalculate CANerrorStatus, first clear some flags */
			status &= 0xFFFF ^ (CO_CAN_ERRTX_BUS_OFF | CO_CAN_ERRRX_WARNING |
					    CO_CAN_ERRRX_PASSIVE | CO_CAN_ERRTX_WARNING |
					    CO_CAN_ERRTX_PASSIVE);

			/* rx bus warning or passive */
			if (rxErrors >= 128) {
				status |= CO_CAN_ERRRX_WARNING | CO_CAN_ERRRX_PASSIVE;
			} else if (rxErrors >= 96) {
				status |= CO_CAN_ERRRX_WARNING;
			}

			/* tx bus warning or passive */
			if (txErrors >= 128) {
				status |= CO_CAN_ERRTX_WARNING | CO_CAN_ERRTX_PASSIVE;
			} else if (txErrors >= 96) {
				status |= CO_CAN_ERRTX_WARNING;
			}

			/* if not tx passive clear also overflow */
			if ((status & CO_CAN_ERRTX_PASSIVE) == 0) {
				status &= 0xFFFF ^ CO_CAN_ERRTX_OVERFLOW;
			}
		}

		if (overflow != 0) {
			/* CAN RX bus overflow */
			status |= CO_CAN_ERRRX_OVERFLOW;
		}

		CANmodule->CANerrorStatus = status;
	}
}

void CO_CANinterrupt(CO_CANmodule_t *CANmodule)
{

	/* receive interrupt */
	if (1) {
		CO_CANrxMsg_t *rcvMsg;     /* pointer to received message in CAN module */
		uint16_t index;            /* index of received message */
		uint32_t rcvMsgIdent;      /* identifier of the received message */
		CO_CANrx_t *buffer = NULL; /* receive message buffer from CO_CANmodule_t object. */
		bool_t msgMatched = false;

		rcvMsg = 0; /* get message from module here */
		rcvMsgIdent = rcvMsg->ident;
		if (CANmodule->useCANrxFilters) {
			/* CAN module filters are used. Message with known 11-bit identifier has
			 * been received */
			index = 0; /* get index of the received message here. Or something similar
				    */
			if (index < CANmodule->rxSize) {
				buffer = &CANmodule->rxArray[index];
				/* verify also RTR */
				if (((rcvMsgIdent ^ buffer->ident) & buffer->mask) == 0U) {
					msgMatched = true;
				}
			}
		} else {
			/* CAN module filters are not used, message with any standard 11-bit
			 * identifier */
			/* has been received. Search rxArray form CANmodule for the same CAN-ID. */
			buffer = &CANmodule->rxArray[0];
			for (index = CANmodule->rxSize; index > 0U; index--) {
				if (((rcvMsgIdent ^ buffer->ident) & buffer->mask) == 0U) {
					msgMatched = true;
					break;
				}
				buffer++;
			}
		}

		/* Call specific function, which will process the message */
		if (msgMatched && (buffer != NULL) && (buffer->CANrx_callback != NULL)) {
			buffer->CANrx_callback(buffer->object, (void *)rcvMsg);
		}

		/* Clear interrupt flag */
	}

	/* transmit interrupt */
	else if (0) {
		/* Clear interrupt flag */

		/* First CAN message (bootup) was sent successfully */
		CANmodule->firstCANtxMessage = false;
		/* clear flag from previous message */
		CANmodule->bufferInhibitFlag = false;
		/* Are there any new messages waiting to be send */
		if (CANmodule->CANtxCount > 0U) {
			uint16_t i; /* index of transmitting message */

			/* first buffer */
			CO_CANtx_t *buffer = &CANmodule->txArray[0];
			/* search through whole array of pointers to transmit message buffers. */
			for (i = CANmodule->txSize; i > 0U; i--) {
				/* if message buffer is full, send it. */
				if (buffer->bufferFull) {
					buffer->bufferFull = false;
					CANmodule->CANtxCount--;

					/* Copy message to CAN buffer */
					CANmodule->bufferInhibitFlag = buffer->syncFlag;
					/* canSend... */
					break; /* exit for loop */
				}
				buffer++;
			} /* end of for loop */

			/* Clear counter if no more messages */
			if (i == 0U) {
				CANmodule->CANtxCount = 0U;
			}
		}
	} else {
		/* some other interrupt reason */
	}
}

static int canopen_init(void)
{

	k_work_queue_start(&canopen_tx_workq, canopen_tx_workq_stack,
			   K_KERNEL_STACK_SIZEOF(canopen_tx_workq_stack),
			   CONFIG_CANOPENNODE_TX_WORKQUEUE_PRIORITY, NULL);

	k_thread_name_set(&canopen_tx_workq.thread, "canopen_tx_workq");

	k_work_init(&canopen_tx_queue.work, canopen_tx_retry);

	return 0;
}

SYS_INIT(canopen_init, APPLICATION, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
