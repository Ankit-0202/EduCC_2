#define ADD(x, y) (x + y)
#define MULTIPLY(x, y) (x * y)
#define COMBINE(a, b, c) (MULTIPLY(ADD(a, b), c))
int main() {
    /* COMBINE(2, 3, 4) = (2+3)*4 = 20 */
    return COMBINE(2, 3, 4) - 20;
}
