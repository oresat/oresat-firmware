#ifndef _HMAC_H_
#define _HMAC_H_

#include "ch.h"
#include "hal.h"

int hmac_send(void *data, size_t len, void *iv, void *seq_num, void *mac, void *arg);
int hmac_recv(void *data, size_t len, void *iv, void *seq_num, void *mac, void *arg);

#endif
