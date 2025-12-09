// Test equivalence between array and pointer notation
int main() {
  int arr[5] = {10, 20, 30, 40, 50};
  int *p = arr;

  // arr[i] == *(arr + i)
  for (int i = 0; i < 5; i++) {
    if (arr[i] != *(arr + i))
      return 1;
  }

  // p[i] == *(p + i)
  for (int i = 0; i < 5; i++) {
    if (p[i] != *(p + i))
      return 2;
  }

  // arr[i] == p[i]
  for (int i = 0; i < 5; i++) {
    if (arr[i] != p[i])
      return 3;
  }

  // &arr[i] == arr + i
  for (int i = 0; i < 5; i++) {
    if (&arr[i] != (arr + i))
      return 4;
  }

  // Commutative property: i[arr] == arr[i]
  if (0 [arr] != arr[0])
    return 5;
  if (2 [arr] != arr[2])
    return 6;
  if (4 [p] != p[4])
    return 7;

  return 0;
}
