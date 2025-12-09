// Options:   --seed 300204 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_204.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  int8_t f0;
  int16_t f1;
  uint64_t f2;
};

struct S1 {
  const uint32_t f0;
  uint8_t f1;
  const volatile uint16_t f2;
};

static volatile int32_t g_2[2][2] = {{0L, 0L}, {0L, 0L}};
static int32_t g_3 = 3L;
static int32_t g_6[2][2] = {{0x45D811F0L, 0x45D811F0L},
                            {0x45D811F0L, 0x45D811F0L}};
static int32_t g_10 = (-8L);
static int8_t g_51 = 0xC1L;
static struct S1 g_55 = {1UL, 1UL, 65535UL};
static uint32_t g_69 = 4294967294UL;
static uint32_t g_73 = 0x0F805AAAL;
static uint8_t *g_75 = &g_55.f1;
static struct S1 *g_102 = (void *)0;
static struct S1 **volatile g_101 = &g_102;
static uint64_t g_117 = 0xEACEA086712C952ALL;
static int16_t g_120 = 4L;
static int32_t *g_122 = &g_10;
static int32_t **volatile g_121 = &g_122;

static int32_t func_1(void);
static int32_t func_20(const int32_t *p_21, int32_t *p_22, int32_t *p_23,
                       int32_t *const p_24, int32_t *p_25);
static struct S1 func_26(const uint32_t p_27, const uint32_t p_28);

static int32_t func_1(void) {
  uint32_t l_13 = 0x2D5FBA25L;
  int32_t *l_16 = &g_6[1][0];
  int32_t l_87 = (-3L);
  int32_t l_88 = 0L;
  int32_t l_89 = 3L;
  int32_t l_90[3];
  int16_t l_91 = 8L;
  struct S1 *l_100 = &g_55;
  int i;
  for (i = 0; i < 3; i++)
    l_90[i] = 0x3EA4B039L;
  for (g_3 = 0; (g_3 == (-15)); g_3 = safe_sub_func_int16_t_s_s(g_3, 4)) {
    int16_t l_12 = 1L;
    for (g_6[1][1] = 0; (g_6[1][1] == (-9)); g_6[1][1]--) {
      int32_t *l_9[2][2] = {{&g_10, &g_10}, {&g_10, &g_10}};
      int64_t l_11[1][1];
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 1; j++)
          l_11[i][j] = 5L;
      }
      ++l_13;
      g_2[1][0] &= g_3;
    }
  }
  if (((*l_16) = 0x9281C1D9L)) {
    return (*l_16);
  } else {
    uint32_t l_19 = 0x81230B63L;
    int32_t *const l_56[1] = {&g_10};
    int32_t *l_57 = &g_3;
    uint8_t *l_84 = &g_55.f1;
    uint32_t l_104 = 4294967295UL;
    int i;
    if ((safe_mod_func_int32_t_s_s(
            l_19, func_20((func_26(l_19, (l_19 == (*l_16))), l_16), &g_6[1][1],
                          l_16, l_56[0], l_57)))) {
      (*l_16) = (*l_16);
    } else {
      uint8_t **l_76 = (void *)0;
      uint8_t **l_77 = &g_75;
      uint8_t **l_78 = (void *)0;
      uint8_t *l_80 = &g_55.f1;
      uint8_t **l_79 = &l_80;
      const int64_t l_83 = 0x71196D9F78EB2920LL;
      int32_t l_85 = 0x35E4DCDAL;
      int32_t l_86[1][1];
      uint32_t l_92 = 0x20B58E85L;
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 1; j++)
          l_86[i][j] = 0x377C446CL;
      }
      g_10 |= ((0x550B438E4B99A093LL &&
                (((*l_79) = ((*l_77) = g_75)) ==
                 ((safe_sub_func_uint16_t_u_u(
                      (((g_55.f2 == 4294967292UL) && (-8L)) && (*l_16)), l_83)),
                  l_84))),
               l_83);
      l_92++;
      if (l_92)
        goto lbl_103;
    }
    if ((((safe_div_func_uint64_t_u_u(((*l_57) = (~g_6[1][1])), (*l_16))) ==
          ((safe_div_func_int32_t_s_s(g_55.f2, 4294967287UL)), (*l_16))) >
         18446744073709551615UL)) {
    lbl_103:
      (*g_101) = l_100;
      (*l_16) = (l_104 == g_2[0][0]);
    } else {
      int32_t l_116 = (-8L);
      int16_t *l_118 = &l_91;
      int16_t *l_119 = &g_120;
      g_10 |=
          ((((((*l_119) =
                   ((*l_118) =
                        ((safe_sub_func_int16_t_s_s(
                             (((safe_rshift_func_int8_t_s_u(
                                   (safe_rshift_func_int16_t_s_u(
                                       (safe_div_func_int16_t_s_s(
                                           (g_117 =
                                                ((((~(safe_div_func_uint32_t_u_u(
                                                       l_116, l_116))) >
                                                   g_6[1][0]) &
                                                  l_116) <=
                                                 0x62E55A95E6A16A95LL)),
                                           g_3)),
                                       g_3)),
                                   (*l_16))) > g_55.f2) ||
                              g_3),
                             g_6[1][1])),
                         0x7979L))) < 0xC417L) &&
             g_2[1][0]) &&
            0x0C0CL) <= g_55.f1);
      (*g_121) = &g_6[0][0];
    }
  }
  return (*l_16);
}

static int32_t func_20(const int32_t *p_21, int32_t *p_22, int32_t *p_23,
                       int32_t *const p_24, int32_t *p_25) {
  struct S0 l_58 = {-1L, 0x7FF9L, 0x38BD60138ADD5270LL};
  struct S0 *l_59 = &l_58;
  (*l_59) = l_58;
  for (g_3 = 0; (g_3 <= 1); g_3 += 1) {
    uint32_t *l_67 = (void *)0;
    uint32_t *l_68 = &g_69;
    uint8_t *l_72[2][1];
    int32_t l_74 = 0L;
    int i, j;
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 1; j++)
        l_72[i][j] = &g_55.f1;
    }
    (*p_22) = (!(safe_rshift_func_int16_t_s_u(
        (((safe_add_func_uint16_t_u_u(
              g_2[1][0],
              (safe_sub_func_uint32_t_u_u(
                  ((*l_68) = g_55.f0),
                  (((safe_lshift_func_uint8_t_u_s(
                        (g_73 = ((g_10 || g_55.f1) >= l_58.f2)), 0)) |
                    0xF838L),
                   4294967295UL))))) <= g_55.f1) > 0x02L),
        l_74)));
    return g_6[1][1];
  }
  return (*p_24);
}

static struct S1 func_26(const uint32_t p_27, const uint32_t p_28) {
  int32_t *l_29 = &g_3;
  int32_t *l_30 = &g_3;
  int32_t *l_31 = (void *)0;
  int32_t *l_32 = &g_6[1][1];
  int32_t *l_33 = &g_10;
  int32_t *l_34 = &g_10;
  int32_t *l_35 = &g_10;
  int32_t l_36 = 0x2E7BAA9DL;
  int32_t *l_37 = &g_3;
  int32_t l_38 = 0x5CF455DBL;
  int32_t *l_39 = (void *)0;
  int32_t l_40 = 0x72BE76DCL;
  int32_t *l_41 = &l_38;
  int32_t *l_42 = &l_38;
  int32_t *l_43 = &g_10;
  int32_t *l_44 = &g_6[1][1];
  int32_t *l_45 = &l_36;
  int32_t *l_46 = &g_10;
  int32_t l_47 = 0x097756EBL;
  int32_t *l_48 = &g_6[0][0];
  int32_t *l_49[3][1];
  int16_t l_50[2];
  uint32_t l_52 = 0x18CA4024L;
  int i, j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++)
      l_49[i][j] = &g_10;
  }
  for (i = 0; i < 2; i++)
    l_50[i] = 0xB2BDL;
  --l_52;
  return g_55;
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
  csmith_sink_ = g_3;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_6[i][j];
    }
  }
  csmith_sink_ = g_10;
  csmith_sink_ = g_51;
  csmith_sink_ = g_55.f0;
  csmith_sink_ = g_55.f1;
  csmith_sink_ = g_55.f2;
  csmith_sink_ = g_69;
  csmith_sink_ = g_73;
  csmith_sink_ = g_117;
  csmith_sink_ = g_120;
  platform_main_end(0, 0);
  return 0;
}
