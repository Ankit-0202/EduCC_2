// Test comma operator in various contexts
int main() {
    // Basic comma operator
    int a = (1, 2, 3);
    if (a != 3) return 1;

    // Comma in for loop
    int sum = 0;
    for (int i = 0, j = 10; i < 5; i++, j--) {
        sum += i + j;
    }
    if (sum != 50) return 2;  // (0+10)+(1+9)+(2+8)+(3+7)+(4+6)

    // Multiple expressions
    int b = (10 + 5, 20 * 2, 3);
    if (b != 3) return 3;

    // Comma with assignments
    int x, y;
    int c = (x = 5, y = 10, x + y);
    if (c != 15) return 4;

    // Comma in expression statement
    int d = 0;
    (d = 5, d = d * 2, d = d + 3);
    if (d != 13) return 5;

    return 0;
}
