# Required libraries for RADIO
include $(PROJ_SRC)/si41xx.mk
include $(PROJ_SRC)/ax5043.mk
include $(PROJ_SRC)/ccsds.mk
include $(PROJ_SRC)/aprs.mk

# List of all the RADIO device files.
RADIOSRC := $(PROJ_SRC)/radio.c     \
            $(PROJ_SRC)/frame_buf.c \

# Required include directories
RADIOINC := $(PROJ_SRC)/include

# Shared variables
ALLCSRC += $(RADIOSRC)
ALLINC  += $(RADIOINC)
