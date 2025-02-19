// test_array_search.c
int main() {
  int arr[5] = {5, 10, 15, 20, 25};
  int searchValue = 15;
  int found = 0;

  // Search for the value in the array
  for (int i = 0; i < 5; i++) {
    if (arr[i] == searchValue) {
      found = 1; // Found
      break;
    }
  }

  return found;
}