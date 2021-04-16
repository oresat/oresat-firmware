#ifndef _COMMS_H_
#define _COMMS_H_

#include "radio.h"

#ifdef __cplusplus
extern "C" {
#endif

void comms_init(void);
void comms_start(void);
void comms_stop(void);

void comms_beacon(bool enable);

void comms_send(fb_t *fb);
void comms_send_ahead(fb_t *fb);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
