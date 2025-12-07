int main() {
  int x = 42;
  char c = 'K';
  float f = 3.14;

  void *ptr;

  ptr = &x;
  if (*(int *)ptr != 42)
    return 1;

  ptr = &c;
  if (*(char *)ptr != 'K')
    return 1;

  ptr = &f;
  if (*(float *)ptr < 3.13 || *(float *)ptr > 3.15)
    return 1;

  // Test void pointer arithmetic (should not compile in strict C)
  // But we can test casting back and forth
  int *int_ptr = (int *)ptr;
  void *ptr2 = int_ptr;
  float *float_ptr = (float *)ptr2;

  if (*float_ptr < 3.13 || *float_ptr > 3.15)
    return 1;

  return 0;
}