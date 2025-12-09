// Options:   --seed 200103 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_103.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  int64_t f0;
  int8_t f1;
};

static volatile uint32_t g_8[2] = {1UL, 1UL};
static const float g_22 = 0x0.Ep-1;
static uint32_t g_24[4][1] = {
    {0x359B504DL}, {0x359B504DL}, {0x359B504DL}, {0x359B504DL}};
static uint8_t g_27[4][4] = {{255UL, 0x8AL, 255UL, 255UL},
                             {0x8AL, 0x8AL, 0x2CL, 0x8AL},
                             {0x8AL, 255UL, 255UL, 0x8AL},
                             {255UL, 0x8AL, 255UL, 255UL}};
static uint32_t g_35 = 4294967295UL;
static float *volatile g_48 = (void *)0;
static float g_50 = 0x7.5p-1;
static int64_t g_56 = 1L;
static float g_58[4] = {0x2.21BA82p+29, 0x2.21BA82p+29, 0x2.21BA82p+29,
                        0x2.21BA82p+29};
static int32_t g_59[3][2] = {{0x29123EBAL, 0x29123EBAL},
                             {0x29123EBAL, 0x29123EBAL},
                             {0x29123EBAL, 0x29123EBAL}};
static struct S0 g_81 = {-1L, -7L};
static int32_t *volatile g_90 = &g_59[1][0];
static int32_t **volatile g_93 = (void *)0;
static int32_t *g_95 = &g_59[1][0];
static int32_t **volatile g_94[4][3] = {{(void *)0, &g_95, &g_95},
                                        {&g_95, &g_95, &g_95},
                                        {(void *)0, &g_95, (void *)0},
                                        {&g_95, &g_95, &g_95}};
static int32_t **volatile g_96 = &g_95;
static int16_t g_116 = (-9L);
static int32_t **volatile g_128 = (void *)0;

static int32_t func_1(void);
static int32_t func_2(int32_t p_3, int8_t p_4, uint64_t p_5);

static int32_t func_1(void) {
  int8_t l_21 = 0xCDL;
  uint64_t l_23 = 0UL;
  uint8_t *l_25 = (void *)0;
  uint8_t *l_26 = &g_27[0][1];
  int32_t l_99 = 0L;
  int32_t l_100 = 0x95B12CA4L;
  int32_t l_101 = 0x0C53E4ABL;
  int32_t **l_129 = &g_95;
  if (func_2(
          ((safe_mul_func_uint8_t_u_u(
               (g_8[0] < ((safe_add_func_uint8_t_u_u(
                              ((*l_26) = (safe_sub_func_uint16_t_u_u(
                                   (safe_add_func_int32_t_s_s(
                                       (safe_mod_func_uint32_t_u_u(
                                           (safe_lshift_func_int8_t_s_s(
                                               ((safe_sub_func_int32_t_s_s(
                                                    (((0xF338L >=
                                                       ((l_21 | l_21) & l_21)) >
                                                      0x65L) <= l_23),
                                                    0xA056EBF4L)) |
                                                g_24[3][0]),
                                               g_24[3][0])),
                                           l_23)),
                                       l_21)),
                                   1UL))),
                              (-9L))),
                          0xE2BFL)),
               l_23)) &
           l_23),
          l_21, l_23)) {
    int32_t l_98[4];
    int32_t l_102[2];
    uint32_t l_103 = 0UL;
    int16_t *l_115 = &g_116;
    int32_t l_117[2];
    int i;
    for (i = 0; i < 4; i++)
      l_98[i] = 0x38F1CEF1L;
    for (i = 0; i < 2; i++)
      l_102[i] = 0x95B8C608L;
    for (i = 0; i < 2; i++)
      l_117[i] = 7L;
    for (l_23 = 0; (l_23 < 5); ++l_23) {
      int32_t *l_97[2];
      int i;
      for (i = 0; i < 2; i++)
        l_97[i] = &g_59[1][0];
      (*g_96) = &g_59[0][1];
      ++l_103;
    }
    l_102[1] &=
        ((safe_mod_func_int64_t_s_s(
             (~(safe_sub_func_uint16_t_u_u(
                 g_24[2][0],
                 ((*l_115) = (safe_mod_func_uint8_t_u_u(
                      g_35,
                      (safe_lshift_func_int8_t_s_u(
                          ((0xADD9D0C5B6348A9CLL > g_81.f1), 0x29L), 5)))))))),
             (-1L))) &&
         l_117[1]);
  } else {
    uint32_t l_125[1][4];
    int i, j;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 4; j++)
        l_125[i][j] = 1UL;
    }
    for (l_100 = 3; (l_100 <= (-10));
         l_100 = safe_sub_func_uint16_t_u_u(l_100, 8)) {
      int32_t *l_120 = &l_101;
      int32_t *l_121 = (void *)0;
      int32_t *l_122 = &g_59[1][1];
      int32_t *l_123 = &l_101;
      int32_t *l_124[1][3];
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 3; j++)
          l_124[i][j] = (void *)0;
      }
      l_120 = (void *)0;
      l_125[0][1]++;
    }
  }
  (*l_129) = &l_99;
  return (*g_90);
}

static int32_t func_2(int32_t p_3, int8_t p_4, uint64_t p_5) {
  uint64_t l_38[1];
  const int8_t l_39 = (-1L);
  uint32_t l_41 = 0xCB5CB1BEL;
  int32_t l_57 = 1L;
  int32_t l_60 = 0x7A919E54L;
  uint32_t l_61 = 7UL;
  struct S0 *l_82 = (void *)0;
  int i;
  for (i = 0; i < 1; i++)
    l_38[i] = 0UL;
  for (p_3 = 0; (p_3 <= (-12)); p_3 = safe_sub_func_uint64_t_u_u(p_3, 8)) {
    uint32_t *l_34 = &g_35;
    int32_t l_40[1];
    const uint16_t l_69 = 0x4F52L;
    int i;
    for (i = 0; i < 1; i++)
      l_40[i] = 0x1A1FD29CL;
    if ((safe_add_func_int16_t_s_s(
            p_4,
            ((safe_sub_func_uint32_t_u_u(
                 (((((*l_34) = g_8[1]) &
                    ((safe_div_func_uint16_t_u_u(
                         (((0xA69EED08E1597618LL ^ 0xF7503AE5685E9D07LL) | p_3),
                          l_38[0]),
                         p_5)) ^
                     l_39)),
                   p_3) ||
                  p_3),
                 l_40[0])) == l_41)))) {
      float *l_49 = &g_50;
      (*l_49) = ((safe_div_func_float_f_f(
                     (0x3.B016FEp-27 >
                      (safe_mul_func_float_f_f(
                          (safe_sub_func_float_f_f(g_27[0][1], g_8[1])), p_3))),
                     (-0x1.Ep-1))) >= 0x3.0p-1);
      return g_8[0];
    } else {
      int32_t *l_51 = &l_40[0];
      int32_t *l_52 = &l_40[0];
      int32_t *l_53 = &l_40[0];
      int32_t *l_54 = (void *)0;
      int32_t *l_55[4][4];
      int i, j;
      for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++)
          l_55[i][j] = &l_40[0];
      }
      ++l_61;
    }
    for (l_61 = (-16); (l_61 != 38);
         l_61 = safe_add_func_uint64_t_u_u(l_61, 6)) {
      int64_t *l_66[1][1];
      int32_t l_77 = 1L;
      uint64_t *l_78 = &l_38[0];
      struct S0 *l_80[4];
      struct S0 **l_79[4][4];
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 1; j++)
          l_66[i][j] = &g_56;
      }
      for (i = 0; i < 4; i++)
        l_80[i] = &g_81;
      for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++)
          l_79[i][j] = &l_80[0];
      }
      l_82 = (((((*l_78) = (((g_56 = p_4) !=
                             (safe_mod_func_uint64_t_u_u(
                                 l_69, ((((safe_lshift_func_int16_t_s_u(
                                              ((!(safe_rshift_func_uint8_t_u_s(
                                                   (safe_sub_func_uint8_t_u_u(
                                                       (p_3, 9UL), 0xAAL)),
                                                   l_77))) ||
                                               l_77),
                                              5)) > 0x23DF491560F218D3LL) ||
                                         p_3) ^
                                        0x67E28F630B13CFF8LL)))) ||
                            p_3)) ||
                0xA776A221E1226129LL) <= 0x30L),
              (void *)0);
    }
  }
  (*g_90) = (safe_div_func_int32_t_s_s(
      g_27[0][1],
      (safe_sub_func_int64_t_s_s(
          (~((safe_mul_func_uint8_t_u_u(g_59[1][1], (-5L))), p_3)), (-2L)))));
  return (*g_90);
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_8[i];
  }
  csmith_sink_ = g_22;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_24[i][j];
    }
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_27[i][j];
    }
  }
  csmith_sink_ = g_35;
  csmith_sink_ = g_50;
  csmith_sink_ = g_56;
  for (i = 0; i < 4; i++) {
    csmith_sink_ = g_58[i];
  }
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_59[i][j];
    }
  }
  csmith_sink_ = g_81.f0;
  csmith_sink_ = g_81.f1;
  csmith_sink_ = g_116;
  platform_main_end(0, 0);
  return 0;
}
