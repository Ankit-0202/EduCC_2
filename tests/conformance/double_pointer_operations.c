int main(void) {
    int value = 5;
    int *p = &value;
    int **pp = &p;
    **pp = 10;
    return value == 10 ? 0 : 1;
}
