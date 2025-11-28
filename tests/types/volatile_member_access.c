struct device_state {
    volatile int status;
    int value;
};

int main(void) {
    struct device_state d = {0, 0};
    for (int i = 0; i < 3; i++) {
        d.status++;
        d.value += 2;
    }
    return (d.status == 3 && d.value == 6) ? 0 : 1;
}
