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
