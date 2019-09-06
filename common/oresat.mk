CANOPEN_SRC   = $(PROJ_SRC)/CANopenNode
CO_STACK      = $(CANOPEN_SRC)/stack

PROJINC       = $(PROJ_SRC)/include             \
                $(CANOPEN_SRC)                  \
                $(CO_STACK)

PROJSRC       = $(PROJ_SRC)/CO_driver.c         \
                $(PROJ_SRC)/CO_master.c         \
                $(CO_STACK)/CO_SDO.c            \
                $(CO_STACK)/CO_Emergency.c      \
                $(CO_STACK)/CO_NMT_Heartbeat.c  \
                $(CO_STACK)/CO_SYNC.c           \
                $(CO_STACK)/CO_PDO.c            \
                $(CO_STACK)/CO_HBconsumer.c     \
                $(CO_STACK)/CO_SDOmaster.c      \
                $(CO_STACK)/CO_LSSmaster.c      \
                $(CO_STACK)/CO_LSSslave.c       \
                $(CO_STACK)/CO_trace.c          \
                $(CO_STACK)/crc16-ccitt.c       \
                $(CANOPEN_SRC)/CANopen.c        \
                $(PROJ_SRC)/events.c            \
                $(PROJ_SRC)/worker.c            \
                $(PROJ_SRC)/oresat.c


# Shared variables.
ALLCSRC      += $(PROJSRC)
ALLINC       += $(PROJINC)
