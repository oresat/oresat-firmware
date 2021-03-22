# List of all the PDU device files.
PDUSRC  := $(PROJ_SRC)/pdu.c

# Required include directories
PDUINC  := $(PROJ_SRC)/include

# Shared variables
ALLCSRC += $(PDUSRC)
ALLINC  += $(PDUINC)
