TOPTARGETS := all clean

SUBDIRS := $(wildcard src/f0/*/.)
SUBDIRS += $(wildcard src/l4/*/.)
SUBDIRS += $(wildcard src/f4/*/.)

$(TOPTARGETS): $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: $(TOPTARGETS) $(SUBDIRS)
