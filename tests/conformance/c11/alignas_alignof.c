#include <stdalign.h>
#include <stddef.h>
#include <stdint.h>

alignas(32) unsigned char buffer[32];

int main(void) {
  uintptr_t addr = (uintptr_t)buffer;
  int aligned = (addr % 32u) == 0u;
  int natural = alignof(max_align_t) >= alignof(double);
  return (aligned && natural) ? 0 : 1;
}
