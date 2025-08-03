// test_array_initialization.c
int main() {
  int arr[5] = {10, 20, 30, 40, 50};
  int result = 0;

  // Check if the array elements are initialized correctly
  if (arr[0] == 10 && arr[1] == 20 && arr[2] == 30 && arr[3] == 40 &&
      arr[4] == 50) {
    result = 1; // Success
  }

  return result;
}