# Required libraries for filesystem

LITTLEFS_SRC = $(PROJ_ROOT)/ext/littlefs

# List of all littlefs sources
FSSRC := $(LITTLEFS_SRC)/lfs.c      \
         $(PROJ_SRC)/lfs_util.c     \
         $(PROJ_SRC)/fs.c

# Required include directories
FSINC := $(PROJ_SRC)/include        \
	     $(LITTLEFS_SRC)

# Shared variables
ALLCSRC += $(FSSRC)
ALLINC  += $(FSINC)
