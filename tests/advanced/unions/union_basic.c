union Data {
    int i;
    float f;
    char str[20];
};

int main() {
    union Data data;
    
    data.i = 10;
    if (data.i != 10) return 1;
    
    data.f = 3.14;
    if (data.f < 3.13 || data.f > 3.15) return 1;
    
    // Test string assignment
    int i = 0;
    while (i < 5) {
        data.str[i] = 'A' + i;
        i++;
    }
    data.str[i] = '\0';
    
    if (data.str[0] != 'A') return 1;
    if (data.str[1] != 'B') return 1;
    if (data.str[2] != 'C') return 1;
    if (data.str[3] != 'D') return 1;
    if (data.str[4] != 'E') return 1;
    if (data.str[5] != '\0') return 1;
    
    return 0;
} 