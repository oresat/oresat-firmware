##############################################################################
# Multi-project makefile rules
#

all:
	@echo
	@echo === Building for STM32F042K6-Nucleo32 ================================
	@make --no-print-directory -f Makefile-ST_NUCLEO32_F042K6 all
	@echo ====================================================================
	@echo
	@echo === Building for STM32F446RE-Nucleo64 ================================
	@make --no-print-directory -f Makefile-ST_NUCLEO64_F446RE all
	@echo ====================================================================
	@echo

clean:
	@echo
	-@make --no-print-directory -f Makefile-ST_NUCLEO32_F042K6 clean
	@echo
	-@make --no-print-directory -f Makefile-ST_NUCLEO64_F446RE clean
	@echo

#
##############################################################################
