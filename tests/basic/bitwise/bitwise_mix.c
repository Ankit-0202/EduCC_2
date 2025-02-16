int main() {
    int x = 5;  // 0101 in binary
    int y = 3;  // 0011 in binary
    // (x & y) is 0001 (1) and (x ^ y) is 0110 (6)
    int result = (x & y) | (x ^ y); // 1 | 6 = 7
    return result;
}
