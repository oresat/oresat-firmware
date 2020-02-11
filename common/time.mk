# Required libraries for time management
#include $(PROJ_SRC)/library.mk

# List of all the time subsystem source files
TIMESRC := $(PROJ_SRC)/time.c

# Required include directories
TIMEINC := $(PROJ_SRC)/include

# Shared variables
ALLCSRC += $(TIMESRC)
ALLINC  += $(TIMEINC)
