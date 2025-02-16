int main() {
    int a = 10, b = 20, c = 30;
    int result = 0;
    if(a < b) {
        if(b < c) {
            result = (a + b) - c;  // 10+20-30 = 0
        } else {
            result = (c - b);
        }
    } else {
        if(a == c) {
            result = a;
        } else {
            result = b;
        }
    }
    return result; // Expected: 0
}
