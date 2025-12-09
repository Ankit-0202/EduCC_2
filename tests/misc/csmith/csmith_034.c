// Options:   --seed 100034 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_034.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static uint32_t g_2 = 4294967290UL;

static uint8_t func_1(void);

static uint8_t func_1(void) { return g_2; }

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  platform_main_end(0, 0);
  return 0;
}
