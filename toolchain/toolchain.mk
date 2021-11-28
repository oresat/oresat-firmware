DATE = $(shell date +%Y%m%d)
APP_HEXFILE = $(BUILDDIR)/$(PROJECT).hex
GDB_ELF = $(BUILDDIR)/$(PROJECT).elf
OOCD_CFG = oocd.cfg
GDB_OOCD_CFG = gdboocd.cmd
GDB_STL_CFG = gdbstl.cmd
SERIAL_RAW != echo -e "$(SERIAL)"

ifeq ($(USE_BOOTLOADER),yes)
POST_MAKE_ALL_RULE_HOOK:
	python3 $(TOOLCHAIN)/f0_pack_image.py $(BUILDDIR)/$(PROJECT).bin $(BUILDDIR)/$(PROJECT).crc32.bin $(DATE)
	@# Convert the crc32 bin file to a hex file that can be written to the STM32F0 with 'make write'
	srec_cat $(BUILDDIR)/$(PROJECT).crc32.bin -binary -offset 0x0800A000 -o $(BUILDDIR)/$(PROJECT).bin.hex -Intel -Line_Length 44
	mv $(BUILDDIR)/$(PROJECT).hex $(BUILDDIR)/$(PROJECT).origional.hex
	cp $(BUILDDIR)/$(PROJECT).bin.hex $(BUILDDIR)/$(PROJECT).hex
	xxd -i $(BUILDDIR)/$(PROJECT).crc32.bin > $(BUILDDIR)/$(PROJECT).crc32.bin.h
endif

write: $(OUTFILES) POST_MAKE_ALL_RULE_HOOK write_ocd

write_ocd:
	openocd -s $(BOARDDIR) -f $(OOCD_CFG) -c "hla_serial $(SERIAL); program $(APP_HEXFILE) verify reset exit"

write_stl:
	st-flash --serial=$(SERIAL_RAW) --reset --format ihex write $(APP_HEXFILE)

gdb: $(GDB_ELF) gdb_ocd

gdb_ocd:
	$(TRGT)gdb -q $(shell pwd)/$(GDB_ELF) -cd $(BOARDDIR) -ex "target remote | openocd -f oocd.cfg -c 'hla_serial $(SERIAL); gdb_port pipe'" -x $(GDB_OOCD_CFG)

gdb_stl:
	$(TRGT)gdb -q $(shell pwd)/$(GDB_ELF) -cd $(TOOLCHAIN) -x ./$(GDB_STL_CFG)

serial:
	picocom -b 115200 /dev/serial/by-id/usb-STMicroelectronics_STLINK-V3_$(SERIAL_RAW)-if02
