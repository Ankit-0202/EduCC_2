int main() {
  int value = 42;
  int *ptr = &value;
  int **pptr = &ptr;
  // Modify the value using the pointer-to-pointer
  **pptr = **pptr + 1; // value becomes 43
  return value;        // returns 43
}
