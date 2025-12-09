// Options:   --seed 100088 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_088.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  int16_t f0;
};

static uint16_t g_5 = 0x0ADEL;
static int32_t g_13 = 0x649F6D4AL;
static int32_t *volatile g_12 = &g_13;
static int32_t *volatile *volatile g_14 = &g_12;
static struct S0 g_24 = {0xDFE9L};
static int32_t *volatile g_25 = &g_13;
static int32_t *volatile g_31 = &g_13;
static int32_t *volatile *volatile g_32 = &g_12;
static int32_t g_42 = 9L;
static int8_t g_58 = 0x1FL;
static uint64_t g_64 = 0x7338D581CA9286DFLL;
static uint64_t *g_63[2][4] = {{(void *)0, &g_64, (void *)0, (void *)0},
                               {&g_64, &g_64, &g_64, &g_64}};
static uint64_t **g_62 = &g_63[1][2];
static uint64_t ***volatile g_61 = &g_62;
static const int8_t g_87 = 0x76L;
static const int8_t *g_86[4] = {&g_87, &g_87, &g_87, &g_87};
static int64_t g_91 = 0x58EF108C6EC2A3D9LL;
static uint32_t g_93 = 0xF019E2F9L;

static const int16_t func_1(void);
static struct S0 func_2(int32_t p_3, int8_t p_4);

static const int16_t func_1(void) {
  int16_t l_11 = 6L;
  int32_t *l_56 = &g_42;
  if (((func_2(g_5, (safe_div_func_int16_t_s_s(
                        0x2E08L,
                        (+(safe_sub_func_int32_t_s_s(0x67F5ED9AL, l_11)))))),
        l_11),
       l_11)) {
    uint32_t l_17[2];
    uint64_t l_22 = 0UL;
    int32_t l_43 = 0x21B78CD9L;
    int i;
    for (i = 0; i < 2; i++)
      l_17[i] = 4UL;
    if (l_17[0]) {
      struct S0 *l_23 = &g_24;
      (*g_25) = (safe_lshift_func_uint8_t_u_s(
          (safe_rshift_func_uint8_t_u_s(
              ((((*l_23) = func_2((l_22 = (-1L)), l_11)), l_17[1]) && 1L), 1)),
          g_13));
      for (l_11 = 0; (l_11 >= 25); l_11++) {
        struct S0 l_28 = {0L};
        (*l_23) = l_28;
      }
    } else {
      const int32_t *l_55 = &g_42;
      for (g_5 = 0; (g_5 <= 1); g_5 += 1) {
        int i;
        (*g_31) =
            (l_17[g_5] <= (safe_mod_func_int64_t_s_s(
                              (g_24.f0 < 0xCFDA6C2E3A4C6382LL), l_17[g_5])));
      }
      if (l_11) {
        (*g_32) = (*g_14);
      } else {
        int32_t *l_41[2];
        int8_t *l_57 = &g_58;
        int16_t l_59 = 0L;
        uint64_t *l_60 = &l_22;
        int i;
        for (i = 0; i < 2; i++)
          l_41[i] = &g_42;
        (*l_56) =
            (0L |
             ((*l_60) &=
              ((safe_lshift_func_int16_t_s_u(
                   ((safe_lshift_func_int8_t_s_u(
                        ((*l_57) =
                             ((safe_div_func_uint16_t_u_u(
                                  ((((safe_sub_func_uint16_t_u_u(
                                         (((l_43 &= (*g_31)),
                                           (((safe_div_func_uint32_t_u_u(
                                                 (safe_sub_func_int8_t_s_s(
                                                     ((safe_unary_minus_func_int8_t_s((
                                                          (safe_lshift_func_uint8_t_u_s(
                                                              (((safe_rshift_func_int8_t_s_s(
                                                                    (safe_add_func_int32_t_s_s(
                                                                        (l_55 !=
                                                                         l_56),
                                                                        (*g_12))),
                                                                    g_13)),
                                                                (*g_14)) ==
                                                               &g_13),
                                                              g_13)) <
                                                          l_17[0]))) <=
                                                      (*l_55)),
                                                     (*l_56))),
                                                 l_17[0])) == 0x9199L) &&
                                            g_24.f0)) |
                                          0x6B495482L),
                                         0x2426L)) > g_24.f0) == g_5) ^
                                   (*l_56)),
                                  g_5)) ||
                              g_5)),
                        l_59)),
                    g_42),
                   4)),
               g_42)));
        (*g_61) = &l_60;
      }
    }
  } else {
    uint64_t l_69 = 0x9B1000BAF34C2E39LL;
    int32_t l_71 = 0x475AC351L;
    int32_t l_95 = 0x432CFC9AL;
    if ((safe_mul_func_uint8_t_u_u((safe_lshift_func_int16_t_s_u(
                                       (l_69 <= 0xD795BCD5918CD8B1LL), l_69)),
                                   (*l_56)))) {
      int32_t *volatile *l_70[4][3] = {{&g_25, &g_25, &g_25},
                                       {&g_12, &g_12, &g_12},
                                       {&g_25, &g_25, &g_25},
                                       {&g_12, &g_12, &g_12}};
      uint64_t l_72[3][3];
      int i, j;
      for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++)
          l_72[i][j] = 1UL;
      }
      (*g_32) = (*g_14);
      l_72[2][0]--;
    } else {
      uint64_t *l_75 = &l_69;
      int32_t l_80 = 3L;
      const int8_t *const l_88 = &g_58;
      if (((g_42 <= (l_75 != ((*g_62) = (**g_61)))) <= (*l_56))) {
        int64_t *l_89 = (void *)0;
        int64_t *l_90 = &g_91;
        uint32_t *l_92 = &g_93;
        int32_t *l_94 = &l_71;
        l_95 = ((*l_94) =
                    ((safe_mul_func_uint8_t_u_u(
                         (safe_mod_func_int8_t_s_s(
                             (((g_58 <
                                ((*l_56) =
                                     (l_80 &&
                                      (((*l_92) &=
                                        (safe_unary_minus_func_uint8_t_u(
                                            (((*l_75)--) ^
                                             ((*l_90) = (((g_86[2] = &g_58) !=
                                                          l_88) < g_58)))))) <=
                                       l_71)))) != l_11) >= l_80),
                             0x0EL)),
                         g_5)) != g_24.f0));
      } else {
        int32_t **l_96 = &l_56;
        (*l_96) = (void *)0;
      }
    }
  }
  return l_11;
}

static struct S0 func_2(int32_t p_3, int8_t p_4) {
  const int32_t l_15 = 0x8F0D0714L;
  struct S0 l_16 = {9L};
  (*g_14) = g_12;
  p_3 |= l_15;
  return l_16;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_5;
  csmith_sink_ = g_13;
  csmith_sink_ = g_24.f0;
  csmith_sink_ = g_42;
  csmith_sink_ = g_58;
  csmith_sink_ = g_64;
  csmith_sink_ = g_87;
  csmith_sink_ = g_91;
  csmith_sink_ = g_93;
  platform_main_end(0, 0);
  return 0;
}
