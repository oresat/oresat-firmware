# SI41XX_SYNTH

This code bitbangs synthesizer SI4123 to generate specific RF outputs.
This code provides an chibios shell interface to update the synthesizers registers or set them up for specific frequencies.

This code can be used with Si41xx family. But please ensure that defaults values are populated appropriatly for specific chip. This code tested with si4123.

See the [Operating Guide](Operating-Guide.pdf) for instructions on how to program a Si41xx synthesizer evaluation board with this app and the NUCLEO-F446RE development board.


# Registers and Functionality for SI41xx family

    Part    RF1  RF2   IF
    Si4133   X    X    X
    Si4123   X    -    X
    Si4122   -    X    X
    Si4113   X    X    -
    Si4112   -    -    X


# Summary of default values for Si4123:

    Reg    17                    0   Addr   Notes
    0       00 0011 0000 0000 0100   0000   Main config
    1       00 0000 0000 0000 0000   0001   P.D. Gain
    2       00 0000 0000 0000 0011   0010   Enable outputs
    3       00 0000 1001 1110 0010   0011   N for RF1 (2530)
    4       00 0000 0000 0000 0000   0100   N for RF2 (0)
    5       00 0000 0011 0110 1001   0101   N for IF (873)
    6       00 0000 0000 0010 0000   0110   R for RF1 (32)
    7       00 0000 0000 0000 0000   0111   R for RF2 (0)
    8       00 0000 0000 0010 0000   1000   R for IF (32)


FYI: EXTERNAL OSC REFERENCE = 16.000 MHz

NOTES FOR DEFAULTS:
- AUXSEL set to lock detect
- IFDIV disabled
- LPWR disabled
- AUTOPDB disabled
- AutoKp enabled
- Registers 4 and 7 for RF2 are not needed for Si4123
- For synthesizers with RF1 and RF2 included, the selected
  output is determined by the last N/R reg written.


# Functionality:
Breakout specific main parameter bits with defaults.
  See p. 21 from datasheet for concatenation/padding.
  
    RFPWR (1)   =  0  (not used)
    AUTOKP (1)  =  1  (enabled)
    AUTOPDB (1) =  0  (disabled)
    LPWR (1)    =  0  (disabled)
    IFDIV (2)   = 00  (no divide)
    AUXSEL (2)  = 11  (lock detect)
    KP1 (2)     = 00  (not used when AUTOKP)
    KP2 (2)     = 00  (not used when AUTOKP)
    KPI (2)     = 00  (not used when AUTOKP)
    PDRB (1)    =  1  (enable RF output)
    PDIB (1)    =  1  (enable IF output)
Breakout specific N and R parameter bits with defaults.
  See p. 21 from datasheet for concatenation/padding.
  These are evaluated defaults using equations below.
  
    NRF1 (18) = 000000100111100010  (2530)
    NRF2 (17) = 000000000000000000  (0)
    NIF (16)  =   0000001101101001  (873)
    RRF1 (13) =      0000000100000  (32)
    RRF2 (13) =      0000000000000  (0)
    RIF (13)  =      0000000100000  (32)
Non-register related variables with defaults (decimal values)
  Note: Fouts in MHz and Pdets in kHz.
  
    FREF (int)      =   16
    FOUTRF1 (float) = 1265
    FOUTRF2 (float) =    0
    FOUTIF (float)  =  436.5
    PDETRF1 (int)   =  500
    PDETRF2 (int)   =    0
    PDETIF (int)    =  500
Equations for N and R:

    RRF1 = FREF * 1000 / PDETRF1
    RRF2 = FREF * 1000 / PDETRF2
    RIF  = FREF * 1000 / PDETIF
    NRF1 = FOUTRF1 * RRF1 / FREF
    NRF2 = FOUTRF2 * RRF2 / FREF
    NIF  = FOUTIF * RIF / FREF
Equation Notes:

  - Calculate N values only if phase detector not changed
  - Calculate R first and N second if phase detector changed
Evaluated Defaults:

  - RF1 output = 1265 MHz
  - RF2 output = disabled
  - IF output  = 436.5 MHz

  
#  Chibios shell functions available 

    reg:   Update registers,Usage reg <register address in decmal/hexadecimal> <register value in binary/decimal/hexadecimal>
    rf1:   Update RF1 registers,Usage: rf1 <frequency in KHz> <Phase detector in Khz>
    rf2:   Update RF2 registers,Usage: rf2 <frequency in KHz> <Phase detector in Khz>
    if:   Update IF registers,Usage: ifr <frequency in KHz> <Phase detector in Khz>
    help:  provides list of commands
    ?:     provides list of commands 
