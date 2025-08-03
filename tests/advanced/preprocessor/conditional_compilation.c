#define DEBUG 1
#define VERSION 2
#define FEATURE_X 1

int main() {
    int result = 0;
    
    #if DEBUG
        result += 10;
    #endif
    
    #if VERSION == 1
        result += 20;
    #elif VERSION == 2
        result += 30;
    #else
        result += 40;
    #endif
    
    #ifdef FEATURE_X
        result += 50;
    #endif
    
    #ifndef FEATURE_Y
        result += 60;
    #endif
    
    #if DEBUG && VERSION == 2
        result += 70;
    #endif
    
    #if DEBUG || VERSION == 1
        result += 80;
    #endif
    
    if (result != 220) return 1;  // 10 + 30 + 50 + 60 + 70 + 80 = 220
    
    return 0;
} 