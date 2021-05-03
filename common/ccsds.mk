# List of all the CCSDS source files.
CCSDSSRC    := $(PROJ_SRC)/uslp.c       \
               $(PROJ_SRC)/cop.c        \
               $(PROJ_SRC)/sdls.c       \
               $(PROJ_SRC)/spp.c

# Required include directories
CCSDSINC    := $(PROJ_SRC)/include

# Shared variables
ALLCSRC     += $(CCSDSSRC)
ALLINC      += $(CCSDSINC)
