##############################################################################
# Build global options
# NOTE: Can be overridden externally.
#

# Compiler options here.
ifeq ($(USE_OPT),)
  USE_OPT = -Og -ggdb -falign-functions=16
endif

# C specific options here (added to USE_OPT).
ifeq ($(USE_COPT),)
  USE_COPT =
endif

# C++ specific options here (added to USE_OPT).
ifeq ($(USE_CPPOPT),)
  USE_CPPOPT = -fno-rtti
endif

# Enable this if you want the linker to remove unused code and data.
ifeq ($(USE_LINK_GC),)
  USE_LINK_GC = yes
endif

# Linker extra options here.
ifeq ($(USE_LDOPT),)
  USE_LDOPT =
endif

# Enable this if you want link time optimizations (LTO).
ifeq ($(USE_LTO),)
  USE_LTO = yes
endif

# Enable this if you want to see the full log while compiling.
ifeq ($(USE_VERBOSE_COMPILE),)
  USE_VERBOSE_COMPILE = no
endif

# If enabled, this option makes the build process faster by not compiling
# modules not used in the current configuration.
ifeq ($(USE_SMART_BUILD),)
  USE_SMART_BUILD = yes
endif

#
# Build global options
##############################################################################

##############################################################################
# Architecture or project specific options
#

# Stack size to be allocated to the Cortex-M process stack. This stack is
# the stack used by the main() thread.
ifeq ($(USE_PROCESS_STACKSIZE),)
  USE_PROCESS_STACKSIZE = 0x100
endif

# Stack size to the allocated to the Cortex-M main/exceptions stack. This
# stack is used for processing interrupts and exceptions.
ifeq ($(USE_EXCEPTIONS_STACKSIZE),)
  USE_EXCEPTIONS_STACKSIZE = 0x100
endif

# Enables the use of FPU (no, softfp, hard).
ifeq ($(USE_FPU),)
  USE_FPU = no
endif

# FPU-related options.
ifeq ($(USE_FPU_OPT),)
  USE_FPU_OPT = -mfloat-abi=$(USE_FPU) -mfpu=fpv4-sp-d16
endif

#
# Architecture or project specific options
##############################################################################

##############################################################################
# Project, target, sources and paths
#

# Define project name here
PROJECT   = app_solar

# Target settings.
MCU       = cortex-m0
BOARD     = SOLAR_V5

# Project sources.
PROJ_ROOT = ../../..
APP_ROOT  = .
PROJ_SRC  = $(PROJ_ROOT)/common
PROJ_INC  = $(PROJ_SRC)/include
TOOLCHAIN = $(PROJ_ROOT)/toolchain

# Imported source files and paths.
CHIBIOS  := $(PROJ_ROOT)/ext/ChibiOS
CONFDIR  := $(APP_ROOT)/cfg
BUILDDIR := $(APP_ROOT)/build
DEPDIR   := $(APP_ROOT)/.dep
ODDIR    := $(APP_ROOT)/od

# Board specific directories.
BOARDDIR  = $(PROJ_ROOT)/boards/$(BOARD)

# Enable bootloader
ifeq ($(USE_BOOTLOADER),)
  USE_BOOTLOADER = yes
endif

# generate OD.c/OD.h from oresat-configs
$(shell oresat-configs canopennode od.yaml $(PROJ_SRC)/od.yaml -d $(ODDIR))
ifneq ($(.SHELLSTATUS),0)
  $(error oresat-configs canopennode failed to generate an Object Dictionary)
endif
# add them
ALLCSRC += $(ODDIR)/OD.c
ALLINC += $(ODDIR)

# Project specific files.
include $(PROJ_SRC)/oresat.mk
include $(PROJ_SRC)/ina226.mk

# Licensing files.
include $(CHIBIOS)/os/license/license.mk
# Startup files.
include $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC/mk/startup_stm32f0xx.mk
# HAL-OSAL files (optional).
include $(CHIBIOS)/os/hal/hal.mk
include $(CHIBIOS)/os/hal/ports/STM32/STM32F0xx/platform.mk
include $(BOARDDIR)/board.mk
include $(CHIBIOS)/os/hal/osal/rt-nil/osal.mk
# RTOS files (optional).
include $(CHIBIOS)/os/rt/rt.mk
include $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/mk/port_v6m.mk
# Auto-build files in ./source recursively.
include $(CHIBIOS)/tools/mk/autobuild.mk
# Other files (optional).
include $(CHIBIOS)/os/hal/lib/streams/streams.mk

# Define linker script file here
ifeq ($(USE_BOOTLOADER),yes)
  LDSCRIPT= $(PROJ_ROOT)/ld/STM32F091xC-app.ld
else
  LDSCRIPT= $(PROJ_ROOT)/ld/STM32F091xC-app-noboot.ld
endif

# C sources that can be compiled in ARM or THUMB mode depending on the global
# setting.
CSRC = $(ALLCSRC) \
       $(TESTSRC) \
       main.c

# C++ sources that can be compiled in ARM or THUMB mode depending on the global
# setting.
CPPSRC = $(ALLCPPSRC)

# List ASM source files here.
ASMSRC = $(ALLASMSRC)

# List ASM with preprocessor source files here.
ASMXSRC = $(ALLXASMSRC)

# Inclusion directories.
INCDIR = $(CONFDIR) $(ALLINC) $(TESTINC)

# Define C warning options here.
CWARN = -Wall -Wextra -Wundef -Wstrict-prototypes -Wsystem-headers

# Define C++ warning options here.
CPPWARN = -Wall -Wextra -Wundef

#
# Project, target, sources and paths
##############################################################################

##############################################################################
# Start of user section
#

# List all user C define here, like -D_DEBUG=1
UDEFS = -D_XOPEN_SOURCE=0 -D_FORTIFY_SOURCE=0 -D__ARM_FP=0 -DDEBUG_PRINT -DFW_VERSION=\"$(shell git describe --always)\"

# Define ASM defines here
UADEFS =

# List all user directories here
UINCDIR = $(PROJ_INC)

# List the user directory to look for the libraries here
ULIBDIR = $(PROJ_SRC)

# List all user libraries here
ULIBS =

#
# End of user section
##############################################################################

##############################################################################
# Common rules
#

RULESPATH = $(CHIBIOS)/os/common/startup/ARMCMx/compilers/GCC/mk
include $(RULESPATH)/arm-none-eabi.mk
include $(RULESPATH)/rules.mk
include $(TOOLCHAIN)/toolchain.mk

#
# Common rules
##############################################################################

##############################################################################
# Custom rules
#

#
# Custom rules
##############################################################################
