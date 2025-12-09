#include <stdio.h>

#define STR(x) #x

int main() {
  printf("%s\n", STR(Hello World));
  return 0;
}
