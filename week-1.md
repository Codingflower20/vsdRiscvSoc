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

## 5- ABI & Register Cheat-Sheet

This section provides a complete list of the 32 integer registers in RV32I, along with their ABI names and conventional roles in the calling convention.

###  RV32I Register Table

| Register | ABI Name | Role / Description                      | Calling Convention Role     |
|----------|----------|------------------------------------------|-----------------------------|
| x0       | zero     | Hardwired zero                          | Constant 0                  |
| x1       | ra       | Return address                          | Return address              |
| x2       | sp       | Stack pointer                           | Stack pointer               |
| x3       | gp       | Global pointer                          | Global pointer              |
| x4       | tp       | Thread pointer                          | Thread pointer              |
| x5       | t0       | Temporary register                      | Caller-saved                |
| x6       | t1       | Temporary register                      | Caller-saved                |
| x7       | t2       | Temporary register                      | Caller-saved                |
| x8       | s0 / fp  | Saved register / Frame pointer          | Callee-saved / Frame ptr    |
| x9       | s1       | Saved register                          | Callee-saved                |
| x10      | a0       | Function argument / Return value        | Caller-saved / Arg/Ret      |
| x11      | a1       | Function argument / Return value        | Caller-saved / Arg/Ret      |
| x12      | a2       | Function argument                       | Caller-saved / Arg          |
| x13      | a3       | Function argument                       | Caller-saved / Arg          |
| x14      | a4       | Function argument                       | Caller-saved / Arg          |
| x15      | a5       | Function argument                       | Caller-saved / Arg          |
| x16      | a6       | Function argument                       | Caller-saved / Arg          |
| x17      | a7       | Function argument                       | Caller-saved / Arg          |
| x18      | s2       | Saved register                          | Callee-saved                |
| x19      | s3       | Saved register                          | Callee-saved                |
| x20      | s4       | Saved register                          | Callee-saved                |
| x21      | s5       | Saved register                          | Callee-saved                |
| x22      | s6       | Saved register                          | Callee-saved                |
| x23      | s7       | Saved register                          | Callee-saved                |
| x24      | s8       | Saved register                          | Callee-saved                |
| x25      | s9       | Saved register                          | Callee-saved                |
| x26      | s10      | Saved register                          | Callee-saved                |
| x27      | s11      | Saved register                          | Callee-saved                |
| x28      | t3       | Temporary register                      | Caller-saved                |
| x29      | t4       | Temporary register                      | Caller-saved                |
| x30      | t5       | Temporary register                      | Caller-saved                |
| x31      | t6       | Temporary register                      | Caller-saved                |

###  Calling Convention Summary

- `a0`–`a7`: Function **arguments and return values**
- `s0`–`s11`: **Callee-saved** registers
- `t0`–`t6`: **Caller-saved** registers
- `ra`: Return address
- `sp`: Stack pointer

## Task 6: RISC-V Debugging with GDB 
Objective: Learn to debug a RISC-V ELF binary using riscv32-unknown-elf-gdb.

Steps
1. Compile the Program
Compile your C code (hello.c) with debug symbols:

```bash
riscv32-unknown-elf-gcc -g -o hello.elf hello.c
```
2. Launch QEMU in Debug Mode
Run the binary and pause for GDB connection:

```bash
qemu-riscv32 -g 1234 hello.elf
```
3. Debug with GDB
In a new terminal:

```bash
riscv32-unknown-elf-gdb hello.elf
```
Inside GDB:

```gdb
(gdb) target remote :1234   # Connect to QEMU
(gdb) break main            # Set breakpoint at main()
(gdb) continue              # Start execution
(gdb) next                  # Step through code
(gdb) info registers        # Inspect RISC-V registers
(gdb) disassemble           # View assembly
```
Key Commands Cheatsheet
Command	Action
break main	Set breakpoint at main().
next (n)	Execute next line (step over).
step (s)	Step into functions.
info reg	Show all registers.
x/s ADDRESS	Examine memory as a string.
disassemble	View assembly of current function.
Expected Output
After running
```C 
 printf("Hello, RISC-V!\n"):
```

Register a0 should contain 14 (bytes printed).

Use disassemble to see RISC-V instructions like lui, addi, jal.

Troubleshooting
QEMU not found: Install with sudo apt install qemu-user-static.

No debug symbols: Recompile with -g flag.

Architecture issues: In GDB, run set architecture riscv:rv32.

Screenshot Example
(Optional: Add a screenshot of your GDB session here.)

We didnt see the expected result as we weren't using emulator.This hasn been addressed in task 7. 
