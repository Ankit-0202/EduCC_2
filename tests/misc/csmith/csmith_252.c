// Options:   --seed 300252 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_252.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static uint16_t g_2 = 1UL;
static int32_t *volatile g_4 = (void *)0;
static uint16_t g_5[1][1] = {{0x70CDL}};

static uint32_t func_1(void);

static uint32_t func_1(void) {
  uint16_t l_3 = 9UL;
  l_3 |= g_2;
  g_5[0][0] = g_2;
  return g_5[0][0];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_5[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
