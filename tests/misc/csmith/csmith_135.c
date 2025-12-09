// Options:   --seed 200135 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_135.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_2 = 0x13B91020L;
static int32_t g_3 = 0x18D4081CL;
static int64_t g_7 = 0x5059B8BC588E1B61LL;
static int32_t g_12 = 0x51A93826L;

static int16_t func_1(void);

static int16_t func_1(void) {
  uint32_t l_13 = 0xBF4D39D9L;
  for (g_3 = 23; (g_3 > 26); g_3 = safe_add_func_int16_t_s_s(g_3, 9)) {
    int64_t *l_6[3][4] = {{&g_7, &g_7, &g_7, &g_7},
                          {&g_7, &g_7, &g_7, &g_7},
                          {&g_7, &g_7, &g_7, &g_7}};
    int32_t l_8 = 0xF21009D4L;
    int32_t *l_11 = &g_12;
    int i, j;
    (*l_11) &= ((l_8 &= g_3) || (((safe_lshift_func_uint8_t_u_u(
                                      (((g_2 && g_2), 0x2251L) == g_7), g_3)) |
                                  g_3) < 0x860A421EL));
  }
  return l_13;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_3;
  csmith_sink_ = g_7;
  csmith_sink_ = g_12;
  platform_main_end(0, 0);
  return 0;
}
