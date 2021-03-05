# List of all the APRS device files.
APRSSRC := $(PROJ_SRC)/aprs.c

# Required include directories
APRSINC := $(PROJ_SRC)/include

# Shared variables
ALLCSRC += $(APRSSRC)
ALLINC  += $(APRSINC)
