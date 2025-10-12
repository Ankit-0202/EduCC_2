// Test conditional compilation
#define DEBUG 1

int main() {
    int result = 0;
    
    #ifdef DEBUG
        result = result + 1;
    #endif
    
    #if DEBUG
        result = result + 1;
    #endif
    
    #ifndef RELEASE
        result = result + 1;
    #endif
    
    return result;
}
