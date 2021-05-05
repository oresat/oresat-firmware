#include <stdlib.h>
#include <string.h>
#include "test_fram.h"
#include "fram.h"
#include "chprintf.h"

/*===========================================================================*/
/* OreSat C3 FRAM                                                            */
/*===========================================================================*/
void cmd_fram(BaseSequentialStream *chp, int argc, char *argv[])
{
    if (argc < 1) {
        goto fram_usage;
    }
    if (!strcmp(argv[0], "read") && argc > 2) {
        uint16_t addr = strtoul(argv[1], NULL, 0);
        size_t len = strtoul(argv[2], NULL, 0);
        uint8_t *buf = calloc(len, sizeof(uint8_t));

        framRead(&FRAMD1, addr, buf, len);

        for (uint32_t i = 0; i < len; i++) {
            if (i % 0x10 == 0) chprintf(chp, "\r\n%04X:", i + addr);
            chprintf(chp, " %02X", buf[i]);
        }
        chprintf(chp, "\r\n");

        free(buf);
    } else if (!strcmp(argv[0], "write") && argc > 3) {
        chprintf(chp, "Unimplemented\r\n");
    } else if (!strcmp(argv[0], "erase") && argc > 2) {
        uint16_t addr = strtoul(argv[1], NULL, 0);
        size_t len = strtoul(argv[2], NULL, 0);
        framErase(&FRAMD1, addr, len);
    } else if (!strcmp(argv[0], "eraseall")) {
        framEraseAll(&FRAMD1);
    } else {
        goto fram_usage;
    }

    return;

fram_usage:
    chprintf(chp,  "Usage: fram <command>\r\n"
                   "    read <addr> <len>:\r\n"
                   "        Read <len> bytes starting at <addr>\r\n"
                   "    erase <addr> <len>:\r\n"
                   "        Erase (set to 0) <len> bytes starting at <addr>\r\n"
                   "    eraseall\r\n"
                   "        Erase (set to 0) entirety of FRAM\r\n"
                   "\r\n");
    return;
}

