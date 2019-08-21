#include "nmt.h"
#include "CANopen.h"
#include "chprintf.h"

// Example blinker thread
THD_WORKING_AREA(nmt_wa, 0x100);
THD_FUNCTION(nmt, arg) {
    CO_SDOclient_return_t ret;
    systime_t prev_time, cur_time, diff_time;
    BaseSequentialStream *chp = (BaseSequentialStream *)&SD2;
    uint8_t data[31];
    uint32_t dataSize;
    (void)arg;

    palSetLineMode(LINE_LED_GREEN,PAL_MODE_OUTPUT_PUSHPULL);

    while (!chThdShouldTerminateX()) {
        palToggleLine(LINE_LED_GREEN);
        chThdSleepMilliseconds(500);
        if (!palReadPad(GPIOC, GPIOC_BUTTON)) {
            CO_SDOclient_setup(CO->SDOclient[0], 0, 0, 0x7F);
            CO_SDOclientUploadInitiate(CO->SDOclient[0], 0x1008, 0x0, data, 30, false);
            prev_time = chVTGetSystemTimeX();
            do {
                diff_time = chTimeDiffX(prev_time, cur_time = chVTGetSystemTimeX());
                prev_time = cur_time;
                ret = CO_SDOclientUpload(CO->SDOclient[0], diff_time, 1000, &dataSize, NULL);
                chThdSleepMilliseconds(10);
            } while (ret > 0);
            CO_SDOclientClose(CO->SDOclient[0]);
            data[dataSize] = '\0';
            chprintf(chp, "Received string: %s\r\n", data);
        }
    }

    palClearLine(LINE_LED_GREEN);
    chThdExit(MSG_OK);
}
