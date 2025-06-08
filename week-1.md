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

### Screenshot

We didnt see the expected result as we weren't using emulator.This hasn been addressed in task 7. 

## Task 7: RISC-V Debugging with GDB and QEMU
Objective: Learn to debug a RISC-V ELF binary using riscv32-unknown-elf-gdb and QEMU.

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
``` C
 printf("Hello, RISC-V!\n"):
```
Register a0 should contain 14 (bytes printed).

Use disassemble to see RISC-V instructions like lui, addi, jal.

Troubleshooting
QEMU not found: Install with sudo apt install qemu-user-static.

No debug symbols: Recompile with -g flag.
Architecture issues: In GDB, run set architecture riscv:rv32.

### Screenshot

Here's a clean, professional README.md for your GitHub repository covering Task 8 (GCC Optimization Analysis):

markdown
# RISC-V GCC Optimization Comparison

## Task 8: Exploring Compiler Optimizations
Compare how different GCC optimization levels affect RISC-V assembly output.

### Quick Start
```bash
# Generate assembly files
riscv32-unknown-elf-gcc -S -O0 -o hello-O0.s hello.c  # No optimization
riscv32-unknown-elf-gcc -S -O2 -o hello-O2.s hello.c  # With optimizations
```
### Compare differences
Key Differences in Assembly
1. Dead Code Elimination
-O0: Keeps unused variables/operations.

-O2: Removes dead code (e.g., unused variables, redundant calculations).

2. Register Allocation
-O0: Uses memory (stack) heavily, fewer register optimizations.

-O2: Maximizes register usage (e.g., a0-a7, s0-s11) to reduce memory accesses.

3. Function Inlining
-O0: Calls functions explicitly (e.g., jal for printf).

-O2: Inlines small functions (replaces calls with direct code).

4. Loop Unrolling
-O0: Preserves original loop structure.

-O2: Unrolls loops (reduces branch overhead).
-O0 Assembly (No Optimization)
asm
main:
    addi    sp,sp,-16
    sw      ra,12(sp)
    li      a0,5           # Dead store (never used)
    lui     a0,%hi(.LC0)
    addi    a0,a0,%lo(.LC0)
    jal     ra,printf      # Normal function call
    li      a0,0
    lw      ra,12(sp)
    addi    sp,sp,16
    ret
-O2 Assembly (Optimized)
asm
main:
    lui     a0,%hi(.LC0)
    addi    a0,a0,%lo(.LC0)
    tail    printf         # Tail call optimization
How to Analyze
Compile with both optimization levels
Compare the files using 
```bash
diff -y hello-O0.s hello-O2.s
```
### Screenshots

## Task 9: Inline Assembly for Reading RISC-V Cycle Counter
Objective: Learn to read the RISC-V cycle CSR (Counter Register) using inline assembly in C, with detailed explanations of constraints and keywords.

Solution Code
```c
#include <stdint.h>

// Read the 32-bit cycle counter (CSR 0xC00)
static inline uint32_t rdcycle(void) {
    uint32_t cycles;
    asm volatile ("csrr %0, cycle" : "=r"(cycles));
    return cycles;
}
```
Key Components Explained
1. asm volatile
asm → Introduces inline assembly in C.

volatile → Instructs the compiler:

Do not optimize this assembly (keeps it even if outputs appear unused).

Do not reorder it relative to other volatile operations (critical for cycle counting).

2. csrr %0, cycle
csrr → RISC-V instruction for "Control Status Register Read".

cycle → CSR address 0xC00 (mnemonic alias for the cycle counter).

%0 → Refers to the first output operand (cycles in this case).

3. Output Constraint "=r"(cycles)
"=r" → Specifies:

= → Output operand (written by the assembly).

r → Store in a general-purpose register (e.g., a0, t0).

(cycles) → C variable that receives the result.

Example Usage
```c
#include <stdio.h>

int main() {
    uint32_t start = rdcycle();
    // Code to measure...
    uint32_t end = rdcycle();
    printf("Cycles elapsed: %u\n", end - start);
    return 0;
}
```
Why This Works?
csrr Instruction → Reads the cycle CSR (a 32-bit counter incrementing every clock cycle).

Constraint "=r" → Ensures GCC:

Assigns cycles to a register (e.g., a0, t0).

Does not optimize away the read.

volatile → Guarantees the read happens exactly once (no reordering/deletion).

Alternative: Direct CSR Number
If your toolchain doesn’t recognize cycle, use the CSR address directly:

```c
asm volatile ("csrr %0, 0xC00" : "=r"(cycles));  // Equivalent to "cycle"
```
Common Pitfalls
Mistake	Consequence	Fix
Missing volatile	GCC may delete "unused" reads.	Always use volatile.
Wrong constraint ("=m")	Forces memory access (slower).	Use "=r" for registers.
64-bit counters (RV64)	uint32_t overflows.	Use uint64_t (see below).
Extensions
1. Reading 64-bit Cycle Counters (RV64)
```c
static inline uint64_t rdcycle64(void) {
    uint64_t cycles;
    asm volatile ("csrr %0, cycle" : "=r"(cycles));  // RV64 reads full 64 bits
    return cycles;
}
```
2. Reading Other CSRs
CSR Name	Address	Description	Example
time	0xC01	Wall-clock timer	asm ("csrr %0, time" : "=r"(t));
instret	0xC02	Instructions retired	asm ("csrr %0, instret" : "=r"(count));
Key Takeaways
Component	Purpose
asm volatile	Ensures assembly is not optimized/reordered.
"=r"(var)	Output operand in a register, mapped to var.
csrr	RISC-V CSR read instruction.
cycle	Hardware counter for cycles since reset (CSR 0xC00).

## Week 10 Task: Memory-Mapped I/O GPIO Control
Objective
Demonstrate bare-metal memory-mapped I/O by toggling a GPIO register at 0x10012000 while preventing compiler optimizations.

Solution Code
```c
#include <stdint.h>

// Memory-mapped GPIO register (volatile + const correctness)
volatile uint32_t * const GPIO = (volatile uint32_t *)0x10012000;

void toggle_led() {
    *GPIO = 0x1;          // Write to register
    (void)*GPIO;          // Read-back barrier (optional)
}```
Key Concepts Applied
volatile Keyword:

Essential for hardware register access

Prevents compiler from optimizing away or reordering accesses

Indicates value may change outside program control

Alignment:

Hardware registers typically require natural alignment

Address 0x10012000 is properly aligned for 32-bit access (divisible by 4)

Pointer Declaration:

volatile uint32_t * const creates a constant pointer to volatile data

Pointer itself cannot be changed (const)

Pointed-to data is volatile (can't be optimized)

