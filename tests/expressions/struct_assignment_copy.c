struct pair {
  int a;
  int b;
};

int main(void) {
  struct pair first = {1, 2};
  struct pair second = {0, 0};
  second = first;
  first.a = 5;
  return (second.a == 1 && second.b == 2 && first.a == 5) ? 0 : 1;
}
