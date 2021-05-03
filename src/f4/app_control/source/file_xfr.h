#ifndef _FILE_XFR_H_
#define _FILE_XFR_H_

#include "fs.h"

typedef struct {
    char filename[32];
    lfs_soff_t off;
    lfs_size_t len;
    uint8_t data[];
} file_xfr_t;

#ifdef __cplusplus
extern "C" {
#endif

int file_recv(file_xfr_t *xfr);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
