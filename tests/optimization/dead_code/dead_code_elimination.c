int main() {
    int x = 10;
    int y = 20;
    int z = x + y;  // This should be optimized away if not used
    return x;  // Only x is used
} 