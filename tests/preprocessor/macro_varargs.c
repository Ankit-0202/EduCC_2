#include <stdio.h>

#define LOG(fmt, ...) printf(fmt, __VA_ARGS__)

int main() {
  LOG("Val: %d\n", 42);
  return 0;
}
