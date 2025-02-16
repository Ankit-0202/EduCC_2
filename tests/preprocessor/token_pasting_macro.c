#define CONCAT(a, b) a##b
int main() {
    int xy = 42;
    return CONCAT(x, y); // Expands to xy, should return 42.
}
