// Options:   --seed 300251 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_251.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  int16_t f0;
  volatile int32_t f1;
  const int32_t f2;
};

static volatile int32_t g_3 = 0xF1D8987FL;
static volatile int32_t g_4[3][3] = {{0x5A5EFA20L, 0x5A5EFA20L, 0x5A5EFA20L},
                                     {(-8L), 0xC5735E4BL, (-8L)},
                                     {0x5A5EFA20L, 0x5A5EFA20L, 0x5A5EFA20L}};
static int32_t g_5 = 0x092F644AL;
static uint8_t g_25 = 253UL;
static uint64_t g_28 = 0x5C2F1FCC1031C36BLL;
static uint16_t g_30 = 1UL;
static int64_t g_46 = 1L;
static int32_t g_49 = (-1L);
static struct S0 g_52 = {5L, -3L, 0xDDA30181L};
static int32_t *volatile g_68 = &g_49;
static int32_t g_70[1][1] = {{0x08F94BBBL}};
static int8_t g_83 = 9L;
static int32_t **volatile g_88 = (void *)0;
static volatile int64_t g_101 = 0x28385865AEC415B4LL;
static int32_t g_109 = 0x73896F98L;
static struct S0 g_113[2] = {{0L, -6L, 0xDCC78C8CL}, {0L, -6L, 0xDCC78C8CL}};

static uint8_t func_1(void);
static int8_t func_7(uint8_t p_8, uint16_t p_9, const uint16_t p_10,
                     uint32_t p_11, uint32_t p_12);
static uint16_t func_21(uint16_t p_22);

static uint8_t func_1(void) {
  int64_t l_2[2][1];
  int16_t l_26 = 0x2845L;
  int i, j;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 1; j++)
      l_2[i][j] = 0xAFE01BD97A888ADALL;
  }
  for (g_5 = 0; (g_5 <= 0); g_5 += 1) {
    int8_t l_6 = 0x1DL;
    uint8_t *l_23 = (void *)0;
    uint8_t *l_24[2][2] = {{&g_25, &g_25}, {&g_25, &g_25}};
    uint64_t *l_27 = &g_28;
    uint16_t *l_29 = &g_30;
    int32_t l_31 = (-4L);
    int32_t *l_108 = &g_109;
    uint16_t l_115 = 0xA23BL;
    int i, j;
    (*l_108) |=
        (l_6 <=
         func_7(
             (safe_lshift_func_uint16_t_u_s(
                 (safe_mod_func_uint32_t_u_u(
                     (safe_add_func_uint8_t_u_u(
                         (safe_mul_func_uint16_t_u_u(
                             func_21((l_31 ^=
                                      ((*l_29) =
                                           (((*l_27) = (g_4[1][2] >=
                                                        ((l_26 |= (g_5 < g_5)) ^
                                                         0x77L))) &&
                                            2UL)))),
                             0x8ED5L)),
                         0xA1L)),
                     g_46)),
                 l_6)),
             g_52.f2, l_2[0][0], g_46, g_46));
    for (g_52.f0 = 0; (g_52.f0 >= 0); g_52.f0 -= 1) {
      const int32_t *l_111 = &g_49;
      const int32_t **l_110 = &l_111;
      (*l_110) = (void *)0;
    }
    for (g_52.f0 = 0; (g_52.f0 >= 0); g_52.f0 -= 1) {
      int16_t *l_114 = (void *)0;
      int i, j;
      l_31 |= (safe_unary_minus_func_int32_t_s(
          ((g_113[1], (l_115 ^= l_2[(g_52.f0 + 1)][g_5])) |
           (safe_rshift_func_int16_t_s_u(
               ((l_2[(g_52.f0 + 1)][g_52.f0], l_2[(g_52.f0 + 1)][g_5]) &
                (*l_108)),
               l_2[(g_52.f0 + 1)][g_5])))));
      if ((*g_68))
        break;
    }
  }
  return l_2[0][0];
}

static int8_t func_7(uint8_t p_8, uint16_t p_9, const uint16_t p_10,
                     uint32_t p_11, uint32_t p_12) {
  int16_t l_81[2];
  struct S0 **const l_86 = (void *)0;
  int32_t *l_87 = &g_70[0][0];
  int32_t l_97 = 0x609311A0L;
  int32_t l_99 = 0x77F61DB4L;
  int32_t l_100[1][2];
  int i, j;
  for (i = 0; i < 2; i++)
    l_81[i] = 2L;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 2; j++)
      l_100[i][j] = 0x93F07CA4L;
  }
  if (p_9) {
    int32_t *l_69 = &g_70[0][0];
    (*l_69) &= (*g_68);
  } else {
    struct S0 *l_78 = (void *)0;
    struct S0 **l_77 = &l_78;
    int8_t *l_82[3];
    int32_t l_84 = 0x785DC571L;
    int32_t l_85 = (-1L);
    int32_t l_98[3][3] = {
        {0L, 0L, 0xBE56F420L}, {0L, 0L, 0xBE56F420L}, {0L, 0L, 0xBE56F420L}};
    int32_t l_103 = 1L;
    uint32_t l_105 = 1UL;
    int i, j;
    for (i = 0; i < 3; i++)
      l_82[i] = &g_83;
    if (((((g_83 = (((safe_rshift_func_int8_t_s_u(
                         ((l_84 = (((safe_lshift_func_uint8_t_u_u(
                                        ((((safe_rshift_func_uint8_t_u_s(
                                               ((((*l_77) = &g_52) ==
                                                 ((((safe_div_func_uint8_t_u_u(
                                                        p_12, p_11)) < 0UL),
                                                   5L),
                                                  (void *)0)) &&
                                                p_11),
                                               0)) &
                                           l_81[1]) |
                                          p_9),
                                         p_8),
                                        p_10)),
                                    18446744073709551611UL),
                                   1L)) &&
                          p_12),
                         l_85)),
                     (void *)0) == l_86)),
           g_4[2][1]),
          0UL),
         l_85)) {
      l_87 = l_87;
    } else {
      int32_t *l_89 = &g_70[0][0];
      int32_t *l_90 = (void *)0;
      int32_t *l_91 = &l_85;
      int32_t *l_92 = (void *)0;
      int32_t *l_93 = &g_70[0][0];
      int32_t *l_94 = (void *)0;
      int32_t *l_95 = (void *)0;
      int32_t *l_96[3][2] = {{&l_84, &l_84}, {&l_84, &l_84}, {&l_84, &l_84}};
      int32_t l_102 = (-7L);
      int64_t l_104 = 0x165F177B5993E3A2LL;
      int i, j;
      l_105++;
    }
  }
  return (*l_87);
}

static uint16_t func_21(uint16_t p_22) {
  const uint32_t l_55 = 0UL;
  uint16_t *l_65 = (void *)0;
  uint16_t *l_66[1];
  uint8_t *l_67 = &g_25;
  int i;
  for (i = 0; i < 1; i++)
    l_66[i] = &g_30;
  for (g_25 = 0; (g_25 < 30); g_25++) {
    uint32_t l_41 = 0x6B9117A5L;
    struct S0 *l_51 = &g_52;
    struct S0 **l_50 = &l_51;
    for (g_28 = 13; (g_28 != 13); g_28 = safe_add_func_uint64_t_u_u(g_28, 6)) {
      uint32_t l_47 = 0xC90ACEFCL;
      int32_t *l_48 = &g_49;
      (*l_48) &= (+(safe_mod_func_int32_t_s_s(
          (((((((246UL ^ (safe_rshift_func_uint16_t_u_s(l_41, 0))) >
                (safe_div_func_uint64_t_u_u(
                    (safe_sub_func_int8_t_s_s((0xEFL > g_4[2][2]), g_5)),
                    g_28))) >= g_46) > g_46) &&
             0x4FCEL) <= p_22) &&
           g_5),
          l_47)));
    }
    (*l_50) = (void *)0;
  }
  (*g_68) |=
      ((safe_mod_func_uint16_t_u_u(
           (l_55 <= (0x70A6L !=
                     ((!(safe_sub_func_uint64_t_u_u(
                          (safe_rshift_func_int16_t_s_s(
                              (safe_lshift_func_uint8_t_u_s(
                                  ((*l_67) = (safe_mul_func_uint8_t_u_u(
                                       (((g_30 ^= 65529UL) || (-1L)), g_52.f0),
                                       g_52.f0))),
                                  6)),
                              p_22)),
                          (-1L)))) == 5L))),
           l_55)) &
       l_55);
  return g_4[2][2];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_4[i][j];
    }
  }
  csmith_sink_ = g_5;
  csmith_sink_ = g_25;
  csmith_sink_ = g_28;
  csmith_sink_ = g_30;
  csmith_sink_ = g_46;
  csmith_sink_ = g_49;
  csmith_sink_ = g_52.f0;
  csmith_sink_ = g_52.f1;
  csmith_sink_ = g_52.f2;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_70[i][j];
    }
  }
  csmith_sink_ = g_83;
  csmith_sink_ = g_101;
  csmith_sink_ = g_109;
  for (i = 0; i < 2; i++) {
  }
  platform_main_end(0, 0);
  return 0;
}
