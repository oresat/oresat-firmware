# List of all the AX5043 device files.
MMC5883MASRC := $(PROJ_SRC)/mmc5883ma.c

# Required include directories
MMC5883MAINC := $(PROJ_SRC)/include

# Shared variables
ALLCSRC += $(MMC5883MASRC)
ALLINC  += $(MMC5883MAINC)
