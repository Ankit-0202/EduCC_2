void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int main() {
  int x = 10, y = 20;
  swap(&x, &y);
  // After swap, x = 20, y = 10.
  return x - y; // returns 10
}
