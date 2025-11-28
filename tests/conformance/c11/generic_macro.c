#define TYPE_CODE(x) _Generic((x), int: 1, long: 2, const char *: 3, default: 4)

int main(void) {
    int total = TYPE_CODE(5);
    total += TYPE_CODE(5L);
    total += TYPE_CODE("hi");
    total += TYPE_CODE(3.14);
    return total == 1 + 2 + 3 + 4 ? 0 : 1;
}
