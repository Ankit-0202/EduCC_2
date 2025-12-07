int main() {
  int x = 10;
  int y = 20;

  const int *ptr1 = &x; // pointer to const
  int *const ptr2 = &y; // const pointer

  if (*ptr1 != 10)
    return 1;
  if (*ptr2 != 20)
    return 1;

  // Can change what ptr1 points to
  ptr1 = &y;
  if (*ptr1 != 20)
    return 1;

  // Cannot change what ptr2 points to, but can change the value
  *ptr2 = 30;
  if (*ptr2 != 30)
    return 1;

  return 0;
}