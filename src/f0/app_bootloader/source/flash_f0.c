#include "flash_f0.h"
#include <string.h>

size_t flashPageSizeF091(flashpage_t sector)
{
    if( sector <= FLASH_PAGE_COUNT ) {
        return(STM32F093_FLASH_PAGE_SIZE);
    }

    return 0;
}

flashaddr_t flashPageBeginF091(flashpage_t page)
{
    flashaddr_t address = FLASH_BASE;
    while (page > 0)
    {
        --page;
        address += flashPageSizeF091(page);
    }
    return address;
}

flashaddr_t flashPageEndF091(flashpage_t page)
{
    return flashPageBeginF091(page + 1);
}

flashpage_t flashPageAtF091(flashaddr_t address)
{
    flashpage_t page_number = 0;
    while (address >= flashPageEndF091(page_number))
        ++page_number;
    return page_number;
}

/**
 * @brief Wait for the flash operation to finish.
 */
#define flashWaitWhileBusy() { while (FLASH->SR & FLASH_SR_BSY) {} }

/**
 * @brief Unlock the flash memory for write access.
 * @return CH_SUCCESS  Unlock was successful.
 * @return CH_FAILED    Unlock failed.
 */
static bool_t flashUnlock(void)
{
    /* Check if unlock is really needed */
    if (!(FLASH->CR & FLASH_CR_LOCK))
        return CH_SUCCESS;

    /* Write magic unlock sequence */
    FLASH->KEYR = 0x45670123;
    FLASH->KEYR = 0xCDEF89AB;

    /* Check if unlock was successful */
    if (FLASH->CR & FLASH_CR_LOCK)
        return CH_FAILED;
    return CH_SUCCESS;
}

/**
 * @brief Lock the flash memory for write access.
 */
#define flashLock() { FLASH->CR |= FLASH_CR_LOCK; }

int flashPageEraseF091(flashpage_t page_number)
{
    /* Unlock flash for write access */
    if(flashUnlock() == CH_FAILED)
        return FLASH_RETURN_NO_PERMISSION;

    /* Wait for any busy flags. */
    flashWaitWhileBusy();

    FLASH->CR |= FLASH_CR_PER;
    //FLASH->AR = page_number;
    FLASH->AR = 0x08000000 + (page_number * STM32F093_FLASH_PAGE_SIZE);
    FLASH->CR |= FLASH_CR_STRT;

    flashWaitWhileBusy();

    if( FLASH->SR & FLASH_SR_EOP ) {
        FLASH->SR = FLASH_SR_EOP;
    }
    FLASH->CR &= ~FLASH_CR_PER;


    /* Lock flash again */
    flashLock();

    /* Check deleted sector for errors */
    if (flashIsErasedF091(flashPageBeginF091(page_number), flashPageSizeF091(page_number)) == FALSE)
        return FLASH_RETURN_BAD_FLASH;  /* Sector is not empty despite the erase cycle! */

    /* Successfully deleted sector */
    return FLASH_RETURN_SUCCESS;
}

int flashEraseF091(flashaddr_t address, size_t size)
{
    while (size > 0)
    {
        flashpage_t page = flashPageAtF091(address);
        int err = flashPageEraseF091(page);
        if (err != FLASH_RETURN_SUCCESS)
            return err;
        address = flashPageEndF091(page);
        size -= flashPageSizeF091(page);
    }

    return FLASH_RETURN_SUCCESS;
}

bool_t flashIsErasedF091(flashaddr_t address, size_t size)
{
    /* Check for default set bits in the flash memory
     * For efficiency, compare flashdata_t values as much as possible,
     * then, fallback to byte per byte comparison. */
    while (size >= sizeof(flashdata_t))
    {
        if (*(volatile flashdata_t*)address != (flashdata_t)(-1)) // flashdata_t being unsigned, -1 is 0xFF..FF
            return FALSE;
        address += sizeof(flashdata_t);
        size -= sizeof(flashdata_t);
    }
    while (size > 0)
    {
        if (*(char*)address != 0xff)
            return FALSE;
        ++address;
        --size;
    }

    return TRUE;
}

bool_t flashCompare(flashaddr_t address, const char* buffer, size_t size)
{
    /* For efficiency, compare flashdata_t values as much as possible,
     * then, fallback to byte per byte comparison. */
    while (size >= sizeof(flashdata_t))
    {
        if (*(volatile flashdata_t*)address != *(flashdata_t*)buffer)
            return FALSE;
        address += sizeof(flashdata_t);
        buffer += sizeof(flashdata_t);
        size -= sizeof(flashdata_t);
    }
    while (size > 0)
    {
        if (*(volatile char*)address != *buffer)
            return FALSE;
        ++address;
        ++buffer;
        --size;
    }

    return TRUE;
}

int flashRead2(flashaddr_t address, char* buffer, size_t size)
{
    memcpy(buffer, (char*)address, size);
    return FLASH_RETURN_SUCCESS;
}

static void flashWriteDataF091(flashaddr_t address, const flashdata_t data)
{
    /* Enter flash programming mode */
    FLASH->CR |= FLASH_CR_PG;

    /* Write the data */
    *(flashdata_t*)address = data;

    /* Wait for completion */
    flashWaitWhileBusy();

    /* Exit flash programming mode */
    FLASH->CR &= ~FLASH_CR_PG;
}

int flashWriteF091(flashaddr_t address, const uint8_t* buffer, size_t size)
{
    /* Unlock flash for write access */
    if(flashUnlock() == CH_FAILED)
        return FLASH_RETURN_NO_PERMISSION;

    /* Wait for any busy flags */
    flashWaitWhileBusy();

    /* Check if the flash address is correctly aligned */
    size_t alignOffset = address % sizeof(flashdata_t);
    if (alignOffset != 0)
    {
        /* Not aligned, thus we have to read the data in flash already present
         * and update them with buffer's data */

        /* Align the flash address correctly */
        flashaddr_t alignedFlashAddress = address - alignOffset;

        /* Read already present data */
        flashdata_t tmp = *(volatile flashdata_t*)alignedFlashAddress;

        /* Compute how much bytes one must update in the data read */
        size_t chunkSize = sizeof(flashdata_t) - alignOffset;
        if (chunkSize > size)
            chunkSize = size; // this happens when both address and address + size are not aligned

        /* Update the read data with buffer's data */
        memcpy((char*)&tmp + alignOffset, buffer, chunkSize);

        /* Write the new data in flash */
        flashWriteDataF091(alignedFlashAddress, tmp);

        /* Advance */
        address += chunkSize;
        buffer += chunkSize;
        size -= chunkSize;
    }

    /* Now, address is correctly aligned. One can copy data directly from
     * buffer's data to flash memory until the size of the data remaining to be
     * copied requires special treatment. */
    while (size >= sizeof(flashdata_t))
    {
        flashWriteDataF091(address, *(const flashdata_t*)buffer);
        address += sizeof(flashdata_t);
        buffer += sizeof(flashdata_t);
        size -= sizeof(flashdata_t);
    }

    /* Now, address is correctly aligned, but the remaining data are to
     * small to fill a entier flashdata_t. Thus, one must read data already
     * in flash and update them with buffer's data before writing an entire
     * flashdata_t to flash memory. */
    if (size > 0)
    {
        flashdata_t tmp = *(volatile flashdata_t*)address;
        memcpy(&tmp, buffer, size);
        flashWriteDataF091(address, tmp);
    }

    /* Lock flash again */
    flashLock();

    return FLASH_RETURN_SUCCESS;
}
