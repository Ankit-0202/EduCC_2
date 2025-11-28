#include <stdlib.h>
#include <string.h>

int main(void) {
  const int size = 16;
  unsigned char *buffer = (unsigned char *)malloc(size);
  if (buffer == NULL) {
    return 1;
  }

  memset(buffer, 0xAB, size);

  int ok = 1;
  for (int i = 0; i < size; ++i) {
    if (buffer[i] != 0xAB) {
      ok = 0;
      break;
    }
  }

  free(buffer);
  return ok ? 0 : 2;
}

