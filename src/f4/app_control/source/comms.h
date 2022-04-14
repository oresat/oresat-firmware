#ifndef _COMMS_H_
#define _COMMS_H_

#include "radio.h"

#define XTAL_CLK                            16000000U
#define EDL_WORKERS                         1

#define SCID                                0x4F53U
#define MCID                                ((USLP_TFVN << 16) | SCID)
/* 16-bit FECF provided by AX5043 driver */
#define FECF_LEN                            2
#define USLP_MAX_LEN                        (FB_MAX_LEN + FECF_LEN)
#define CMD_RESP_LEN                        64
#define CMD_RESP_ALLOC                      (CMD_RESP_LEN + USLP_MAX_HEADER_LEN)
#define FILE_BUF_LEN                        1024

#ifdef __cplusplus
extern "C" {
#endif

extern AX5043Driver lband;
extern AX5043Driver uhf;

void comms_init(void);
void comms_start(void);
void comms_stop(void);

void comms_cmd(fb_t *fb, void *arg);
void comms_file(fb_t *fb, void *arg);
void comms_beacon(fb_t *fb, void *arg);
void beacon_enable(bool enable);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
