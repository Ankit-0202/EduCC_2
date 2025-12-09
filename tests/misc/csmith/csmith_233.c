// Options:   --seed 300233 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_233.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int8_t g_3 = 0x38L;

static uint64_t func_1(void);

static uint64_t func_1(void) {
  uint32_t l_2 = 18446744073709551615UL;
  g_3 &= (l_2 = (-1L));
  return g_3;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  platform_main_end(0, 0);
  return 0;
}
