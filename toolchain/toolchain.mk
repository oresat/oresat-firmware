APP_HEXFILE = $(BUILDDIR)/$(PROJECT).hex
APP_CRC_BIN_FILE = $(BUILDDIR)/$(PROJECT).crc32.bin
GDB_ELF = $(BUILDDIR)/$(PROJECT).elf
OOCD_CFG = oocd.cfg
GDB_OOCD_CFG = gdboocd.cmd
GDB_STL_CFG = gdbstl.cmd
SERIAL_RAW != echo -e "$(SERIAL)"

write: $(APP_HEXFILE) write_ocd

write_ocd:
	openocd -s $(BOARDDIR) -f $(OOCD_CFG) -c "hla_serial $(SERIAL); program $(APP_HEXFILE) verify reset exit"

write_crc:
	openocd -s $(BOARDDIR) -f $(OOCD_CFG) -c "hla_serial $(SERIAL); program $(APP_CRC_BIN_FILE) verify reset exit 0x800A000"

write_stl:
	st-flash --serial=$(SERIAL_RAW) --reset --format ihex write $(APP_HEXFILE)

gdb: $(GDB_ELF) gdb_ocd

gdb_ocd:
	$(TRGT)gdb -q $(shell pwd)/$(GDB_ELF) -cd $(BOARDDIR) -ex "target remote | openocd -f oocd.cfg -c 'hla_serial $(SERIAL); gdb_port pipe'" -x $(GDB_OOCD_CFG)

gdb_stl:
	$(TRGT)gdb -q $(shell pwd)/$(GDB_ELF) -cd $(TOOLCHAIN) -x ./$(GDB_STL_CFG)

serial:
	picocom -b 115200 /dev/serial/by-id/usb-STMicroelectronics_STLINK-V3_$(SERIAL_RAW)-if02
