#include <stdlib.h>
#include <string.h>
#include "test_bootloader.h"
#include "can_bootloader.h"
#include "chprintf.h"

/*===========================================================================*/
/* Time                                                                      */
/*===========================================================================*/
void cmd_bootloader(BaseSequentialStream *chp, int argc, char *argv[])
{

    if (argc < 1) {
        goto bootloader_usage;
    }
    if (!strcmp(argv[0], "cmd1")) {
    } else if (!strcmp(argv[0], "cmd2")) {
    } else {
        goto bootloader_usage;
    }

    return;

bootloader_usage:
    chprintf(chp, "Usage: bootloader <cmd>\r\n"
                  "    cmd1: <options>\r\n"
                  "        Does blah\r\n"
                  "    cmd2: <options>\r\n"
                  "        Does other blah\r\n"
                  "\r\n");
    return;
}
