struct signed_bits {
  signed int a : 4;
  unsigned int b : 4;
};

int main(void) {
  struct signed_bits v = {.a = -3, .b = 15};
  return (v.a == -3 && v.b == 15) ? 0 : 1;
}
