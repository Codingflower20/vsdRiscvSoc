volatile int shared_counter = 0;

void main() {
    while (1) {
        shared_counter++;
        for (volatile int i = 0; i < 100000; ++i); // delay
    }
}
