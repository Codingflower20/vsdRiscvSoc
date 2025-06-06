# Week-1 tasks
This contains progress and solutions of week 1 tasks.
## 1- Setup ToolChain
Extracted the ToolChain using 
```bash
tar -xzf
```
## 2- Hello.C
Created the Hello.c file
```C
// hello.c
#include <stdio.h>

int main() {
    printf("Hello, RISC-V!\n");
    return 0;
}

```
Compiled the C file using
```bash
riscv32-unknown-elf-gcc -o hello.elf hello.c
```
verified using 
```bash
file hello.elf
```
Output 
```bash
hello.elf: ELF 32-bit LSB executable, UCB RISC-V, RVC, soft-float ABI, version 1 (SYSV), statically linked, not stripped
```
## 3- Hello.S
Converted the C code into Assembly language
```bash
riscv32-unknown-elf-gcc -S -O0 hello.c
```
contents of the Hello.S
```c
  .file   "hello.c"
        .option nopic
        .attribute arch, "rv32i2p1_m2p0_a2p1_c2p0"
        .attribute unaligned_access, 0
        .attribute stack_align, 16
        .text
        .section        .rodata
        .align  2
.LC0:
        .string "Hello, RISC-V!"
        .text
        .align  1
        .globl  main
        .type   main, @function
main:
        addi    sp,sp,-16
        sw      ra,12(sp)
        sw      s0,8(sp)
        addi    s0,sp,16
        lui     a5,%hi(.LC0)

```
## 4- Convert into Hex Dump & Disassembly
Converted ELF into Raw Binary
```bash
riscv32-unknown-elf-objcopy -O binary hello.elf hello.bin 
```
Created HEXDump OF Binary
```bash
xd hello.bin > hello_binary_hexdump.txt 
```
Disassemble the ELF with objdump
```bash
riscv32-unknown-elf-objdump -d -M numeric,no-aliases hello.elf > hello_disassembly.txt 
```

