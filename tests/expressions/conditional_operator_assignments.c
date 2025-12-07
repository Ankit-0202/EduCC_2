int main(void) {
  int x = 5;
  int y = (x > 0) ? ++x : (x - 1);
  int z = (x < 0) ? x : --x;
  return (y == 6 && z == 5 && x == 5) ? 0 : 1;
}
