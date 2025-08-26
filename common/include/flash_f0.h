#ifndef FLASH_H
#define FLASH_H

#include <ch.h>
#include <hal.h>
#include <stdint.h>
#include <stdbool.h>

#define CH_SUCCESS       FALSE
#define CH_FAILED        TRUE

#define STM32F093_FLASH_PAGE_SIZE    2048

/**
 * @brief Number of sectors in the flash memory.
 */
#define FLASH_PAGE_COUNT                         127


/* Error codes */

/** @brief Flash operation successful */
#define FLASH_RETURN_SUCCESS           CH_SUCCESS

/** @brief Flash operation error because of denied access, corrupted memory.*/
#define FLASH_RETURN_NO_PERMISSION -1

/** @brief Flash operation error because of bad flash, corrupted memory */
#define FLASH_RETURN_BAD_FLASH -11

#ifdef __cplusplus
extern "C" {
#endif

//The F0 uses half-word writes
typedef uint16_t flashdata_t;
//typedef bool bool;

/**
 * @brief Maximum program/erase parallelism
 *
 * FLASH_CR_PSIZE_MASK is the mask to configure the parallelism value.
 * FLASH_CR_PSIZE_VALUE is the parallelism value suitable for the voltage range.
 *
 * PSIZE(1:0) is defined as:
 * 00 to program 8 bits per step
 * 01 to program 16 bits per step
 * 10 to program 32 bits per step
 * 11 to program 64 bits per step
 */
// Warning, flashdata_t must be unsigned!!!


/** @brief Address in the flash memory */
typedef uintptr_t flashaddr_t;

/** @brief Index of a page */
typedef uint8_t flashpage_t;

/**
 * @brief Get the size of @p sector.
 * @return @p sector size in bytes.
 */
size_t flashPageSizeF091(flashpage_t page);

/**
 * @brief Get the beginning address of @p sector.
 * @param sector Sector to retrieve the beginning address of.
 * @return First address (inclusive) of @p sector.
 */
flashaddr_t flashPageBeginF091(flashpage_t page);

/**
 * @brief Get the end address of @p sector.
 * @param sector Sector to retrieve the end address of.
 * @return End address (exclusive) of @p sector (i.e. beginning address of the next sector).
 */
flashaddr_t flashPageEndF091(flashpage_t page);

/**
 * @brief Get the sector containing @p address.
 * @warning @p address must be in the flash addresses range.
 * @param address Address to be searched for.
 * @return Sector containing @p address.
 */
flashpage_t flashPageAtF091(flashaddr_t address);

/**
 * @brief Erase the flash @p sector.
 * @details The sector is checked for errors after erase.
 * @note The sector is deleted regardless of its current state.
 *
 * @param sector Sector which is going to be erased.
 * @return FLASH_RETURN_SUCCESS         No error erasing the sector.
 * @return FLASH_RETURN_BAD_FLASH       Flash cell error.
 * @return FLASH_RETURN_NO_PERMISSION   Access denied.
 */
int flashPageEraseF091(flashpage_t page);

/**
 * @brief Erase the sectors containing the span of @p size bytes starting at @p address.
 *
 * @warning If @p address doesn't match the beginning of a sector, the
 * data contained between the beginning of the sector and @p address will
 * be erased too. The same applies for data contained at @p address + @p size
 * up to the end of the sector.
 *
 * @param address Starting address of the span in flash memory.
 * @param size Size of the span in bytes.
 * @return FLASH_RETURN_SUCCESS         No error erasing the flash memory.
 * @return FLASH_RETURN_BAD_FLASH       Flash cell error.
 * @return FLASH_RETURN_NO_PERMISSION   Access denied.
 */
int flashEraseF091(flashaddr_t address, size_t size);

/**
 * @brief Check if the @p size bytes of flash memory starting at @p address are erased.
 * @note If the memory is erased, one can write data into it safely.
 * @param address First address in flash memory to be checked.
 * @param size Size of the memory space to be checked in bytes.
 * @return TRUE Memory is already erased.
 * @return FALSE Memory is not erased.
 */
bool flashIsErasedF091(flashaddr_t address, size_t size);

/**
 * @brief Check if the data in @p buffer are identical to the one in flash memory.
 * @param address First address in flash memory to be checked.
 * @param buffer Buffer containing the data to compare.
 * @param size Size of @p buffer in bytes.
 * @return TRUE if the flash memory and the buffer contain identical data.
 * @return FALSE if the flash memory and the buffer don't contain identical data.
 */
bool flashCompare(flashaddr_t address, const char* buffer, size_t size);

/**
 * @brief Copy data from the flash memory to a @p buffer.
 * @warning The @p buffer must be at least @p size bytes long.
 * @param address First address of the flash memory to be copied.
 * @param buffer Buffer to copy to.
 * @param size Size of the data to be copied in bytes.
 * @return FLASH_RETURN_SUCCESS if successfully copied.
 */
int flashRead2(flashaddr_t address, char* buffer, size_t size);

/**
 * @brief Copy data from a @p buffer to the flash memory.
 * @warning The flash memory area receiving the data must be erased.
 * @warning The @p buffer must be at least @p size bytes long.
 * @param address First address in the flash memory where to copy the data to.
 * @param buffer Buffer containing the data to copy.
 * @param size Size of the data to be copied in bytes.
 * @return FLASH_RETURN_SUCCESS         No error.
 * @return FLASH_RETURN_NO_PERMISSION   Access denied.
 */
int flashWriteF091(flashaddr_t address, const uint8_t* buffer, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* FLASH_H */
