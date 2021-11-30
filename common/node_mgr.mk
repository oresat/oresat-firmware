# Required libraries for node manager
include $(PROJ_SRC)/opd.mk

# List of all the node manager files.
NODEMGRSRC := $(PROJ_SRC)/node_mgr.c

# Required include directories
NODEMGRINC := $(PROJ_SRC)/include

# Shared variables
ALLCSRC += $(NODEMGRSRC)
ALLINC  += $(NODEMGRINC)
