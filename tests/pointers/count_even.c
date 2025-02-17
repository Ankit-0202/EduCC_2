int main() {
  int arr[] = {1, 2, 3, 4, 5, 6};
  int count = 0;
  int *ptr = arr;
  int i;
  for (i = 0; i < 6; i++) {
    if (*(ptr + i) % 2 == 0)
      count++;
  }
  return count; // returns 3
}
