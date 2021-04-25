#include <stdlib.h>
#include <string.h>

#include "cli.h"
#include "c3.h"
#include "CANopen.h"
#include "test_fw.h"
#include "test_canopen.h"
#include "test_opd.h"
#include "test_time.h"
#include "test_fram.h"
#include "test_lfs.h"
#include "test_mmc.h"
#include "test_radio.h"
#include "test_comms.h"
#include "test_deploy.h"
#include "test_crc.h"
#include "chprintf.h"
#include "shell.h"

static thread_t *shell_tp;
extern thread_t *c3_tp;

/*===========================================================================*/
/* OreSat C3 State Control                                                   */
/*===========================================================================*/
void cmd_state(BaseSequentialStream *chp, int argc, char *argv[])
{
    if (argc < 1) {
        goto state_usage;
    }
    if (!strcmp(argv[0], "status")) {
        chprintf(chp, "C3 State:  %c\r\n", OD_C3State[0]);
        chprintf(chp, "TX Enable: %s\r\n", (tx_enabled() ? "TRUE" : "FALSE"));
        chprintf(chp, "Bat Good:  %s\r\n", (bat_good() ? "TRUE" : "FALSE"));
        chprintf(chp, "EDL Mode:  %s\r\n", (edl_enabled() ? "TRUE" : "FALSE"));
        chprintf(chp, "Current Bank: %d\r\n"
                      "Next Boot Bank: %d\r\n\r\n",
                      (SYSCFG->MEMRMP & SYSCFG_MEMRMP_UFB_MODE ? 1 : 0),
                      (FLASH->OPTCR & FLASH_OPTCR_BFB2 ? 1 : 0));
        chprintf(chp, "===RTC===\r\n"
                      "Date:      %08X\r\n"
                      "Time:      %08X\r\n"
                      "Wakeup:    %08X (%s)\r\n"
                      "Alarm A:   %08X (%s)\r\n"
                      "Alarm B:   %08X (%s)\r\n",
                      RTCD1.rtc->DR, RTCD1.rtc->TR,
                      RTCD1.rtc->WUTR, (RTCD1.rtc->CR & RTC_CR_WUTE ? "ENABLED" : "DISABLED"),
                      RTCD1.rtc->ALRMAR, (RTCD1.rtc->CR & RTC_CR_ALRAE ? "ENABLED" : "DISABLED"),
                      RTCD1.rtc->ALRMBR, (RTCD1.rtc->CR & RTC_CR_ALRBE ? "ENABLED" : "DISABLED"));
    } else if (!strcmp(argv[0], "tx") && argc > 1) {
        tx_enable(argv[1][0] == 't');
    } else if (!strcmp(argv[0], "edl") && argc > 1) {
        edl_enable(argv[1][0] == 't');
    } else if (!strcmp(argv[0], "i2c_cycle")) {
        palSetLine(LINE_I2C_PWROFF);
        chThdSleepMilliseconds(10);
        palClearLine(LINE_I2C_PWROFF);
    } else if (!strcmp(argv[0], "reset")) {
        NVIC_SystemReset();
    } else if (!strcmp(argv[0], "factoryreset")) {
        chprintf(chp, "Initiating factory reset...");
        factory_reset();
    } else {
        goto state_usage;
    }

    return;

state_usage:
    chprintf(chp,  "Usage: state <command>\r\n"
                   "    status:         Get current system state\r\n"
                   "    tx <t/f>:       Override TX enable state\r\n"
                   "    edl <t/f>:      Override EDL state\r\n"
                   "    i2c_cycle:      Power cycle I2C peripheral bus\r\n"
                   "    reset:          Soft reset C3\r\n"
                   "    factoryreset:   Reset C3 to factory defaults\r\n"
                   "\r\n");
    return;
}

/*===========================================================================*/
/* Shell                                                                     */
/*===========================================================================*/
static const ShellCommand commands[] = {
    {"fw", cmd_fw},
    {"nmt", cmd_nmt},
    /*{"sdo", cmd_sdo},*/
    {"opd", cmd_opd},
    {"node", cmd_node},
    {"mmc", cmd_mmc},
    {"time", cmd_time},
    {"lfs", cmd_lfs},
    {"radio", cmd_radio},
    {"synth", cmd_synth},
    {"rf", cmd_rf},
    {"rftest", cmd_rftest},
    {"beacon", cmd_beacon},
    {"state", cmd_state},
    {"fram", cmd_fram},
    {"crc", cmd_crc},
    {"deploy", cmd_deploy},
    {"edl", cmd_edl},
    {NULL, NULL}
};

static char histbuf[SHELL_MAX_HIST_BUFF];

static const ShellConfig shell_cfg = {
    (BaseSequentialStream *)&SD3,
    commands,
    histbuf,
    sizeof(histbuf),
};

THD_WORKING_AREA(shell_wa, 0x1000);
THD_WORKING_AREA(cli_wa, 0x100);
THD_FUNCTION(cli, arg)
{
    (void)arg;

    /* Start a shell */
    while (!chThdShouldTerminateX()) {
        shell_tp = chThdCreateStatic(shell_wa, sizeof(shell_wa), NORMALPRIO, shellThread, (void *)&shell_cfg);
        chThdWait(shell_tp);
        chThdSleepMilliseconds(500);
    }

    chThdExit(MSG_OK);
}
