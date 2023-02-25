#include "gps_time_sync.h"
#include "301/CO_NMT_Heartbeat.h"
#include "301/CO_SYNC.h"
#include "CANopen.h"
#include "node_mgr.h"
#include "opd.h"

#define GPS_OPD_ID 0x19

#define GPS_STATUS_INIT_TIMEOUT_S 30
#define GPS_STATUS_LOOP_TIMEOUT_S 90
#define GPS_LOCK_TIMEOUT_S (60 * 15)

#define GPS_INDEX 0x700D
#define GPS_STATUS_SUBINDEX 0x9

#define STATE_CTRL_INDEX 0x6001
#define TIME_SYNC_TIMEOUT_SUBINDEX 0x5

extern CO_t *CO;

enum {
    GPS_OFF = 0x00,
    GPS_SEARCHING = 0x01,
    GPS_LOCKED = 0x02,
    GPS_ERROR = 0xFF,
} gps_state_t;


static void gps_time_sync_loop(void)
{
    int i;
    CO_NMT_internalState_t status;
    OD_entry_t *entry;
    uint8_t gps_status;

    entry = OD_find(OD, GPS_INDEX);

    // turn on the GPS card
    node_enable(GPS_OPD_ID, true);

    // wait for the GPS card to boot up and app to start sending hearbeats
    chThdSleepSeconds(GPS_STATUS_INIT_TIMEOUT_S);
    for (i=0; ; ++i) {
        node_status(GPS_OPD_ID, &status);
        if (status == CO_NMT_OPERATIONAL)
            break; // node is alive
        if (i > GPS_STATUS_LOOP_TIMEOUT_S)
            goto error; // give up
        chThdSleepSeconds(1);
    }

    // wait for gps lock
    for (i=0; ; ++i) {
        OD_get_u8(entry, GPS_STATUS_SUBINDEX, &gps_status, false);
        if (gps_status != GPS_LOCKED)
            break; // locked
        else if (gps_status == GPS_ERROR || i > GPS_LOCK_TIMEOUT_S)
            goto error; // give up
        chThdSleepSeconds(1);
    }

    // send CO SYNC, GPS should response with the Time Sync TPDO
    CO_SYNCsend(CO->SYNC);

    chThdSleepSeconds(5);

error:
    // turn off the GPS card
    node_enable(GPS_OPD_ID, false);

    return;
}


/* Watchdog Timer Thread */
THD_WORKING_AREA(gps_time_sync_wa, 0x100);
THD_FUNCTION(gps_time_sync, arg)
{
    (void)arg;
    uint32_t timeout = 0;

    OD_entry_t *timeout_entry = OD_find(OD, STATE_CTRL_INDEX);
    OD_get_u32(timeout_entry, TIME_SYNC_TIMEOUT_SUBINDEX, &timeout, false);

    if (timeout != 0) {
        chThdSleepSeconds(timeout);
        gps_time_sync_loop();
    }

    chThdExit(MSG_OK);
}
