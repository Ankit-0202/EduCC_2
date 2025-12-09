// Options:   --seed 100035 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_035.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  int32_t f0;
};

static int32_t g_2[4][3] = {{0x7E8EDF1FL, 0x7E8EDF1FL, 0x7E8EDF1FL},
                            {0x7E8EDF1FL, 0x7E8EDF1FL, 0x7E8EDF1FL},
                            {0x7E8EDF1FL, 0x7E8EDF1FL, 0x7E8EDF1FL},
                            {0x7E8EDF1FL, 0x7E8EDF1FL, 0x7E8EDF1FL}};
static int32_t g_5 = 0x1E2C0D37L;
static int8_t g_9 = 0x81L;
static int32_t g_11 = 0xA4D63A88L;
static int32_t *volatile g_10 = &g_11;
static uint8_t g_27 = 0x7FL;
static int32_t **volatile g_54 = (void *)0;
static int32_t g_57[4] = {0x2DBE4212L, 0x2DBE4212L, 0x2DBE4212L, 0x2DBE4212L};
static volatile union U0 g_86 = {0x70FB2EC1L};
static volatile union U0 *const g_85[2][3] = {{&g_86, &g_86, &g_86},
                                              {&g_86, &g_86, &g_86}};
static int16_t g_88 = 0L;
static int32_t *volatile g_95 = &g_57[2];
static int32_t *volatile g_96 = &g_11;
static int32_t **volatile g_99 = (void *)0;
static int32_t *g_110 = (void *)0;
static int32_t **volatile g_109 = &g_110;
static int8_t g_117 = 0xF2L;
static uint16_t g_121 = 65529UL;
static const uint32_t g_146 = 4294967295UL;
static int32_t *g_153 = &g_2[0][0];
static int32_t **volatile g_152 = &g_153;

static uint64_t func_1(void);
static int8_t func_17(int64_t p_18, int8_t *p_19, uint32_t p_20, int64_t p_21);

static uint64_t func_1(void) {
  uint8_t l_22 = 1UL;
  for (g_2[2][2] = 0; (g_2[2][2] >= 14); ++g_2[2][2]) {
    uint8_t l_16[1][1];
    const int32_t l_149 = 0x93478865L;
    int i, j;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 1; j++)
        l_16[i][j] = 251UL;
    }
    for (g_5 = 0; (g_5 > 15); g_5 = safe_add_func_int32_t_s_s(g_5, 5)) {
      int8_t *l_8 = &g_9;
      (*g_10) = (((*l_8) = g_2[1][1]) || g_2[2][2]);
      if ((*g_10))
        break;
    }
    for (g_5 = 0; (g_5 > 2); g_5++) {
      uint32_t l_32 = 0xE819D338L;
      int8_t *l_33 = &g_9;
      if (((safe_lshift_func_int8_t_s_u(
               l_16[0][0],
               ((func_17(
                     ((l_22, (safe_div_func_uint8_t_u_u(
                                 (safe_div_func_int32_t_s_s(
                                     ((g_27--), (((safe_div_func_uint64_t_u_u(
                                                      l_32, l_22)) > 8L) &
                                                 g_9)),
                                     g_2[2][2])),
                                 0xA7L))) |
                      l_22),
                     l_33, l_32, l_22) < g_2[0][1]) |
                1L))),
           l_149)) {
        int32_t *l_150 = &g_2[3][1];
        int32_t **l_151 = &g_110;
        (*g_152) = ((*l_151) = l_150);
      } else {
        int16_t *l_162 = (void *)0;
        int16_t **l_163 = &l_162;
        int32_t l_164 = (-6L);
        int32_t *l_165 = &l_164;
        (*l_165) = (safe_lshift_func_int16_t_s_u(
            (safe_mul_func_int8_t_s_s(
                ((safe_lshift_func_int16_t_s_u(
                     ((safe_add_func_uint8_t_u_u(
                          0UL, (((*l_33) = (g_86.f0 >= (((*l_163) = l_162) ==
                                                        (void *)0))) >=
                                g_88))) != g_57[3]),
                     l_164)) != g_2[2][0]),
                l_16[0][0])),
            7));
      }
    }
  }
  return g_117;
}

static int8_t func_17(int64_t p_18, int8_t *p_19, uint32_t p_20, int64_t p_21) {
  uint64_t l_42 = 0x6D4C01E07AD46D23LL;
  union U0 l_66 = {0xA04A8F9BL};
  uint8_t l_78 = 246UL;
  uint32_t l_90 = 0UL;
  uint8_t l_103 = 0xA0L;
  int32_t *l_108 = (void *)0;
lbl_113:
  if ((((((((((((((safe_mod_func_uint8_t_u_u(
                      (safe_add_func_uint32_t_u_u(
                          ((safe_sub_func_uint16_t_u_u(
                               (p_18 ^
                                (((safe_sub_func_int8_t_s_s(
                                      0x93L, ((((*g_10), p_19) == &g_9) >=
                                              (*p_19)))) > l_42),
                                 0x5E60D1F283019C36LL)),
                               0xD66BL)) &
                           (-1L)),
                          g_5)),
                      g_9)) ^
                  g_2[2][2]) |
                 l_42) ^
                g_9) == 0x4AL) < p_21),
             l_42),
            g_2[0][2]),
           0x3DL),
          l_42) != 0x93L) != 0xE745C5BBL) |
       p_20)) {
    int32_t *const l_53 = &g_5;
    if ((safe_rshift_func_uint16_t_u_s(0x8927L, 10))) {
      uint64_t l_47[1][2];
      uint64_t *l_50 = &l_42;
      int32_t *l_51 = &g_11;
      uint32_t l_52 = 0xB8731485L;
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 2; j++)
          l_47[i][j] = 0UL;
      }
      l_52 =
          ((*l_51) = (safe_mul_func_uint16_t_u_u(
               l_47[0][1],
               (safe_add_func_int64_t_s_s(
                   (((*l_50) = 0xFFFBC9EE52129E5ELL) >
                    ((((6L < 4294967295UL) < (*g_10)) | 0x4FF2D4E203D7E6DELL),
                     0x69C043CA38079068LL)),
                   g_9)))));
    } else {
      int32_t *l_56 = &g_11;
      int32_t **l_55 = &l_56;
      (*l_55) = l_53;
    }
  } else {
    uint32_t l_70[4] = {3UL, 3UL, 3UL, 3UL};
    int32_t l_77[1][1];
    int32_t *l_102[2];
    int i, j;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 1; j++)
        l_77[i][j] = 0x6903F87FL;
    }
    for (i = 0; i < 2; i++)
      l_102[i] = &g_57[2];
    for (g_11 = 0; (g_11 <= 3); g_11 += 1) {
      union U0 *l_67 = &l_66;
      int32_t l_71 = 0L;
      int32_t *l_72 = &g_57[g_11];
      int32_t *l_73 = &g_57[g_11];
      int32_t *l_74 = &g_57[0];
      int32_t *l_75 = &g_57[g_11];
      int32_t *l_76[2][3] = {{(void *)0, (void *)0, (void *)0},
                             {(void *)0, (void *)0, (void *)0}};
      int i, j;
      l_71 &= (safe_add_func_int16_t_s_s(
          (safe_lshift_func_int8_t_s_u(
              g_57[g_11],
              ((safe_mul_func_int8_t_s_s(
                   (safe_add_func_int64_t_s_s(
                       (((((*l_67) = l_66),
                          (safe_mul_func_uint8_t_u_u(l_70[0], 0xD1L))) !=
                         4294967294UL) == p_21),
                       1L)),
                   0x80L)) ||
               0x0EL))),
          g_11));
      l_78--;
    }
    if ((g_9 != (g_5 != (6L != g_2[2][2])))) {
      uint32_t l_83 = 0x52FFB46DL;
      int16_t *l_87[1][3];
      int32_t l_89[3];
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 3; j++)
          l_87[i][j] = &g_88;
      }
      for (i = 0; i < 3; i++)
        l_89[i] = (-1L);
      if (((safe_div_func_int16_t_s_s(
               l_83,
               ((~(((l_89[0] = (g_85[0][0] == (void *)0)) >= p_21) || 6UL)) &&
                l_42))),
           l_90)) {
        (*g_95) = ((safe_mod_func_int16_t_s_s(
                       ((safe_div_func_uint32_t_u_u(0x648FB317L, (-3L))) &&
                        g_2[3][0]),
                       g_2[0][1])) |
                   0UL);
      } else {
        (*g_96) = l_70[2];
      }
      for (g_11 = (-10); (g_11 != 14); g_11++) {
        int32_t *l_101[2];
        int32_t **l_100[3];
        int i;
        for (i = 0; i < 2; i++)
          l_101[i] = &g_2[1][1];
        for (i = 0; i < 3; i++)
          l_100[i] = &l_101[1];
        l_102[0] = &l_89[0];
      }
    } else {
      ++l_103;
    }
  }
  for (g_9 = 0; (g_9 > 9); g_9 = safe_add_func_int16_t_s_s(g_9, 4)) {
    int8_t l_129 = 0xDCL;
    union U0 l_137 = {-1L};
    (*g_109) = l_108;
    for (p_20 = 26; (p_20 >= 20); --p_20) {
      int8_t *l_116 = &g_117;
      int32_t l_134 = (-9L);
      if (p_18)
        goto lbl_113;
      if ((((*l_116) = ((void *)0 != l_108)) ||
           ((safe_add_func_uint16_t_u_u(0x3DFDL, 1L)) < g_27))) {
        uint16_t *l_120 = &g_121;
        int32_t l_128 = (-1L);
        uint32_t *l_130 = &l_90;
        int32_t l_133 = 0x0E8DF19FL;
        uint64_t *l_138 = &l_42;
        l_134 ^= (((*l_120)--) ^
                  ((safe_rshift_func_int16_t_s_u(
                       (((safe_add_func_uint32_t_u_u(l_128, g_27)) &
                         (((((*l_130)--), (l_133, 0x53DCL)) > g_27), p_20)),
                        g_5),
                       g_117)) != g_117));
        (*g_95) = (((*l_138) |= (safe_mod_func_uint32_t_u_u(
                        (0xCAC18070L <= (0xA873L <= (l_137, l_134))), p_21))),
                   0x76A3B401L);
      } else {
        uint8_t *l_141 = &l_103;
        int32_t l_145 = 0xFBA12C33L;
        int32_t l_147 = 0L;
        int32_t ***l_148[1][3];
        int i, j;
        for (i = 0; i < 1; i++) {
          for (j = 0; j < 3; j++)
            l_148[i][j] = (void *)0;
        }
        l_147 ^=
            (((safe_rshift_func_uint8_t_u_u((++(*l_141)), 1)) <
              (((((+((g_96 != &p_20) &
                     (((((g_27, 1L), l_145) != l_134) | p_21), 0UL))) == g_146),
                 p_21) &&
                g_11) != l_134)) >= 0x97L);
        g_99 = (void *)0;
      }
    }
  }
  return g_117;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_2[i][j];
    }
  }
  csmith_sink_ = g_5;
  csmith_sink_ = g_9;
  csmith_sink_ = g_11;
  csmith_sink_ = g_27;
  for (i = 0; i < 4; i++) {
    csmith_sink_ = g_57[i];
  }
  csmith_sink_ = g_86.f0;
  csmith_sink_ = g_88;
  csmith_sink_ = g_117;
  csmith_sink_ = g_121;
  csmith_sink_ = g_146;
  platform_main_end(0, 0);
  return 0;
}
