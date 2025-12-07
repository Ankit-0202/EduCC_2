int main() {
  int arr[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

  int (*ptr)[4] = arr;

  // Access through pointer to array
  if (ptr[0][0] != 1)
    return 1;
  if (ptr[0][1] != 2)
    return 1;
  if (ptr[1][2] != 7)
    return 1;
  if (ptr[2][3] != 12)
    return 1;

  // Pointer arithmetic with array pointer
  ptr++;
  if (ptr[0][0] != 5)
    return 1;
  if (ptr[0][1] != 6)
    return 1;

  ptr++;
  if (ptr[0][0] != 9)
    return 1;
  if (ptr[0][1] != 10)
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