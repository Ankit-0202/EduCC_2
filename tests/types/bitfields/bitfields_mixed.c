struct MixedBitfields {
    unsigned int a : 3;
    int b : 4;
    unsigned char c : 2;
    char d : 3;
    unsigned int e : 8;
};

int main() {
    struct MixedBitfields mixed = {5, -3, 2, -2, 200};
    
    if (mixed.a != 5) return 1;
    if (mixed.b != -3) return 1;
    if (mixed.c != 2) return 1;
    if (mixed.d != -2) return 1;
    if (mixed.e != 200) return 1;
    
    mixed.a = 7;
    mixed.b = 7;
    mixed.c = 3;
    mixed.d = 3;
    mixed.e = 255;
    
    if (mixed.a != 7) return 1;
    if (mixed.b != 7) return 1;
    if (mixed.c != 3) return 1;
    if (mixed.d != 3) return 1;
    if (mixed.e != 255) return 1;
    
    return 0;
} 