# Source files located under $(PROJ_SRC) are automatically added.
rwildcard    = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
PROJCSRC    := $(call rwildcard,$(PROJ_SRC),*.c)
PROJCPPSRC  := $(call rwildcard,$(PROJ_SRC),*.cpp)
PROJASMSRC  := $(call rwildcard,$(PROJ_SRC),*.s)
PROJXASMSRC := $(call rwildcard,$(PROJ_SRC),*.S)
PROJINC     := $(sort $(dir $(call rwildcard,$(PROJ_SRC),*)))

# Shared variables.
ALLCSRC     += $(PROJCSRC)
ALLCPPSRC   += $(PROJCPPSRC)
ALLASMSRC   += $(PROJASMSRC)
ALLXASMSRC  += $(PROJXASMSRC)
ALLINC      += $(PROJINC)
