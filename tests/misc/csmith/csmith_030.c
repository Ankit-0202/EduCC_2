// Options:   --seed 100030 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_030.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  volatile int16_t f0;
  int32_t f1;
};

union U1 {
  int8_t *f0;
};

union U2 {
  const uint32_t f0;
};

static int8_t *volatile g_4[2] = {(void *)0, (void *)0};
static int8_t g_6 = 0xBFL;
static int32_t g_15[3] = {1L, 1L, 1L};
static int32_t g_16 = 1L;
static int8_t *g_36 = &g_6;
static int64_t g_54 = 0x33AB1ADF13F3F2C7LL;
static union U0 g_62 = {0x2499L};
static uint64_t g_85 = 0x35ED9E4BB11E4031LL;
static union U2 g_86[1] = {{1UL}};
static int32_t *volatile g_90 = &g_16;
static volatile union U0 g_110 = {-3L};
static volatile int16_t g_120 = 0L;
static uint64_t g_155 = 0x34082CCC8094C73ALL;
static const int32_t *g_163 = &g_15[0];
static const int32_t **volatile g_162 = &g_163;
static union U1 g_167 = {0};

static union U1 func_1(void);
static union U2 func_9(const int8_t *p_10, const uint8_t p_11,
                       int8_t *const p_12, int8_t *p_13);

static union U1 func_1(void) {
  int8_t *l_5 = &g_6;
  union U1 l_89 = {0};
  const int32_t l_97 = 0xA0FB3452L;
  uint8_t l_111 = 0xE2L;
  int32_t l_127 = 0x0DBADF69L;
  uint16_t l_148 = 0x510CL;
  if ((safe_rshift_func_uint16_t_u_u(
          ((g_4[0] == l_5) |
           (safe_mul_func_int8_t_s_s((func_9(&g_6, g_6, l_5, l_5), (*g_36)),
                                     0x2CL))),
          10))) {
    const uint8_t l_95 = 0x2AL;
    int32_t *l_96 = &g_16;
    if (g_62.f0) {
      for (g_54 = 0; (g_54 <= 24); g_54++) {
        return l_89;
      }
      (*g_90) &= g_54;
    } else {
      return l_89;
    }
    for (g_85 = 0; (g_85 < 51); g_85 = safe_add_func_int16_t_s_s(g_85, 6)) {
      for (g_54 = 15; (g_54 <= 24); g_54 = safe_add_func_uint8_t_u_u(g_54, 2)) {
        if (l_95)
          break;
        l_96 = l_96;
      }
      (*l_96) = l_97;
    }
  } else {
    int32_t *l_108 = (void *)0;
    int32_t l_109[1][2];
    int32_t l_112 = 0x26F2AC0DL;
    int i, j;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 2; j++)
        l_109[i][j] = (-5L);
    }
    if ((l_112 = (safe_rshift_func_int16_t_s_u(
             l_97, (((((safe_mod_func_uint8_t_u_u(
                           (((l_109[0][0] |=
                              (((safe_rshift_func_uint8_t_u_s(
                                    l_97, (safe_rshift_func_uint8_t_u_s(
                                              (safe_mul_func_int16_t_s_s(
                                                  g_86[0].f0, g_54)),
                                              0)))) &&
                                g_62.f0),
                               l_97)),
                             (void *)0) != &g_36),
                           g_85)) &&
                       1UL) == l_97),
                     g_110),
                    l_111))))) {
      int32_t l_128 = 0xCE275991L;
      int32_t *l_132 = (void *)0;
      int32_t *l_133 = &g_16;
      int32_t *l_134 = (void *)0;
      int32_t *l_135 = &g_15[0];
      int32_t *l_136 = (void *)0;
      int32_t *l_137 = &l_109[0][1];
      int32_t *l_138 = (void *)0;
      int32_t *l_139 = &l_109[0][0];
      int32_t *l_140 = &l_127;
      int32_t *l_141 = &g_15[0];
      int32_t *l_142 = &l_109[0][0];
      int32_t *l_143 = (void *)0;
      int32_t *l_144 = &g_62.f1;
      int32_t *l_145 = &g_16;
      int32_t *l_146 = (void *)0;
      int32_t *l_147[3];
      int i;
      for (i = 0; i < 3; i++)
        l_147[i] = (void *)0;
      for (l_112 = 11; (l_112 == 24); ++l_112) {
        int32_t *l_115 = &g_15[0];
        int32_t *l_116 = &g_15[2];
        int32_t *l_117 = (void *)0;
        int32_t *l_118 = (void *)0;
        int32_t *l_119 = (void *)0;
        int32_t *l_121 = (void *)0;
        int32_t *l_122 = &g_15[0];
        int32_t *l_123 = &g_15[0];
        int32_t *l_124 = &g_15[0];
        int32_t *l_125 = &g_15[0];
        int32_t *l_126[2];
        uint64_t l_129 = 0xAE6F46489DC94FE3LL;
        int i;
        for (i = 0; i < 2; i++)
          l_126[i] = &g_16;
        --l_129;
      }
      --l_148;
    } else {
      uint16_t *l_152 = (void *)0;
      uint16_t *l_153 = (void *)0;
      uint16_t *l_154[1][3];
      int32_t l_166 = 0x9802BA47L;
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 3; j++)
          l_154[i][j] = &l_148;
      }
      if ((~(0xD07DL !=
             ((g_155--) |
              (safe_add_func_int16_t_s_s(
                  (((0x1901L != (safe_add_func_uint8_t_u_u(
                                    ((((((*g_90) ^ (-1L)) == g_86[0].f0), g_54),
                                      18446744073709551614UL) ^
                                     l_111),
                                    l_127))) |
                    g_85) == 0x88185611DFC2BB03LL),
                  g_54)))))) {
        int32_t **l_164[3][3] = {{&l_108, &l_108, &l_108},
                                 {&l_108, &l_108, &l_108},
                                 {&l_108, &l_108, &l_108}};
        int i, j;
        (*g_162) = &l_97;
        (*g_162) = (void *)0;
      } else {
        int32_t *l_165[1];
        int i;
        for (i = 0; i < 1; i++)
          l_165[i] = &l_127;
        l_166 &= 0L;
        return g_167;
      }
    }
  }
  return g_167;
}

static union U2 func_9(const int8_t *p_10, const uint8_t p_11,
                       int8_t *const p_12, int8_t *p_13) {
  int32_t l_37[1];
  int i;
  for (i = 0; i < 1; i++)
    l_37[i] = 3L;
  if ((((void *)0 == p_10) <= 0xB7AB61B583DC0E3ELL)) {
    uint8_t l_14[3][2] = {{0xDEL, 0xDEL}, {0xDEL, 0xDEL}, {0xDEL, 0xDEL}};
    int32_t l_49 = (-10L);
    int32_t l_51 = 9L;
    int32_t l_53[1][3];
    int16_t l_55 = 0xB0C6L;
    int i, j;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 3; j++)
        l_53[i][j] = 0x841C2FCEL;
    }
    for (g_6 = 1; (g_6 >= 0); g_6 -= 1) {
      for (g_15[0] = 0; (g_15[0] <= 1); g_15[0] += 1) {
        int i, j;
        if (l_14[g_15[0]][g_15[0]])
          break;
      }
      for (g_16 = 1; (g_16 >= 0); g_16 -= 1) {
        int32_t *l_17 = &g_15[2];
        int i, j;
        (*l_17) ^= (p_10 == p_13);
        if (l_14[g_6][g_6])
          continue;
      }
    }
    if ((p_11 ^
         ((65530UL ||
           (((safe_mod_func_int16_t_s_s(
                 ((safe_lshift_func_int8_t_s_u(l_14[1][0], 3)) < 0L), 0x67F6L)),
             p_11),
            g_6)) > (-5L)))) {
      int8_t *l_33 = &g_6;
      int8_t **l_32 = &l_33;
      int8_t *l_35 = (void *)0;
      int8_t **l_34 = &l_35;
      for (g_16 = (-16); (g_16 != 15);
           g_16 = safe_add_func_uint16_t_u_u(g_16, 1)) {
        int32_t *l_24 = (void *)0;
        int32_t *l_25[1];
        int i;
        for (i = 0; i < 1; i++)
          l_25[i] = &g_15[2];
        g_15[1] = (-7L);
      }
      g_15[2] &=
          ((safe_mul_func_int16_t_s_s(
               0x9CDEL,
               (safe_mod_func_uint16_t_u_u(
                   ((((safe_add_func_int16_t_s_s(
                          (((*l_34) = ((*l_32) = (void *)0)) != (g_36 = p_13)),
                          g_16)) != l_37[0]) &
                     l_37[0]) == p_11),
                   65535UL)))) > 0x4CCC41425452E2CCLL);
    } else {
      uint32_t l_42 = 0x84EBF8C3L;
      int32_t l_48 = 0x139A53AAL;
      int32_t l_50 = 0x1672C651L;
      int32_t l_52[4] = {1L, 1L, 1L, 1L};
      uint16_t l_56 = 0xC39AL;
      union U1 l_59 = {0};
      int i;
      if (p_11) {
        int32_t *l_38 = (void *)0;
        int32_t *l_39 = &l_37[0];
        int32_t *l_40 = (void *)0;
        int32_t *l_41[2];
        int i;
        for (i = 0; i < 2; i++)
          l_41[i] = &g_15[0];
        --l_42;
      } else {
        int32_t *l_45 = &l_37[0];
        int32_t *l_46 = &l_37[0];
        int32_t *l_47[1];
        union U1 *l_60 = &l_59;
        union U0 *l_61 = &g_62;
        union U0 **l_63 = &l_61;
        int i;
        for (i = 0; i < 1; i++)
          l_47[i] = &g_15[2];
        ++l_56;
        (*l_63) = (((*l_60) = l_59), l_61);
      }
    }
  } else {
    const int32_t l_64 = 2L;
    int32_t l_83 = 1L;
    if ((l_64 && (safe_mod_func_uint64_t_u_u(((-4L) == 0x61L), l_64)))) {
      int32_t l_67 = (-1L);
      int32_t *l_68 = (void *)0;
      int32_t *l_69 = &l_37[0];
      g_15[0] |= ((*l_69) &= l_67);
    } else {
      union U2 l_70[3] = {{0UL}, {0UL}, {0UL}};
      int i;
      return l_70[2];
    }
    for (g_6 = 0; (g_6 < (-12)); g_6--) {
      uint64_t *l_84 = &g_85;
      l_37[0] = (safe_sub_func_int64_t_s_s(
          (p_11 ==
           ((~(0x4BC67B678304AF2CLL >=
               ((*l_84) = (safe_lshift_func_uint16_t_u_s(
                    ((+((safe_sub_func_int64_t_s_s(l_64, l_83)) && 0L)) &&
                     0xD8C8EF01L),
                    l_83))))) == l_64)),
          18446744073709551615UL));
    }
  }
  return g_86[0];
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_6;
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_15[i];
  }
  csmith_sink_ = g_16;
  csmith_sink_ = g_54;
  csmith_sink_ = g_62.f0;
  csmith_sink_ = g_85;
  for (i = 0; i < 1; i++) {
  }
  csmith_sink_ = g_110.f0;
  csmith_sink_ = g_120;
  csmith_sink_ = g_155;
  platform_main_end(0, 0);
  return 0;
}
