.section .text
.global _start

_start:
    la sp, _stack_top
    call main
    j .
