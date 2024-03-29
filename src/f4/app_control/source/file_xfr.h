#ifndef _FILE_XFR_H_
#define _FILE_XFR_H_

#include "fs.h"

typedef struct {
    char filename[8];
    uint32_t off;
    uint32_t len;
    uint8_t data[];
} file_xfr_t;

#ifdef __cplusplus
extern "C" {
#endif

int file_recv(file_xfr_t *xfr, uint32_t *crc);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
