// Options:   --seed 200168 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_168.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U5 {
  uint32_t f0;
};

static volatile float g_4 = 0x8.8999D9p+28;
static uint64_t g_5 = 0x1D21F1EB32A831D2LL;
static int8_t g_13 = 0x67L;
static int32_t g_22 = 0x7374FD52L;
static volatile uint32_t g_32 = 9UL;
static int32_t *volatile g_44 = &g_22;
static int64_t g_49 = (-5L);
static int32_t g_50 = 1L;
static volatile float g_51[1][4] = {
    {0x1.E3C1DCp+74, 0x1.E3C1DCp+74, 0x1.E3C1DCp+74, 0x1.E3C1DCp+74}};
static volatile uint64_t g_53 = 18446744073709551607UL;
static int32_t *g_57 = &g_22;
static int32_t **volatile g_56 = &g_57;
static uint16_t g_63 = 0x7D2AL;

static int16_t func_1(void);
static int8_t func_9(int8_t *p_10, uint32_t p_11);

static int16_t func_1(void) {
  uint32_t l_6 = 18446744073709551606UL;
  int32_t l_52 = 9L;
  int32_t l_60 = (-3L);
  int32_t l_61 = 0x705E7732L;
  int32_t l_62 = 0L;
  if ((g_5 >= ((0x9C63C407858F9C25LL & (l_6 >= l_6)) > g_5))) {
    int8_t *l_12 = &g_13;
    int32_t l_18[2][4] = {{(-3L), (-3L), (-3L), (-3L)},
                          {(-3L), (-3L), (-3L), (-3L)}};
    union U5 l_19[4] = {{3UL}, {3UL}, {3UL}, {3UL}};
    int i, j;
    if ((safe_lshift_func_int8_t_s_s(
            func_9(l_12, ((safe_sub_func_int64_t_s_s(
                              (safe_div_func_uint32_t_u_u(
                                  l_18[1][3], (l_19[3], 4294967293UL))),
                              l_18[1][0])) &&
                          g_5)),
            7))) {
      int8_t **l_43 = &l_12;
      (*g_44) &=
          (((safe_sub_func_int32_t_s_s(
                (safe_mod_func_int32_t_s_s(
                    (safe_sub_func_int8_t_s_s(
                        (&g_22 == &g_22),
                        ((((*l_43) = &g_13) == (void *)0) && l_18[1][1]))),
                    1L)),
                0L)) >= 0xD982L) > g_13);
    } else {
      int32_t *l_45 = &g_22;
      int32_t *l_46 = &l_18[1][3];
      int32_t *l_47 = (void *)0;
      int32_t *l_48[1][4] = {{&g_22, &g_22, &g_22, &g_22}};
      int i, j;
      --g_53;
      (*g_56) = &g_22;
    }
  } else {
    int32_t *l_58 = (void *)0;
    int32_t *l_59[2];
    int i;
    for (i = 0; i < 2; i++)
      l_59[i] = &g_22;
    --g_63;
  }
  return l_62;
}

static int8_t func_9(int8_t *p_10, uint32_t p_11) {
  int32_t *l_20 = (void *)0;
  int32_t *l_21 = &g_22;
  int32_t *l_23 = &g_22;
  int32_t *l_24 = &g_22;
  int32_t *l_25 = &g_22;
  int32_t l_26 = 0x1F0EF2F3L;
  int32_t *l_27 = &g_22;
  int32_t *l_28 = &l_26;
  int32_t *l_29 = (void *)0;
  int32_t *l_30 = &l_26;
  int32_t *l_31[3][2] = {{&g_22, &l_26}, {&g_22, &g_22}, {&l_26, &g_22}};
  int i, j;
  g_32++;
  for (g_13 = 13; (g_13 > 24); g_13 = safe_add_func_int8_t_s_s(g_13, 2)) {
    return g_32;
  }
  return (*l_24);
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_4;
  csmith_sink_ = g_5;
  csmith_sink_ = g_13;
  csmith_sink_ = g_22;
  csmith_sink_ = g_32;
  csmith_sink_ = g_49;
  csmith_sink_ = g_50;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_51[i][j];
    }
  }
  csmith_sink_ = g_53;
  csmith_sink_ = g_63;
  platform_main_end(0, 0);
  return 0;
}
