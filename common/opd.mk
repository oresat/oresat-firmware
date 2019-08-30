# Required libraries for OPD
include $(PROJ_SRC)/max7310.mk

# List of all the OPD device files.
OPDSRC := $(PROJ_SRC)/opd.c

# Required include directories
OPDINC := $(PROJ_SRC)/include

# Shared variables
ALLCSRC += $(OPDSRC)
ALLINC  += $(OPDINC)
