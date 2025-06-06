# Week-1 tasks
This contains progress and solutions of week 1 tasks.
## Setup ToolChain
Extracted the ToolChain using 
```bash
tar -xzf
```
## Hello.C
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
