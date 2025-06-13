.section .text
.globl _start
_start:
    la sp, _stack_top        # Initialize stack pointer

    # Copy .data section from Flash to RAM
    la a0, _data_load
    la a1, _data_start
    la a2, _data_end
1:
    beq a1, a2, 2f
    lw t0, 0(a0)
    sw t0, 0(a1)
    addi a0, a0, 4
    addi a1, a1, 4
    j 1b
2:

    # Zero initialize .bss section
    la a0, _bss_start
    la a1, _bss_end
3:
    beq a0, a1, 4f
    sw zero, 0(a0)
    addi a0, a0, 4
    j 3b
4:

    # Call main()
    call main

    # Loop forever after main returns
    j .
