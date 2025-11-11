#include <stdio.h>
#include <string.h>

int main(void) {
  const char *message = "Linker integration test";
  size_t len = strlen(message);
  printf("len=%zu:%s\n", len, message);
  return len == 24 ? 0 : 1;
}


