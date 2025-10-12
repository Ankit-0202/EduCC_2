// Test basic union
union Data {
    int i;
    float f;
    char c;
};

int main() {
    union Data data;
    data.i = 42;
    
    return data.i;
}
