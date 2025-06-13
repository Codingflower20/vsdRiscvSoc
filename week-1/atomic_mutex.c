#include <stdint.h>
#include <stdio.h>

typedef struct {
    volatile uint32_t lock;
} mutex_t;

// Initialize mutex
void mutex_init(mutex_t *m) {
    asm volatile ("fence rw,w");  // Ensure visibility
    m->lock = 0;
    asm volatile ("fence rw,w");
}

// Acquire lock using LR/SC
void mutex_lock(mutex_t *m) {
    uint32_t temp = 1;
    uint32_t result;
    
    do {
        asm volatile (
            "1: lr.w %0, (%1)\n"      // Load-Reserved
            "   bnez %0, 1b\n"        // Spin if locked
            "   sc.w %0, %2, (%1)\n"  // Store-Conditional
            : "=&r" (result)
            : "r" (&m->lock), "r" (temp)
            : "memory");
    } while (result != 0);  // Retry if SC failed
    
    asm volatile ("fence r,rw");  // Acquire barrier
}

// Release lock
void mutex_unlock(mutex_t *m) {
    asm volatile ("fence rw,w");  // Release barrier
    m->lock = 0;
    asm volatile ("fence rw,rw");
}

// Shared counter
static uint32_t shared_counter = 0;
static mutex_t counter_mutex;

void thread_function(const char *name) {
    mutex_lock(&counter_mutex);
    
    printf("[%s] Counter: %d -> ", name, shared_counter);
    shared_counter++;
    printf("%d\n", shared_counter);
    
    mutex_unlock(&counter_mutex);
}

int main() {
    mutex_init(&counter_mutex);
    
    // Simulate two threads
    for (int i = 0; i < 10; i++) {
        thread_function("ThreadA");
        thread_function("ThreadB");
    }
    
    printf("Final value: %d\n", shared_counter);
    return 0;
}
