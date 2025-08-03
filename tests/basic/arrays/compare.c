// test_array_comparison.c
int main() {
  int arr1[3] = {1, 2, 3};
  int arr2[3] = {1, 2, 3};
  int result = 1; // Assume success initially

  // Compare each element of the arrays
  for (int i = 0; i < 3; i++) {
    if (arr1[i] != arr2[i]) {
      result = 0; // Failure
    }
  }

  return result;
}