#include <stddef.h>
#include <string.h>
#include <time.h>

int main(void) {
  time_t now = time(NULL);
  if (now == (time_t)-1) {
    return 1;
  }

  struct tm *info = localtime(&now);
  if (!info) {
    return 2;
  }

  char buffer[64];
  size_t written = strftime(buffer, sizeof buffer, "%Y-%m-%d %H:%M", info);
  if (written == 0) {
    return 3;
  }
  if (buffer[4] != '-' || buffer[7] != '-') {
    return 4;
  }

  return 0;
}


