// Options:   --seed 300257 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_257.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static const volatile int32_t *g_2 = (void *)0;

static uint8_t func_1(void);

static uint8_t func_1(void) {
  const volatile int32_t **l_3 = &g_2;
  int32_t l_4 = 7L;
  (*l_3) = g_2;
  return l_4;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  platform_main_end(0, 0);
  return 0;
}
