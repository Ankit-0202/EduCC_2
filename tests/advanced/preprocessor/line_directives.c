#line 100 "test_file.c"

int main() {
    int x = 10;
    
    #line 200 "another_file.c"
    
    int y = 20;
    
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-variable"
    
    int unused = 30;
    
    #pragma GCC diagnostic pop
    
    if (x != 10) return 1;
    if (y != 20) return 1;
    
    return 0;
} 