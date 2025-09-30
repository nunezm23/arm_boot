/* stm32l476rg.ld
   Basic linker script for bootloader at start of flash.
   For this purpose, I'm use a STM32L476RG.
   This microcontroller have 1MB flash, 128KB SRAM1 and 32KB SRAM2.
   WARNING: I'm not sure if this is correct, i'm learning :D
   The comments are what i have found through my research about what each thing means. D:
*/

MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1M   /* Full device flash (linker only needs origin) */
  RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 96K  /* SRAM1: main RAM; keep SRAM2 for special uses. */
}

SECTIONS
{
    .text :
    {
        _start_text = ORIGIN(FLASH);        /* Optional explicit start marker */
        KEEP(*(.isr_vector))                /* Keep the vector table at FLASH base */
        /* Reserve the first 0x400 bytes for a vector/bootloader area */
        . = ORIGIN(FLASH) + 0x400;          /* Start placing the rest at flash-base+0x400 */
        KEEP(*(.utils))                     /* Helper functions (optional) */
        KEEP(*(.text*))                     /* Compiled C functions (main program)*/
        *(.rodata*)                         /* Compiler stores constants that never change at runtime. */
        . = ALIGN(4);                       /* Ensures the location counter is a multiple of 4 before moving on to the next section. */
        _end_text = .;                      /* Align the location counter to a 4-byte boundary. */
    } > FLASH                               /* Request that the .text VMA be in the FLASH memory region. */

    _stored_data = .;                   /* Start of the memory block in Flash that holds the initial values of global variables.*/

    .data : AT (_stored_data)
    {
        _start_data = .;            /* Start location counter in RAM. */
        KEEP(*(.data*))             /* Collect all .data sections from object files. */
        . = ALIGN(4);               /* Align the end of .data to the next 4-byte boundary. */
        _end_data = .;              /* End of .data in RAM. */
    } > RAM                         /* .data section executes from RAM. */

    .bss (NOLOAD) : 
    {
        _start_bss = .;             /* Save the current location counter. */
        *(.bss*)                    /* Copies all input object-file whose name starts with .bss into this output .bss*/
        *(COMMON)                   /* Here the linker puts common symbols. */
        . = ALIGN(4);               /* Align the location counter to a 4-byte boundary after placing the .bss contents. */
        _end_bss = .;               /* Current location counter to define the end of .bss in RAM. */
        _end = .;                   /* Generic _end symbol. */
    } > RAM
    . = ALIGN(4);                   /* It makes sure any subsequent placement begins on a 4-byte boundary. */
}

END_STACK = ORIGIN(RAM) + LENGTH(RAM); /* This computes the top address of the RAM region: the RAM base + RAM size. */