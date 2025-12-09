// Options:   --seed 200153 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_153.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_7 = (-2L);
static int32_t *g_6 = &g_7;
static uint32_t g_12 = 0x555145CCL;
static uint16_t g_21 = 1UL;
static uint32_t g_27[1] = {0x169B41DBL};
static float g_29 = 0x7.B364FEp+36;
static float *volatile g_28[4] = {&g_29, &g_29, &g_29, &g_29};
static volatile uint32_t g_42 = 0xCBC3393AL;

static uint16_t func_1(void);
static int32_t *func_2(int32_t *p_3, int32_t p_4, float p_5);

static uint16_t func_1(void) {
  int32_t **l_30 = &g_6;
  float *l_33 = &g_29;
  int32_t l_34[4] = {9L, 9L, 9L, 9L};
  int i;
  (*l_30) = func_2(g_6, g_7, g_7);
  for (g_12 = 0; (g_12 <= 3); g_12 += 1) {
    int32_t *l_35 = &l_34[2];
    int32_t *l_36 = &g_7;
    int32_t *l_37 = &l_34[2];
    int32_t *l_38 = &g_7;
    int32_t *l_39 = &g_7;
    int32_t *l_40 = &g_7;
    int32_t *l_41[1];
    int i;
    for (i = 0; i < 1; i++)
      l_41[i] = &l_34[2];
    for (g_7 = 0; (g_7 >= 0); g_7 -= 1) {
      float *l_31[4];
      int32_t l_32 = (-9L);
      int i;
      for (i = 0; i < 4; i++)
        l_31[i] = &g_29;
      l_32 = g_27[g_7];
      (*l_33) = ((0x2.31A295p+83 < g_27[g_7]) <=
                 ((((l_33 == l_33), 0xF.2F1E73p-79) > l_34[2]) != g_27[g_7]));
    }
    ++g_42;
  }
  return g_12;
}

static int32_t *func_2(int32_t *p_3, int32_t p_4, float p_5) {
  uint32_t l_8[3];
  uint64_t l_19 = 0x4C5530C4E2BF5F40LL;
  int32_t l_22 = 0x737AE9F9L;
  uint32_t l_26 = 8UL;
  int i;
  for (i = 0; i < 3; i++)
    l_8[i] = 0x4F2887CFL;
  for (p_4 = 2; (p_4 >= 0); p_4 -= 1) {
    int8_t l_9 = 0xD8L;
    uint16_t *l_25 = &g_21;
    for (g_7 = 2; (g_7 >= 0); g_7 -= 1) {
      int i;
      l_9 = (l_8[g_7] || g_7);
      g_12 = (l_9 || ((0L ^ (safe_rshift_func_int8_t_s_u(g_7, 4))) & p_4));
    }
    for (g_7 = 0; (g_7 <= 2); g_7 += 1) {
      uint16_t *l_20 = &g_21;
      l_22 =
          ((safe_add_func_float_f_f(
               (safe_div_func_float_f_f(
                   (((((p_5, g_12) < (((*l_20) |= (safe_lshift_func_uint8_t_u_s(
                                           (0L & l_19), 1))),
                                      9L)) &
                      p_4) ||
                     p_4),
                    g_21),
                   l_8[0])),
               g_7)) < g_12);
      l_22 &= l_9;
    }
    for (l_19 = 0; (l_19 <= 2); l_19 += 1) {
      uint16_t *l_23 = (void *)0;
      uint16_t **l_24 = &l_23;
      if ((*g_6))
        break;
      p_5 = ((g_27[0] = (((((&g_21 != ((*l_24) = l_23)) !=
                            (((&l_22 != &g_7) & g_12) ^ p_4)),
                           &g_21) != l_25),
                         l_26)) < 0x8.FA1B44p-40);
    }
  }
  return &g_7;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_7;
  csmith_sink_ = g_12;
  csmith_sink_ = g_21;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_27[i];
  }
  csmith_sink_ = g_29;
  csmith_sink_ = g_42;
  platform_main_end(0, 0);
  return 0;
}
