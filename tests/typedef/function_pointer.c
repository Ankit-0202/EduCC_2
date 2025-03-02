int square(int x) { return x * x; }

int main() {
  typedef int (*myFuncPtr)(int);
  myFuncPtr f = square;
  return f(5) - 25;
}
