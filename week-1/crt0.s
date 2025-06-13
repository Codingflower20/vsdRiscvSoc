.section .text
.global _start

_start:
    la sp, _stack_top
    call main
    j .

.section .bss
.space 4096
_stack_top:
