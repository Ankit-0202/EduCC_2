#include <string.h>

int main(void) {
  unsigned char buffer[32];
  memset(buffer, 0xAA, sizeof buffer);
  for (size_t i = 0; i < sizeof buffer; ++i) {
    if (buffer[i] != 0xAA) {
      return 1;
    }
  }

  const unsigned char data[] = {1, 2, 3, 4, 5};
  memcpy(buffer, data, sizeof data);
  for (size_t i = 0; i < sizeof data; ++i) {
    if (buffer[i] != data[i]) {
      return 2;
    }
  }

  unsigned char overlap[] = {0, 1, 2, 3, 4, 5, 6, 7};
  memmove(overlap + 2, overlap, 6);
  const unsigned char expected[] = {0, 1, 0, 1, 2, 3, 4, 7};
  for (size_t i = 0; i < sizeof overlap; ++i) {
    if (overlap[i] != expected[i]) {
      return 3;
    }
  }

  return 0;
}
