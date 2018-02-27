target remote | openocd -s ../../../toolchain/openocd -f oocd_ST_NUCLEO64_F446RE.cfg -c "gdb_port pipe"
monitor stm32f4x.cpu configure -rtos ChibiOS
monitor reset halt
