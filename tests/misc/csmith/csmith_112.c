// Options:   --seed 200112 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_112.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S1 {
  int64_t f0;
};

union U2 {
  uint8_t f0;
};

static int32_t g_2 = (-4L);
static int16_t g_33[2][2] = {{0xBF7CL, 0xBF7CL}, {0xBF7CL, 0xBF7CL}};
static int32_t g_35 = (-1L);
static uint32_t g_45 = 0x6F576105L;
static uint64_t g_50 = 0x8BF51449BABE4A9FLL;
static int32_t *volatile g_51 = &g_35;

static int32_t func_1(void);
static int32_t func_5(uint32_t p_6);

static int32_t func_1(void) {
  struct S1 l_7[1] = {{0x9565E08CCCDDD1D8LL}};
  int32_t l_44 = 1L;
  int16_t *l_48[4][1] = {
      {&g_33[1][0]}, {&g_33[0][0]}, {&g_33[1][0]}, {&g_33[0][0]}};
  int i, j;
  for (g_2 = 0; (g_2 <= (-27)); --g_2) {
    int32_t l_14 = 9L;
    int32_t l_15 = 2L;
    if (func_5((((l_7[0], (safe_lshift_func_uint16_t_u_u(
                              l_7[0].f0, (safe_sub_func_int8_t_s_s(
                                             ((safe_lshift_func_int16_t_s_u(
                                                  ((l_14 && 0x18E9L), 0xEF66L),
                                                  l_14)) < l_7[0].f0),
                                             l_14))))),
                 l_15) < 0xA5F27A41L))) {
      uint64_t *l_49 = &g_50;
      (*g_51) &= (safe_mod_func_uint64_t_u_u(
          ((*l_49) = (safe_add_func_uint32_t_u_u(
               (((safe_div_func_uint32_t_u_u(
                     (safe_sub_func_uint16_t_u_u(
                         (++g_45),
                         ((g_33[0][1] != ((1UL >= (l_48[1][0] != (void *)0)) &
                                          l_44)) >= l_14))),
                     g_2)) &&
                 g_2) ^
                l_14),
               0UL))),
          (-7L)));
    } else {
      int32_t *l_52 = &g_35;
      (*l_52) = l_44;
      if ((*l_52))
        continue;
    }
  }
  for (g_2 = 0; (g_2 == 11); g_2++) {
    float l_55 = 0xF.F4914Dp-99;
    return l_7[0].f0;
  }
  return (*g_51);
}

static int32_t func_5(uint32_t p_6) {
  union U2 l_30[1][3] = {{{0x96L}, {0x96L}, {0x96L}}};
  int16_t *l_31 = (void *)0;
  int16_t *l_32[4][3] = {{&g_33[0][1], &g_33[1][0], &g_33[1][0]},
                         {&g_33[1][0], &g_33[0][1], (void *)0},
                         {&g_33[0][1], &g_33[0][1], &g_33[0][1]},
                         {&g_33[1][0], &g_33[1][0], (void *)0}};
  int32_t *l_34[3];
  int i, j;
  for (i = 0; i < 3; i++)
    l_34[i] = &g_35;
  g_35 |=
      ((safe_mod_func_uint16_t_u_u(
           (safe_mod_func_int8_t_s_s(
               0xDCL,
               (safe_rshift_func_uint8_t_u_u(
                   (safe_div_func_uint16_t_u_u(
                       (((((((safe_sub_func_int8_t_s_s(
                                 (safe_mod_func_int16_t_s_s(
                                     (g_33[1][0] = (safe_mod_func_int16_t_s_s(
                                          g_2, (((l_30[0][1], (-3L)), 1L) ||
                                                l_30[0][1].f0)))),
                                     0x1177L)),
                                 l_30[0][1].f0)) == p_6) &
                            l_30[0][1].f0) ^
                           l_30[0][1].f0) != p_6),
                         p_6) == g_2),
                       (-3L))),
                   l_30[0][1].f0)))),
           g_2)) |
       0xFE96L);
  return g_2;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_33[i][j];
    }
  }
  csmith_sink_ = g_35;
  csmith_sink_ = g_45;
  csmith_sink_ = g_50;
  platform_main_end(0, 0);
  return 0;
}
