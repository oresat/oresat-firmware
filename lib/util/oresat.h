#ifndef ORESAT_H
#define ORESAT_H

#include <CANopen.h>
#include <CO_OD.h>
#ifdef STM32F091xC
#include "stm32f0xx_hal.h"
#endif

#define DEFAULT_NODE_ID 0x7C

static inline uint8_t oresat_get_node_id(void)
{
	uint8_t node_id = DEFAULT_NODE_ID;
#ifdef STM32F091xC
	/* node id is set in the stm32f091rc's option bytes. */
	node_id = HAL_FLASHEx_OBGetUserData(OB_DATA_ADDRESS_DATA0); // (FLASH->OBR & FLASH_OBR_DATA0_Msk) >> FLASH_OBR_DATA0_Pos;
	if (node_id == 0 || node_id > DEFAULT_NODE_ID) {
		node_id = DEFAULT_NODE_ID;
	}
#endif
	return node_id;
}

static inline void oresat_fix_pdo_cob_ids(uint8_t node_id)
{
	int i;
	int e;
	uint32_t cob_id;
	const CO_OD_entry_t *entry;
	CO_RPDO_t *rpdo;
	CO_TPDO_t *tpdo;
	void *data;

	for (e = 0; e < CO_NO_RPDO; e++) {
		rpdo = CO->RPDO[e];
		entry = rpdo->SDO->OD;
		if ((entry->index >= 0x1400) && (entry->index < 0x1600)) {
			i = entry->index - 0x1400;
			data = CO_OD_getDataPointer(rpdo->SDO, 0, 1);
			cob_id = CO_getUint32(data);
			//OD_get_u32(entry, 1, &cob_id, true);
			if ((cob_id & 0x7FF) == (0x200U + (0x100U * (i % 4) + (i / 4)))) {
				CO_setUint32(data, cob_id + node_id);
				//OD_set_u32(entry, 1, cob_id + node_id, true);
			}
		}
	}

	for (e = 0; e < CO_NO_TPDO; e++) {
		tpdo = CO->TPDO[e];
		entry = tpdo->SDO->OD;
		if ((entry->index >= 0x1800) && (entry->index < 0x1A00)) {
			i = entry->index - 0x1800;
			data = CO_OD_getDataPointer(tpdo->SDO, 0, 1);
			cob_id = CO_getUint32(data);
			//OD_get_u32(entry, 1, &cob_id, true);
			if ((cob_id & 0x7FF) == (0x180U + (0x100U * (i % 4) + (i / 4)))) {
				CO_setUint32(data, cob_id + node_id);
				//OD_set_u32(entry, 1, cob_id + node_id, true);
			}
		}
	}
}

#endif
