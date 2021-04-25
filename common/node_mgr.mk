# Required libraries for node manager
include $(PROJ_SRC)/opd.mk

# List of all the node manager files.
OPDSRC := $(PROJ_SRC)/node.c

# Required include directories
OPDINC := $(PROJ_SRC)/include

# Shared variables
ALLCSRC += $(OPDSRC)
ALLINC  += $(OPDINC)
