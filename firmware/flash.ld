ENTRY(Reset_Handler)

MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 32K
  RAM (rwx)   : ORIGIN = 0x20000000, LENGTH = 4K
}
_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS {
  /* Interrupt vector table at the beginning of flash */
  .isr_vector ORIGIN(FLASH) : {
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } >FLASH
  /* Then the text section goes into flash */
  .text : {
    . = ALIGN(4);
    *(.text)
    *(.text*)
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  } >FLASH
  /* The data section gets a VMA in RAM but an LMA in flash */
  _sidata = .;
  .data : AT ( _sidata ) {
    . = ALIGN(4);
    _sdata = .;
    *(.data)
    *(.data*)
    . = ALIGN(4);
    _edata = .;
  } >RAM
  /* The BSS goes into RAM */
  .bss : {
    . = ALIGN(4);
    _sbss = .;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } >RAM
}
