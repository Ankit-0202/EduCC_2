// Test pointer to pointer
int main() {
    int x = 42;
    int *ptr1 = &x;
    int **ptr2 = &ptr1;
    
    return **ptr2;
}