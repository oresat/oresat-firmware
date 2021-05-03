/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/* ChibiOS header files */
#include "ch.h"
#include "hal.h"
#include "shell.h"

/* Project header files */
#include "oresat.h"
#include "rtc.h"
#include "can_bootloader.h"
#ifdef SHELL_ENABLE
#include "cmd.h"
#endif

/*
static const oresat_node_t nodes[] = {
    {0x02, 0x00, 2000, "Battery 1"},
    {0x03, 0x00, 2000, "Battery 2"},
    {0x04, 0x00, 2000, "Solar Panel 1"},
    {0x05, 0x00, 2000, "Solar Panel 2"},
    {0x06, 0x00, 2000, "Solar Panel 3"},
    {0x07, 0x00, 2000, "Solar Panel 4"},
    {0x08, 0x00, 2000, "Solar Panel 5"},
    {0x09, 0x00, 2000, "Solar Panel 6"},
    {0x0A, 0x00, 2000, "Solar Panel 7"},
    {0x0B, 0x00, 2000, "Solar Panel 8"},
    {0x31, 0x18, 2000, "Protocard 1"},
    {0x32, 0x19, 2000, "Protocard 2"},
    {0x33, 0x1A, 2000, "Protocard 3"},
    {0x11, 0x1D, 2000, "Star Tracker"}
};
*/

#ifdef SHELL_ENABLE
static worker_t cmd_worker;
static thread_descriptor_t cmd_desc = {
    .name = "Shell",
    .wbase = THD_WORKING_AREA_BASE(cmd_wa),
    .wend = THD_WORKING_AREA_END(cmd_wa),
    .prio = NORMALPRIO,
    .funcp = cmd,
    .arg = NULL
};
#endif

static flt_reg_t fifo1_filters[] = {
    {
        .scale16.id_mask[0].STID = ORESAT_BOOTLOADER_CAN_COMMAND_GET,
        .scale16.id_mask[1].STID = ORESAT_BOOTLOADER_CAN_COMMAND_READ_MEMORY,
    },
    {
        .scale16.id_mask[0].STID = ORESAT_BOOTLOADER_CAN_COMMAND_GO,
        .scale16.id_mask[1].STID = ORESAT_BOOTLOADER_CAN_COMMAND_WRITE_MEMORY,
    },
    {
        .scale16.id_mask[0].STID = ORESAT_BOOTLOADER_CAN_COMMAND_ERASE,
        .scale16.id_mask[1].STID = CAN_BOOTLOADER_WRITE_MEMORY_RESPONSE_SID,
    },
    {
        .scale16.id_mask[0].STID = STM32_BOOTLOADER_CAN_ACK,
        .scale16.id_mask[1].STID = STM32_BOOTLOADER_CAN_NACK,
    }
};

static oresat_config_t oresat_conf = {
    .cand = &CAND1,
    .node_id = 0x01,
    .bitrate = ORESAT_DEFAULT_BITRATE,
    .fifo1_filters = fifo1_filters,
    .filter_count = sizeof(fifo1_filters),
};

/**
 * @brief App Initialization
 */
static void app_init(void)
{

    /* Initialize shell worker thread */
#ifdef SHELL_ENABLE
    reg_worker(&cmd_worker, &cmd_desc, true, true);
#endif

    /* Initialize shell and start serial interface */
#ifdef SHELL_ENABLE
    shellInit();
#endif
    sdStart(&SD3, NULL);
}

/**
 * @brief Main Application
 */
int main(void)
{
    // Initialize and start
    oresat_init(&oresat_conf);
    app_init();
    oresat_start();
    return 0;
}
