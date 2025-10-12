// Test switch statement
int main() {
    int value = 3;
    int result = 0;
    
    switch (value) {
        case 1:
            result = 10;
            break;
        case 2:
            result = 20;
            break;
        case 3:
            result = 30;
            break;
        default:
            result = 0;
            break;
    }
    
    return result;
}
