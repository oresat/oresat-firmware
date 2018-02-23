OPENOCD_DIR = $(TOOLCHAIN)/openocd

OPENOCD_HEXFILE = $(BUILDDIR)/$(PROJECT).hex
GDB_ELF = $(BUILDDIR)/$(PROJECT).elf
OOCD_CFG = oocd_$(BOARD).cfg
GDB_CFG = $(OPENOCD_DIR)/gdboocd_$(BOARD).cmd

write: $(OPENOCD_HEXFILE) write_stl

write_base:
	openocd -s $(OPENOCD_DIR) -f $(OOCD_CFG) -c "program $(OPENOCD_HEXFILE) verify reset exit"

#write_stl: OOCD_CFG = stlinkv2-1_stm32.cfg
write_stl: write_base

gdb: $(GDB_ELF) gdb_ocd

gdb_base:
	$(TRGT)gdb -q $(GDB_ELF) -x $(GDB_CFG)

cgdb_base:
	cgdb -d $(TRGT)gdb -q $(GDB_ELF) -x $(GDB_CFG)

#gdb_ocd: GDB_CFG = $(OPENOCD_DIR)/gdboocd_ocd.cmd
gdb_ocd: gdb_base

gdb_stl: GDB_CFG = $(OPENOCD_DIR)/gdboocd_stl.cmd
gdb_stl: gdb_base

cgdb_stl: GDB_CFG = $(OPENOCD_DIR)/gdboocd_stl.cmd
cgdb_stl: cgdb_base

