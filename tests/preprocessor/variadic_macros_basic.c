#define ADD3(a, b, c) ((a) + (b) + (c))
#define WRAP3(...) ADD3(__VA_ARGS__)

int main(void) {
    return WRAP3(1, 2, 3) == 6 ? 0 : 1;
}
