int main(void) {
    int value = 0;
    goto skip;
    value = 1;
skip:
    value += 2;
    return value == 2 ? 0 : 1;
}
