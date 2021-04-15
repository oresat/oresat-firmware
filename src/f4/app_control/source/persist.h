#ifndef _PERSIST_H_
#define _PERSIST_H_

#include "ch.h"
#include "hal.h"

#define FRAM_STATE_ADDR                     0x0000U
#define FRAM_COMM_ADDR                      0x0100U
#define FRAM_MFR_ADDR                       0x0200U
#define FRAM_APP_ADDR                       0x0300U

void storeGroup(void *group);
void restoreGroup(void *group);

#endif
