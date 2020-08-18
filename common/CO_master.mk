# Required libraries for CANopen master nodes
#include $(PROJ_SRC)/include.mk

CANOPEN_SRC  = $(PROJ_SRC)/CANopenNode

# List of all CANopen sources for master nodes
CO_MST_SRC  := $(PROJ_SRC)/CO_master.c                  \
               $(CANOPEN_SRC)/301/CO_SDOclient.c        \
               $(CANOPEN_SRC)/301/CO_fifo.c             \
               $(CANOPEN_SRC)/309/CO_gateway_ascii.c

# Required include directories
CO_MST_INC  := $(CANOPEN_SRC)

# Shared variables
ALLCSRC     += $(CO_MST_SRC)
ALLINC      += $(CO_MST_INC)
