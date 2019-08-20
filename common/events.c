#include "events.h"

EVENTSOURCE_DECL(oresat_event);

static eventmask_t registered_events;
static evhandler_t evhandlers[32];

void reg_event(eventid_t event, evhandler_t event_handler)
{
    chDbgCheck(event < 32);

    chSysLock();
    registered_events |= EVENT_MASK(event);
    evhandlers[event] = event_handler;
    chSysUnlock();
}

void unreg_event(eventid_t event)
{
    chDbgCheck(event < 32);

    chSysLock();
    registered_events &= ~EVENT_MASK(event);
    evhandlers[event] = NULL;
    chSysUnlock();
}

void unreg_all_events(void)
{
    chSysLock();
    registered_events = 0;
    for (uint32_t i = 0; i < 32; i++)
        evhandlers[i] = NULL;
    chSysUnlock();
}

THD_WORKING_AREA(can_events_wa, 0x40);
THD_FUNCTION(can_events, p)
{
    event_listener_t el;
    eventmask_t events;
    (void)p;

    // Set thread name
    chRegSetThreadName("can_ev");
    // Register RX event
    chEvtRegisterMask(&oresat_event, &el, registered_events);

    while (!chThdShouldTerminateX()) {
        events = chEvtWaitAnyTimeout(ALL_EVENTS, TIME_MS2I(100));
        if (events == 0)
            continue;
        chEvtDispatch(evhandlers, events);
    }

    chEvtUnregister(&oresat_event, &el);
    chThdExit(MSG_OK);
}
