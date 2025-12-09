// Options:   --seed 100097 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_097.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  const uint8_t f0;
};

struct S1 {
  uint16_t f0;
  uint32_t f1;
};

struct S2 {
  struct S0 f0;
};

static volatile int32_t g_3 = (-1L);
static int32_t g_4[1] = {0L};
static struct S1 g_13[1][2] = {{{2UL, 0UL}, {2UL, 0UL}}};
static int32_t g_41 = 4L;
static uint8_t g_57 = 0xBCL;
static uint16_t g_59 = 65535UL;
static uint64_t g_64 = 0x720FAE2361AE7D51LL;
static int32_t g_72[2][1] = {{(-5L)}, {(-5L)}};
static volatile struct S2 g_74 = {{0xF1L}};
static volatile struct S2 *g_73 = &g_74;
static int16_t g_84 = 0x4F54L;

static int16_t func_1(void);
static uint8_t func_7(struct S1 p_8, int32_t p_9, uint64_t p_10, uint32_t p_11);

static int16_t func_1(void) {
  int32_t l_2[4][2];
  struct S0 l_12 = {0x2DL};
  const int32_t l_69 = (-1L);
  int16_t *l_82 = (void *)0;
  int16_t *l_83 = &g_84;
  uint64_t *l_85[3];
  int i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 2; j++)
      l_2[i][j] = 0xF4288A13L;
  }
  for (i = 0; i < 3; i++)
    l_85[i] = &g_64;
  for (g_4[0] = 0; (g_4[0] <= 1); g_4[0] += 1) {
    int16_t l_14[1];
    int32_t *l_70 = (void *)0;
    int32_t *l_71 = &g_72[1][0];
    volatile struct S2 **l_75 = &g_73;
    int i;
    for (i = 0; i < 1; i++)
      l_14[i] = 1L;
    (*l_71) ^= (((safe_lshift_func_uint16_t_u_s(
                     g_4[0], (l_2[3][0] = ((func_7((l_12, g_13[0][1]), g_4[0],
                                                   l_14[0], g_4[0]) >= g_59) ^
                                           18446744073709551608UL)))) ^
                 l_14[0]) == l_69);
    (*l_75) = g_73;
    for (g_41 = 1; (g_41 >= 0); g_41 -= 1) {
      struct S1 l_78 = {0x5C01L, 0x8B95DE17L};
      struct S1 *l_79 = &l_78;
      int i, j;
      (*l_79) =
          ((safe_mul_func_uint8_t_u_u(
               (4294967295UL &
                (l_2[(g_41 + 1)][g_41] ||
                 ((((&g_64 == &g_64) & g_72[0][0]), g_72[0][0]) && l_69))),
               g_13[0][1].f0)),
           l_78);
    }
  }
  if (((safe_lshift_func_int16_t_s_u(
           l_12.f0,
           (((*l_83) = l_12.f0) > (((((l_85[2] != l_85[0]) || 1UL) == g_4[0]),
                                    &g_13[0][1]) != (void *)0)))) <= 0xFFL)) {
    for (g_57 = (-3); (g_57 <= 33); g_57++) {
      if (g_13[0][1].f0)
        break;
    }
  } else {
    int32_t *l_89 = &g_4[0];
    g_72[1][0] = ((*l_89) ^= (safe_unary_minus_func_int8_t_s(0x44L)));
  }
  return l_2[2][0];
}

static uint8_t func_7(struct S1 p_8, int32_t p_9, uint64_t p_10,
                      uint32_t p_11) {
  uint16_t l_42 = 65535UL;
  int32_t l_43 = 0xA75E3AA9L;
  struct S2 l_48[1][3] = {{{{2UL}}, {{2UL}}, {{2UL}}}};
  int i, j;
  for (p_10 = (-5); (p_10 < 23); p_10 = safe_add_func_int32_t_s_s(p_10, 1)) {
    int32_t *l_40[1];
    int i;
    for (i = 0; i < 1; i++)
      l_40[i] = &g_41;
    g_41 &= (safe_div_func_uint64_t_u_u(
        (safe_mod_func_uint16_t_u_u(
            (safe_lshift_func_int8_t_s_u(
                ((safe_mod_func_uint64_t_u_u(
                     (safe_add_func_uint16_t_u_u(
                         (safe_add_func_int16_t_s_s(
                             ((+((safe_add_func_int64_t_s_s(
                                     ((l_42 = (safe_sub_func_int32_t_s_s(
                                           g_4[0],
                                           (safe_rshift_func_uint16_t_u_s(
                                               ((safe_sub_func_uint8_t_u_u(
                                                    (safe_sub_func_uint32_t_u_u(
                                                        g_13[0][1].f0, p_10)),
                                                    252UL)) &
                                                p_8.f1),
                                               p_11))))) ||
                                      0L),
                                     g_4[0])) &
                                 p_8.f1)) <= p_10),
                             l_43)),
                         p_11)),
                     p_8.f0)) != g_13[0][1].f0),
                g_3)),
            p_11)),
        0x964069A3E2BE8CA4LL));
    for (p_9 = 25; (p_9 == 1); p_9 = safe_sub_func_uint16_t_u_u(p_9, 7)) {
      uint16_t *l_56 = &l_42;
      uint16_t *l_58[3][1];
      int i, j;
      for (i = 0; i < 3; i++) {
        for (j = 0; j < 1; j++)
          l_58[i][j] = &g_59;
      }
      if ((safe_div_func_uint16_t_u_u(
              g_13[0][1].f0,
              (l_48[0][1],
               (l_43 = (safe_rshift_func_uint16_t_u_u(
                    (g_57 = (safe_rshift_func_int8_t_s_u(
                         (((((*l_56) ^= (safe_lshift_func_int8_t_s_u(
                                 (safe_unary_minus_func_uint16_t_u(
                                     ((p_8, 18446744073709551613UL) ^ p_9))),
                                 l_48[0][1].f0.f0))) > p_8.f0) >= p_8.f1) >=
                          p_8.f0),
                         p_8.f1))),
                    15))))))) {
        return p_8.f1;
      } else {
        uint32_t l_62 = 18446744073709551613UL;
        uint64_t *l_63 = &g_64;
        struct S2 l_68[4] = {{{255UL}}, {{255UL}}, {{255UL}}, {{255UL}}};
        int i;
        l_43 |= ((safe_mod_func_uint64_t_u_u(0x9ACCE3044B1310F0LL,
                                             ((*l_63) = l_62))) !=
                 (((safe_mod_func_int8_t_s_s(
                       ((((~(l_68[3], 0UL)), &p_9) == &g_3) > p_8.f0),
                       255UL)) == 0x5225L) ||
                  g_59));
      }
    }
  }
  return p_10;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_4[i];
  }
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 2; j++) {
    }
  }
  csmith_sink_ = g_41;
  csmith_sink_ = g_57;
  csmith_sink_ = g_59;
  csmith_sink_ = g_64;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_72[i][j];
    }
  }
  csmith_sink_ = g_74.f0.f0;
  csmith_sink_ = g_84;
  platform_main_end(0, 0);
  return 0;
}
