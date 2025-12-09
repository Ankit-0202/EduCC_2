// Options:   --seed 200177 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_177.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S2 {
  int64_t f0;
  int16_t f1;
};

static int16_t g_2 = 0x290BL;
static int32_t g_4 = (-8L);
static volatile int32_t g_13 = 0xE974A520L;
static int32_t g_14 = 0L;
static int32_t *g_18 = &g_14;
static int32_t **volatile g_17 = &g_18;
static struct S2 g_24[3][3] = {{{0xB5CF0ADC1094D0E8LL, 0x4AB4L},
                                {0xB5CF0ADC1094D0E8LL, 0x4AB4L},
                                {0xB5CF0ADC1094D0E8LL, 0x4AB4L}},
                               {{4L, 0L}, {0L, -7L}, {4L, 0L}},
                               {{0xB5CF0ADC1094D0E8LL, 0x4AB4L},
                                {0xB5CF0ADC1094D0E8LL, 0x4AB4L},
                                {0xB5CF0ADC1094D0E8LL, 0x4AB4L}}};
static struct S2 *volatile g_23 = &g_24[0][1];
static uint32_t g_30 = 0x8E12B6A3L;

static int16_t func_1(void);
static float func_7(int32_t *p_8, int64_t p_9);

static int16_t func_1(void) {
  int32_t *l_3[2];
  struct S2 l_22 = {-1L, 0xB56CL};
  int i;
  for (i = 0; i < 2; i++)
    l_3[i] = &g_4;
  if ((g_4 = g_2)) {
    int32_t *l_10 = (void *)0;
    int32_t l_21 = 0xCADFB1AFL;
    if (g_4) {
      float l_20 = (-0x1.9p-1);
      l_21 = (g_4 <= ((safe_mul_func_float_f_f(g_2, func_7(l_10, g_2))), 0UL));
      (*g_23) = l_22;
    } else {
      int32_t **l_25 = &l_3[0];
      (*l_25) = (*g_17);
      g_4 |= (*g_18);
    }
  } else {
    return g_24[0][1].f1;
  }
  g_30 &=
      (g_4 >
       (safe_rshift_func_uint16_t_u_s(
           g_4, (safe_div_func_uint64_t_u_u(((g_13 ^ 1UL) > 251UL), g_14)))));
  return g_30;
}

static float func_7(int32_t *p_8, int64_t p_9) {
  uint32_t l_19 = 0UL;
  for (p_9 = 22; (p_9 < 14); p_9 = safe_sub_func_int16_t_s_s(p_9, 7)) {
    for (g_14 = (-3); (g_14 > (-7));
         g_14 = safe_sub_func_int64_t_s_s(g_14, 9)) {
      (*g_17) = p_8;
      return l_19;
    }
    if (l_19)
      break;
  }
  return g_13;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_4;
  csmith_sink_ = g_13;
  csmith_sink_ = g_14;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
    }
  }
  csmith_sink_ = g_30;
  platform_main_end(0, 0);
  return 0;
}
