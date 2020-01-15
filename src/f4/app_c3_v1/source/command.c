#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "CO_master.h"
#include "opd.h"
#include "max7310.h"
#include "mmc.h"
#include "chprintf.h"
#include "shell.h"

#ifndef BUF_SIZE
#define BUF_SIZE 0x10000 /* 64k */
#endif

typedef struct {
    uint32_t code;
    char *desc;
} errorstr_t;

static const errorstr_t errors[] = {
        {0x05030000, "Toggle bit not altered."},
        {0x05040000, "SDO protocol timed out."},
        {0x05040001, "Command specifier not valid or unknown."},
        {0x05040002, "Invalid block size in block mode."},
        {0x05040003, "Invalid sequence number in block mode."},
        {0x05040004, "CRC error (block mode only)."},
        {0x05040005, "Out of memory."},
        {0x06010000, "Unsupported access to an object."},
        {0x06010001, "Attempt to read a write only object."},
        {0x06010002, "Attempt to write a read only object."},
        {0x06020000, "Object does not exist."},
        {0x06040041, "Object cannot be mapped to the PDO."},
        {0x06040042, "Number and length of object to be mapped exceeds PDO length."},
        {0x06040043, "General parameter incompatibility reasons."},
        {0x06040047, "General internal incompatibility in device."},
        {0x06060000, "Access failed due to hardware error."},
        {0x06070010, "Data type does not match, length of service parameter does not match."},
        {0x06070012, "Data type does not match, length of service parameter too high."},
        {0x06070013, "Data type does not match, length of service parameter too short."},
        {0x06090011, "Sub index does not exist."},
        {0x06090030, "Invalid value for parameter (download only)."},
        {0x06090031, "Value range of parameter written too high."},
        {0x06090032, "Value range of parameter written too low."},
        {0x06090036, "Maximum value is less than minimum value."},
        {0x060A0023, "Resource not available: SDO connection."},
        {0x08000000, "General error."},
        {0x08000020, "Data cannot be transferred or stored to application."},
        {0x08000021, "Data cannot be transferred or stored to application because of local control."},
        {0x08000022, "Data cannot be transferred or stored to application because of present device state."},
        {0x08000023, "Object dictionary not present or dynamic generation fails."},
        {0x08000024, "No data available."},
        {0x00000000, "Unknown error."}
};

static uint8_t data[BUF_SIZE];

/*===========================================================================*/
/* CAN Network Management                                                    */
/*===========================================================================*/
void nmt_usage(BaseSequentialStream *chp)
{
    chprintf(chp, "Usage: nmt start|stop|preop|resetcomm|resetnode <NodeID>\r\n");
}

void cmd_nmt(BaseSequentialStream *chp, int argc, char *argv[])
{
    uint8_t node_id = 0;
    if (argc < 2) {
        nmt_usage(chp);
        return;
    }
    node_id = strtoul(argv[1], NULL, 0);

    if (!strcmp(argv[0], "start")) {
        CO_sendNMTcommand(CO, CO_NMT_ENTER_OPERATIONAL, node_id);
    } else if (!strcmp(argv[0], "stop")) {
        CO_sendNMTcommand(CO, CO_NMT_ENTER_STOPPED, node_id);
    } else if (!strcmp(argv[0], "preop")) {
        CO_sendNMTcommand(CO, CO_NMT_ENTER_PRE_OPERATIONAL, node_id);
    } else if (!strcmp(argv[0], "resetcomm")) {
        CO_sendNMTcommand(CO, CO_NMT_RESET_COMMUNICATION, node_id);
    } else if (!strcmp(argv[0], "resetnode")) {
        CO_sendNMTcommand(CO, CO_NMT_RESET_NODE, node_id);
    } else {
        chprintf(chp, "Invalid command: %s\r\n", argv[0]);
        nmt_usage(chp);
        return;
    }
}

/*===========================================================================*/
/* CAN SDO Master                                                            */
/*===========================================================================*/
void sdo_usage(BaseSequentialStream *chp)
{
    chprintf(chp, "Usage: sdo read|write <NodeID> <index> <subindex> [blockmode]\r\n");
}

void cmd_sdo(BaseSequentialStream *chp, int argc, char *argv[])
{
    uint32_t data_len = 0;
    uint32_t abrt_code = 0;
    uint8_t node_id = 0;
    uint16_t index = 0;
    uint8_t subindex = 0;
    bool block = false;

    if (argc < 4) {
        sdo_usage(chp);
        return;
    }

    node_id = strtoul(argv[1], NULL, 0);
    index = strtoul(argv[2], NULL, 0);
    subindex = strtoul(argv[3], NULL, 0);
    if (argc == 5)
        block = !strcmp(argv[4], "true");

    if (!strcmp(argv[0], "read")) {
        sdo_upload(CO->SDOclient[0], node_id, index, subindex, data, sizeof(data), &data_len, &abrt_code, 1000, block);
        if (abrt_code == CO_SDO_AB_NONE) {
            chprintf(chp, "Received %u bytes of data.\r\n", data_len);
        } else {
            const errorstr_t *err;
            for (err = &errors[0]; err->code != 0 && err->code != abrt_code; err++);
            chprintf(chp, "Received abort code: (%08X) %s\r\n", abrt_code, err->desc);
        }
    } else if (!strcmp(argv[0], "write")) {
        chprintf(chp, "Disabled for now\r\n");
        /*sdo_download(CO->SDOclient[0], node_id, index, subindex, data, data_len, &abrt_code, 1000, block);*/
    } else {
        sdo_usage(chp);
        return;
    }
}

/*===========================================================================*/
/* OreSat Power Domain Control                                               */
/*===========================================================================*/
void opd_usage(BaseSequentialStream *chp)
{
    chprintf(chp, "Usage: opd sysenable|sysdisable|sysrestart|enable|disable|reset|probe|status <opd_addr>\r\n");
}

void cmd_opd(BaseSequentialStream *chp, int argc, char *argv[])
{
    static opd_addr_t opd_addr = 0;
    opd_status_t status = {0};

    if (argc < 1) {
        opd_usage(chp);
        return;
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
    } else {
        if (opd_addr == 0) {
            chprintf(chp, "Please specify an OPD address at least once (it will persist)\r\n");
            opd_usage(chp);
            return;
        }
        if (!strcmp(argv[0], "enable")) {
            chprintf(chp, "Enabling board 0x%02X: ", opd_addr);
            if (!opd_enable(opd_addr)) {
                chprintf(chp, "ENABLED\r\n");
            } else {
                chprintf(chp, "NOT CONNECTED\r\n");
            }
        } else if (!strcmp(argv[0], "disable")) {
            chprintf(chp, "Disabling board 0x%02X: ", opd_addr);
            if (!opd_disable(opd_addr)) {
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
        } else if (!strcmp(argv[0], "probe")) {
            chprintf(chp, "Probing board 0x%02X: ", opd_addr);
            if (opd_probe(opd_addr)) {
                chprintf(chp, "CONNECTED\r\n");
            } else {
                chprintf(chp, "NOT CONNECTED\r\n");
            }
        }  else if (!strcmp(argv[0], "status")) {
            chprintf(chp, "Status of board 0x%02X: ", opd_addr);
            if (!opd_status(opd_addr, &status)) {
                chprintf(chp, "CONNECTED\r\n");
                chprintf(chp, "State: %s-%s\r\n",
                        (status.odr & MAX7310_PIN_MASK(OPD_EN) ? "ENABLED" : "DISABLED"),
                        (status.input & MAX7310_PIN_MASK(OPD_FAULT) ? "TRIPPED" : "NOT TRIPPED"));
                chprintf(chp, "Raw register values:\r\n");
                chprintf(chp, "Input:       %02X\r\n", status.input);
                chprintf(chp, "Output:      %02X\r\n", status.odr);
                chprintf(chp, "Polarity:    %02X\r\n", status.pol);
                chprintf(chp, "Mode:        %02X\r\n", status.mode);
                chprintf(chp, "Timeout:     %02X\r\n", status.timeout);
            } else {
                chprintf(chp, "NOT CONNECTED\r\n");
            }
        } else {
            opd_usage(chp);
            return;
        }
    }
}

/*===========================================================================*/
/* Shell                                                                     */
/*===========================================================================*/
static const ShellCommand commands[] = {
    {"nmt", cmd_nmt},
    {"sdo", cmd_sdo},
    {"opd", cmd_opd},
    {"mmc", cmd_mmc},
    {NULL, NULL}
};

static char histbuf[SHELL_MAX_HIST_BUFF];

static const ShellConfig shell_cfg = {
    (BaseSequentialStream *)&SD2,
    commands,
    histbuf,
    sizeof(histbuf),
};

THD_WORKING_AREA(shell_wa, 0x200);
THD_WORKING_AREA(cmd_wa, 0x200);
THD_FUNCTION(cmd, arg)
{
    (void)arg;

    while (!chThdShouldTerminateX()) {
        thread_t *shell_tp = chThdCreateStatic(shell_wa, sizeof(shell_wa), NORMALPRIO, shellThread, (void *)&shell_cfg);
        chThdWait(shell_tp);
        chThdSleepMilliseconds(500);
    }

    chThdExit(MSG_OK);
}
