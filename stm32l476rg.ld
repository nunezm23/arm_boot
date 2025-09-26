/* stm32l476rg.ld
   Basic linker script for bootloader at start of flash.
   For this purpose, I'm use a STM32L476RG.
   This microcontroller have 1MB flash, 128KB SRAM1 and 32KB SRAM2
*/

MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1M   /* full device flash (linker only needs origin) */
  RAM (xrw)  : ORIGIN = 0x20000000, LENGTH = 96K  /* SRAM1: main RAM; keep SRAM2 for special uses */
}

SECTIONS
{
    .text :
    {
        _start_text = .;
        KEEP(*(.isr_vector))
        . = 0x400;
        KEEP(*(.utils))
        KEEP(*(.text*))
        *(.rodata*)
        . = ALIGN(4);
        _end_text = .;
    } > FLASH

    _stored_data = .;

    .data : AT (_stored_data)
    {
        _start_data = .;
        KEEP(*(.data*))
        . = ALIGN(4);
        _end_data = .;
    } > RAM

    .bss (NOLOAD) : 
    {
        _start_bss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _end_bss = .;
        _end = .;
    } > RAM
    . = ALIGN(4);
}

END_STACK = ORIGIN(RAM) + LENGTH(RAM);