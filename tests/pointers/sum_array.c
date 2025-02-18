int main() {
  int arr[] = {1, 2, 3, 4, 5};
  int *ptr = arr; // pointer to first element
  int sum = 0;
  int i;
  for (i = 0; i < 5; i++) {
    sum += *(ptr + i);
  }
  return sum; // returns 15
}
