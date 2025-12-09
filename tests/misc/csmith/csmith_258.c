// Options:   --seed 300258 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_258.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  volatile uint16_t f0;
  int32_t f1;
};

static volatile uint64_t g_2[2][2] = {{6UL, 6UL}, {6UL, 6UL}};
static volatile uint16_t g_4 = 65531UL;
static int32_t g_15 = 0L;
static uint16_t g_26[3][2] = {
    {0x62CCL, 0x62CCL}, {65529UL, 0x62CCL}, {0x62CCL, 65529UL}};
static uint8_t g_30 = 1UL;
static union U0 *const g_33 = (void *)0;
static union U0 g_36 = {65531UL};
static union U0 *g_35 = &g_36;
static union U0 **volatile g_34[3][1] = {{&g_35}, {&g_35}, {&g_35}};
static union U0 **volatile g_37 = &g_35;
static uint8_t g_41 = 1UL;
static int32_t *g_45 = &g_15;
static int32_t **volatile g_44 = &g_45;
static const uint32_t g_54 = 0xF54CEAA9L;
static int32_t g_68 = 0xB7F04272L;
static int32_t *volatile g_67 = &g_68;
static uint64_t g_69 = 0xC758019D44E4153CLL;
static const union U0 *g_77 = &g_36;
static const union U0 **g_76 = &g_77;
static const union U0 **g_79 = &g_77;
static int16_t g_88 = 0x1AC8L;
static int64_t g_113 = (-8L);

static int8_t func_1(void);
static int32_t func_5(int32_t p_6, uint32_t p_7, int64_t p_8);
static int8_t func_9(int32_t *p_10, uint16_t p_11, int32_t *p_12, int8_t p_13);

static int8_t func_1(void) {
  volatile int32_t *l_3 = (void *)0;
  int32_t *l_14 = &g_15;
  int32_t *l_17[1][1];
  int32_t *l_19 = (void *)0;
  int32_t **l_18 = &l_19;
  uint8_t l_53[2][2] = {{1UL, 1UL}, {1UL, 1UL}};
  int32_t l_55[3][1];
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++)
      l_17[i][j] = (void *)0;
  }
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++)
      l_55[i][j] = 0x1CAE4674L;
  }
  g_4 = g_2[1][1];
  if (func_5((((((func_9(l_14,
                         (((+g_2[1][1]) <=
                           (((*l_18) = (l_17[0][0] = &g_15)) == (void *)0)),
                          0UL),
                         &g_15, g_15) ||
                  (*l_19)) ||
                 0UL) < l_53[1][1]),
               1L) <= g_54),
             l_55[0][0], g_54)) {
    uint64_t l_70 = 7UL;
    union U0 **l_80 = &g_35;
    uint32_t l_99[2];
    int i;
    for (i = 0; i < 2; i++)
      l_99[i] = 4294967290UL;
    for (g_69 = 0; (g_69 <= 1); g_69 += 1) {
      (*g_45) &= l_70;
    }
    if ((g_41 & (safe_mod_func_uint16_t_u_u(((0xD53B18A5L || g_69) == (-1L)),
                                            g_2[0][1])))) {
      const union U0 ***l_78 = &g_76;
      union U0 ***l_81 = &l_80;
      uint8_t l_82 = 0x20L;
      int32_t *l_87 = &g_36.f1;
      l_82 = ((*g_45) = ((safe_add_func_int16_t_s_s(
                             (~l_70), ((g_79 = ((*l_78) = g_76)) ==
                                       ((*l_81) = l_80)))) <=
                         18446744073709551615UL));
      (**l_18) |=
          ((safe_sub_func_uint32_t_u_u(
               g_69, (safe_add_func_uint32_t_u_u(
                         ((**g_76), (((g_88 = ((*l_87) = (&g_37 == (void *)0))),
                                      0xBE4505C2614AC9ACLL) &
                                     0x793451EA71B313CFLL)),
                         l_82)))) <= g_26[0][0]);
    } else {
      uint8_t l_95 = 0x7AL;
      int8_t *l_96[2][1];
      int32_t l_97 = 0xB7CF170CL;
      int32_t l_98[1];
      int i, j;
      for (i = 0; i < 2; i++) {
        for (j = 0; j < 1; j++)
          l_96[i][j] = (void *)0;
      }
      for (i = 0; i < 1; i++)
        l_98[i] = 0x4CEBEE4CL;
      (*l_18) =
          (((safe_sub_func_int16_t_s_s(g_15, 0xC621L)) &&
            (safe_div_func_uint32_t_u_u(
                (l_98[0] =
                     ((l_97 = ((((safe_mod_func_int64_t_s_s(g_26[0][0], l_95)) <
                                 g_30) != g_2[1][1]),
                               g_36.f0)) &&
                      l_97)),
                0xFEF296F1L))),
           &l_98[0]);
      ++l_99[1];
    }
  } else {
    uint16_t l_106 = 2UL;
    for (g_15 = 0; (g_15 > (-2)); g_15 = safe_sub_func_uint8_t_u_u(g_15, 6)) {
      uint64_t *l_107 = &g_69;
      int64_t *l_112 = &g_113;
      uint16_t *l_117 = (void *)0;
      uint16_t *l_118 = &g_26[1][1];
      int32_t l_119 = 0xBBBCA155L;
      (*g_67) = (safe_sub_func_uint64_t_u_u(
          ((*l_107) = l_106),
          ((*l_112) =
               (0xE968L ==
                ((safe_mul_func_uint8_t_u_u(
                     (safe_div_func_uint32_t_u_u(g_26[0][0], 0xA0DB06F5L)),
                     0xD7L)) != g_88)))));
      l_119 |= (g_15 > (((*l_118) |= (safe_sub_func_int8_t_s_s(
                             (safe_unary_minus_func_int16_t_s(
                                 ((g_4 == (&g_68 == (void *)0)) ^ g_41))),
                             g_113))) != 5UL));
    }
  }
  return g_68;
}

static int32_t func_5(int32_t p_6, uint32_t p_7, int64_t p_8) {
  uint8_t l_62 = 253UL;
  for (g_15 = 1; (g_15 >= 0); g_15 -= 1) {
    int64_t l_65 = 1L;
    int32_t l_66 = 0x42F9032BL;
    (*g_67) = (safe_lshift_func_uint8_t_u_u(
        ((safe_div_func_uint16_t_u_u(
             (((safe_div_func_uint16_t_u_u(
                   (l_62 >= (safe_lshift_func_int8_t_s_u(
                                (l_65 >= ((l_66 = p_6) | g_26[0][0])), p_7))),
                   0x3084L)) <= 0xE5FAF1BECDE87198LL) >= 0xDFL),
             p_8)) ^
         g_2[1][1]),
        2));
    for (l_66 = 1; (l_66 >= 0); l_66 -= 1) {
      int i, j;
      return g_2[g_15][g_15];
    }
  }
  (*g_67) = ((((l_62 <= (g_69 = l_62)) <= (g_15 | 3L)) >= 3UL) & (**g_44));
  return p_6;
}

static int8_t func_9(int32_t *p_10, uint16_t p_11, int32_t *p_12, int8_t p_13) {
  int32_t *l_22 = &g_15;
  uint16_t *l_25 = &g_26[0][0];
  uint8_t *l_29 = &g_30;
  int32_t l_40 = 8L;
  uint8_t **l_52 = &l_29;
  if (((safe_mul_func_int16_t_s_s(
           (((void *)0 != l_22),
            (((*l_29) = ((safe_add_func_uint16_t_u_u((--(*l_25)),
                                                     (0x2EL & (*l_22)))) |
                         g_2[1][0])) == p_11)),
           0xE712L)) &&
       g_15)) {
    uint64_t l_32 = 0x8FAB8D2321210CBELL;
    if (((safe_unary_minus_func_uint8_t_u(p_13)) >
         (l_32 = ((void *)0 != p_12)))) {
      int32_t *l_38 = &g_15;
      int32_t *l_39[1][2];
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 2; j++)
          l_39[i][j] = &g_15;
      }
      (*g_37) = g_33;
      ++g_41;
    } else {
      (*g_44) = p_12;
    }
  } else {
    int32_t *l_46[3];
    uint8_t l_47[3][2];
    int i, j;
    for (i = 0; i < 3; i++)
      l_46[i] = &g_15;
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 2; j++)
        l_47[i][j] = 0UL;
    }
    ++l_47[0][1];
    for (p_11 = 20; (p_11 <= 51); ++p_11) {
      return g_15;
    }
  }
  (*g_45) |= (((*l_52) = l_29) == &g_41);
  return g_2[1][1];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_2[i][j];
    }
  }
  csmith_sink_ = g_4;
  csmith_sink_ = g_15;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_26[i][j];
    }
  }
  csmith_sink_ = g_30;
  csmith_sink_ = g_36.f0;
  csmith_sink_ = g_41;
  csmith_sink_ = g_54;
  csmith_sink_ = g_68;
  csmith_sink_ = g_69;
  csmith_sink_ = g_88;
  csmith_sink_ = g_113;
  platform_main_end(0, 0);
  return 0;
}
