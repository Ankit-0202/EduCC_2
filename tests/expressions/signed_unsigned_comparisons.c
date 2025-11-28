int main(void) {
    unsigned int u = 1;
    int s = -1;

    if (s < u) {
        return 1; // -1 converts to large unsigned value, so comparison should be false
    }

    return 0;
}
