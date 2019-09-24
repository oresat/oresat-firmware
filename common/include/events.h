#ifndef _EVENTS_H_
#define _EVENTS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ch.h"

typedef struct {
    eventmask_t registered_events;
    evhandler_t evhandlers[32];
} evreg_t;

void clear_evreg(evreg_t *evreg);
void reg_event(evreg_t *evreg, eventid_t event, evhandler_t event_handler);
void unreg_event(evreg_t *evreg, eventid_t event);
void event_dispatch(evreg_t *evreg, eventmask_t events);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
