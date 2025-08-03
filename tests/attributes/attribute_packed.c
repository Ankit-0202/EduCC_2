struct __attribute__((packed)) PackedStruct {
    char a;
    int b;
    char c;
    short d;
};

struct NormalStruct {
    char a;
    int b;
    char c;
    short d;
};

int main() {
    struct PackedStruct packed = {'A', 42, 'B', 123};
    struct NormalStruct normal = {'X', 100, 'Y', 456};
    
    if (packed.a != 'A') return 1;
    if (packed.b != 42) return 1;
    if (packed.c != 'B') return 1;
    if (packed.d != 123) return 1;
    
    if (normal.a != 'X') return 1;
    if (normal.b != 100) return 1;
    if (normal.c != 'Y') return 1;
    if (normal.d != 456) return 1;
    
    return 0;
} 