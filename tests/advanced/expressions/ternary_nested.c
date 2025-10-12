int main() {
    int x = 15;
    int result = (x > 10) ? ((x > 20) ? 30 : 20) : 10;
    if (result != 20) return 1;
    
    return 0;
} 