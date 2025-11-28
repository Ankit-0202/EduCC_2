// Test assignment expressions in conditions
int main() {
    int x;

    // Assignment in if condition
    if ((x = 5) == 5) {
        if (x != 5) return 1;
    } else {
        return 2;
    }

    // Assignment in while condition
    int y;
    int count = 0;
    while ((y = count++) < 3) {
        // Loop 3 times
    }
    if (count != 4) return 3;

    // Assignment in for condition
    int z;
    int sum = 0;
    for (int i = 0; (z = i) < 5; i++) {
        sum += z;
    }
    if (sum != 10) return 4;  // 0+1+2+3+4 = 10

    // Chained assignment
    int a, b, c;
    a = b = c = 10;
    if (a != 10 || b != 10 || c != 10) return 5;

    return 0;
}
