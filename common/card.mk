# Required libraries for card manager
include $(PROJ_SRC)/opd.mk

# List of all the card manager files.
OPDSRC := $(PROJ_SRC)/card.c

# Required include directories
OPDINC := $(PROJ_SRC)/include

# Shared variables
ALLCSRC += $(OPDSRC)
ALLINC  += $(OPDINC)
