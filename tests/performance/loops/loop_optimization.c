// Test loop optimization opportunities
int main() {
    int sum = 0;
    
    // Simple loop that could be optimized
    for (int i = 0; i < 1000; i = i + 1) {
        sum = sum + i;
    }
    
    return sum;
}
