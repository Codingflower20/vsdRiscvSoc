int main() {
    int main() {
    volatile int *led = (int*) 0x10012000;
    *led = 0x1;
    while (1);
}
}
