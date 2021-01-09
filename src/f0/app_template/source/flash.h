/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    hal_efl_lld.h
 * @brief   STM32F1xx Embedded Flash subsystem low level driver header.
 *
 * @addtogroup HAL_EFL
 * @{
 */

#define LOCATE_FUNC  __attribute__((__section__(".coderam")))


extern EFlashDriver EFLD_RAM;

void efl_lld_init_ram(void);
void efl_lld_start_ram(EFlashDriver *eflp);
void efl_lld_stop_ram(EFlashDriver *eflp);
const flash_descriptor_t *efl_lld_get_descriptor_ram(void *instance);
flash_error_t efl_lld_read_ram(void *instance, flash_offset_t offset,
                           size_t n, uint8_t *rp);
flash_error_t efl_lld_program_ram(void *instance, flash_offset_t offset,
                              size_t n, const uint8_t *pp);
flash_error_t efl_lld_start_erase_all_ram(void *instance);
flash_error_t efl_lld_start_erase_sector_ram(void *instance,
                                         flash_sector_t sector);
flash_error_t efl_lld_query_erase_ram(void *instance, uint32_t *wait_time);
flash_error_t efl_lld_verify_erase_ram(void *instance, flash_sector_t sector);

// functions copied from outside of 'hal_efl_lld.c'
void memcpy_ram(void *dest, void *src, int n);
flash_offset_t flashGetSectorOffset_ram(flash_sector_t sector);
flash_error_t flashWaitErase_ram(void);
