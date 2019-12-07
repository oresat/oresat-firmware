target remote | openocd -s ../../../toolchain/openocd -f oocd_ORESAT_C3_V1.cfg -c "gdb_port pipe"
monitor stm32f4x.cpu configure -rtos ChibiOS
monitor reset halt
