int main() {
    // Large array operations
    int large_array[1000];
    
    // Initialize array
    for (int i = 0; i < 1000; i++) {
        large_array[i] = i * 2;
    }
    
    // Process array
    int sum = 0;
    for (int i = 0; i < 1000; i++) {
        sum += large_array[i];
    }
    
    if (sum != 999000) return 1;  // Sum of 0,2,4,...,1998
    
    // Large struct operations
    struct LargeStruct {
        int data[100];
        char padding[100];
    };
    
    struct LargeStruct structs[10];
    
    // Initialize structs
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 100; j++) {
            structs[i].data[j] = i * 100 + j;
        }
    }
    
    // Process structs
    int struct_sum = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 100; j++) {
            struct_sum += structs[i].data[j];
        }
    }
    
    if (struct_sum != 499500) return 1;  // Sum of all elements
    
    return 0;
} 