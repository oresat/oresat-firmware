APP_HEXFILE = $(BUILDDIR)/$(PROJECT).hex
GDB_ELF = $(BUILDDIR)/$(PROJECT).elf
OOCD_CFG = oocd.cfg
GDB_OOCD_CFG = gdboocd.cmd
GDB_STL_CFG = gdbstl.cmd

write: $(APP_HEXFILE) write_stl

write_ocd:
	openocd -s $(BOARDDIR) -f $(OOCD_CFG) -c "program $(APP_HEXFILE) verify reset exit"

write_stl:
	st-flash $(ARGS) --reset --format ihex write $(APP_HEXFILE)

gdb: $(GDB_ELF) gdb_stl

gdb_ocd:
	$(TRGT)gdb -q $(shell pwd)/$(GDB_ELF) -cd $(BOARDDIR) -x $(GDB_OOCD_CFG)

gdb_stl:
	$(TRGT)gdb -q $(shell pwd)/$(GDB_ELF) -cd $(TOOLCHAIN) -x ./$(GDB_STL_CFG)
