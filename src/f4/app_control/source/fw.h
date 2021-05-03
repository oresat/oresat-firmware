#ifndef _FW_H_
#define _FW_H_

#include "ch.h"
#include "hal.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    BANK_0 = 0,
    BANK_1 = 1
} fw_bank_t;

typedef struct {
    uint32_t crc;
    size_t len;
} fw_info_t;

int fw_read(EFlashDriver *eflp, char *filename, flash_offset_t offset, size_t len);
int fw_write(EFlashDriver *eflp, char *filename, flash_offset_t offset);
uint32_t fw_crc(EFlashDriver *eflp, fw_bank_t bank, size_t len);
uint32_t fw_verify(EFlashDriver *eflp, fw_bank_t bank);
void fw_set_info(fw_info_t fw_info, fw_bank_t bank);
int fw_flash(EFlashDriver *eflp, char *filename, uint32_t expected_crc);
int fw_set_bank(EFlashDriver *eflp, fw_bank_t bank);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
