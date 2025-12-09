int read_const(const int *value) { return *value; }

int main(void) {
  const int number = 10;
  return read_const(&number) == 10 ? 0 : 1;
}
