// Options:   --seed 300242 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_242.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  uint64_t f0;
};

union U1 {
  int8_t f0;
  int32_t f1;
};

static volatile uint32_t g_2 = 0xD05BA772L;
static int64_t g_12 = 0x9C2132456160CBEBLL;
static int8_t g_13 = 1L;
static int32_t g_46 = 6L;
static uint32_t g_49 = 1UL;
static int32_t g_52 = 0x7A557527L;
static int64_t g_83 = 0L;
static int16_t g_84[1][1] = {{0L}};
static int32_t g_85 = 0xC9DB4546L;
static uint64_t g_87 = 18446744073709551612UL;
static struct S0 g_90[2][3] = {{{18446744073709551606UL},
                                {18446744073709551606UL},
                                {18446744073709551606UL}},
                               {{9UL}, {9UL}, {9UL}}};
static volatile int32_t g_107 = 1L;
static volatile uint16_t g_108[1] = {1UL};
static volatile union U1 g_152 = {0x40L};
static uint16_t g_155 = 0xC406L;

static uint64_t func_1(void);
static uint64_t func_5(int32_t p_6, int8_t p_7);
static uint8_t func_8(int64_t p_9, const uint8_t p_10);

static uint64_t func_1(void) {
  uint32_t l_11[3];
  int8_t *l_92 = (void *)0;
  int32_t l_93 = (-1L);
  int32_t l_127[3];
  int8_t l_137[3];
  uint64_t l_138[1];
  uint64_t l_147 = 0x5127A50812B24AB7LL;
  int i;
  for (i = 0; i < 3; i++)
    l_11[i] = 0UL;
  for (i = 0; i < 3; i++)
    l_127[i] = 0x7FF15597L;
  for (i = 0; i < 3; i++)
    l_137[i] = 0xF4L;
  for (i = 0; i < 1; i++)
    l_138[i] = 0xC2843333429DD6F4LL;
  if ((g_2 < ((safe_mul_func_int8_t_s_s(
                  (l_93 = (func_5((func_8(l_11[2], l_11[2]) >= 0xE9L), g_12) &
                           18446744073709551606UL)),
                  l_11[2])) ||
              l_93))) {
    for (g_85 = 26; (g_85 != (-16)); --g_85) {
      int32_t *l_96 = (void *)0;
      int32_t *l_97 = (void *)0;
      int32_t *l_98 = &g_52;
      int32_t *l_99 = (void *)0;
      int32_t *l_100 = (void *)0;
      int32_t *l_101 = &l_93;
      int32_t *l_102 = &l_93;
      int32_t *l_103 = &g_52;
      int32_t *l_104 = &g_52;
      int32_t *l_105 = &g_52;
      int32_t *l_106[1];
      int i;
      for (i = 0; i < 1; i++)
        l_106[i] = &g_52;
      g_108[0]--;
    }
    for (g_12 = 0; (g_12 == 8); g_12 = safe_add_func_uint64_t_u_u(g_12, 6)) {
      g_90[1][0] = g_90[1][0];
    }
  } else {
    uint8_t l_114 = 0xF5L;
    int16_t l_128 = (-6L);
    uint32_t l_131 = 1UL;
    int32_t l_133 = (-3L);
    if ((!l_114)) {
      int8_t l_120 = (-1L);
      int16_t *l_129 = (void *)0;
      int16_t *l_130 = (void *)0;
      int16_t *l_132[2][3] = {{&g_84[0][0], &g_84[0][0], &g_84[0][0]},
                              {&g_84[0][0], &g_84[0][0], &g_84[0][0]}};
      int32_t *l_134 = &g_52;
      int i, j;
      (*l_134) &= (~(safe_mod_func_uint16_t_u_u(
          (g_85 |
           (g_84[0][0] =
                (l_131 =
                     (((safe_add_func_int8_t_s_s(
                           ((l_120 ||
                             (safe_add_func_uint64_t_u_u(
                                 (((safe_mul_func_uint16_t_u_u(
                                       (safe_div_func_int32_t_s_s((-6L), 5UL)),
                                       l_120)),
                                   l_11[2]) ||
                                  l_127[2]),
                                 l_128))) &
                            g_85),
                           l_93)),
                       g_13) ^
                      0UL)))),
          l_133)));
    } else {
      int32_t *l_135 = &g_52;
      int32_t *l_136[3][2] = {
          {&g_46, (void *)0}, {&g_46, &g_46}, {(void *)0, &g_46}};
      const int16_t *l_153 = (void *)0;
      uint8_t *l_154 = &l_114;
      int i, j;
      ++l_138[0];
      (*l_135) = (safe_sub_func_int16_t_s_s(
          (((safe_mod_func_uint64_t_u_u(
                g_52,
                ((safe_rshift_func_int16_t_s_s(
                     (l_147 <= ((*l_154) = (safe_add_func_uint8_t_u_u(
                                    ((safe_rshift_func_uint8_t_u_u(
                                         ((g_152, l_153) != (void *)0), 3)) ||
                                     g_152.f0),
                                    l_131)))),
                     g_83)) ^
                 0x2CAAL))),
            g_152.f0) ||
           g_84[0][0]),
          0x8848L));
    }
  }
  return g_155;
}

static uint64_t func_5(int32_t p_6, int8_t p_7) {
  uint32_t l_70[1][2];
  int32_t l_82[2];
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 2; j++)
      l_70[i][j] = 0xDF47B588L;
  }
  for (i = 0; i < 2; i++)
    l_82[i] = 0x64560F91L;
  for (g_13 = 0; (g_13 < (-10)); g_13 = safe_sub_func_int16_t_s_s(g_13, 6)) {
    uint32_t *l_63 = &g_49;
    int32_t l_66 = 0L;
    int64_t l_67 = (-1L);
    int64_t l_86 = (-9L);
    if ((safe_div_func_int8_t_s_s((l_63 == &g_49),
                                  (safe_rshift_func_int8_t_s_u(l_66, l_67))))) {
      int32_t *l_71 = &g_52;
      (*l_71) |=
          (((p_7,
             (((l_67, ((safe_lshift_func_int8_t_s_u(0x95L, g_46)), 65527UL)) |
               (-1L)) != 0x2BC12A55L)) < l_70[0][0]) &
           0x7AB8L);
    } else {
      int32_t *l_72 = &l_66;
      int32_t *l_73 = &l_66;
      int32_t *l_74 = &g_52;
      int32_t *l_75 = &g_46;
      int32_t *l_76 = &g_52;
      int32_t *l_77 = &l_66;
      int32_t *l_78 = &g_46;
      int32_t *l_79 = &g_52;
      int32_t l_80 = 0xCE07B88CL;
      int32_t *l_81[3];
      struct S0 *l_91 = &g_90[0][2];
      int i;
      for (i = 0; i < 3; i++)
        l_81[i] = (void *)0;
      ++g_87;
      (*l_91) = g_90[1][0];
    }
    if (g_90[1][0].f0)
      break;
  }
  return p_7;
}

static uint8_t func_8(int64_t p_9, const uint8_t p_10) {
  uint32_t l_16 = 0xD303F024L;
  uint8_t l_27 = 1UL;
  int8_t l_50 = 1L;
lbl_58:
  g_13 &= (g_12 < p_10);
  if ((safe_div_func_uint64_t_u_u(
          l_16,
          (safe_sub_func_uint8_t_u_u(
              0UL,
              ((safe_mod_func_uint16_t_u_u(
                   (!(safe_add_func_uint16_t_u_u(
                       (!(safe_unary_minus_func_uint32_t_u((+g_12)))), p_9))),
                   l_27)) |
               0xC593L)))))) {
    uint32_t *l_47 = (void *)0;
    uint32_t *l_48 = &g_49;
    int32_t *l_51 = &g_52;
    (*l_51) =
        (((*l_48) = (~(!(safe_mod_func_int32_t_s_s(
              (g_46 =
                   ((safe_lshift_func_int8_t_s_u(
                        ((safe_div_func_int32_t_s_s(
                             (safe_lshift_func_uint16_t_u_u(
                                 (safe_sub_func_uint32_t_u_u(
                                     ((safe_mul_func_uint16_t_u_u(
                                          g_13,
                                          (safe_mod_func_uint8_t_u_u(
                                              0xBBL, (safe_mod_func_int64_t_s_s(
                                                         p_10, g_13)))))) &
                                      g_13),
                                     0xBA9A9843L)),
                                 5)),
                             l_27)) ^
                         (-10L)),
                        l_27)) ||
                    g_13)),
              l_27))))) > l_50);
  } else {
    uint32_t l_55[2][2] = {{0x2FA43DEEL, 0x2FA43DEEL},
                           {0x2FA43DEEL, 0x2FA43DEEL}};
    int i, j;
    for (p_9 = (-19); (p_9 >= (-12)); p_9 = safe_add_func_int64_t_s_s(p_9, 7)) {
      int32_t *l_56 = &g_46;
      int32_t **l_57 = &l_56;
      (*l_57) = ((0x65D3E8EAL | (g_12 < l_55[0][1])), l_56);
      if (l_27)
        goto lbl_58;
    }
  }
  return g_13;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_12;
  csmith_sink_ = g_13;
  csmith_sink_ = g_46;
  csmith_sink_ = g_49;
  csmith_sink_ = g_52;
  csmith_sink_ = g_83;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_84[i][j];
    }
  }
  csmith_sink_ = g_85;
  csmith_sink_ = g_87;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 3; j++) {
    }
  }
  csmith_sink_ = g_107;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_108[i];
  }
  csmith_sink_ = g_152.f0;
  csmith_sink_ = g_155;
  platform_main_end(0, 0);
  return 0;
}
