struct Flags {
    unsigned int flag1 : 1;
    unsigned int flag2 : 1;
    unsigned int flag3 : 1;
    unsigned int flag4 : 1;
    unsigned int value : 4;
};

int main() {
    struct Flags flags = {1, 0, 1, 0, 10};
    
    if (flags.flag1 != 1) return 1;
    if (flags.flag2 != 0) return 1;
    if (flags.flag3 != 1) return 1;
    if (flags.flag4 != 0) return 1;
    if (flags.value != 10) return 1;
    
    flags.flag2 = 1;
    flags.value = 15;
    
    if (flags.flag2 != 1) return 1;
    if (flags.value != 15) return 1;
    
    return 0;
} 