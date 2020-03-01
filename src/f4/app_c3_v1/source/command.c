#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "CO_master.h"
#include "opd.h"
#include "time_sync.h"
#include "max7310.h"
#include "mmc.h"
#include "chprintf.h"
#include "shell.h"

#ifndef BUF_SIZE
#define BUF_SIZE 0x10000 /* 64k */
#endif

typedef struct {
    uint16_t code;
    char *desc;
} em_codestr_t;

typedef struct {
    uint8_t bits;
    char *desc;
} em_bitstr_t;

typedef struct {
    uint32_t code;
    char *desc;
} sdo_errstr_t;

static const em_codestr_t em_codes[] = {
    {0x0000U, "Error Reset or No Error"},
    {0x1000U, "Generic Error"},
    {0x2000U, "Current"},
    {0x2100U, "Current, device input side"},
    {0x2200U, "Current inside the device"},
    {0x2300U, "Current, device output side"},
    {0x3000U, "Voltage"},
    {0x3100U, "Mains Voltage"},
    {0x3200U, "Voltage inside the device"},
    {0x3300U, "Output Voltage"},
    {0x4000U, "Temperature"},
    {0x4100U, "Ambient Temperature"},
    {0x4200U, "Device Temperature"},
    {0x5000U, "Device Hardware"},
    {0x6000U, "Device Software"},
    {0x6100U, "Internal Software"},
    {0x6200U, "User Software"},
    {0x6300U, "Data Set"},
    {0x7000U, "Additional Modules"},
    {0x8000U, "Monitoring"},
    {0x8100U, "Communication"},
    {0x8110U, "CAN Overrun (Objects lost)"},
    {0x8120U, "CAN in Error Passive Mode"},
    {0x8130U, "Life Guard Error or Heartbeat Error"},
    {0x8140U, "recovered from bus off"},
    {0x8150U, "CAN-ID collision"},
    {0x8200U, "Protocol Error"},
    {0x8210U, "PDO not processed due to length error"},
    {0x8220U, "PDO length exceeded"},
    {0x8230U, "DAM MPDO not processed, destination object not available"},
    {0x8240U, "Unexpected SYNC data length"},
    {0x8250U, "RPDO timeout"},
    {0x9000U, "External Error"},
    {0xF000U, "Additional Functions"},
    {0xFF00U, "Device specific"},
    {0xFFFFU, "Unknown error"} /* TODO: Better termination */
};

static const em_bitstr_t em_bits[] = {
    {0x00U, "Error Reset or No Error"},
    {0x01U, "communication, info, CAN bus warning limit reached"},
    {0x02U, "communication, info, Wrong data length of the received CAN message"},
    {0x03U, "communication, info, Previous received CAN message wasn't processed yet"},
    {0x04U, "communication, info, Wrong data length of received PDO"},
    {0x05U, "communication, info, Previous received PDO wasn't processed yet"},
    {0x06U, "communication, info, CAN receive bus is passive"},
    {0x07U, "communication, info, CAN transmit bus is passive"},
    {0x08U, "communication, info, Wrong NMT command received"},
    {0x12U, "communication, critical, CAN transmit bus is off"},
    {0x13U, "communication, critical, CAN module receive buffer has overflowed"},
    {0x14U, "communication, critical, CAN transmit buffer has overflowed"},
    {0x15U, "communication, critical, TPDO is outside SYNC window"},
    {0x18U, "communication, critical, SYNC message timeout"},
    {0x19U, "communication, critical, Unexpected SYNC data length"},
    {0x1AU, "communication, critical, Error with PDO mapping"},
    {0x1BU, "communication, critical, Heartbeat consumer timeout"},
    {0x1CU, "communication, critical, Heartbeat consumer detected remote node reset"},
    {0x20U, "generic, info, Emergency buffer is full, Emergency message wasn't sent"},
    {0x22U, "generic, info, Microcontroller has just started"},
    {0x28U, "generic, critical, Wrong parameters to CO_errorReport() function"},
    {0x29U, "generic, critical, Timer task has overflowed"},
    {0x2AU, "generic, critical, Unable to allocate memory for objects"},
    {0x2BU, "generic, critical, Generic error, test usage"},
    {0x2CU, "generic, critical, Software error"},
    {0x2DU, "generic, critical, Object dictionary does not match the software"},
    {0x2EU, "generic, critical, Error in calculation of device parameters"},
    {0x2FU, "generic, critical, Error with access to non volatile device memory"},
    {0xFFU, "Unknown bits"}
};

static const sdo_errstr_t sdo_errors[] = {
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
/* Support functions                                                         */
/*===========================================================================*/
void print_data(BaseSequentialStream *chp, char *format, void *data, size_t len)
{
    char str[100];

    if (!strcmp(format, "u8")) {
        chprintf(chp, "%u\r\n", *((uint8_t*)data));
    } else if (!strcmp(format, "u16")) {
        chprintf(chp, "%u\r\n", *((uint16_t*)data));
    } else if (!strcmp(format, "u32")) {
        chprintf(chp, "%u\r\n", *((uint32_t*)data));
    } else if (!strcmp(format, "s8")) {
        chprintf(chp, "%d\r\n", *((int8_t*)data));
    } else if (!strcmp(format, "s16")) {
        chprintf(chp, "%d\r\n", *((int16_t*)data));
    } else if (!strcmp(format, "s32")) {
        chprintf(chp, "%d\r\n", *((int32_t*)data));
    } else if (!strcmp(format, "vs")) {
        strncpy(str, data, 99);
        str[(len<100?len:100)] = '\0';
        chprintf(chp, "%s\r\n", str);
    } else {
        chprintf(chp, "Unknown format\r\n");
    }
}

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
    chprintf(chp, "Usage: sdo read|write <NodeID> <index> <subindex> <format> [blockmode]\r\n");
}

void cmd_sdo(BaseSequentialStream *chp, int argc, char *argv[])
{
    uint32_t data_len = 0;
    uint32_t abrt_code = 0;
    uint8_t node_id = 0;
    uint16_t index = 0;
    uint8_t subindex = 0;
    bool block = false;

    if (argc < 5) {
        sdo_usage(chp);
        return;
    }

    node_id = strtoul(argv[1], NULL, 0);
    index = strtoul(argv[2], NULL, 0);
    subindex = strtoul(argv[3], NULL, 0);
    if (argc == 6)
        block = !strcmp(argv[5], "true");

    if (!strcmp(argv[0], "read")) {
        sdo_upload(CO->SDOclient[0], node_id, index, subindex, data, sizeof(data), &data_len, &abrt_code, 1000, block);
        if (abrt_code == CO_SDO_AB_NONE) {
            chprintf(chp, "Received %u bytes of data.\r\n", data_len);
            print_data(chp, argv[4], data, data_len);
        } else {
            const sdo_errstr_t *err;
            for (err = &sdo_errors[0]; err->code != 0 && err->code != abrt_code; err++);
            chprintf(chp, "Received abort code: (%08X) %s\r\n", abrt_code, err->desc);
        }
    } else if (!strcmp(argv[0], "write")) {
        chprintf(chp, "Function disabled\r\n");
        /*sdo_download(CO->SDOclient[0], node_id, index, subindex, data, data_len, &abrt_code, 1000, block);*/
    } else {
        sdo_usage(chp);
        return;
    }
}

/*===========================================================================*/
/* CAN Emergency Messages                                                    */
/*===========================================================================*/
void em_usage(BaseSequentialStream *chp)
{
    chprintf(chp, "Usage: em \r\n");
}

void cmd_em(BaseSequentialStream *chp, int argc, char *argv[])
{
    if (argc < 1) {
        em_usage(chp);
        return;
    }

    if (!strcmp(argv[0], "test1")) {
        chprintf(chp, "Placeholder\r\n");
    } else if (!strcmp(argv[0], "test2")) {
        chprintf(chp, "Placeholder\r\n");
    } else {
        chprintf(chp, "Invalid command: %s\r\n", argv[0]);
        em_usage(chp);
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
/* Time                                                                      */
/*===========================================================================*/
void time_usage(BaseSequentialStream *chp)
{
    chprintf(chp, "Usage: time set|get <UNIX Time>\r\n");
}

void cmd_time(BaseSequentialStream *chp, int argc, char *argv[])
{
    time_t unix_time;
    uint32_t msec;
    if (argc < 1) {
        time_usage(chp);
        return;
    }
    if (!strcmp(argv[0], "get")) {
        unix_time = get_time_unix(&msec);
        chprintf(chp, "UNIX Time: %s\r\n", ctime(&unix_time));
    } else if (!strcmp(argv[0], "set") && argc > 1) {
        set_time_unix(strtoul(argv[1], NULL, 0), 0);
    } else {
        time_usage(chp);
        return;
    }
}

/*===========================================================================*/
/* Shell                                                                     */
/*===========================================================================*/
static const ShellCommand commands[] = {
    {"nmt", cmd_nmt},
    {"sdo", cmd_sdo},
    {"em",  cmd_em},
    {"opd", cmd_opd},
    {"mmc", cmd_mmc},
    {"time", cmd_time},
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
