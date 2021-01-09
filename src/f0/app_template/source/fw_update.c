#include "fw_update.h"

// pointers to sections
extern unsigned int __flash1_base__;
extern unsigned int __flash1_end__;
unsigned int flash1_base = (unsigned int)&__flash1_base__;
unsigned int flash1_end = (unsigned int)&__flash1_end__;
extern unsigned int __flash0_base__;
extern unsigned int __flash0_end__;
unsigned int flash0_base = (unsigned int)&__flash0_base__;
unsigned int flash0_end = (unsigned int)&__flash0_end__;

extern unsigned int __coderam_base__;
extern unsigned int __coderam_init__;
extern unsigned int __coderam_end__;
extern unsigned int __coderam_size__;
unsigned int* coderam_base = (unsigned int*)&__coderam_base__;
unsigned int* coderam_init = (unsigned int*)&__coderam_init__;
unsigned int* coderam_end = (unsigned int*)&__coderam_end__;
unsigned int coderam_size = (unsigned int)&__coderam_size__;
fw_header header;

BaseSequentialStream *s = (BaseSequentialStream *)&SD2;
SerialDriver *ser = (SerialDriver *)&SD2;
BaseFlash *efl = (BaseFlash *)&EFLD1;

// FW update thread
THD_WORKING_AREA(fw_update_wa, 0x4000);
THD_FUNCTION(fw_update, arg)
{
    (void)arg;

    palSetLineMode(LINE_LED, PAL_MODE_OUTPUT_PUSHPULL);

    while (1)
    {
        int err = readFWImage();
        if (err != SUCCESS)
            chprintf(s, "FW image download returned error code: %d\n", err);
        else
            chprintf(s, "download FW image suceeded!\n");

        chprintf(s, "starting update process!\n\r");
        doFWUpdate();
    }

    palClearLine(LINE_LED);
    chThdExit(MSG_OK);
}

int readFWImage() 
{
    unsigned int flash1_base_offset = flash1_base - FLASH_BASE;
    unsigned int image_base_offset = flash1_base_offset;
    uint8_t buf[BUF_SIZE];
    int n;
    int recv_size;
    int err;
    unsigned int crc_read;

    chprintf(s, "waiting for FW update header\n\r");
    // wait for FW update header forever
    n = sdReadTimeout(ser, (uint8_t *)&header, sizeof(fw_header), TIME_INFINITE);
    if (n != sizeof(fw_header))
    {
        chprintf(s, "READ ERR: read %d bytes\n", n);
        return ERR_HEADER_READ;
    }

    chprintf(s, "FW Header: [CRC:0x%x; SIZE:%d; FLAGS:0x%x]\n",
            header.crc, header.size, header.flags);

    chprintf(s, "reading program section\n", n);
    for (recv_size = 0; recv_size < header.size;)
    {
        // default to reading BUF_SIZE bytes
        int read_len = BUF_SIZE;

        // if there are less that BUF_SIZE bytes left, only read the remaining bytes
        if ((header.size - recv_size) < (int)BUF_SIZE)
            read_len = header.size - recv_size;

        // zero the buffer
        memset(buf, 0, BUF_SIZE);

        // read from serial into buffer
        n = sdReadTimeout(ser, buf, read_len, TIME_MS2I(500));
        if (n < read_len)
        {
            chprintf(s, "ERROR: expected %d but for %d\n", read_len, n);
            return ERR_SERIAL_READ;
        }

        recv_size += n;

        // TODO check error here
        // erase the page we are about to write
        int sector = OFFSET_2_FLASH_SECTOR(image_base_offset);
        flashStartEraseSector(efl, sector);
        flashWaitErase(efl);

        // write the page
        err = flashProgram(efl, image_base_offset, sizeof(buf), (uint8_t *)buf);
        if(err != FLASH_NO_ERROR)
        {
            chprintf(s, "flashProgram returned error code: %d\n", err);
            return err;
        }

        image_base_offset += BUF_SIZE;
    }

    chprintf(s, "received image size: %d\n", recv_size);

    // check that the received size matches the header size
    if (recv_size != header.size)
    {
        chprintf(s, "received image size (%d) does not match expected (%d)\n", recv_size, header.size);
        return ERR_READ_SIZE;
    }

    n = 0;

    // initialize the CRC unit for a new, ongoing calculation
    crcInit();

    chprintf(s, "validating new FW image...\n", n);

    // read back the FW image and calculate the CRC
    for (unsigned int offset = flash1_base_offset; offset < flash1_base_offset + header.size; offset += sizeof(buf))
    {
        // default to reading BUF_SIZE bytes
        int read_len = BUF_SIZE;

        // if there are less that BUF_SIZE bytes left in the image, get the correct read length
        if (((flash1_base_offset + header.size) - offset) < BUF_SIZE)
            read_len = (flash1_base_offset + header.size) - offset;

        // TODO check error
        // read the bytes from flash
        flashRead(efl, offset, read_len, (uint8_t *)buf);

        // CRC the bytes we read
        crc_read = crc32_ongoing(buf, read_len);

        n += read_len;
    }

    // disable CRC unit
    //crcDisable();

    // check read size
    if (n != header.size)
    {
        chprintf(s, "read len (%d) does not match expected (%d)\n", n, header.size);
        return ERR_REREAD_SIZE;
    }

    // check CRC of read FW image
    if (crc_read != header.crc)
    {
        chprintf(s, "read CRC (%u) does not match expected (%u)\n", crc_read, header.crc);
        return ERR_FW_CRC_INVAL;
    }

    chprintf(s, "FW download suceeded!\n");
    return SUCCESS;
}

int doFWUpdate()
{
    chprintf(s, "BASE: 0x%08x\r\n", coderam_base);
    chprintf(s, "INIT: 0x%08x\r\n", coderam_init);
    chprintf(s, "END: 0x%08x\r\n", coderam_end);
    chprintf(s, "SIZE: 0x%08x\r\n", coderam_size);

    // init the ram function memory region
    memcpy(coderam_base, coderam_init, coderam_size);

    for(int i = 0; i < 5 ; i++) {
        palSetLine(LINE_LED);
        chThdSleepMilliseconds(100);
        palClearLine(LINE_LED);
        chThdSleepMilliseconds(100);
    }

    return __doFWUpdate();
}


// TODO what to do with returned error codes?
int LOCATE_FUNC __doFWUpdate()
{
    unsigned int flash0_base_offset = flash0_base - FLASH_BASE;
    unsigned int flash1_base_offset = flash1_base - FLASH_BASE;
    uint8_t buf[BUF_SIZE];

    chSysLock();
    int count = 10;

    for (unsigned int i = 0; i < header.size; i += BUF_SIZE)
    {
        //chprintf(s, "flash0[%d] 0x%08x\r\n", i, flash0_base_offset);
        //chprintf(s, "flash0 sector %d\r\n", OFFSET_2_FLASH_SECTOR(flash0_base_offset));
        //chprintf(s, "flash1[%d] 0x%08x\r\n\r\n", i, flash1_base_offset);

        // zero the buffer
        //memset(buf, 0, BUF_SIZE); //TODO ram func here?
        // read from flash1 into buf
        efl_lld_read_ram(efl, flash1_base_offset, BUF_SIZE, (uint8_t *)buf);

        // erase the flash0 page we are about to write
        int sector = OFFSET_2_FLASH_SECTOR(flash0_base_offset);
        //flashStartEraseSector(efl, sector);
        efl_lld_start_erase_sector_ram(efl, sector);

        flashWaitErase_ram();
// TODO increase wait time!
        // write the page
       int err = efl_lld_program_ram(efl, flash0_base_offset, BUF_SIZE, (uint8_t *)buf);
       if(err != FLASH_NO_ERROR) {
          count = err;
       }

        flash0_base_offset += BUF_SIZE;
        flash1_base_offset += BUF_SIZE;
    }

    for(int i = 0; i < count ; i++) {
        palSetLine(LINE_LED);
        for(int i = 0; i < 1<<20; i++);
        palClearLine(LINE_LED);
        for(int i = 0; i < 1<<20; i++);
    }


    chSysUnlock();
    chSysHalt("fw_update");
    while(1);
}

/*
   int LOCATE_FUNC __doFWUpdate()
   {
   unsigned int flash1_base_offset = flash1_base - FLASH_BASE;
   unsigned int flash0_base_offset = flash0_base - FLASH_BASE;
   unsigned int flash1_end_offset = flash1_end - FLASH_BASE;
   unsigned int image_base_offset = flash1_base_offset;
   uint8_t buf[BUF_SIZE], vectors[BUF_SIZE];
   int n;
   int recv_size;
   int err;
   fw_header header;
   unsigned int crc_read;

   chprintf(s, "waiting for FW update header\n");
// wait for FW update header forever
n = sdReadTimeout(ser, (uint8_t *)&header, sizeof(fw_header), TIME_INFINITE);
if (n != sizeof(fw_header))
{
chprintf(s, "READ ERR: read %d bytes\n", n);
return ERR_HEADER_READ;
}

chprintf(s, "FW Header: [PROG CRC:0x%x; VECT CRC:0x%x; PROG SIZE:%d; VECT SIZE:%d; FLAGS:0x%x; HEADER_CRC:0x%x]\n",
header.prog_crc, header.vectors_crc, header.prog_size, header.vectors_size, header.flags, header.header_crc);

// calculate the header crc by crcing the bytes of the header minus the header crc.
// check it against expected
unsigned int calc_header_crc = crc32_single((uint8_t *)&header, sizeof(fw_header) - sizeof(unsigned int));
if (calc_header_crc != header.header_crc)
{
chprintf(s, "calculated header crc (%u) does match header crc (%u)\n", calc_header_crc, header.header_crc);
return ERR_HEADER_CRC_INVAL;
}

chprintf(s, "reading vectors section\n");

// zero the vectors buffer
memset(vectors, 0, VECTOR_SECTION_SIZE);

// read vectors section from serial into buffer
n = sdReadTimeout(ser, vectors, VECTOR_SECTION_SIZE, TIME_MS2I(500));
if (n < (int)VECTOR_SECTION_SIZE)
{
chprintf(s, "error reading vector section, expected %d but for %d\n", VECTOR_SECTION_SIZE, n);
return ERR_SERIAL_READ;
}

// calculate the vectors section crc
unsigned int vectors_crc = crc32_single(vectors, sizeof(vectors));
if (vectors_crc != header.vectors_crc)
{
chprintf(s, "calculated vectors crc (%u) does match vectors crc (%u)\n", vectors_crc, header.vectors_crc);
return ERR_FW_CRC_INVAL;
}

chprintf(s, "reading program section\n", n);
for (recv_size = 0; recv_size < header.prog_size;)
{
// default to reading BUF_SIZE bytes
int read_len = BUF_SIZE;

// if there are less that BUF_SIZE bytes left, only read the remaining bytes
if ((header.prog_size - recv_size) < (int)BUF_SIZE)
read_len = header.prog_size - recv_size;

// zero the buffer
memset(buf, 0, BUF_SIZE);

// read from serial into buffer
n = sdReadTimeout(ser, buf, read_len, TIME_MS2I(500));
if (n < read_len)
{
    chprintf(s, "ERROR: expected %d but for %d\n", read_len, n);
    return ERR_SERIAL_READ;
}

recv_size += n;

// TODO check error here
// erase the page we are about to write
int sector = OFFSET_2_FLASH_SECTOR(image_base_offset);
flashStartEraseSector(efl, sector);
flashWaitErase(efl);

// write the page
err = flashProgram(efl, image_base_offset, sizeof(buf), (uint8_t *)buf);
if(err != FLASH_NO_ERROR)
{
    chprintf(s, "flashProgram returned error code: %d\n", err);
    return err;
}


image_base_offset += BUF_SIZE;
}

chprintf(s, "received image size: %d\n", recv_size);

// check that the received size matches the header size
if (recv_size != header.prog_size)
{
    chprintf(s, "received image size (%d) does not match expected (%d)\n", recv_size, header.prog_size);
    return ERR_READ_SIZE;
}

n = 0;

// initialize the CRC unit for a new, ongoing calculation
crcInit();

chprintf(s, "validating new FW image...\n", n);

// read back the FW image and calculate the CRC
for (unsigned int offset = flash1_base_offset; offset < flash1_base_offset + header.prog_size; offset += sizeof(buf))
{
    // default to reading BUF_SIZE bytes
    int read_len = BUF_SIZE;

    // if there are less that BUF_SIZE bytes left in the image, get the correct read length
    if (((flash1_base_offset + header.prog_size) - offset) < BUF_SIZE)
        read_len = (flash1_base_offset + header.prog_size) - offset;

    // TODO check error
    // read the bytes from flash
    flashRead(efl, offset, read_len, (uint8_t *)buf);

    // CRC the bytes we read
    crc_read = crc32_ongoing(buf, read_len);

    n += read_len;
}

// disable CRC unit
//crcDisable();

// check read size
if (n != header.prog_size)
{
    chprintf(s, "read len (%d) does not match expected (%d)\n", n, header.prog_size);
    return ERR_REREAD_SIZE;
}

// check CRC of read FW image
if (crc_read != header.prog_crc)
{
    chprintf(s, "read CRC (%u) does not match expected (%u)\n", crc_read, header.prog_crc);
    return ERR_FW_CRC_INVAL;
}

chprintf(s, "doFWUpdate suceeded!\n");

int delay = 1<<20;
int count = 4;

// wait for uart buffer to clear
chThdSleepMilliseconds(100);

// disable interrupts
chSysLock();
int sector = OFFSET_2_FLASH_SECTOR(0);
flashStartEraseSector(efl, sector);
int wait = 0;
efl_lld_query_erase(efl, &wait);

// can't call flashWaitErase() because it calls sleep
for(volatile int i = 0; i < 1<<23; i++);
//chSysUnlock();
err = flashProgram(efl, 0, VECTOR_SECTION_SIZE, (uint8_t *)vectors);
//chprintf(s, "RAW ERR: 0x%08x\n", ((EFlashDriver*)&EFLD1)->flash->SR);
if(err != FLASH_NO_ERROR)
{
    count = err;
    //chprintf(s, "flashProgram vectors returned error code: %d\n", err);
    //chSysUnlock();
    //return err;
}

// TODO check error
// read the bytes from flash
//flashRead(efl, 0, VECTOR_SECTION_SIZE, (uint8_t *)buf);

// CRC the bytes we read
//crc_read = crc32_single(buf, VECTOR_SECTION_SIZE);
//chprintf(s, "vectors CRC: 0x%x\n", crc_read);

// enable interrupts
//chSysUnlock();
//chprintf(s, "finished!\n");
//chprintf(s, "vectors CRC: 0x%x\n", crc_read);

for(int i = 0; i < count; i++)
{
    palSetLine(LINE_LED);
    for(volatile int j = 0; j < delay; j++);
    palClearLine(LINE_LED);
    for(volatile int j = 0; j < delay; j++);
}
chSysUnlock();
chSysHalt("fw_update");

return SUCCESS;
}
*/
