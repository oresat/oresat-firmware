#ifndef _GPS_TIME_SYNC_H_
#define _GPS_TIME_SYNC_H_

#include "ch.h"
#include "hal.h"

/* GPS Time Sync Thread Prototypes */
extern THD_WORKING_AREA(gps_time_sync_wa, 0x100);
extern THD_FUNCTION(gps_time_sync, arg);

#endif /* _GPS_TIME_SYNC_H_ */
