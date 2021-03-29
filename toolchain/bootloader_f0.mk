DATE=$(shell date +%Y%m%d)
POST_MAKE_ALL_RULE_HOOK:
	python3 $(TOOLCHAIN)/f0_pack_image.py $(BUILDDIR)/$(PROJECT).bin $(BUILDDIR)/$(PROJECT).crc32.bin $(DATE)
	@# Convert the crc32 bin file to a hex file that can be written to the STM32F0 with 'make write'
	srec_cat $(BUILDDIR)/$(PROJECT).crc32.bin -binary -offset 0x0800A000 -o $(BUILDDIR)/$(PROJECT).bin.hex -Intel -Line_Length 44
	mv $(BUILDDIR)/$(PROJECT).hex $(BUILDDIR)/$(PROJECT).origional.hex
	cp $(BUILDDIR)/$(PROJECT).bin.hex $(BUILDDIR)/$(PROJECT).hex
