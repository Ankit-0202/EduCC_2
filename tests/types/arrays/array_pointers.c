int main() {
  int arr[5] = {1, 2, 3, 4, 5};
  int *ptr = arr;

  // Array name as pointer
  if (*arr != 1)
    return 1;
  if (*(arr + 1) != 2)
    return 1;
  if (*(arr + 2) != 3)
    return 1;

  // Pointer arithmetic
  if (*ptr != 1)
    return 1;
  ptr++;
  if (*ptr != 2)
    return 1;
  ptr += 2;
  if (*ptr != 4)
    return 1;

  // Array indexing with pointer
  if (ptr[0] != 4)
    return 1;
  if (ptr[1] != 5)
    return 1;

  // Pointer to array
  int (*array_ptr)[5] = &arr;
  if ((*array_ptr)[0] != 1)
    return 1;
  if ((*array_ptr)[1] != 2)
    return 1;

  // Array of pointers
  int *ptr_array[3];
  int a = 10, b = 20, c = 30;
  ptr_array[0] = &a;
  ptr_array[1] = &b;
  ptr_array[2] = &c;

  if (*ptr_array[0] != 10)
    return 1;
  if (*ptr_array[1] != 20)
    return 1;
  if (*ptr_array[2] != 30)
    return 1;

  return 0;
}