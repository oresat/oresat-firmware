# Source files located under $(LOCAL_SRC) are automatically added.
ifeq ($(LOCAL_SRC),)
  LOCAL_SRC := ./source/
endif

rwildcard    = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
LOCALCSRC    := $(call rwildcard,$(LOCAL_SRC),*.c)
LOCALCPPSRC  := $(call rwildcard,$(LOCAL_SRC),*.cpp)
LOCALASMSRC  := $(call rwildcard,$(LOCAL_SRC),*.s)
LOCALXASMSRC := $(call rwildcard,$(LOCAL_SRC),*.S)
LOCALINC     := $(sort $(dir $(call rwildcard,$(LOCAL_SRC),*)))

# Shared variables.
ALLCSRC     += $(LOCALCSRC)
ALLCPPSRC   += $(LOCALCPPSRC)
ALLASMSRC   += $(LOCALASMSRC)
ALLXASMSRC  += $(LOCALXASMSRC)
ALLINC      += $(LOCALINC)
