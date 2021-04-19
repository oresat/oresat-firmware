#include <stdlib.h>
#include <string.h>
#include "test_opd.h"
#include "opd.h"
#include "chprintf.h"

/*===========================================================================*/
/* OreSat Power Domain Control                                               */
/*===========================================================================*/
void cmd_opd(BaseSequentialStream *chp, int argc, char *argv[])
{
    static uint8_t opd_addr = 0;
    opd_status_t status = {0};

    if (argc < 1) {
        goto opd_usage;
    } else if (argc > 1) {
        opd_addr = strtoul(argv[1], NULL, 0);
        chprintf(chp, "Setting persistent board address to 0x%02X\r\n", opd_addr);
    }

    if (!strcmp(argv[0], "sysenable")) {
        chprintf(chp, "Enabling OPD subsystem\r\n");
        opd_start();
    } else if (!strcmp(argv[0], "sysdisable")) {
        chprintf(chp, "Disabling OPD subsystem\r\n");
        opd_stop();
    } else if (!strcmp(argv[0], "sysrestart")) {
        chprintf(chp, "Restarting OPD subsystem\r\n");
        opd_stop();
        opd_start();
    } else if (!strcmp(argv[0], "rescan")) {
        chprintf(chp, "Re-scanning OPD devices\r\n");
        opd_scan(false);
    } else if (!strcmp(argv[0], "summary")) {
        chprintf(chp, "Board summary:\r\n");
        for (i2caddr_t i = OPD_MIN_ADDR; i <= OPD_MAX_ADDR; i++) {
            if (!opd_status(i, &status)) {
                chprintf(chp, "0x%02X: CONNECTED - %s - %s\r\n", i,
                        (status.odr & OPD_PIN_MASK(OPD_EN) ? "ENABLED" : "DISABLED"),
                        (status.input & OPD_PIN_MASK(OPD_FAULT) ? "TRIPPED" : "NOT TRIPPED"));
            } else {
                chprintf(chp, "0x%02X: NOT CONNECTED\r\n", i);
            }
        }
    } else {
        if (opd_addr == 0) {
            chprintf(chp, "Please specify an OPD address at least once (it will persist)\r\n");
            goto opd_usage;
        }
        if (!strcmp(argv[0], "enable")) {
            chprintf(chp, "Enabling board 0x%02X: ", opd_addr);
            if (!opd_state(opd_addr, true)) {
                chprintf(chp, "ENABLED\r\n");
            } else {
                chprintf(chp, "NOT CONNECTED\r\n");
            }
        } else if (!strcmp(argv[0], "disable")) {
            chprintf(chp, "Disabling board 0x%02X: ", opd_addr);
            if (!opd_state(opd_addr, false)) {
                chprintf(chp, "DISABLED\r\n");
            } else {
                chprintf(chp, "NOT CONNECTED\r\n");
            }
        } else if (!strcmp(argv[0], "reset")) {
            chprintf(chp, "Resetting board 0x%02X: ", opd_addr);
            if (!opd_reset(opd_addr)) {
                chprintf(chp, "RESET\r\n");
            } else {
                chprintf(chp, "NOT CONNECTED\r\n");
            }
        } else if (!strcmp(argv[0], "reinit")) {
            chprintf(chp, "Attempting to reinitialize 0x%02X: ", opd_addr);
            if (opd_probe(opd_addr, true)) {
                chprintf(chp, "CONNECTED\r\n");
            } else {
                chprintf(chp, "NOT CONNECTED\r\n");
            }
        } else if (!strcmp(argv[0], "probe")) {
            chprintf(chp, "Probing board 0x%02X: ", opd_addr);
            if (opd_probe(opd_addr, false)) {
                chprintf(chp, "CONNECTED\r\n");
            } else {
                chprintf(chp, "NOT CONNECTED\r\n");
            }
        } else if (!strcmp(argv[0], "status")) {
            chprintf(chp, "Status of board 0x%02X: ", opd_addr);
            if (!opd_status(opd_addr, &status)) {
                chprintf(chp, "CONNECTED\r\n");
                chprintf(chp, "State: %s-%s\r\n",
                        (status.odr & OPD_PIN_MASK(OPD_EN) ? "ENABLED" : "DISABLED"),
                        (status.input & OPD_PIN_MASK(OPD_FAULT) ? "TRIPPED" : "NOT TRIPPED"));
                chprintf(chp, "Raw register values:\r\n");
                chprintf(chp, "Input:       %02X\r\n", status.input);
                chprintf(chp, "Output:      %02X\r\n", status.odr);
                chprintf(chp, "Polarity:    %02X\r\n", status.pol);
                chprintf(chp, "Mode:        %02X\r\n", status.mode);
                chprintf(chp, "Timeout:     %02X\r\n", status.timeout);
            } else {
                chprintf(chp, "NOT CONNECTED\r\n");
            }
        } else if (!strcmp(argv[0], "boot")) {
            int retval = opd_boot(opd_addr);
            chprintf(chp, "Boot returned 0x%02X\r\n", retval);
        } else if (!strcmp(argv[0], "linux_normal")) {
            chprintf(chp, "Linux boot normal\r\n");
            opd_linux_recover(opd_addr, false);
        } else if (!strcmp(argv[0], "linux_recover")) {
            chprintf(chp, "Linux boot recovery\r\n");
            opd_linux_recover(opd_addr, true);
        } else {
            goto opd_usage;
        }
    }

    return;

opd_usage:
    chprintf(chp, "Usage: opd <cmd> <opd_addr>\r\n"
                  "    sysenable:       Enable OPD subsystem (Power On)\r\n"
                  "    sysdisable:      Disable OPD subsystem (Power Off)\r\n"
                  "    sysrestart:      Cycle power on OPD subsystem\r\n"
                  "    rescan:          Rescans devices on OPD\r\n"
                  "    enable:          Enable an OPD attached card\r\n"
                  "    disable:         Disable an OPD attached card\r\n"
                  "    reset:           Reset the circuit breaker of a card\r\n"
                  "    reinit:          Reinitialize a device\r\n"
                  "    probe:           Probe an address to see if a card responds\r\n"
                  "    status:          Report the status of a card\r\n"
                  "    summary:         Report the status of all cards\r\n"
                  "\r\n"
                  "    boot:            Attempt to bootstrap a card via OPD\r\n"
                  "    linux_normal:    Set linux boot pin to normal\r\n"
                  "    linux_recover:   Set linux boot pin to recovery\r\n"
                  "\r\n");
    return;
}


