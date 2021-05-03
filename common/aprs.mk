# List of all the APRS protocol files.
APRSSRC := $(PROJ_SRC)/ax25.c   \
           $(PROJ_SRC)/aprs.c

# Required include directories
APRSINC := $(PROJ_SRC)/include

# Shared variables
ALLCSRC += $(APRSSRC)
ALLINC  += $(APRSINC)
