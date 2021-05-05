#include <stdlib.h>
#include <string.h>

#include "test_deploy.h"
#include "chprintf.h"
#include "deployer.h"


/*===========================================================================*/
/* Deployer Testing                                                          */
/*===========================================================================*/
void cmd_deploy(BaseSequentialStream *chp, int argc, char *argv[]) {
    if (argc < 2) {
        goto deploy_usage;
    }

    uint32_t duration = strtoul(argv[1], NULL, 0);

    if (argv[0][0] == 'h') {
        chprintf(chp, "Attempting to deploy helical antenna...");
        deploy_heli(duration);
    } else if (argv[0][0] == 't') {
        chprintf(chp, "Attempting to deploy turnstile antenna...");
        deploy_turn(duration);
    } else {
        goto deploy_usage;
    }

    chprintf(chp, "Done!\r\n");

    return;

deploy_usage:
    chprintf(chp, "Usage: deploy (h)eli|(t)urn <duration>\r\n");
    return;
}
