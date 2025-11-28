// Test multiple levels of pointer indirection
int main() {
    int value = 42;
    int *ptr1 = &value;
    int **ptr2 = &ptr1;
    int ***ptr3 = &ptr2;

    // Single dereference
    if (*ptr1 != 42) return 1;

    // Double dereference
    if (**ptr2 != 42) return 2;

    // Triple dereference
    if (***ptr3 != 42) return 3;

    // Modify through double pointer
    **ptr2 = 100;
    if (value != 100) return 4;

    // Modify through triple pointer
    ***ptr3 = 200;
    if (value != 200) return 5;

    // Pointer chain
    if (value != 200) return 6;
    if (*ptr1 != 200) return 7;
    if (**ptr2 != 200) return 8;
    if (***ptr3 != 200) return 9;

    return 0;
}
