#define CONCAT(a, b) a##b
#define MAKE_VAR(x) var_##x
int main() {
  int MAKE_VAR(1) = 100;
  return CONCAT(var_, 1) - 100;
}
