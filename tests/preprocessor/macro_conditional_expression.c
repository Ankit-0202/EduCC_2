#define PICK(cond, a, b) ((cond) ? (a) : (b))

int main(void) {
  int first = PICK(1, 2, 3);
  int second = PICK(0, 2, 3);
  return (first == 2 && second == 3) ? 0 : 1;
}
