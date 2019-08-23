#ifndef _EVENTS_H_
#define _EVENTS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ch.h"

#define ORESAT_NMT_OPERATIONAL 0
#define ORESAT_NMT_NONOPERATIONAL 1

extern event_source_t oresat_event;

void reg_event(eventid_t event, evhandler_t event_handler);
void unreg_event(eventid_t event);
void unreg_all_events(void);

extern THD_WORKING_AREA(can_events_wa, 0x40);
extern THD_FUNCTION(can_events, p);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
