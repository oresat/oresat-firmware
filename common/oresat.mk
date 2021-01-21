include $(PROJ_SRC)/CANopen.mk

PROJINC       = $(PROJ_SRC)/include

PROJSRC       = $(PROJ_SRC)/sensors.c                   \
                $(PROJ_SRC)/worker.c                    \
                $(PROJ_SRC)/oresat.c


# Shared variables.
ALLCSRC      += $(PROJSRC)
ALLINC       += $(PROJINC)
