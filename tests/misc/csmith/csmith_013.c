// Options:   --seed 100013 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_013.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_9 = 0xA1E94870L;
static uint8_t g_13 = 247UL;
static volatile int8_t g_18 = 0x14L;
static volatile int32_t g_19 = 0x4A219909L;
static volatile int16_t g_21 = 0x8360L;
static int32_t g_22 = 5L;
static volatile uint8_t g_23[4][4] = {{1UL, 0UL, 0UL, 1UL},
                                      {1UL, 0UL, 0UL, 1UL},
                                      {1UL, 0UL, 0UL, 1UL},
                                      {1UL, 0UL, 0UL, 1UL}};
static int32_t *g_27 = &g_22;
static int32_t **volatile g_26 = &g_27;
static uint32_t g_45[3][4] = {
    {0UL, 18446744073709551615UL, 2UL, 18446744073709551615UL},
    {18446744073709551615UL, 0x6A5A8E70L, 2UL, 2UL},
    {0UL, 0UL, 18446744073709551615UL, 2UL}};
static int32_t g_58[2] = {0x0583186DL, 0x0583186DL};
static uint16_t g_62 = 65535UL;
static int32_t **volatile g_67 = (void *)0;
static int32_t g_108 = (-7L);
static int32_t *const g_107[2] = {&g_108, &g_108};
static int32_t *const *g_106[2] = {&g_107[0], &g_107[0]};
static uint8_t g_112 = 7UL;

static uint32_t func_1(void);
static int32_t *func_2(int32_t p_3, int64_t p_4, int8_t p_5, int32_t *p_6,
                       uint32_t p_7);

static uint32_t func_1(void) {
  int32_t *const l_8 = &g_9;
  uint8_t *l_12 = &g_13;
  int32_t *l_14 = &g_9;
  int32_t *l_43 = &g_22;
  int32_t l_92[2];
  int32_t l_97 = 0xD0F00198L;
  int32_t l_99[3];
  uint32_t l_110[2];
  int i;
  for (i = 0; i < 2; i++)
    l_92[i] = (-7L);
  for (i = 0; i < 3; i++)
    l_99[i] = 0xDC33B3E5L;
  for (i = 0; i < 2; i++)
    l_110[i] = 1UL;
lbl_36:
  (*g_26) = func_2(
      (l_8 == &g_9),
      ((safe_mod_func_uint8_t_u_u(
           ((*l_12) = (((((*l_8) >= 65535UL) != g_9) >= g_9) == 4294967287UL)),
           g_9)) >= g_9),
      (*l_8), l_14, g_9);
  if ((g_23[3][2] ^
       (safe_mul_func_int16_t_s_s(
           (~g_22), (safe_mod_func_uint8_t_u_u((*l_8), 0x84L)))))) {
    uint32_t l_33 = 0xC2130BECL;
    int8_t l_35 = (-1L);
    int32_t l_47 = 0x89059105L;
    int32_t l_60 = 0x1B3380F2L;
    int32_t l_61[2];
    int i;
    for (i = 0; i < 2; i++)
      l_61[i] = (-3L);
    for (g_9 = 0; (g_9 <= 3); g_9 += 1) {
      int32_t *l_34[4][2] = {
          {&g_22, &g_22}, {&g_22, &g_22}, {&g_22, &g_22}, {&g_22, &g_22}};
      int i, j;
      l_35 = ((**g_26) == l_33);
      if (g_9)
        goto lbl_36;
      for (g_13 = 0; (g_13 <= 3); g_13 += 1) {
        int i, j;
        return g_23[g_9][g_13];
      }
    }
    if ((safe_sub_func_int32_t_s_s(
            (((g_22 > g_21),
              ((((safe_add_func_uint8_t_u_u(g_23[3][0], g_13)) ^ g_13) &&
                g_19) == 0x60L)),
             (*g_27)),
            (*l_14)))) {
      uint32_t *l_44 = &g_45[2][2];
      int32_t l_46 = 0xE9ABA4A7L;
      int16_t l_56 = 0L;
      int32_t l_57 = 4L;
      if ((((((((*l_44) = (safe_lshift_func_int8_t_s_u(
                    ((*g_26) != (l_43 = (void *)0)),
                    (g_13 ^= (&g_27 == (void *)0))))),
               (*l_8)) ||
              l_46) &&
             g_18),
            l_47) != 0xDEF23EAFL)) {
        int32_t *l_48 = (void *)0;
        int32_t *l_49 = &g_9;
        int32_t *l_50 = &l_47;
        int32_t *l_51 = &g_22;
        int32_t *l_52 = &l_46;
        int32_t *l_53 = (void *)0;
        int32_t *l_54 = &g_9;
        int32_t *l_55[3];
        int32_t l_59 = 0L;
        int i;
        for (i = 0; i < 3; i++)
          l_55[i] = &g_22;
        --g_62;
      } else {
        int64_t l_65 = 0xA9C08A91624B3AEBLL;
        int8_t *l_66 = &l_35;
        int32_t *l_68 = (void *)0;
        l_68 = func_2((*g_27), l_47,
                      ((*l_66) = (((g_62, g_23[3][1]) == l_65) & g_9)), &l_60,
                      l_61[1]);
      }
    } else {
      for (g_9 = 1; (g_9 >= 0); g_9 -= 1) {
        int i;
        return g_58[g_9];
      }
    }
  } else {
    const uint16_t l_82 = 65531UL;
    int32_t l_93 = 0x84ADD174L;
    int32_t l_95 = 4L;
    int32_t l_96 = 1L;
    int32_t l_98 = 0x07845806L;
    int32_t l_100[1];
    int32_t *l_111[3];
    int i;
    for (i = 0; i < 1; i++)
      l_100[i] = (-2L);
    for (i = 0; i < 3; i++)
      l_111[i] = (void *)0;
    if ((safe_sub_func_int16_t_s_s(
            ((safe_unary_minus_func_int64_t_s((safe_mul_func_uint16_t_u_u(
                 (*l_8),
                 (safe_mul_func_uint8_t_u_u(
                     (~((-1L) && ((safe_add_func_uint32_t_u_u(
                                      ((safe_mul_func_uint16_t_u_u(
                                           ((!(0UL >= (-1L))) != (*l_43)),
                                           g_13)) < l_82),
                                      l_82)),
                                  g_18))),
                     g_58[1])))))) ||
             0x3BFD2720855C5D77LL),
            l_82))) {
      int32_t *l_85 = &g_58[1];
      int32_t *l_86 = &g_9;
      int32_t *l_87 = &g_9;
      int32_t *l_88 = &g_58[0];
      int32_t l_89 = 0x0B88CC77L;
      int32_t *l_90 = &g_58[0];
      int32_t *l_91[4][4] = {{&g_22, &g_22, &g_22, &g_22},
                             {&g_22, &g_22, &g_22, &g_22},
                             {&g_22, &g_22, &g_22, &g_22},
                             {&g_22, &g_22, &g_22, &g_22}};
      int64_t l_94 = 0x764E3E385C008FFCLL;
      int32_t l_101 = 0x0AE147BCL;
      uint32_t l_102[4][1] = {{0x0693EAE9L},
                              {18446744073709551615UL},
                              {0x0693EAE9L},
                              {18446744073709551615UL}};
      int i, j;
      for (g_62 = 0; (g_62 < 16); ++g_62) {
        if ((**g_26))
          break;
      }
      l_102[2][0]++;
    } else {
      uint16_t *l_109 = &g_62;
      (*l_14) =
          ((*l_43) =
               ((g_45[0][1] !=
                 (((((*l_109) = (!(0x6DFF3C42993B2435LL &&
                                   ((g_106[1] = &g_27) == &g_27)))) < l_110[0]),
                   l_100[0]) ^
                  0x4BDB83C02C40A721LL)) >= 1UL));
    }
    g_112++;
  }
  return g_22;
}

static int32_t *func_2(int32_t p_3, int64_t p_4, int8_t p_5, int32_t *p_6,
                       uint32_t p_7) {
  int32_t **l_15 = (void *)0;
  int32_t *l_16 = &g_9;
  int32_t *l_17[3][4] = {{&g_9, &g_9, &g_9, &g_9},
                         {&g_9, &g_9, &g_9, &g_9},
                         {&g_9, &g_9, &g_9, &g_9}};
  int64_t l_20 = 0x79096A9CBDE6B786LL;
  int i, j;
  p_6 = &p_3;
  g_23[3][0]++;
  return l_17[0][1];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_9;
  csmith_sink_ = g_13;
  csmith_sink_ = g_18;
  csmith_sink_ = g_19;
  csmith_sink_ = g_21;
  csmith_sink_ = g_22;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_23[i][j];
    }
  }
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_45[i][j];
    }
  }
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_58[i];
  }
  csmith_sink_ = g_62;
  csmith_sink_ = g_108;
  csmith_sink_ = g_112;
  platform_main_end(0, 0);
  return 0;
}
