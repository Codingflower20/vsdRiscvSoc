# Week-1 tasks
This contains progress and solutions of week 1 tasks.
## Task 1: Setup ToolChain
Extracted the ToolChain using 
```bash
tar -xzf
```
## Task 2: Hello.C
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
## Task 3: Hello.S
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
## Task 4: Convert into Hex Dump & Disassembly
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

## Task 5: ABI & Register Cheat-Sheet

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
![Screenshot of result](Screenshots/Task6.png)

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
![Screenshot of result](Screenshots/Task7.png)

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
![Screenshot of result](Screenshots/Task8.png)

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

## Task 10: Memory-Mapped I/O GPIO Control
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

## Task 11: Linker Script 101 – RISC-V Bare-Metal

This task demonstrates how to write and use a minimal **linker script** for bare-metal RISC-V development targeting the `RV32IMC` ISA. The goal is to manually control the placement of `.text` and `.data` sections in memory.

---
Objective

- Place `.text` (code) section at address `0x00000000` (typically Flash)
- Place `.data` (initialized data) section at `0x10000000` (SRAM)
- Fix errors caused by missing or overlapping sections (e.g., `.eh_frame`, `.sdata`, `__bss_start`)
- Build a working ELF binary with this custom memory layout

---
 Files

- `hello.c`: A simple Hello World C program
- `linker.ld`: Custom linker script defining memory layout
- `week-1.md`: This file

---

Linker Script Overview (`linker.ld`)

```ld
ENTRY(_start)

MEMORY
{
  FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 256K
  RAM (rwx)  : ORIGIN = 0x10000000, LENGTH = 64K
}

SECTIONS
{
  .text : 
  {
    *(.text*)
    *(.rodata*)
    *(.eh_frame*)
  } > FLASH

  .data : 
  {
    _data_start = .;
    *(.data*)
    *(.sdata*)
    _data_end = .;
  } > RAM AT > FLASH

  .bss (NOLOAD) : 
  {
    _bss_start = .;
    *(.bss*)
    *(.sbss*)
    *(COMMON)
    _bss_end = .;
  } > RAM

  PROVIDE(__global_pointer$ = _data_start + 0x800);
  PROVIDE(__bss_start = _bss_start);
  PROVIDE(_end = .);
}
```
Commands:
``` bash 
riscv32-unknown-elf-gcc -g -o hello.elf hello.c -T linker.ld 
riscv32-unknown-elf-objdump -h hello.elf
```
Output
The final hello.elf binary should:

Have .text at 0x00000000

Have .data and .bss in SRAM at 0x10000000+

Link without errors or section overlap

### Screenshots 
![Screenshot of result](Screenshots/Task11.png)

# Task 12: Start-up Code and `crt0` – RISC-V Bare-Metal

This task demonstrates how to implement the **startup code** (`crt0.S`) required to boot a bare-metal RISC-V application. The `crt0` code sets up the environment before calling `main()`, and is essential for systems that do not rely on an operating system.

---

 Purpose

In a bare-metal embedded system:
- There's no OS to initialize RAM, stack, or call `main()`.
- The startup file (`crt0.S`) must do this manually.

---

 What `crt0.S` Does

1. Set the **stack pointer (`sp`)**.
2. Copy **.data** section from flash to RAM.
3. Zero out the **.bss** section.
4. Call the **`main()`** function.
5. Halt the CPU in an **infinite loop** after `main()` returns.

---

Files

- `crt0.S`: Startup assembly code.
- `hello.c`: Minimal C program (e.g., toggling a GPIO).
- `linker.ld`: Custom linker script that defines memory layout and section symbols.
- `week-1.md`: This documentation.

---

Linker Script Snippet (`linker.ld`)

Ensure these definitions exist **outside the `SECTIONS` block**:

```ld
_stack_top = ORIGIN(RAM) + LENGTH(RAM);

PROVIDE(_data_start = ADDR(.data));
PROVIDE(_data_end   = ADDR(.data) + SIZEOF(.data));
PROVIDE(_data_load  = LOADADDR(.data));
PROVIDE(_bss_start  = ADDR(.bss));
PROVIDE(_bss_end    = ADDR(.bss) + SIZEOF(.bss));
```
crt0.S
```crt0
.section .text
.globl _start
_start:
    la sp, _stack_top

    # Copy .data from Flash to RAM
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

    # Zero .bss
    la a0, _bss_start
    la a1, _bss_end
3:
    beq a0, a1, 4f
    sw zero, 0(a0)
    addi a0, a0, 4
    j 3b
4:

    call main
    j .  # Infinite loop after main
```
Updated hello.c
```c
int main() {
    volatile int *gpio = (int*)0x10012000;
    *gpio = 0x1;
    while (1);
}
```
Build & Run
```bash
riscv32-unknown-elf-gcc -march=rv32imc -mabi=ilp32 -nostartfiles -T linker.ld crt0.S hello.c -o hello.elf
```
Dissassemble
```bash
riscv32-unknown-elf-objdump -d hello.elf
```
Outcome

You now have a fully bare-metal RISC-V binary:

Stack pointer is initialized.

Global/static variables are correctly handled.

main() runs without an OS.

Compatible with simulators like QEMU or Spike.
### Screenshots 
![Screenshot of result](Screenshots/Task12.png)

## Task 13: Demonstrate how to make a machine-Timer-Interrupt(MITP),Simple handler in C:
Enable the Machine Timer Interrupt (MTIP)

Write a simple interrupt handler in C or assembly

Understand how to configure and acknowledge interrupts on RISC-V

Step 1: Understand the Key Registers
Register	Purpose
mtime	64-bit timer that keeps incrementing
mtimecmp	Timer compare register — when mtime >= mtimecmp, MTIP is set
mstatus	Global interrupt enable (MIE)
mie	Interrupt enable for individual sources (enable MTIP here)
mcause	Indicates what caused the interrupt

Step 2: Memory-Mapped Timer Registers (Typical for QEMU/Spike)
Register	Address
mtime	0x0200BFF8 (64-bit)
mtimecmp	0x02004000 (64-bit)

Note: Your actual platform may vary — this is for QEMU/Spike with --machine virt.

basic handler : 
```c
#include <stdint.h>

#define MTIME       (*(volatile uint64_t*)0x0200BFF8)
#define MTIMECMP    (*(volatile uint64_t*)0x02004000)
#define MSTATUS_MIE (1 << 3)
#define MIE_MTIE    (1 << 7)

void trap_handler(void) __attribute__((interrupt));
void trap_handler(void) {
    // Acknowledge timer interrupt by setting next mtimecmp
    MTIMECMP = MTIME + 1000000;

    // Do something (e.g., toggle GPIO or counter)
}

void enable_timer_interrupt() {
    MTIMECMP = MTIME + 1000000;           // Schedule first interrupt

    asm volatile("csrs mie, %0" :: "r"(MIE_MTIE));   // Enable timer interrupt
    asm volatile("csrs mstatus, %0" :: "r"(MSTATUS_MIE)); // Enable global interrupts
}

int main() {
    enable_timer_interrupt();
    while (1); // Wait for interrupts
}
```
Summary :

Configured a RISC-V timer interrupt using mtimecmp

Wrote a basic interrupt handler in C

Set the mtvec register to handle traps

Successfully created a timer-based event system

### Screenshots
![Screenshot of result](Screenshots/Task13.png)

## Task 14: rv32imac vs rv32imc – What’s the “A”?
Question 
**“Explain the ‘A’ (atomic) extension in rv32imac. What instructions are added and why are they useful?”**

What is the “A” Extension?
- The **“A” stands for Atomic** — it adds **atomic read-modify-write** instructions.
- These instructions allow for **safe, hardware-supported access to shared memory**.
- It is used when multiple cores/threads need to access the same variable without conflicts.

Instructions Introduced by the "A" Extension

| Instruction   | Meaning                             | Purpose                            |
|---------------|--------------------------------------|-------------------------------------|
| `lr.w`        | Load-Reserved word                   | Starts an atomic load-store block   |
| `sc.w`        | Store-Conditional word               | Stores only if no one else touched |
| `amoadd.w`    | Atomic add                           | Adds a value atomically             |
| `amoswap.w`   | Atomic swap                          | Atomically swaps memory             |
| `amoand.w`    | Atomic AND                           | Useful for bitmask flags            |
| `amoor.w`     | Atomic OR                            | Used in setting flags atomically    |
 Use Cases
- **Operating Systems**: Manage shared memory between tasks/interrupts.
- **Multithreading**: Protect shared counters or variables.
- **Lock-Free Data Structures**: Like queues or stacks, to avoid performance penalties from locking.
Analogy

Imagine you're writing on a shared whiteboard:

- `lr.w` → You reserve a spot to write. 
- `sc.w` → You try to write, but **only succeed if no one else has written there** since you reserved it. 
- `amoadd.w` → You **add a number** to the current value, and it's done **safely**, even if others are trying at the same time.
Summary
- The “A” extension makes **safe concurrent memory access** possible in RISC-V.
- It is essential for low-level OS and embedded systems programming.
- It **distinguishes `rv32imac` (which supports atomics)** from `rv32imc` (which does not)

## Task 15: Spin-lock implementation in C with inline asm fallback.
Objective:
Understand and implement atomic operations in bare-metal RISC-V to safely update a shared variable (shared_counter) in a multi-thread-like context (simulated).
Core Concepts:
1. Atomic Operations
An atomic operation is one that completes as a single, uninterruptible unit.
In RISC-V, atomic operations prevent race conditions when multiple "threads" access shared memory.

2. LR/SC Pair (Load-Reserved / Store-Conditional)
RISC-V uses lr.w (load-reserved) and sc.w (store-conditional) for atomic operations.

These ensure a variable is only updated if no one else has written to it between the load and store.

3. Race Conditions
If two cores (or software threads) try to update shared_counter at the same time, the value may be corrupted.

Atomic operations protect against this.

task15.c

```c
// task15.c
volatile int shared_counter = 0;

void main() {
    while (1) {
        shared_counter++;
        for (volatile int i = 0; i < 100000; ++i); // delay
    }
}
```

start15.S

```S
// main.c
volatile int shared_counter = 0;

void main() {
    while (1) {
        shared_counter++;
        for (volatile int i = 0; i < 100000; ++i); // delay
    }
}
```

link15.ld

```ld
OUTPUT_ARCH(riscv)
ENTRY(_start)

MEMORY
{
  RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 128K
}

SECTIONS
{
  .text : {
    *(.text*)
    *(.rodata*)
  } > RAM

  .data : {
    *(.data*)
  } > RAM

  .bss : {
    *(.bss*)
    *(COMMON)
  } > RAM
}
```
Compiled Using
```bash
riscv32-unknown-elf-gcc -g -nostartfiles -T link15.ld start15.S task15.c -o task15.elf
```
Emulated via Qemu
```bash
qemu-riscv32 -machine virt -bios none -kernel task15.elf -S -gdb tcp::1234
```
Connect gdb to qemu

```bash
riscv32-unknown-elf-gdb task15.elf
```
GDB Commands
```GDB
(gdb)target main :1234
(gdb)b main
(gdb)c
(gdb)print shared_counter
(gdb)info registers
```
### ScreenShots
![Screenshot of result](Screenshots/Task15.png)

## Task 16:Using Newlib printf Without an OS

Explanation and Objective:
Task 16 is a continuation of Task 15 and focuses on using atomic operations in RISC-V in a bare-metal environment to simulate synchronization between multiple threads (or cores). The setup is similar to Task 15, but Task 16 emphasizes on:
1. Using atomic RISC-V instructions (lr.w, sc.w) for lock-free synchronization
2. Observing the result of concurrent access to a shared variable (shared_counter)
3. Using QEMU for multi-core simulation and GDB for inspection

Goal:
1. Implement atomic increment of a global variable from two functions running in parallel (simulated as threads).
2. Verify the final value using gdb.

task16.c

```c
// task16.c
volatile int shared_counter = 0;

void thread1() {
    for (int i = 0; i < 3; i++) {
        __sync_fetch_and_add(&shared_counter, 1);
    }
}

void thread2() {
    for (int i = 0; i < 3; i++) {
        __sync_fetch_and_add(&shared_counter, 1);
    }
}

int main() {
    thread1();
    thread2();
    return 0;
}
```

link16.ld
 
```ld
ENTRY(_start)

MEMORY {
    RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 128K
}

SECTIONS {
    . = ORIGIN(RAM);
    .text : {
        *(.text*)
    }

    .rodata : {
        *(.rodata*)
    }

    .data : {
        *(.data*)
    }

    .bss : {
        *(.bss*)
        *(COMMON)
    }

    _stack_top = . + 2048;
}
```
start16.S

```S
    .section .text
    .globl _start
_start:
    la sp, _stack_top
    call main
1:  j 1b

    .section .bss
    .space 2048
_stack_top:
```

Compiled Using
```bash
riscv32-unknown-elf-gcc -g -nostartfiles -T link16.ld start16.S task16.c -o task16.elf
```
Emulated via Qemu
```bash
qemu-riscv32 -machine virt -bios none -kernel task16.elf -S -gdb tcp::1234
```
Connect gdb to qemu

```bash
riscv32-unknown-elf-gdb task16.elf
```
GDB Commands
```GDB
(gdb)target main :1234
(gdb)b main
(gdb)c
(gdb)print shared_counter
```
### ScreenShots
![Screenshot of result](Screenshots/Task16.png)

## Task 17: RISC-V Bare-Metal – Thread Scheduling and Mutex (Using qemu-riscv32, GDB, and Atomics)
Objective
1. To understand and implement preemptive multithreading using RISC-V atomic instructions and mutual exclusion (mutex) in a bare-metal environment using QEMU and GDB.

2. Create two threads (thread1, thread2) which increment a shared counter.

3. Use atomic instructions (e.g. amoswap.w, lr.w, sc.w) to protect critical sections.

4. Verify mutual exclusion using GDB.

Concept Overview

1. Atomic Operations: Prevent race conditions without disabling interrupts.
2. Shared Resource: A global variable (e.g. shared_counter) is modified by both threads.
3. Mutex: Implemented using a spinlock with lr.w and sc.w.
4. Threading: Cooperative or manually invoked by jumping between functions in this task.

task17.c
```c
volatile int lock = 0;
volatile int shared_counter = 0;

void acquire_lock(volatile int *lock) {
    int tmp;
    do {
        __asm__ volatile (
            "lr.w %0, %1\n"
            "bnez %0, 1f\n"
            "li t1, 1\n"
            "sc.w t1, t1, %1\n"
            "bnez t1, 1f\n"
            "j 2f\n"
            "1:\n"
            "j acquire_lock\n"
            "2:\n"
            : "=&r" (tmp), "+A" (*lock)
            :
            : "t1"
        );
    } while (0);
}

void release_lock(volatile int *lock) {
    __asm__ volatile (
        "sw zero, %0"
        : "=m" (*lock)
    );
}

void thread1() {
    acquire_lock(&lock);
    for (int i = 0; i < 5; ++i)
        shared_counter++;
    release_lock(&lock);
}

void thread2() {
    acquire_lock(&lock);
    for (int i = 0; i < 5; ++i)
        shared_counter++;
    release_lock(&lock);
}

int main() {
    thread1();
    thread2();
    return 0;
}
```
link17.ld

```ld
ENTRY(_start)

MEMORY
{
  RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 128K
}

SECTIONS
{
  . = ORIGIN(RAM);

  .text : {
    *(.text*)
  }

  .rodata : {
    *(.rodata*)
  }

  .data : {
    *(.data*)
  }

  .bss : {
    *(.bss COMMON)
  }

  . = . + 0x1000;
  _stack_top = .;
}
```

start17.S

```S
.section .text
.global _start

_start:
    la sp, _stack_top
    call main
    j .
```
Compiled Using
```bash
riscv32-unknown-elf-gcc -g -nostartfiles -T link17.ld start17.S task17.c -o task17.elf
```
Emulated via Qemu
```bash
qemu-riscv32 -machine virt -bios none -kernel task17.elf -S -gdb tcp::1234
```
Connect gdb to qemu

```bash
riscv32-unknown-elf-gdb task17.elf
```
GDB Commands
```GDB
(gdb)target main :1234
(gdb)b main
(gdb)c
(gdb)print shared_counter
```
### ScreenShots
![Screenshot of result](Screenshots/Task17.png)	
