// Options:   --seed 200121 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_121.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_2 = (-1L);
static volatile int32_t g_3[2] = {0L, 0L};
static volatile int32_t g_4 = (-1L);
static int32_t g_5 = 0x37D45DB3L;

static float func_1(void);

static float func_1(void) {
  uint64_t l_10 = 0x872D9EE1C97412DFLL;
  uint16_t l_11 = 65531UL;
  for (g_5 = (-4); (g_5 <= 4); ++g_5) {
    l_11 ^= (g_4 | (safe_add_func_uint16_t_u_u(l_10, 0x37A5L)));
  }
  return l_11;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_3[i];
  }
  csmith_sink_ = g_4;
  csmith_sink_ = g_5;
  platform_main_end(0, 0);
  return 0;
}
