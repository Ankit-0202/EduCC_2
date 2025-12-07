// Test pointer difference calculations
int main() {
  int arr[20];
  for (int i = 0; i < 20; i++) {
    arr[i] = i * 10;
  }

  int *start = &arr[0];
  int *end = &arr[19];

  // Full array distance
  if (end - start != 19)
    return 1;

  // Midpoint distance
  int *mid = &arr[10];
  if (mid - start != 10)
    return 2;
  if (end - mid != 9)
    return 3;

  // Calculate array size via pointer difference
  int size = end - start + 1;
  if (size != 20)
    return 4;

  // Use difference to iterate
  int count = 0;
  for (int *p = start; p <= end; p++) {
    count++;
  }
  if (count != 20)
    return 5;

  return 0;
}
