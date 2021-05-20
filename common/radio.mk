CCSDS_ROOT   = $(PROJ_ROOT)/ext/OpenCCSDS

# Required libraries for RADIO
include $(CCSDS_ROOT)/ccsds.mk
include $(PROJ_SRC)/si41xx.mk
include $(PROJ_SRC)/ax5043.mk
include $(PROJ_SRC)/aprs.mk

# List of all the RADIO device files.
RADIOSRC := $(PROJ_SRC)/radio.c     \

# Required include directories
RADIOINC := $(PROJ_SRC)/include

# Shared variables
ALLCSRC += $(RADIOSRC) $(CCSDS_SRC)
ALLINC  += $(RADIOINC) $(CCSDS_INC)
