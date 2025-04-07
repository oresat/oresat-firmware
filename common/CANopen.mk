# Required libraries for CANopen
#include $(PROJ_SRC)/include.mk

CANOPEN_SRC  = $(PROJ_ROOT)/ext/CANopenNode

# List of all CANopen sources
CANOPENSRC  := $(PROJ_SRC)/CO_driver.c                  \
               $(PROJ_SRC)/CO_threads.c                 \
               $(CANOPEN_SRC)/301/CO_ODinterface.c      \
               $(CANOPEN_SRC)/301/CO_NMT_Heartbeat.c    \
               $(CANOPEN_SRC)/301/CO_HBconsumer.c       \
               $(CANOPEN_SRC)/301/CO_Emergency.c        \
               $(CANOPEN_SRC)/301/CO_SDOserver.c        \
               $(CANOPEN_SRC)/301/CO_SYNC.c             \
               $(CANOPEN_SRC)/301/CO_PDO.c              \
               $(CANOPEN_SRC)/301/crc16-ccitt.c         \
               $(CANOPEN_SRC)/CANopen.c

# Optional sources
#CANOPENSRC  += $(CANOPEN_SRC)/303/CO_LEDs.c             \
               #$(CANOPEN_SRC)/304/CO_GFC.c              \
               #$(CANOPEN_SRC)/304/CO_SRDO.c             \
               #$(CANOPEN_SRC)/305/CO_LSSslave.c         \
               #$(CANOPEN_SRC)/305/CO_LSSmaster.c        \
               #$(CANOPEN_SRC)/extra/CO_trace.c

# Required include directories
CANOPENINC  := $(CANOPEN_SRC)

# Shared variables
ALLCSRC     += $(CANOPENSRC)
ALLINC      += $(CANOPENINC)
