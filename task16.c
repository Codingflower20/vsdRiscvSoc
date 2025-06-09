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
