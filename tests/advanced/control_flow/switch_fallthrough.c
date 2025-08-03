int main() {
    int x = 2;
    int result = 0;
    
    switch (x) {
        case 1:
            result += 10;
            break;
        case 2:
            result += 20;
            // Fallthrough
        case 3:
            result += 30;
            break;
        case 4:
            result += 40;
            break;
        default:
            result += 100;
    }
    
    if (result != 50) return 1;  // 20 + 30 = 50
    
    // Test with default
    x = 5;
    result = 0;
    
    switch (x) {
        case 1:
            result += 10;
            break;
        case 2:
            result += 20;
            break;
        default:
            result += 100;
    }
    
    if (result != 100) return 1;
    
    return 0;
} 