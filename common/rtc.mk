# Required libraries for RTC and time management
#include $(PROJ_SRC)/library.mk

# List of all the time subsystem source files
RTCSRC := $(PROJ_SRC)/rtc.c

# Required include directories
RTCINC := $(PROJ_SRC)/include

# Shared variables
ALLCSRC += $(RTCSRC)
ALLINC  += $(RTCINC)
