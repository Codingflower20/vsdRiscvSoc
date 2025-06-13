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
