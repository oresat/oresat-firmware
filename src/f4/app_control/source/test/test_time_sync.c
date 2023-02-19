#include <stdlib.h>
#include <string.h>
#include "CO_master.h"
#include "test_time_sync.h"
#include "chprintf.h"

extern CO_t *CO;

/*===========================================================================*/
/* Send Time Sync TPDO                                                       */
/*===========================================================================*/
void cmd_time_sync(BaseSequentialStream *chp, int argc, char *argv[])
{
    (void)argv;

    if (argc != 0) {
        goto sync_usage;
    }

    CO_TPDOsendRequest(&CO->TPDO[0]);
    chprintf(chp, "Sent!\r\n");
    return;

sync_usage:
    chprintf(chp, "Usage: timesync\r\n");
    return;
}
