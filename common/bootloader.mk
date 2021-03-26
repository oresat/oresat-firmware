BOOTLOADERINC = $(PROJ_SRC)/include

BOOTLOADERSRC = $(PROJ_SRC)/util.c                      \
                $(PROJ_SRC)/can_bootloader.c

# Shared variables.
ALLCSRC      += $(BOOTLOADERSRC)
ALLINC       += $(BOOTLOADERINC)
