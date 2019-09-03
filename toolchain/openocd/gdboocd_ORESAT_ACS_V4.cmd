target remote | openocd -s ../../../toolchain/openocd -f oocd_ORESAT_ACS_V4.cfg -c "gdb_port pipe"
monitor stm32l4x.cpu configure -rtos ChibiOS
monitor reset halt
