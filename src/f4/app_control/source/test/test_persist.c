#include <stdlib.h>
#include <string.h>
#include "CANopen.h"
#include "OD.h"
#include "test_persist.h"
#include "persist.h"
#include "chprintf.h"

/*===========================================================================*/
/* OreSat C3 Persistent Storage                                              */
/*===========================================================================*/
void cmd_persist(BaseSequentialStream *chp, int argc, char *argv[])
{
    void *group = NULL;
    if (argc < 3) {
        goto persist_usage;
    }
    if (!strcmp(argv[1], "keys")) {
        group = &OD_PERSIST_KEYS;
    } else if (!strcmp(argv[1], "state")) {
        group = &OD_PERSIST_STATE;
    } else if (!strcmp(argv[1], "comm")) {
        group = &OD_PERSIST_COMM;
    } else if (!strcmp(argv[1], "mfr")) {
        group = &OD_PERSIST_MFR;
    } else if (!strcmp(argv[1], "app")) {
        group = &OD_PERSIST_APP;
    } else {
        goto persist_usage;
    }
    if (!strcmp(argv[0], "store")) {
        storeGroup(group);
    } else if (!strcmp(argv[0], "restore")) {
        restoreGroup(group);
    } else if (!strcmp(argv[0], "reset")) {
        resetGroup(group);
    } else {
        goto persist_usage;
    }

    return;

persist_usage:
    chprintf(chp,  "Usage: persist <command> <group>\r\n"
                   "  Commands:\r\n"
                   "    store:\r\n"
                   "        Store OD <group> to FRAM\r\n"
                   "    restore:\r\n"
                   "        Restore OD <group> from FRAM\r\n"
                   "    reset\r\n"
                   "        Reset OD <group> in FRAM\r\n"
                   "  Groups:\r\n"
                   "    keys\r\n"
                   "    state\r\n"
                   "    comm\r\n"
                   "    mfr\r\n"
                   "    app\r\n"
                   "\r\n");
    return;
}
