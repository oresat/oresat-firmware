/*
 * lfs util functions
 *
 * Copyright (c) 2017, Arm Limited. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "lfs_util.h"
#include "crc.h"

// Software CRC implementation with small lookup table
uint32_t lfs_crc(uint32_t crc, const void *buffer, size_t size) {
    return crc32(buffer, size, ~crc);
}
