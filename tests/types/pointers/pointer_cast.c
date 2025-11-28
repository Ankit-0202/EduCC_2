#include <stdio.h>

int main() {
    int a = 0x12345678;
    char *p = (char *)&a;
    // Little endian check usually
    printf("First byte: %x\n", *p); 
    return 0;
}
