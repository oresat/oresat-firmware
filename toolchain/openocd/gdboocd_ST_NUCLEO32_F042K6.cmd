target remote | openocd -s ../../../toolchain/openocd -f oocd_ST_NUCLEO32_F042K6.cfg -c "gdb_port pipe"
monitor stm32f0x.cpu configure -rtos ChibiOS
monitor reset halt
