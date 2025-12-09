// Options:   --seed 200172 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_172.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_2 = 0x2B165808L;
static volatile int32_t g_6 = 0L;

static float func_1(void);

static float func_1(void) {
  uint32_t l_5[4] = {0UL, 0UL, 0UL, 0UL};
  int i;
  for (g_2 = 0; (g_2 >= 19); g_2 = safe_add_func_int8_t_s_s(g_2, 1)) {
    for (g_6 = 0; g_6 < 4; g_6 += 1) {
      l_5[g_6] = 0UL;
    }
    return g_6;
  }
  return l_5[0];
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_6;
  platform_main_end(0, 0);
  return 0;
}
