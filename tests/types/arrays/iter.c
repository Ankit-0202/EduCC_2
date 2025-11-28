// test_array_iteration.c
int main() {
  int arr[4] = {1, 2, 3, 4};
  int sum = 0;

  // Iterate through the array and calculate the sum
  for (int i = 0; i < 4; i++) {
    sum += arr[i];
  }

  // Check if the sum is correct
  if (sum == 10) {
    return 1; // Success
  }

  return 0;
}