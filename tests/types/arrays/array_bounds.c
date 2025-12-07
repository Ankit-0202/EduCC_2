// Test array boundary access patterns
int main() {
  int arr[10];
  for (int i = 0; i < 10; i++) {
    arr[i] = i * 10;
  }

  // First element
  if (arr[0] != 0)
    return 1;

  // Last element
  if (arr[9] != 90)
    return 2;

  // Middle element
  if (arr[5] != 50)
    return 3;

  // Sequential access
  int sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += arr[i];
  }
  if (sum != 450)
    return 4; // 0+10+20+...+90

  // Reverse access
  int rsum = 0;
  for (int i = 9; i >= 0; i--) {
    rsum += arr[i];
  }
  if (rsum != 450)
    return 5;

  // Every other element
  int even_sum = 0;
  for (int i = 0; i < 10; i += 2) {
    even_sum += arr[i];
  }
  if (even_sum != 200)
    return 6; // 0+20+40+60+80

  return 0;
}
