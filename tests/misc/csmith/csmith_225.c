// Options:   --seed 300225 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_225.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  int16_t f0;
  volatile int32_t f1;
};

struct S1 {
  int8_t f0;
  int8_t f1;
};

struct S2 {
  const struct S1 f0;
  uint8_t f1;
};

static int16_t g_9 = 0x6137L;
static int8_t g_39[2] = {0x50L, 0x50L};
static uint32_t g_41 = 0x40452383L;
static int32_t g_45 = (-10L);
static int32_t *volatile g_44 = &g_45;
static uint64_t g_49 = 0xD0C5FD78DB5841ECLL;
static int64_t g_65 = 0L;
static uint32_t g_67 = 0xA83C5EE7L;
static uint64_t g_71[3][3] = {
    {18446744073709551615UL, 18446744073709551615UL, 18446744073709551615UL},
    {0UL, 0xBDC27B9F09720137LL, 0UL},
    {18446744073709551615UL, 18446744073709551615UL, 18446744073709551615UL}};
static int32_t *volatile g_95 = &g_45;
static struct S0 g_98 = {0L, 0x6B660488L};
static int8_t *g_104 = &g_39[1];
static int8_t *volatile *volatile g_103 = &g_104;
static int8_t *volatile *const volatile *g_102 = &g_103;
static int32_t *g_117 = &g_45;
static int32_t **volatile g_116[3] = {&g_117, &g_117, &g_117};
static int32_t **volatile g_118[1][1] = {{&g_117}};

static int32_t func_1(void);
static int8_t func_4(struct S2 p_5, int16_t p_6, int8_t p_7);
static int16_t func_12(int8_t p_13, int32_t p_14, int64_t p_15);

static int32_t func_1(void) {
  struct S2 l_8 = {{0xE4L, 0x28L}, 0x06L};
  int16_t l_43 = 0x2B72L;
  int32_t l_69[1];
  int64_t *l_78 = (void *)0;
  int64_t l_90 = 1L;
  int32_t l_92[1][2];
  int32_t l_101 = 0xBCECFDE0L;
  int i, j;
  for (i = 0; i < 1; i++)
    l_69[i] = 0L;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 2; j++)
      l_92[i][j] = 0x9E5886D3L;
  }
  if ((safe_rshift_func_int8_t_s_u(func_4(l_8, l_8.f1, g_9), 3))) {
    struct S2 l_19 = {{9L, 0xB6L}, 1UL};
    int64_t *l_20 = (void *)0;
    int32_t l_21 = 0xCAA8E55AL;
    int32_t l_28 = 0xBC23CEA2L;
    int32_t l_42 = 0x75A8055AL;
    if ((~(l_28 =
               func_12((safe_add_func_uint16_t_u_u(
                           (l_8.f0.f0, (+(l_19, ((l_21 = 2L) <= l_8.f0.f1)))),
                           0x8B4DL)),
                       g_9, g_9)))) {
      int8_t *l_38[2][1];
      uint32_t *l_40 = &g_41;
      uint64_t *l_48 = &g_49;
      struct S1 l_56 = {0xD5L, 0x26L};
      int8_t l_62 = 0xF0L;
      uint8_t *l_63 = &l_8.f1;
      uint8_t *l_64[2][2];
      uint32_t *l_66 = &g_67;
      int32_t *l_68[3][2];
      int i, j;
      for (i = 0; i < 2; i++) {
        for (j = 0; j < 1; j++)
          l_38[i][j] = &g_39[0];
      }
      for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++)
          l_64[i][j] = &l_19.f1;
      }
      for (i = 0; i < 3; i++) {
        for (j = 0; j < 2; j++)
          l_68[i][j] = (void *)0;
      }
      (*g_44) |=
          ((safe_sub_func_int32_t_s_s(
               (((safe_mul_func_int16_t_s_s(
                     (g_9 >=
                      (l_42 =
                           (((safe_add_func_int8_t_s_s(
                                 (((safe_lshift_func_int8_t_s_s(
                                       (safe_unary_minus_func_int64_t_s((-5L))),
                                       ((l_21 ^=
                                         (((((*l_40) =
                                                 ((g_39[0] &=
                                                   ((((l_8.f0, g_9) != 0x6BL) >
                                                     0x6511L) < 0xABL)) &
                                                  0xE2L)) ||
                                            g_41) >= 0x3AL) < 0UL)),
                                        0x54L))) &&
                                   0x9719EFCC72FDDD0CLL) != g_9),
                                 g_9)) >= 255UL),
                            3L))),
                     g_9)) &&
                 1L) |
                g_9),
               g_9)) != l_43);
      l_69[0] =
          ((safe_lshift_func_int8_t_s_s(
               ((--(*l_48)),
                (((*l_66) ^=
                  ((0x91L ||
                    (g_65 = ((l_42 = ((*l_48)--)) >=
                             (((safe_lshift_func_uint8_t_u_s(
                                   (l_56,
                                    (((~((*l_63) =
                                             (((safe_add_func_uint32_t_u_u(
                                                   ((*l_40) =
                                                        ((0xF081L > l_62) !=
                                                         0x13FE74C19FD8DD93LL)),
                                                   g_39[1])),
                                               g_39[1]) > l_62))),
                                      0xF7D1D410A02D5285LL) >= 0UL)),
                                   l_56.f1)) ^
                               l_28) &
                              g_9)))) <= g_45)) <= 0x3943E124L)),
               l_19.f1)) <= l_28);
    } else {
      int32_t *l_70[2];
      int i;
      for (i = 0; i < 2; i++)
        l_70[i] = (void *)0;
      g_71[1][1]--;
    }
  } else {
    int64_t *l_76 = &g_65;
    int64_t **l_77 = &l_76;
    int32_t l_79[3];
    uint64_t *l_99 = &g_71[1][1];
    int i;
    for (i = 0; i < 3; i++)
      l_79[i] = 1L;
    if (((safe_rshift_func_uint8_t_u_u(((((((((*l_77) = l_76) != &g_65),
                                            ((void *)0 != l_78)) != l_79[0]) |
                                          4294967294UL) > l_79[0]),
                                        l_8.f1),
                                       l_8.f1)),
         l_8.f0.f0)) {
      int32_t *l_91 = &l_79[0];
      const int8_t *l_94 = &l_8.f0.f0;
      const int8_t **l_93 = &l_94;
      uint64_t *l_100 = &g_49;
      (*g_95) ^=
          ((((*l_93) =
                 ((safe_mod_func_uint8_t_u_u(
                      (safe_lshift_func_int16_t_s_s(
                          (safe_lshift_func_int8_t_s_u(
                              ((void *)0 == &g_67),
                              (safe_lshift_func_int16_t_s_s(
                                  (((safe_add_func_uint8_t_u_u(
                                        (((l_79[0] > l_90), l_91) == (void *)0),
                                        l_90)) &
                                    0xDEE7960BL) > (*l_91)),
                                  g_9)))),
                          l_92[0][1])),
                      g_9)),
                  (void *)0)) != &g_39[1]) != g_49);
      (*l_91) &= ((safe_mod_func_uint16_t_u_u(
                      ((g_98, ((l_99 = &g_49) != l_100)) && l_101), 6UL)) ^
                  0x38L);
    } else {
      return l_79[2];
    }
    g_102 = g_102;
  }
  for (l_43 = 0; (l_43 <= (-7)); l_43 = safe_sub_func_uint8_t_u_u(l_43, 5)) {
    for (g_41 = 15; (g_41 > 49); g_41++) {
      const uint32_t l_111[2][2] = {{0xE225A2E6L, 0xE225A2E6L},
                                    {0xE225A2E6L, 0xE225A2E6L}};
      int32_t **l_119[2][1];
      int32_t *l_120[3];
      uint64_t l_121 = 0x78518540A1317D21LL;
      int i, j;
      for (i = 0; i < 2; i++) {
        for (j = 0; j < 1; j++)
          l_119[i][j] = &g_117;
      }
      for (i = 0; i < 3; i++)
        l_120[i] = &l_69[0];
      l_120[2] =
          (((safe_mod_func_int64_t_s_s(
                l_111[1][1],
                ((l_111[1][1] < (safe_add_func_uint64_t_u_u(
                                    (safe_div_func_int64_t_s_s(
                                        (g_49, 0x57597B358AE84C8BLL), 6L)),
                                    1UL))) ^
                 g_65))) ||
            l_111[0][0]),
           &g_45);
      --l_121;
    }
    if ((*g_95))
      break;
  }
  return g_41;
}

static int8_t func_4(struct S2 p_5, int16_t p_6, int8_t p_7) {
  int8_t l_10 = 1L;
  return l_10;
}

static int16_t func_12(int8_t p_13, int32_t p_14, int64_t p_15) {
  uint32_t l_26 = 0xBB000E2EL;
  int32_t l_27[3][3];
  int i, j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++)
      l_27[i][j] = 0L;
  }
  l_27[2][0] |=
      ((0x4082L ^
        (safe_div_func_int8_t_s_s((safe_div_func_uint64_t_u_u(l_26, g_9)),
                                  0xE4L))) < 0x0FA1A8F1EDD1EDB6LL);
  return g_9;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_9;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_39[i];
  }
  csmith_sink_ = g_41;
  csmith_sink_ = g_45;
  csmith_sink_ = g_49;
  csmith_sink_ = g_65;
  csmith_sink_ = g_67;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_71[i][j];
    }
  }
  csmith_sink_ = g_98.f0;
  csmith_sink_ = g_98.f1;
  platform_main_end(0, 0);
  return 0;
}
