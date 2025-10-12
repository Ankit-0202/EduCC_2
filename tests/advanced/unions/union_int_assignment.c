union Data {
    int i;
    float f;
    char str[20];
};

int main() {
    union Data data;
    
    data.i = 10;
    if (data.i != 10) return 1;
    
    return 0;
} 