# Battery App
## Summary
This application monitors and reports over CAN the telemetry related to
the two dual cell battery packs on the battery card. Data include:

- the SOC (state of charge, a percentage)
- temperature
- current draw
- voltage per cell
- time to full and time to empty
- status bit flags

## Compile-time options
In the lab, it is useful to enable debug logging over serial. This is done
by defining the C macro DEBUG_PRINT in the Makefile:

`UDEFS = -DCO_VERSION_MAJOR=4 -DDEBUG_PRINT=1`

Detailed logging of battery history can be enabled by uncommenting the following at the top
of batt.c:

`//#define VERBOSE_DEBUG 1`

Battery history includes both the MAX17205 life logging data (up to 203 snapshots of NV registers 1A0h to 1AFh; see datasheet),
as well as our custom periodic logging of MAX17205_AD_MIXCAP and MAX17205_AD_REPCAP used for reset recovery.

Two more options are used for a special build to be run in the lab:

```
#define ENABLE_NV_MEMORY_UPDATE_CODE 1
...
#define ENABLE_LEARN_COMPLETE 1
```

Use these on a new battery pack to get the MAX17205 fuel gauge chips through multiple full charge / discharge learning cycles.
This is needed for them to learn the battery characteristics for proper operation of the ModelGauge m5 algorithm's coulomb counting mode.
Without this step, the default, much less accurate voltage-based mode is used by the MAX17205. The latter is what was used on Oresat 0 and Oresat 0.5, 
resulting in very untrustworthy battery telemetry.

**Note: the MAX17205 has a very limited number of NV (non-volatile) memory write cycles: 7 total.**

## Shortcomings of original Oresat battery app
- original code was not using all register values from the Maxim Wizard software with no explanation as to why
- no learning cycles performed -- full charge/discharge never done to tune the fuel guage prior to launch
- lots of duplicate code differing only in pack1 vs. pack2
- magic numbers in code
- no use of firmware reset to allow for runtime experimentation with register values

## Shortcomings of v2.1 and v3.0 battery boards
- cells 1 and 2 in each pack tend to get out of balance quickly (at least in the lab)
- unexpected and uninvestigated charge behavior observed on the EU (v3.0 pack) between packs 1 and 2
- Vov (overvoltage) cutoff is slightly too low at 4.1v but cells are only full at 4.2v

## Limitations of the MAX17205
- the datasheet is large, complex, incomplete, and not well organized -- important info also in various app notes
- ModelGauge m5 EZ model is not well documented -- there is no clear list of how to get the chip in that mode
- works best if one pays Maxim to generate custom characteristic data for the specific cells being used (cost-prohibitive)
- built-in ModelGauge m5 EZ battery model does not fit Oresat's cells well
- acceptable performance of EZ mode requires the chip to reach learn level 7, which requires 7 full in-lab charge/discharge cycles with NO resets the entire training period, followed by writing to NV registers
- only 7 writes possible to the nonvolatile registers; this mandates adding code to do runtime volatile configuration when performing experiments
- Coulomb-based fuel gauge tracking does not tolerate our daily reset behavior in orbit (meant to recover from hard-faults in orbit)
- battery balancing circuit is limited to operating only when close to the end of a charge cycle

## Recovery from limitations
- fully train and store to EV with:
  - `MAX17205_AD_NLEARNCFG` = 7 (learning complete)
  - `MAX17205_AD_NFULLCAPNOM` = 0x1A22 (higher than Wizard value of 0x1794; found during full learning on 2 battery boards; redo for Oresat 1.0)
  - `MAX17205_AD_MIXCAP` and `MAX17205_AD_REPCAP` = 2600 mAh (rated full capacity of the cells we use)
- add logging of `MAX17205_AD_MIXCAP`, `MAX17205_AD_REPCAP`, number of reset cycles, and current cycle run time to a page in flash on the STM processor
- on reset use last good history entry to restore coulomb-counting
- balancing may or may not be a long-term problem in orbit; need latest Oresat 0.5 telemetry for analysis

### Battery characteristic learning procedure
- battery card must be setup in a standalone mode:
  - connect external 3.3v supply to `OPD_PWR`
  - connect a USB to I2C dongle to the Oresat Power Domain Controller MAX7310's pins using `OPD_SDA`, `OPD_SCL`, and `GND` to enable Vbusp
  - write the MAX7310's direction register and the output register:

    1. register 0x03 --> 0x07 (bits 0, 1, 2 = input, remaining bits = output)
    2. register 0x01 --> 0 for reset / power off
    3. register 0x01 --> 0x98 for ON/OFF = 1, CB-RESET = 1, UART_EN = 1

  - no resetting of the processor is allowed or learning progress is entirely lost
  - no totally full discharge is allowed below Vuv = 2.5v (under voltage) or processor will reset
  - set an external supply to Vbus for charging to 4.2v with current limited to 1.25A per pack (2.5A total)
  - connect a dummy load to Vbus, such as a 20 ohm 10 watt power resistor, to drain the pack in a few hours rather than days
  - cycle pack through:

    1. from fully charged (indicated when time to full jumps from 0 to 368634 and SOC = 100%)
    2. to nearly fully discharged (Vbatt in either pack <= 2.85v; `Batteries are critically low` in terminal)
    3. observe `MAX17205_AD_LEARNCFG` debug output and confirm it increments from 0 to 7 over the 7 charge/discharge cycles
    4. when learning complete, debug output = `Learning state set = 7`
    5. `Write NV memory on MAX17205 for pack (1 or 2) ? y/n?` will appear; you have 15 seconds to say `y` otherwise it will not be written

- cells should be well-balanced before starting; do so by manually charging each cell using their test points while OPD is shut down / safety switches closed
- TODO: automation of USB-interface power supply and scripting of learning cycles would be very helpful, but must be monitored for fire safety reasons

### Daily satellite reset recovery
- on reset:
  - read from logging page
  - restore newest entry that also passes CRC checks
  - this ensures the fuel gauge restarts tracking where it left off
- a limitation is that a long off time due to prelaunch processing or simply leaving the battery board on the shelf will result in loss of accuracy
- the voltage-based fuel gauge should eventually correct the discrepancy (TODO: verify this)

## Volatile vs. Non-volatile registers
The MAX17205 has two sets of registers: RAM-based vs. Non-volatile (NV).
The RAM-based registers, sometimes called NV-RAM registers or shadow registers, can change values over time while running.
The Non-volatile registers are loaded into the RAM-based registers at hardware reset and used as a starting point.

Because the number of write cycles allowed to the NV registers is limited to 7, writing should only be done when certain that the values being written are correct.
This makes NV writes useless for experimentation.

Luckily, the MAX17205 has both a hardware and a firmware reset.

- hardware reset loads RAM registers from NV registers
- firmware reset simply restarts the ModelGauge m5 algorithm with the current RAM registers left alone

We leverage the firmware reset functionality in the `nv_ram_write()` function to make temporary changes to the registers without wasting NV write cycles.
This function first validates the current contents. If they match, then nothing further is done. Otherwise the registers are written and then validated again.
This will be useful in orbit to change behavior if either the NV writes are already exhausted, or we do not want to risk using them.

# Application Main Directory
## Directory Structure
This folder contains the root of an applications sources. It contains
several files and folders:

* [main.c](main.c): The main program file called by ChibiOS. Contains
  initialization code and registers threads and functions.
* [Makefile](Makefile): The main Makefile for the application. Sources
  all other build files.
* [cfg](cfg): The directory containing ChibiOS's configuration files for
  this application.
* [source](source): The directory where application code is put.
  Everything within this directory automatically builds.
