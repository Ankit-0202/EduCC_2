// Options:   --seed 100019 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_019.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_2 = 0L;
static int32_t *volatile g_8 = (void *)0;
static int32_t *volatile g_9 = &g_2;

static int16_t func_1(void);

static int16_t func_1(void) {
  uint8_t l_5[2][2] = {{0xCDL, 0xCDL}, {0xCDL, 0xCDL}};
  int i, j;
  for (g_2 = 16; (g_2 != (-14)); g_2 = safe_sub_func_int32_t_s_s(g_2, 5)) {
    return l_5[0][0];
  }
  (*g_9) = (safe_rshift_func_int16_t_s_s((-2L), 11));
  return l_5[0][0];
}

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
