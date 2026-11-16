#ifndef ORESAT_H
#define ORESAT_H

#include <canopennode.h>
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

static inline uint32_t *get_cob_id_ptr(CO_OD_entry_t *entry)
{
	CO_OD_entryRecord_t *rec;

	// check that we are pointing at an Object Type of record; if we are:
	if (entry && !entry->attribute && !entry->length && entry->pData) {

		// pData should then point to an array of CO_OD_entryRecord_t structures
		rec = (CO_OD_entryRecord_t *)entry->pData;

		// this should point to an array of 7; subindex 1 is where the COB ID is stored
		// which should be a 4 byte value
		if (rec[1].pData && (rec[1].length == sizeof(uint32_t))) {
			// if all that is true, then we have the cob_id
			return (uint32_t *)rec[1].pData;
		} else {
			printk("ERROR on entry %p: rec pData %p, len %u\n", entry, rec[1].pData, rec[1].length);
		}
	} else {
		printk("ERROR on entry %p: attrib 0x%04x, len 0x%04x, pData %p\n",
			   entry, entry->attribute, entry->length, entry->pData);
	}
	return NULL;
}

static inline void oresat_fix_pdo_cob_ids(uint8_t node_id)
{
	extern CO_OD_entry_t CO_OD[CO_OD_NoOfElements];
	CO_OD_entry_t *entry = CO_OD;
	uint32_t *cob_id_ptr;
	uint32_t cob_id;
	int i;
	int e;

	for (e = 0; e < CO_OD_NoOfElements; e++) {
#if CO_NO_RPDO > 0
		if ((entry->index >= 0x1400) && (entry->index < 0x1600)) {
			i = entry->index - 0x1400;

			cob_id_ptr = get_cob_id_ptr(entry);
			if (cob_id_ptr) {
				cob_id = *cob_id_ptr;

				if ((cob_id & 0x7FF) == (0x200U + (0x100U * (i % 4) + (i / 4)))) {
					// modify the cob_id to include the node_id
					*cob_id_ptr = cob_id + node_id;
					printk("Fixed RPDO 0x%04x: cob_id = 0x%08x\n", entry->index, *cob_id_ptr);
				}
			}
		}
#endif
#if CO_NO_TPDO > 0
		if ((entry->index >= 0x1800) && (entry->index < 0x1A00)) {
			i = entry->index - 0x1800;

			cob_id_ptr = get_cob_id_ptr(entry);
			if (cob_id_ptr) {
				cob_id = *cob_id_ptr;

				if ((cob_id & 0x7FF) == (0x180U + (0x100U * (i % 4) + (i / 4)))) {
					// modify the cob_id to include the node_id
					*cob_id_ptr = cob_id + node_id;
					printk("Fixed TPDO 0x%04x: cob_id = 0x%08x\n", entry->index, *cob_id_ptr);
				}
			}
		}
#endif
		entry++; // point at next element of the CO_OD array
	}
}

#endif
