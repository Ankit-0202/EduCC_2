int main() {
  // Large array operations
  int large_array[1000];

  // Initialize array
  for (int i = 0; i < 1000; i++) {
    large_array[i] = i * 2;
  }

  // Process array
  int sum = 0;
  for (int i = 0; i < 1000; i++) {
    sum += large_array[i];
  }

  if (sum != 999000)
    return 1; // Sum of 0,2,4,...,1998

  return 0;
}