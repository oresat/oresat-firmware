SECTIONS
{
  
  .coderam : 
  {
    . = ALIGN(4);
    __coderam_init__ = LOADADDR(.coderam);
    __coderam_base__ = .;
	*(.coderam*)
    __coderam_end__ = .;
  } > CODE_RAM AT > CODE_RAM_LMA
}

/* get size of section */
__coderam_size__ = __coderam_end__ - __coderam_base__;
