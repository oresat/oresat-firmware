target remote | openocd -f oocd.cfg -c "gdb_port pipe"
monitor stm32f4x.cpu configure -rtos chibios
monitor reset halt
