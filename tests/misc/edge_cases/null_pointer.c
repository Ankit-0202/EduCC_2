int main() {
  int *null_ptr = 0;

  // These should cause undefined behavior, but we test that they don't crash
  int value = *null_ptr; // Dereference null pointer

  // Test null pointer arithmetic
  int *ptr2 = null_ptr + 1;
  int *ptr3 = null_ptr - 1;

  // Test null pointer comparison
  if (null_ptr == 0) {
    // This should be true
  }

  // Test null pointer assignment
  int *ptr4 = null_ptr;

  return 0; // If we get here, null pointer dereference didn't crash
}