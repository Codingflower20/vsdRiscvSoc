// blink.c - A simple program to run in GDB without printf
int main() {
    volatile int i = 0; // 'volatile' prevents compiler from optimizing it away

    while (1) {
        // This loop ensures the program keeps running so GDB can attach
        // In a real embedded system, this might toggle an LED or do other work.
        i++;
    }

    return 0; // Unreachable in this infinite loop, but good practice
}
