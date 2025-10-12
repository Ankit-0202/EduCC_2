// Test nested if-else statements
int main() {
    int a = 10;
    int b = 5;
    int c = 3;
    int result = 0;
    
    if (a > b) {
        if (b > c) {
            result = 1;
        } else {
            result = 2;
        }
    } else {
        if (a > c) {
            result = 3;
        } else {
            result = 4;
        }
    }
    
    return result;
}
