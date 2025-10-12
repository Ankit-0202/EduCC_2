// Test null pointer dereference
int main() {
    int *ptr = 0;  // NULL pointer
    int result = *ptr;  // Dereference null pointer
    
    return result;
}
