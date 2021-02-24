#include <string.h>

#include "test_deploy.h"
#include "chprintf.h"
#include "deployer.h"


/*===========================================================================*/
/* Deployer Testing                                                          */
/*===========================================================================*/
void cmd_deploy(BaseSequentialStream *chp, int argc, char *argv[]) {
    bool deployed = false;

    if (argc < 1) {
        goto deploy_usage;
    }

    if (argv[0][0] == 'h') {
        chprintf(chp, "Attempting to deploy helical antenna...");
        deployed = deploy_heli();
    } else if (argv[0][0] == 't') {
        chprintf(chp, "Attempting to deploy helical antenna...");
        deployed = deploy_turn();
    } else {
        goto deploy_usage;
    }

    if (deployed) {
        chprintf(chp, "Success!\r\n");
    } else {
        chprintf(chp, "Failed!\r\n");
    }
    return;

deploy_usage:
    chprintf(chp, "Usage: deploy (h)eli|(t)urn\r\n");
    return;
}
