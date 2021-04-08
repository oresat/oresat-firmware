#include "beacon.h"
#include "radio.h"
#include "CANopen.h"
#include "ax25.h"

static const ax25_link_t ax25 = {
    .dest = "SPACE ",
    .dest_ssid = 0,
    .src = "KJ7SAT",
    .src_ssid = 0,
    .control = AX25_CTRL_UFRAME | _VAL2FLD(AX25_CTRL_U_FLD, AX25_UFRAME_UI),
    .sid = AX25_PID_NONE,
};

static char tlm_frame = 'T';

THD_FUNCTION(beacon, arg) {
    const radio_cfg_t *cfg = arg;

    while (!chThdShouldTerminateX()) {
        fb_t *fb = fb_alloc(AX25_MAX_FRAME_LEN);

        fb_reserve(fb, AX25_MAX_HDR_LEN);
        fb->data_ptr = fb_put(fb, sizeof(tlm_frame));
        memcpy(fb->data_ptr, &tlm_frame, sizeof(tlm_frame));
        ax25_sdu(fb, &ax25);

        /* APRS Beacon */
        ax5043TX(cfg->devp, cfg->profile, fb->data, fb->len, fb->len, NULL, NULL, false);
        fb_free(fb);

        chThdSleepMilliseconds(OD_TX_Control.beaconInterval);
    }

    chThdExit(MSG_OK);
}
