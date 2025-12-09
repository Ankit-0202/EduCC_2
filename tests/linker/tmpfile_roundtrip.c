#include <stdio.h>
#include <string.h>

int main(void) {
  const char *message = "Hello tmpfile!\n";
  FILE *fp = tmpfile();
  if (!fp) {
    return 1;
  }
  if (fputs(message, fp) == EOF) {
    fclose(fp);
    return 2;
  }
  if (fflush(fp) != 0) {
    fclose(fp);
    return 3;
  }
  rewind(fp);
  char buffer[32];
  if (!fgets(buffer, sizeof buffer, fp)) {
    fclose(fp);
    return 4;
  }
  fclose(fp);
  if (strncmp(buffer, message, strlen(message)) != 0) {
    return 5;
  }
  return 0;
}
