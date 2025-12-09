// Options:   --seed 300245 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_245.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_2[3][2] = {{0x4EC2E0CFL, 0x4EC2E0CFL},
                                     {0x4EC2E0CFL, 0x4EC2E0CFL},
                                     {0x4EC2E0CFL, 0x4EC2E0CFL}};
static int32_t g_3[3][1] = {{0x730F94F3L}, {0x730F94F3L}, {0x730F94F3L}};
static uint8_t g_9 = 0xDBL;
static int32_t g_12 = (-5L);
static int16_t g_21 = 0xB3A0L;
static uint8_t g_24 = 0x52L;
static uint8_t *g_23 = &g_24;
static int8_t g_41[1] = {(-9L)};
static volatile uint32_t g_44 = 0xB6369DDAL;
static int32_t g_70 = 0x72C95C8FL;
static int8_t g_73 = 0x57L;
static int64_t g_76 = 0L;
static int32_t g_96 = 0x9EC2B408L;
static int8_t g_97 = (-5L);
static uint16_t g_114 = 0xBD67L;
static uint32_t g_134 = 4294967288UL;

static int32_t func_1(void);
static const int32_t func_15(int16_t p_16, uint8_t *p_17);
static int32_t func_25(int64_t p_26, uint8_t p_27, uint64_t p_28,
                       const int32_t p_29, uint8_t *p_30);

static int32_t func_1(void) {
  uint8_t *l_7 = (void *)0;
  uint8_t *l_8 = &g_9;
  int32_t l_20 = 3L;
  int64_t l_22 = 0x2B82C4475EE4C20FLL;
  uint8_t *l_100 = &g_9;
  uint32_t l_135 = 4294967288UL;
  for (g_3[1][0] = 0; (g_3[1][0] > (-4)); --g_3[1][0]) {
    uint8_t l_6 = 0x2DL;
    return l_6;
  }
  if ((((g_12 = ((*l_8)++)) !=
        (((safe_add_func_int32_t_s_s(
              (func_15(((l_22 |=
                         ((g_21 = (safe_rshift_func_uint16_t_u_s(l_20, 9))) &&
                          0x0EL)) |
                        (0xC099A56718E50348LL ^ g_3[1][0])),
                       g_23) >= l_20),
              g_97)) >= l_20),
         l_20)) != (-1L))) {
    int8_t *l_105 = &g_73;
    int32_t l_106 = 0x7EBF99C4L;
    int64_t *l_107 = &l_22;
    uint8_t l_116 = 249UL;
    if (((safe_rshift_func_uint8_t_u_s(
             (((*l_107) =
                   ((l_100 != (void *)0) >
                    (safe_div_func_int64_t_s_s(
                        ((((safe_rshift_func_int8_t_s_s(((*l_105) = 0x21L), 1)),
                           0x39L),
                          (void *)0) != (void *)0),
                        l_106)))) != 6UL),
             4)) ^
         l_20)) {
      int32_t *l_108 = &g_3[1][0];
      l_108 = &l_20;
    } else {
      int64_t **l_109 = &l_107;
      int32_t l_112[1];
      uint16_t *l_113[2][1];
      int32_t *l_115[1];
      int i, j;
      for (i = 0; i < 1; i++)
        l_112[i] = 4L;
      for (i = 0; i < 2; i++) {
        for (j = 0; j < 1; j++)
          l_113[i][j] = &g_114;
      }
      for (i = 0; i < 1; i++)
        l_115[i] = &l_112[0];
      l_116 = (g_3[1][0] =
                   ((((*l_109) = &g_76) == (void *)0) >=
                    (g_114 &=
                     ((safe_mul_func_uint8_t_u_u((l_112[0], (*g_23)), g_41[0])),
                      g_44))));
    }
    for (g_76 = 0; (g_76 == (-19)); g_76 = safe_sub_func_uint8_t_u_u(g_76, 5)) {
      int8_t l_119 = 0x58L;
      l_119 = 0x496EB75EL;
    }
  } else {
    volatile int32_t *l_121 = &g_2[1][0];
    volatile int32_t **l_120 = &l_121;
    int32_t l_132[2];
    uint32_t *l_133 = &g_134;
    int i;
    for (i = 0; i < 2; i++)
      l_132[i] = 0L;
    (*l_120) = &g_2[0][1];
    (**l_120) = (safe_rshift_func_uint16_t_u_s(
        (safe_div_func_int16_t_s_s(
            ((safe_mod_func_uint32_t_u_u(
                 0x801B025BL,
                 ((*l_133) =
                      ((((safe_add_func_int8_t_s_s(
                             l_22, (((safe_mod_func_uint8_t_u_u(
                                         ((g_96, (*g_23)), (*l_121)), (-1L))) &&
                                     l_22) ||
                                    g_12))) ||
                         0xAAC1EF8BL) >= g_21) ^
                       l_132[1])))) ||
             0x5C4AL),
            g_3[2][0])),
        l_135));
  }
  return g_2[1][0];
}

static const int32_t func_15(int16_t p_16, uint8_t *p_17) {
  int8_t *l_40 = &g_41[0];
  int32_t l_42 = 0x2324067BL;
  int16_t *l_43[2][2];
  const int32_t l_45 = (-10L);
  int32_t *l_95 = &g_96;
  int i, j;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++)
      l_43[i][j] = &g_21;
  }
  (*l_95) |=
      (func_25((&g_24 !=
                ((safe_rshift_func_int16_t_s_u(
                     (l_42 = ((safe_add_func_uint16_t_u_u(
                                  (((!(safe_lshift_func_int8_t_s_u(
                                        ((*l_40) ^= (safe_add_func_int8_t_s_s(
                                             p_16, 250UL))),
                                        1))) != 1UL) ^
                                   l_42),
                                  3L)) < l_42)),
                     g_44)),
                 &g_24)),
               (*g_23), p_16, l_45, p_17) == 0L);
  return p_16;
}

static int32_t func_25(int64_t p_26, uint8_t p_27, uint64_t p_28,
                       const int32_t p_29, uint8_t *p_30) {
  uint32_t l_49 = 0x9ADBD3D3L;
  const uint16_t l_71 = 8UL;
  int32_t l_77 = (-1L);
  int16_t *l_93 = &g_21;
  for (p_27 = 0; (p_27 <= 0); p_27 += 1) {
    int32_t *l_46 = &g_3[2][0];
    int32_t *l_47 = &g_3[1][0];
    int32_t *l_48 = &g_3[0][0];
    int64_t l_80[3][1];
    int32_t l_83 = 6L;
    uint32_t l_84 = 3UL;
    int i, j;
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 1; j++)
        l_80[i][j] = (-1L);
    }
    --l_49;
    for (g_44 = 0; g_44 < 1; g_44 += 1) {
      g_41[g_44] = 0x45L;
    }
    for (p_28 = 0; (p_28 <= 1); p_28 += 1) {
      int8_t *l_72 = &g_73;
      int64_t *l_74 = (void *)0;
      int64_t *l_75[3][3] = {
          {&g_76, &g_76, &g_76}, {&g_76, &g_76, &g_76}, {&g_76, &g_76, &g_76}};
      int32_t *l_78 = &l_77;
      int32_t *l_79 = &l_77;
      int32_t *l_81 = (void *)0;
      int32_t *l_82[3];
      int i, j;
      for (i = 0; i < 3; i++)
        l_82[i] = &l_77;
      g_2[p_27][p_27] =
          (l_77 =
               (((*g_23) = g_2[(p_27 + 1)][p_28]),
                ((safe_add_func_uint32_t_u_u(
                     (safe_add_func_uint32_t_u_u(
                         (safe_div_func_int64_t_s_s(
                             (g_76 &= (safe_lshift_func_int8_t_s_s(
                                  ((*l_72) =
                                       (g_41[p_27] = (~(+(
                                            (safe_lshift_func_uint16_t_u_u(
                                                (g_70 = (safe_lshift_func_uint8_t_u_s(
                                                     (((safe_rshift_func_int8_t_s_u(
                                                           g_2[p_27][p_28],
                                                           5)) >=
                                                       (safe_add_func_int32_t_s_s(
                                                           ((*l_46) =
                                                                ((-3L) == 0L)),
                                                           g_41[p_27]))) ||
                                                      g_41[p_27]),
                                                     5))),
                                                8)) >= l_71))))),
                                  6))),
                             0xE1ABB416C011945BLL)),
                         0x2E653D3AL)),
                     0L)) < 7L)));
      ++l_84;
    }
  }
  for (p_28 = 24; (p_28 < 60); p_28 = safe_add_func_uint8_t_u_u(p_28, 8)) {
    int16_t *l_91 = (void *)0;
    int16_t **l_92 = &l_91;
    int32_t *l_94 = &l_77;
    (*l_94) = (p_29 !=
               (((safe_add_func_int16_t_s_s((((*l_92) = l_91) == l_93), 0UL)) |
                 255UL) ^
                (-1L)));
    return g_2[1][0];
  }
  return p_29;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_2[i][j];
    }
  }
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_3[i][j];
    }
  }
  csmith_sink_ = g_9;
  csmith_sink_ = g_12;
  csmith_sink_ = g_21;
  csmith_sink_ = g_24;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_41[i];
  }
  csmith_sink_ = g_44;
  csmith_sink_ = g_70;
  csmith_sink_ = g_73;
  csmith_sink_ = g_76;
  csmith_sink_ = g_96;
  csmith_sink_ = g_97;
  csmith_sink_ = g_114;
  csmith_sink_ = g_134;
  platform_main_end(0, 0);
  return 0;
}
