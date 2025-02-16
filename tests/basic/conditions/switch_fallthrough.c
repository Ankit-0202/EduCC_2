int main() {
    int val = 2;
    int result = 0;
    switch(val) {
        case 1:
            result = result + 1;
        case 2:
            result = result + 2;
        case 3:
            result = result + 3;
            break;
        default:
            result = 0;
    }
    // For val == 2, fall-through yields: result = 2 + 3 = 5.
    return result;
}
