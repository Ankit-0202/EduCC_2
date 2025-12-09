// Test pointer increment operations
int main() {
  int arr[5] = {10, 20, 30, 40, 50};
  int *p = arr;

  // Initial value
  if (*p != 10)
    return 1;

  // Post-increment
  p++;
  if (*p != 20)
    return 2;

  // Pre-increment
  ++p;
  if (*p != 30)
    return 3;

  // Multiple increments
  p++;
  p++;
  if (*p != 50)
    return 4;

  // Decrement back
  p--;
  if (*p != 40)
    return 5;

  // Pre-decrement
  --p;
  if (*p != 30)
    return 6;

  // Pointer arithmetic with addition
  p = arr;
  p = p + 3;
  if (*p != 40)
    return 7;

  // Compound assignment
  p = arr;
  p += 4;
  if (*p != 50)
    return 8;

  return 0;
}
