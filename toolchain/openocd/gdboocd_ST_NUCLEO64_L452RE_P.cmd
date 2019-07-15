target remote | openocd -s ../../../toolchain/openocd -f oocd_ST_NUCLEO64_L452RE.cfg -c "gdb_port pipe"
monitor stm32l4x.cpu configure -rtos ChibiOS
monitor reset halt
