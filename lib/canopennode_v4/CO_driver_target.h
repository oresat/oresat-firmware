/* Stitched together the Zephyr CANopenNode v2 module and the CANopenNode v4 example app
 * to make this interface code between Zephyr and CANopenNode v4.
 *
 * Zephyr CANopenNode v2 module:
 * https://github.com/zephyrproject-rtos/zephyr/tree/main/modules/canopennode
 *
 * CANopenNode v4 example app:
 * https://github.com/CANopenNode/CANopenNode/tree/master/example
 */

#ifndef CO_DRIVER_TARGET_H
#define CO_DRIVER_TARGET_H

#ifdef __cplusplus
extern "C" {
#endif

#include <zephyr/kernel.h>
#include <zephyr/types.h>
#include <zephyr/device.h>
#include <zephyr/drivers/can.h>
#include <zephyr/toolchain.h>
#include <zephyr/dsp/types.h>
#include <CO_driver_custom.h>

/* Use static variables instead of calloc() */
#define CO_USE_GLOBALS

/* Use Zephyr provided crc16 implementation */
#define CO_USE_OWN_CRC16

/* Use SDO buffer size from Kconfig */
#define CO_SDO_BUFFER_SIZE CONFIG_CANOPENNODE_SDO_BUFFER_SIZE

/* Use trace buffer size from Kconfig */
#define CO_TRACE_BUFFER_SIZE_FIXED CONFIG_CANOPENNODE_TRACE_BUFFER_SIZE

#ifdef CONFIG_LITTLE_ENDIAN
#define CO_LITTLE_ENDIAN
#else
#define CO_BIG_ENDIAN
#endif

typedef bool bool_t;
typedef char char_t;
typedef unsigned char oChar_t;
typedef unsigned char domain_t;

BUILD_ASSERT(sizeof(float32_t) >= 4);
BUILD_ASSERT(sizeof(float64_t) >= 8);

typedef struct canopen_rx_msg {
	uint8_t data[8];
	uint16_t ident;
	uint8_t DLC;
} CO_CANrxMsg_t;

/* Stack configuration override default values. For more information see file CO_config.h. */

/* Basic definitions. If big endian, CO_SWAP_xx macros must swap bytes. */
#define CO_LITTLE_ENDIAN
#define CO_SWAP_16(x) x
#define CO_SWAP_32(x) x
#define CO_SWAP_64(x) x

static inline uint16_t CO_CANrxMsg_readIdent(void *rxMsg)
{
	return ((struct can_frame *)rxMsg)->id;
}

static inline uint16_t CO_CANrxMsg_readDLC(void *rxMsg)
{
	return ((struct can_frame *)rxMsg)->dlc;
}
static inline const uint8_t *CO_CANrxMsg_readData(void *rxMsg)
{
	return ((struct can_frame *)rxMsg)->data;
}

/* Received message object */
typedef struct {
	uint16_t ident;
	uint16_t mask;
	void *object;
	void (*CANrx_callback)(void *object, void *message);
} CO_CANrx_t;

/* Transmit message object */
typedef struct {
	uint32_t ident;
	uint8_t DLC;
	uint8_t data[8];
	volatile bool_t bufferFull;
	volatile bool_t syncFlag;
} CO_CANtx_t;

/* CAN module object */
typedef struct {
	void *CANptr;
	CO_CANrx_t *rxArray;
	uint16_t rxSize;
	CO_CANtx_t *txArray;
	uint16_t txSize;
	uint16_t CANerrorStatus;
	volatile bool_t CANnormal;
	volatile bool_t useCANrxFilters;
	volatile bool_t bufferInhibitFlag;
	volatile bool_t firstCANtxMessage;
	volatile uint16_t CANtxCount;
	uint32_t errOld;
} CO_CANmodule_t;

/* Data storage object for one entry */
typedef struct {
	void *addr;
	size_t len;
	uint8_t subIndexOD;
	uint8_t attr;
	/* Additional variables (target specific) */
	void *addrNV;
} CO_storage_entry_t;

/* Synchronization between CAN receive and message processing threads. */
#define CO_MemoryBarrier()
#define CO_FLAG_READ(rxNew) ((rxNew) != NULL)
#define CO_FLAG_SET(rxNew)                                                                         \
	{                                                                                          \
		CO_MemoryBarrier();                                                                \
		rxNew = (void *)1L;                                                                \
	}
#define CO_FLAG_CLEAR(rxNew)                                                                       \
	{                                                                                          \
		CO_MemoryBarrier();                                                                \
		rxNew = NULL;                                                                      \
	}

void canopen_send_lock(CO_CANmodule_t *CANmodule);
void canopen_send_unlock(CO_CANmodule_t *CANmodule);
#define CO_LOCK_CAN_SEND(module)   canopen_send_lock(module)
#define CO_UNLOCK_CAN_SEND(module) canopen_send_unlock(module)

void canopen_emcy_lock(CO_CANmodule_t *CANmodule);
void canopen_emcy_unlock(CO_CANmodule_t *CANmodule);
#define CO_LOCK_EMCY(module)   canopen_emcy_lock(module)
#define CO_UNLOCK_EMCY(module) canopen_emcy_unlock(module)

void canopen_od_lock(CO_CANmodule_t *CANmodule);
void canopen_od_unlock(CO_CANmodule_t *CANmodule);
#define CO_LOCK_OD(module)   canopen_od_lock(module)
#define CO_UNLOCK_OD(module) canopen_od_unlock(module)

/*
 * CANopenNode RX callbacks run in interrupt context, no memory
 * barrier needed.
 */
#define CANrxMemoryBarrier()
#define IS_CANrxNew(rxNew) ((uintptr_t)rxNew)
#define SET_CANrxNew(rxNew)                                                                        \
	{                                                                                          \
		CANrxMemoryBarrier();                                                              \
		rxNew = (void *)1L;                                                                \
	}
#define CLEAR_CANrxNew(rxNew)                                                                      \
	{                                                                                          \
		CANrxMemoryBarrier();                                                              \
		rxNew = (void *)0L;                                                                \
	}

#ifdef __cplusplus
}
#endif

#endif
