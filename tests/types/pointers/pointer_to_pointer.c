int main() {
  int x = 42;
  int *ptr1 = &x;
  int **ptr2 = &ptr1;
  int ***ptr3 = &ptr2;

  if (*ptr1 != 42)
    return 1;
  if (**ptr2 != 42)
    return 1;
  if (***ptr3 != 42)
    return 1;

  // Modify through different levels
  *ptr1 = 100;
  if (x != 100)
    return 1;
  if (*ptr1 != 100)
    return 1;
  if (**ptr2 != 100)
    return 1;
  if (***ptr3 != 100)
    return 1;

  **ptr2 = 200;
  if (x != 200)
    return 1;
  if (*ptr1 != 200)
    return 1;
  if (**ptr2 != 200)
    return 1;
  if (***ptr3 != 200)
    return 1;

  ***ptr3 = 300;
  if (x != 300)
    return 1;
  if (*ptr1 != 300)
    return 1;
  if (**ptr2 != 300)
    return 1;
  if (***ptr3 != 300)
    return 1;

  return 0;
}