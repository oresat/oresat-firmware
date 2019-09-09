#include "events.h"

void clear_evreg(evreg_t *evreg)
{
    chDbgCheck(evreg != NULL);

    chSysLock();
    evreg->registered_events = 0;
    for (uint32_t i = 0; i < 32; i++)
        evreg->evhandlers[i] = NULL;
    chSysUnlock();
}

void reg_event(evreg_t *evreg, eventid_t event, evhandler_t event_handler)
{
    chDbgCheck(evreg != NULL);
    chDbgAssert(event < 32 && event_handler != NULL,
            "reg_event(): Invalid parameters");

    chSysLock();
    evreg->registered_events |= EVENT_MASK(event);
    evreg->evhandlers[event] = event_handler;
    chSysUnlock();
}

void unreg_event(evreg_t *evreg, eventid_t event)
{
    chDbgCheck(evreg != NULL);
    chDbgAssert(event < 32, "unreg_event(): Invalid parameter");

    chSysLock();
    evreg->registered_events &= ~EVENT_MASK(event);
    evreg->evhandlers[event] = NULL;
    chSysUnlock();
}

void event_dispatch(evreg_t *evreg, eventmask_t events)
{
    chEvtDispatch(evreg->evhandlers, evreg->registered_events & events);
}
