// test_array_modification.c
int main() {
  int arr[3] = {1, 2, 3};
  int result = 0;

  // Modify the array elements
  arr[0] = 10;
  arr[1] = 20;
  arr[2] = 30;

  // Check if the modifications are correct
  if (arr[0] == 10 && arr[1] == 20 && arr[2] == 30) {
    result = 1; // Success
  }

  return result;
}