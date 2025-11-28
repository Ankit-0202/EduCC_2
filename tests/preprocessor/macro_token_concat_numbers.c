#define JOIN(a, b) a##b

int main(void) {
    int ab = 7;
    return JOIN(a, b) == 7 ? 0 : 1;
}
