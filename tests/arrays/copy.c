// test_array_copy.c
int main() {
  int source[3] = {1, 2, 3};
  int destination[3];
  int result = 0;

  // Copy elements from source to destination
  destination[0] = source[0];
  destination[1] = source[1];
  destination[2] = source[2];

  // Check if the copy was successful
  if (destination[0] == 1 && destination[1] == 2 && destination[2] == 3) {
    result = 1; // Success
  }

  return result;
}