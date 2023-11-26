# Manually Setting Node IDs

## Background

This references the [STM32F09x Reference Manual].

In the code, in `oresat-firmware/common/oresat.c`, is:

```c
node_id = ((FLASH->OBR & FLASH_OBR_DATA0_Msk) >> FLASH_OBR_DATA0_Pos)
```

We store the Node IDs in the "Flash Option Byte Register" (See RM00091 Reference
Manual - 3.5.7 Flash Option byte register (FLASH_OBR)).

According to "2.2.2 Memory map and register boundary addresses": the base
address for the FLASH registers is 0x40022000 - 0x400223FF (1 KB) = FLASH
interface

According to "3.5.9 Flash register map", FLASH_OBR is offset 0x1C which is the
Option Byte Register.
Inside that 32 bit word, we want the 3rd byte which is "DATA0".

In `oresat-firmware/ext/ChibiOS/os/common/ext/ST/STM32F0xx/stm32f091xc.h` are
these definitions:

```c
__IO uint32_t OBR;  /*!<FLASH option bytes register, Address offset: 0x1C */
#define FLASH_OBR_DATA0_Pos   (16U)                                
#define FLASH_OBR_DATA0_Msk   (0xFFU << FLASH_OBR_DATA0_Pos)    /*!< 0x00FF0000 */
#define FLASH_OBR_DATA0       FLASH_OBR_DATA0_Msk               /*!< Data0 */
```

... which seem to line up with everything else.

[This website](https://iwasz.pl/electronics/2020-07-29-stm32f042-option-bytes-linux/)
gives a great overview of this!

According to "4.1.2 User data option byte", the flash memory address is 0x1FFF
F804 = nData1:Data1:nData0:Data0

## OpenOCD

In the directory `oresat-firmware/toolchain`, you can run:

```bash
openocd -f ../boards/PROTOCARD_V4/oocd.cfg
```

Run `halt`. This seems to be important, we don’t want the processor doing weird things.

Read all 32 bit option bytes registers:

```bash
mdw 0x1ffff800 4
0x1ffff800: 00ff55aa 00ff00ff 00ff00ff 00ff00ff 
```

We can see 0x1ffff804 is 00ff, which is our nData0:Data0.

Check that the flash is locked:

```bash
mdw 0x40022010
0x40022010: 00000080 
```

Unlock the flash directly performing the unlocking sequence on the FLASH_KEYR
(0x40022004) register.

```bash
mww 0x40022004 0x45670123
mww 0x40022004 0xCDEF89AB
```

Reassure that the flash is unlocked. Read the FLASH_CR:

```bash
mdw 0x40022010
0x40022010: 00000000 
```

Unlock option bytes for writing (which is described in the reference manual as
setting the OPTWRE bit in the FLASH_CR).

```bash
mww 0x40022008 0x45670123
mww 0x40022008 0xCDEF89AB
mdw 0x40022010           
0x40022010: 00000200
```

Clear option bytes (they are stored in the FLASH after all).

```bash
mww 0x40022010 0x00000220
mww 0x40022010 0x00000260
```

Enable programming by setting FLASH_CR.OPTPG:

```bash
mww 0x40022010 0x00000210
mdw 0x40022010
0x40022010: 00000210
```

So after doing all the unlocky things, we can write the new option register.

Here’s the example, for Battery 0, which is Node ID 4. You have to put in a
half word with the ID in the low byte (e.g.0x04), and the complement of the
ID in the high byte (e.g., 0xfb).

ACS board Node ID 0x38: 0xc738
Battery board Node ID 0x04: 0xfb04
Solar Module 3 Node ID 0x18: 0xe718
Solar Module 1 Node ID 0x10: 0xef10
Solar Module 2 Node ID 0x14: 0xe

```bash
mwh 0x1ffff800 0x55AA
mwh 0x1ffff802 0x00ff
mwh 0x1ffff804 0xfb04
mwh 0x1ffff806 0x00ff
mwh 0x1ffff808 0x00ff
mwh 0x1ffff80a 0x00ff
mwh 0x1ffff80c 0x00ff
mwh 0x1ffff80e 0x00ff 
```

Now we can check this worked:

```bash
mdw 0x1ffff800 4
0x1ffff800: 00ff55aa 00fffb04 00ff00ff 00ff00ff 
```

Now power cycle the board, and re-check that this change stuck.

## Verifying for Realsies

Finally, you should see that canopen-monitor actually reads the changed
board/card/solar module as the right device.

[STM32F09x Reference Manual]: https://www.st.com/resource/en/reference_manual/dm00031936-stm32f0x1-stm32f0x2-stm32f0x8-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf
