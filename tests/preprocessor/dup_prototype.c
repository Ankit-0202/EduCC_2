#include "dup_prototype.h"

// Another identical prototype is fine
int do_stuff(int x, int y);

// The definition
int do_stuff(int a, int b) { return a * b; }

int main() {
  int x = 2;
  int y = 8;
  int result = do_stuff(x, y);
  return result; // Expect 16
}