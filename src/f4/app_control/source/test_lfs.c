#include <stdio.h>
#include <ctype.h>
#include "test_lfs.h"
#include "fs.h"

#define BUF_SIZE 256

/*===========================================================================*/
/* OreSat LFS Operations                                                     */
/*===========================================================================*/
void cmd_lfs(BaseSequentialStream *chp, int argc, char *argv[])
{
    int ret;
    lfs_file_t *file;
    lfs_dir_t *dir;
    struct lfs_info info;
    char buf[BUF_SIZE];

    if (!strcmp(argv[0], "ls") && argc > 1) {
        dir = dir_open(&FSD1, argv[1]);
        if (dir == NULL) {
            chprintf(chp, "Error in dir_open: %d\r\n", FSD1.err);
            return;
        }
        do {
            ret = dir_read(&FSD1, dir, &info);
            if (ret <= 0) {
                if (ret < 0) {
                    chprintf(chp, "Error in dir_read: %d\r\n", ret);
                }
                continue;
            }
            if (info.type == LFS_TYPE_REG) {
                chprintf(chp, "reg  ");
            } else if (info.type == LFS_TYPE_DIR) {
                chprintf(chp, "dir  ");
            } else {
                chprintf(chp, "?    ");
            }
            chprintf(chp, "%8u %s\r\n", info.size, info.name);
        } while (ret > 0);
        ret = dir_close(&FSD1, dir);
        if (ret < 0) {
            chprintf(chp, "Error in dir_close: %d\r\n", ret);
            return;
        }
        chprintf(chp, "\r\n");
    } else if (!strcmp(argv[0], "mkdir") && argc > 1) {
        ret = fs_mkdir(&FSD1, argv[1]);
        if (ret < 0) {
            chprintf(chp, "Error in fs_mkdir: %d\r\n");
            return;
        }
    } else if (!strcmp(argv[0], "rm") && argc > 1) {
        ret = fs_remove(&FSD1, argv[1]);
        if (ret < 0) {
            chprintf(chp, "Error in fs_remove: %d\r\n");
            return;
        }
    } else if (!strcmp(argv[0], "crc") && argc > 1) {
        file = file_open(&FSD1, argv[1], LFS_O_RDONLY);
        if (file == NULL) {
            chprintf(chp, "Error in file_open: %d\r\n", FSD1.err);
            return;
        }

        chprintf(chp, "CRC32: %08X\r\n", file_crc(&FSD1, file));

        ret = file_close(&FSD1, file);
        if (ret < 0) {
            chprintf(chp, "Error in file_close: %d\r\n", ret);
            return;
        }
    } else if (!strcmp(argv[0], "cat") && argc > 1) {
        file = file_open(&FSD1, argv[1], LFS_O_RDONLY);
        if (file == NULL) {
            chprintf(chp, "Error in file_open: %d\r\n", FSD1.err);
            return;
        }

        ret = file_read(&FSD1, file, buf, BUF_SIZE - 1);
        if (ret < 0) {
            chprintf(chp, "Error in file_read: %d\r\n", ret);
            file_close(&FSD1, file);
            return;
        }
        buf[ret] = '\0';
        chprintf(chp, "%s\r\n", buf);

        ret = file_close(&FSD1, file);
        if (ret < 0) {
            chprintf(chp, "Error in file_close: %d\r\n", ret);
            return;
        }
    } else if (!strcmp(argv[0], "hexdump") && argc > 1) {
        file = file_open(&FSD1, argv[1], LFS_O_RDONLY);
        if (file == NULL) {
            chprintf(chp, "Error in file_open: %d\r\n", FSD1.err);
            return;
        }

        ret = file_read(&FSD1, file, buf, BUF_SIZE);
        if (ret < 0) {
            chprintf(chp, "Error in file_read: %d\r\n", ret);
            file_close(&FSD1, file);
            return;
        }
        for (int i = 0; i < ret; i++) {
            if (i % 0x10 == 0) chprintf(chp, "\r\n%04X:", i);
            chprintf(chp, " %02X", buf[i]);
        }
        chprintf(chp, "\r\n");

        ret = file_close(&FSD1, file);
        if (ret < 0) {
            chprintf(chp, "Error in file_close: %d\r\n", ret);
            return;
        }
    } else if (!strcmp(argv[0], "load") && argc > 1) {
        uint8_t buf[BUF_SIZE] = {0};
        char line[BUF_SIZE * 2] = {0};
        char c, *p = line;
        size_t count = 0;
        file = file_open(&FSD1, argv[1], LFS_O_RDWR | LFS_O_CREAT | LFS_O_TRUNC);
        if (file == NULL) {
            chprintf(chp, "Error in file_open: %d\r\n", FSD1.err);
            return;
        }

        while (streamRead(chp, (uint8_t*)&c, 1) != 0 && c != 4) {
            c = toupper(c);

            if (isdigit(c) || (c >= 'A' && c <= 'F')) {
                streamPut(chp, c);
                *(p++) = c;
                if (p == &line[BUF_SIZE * 2]) {
                    for (size_t off = 0; off < BUF_SIZE; off++) {
                        sscanf(&line[off*2], "%2hhx", &buf[off]);
                    }
                    p = line;
                    ret = file_write(&FSD1, file, buf, BUF_SIZE);
                    if (ret < 0) {
                        chprintf(chp, "Error in file_write: %d\r\n", ret);
                        break;
                    }
                    count += ret;
                }
            } else if ((c == 8) || (c == 127)) {
                if (p != line) {
                    streamPut(chp, 0x08);
                    streamPut(chp, 0x20);
                    streamPut(chp, 0x08);
                    p--;
                }
            }
        }
        if (p != line) {
            size_t len = (p - line) / 2;
            for (size_t off = 0; off < len; off++) {
                sscanf(&line[off*2], "%2hhx", &buf[off]);
            }
            ret = file_write(&FSD1, file, buf, len);
            if (ret < 0) {
                chprintf(chp, "Error in file_write: %d\r\n", ret);
            } else {
                count += ret;
            }
        }
        chprintf(chp, "\r\nWrote %u bytes to %s\r\n", count, argv[1]);

        ret = file_close(&FSD1, file);
        if (ret < 0) {
            chprintf(chp, "Error in file_close: %d\r\n", ret);
            return;
        }
    } else if (!strcmp(argv[0], "mount")) {
        chprintf(chp, "Attempting to mount LFS...\r\n");
        ret = fs_mount(&FSD1, false);
        if (ret < 0) {
            chprintf(chp, "Mount failed: %d\r\n", ret);
            return;
        }
        chprintf(chp, "OK\r\n");
    } else if (!strcmp(argv[0], "unmount")) {
        chprintf(chp, "Attempting to unmount LFS...\r\n");
        ret = fs_unmount(&FSD1);
        if (ret < 0) {
            chprintf(chp, "Unmount failed: %d\r\n", ret);
            return;
        }
        chprintf(chp, "OK\r\n");
    } else if (!strcmp(argv[0], "format")) {
        chprintf(chp, "Attempting to format LFS...\r\n");
        ret = fs_format(&FSD1);
        if (ret < 0) {
            chprintf(chp, "Format failed: %d\r\n", ret);
            return;
        }
        chprintf(chp, "OK\r\n");
    } else {
        goto lfs_usage;
    }

    return;

lfs_usage:
    chprintf(chp,  "Usage: lfs <command> <path>\r\n"
                   "    ls:         List directories\r\n"
                   "    mkdir:      Make a directory\r\n"
                   "    rm:         Delete file or directory\r\n"
                   "    crc:        Print CRC32 of file\r\n"
                   "    cat:        Dump 255 bytes of file as string\r\n"
                   "    hexdump:    Dump 255 bytes of file as hex\r\n"
                   "\r\n"
                   "    mount:      Mount LFS\r\n"
                   "    unmount:    Unmount LFS\r\n"
                   "    format:     Format eMMC for LFS\r\n"
                   "\r\n");
    return;
}

