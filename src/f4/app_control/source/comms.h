#ifndef _COMMS_H_
#define _COMMS_H_

#include "radio.h"

#define XTAL_CLK                            16000000U
#define EDL_WORKERS                         2

#define SCID                                0x4F53U
#define MCID                                ((USLP_TFVN << 16) | SCID)
/* 16-bit FECF provided by AX5043 driver */
#define FECF_LEN                            2
#define USLP_MAX_LEN                        (FB_MAX_LEN + FECF_LEN)
#define CMD_RESP_SIZE                       (64U + USLP_MAX_HEADER_LEN)

#ifdef __cplusplus
extern "C" {
#endif

void comms_init(void);
void comms_start(void);
void comms_stop(void);

void comms_cmd(fb_t *fb);
void comms_beacon(bool enable);

void comms_send(fb_t *fb);
void comms_send_ahead(fb_t *fb);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
