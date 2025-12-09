// Options:   --seed 300278 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_278.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  const int8_t f0;
  volatile uint64_t f1;
};

struct S1 {
  struct S0 f0;
  struct S0 f1;
  const uint32_t f2;
};

union U2 {
  const volatile uint64_t f0;
};

static int32_t g_2[2] = {0L, 0L};
static volatile int32_t g_5 = 0x67215912L;
static volatile int32_t g_6 = (-8L);
static int32_t g_7[3][2] = {{0x41449C9FL, 0x41449C9FL},
                            {0x41449C9FL, 0x41449C9FL},
                            {0x41449C9FL, 0x41449C9FL}};
static struct S1 g_24 = {{-5L, 0x9FA553FC2F92E6C0LL}, {-7L, 1UL}, 0x7684593FL};
static int32_t g_25[1] = {7L};
static int32_t g_29 = 0x8A996121L;
static uint64_t g_42[2] = {0x0312349124C6E12CLL, 0x0312349124C6E12CLL};
static int8_t g_44 = 1L;
static int32_t g_46[2][2] = {{0x561F6604L, 0x561F6604L},
                             {0x561F6604L, 0x561F6604L}};
static int8_t g_48 = 0x75L;
static uint32_t g_55 = 0x8F6F7E70L;
static int32_t *volatile g_60 = &g_29;
static int16_t g_102 = 4L;
static uint32_t g_104 = 0x68F5644FL;
static volatile struct S1 g_105 = {
    {0xEEL, 0x57E67F5904BE6A82LL}, {0x78L, 0xABE16947F7088E2DLL}, 0xE931266FL};
static int32_t *volatile g_112 = &g_25[0];
static union U2 g_114 = {0x6BE4B2277CB2DEB4LL};
static int32_t *volatile g_124 = &g_25[0];
static struct S0 g_132 = {0L, 0UL};
static uint16_t g_138 = 65535UL;
static int32_t *volatile g_140 = &g_2[1];

static int64_t func_1(void);
static int16_t func_14(uint32_t p_15, uint64_t p_16, uint8_t p_17, int8_t p_18,
                       uint32_t p_19);
static int32_t func_22(const uint16_t p_23);

static int64_t func_1(void) {
  uint32_t l_122 = 0xA4DE48ECL;
  uint16_t l_123 = 0x2677L;
  int8_t *l_136[2][3] = {{(void *)0, (void *)0, (void *)0},
                         {(void *)0, (void *)0, (void *)0}};
  int8_t **l_135[3][2];
  uint8_t l_150 = 246UL;
  int32_t l_152 = (-2L);
  int i, j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++)
      l_135[i][j] = &l_136[1][0];
  }
lbl_125:
  for (g_2[1] = 0; (g_2[1] >= (-22));
       g_2[1] = safe_sub_func_uint16_t_u_u(g_2[1], 4)) {
    for (g_7[0][0] = 0; (g_7[0][0] >= 0);
         g_7[0][0] = safe_add_func_int8_t_s_s(g_7[0][0], 8)) {
      const uint8_t l_113[3] = {0xF1L, 0xF1L, 0xF1L};
      int i;
      (*g_124) =
          (((safe_mul_func_uint8_t_u_u(
                ((g_7[0][0] <=
                  ((((((safe_mul_func_int16_t_s_s(
                           func_14(((((((safe_sub_func_uint32_t_u_u(
                                            0xB3493876L,
                                            func_22((g_24, 65532UL)))) ||
                                        g_24.f0.f1) &
                                       l_113[0]) >= g_46[0][1]) >= 0L) ^
                                    1L),
                                   l_113[0], g_2[0], g_46[0][0], g_24.f0.f0),
                           g_7[1][0])) &
                       l_122) == g_24.f1.f0) &&
                     g_7[0][0]) > 18446744073709551613UL) < g_7[2][1])),
                 1UL),
                l_122)) |
            0xEB91L) &
           l_123);
    }
    if (g_44)
      goto lbl_125;
    if ((*g_60))
      break;
  }
  for (g_102 = 24; (g_102 <= (-12)); --g_102) {
    uint16_t *l_137[3];
    const int32_t l_139 = (-6L);
    int8_t l_151[3][3] = {
        {(-1L), (-1L), (-1L)}, {0xFAL, 0xFAL, 0xFAL}, {(-1L), (-1L), (-1L)}};
    int i, j;
    for (i = 0; i < 3; i++)
      l_137[i] = &l_123;
    (*g_140) = (safe_sub_func_uint16_t_u_u(
        (safe_mod_func_int32_t_s_s(
            (g_132, ((safe_sub_func_uint16_t_u_u(
                         (g_138 |= (((void *)0 == l_135[0][1]) == 0L)), 1UL)) <
                     0x9C9769B2L)),
            l_139)),
        g_48));
    l_152 = ((((~g_7[0][0]),
               (safe_add_func_uint8_t_u_u(
                   (((safe_add_func_uint16_t_u_u(
                         (safe_sub_func_uint16_t_u_u(
                             g_105.f1.f1,
                             (g_138 &=
                              (l_151[1][2] ^= (safe_mul_func_uint8_t_u_u(
                                   (((((g_29 < l_122), g_24.f0.f0), (-2L)) &&
                                     l_150) |
                                    0x699CL),
                                   g_55)))))),
                         l_139)) > g_48),
                    l_151[2][1]),
                   0x39L))) ||
              0x128CL) &&
             l_150);
  }
  return g_105.f2;
}

static int16_t func_14(uint32_t p_15, uint64_t p_16, uint8_t p_17, int8_t p_18,
                       uint32_t p_19) {
  int32_t l_115 = 0L;
  int32_t *l_116[2];
  int i;
  for (i = 0; i < 2; i++)
    l_116[i] = &g_25[0];
  g_25[0] |= ((g_114, g_105), (g_2[1] && l_115));
  for (p_16 = 0; (p_16 <= 1); p_16 += 1) {
    uint32_t l_121 = 0xDCE6BA5CL;
    for (g_102 = 0; (g_102 <= 1); g_102 += 1) {
      int32_t l_120 = 1L;
      int i;
      l_120 ^= ((~(((safe_mul_func_uint16_t_u_u(0x7827L, g_42[g_102])) <
                    p_18) <= 0x8BE1L)) == g_24.f0.f0);
      l_121 = 1L;
    }
    return g_104;
  }
  return g_102;
}

static int32_t func_22(const uint16_t p_23) {
  uint8_t l_32 = 0x0BL;
  int32_t l_47 = 0xC8609E00L;
  int32_t *l_58 = &g_29;
  const int8_t *l_79 = &g_44;
lbl_85:
  for (g_25[0] = 0; (g_25[0] == (-15)); g_25[0]--) {
    int16_t l_31 = 0x947FL;
    int32_t l_49 = (-6L);
    int32_t l_50 = 0x15CD63CCL;
    int32_t l_52 = 0xD7AFF79CL;
    int32_t l_53 = (-1L);
    int32_t l_54 = 1L;
    if (p_23) {
      int32_t *l_28 = &g_29;
      int32_t *l_30[2];
      uint64_t *l_41 = &g_42[1];
      int8_t *l_43 = &g_44;
      int i;
      for (i = 0; i < 2; i++)
        l_30[i] = &g_29;
      --l_32;
      (*l_28) ^=
          (g_24.f0,
           ((((*l_43) = ((safe_sub_func_uint8_t_u_u(
                             g_24.f2, (safe_add_func_int32_t_s_s(
                                          ((safe_div_func_uint64_t_u_u(
                                               ((*l_41) = g_7[2][0]),
                                               18446744073709551613UL)) &&
                                           0xE8B7L),
                                          0xFCA5EB5AL)))) != p_23)),
             (void *)0) == (void *)0));
    } else {
      uint32_t *l_45[3];
      int32_t l_51 = 0x572AB10EL;
      int32_t *l_59 = (void *)0;
      int i;
      for (i = 0; i < 3; i++)
        l_45[i] = (void *)0;
      (*g_60) &= ((g_55--), ((l_58 = (void *)0) == &l_51));
    }
    for (l_54 = (-19); (l_54 == 15); ++l_54) {
      uint8_t *l_65 = &l_32;
      int32_t l_69[3][3] = {
          {0L, 0x40D8EB8AL, 0L}, {4L, 4L, 4L}, {0L, 0x40D8EB8AL, 0L}};
      int8_t *l_70[1];
      int32_t l_71[2][3];
      int32_t *l_72 = &l_52;
      int i, j;
      for (i = 0; i < 1; i++)
        l_70[i] = (void *)0;
      for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++)
          l_71[i][j] = (-4L);
      }
      (*l_72) = (safe_sub_func_int64_t_s_s(
          p_23,
          (((*l_65) &= g_2[1]) &&
           (l_71[1][1] ^= (l_49 = (l_53 = (safe_add_func_int64_t_s_s(
                                       ((+1UL) != l_69[2][2]), g_44))))))));
      (*l_72) = (*g_60);
    }
  }
  if (p_23) {
    const int8_t **l_80 = &l_79;
    const int8_t *l_82 = (void *)0;
    const int8_t **l_81 = &l_82;
    int32_t l_83 = 0L;
    int8_t l_84 = 1L;
    uint8_t l_90[3][1];
    int i, j;
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 1; j++)
        l_90[i][j] = 1UL;
    }
    if ((safe_rshift_func_uint16_t_u_u(
            (safe_sub_func_int8_t_s_s(
                (safe_add_func_int8_t_s_s(
                    ((((*l_81) = ((*l_80) = l_79)) != (void *)0),
                     (g_24.f1.f0 || l_83)),
                    l_83)),
                1UL)),
            l_84))) {
      if (g_29)
        goto lbl_85;
    } else {
      int32_t *l_86 = &l_83;
      int32_t *l_87 = &g_29;
      int32_t *l_88 = &l_83;
      int32_t *l_89[3][3] = {{&g_29, &g_29, &g_29},
                             {&g_29, &g_29, &g_7[0][0]},
                             {&g_7[0][0], &g_29, &g_7[0][0]}};
      int i, j;
      l_90[0][0]++;
    }
  } else {
    int32_t **l_93 = (void *)0;
    int32_t **l_94 = &l_58;
    int16_t *l_101 = &g_102;
    uint32_t *l_103 = &g_104;
    const uint64_t *l_111 = &g_42[0];
    (*l_94) = (void *)0;
    if (((safe_mul_func_uint8_t_u_u(
             (safe_div_func_int32_t_s_s(
                 ((safe_rshift_func_int16_t_s_s(((*l_101) = (&g_60 == &g_60)),
                                                ((g_25[0], l_103) != l_103))) <=
                  g_24.f2),
                 p_23)),
             g_25[0])) == g_24.f2)) {
      uint32_t l_109 = 0UL;
      int32_t *l_110 = &g_25[0];
      (*l_110) =
          ((&g_2[1] ==
            ((g_105, (!(safe_div_func_int8_t_s_s(l_109, p_23)))), &g_7[0][0])),
           p_23);
    } else {
      (*g_112) &= ((void *)0 != l_111);
    }
  }
  return l_47;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_2[i];
  }
  csmith_sink_ = g_5;
  csmith_sink_ = g_6;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_7[i][j];
    }
  }
  csmith_sink_ = g_24.f0.f0;
  csmith_sink_ = g_24.f0.f1;
  csmith_sink_ = g_24.f1.f0;
  csmith_sink_ = g_24.f1.f1;
  csmith_sink_ = g_24.f2;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_25[i];
  }
  csmith_sink_ = g_29;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_42[i];
  }
  csmith_sink_ = g_44;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_46[i][j];
    }
  }
  csmith_sink_ = g_48;
  csmith_sink_ = g_55;
  csmith_sink_ = g_102;
  csmith_sink_ = g_104;
  csmith_sink_ = g_105.f0.f0;
  csmith_sink_ = g_105.f0.f1;
  csmith_sink_ = g_105.f1.f0;
  csmith_sink_ = g_105.f1.f1;
  csmith_sink_ = g_105.f2;
  csmith_sink_ = g_114.f0;
  csmith_sink_ = g_132.f0;
  csmith_sink_ = g_132.f1;
  csmith_sink_ = g_138;
  platform_main_end(0, 0);
  return 0;
}
