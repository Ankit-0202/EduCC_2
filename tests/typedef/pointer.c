int main() {
  typedef int *IntPtr;
  int value = 77;
  IntPtr ptr = &value;
  return *ptr - 77;
}
