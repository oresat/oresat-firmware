app_diode

ChibiOS firmware for the SWIR diode test card

This app is controlled and monitored via the oresat-configs CANOpen object dictionary. These 
entries are:

dtc - diode test card
	ctrl - the control object
		this is an 8-bit unsigned object that  accesses control functions based on their index into
		an array of function pointers:
		1 dtc_dacStart - starts the dac driver (called on app startup)
		2 dtc_dacStop - stops the dac driver (called on app startup)
		3 dtc_gptStart - starts the gpt driver for the adc (called on app startup)
		4 dtc_gptStop - stops the gpt driver
		5 dtc_adcStart - starts (called on app startup)
		6 dtc_adcStop - stops the adc driver
		7 dtc_muxEnable - enables the diode mux (logic low, called on app startup)
		8 dtc_muxDisable - disables the diode mux (logic high)
	mux_select - selects a diode (unsigned value 0 - 7)
	dac	- sets the dac with a 12 bit unsigned value 0 - 4095
	status - status object. this is a wip
	error	- error object. this is a wip

adcsample - adc diode feedback and temperature sensor. these are 12 bit unsigned values 0 - 4095
	led_current	
	led_swir_pd_current	
	uv_pd_current	
	tsen - internal mcu temperature sensor
-------------------------------------

oresat-configs and CANopen OD cli example usage:

to select a diode at mux_select 5
oresat-configs sdo can0 diode_test w dtc mux_select 5

to set the DAC to 4095
oresat-configs sdo can0 diode_test w dtc dac 4095

------------------------------------

app_diode provides a serial dump of the OD
serial setup example:

picocom -b 115200 -l /dev/ttyACM0
or
picocom -b 115200 -l /dev/serial/by-id/usb-STMicroelectronics_STLINK-V3_0036002F3431510837393937-if02

