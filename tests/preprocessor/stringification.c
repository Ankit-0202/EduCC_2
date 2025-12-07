#define STRINGIFY(x) #x
#define CONCAT(a, b) a##b
#define MAKE_FUNC(name) func_##name

int func_hello() { return 10; }
int func_world() { return 20; }

int main() {
  // Stringification
  char *str1 = STRINGIFY(Hello);
  if (str1[0] != 'H')
    return 1;
  if (str1[1] != 'e')
    return 1;
  if (str1[2] != 'l')
    return 1;
  if (str1[3] != 'l')
    return 1;
  if (str1[4] != 'o')
    return 1;

  // Token pasting
  int CONCAT(var, 1) = 100;
  if (var1 != 100)
    return 1;

  int CONCAT(var, 2) = 200;
  if (var2 != 200)
    return 1;

  // Function name generation
  int result1 = MAKE_FUNC(hello)();
  if (result1 != 10)
    return 1;

  int result2 = MAKE_FUNC(world)();
  if (result2 != 20)
    return 1;

  return 0;
}