// Options:   --seed 200109 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_109.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_9 = 0xF14C90D2L;
static int32_t *g_8 = &g_9;
static float g_16 = 0x7.B051AFp-50;
static int32_t g_18 = 0x14F4E797L;
static int32_t *volatile g_17[4] = {&g_18, &g_18, &g_18, &g_18};
static int32_t *volatile g_19 = &g_18;

static int64_t func_1(void);
static int32_t *const func_2(int32_t p_3, uint16_t p_4, int32_t *p_5);

static int64_t func_1(void) {
  int8_t l_6 = (-1L);
  int32_t *l_7 = (void *)0;
  g_19 = func_2(l_6, ((l_7 == l_7), 65527UL), g_8);
  return g_9;
}

static int32_t *const func_2(int32_t p_3, uint16_t p_4, int32_t *p_5) {
  int32_t *l_14 = &g_9;
  int32_t *l_15 = (void *)0;
  int32_t *l_20 = &g_18;
  (*g_19) &= ((safe_add_func_uint64_t_u_u(
                  p_4, (((safe_add_func_uint64_t_u_u(p_3, g_9)), l_14) ==
                        (void *)0))) |
              p_3);
  (*l_20) ^= (*l_14);
  return p_5;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_9;
  csmith_sink_ = g_16;
  csmith_sink_ = g_18;
  platform_main_end(0, 0);
  return 0;
}
