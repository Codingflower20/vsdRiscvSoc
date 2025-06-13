/* Linker script for RV32 baremetal programs on QEMU virt machine */
ENTRY(_start)

MEMORY {
    RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 128K
}

SECTIONS {
    /* Code section */
    .text : {
        *(.text.init)      /* Startup code first */
        *(.text .text.*)   /* All other code */
    } > RAM

    /* Read-only data */
    .rodata : {
        *(.rodata .rodata.*)
        . = ALIGN(4);
    } > RAM

    /* Initialized data */
    .data : {
        __data_start = .;
        *(.data .data.*)
        *(.sdata .sdata.*) /* Small data */
        . = ALIGN(4);
        __data_end = .;
    } > RAM

    /* Uninitialized data (BSS) */
    .bss : {
        __bss_start = .;
        *(.bss .bss.*)
        *(.sbss .sbss.*)   /* Small BSS */
        . = ALIGN(4);
        __bss_end = .;
    } > RAM

    /* Stack starts at end of RAM and grows downward */
    .stack : {
        . = ALIGN(16);
        __stack_bottom = .;
        . += 4K;           /* 4KB stack */
        __stack_top = .;
    } > RAM

    /* Symbols for startup code */
    _end = .;
    PROVIDE(end = .);
}
