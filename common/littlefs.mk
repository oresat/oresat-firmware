# Required libraries for littlefs
#include $(PROJ_SRC)/include.mk

LITTLEFS_SRC = $(PROJ_ROOT)/ext/littlefs

# List of all littlefs sources
LITTLEFSSRC := $(LITTLEFS_SRC)/lfs.c                    \
               $(LITTLEFS_SRC)/lfs_util.c

# Required include directories
LITTLEFSINC := $(LITTLEFS_SRC)

# Shared variables
ALLCSRC     += $(LITTLEFSSRC)
ALLINC      += $(LITTLEFSINC)
