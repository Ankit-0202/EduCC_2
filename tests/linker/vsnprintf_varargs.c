#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static int format_into(char *buffer, size_t size, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  int written = vsnprintf(buffer, size, fmt, args);
  va_end(args);
  return written;
}

int main(void) {
  char buffer[128];
  int written =
      format_into(buffer, sizeof buffer, "value=%d, hex=%#x", 42, 255);
  if (written <= 0) {
    return 1;
  }
  if (strcmp(buffer, "value=42, hex=0xff") != 0) {
    return 2;
  }

  char small[8];
  written = format_into(small, sizeof small, "123456789");
  if (written != 9) {
    return 3;
  }
  if (strcmp(small, "1234567") != 0) {
    return 4;
  }

  return 0;
}
