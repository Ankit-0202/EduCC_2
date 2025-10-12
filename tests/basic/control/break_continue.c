// Test break and continue statements
int main() {
    int sum = 0;
    
    for (int i = 0; i < 10; i = i + 1) {
        if (i == 3) {
            continue;
        }
        if (i == 7) {
            break;
        }
        sum = sum + i;
    }
    
    return sum;
}
