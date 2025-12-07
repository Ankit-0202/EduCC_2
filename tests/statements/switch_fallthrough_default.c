int main(void) {
  int value = 0;
  int input = 2;
  switch (input) {
  case 1:
    value += 1;
    break;
  case 2:
    value += 2;
    /* fallthrough */
  case 3:
    value += 3;
    break;
  default:
    value = -1;
  }
  return value == 5 ? 0 : 1;
}
