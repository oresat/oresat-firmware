#include "file_xfr.h"
#include "crc.h"

int file_recv(file_xfr_t *xfr, uint32_t *crc)
{
    lfs_file_t *file;
    int ret;

    file = file_open(&FSD1, xfr->filename, LFS_O_WRONLY | LFS_O_CREAT);
    if (file == NULL) {
        return FSD1.err;
    }

    ret = file_seek(&FSD1, file, xfr->off, LFS_SEEK_SET);
    if (ret < 0)
        goto file_recv_fail;

    ret = file_write(&FSD1, file, xfr->data, xfr->len);
    if (ret < 0)
        goto file_recv_fail;

    *crc = crc32(xfr->data, xfr->len, 0);

file_recv_fail:
    file_close(&FSD1, file);
    return ret;
}
