// Options:   --seed 300277 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_277.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  uint32_t f0;
  volatile int16_t f1;
};

struct S1 {
  int64_t f0;
  const uint64_t f1;
  volatile int64_t f2;
};

struct S2 {
  const uint32_t f0;
  volatile struct S1 f1;
};

static volatile int64_t g_14 = 0xD5F8D9A2B82C4475LL;
static uint8_t g_16 = 0UL;
static const int8_t g_17 = 0x03L;
static uint16_t g_27 = 0x4DE8L;
static int32_t g_32 = (-10L);
static uint8_t *g_36[2] = {(void *)0, (void *)0};
static uint8_t *volatile *volatile g_35[1][3] = {
    {&g_36[1], &g_36[1], &g_36[1]}};
static uint8_t *volatile *volatile *volatile g_37 = &g_35[0][0];
static struct S2 g_38 = {0x22CBD4DAL,
                         {0xD0F12AFBCAE26E16LL, 18446744073709551607UL, -1L}};
static volatile struct S0 g_57 = {0x54A037A7L, 0x2AFEL};
static uint32_t g_59 = 0x8F381C4EL;
static volatile struct S0 g_61 = {0x64616E91L, 0x1311L};
static struct S0 g_70 = {0UL, 0x622BL};
static struct S0 *g_69 = &g_70;
static uint64_t g_72 = 1UL;
static int8_t g_75 = 0x26L;
static uint32_t g_77 = 1UL;
static volatile uint8_t g_86 = 0xD7L;
static int32_t *g_91[3][1] = {{(void *)0}, {(void *)0}, {(void *)0}};
static int32_t **volatile g_90 = &g_91[0][0];
static struct S1 g_97[3][2] = {
    {{0xFAFEA3E439E4EAF1LL, 18446744073709551613UL, 0L},
     {0xFAFEA3E439E4EAF1LL, 18446744073709551613UL, 0L}},
    {{0xFAFEA3E439E4EAF1LL, 18446744073709551613UL, 0L},
     {0xFAFEA3E439E4EAF1LL, 18446744073709551613UL, 0L}},
    {{0xFAFEA3E439E4EAF1LL, 18446744073709551613UL, 0L},
     {0xFAFEA3E439E4EAF1LL, 18446744073709551613UL, 0L}}};
static struct S1 g_98 = {-2L, 3UL, 5L};

static struct S1 func_1(void);
static int8_t func_2(const int64_t p_3);
static struct S2 func_4(int64_t p_5, uint8_t p_6, const uint32_t p_7,
                        const int16_t p_8);

static struct S1 func_1(void) {
  uint8_t *l_15 = &g_16;
  const int32_t l_18 = 0L;
  int32_t l_78 = 0x494CF712L;
  int32_t l_80 = 8L;
  int32_t *l_89 = &l_80;
  if ((func_2((func_4((safe_mod_func_int64_t_s_s(
                          (-4L),
                          ((safe_unary_minus_func_uint16_t_u(
                               (safe_sub_func_uint16_t_u_u(
                                   g_14, ((((*l_15) |= 1UL) < g_17), 0UL))))) ^
                           g_17))),
                      g_17, l_18, l_18),
               0x015E1B460D54BA4FLL)) ^
       l_18)) {
    int16_t l_63 = 0xC1AAL;
    uint8_t **l_67 = &g_36[1];
    for (g_32 = 0; (g_32 <= 0); g_32 += 1) {
      volatile struct S0 *l_62 = &g_61;
      if (g_59)
        break;
      (*l_62) = g_61;
    }
    if (l_63) {
      int32_t l_64 = 0xD189EEBBL;
      uint16_t *l_68 = &g_27;
      uint64_t *l_71 = &g_72;
      int32_t l_73[1][1];
      int8_t *l_74 = &g_75;
      int32_t *l_76 = &g_32;
      int32_t *l_79 = (void *)0;
      int32_t *l_81 = &l_78;
      int32_t *l_82 = &l_80;
      int32_t *l_83 = &l_73[0][0];
      int32_t *l_84 = &l_78;
      int32_t *l_85[3][1];
      int i, j;
      for (i = 0; i < 1; i++) {
        for (j = 0; j < 1; j++)
          l_73[i][j] = 0x583C6DDDL;
      }
      for (i = 0; i < 3; i++) {
        for (j = 0; j < 1; j++)
          l_85[i][j] = (void *)0;
      }
      g_77 ^=
          ((*l_76) |=
           (l_64 ==
            (g_38.f1.f0 |
             (((*l_74) |=
               ((l_73[0][0] = (safe_add_func_uint64_t_u_u(
                     ((*l_71) ^= (((((((*l_68) = (((void *)0 == l_67) >= g_59)),
                                      g_69) == g_69),
                                    g_59) == g_17),
                                  g_17)),
                     (-1L)))) < g_38.f0)) &&
              0x89L))));
      --g_86;
    } else {
      const uint32_t l_92 = 4294967288UL;
      int32_t l_93 = 0x9947D74EL;
      (*g_90) = l_89;
      l_93 ^= (l_92 > (*l_89));
    }
  } else {
    uint32_t l_96 = 0xE72CC649L;
    for (g_70.f0 = 11; (g_70.f0 == 21);
         g_70.f0 = safe_add_func_uint16_t_u_u(g_70.f0, 7)) {
      (*l_89) ^= l_96;
    }
    return g_97[2][1];
  }
  return g_98;
}

static int8_t func_2(const int64_t p_3) {
  uint16_t l_56 = 0xEBDCL;
  uint32_t *l_58 = &g_59;
  int32_t *l_60 = &g_32;
  (*l_60) &= (safe_div_func_int32_t_s_s(
      p_3, (safe_sub_func_int16_t_s_s(
               (((safe_div_func_uint32_t_u_u(
                     (+(safe_mul_func_uint16_t_u_u(
                         (+(safe_rshift_func_int8_t_s_u(
                             ((safe_mul_func_uint16_t_u_u(
                                  (!((((*l_58) &= (safe_mul_func_uint16_t_u_u(
                                           l_56, (g_57, l_56)))),
                                      &g_27) == (void *)0)),
                                  0xAD1DL)) <= l_56),
                             6))),
                         0UL))),
                     1L)) &
                 g_17),
                0x1194L),
               p_3))));
  (*l_60) &= 0x3A1A91F1L;
  return g_57.f0;
}

static struct S2 func_4(int64_t p_5, uint8_t p_6, const uint32_t p_7,
                        const int16_t p_8) {
  int64_t l_25 = 0x8475761AC7EB2367LL;
  uint16_t *l_26 = &g_27;
  uint32_t l_30[2];
  int32_t *l_31 = &g_32;
  int i;
  for (i = 0; i < 2; i++)
    l_30[i] = 0x1BD77DFCL;
  (*l_31) |=
      ((safe_lshift_func_uint8_t_u_s(
           ((((safe_mod_func_int32_t_s_s(
                  (((*l_26) = (safe_div_func_uint16_t_u_u(65535UL, l_25))) <
                   (safe_lshift_func_int16_t_s_u(g_17, g_16))),
                  l_30[1])),
              0UL) ^
             0x4067BC62L) != g_17),
           g_14)) > g_16);
  for (p_6 = (-27); (p_6 > 26); p_6 = safe_add_func_uint64_t_u_u(p_6, 8)) {
    (*g_37) = g_35[0][2];
  }
  return g_38;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_14;
  csmith_sink_ = g_16;
  csmith_sink_ = g_17;
  csmith_sink_ = g_27;
  csmith_sink_ = g_32;
  csmith_sink_ = g_38.f0;
  csmith_sink_ = g_38.f1.f0;
  csmith_sink_ = g_38.f1.f1;
  csmith_sink_ = g_38.f1.f2;
  csmith_sink_ = g_57.f0;
  csmith_sink_ = g_57.f1;
  csmith_sink_ = g_59;
  csmith_sink_ = g_61.f0;
  csmith_sink_ = g_61.f1;
  csmith_sink_ = g_70.f0;
  csmith_sink_ = g_70.f1;
  csmith_sink_ = g_72;
  csmith_sink_ = g_75;
  csmith_sink_ = g_77;
  csmith_sink_ = g_86;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++) {
    }
  }
  csmith_sink_ = g_98.f0;
  csmith_sink_ = g_98.f1;
  csmith_sink_ = g_98.f2;
  platform_main_end(0, 0);
  return 0;
}
