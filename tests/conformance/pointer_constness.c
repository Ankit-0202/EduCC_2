int main(void) {
    int value = 5;
    int *const ptr = &value;
    *ptr = 7;
    return value == 7 ? 0 : 1;
}
