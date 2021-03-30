#ifndef _C3_H_
#define _C3_H_

#include "ch.h"
#include "hal.h"

#define C3_EVENT_WAKEUP                     EVENT_MASK(0)
#define C3_EVENT_TERMINATE                  EVENT_MASK(1)
#define C3_EVENT_TX                         EVENT_MASK(2)
#define C3_EVENT_BAT                        EVENT_MASK(3)
#define C3_EVENT_EDL                        EVENT_MASK(4)

typedef enum {
    PREDEPLOY           = 'B',
    DEPLOY              = 'C',
    STANDBY             = 'D',
    BEACON              = 'E',
    EDL                 = 'F'
} c3_state_t;

typedef struct {
    event_listener_t    el;
    event_source_t     *event;
    eventflags_t        flags;
} c3_event_t;

typedef struct {
    c3_state_t          state;
    c3_state_t          next_state;
    eventmask_t         events;
} c3_fsm_t;

typedef struct {
    RTCDateTime timestamp;
    RTCAlarm    alarm_a;
    RTCAlarm    alarm_b;
    RTCWakeup   wakeup;
} rtc_state_t;

/* Placeholder variables for satellite state from object dictionary */
/* TODO: Switch to actual OD variables */
extern bool bat_good;
extern bool edl;

/* Main Command, Communications, and Control Thread Prototype */
extern THD_WORKING_AREA(c3_wa, 0x400);
extern THD_FUNCTION(c3, arg);

/* Support function prototypes */
void factory_reset(void);

#endif
