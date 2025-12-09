// Options:   --seed 100087 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_087.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int16_t g_2 = 0xE5F3L;
static int32_t g_4 = (-6L);
static int32_t *volatile g_3 = &g_4;

static int8_t func_1(void);

static int8_t func_1(void) {
  uint32_t l_5[3][2] = {{18446744073709551615UL, 18446744073709551615UL},
                        {18446744073709551615UL, 18446744073709551615UL},
                        {18446744073709551615UL, 18446744073709551615UL}};
  int i, j;
  (*g_3) |= g_2;
  return l_5[2][1];
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_4;
  platform_main_end(0, 0);
  return 0;
}
