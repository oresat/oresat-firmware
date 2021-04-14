include $(PROJ_SRC)/CANopen.mk
include $(PROJ_SRC)/util.mk

PROJINC       = $(PROJ_SRC)/include

PROJSRC       = $(PROJ_SRC)/sensors.c                   \
                $(PROJ_SRC)/worker.c                    \
                $(PROJ_SRC)/oresat.c

ifeq ($(USE_BOOTLOADER),yes)
    PROJSRC  += $(PROJ_SRC)/oresat_f0.c
endif

# Shared variables.
ALLCSRC      += $(PROJSRC)
ALLINC       += $(PROJINC)
