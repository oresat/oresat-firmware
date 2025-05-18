# List of all the VERSION device files.
VERSIONSRC := $(PROJ_SRC)/version.c

# Required include directories
VERSIONINC := $(PROJ_SRC)/include

# Shared variables
ALLCSRC += $(VERSIONSRC)
ALLINC  += $(VERSIONINC)
