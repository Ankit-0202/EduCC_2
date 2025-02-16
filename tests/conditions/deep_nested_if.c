int main() {
    int a = 5;
    int b = 10;
    int c = 15;
    int result = 0;
    if(a < b) {
        if(b < c) {
            if(a + b == 15) {
                result = 1;
            } else {
                result = 2;
            }
        } else {
            result = 3;
        }
    } else {
        result = 4;
    }
    return result - 1; /* Expected: 1 */
}
