.section .text
.global _start
_start:
    la sp, _stack_top     # set stack pointer
    call main             # call main
    j .                   # infinite loop if main returns

.section .bss
.space 4096
_stack_top:
