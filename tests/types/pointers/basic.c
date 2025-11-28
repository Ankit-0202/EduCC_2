int main() {
  int value = 42;
  int *ptr = &value;
  if (*ptr == 42) {
    return 0;
  }
  return 1;
}
