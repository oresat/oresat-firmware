target remote | openocd -f oocd.cfg -c "gdb_port pipe"
monitor stm32l4x.cpu configure -rtos chibios
monitor reset halt
