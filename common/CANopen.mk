# Required libraries for CANopen
#include $(PROJ_SRC)/include.mk

CANOPEN_SRC  = $(PROJ_SRC)/CANopenNode

# List of all CANopen sources
CANOPENSRC  := $(PROJ_SRC)/CO_driver.c                 \
               $(PROJ_SRC)/CO_master.c                 \
               $(CANOPEN_SRC)/301/CO_SDOserver.c       \
               $(CANOPEN_SRC)/301/CO_Emergency.c       \
               $(CANOPEN_SRC)/301/CO_NMT_Heartbeat.c   \
               $(CANOPEN_SRC)/301/CO_HBconsumer.c      \
               $(CANOPEN_SRC)/301/CO_SYNC.c            \
               $(CANOPEN_SRC)/301/CO_PDO.c             \
               $(CANOPEN_SRC)/301/CO_TIME.c            \
               $(CANOPEN_SRC)/301/CO_SDOclient.c       \
               $(CANOPEN_SRC)/301/crc16-ccitt.c        \
               #$(CANOPEN_SRC)/305/CO_LSSmaster.c       \
               #$(CANOPEN_SRC)/305/CO_LSSslave.c        \
               $(CANOPEN_SRC)/extra/CO_trace.c         \
               $(CANOPEN_SRC)/CANopen.c

# Required include directories
CANOPENINC  := $(CANOPEN_SRC)

# Shared variables
ALLCSRC     += $(CANOPENSRC)
ALLINC      += $(CANOPENINC)
