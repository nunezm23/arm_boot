# arm_boot
Basic implementation for a boot sequence for ARM microcontroller from scratch.



## Command to compile the file "myprogram.c"

arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -std=c11 -g -O0 -c myprogram.c -o myprogram.o

![Assembly code for .o file](docs/images/asm_o.png)


![Size for file](docs/images/asm_o_size.png)


![Fails when trying to compile .elf](docs/images/elf_warning.png)


![Execuitable Linked Formart Size](docs/images/elf_size.png)

Sections:
* .text: the code(instructions)
* .data: initialized variables (Flash section that then its copy to RAM at runtime)
* .bss unitialized variables (zero - RAM section)
* .rodata constants