// Options:   --seed 300237 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_237.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  int16_t f0;
};

struct S1 {
  volatile uint8_t f0;
  volatile uint32_t f1;
};

struct S5 {
  int8_t f0;
  volatile int8_t f1;
  uint8_t f2;
};

struct S6 {
  uint16_t f0;
  uint16_t f1;
  uint32_t f2;
};

static struct S6 g_11 = {1UL, 8UL, 0x3735B263L};
static int32_t g_12[2] = {(-1L), (-1L)};
static int8_t g_25 = 1L;
static struct S1 g_43 = {7UL, 0xBA6F4617L};
static int64_t g_45 = 0xED293A85175EF58ELL;
static int32_t *volatile g_64 = &g_12[0];
static struct S0 g_65 = {9L};
static struct S5 g_75[2][2] = {{{0x20L, -2L, 9UL}, {0x20L, -2L, 9UL}},
                               {{0x20L, -2L, 9UL}, {0x20L, -2L, 9UL}}};
static int32_t *g_86 = &g_12[0];
static int32_t **volatile g_85[3] = {&g_86, &g_86, &g_86};
static struct S6 g_94 = {0x9083L, 65535UL, 4294967289UL};

static int16_t func_1(void);
static int8_t func_4(uint16_t p_5, int32_t p_6, const int32_t p_7,
                     struct S0 p_8);
static uint16_t func_9(struct S6 p_10);

static int16_t func_1(void) {
  int64_t *l_68 = &g_45;
  int64_t **l_69 = (void *)0;
  int64_t **l_70 = &l_68;
  struct S0 l_71 = {8L};
  int32_t *const l_84 = &g_12[1];
  uint32_t l_96 = 0UL;
  if ((safe_rshift_func_int8_t_s_u(
          func_4(func_9(g_11), ((((*l_70) = l_68) != &g_45) ^ 0x9755A17AL),
                 g_25, l_71),
          7))) {
    int64_t l_77 = 0L;
    return l_77;
  } else {
    uint32_t l_81 = 9UL;
    for (g_45 = 0; (g_45 != (-16)); g_45--) {
      int32_t *l_80[3][3] = {{&g_12[1], &g_12[1], &g_12[1]},
                             {(void *)0, (void *)0, (void *)0},
                             {&g_12[1], &g_12[1], &g_12[1]}};
      int32_t **l_87 = &l_80[2][2];
      int i, j;
      l_81--;
      (*l_87) = l_84;
    }
    for (g_11.f1 = 0; (g_11.f1 < 35); ++g_11.f1) {
      uint16_t l_90 = 0xDFDFL;
      struct S6 *l_93 = &g_94;
      int32_t l_95 = 5L;
      (*g_64) = (l_90 = l_81);
      l_95 = (safe_mul_func_uint8_t_u_u(g_43.f0,
                                        (((*l_93) = (l_90, g_11)), g_45)));
    }
  }
  l_96--;
  return (*l_84);
}

static int8_t func_4(uint16_t p_5, int32_t p_6, const int32_t p_7,
                     struct S0 p_8) {
  int32_t *l_73 = &g_12[0];
  int32_t **l_72[3];
  int32_t *l_74 = &g_12[1];
  struct S5 *l_76 = &g_75[1][1];
  int i;
  for (i = 0; i < 3; i++)
    l_72[i] = &l_73;
  l_74 = &p_6;
  (*l_76) = g_75[1][0];
  return p_6;
}

static uint16_t func_9(struct S6 p_10) {
  int32_t l_17 = 0xB302AFF6L;
  int32_t l_27 = (-6L);
  int32_t l_30 = 1L;
  int32_t l_31 = 0L;
  int32_t l_32 = (-9L);
  int32_t l_33 = 0xEB13E27CL;
  int32_t l_34 = 0xF9F6D65DL;
  struct S0 l_48 = {-5L};
  int32_t l_67 = 7L;
  for (g_11.f2 = 0; (g_11.f2 <= 1); g_11.f2 += 1) {
    uint32_t l_18 = 0x0C11E043L;
    uint16_t *l_19 = (void *)0;
    uint16_t *l_20 = &g_11.f0;
    int32_t l_26 = 0xF22A1EFEL;
    int32_t l_28 = 0x96FD0FE1L;
    int32_t l_29[1][2];
    uint64_t l_35 = 0x64D14C5BDDF9C202LL;
    uint32_t l_40 = 18446744073709551606UL;
    int64_t *l_44[3][3] = {{(void *)0, (void *)0, (void *)0},
                           {&g_45, &g_45, &g_45},
                           {(void *)0, (void *)0, (void *)0}};
    int i, j;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 2; j++)
        l_29[i][j] = 9L;
    }
    if ((safe_mod_func_uint32_t_u_u(
            (safe_add_func_uint16_t_u_u(
                ((*l_20) |= ((l_17 != 0x88L) ^ ((l_18 == g_11.f1) <= g_11.f1))),
                1L)),
            p_10.f2))) {
      int32_t *l_21 = &g_12[g_11.f2];
      int32_t *l_22 = &g_12[1];
      int32_t *l_23 = &g_12[g_11.f2];
      int32_t *l_24[3][2];
      int i, j;
      for (i = 0; i < 3; i++) {
        for (j = 0; j < 2; j++)
          l_24[i][j] = &g_12[g_11.f2];
      }
      l_35--;
    } else {
      int32_t *l_38 = (void *)0;
      int32_t *l_39[3];
      int i;
      for (i = 0; i < 3; i++)
        l_39[i] = (void *)0;
      ++l_40;
    }
    if (((p_10.f2 < (l_33 = (((*l_20) = (g_43, l_26)), l_40))), 0x4A3AAF95L)) {
      uint32_t l_62 = 18446744073709551608UL;
      int32_t l_63[2][3] = {{1L, 0x79765BC9L, 1L}, {1L, 0x79765BC9L, 1L}};
      int i, j;
      (*g_64) =
          (l_63[1][0] = (safe_lshift_func_uint16_t_u_s(
               (l_48, p_10.f1),
               (safe_div_func_uint32_t_u_u(
                   (((safe_mod_func_int32_t_s_s(
                         (~((safe_add_func_int16_t_s_s(
                                (safe_mul_func_int16_t_s_s(
                                    (safe_add_func_uint32_t_u_u(
                                        ((p_10.f0--) | 0x8E67L), 0x51155E33L)),
                                    65535UL)),
                                l_62)) ^
                            l_62)),
                         l_62)) <= 0x6052A731L) == g_25),
                   p_10.f2)))));
    } else {
      struct S0 *l_66 = &g_65;
      (*l_66) = g_65;
    }
  }
  return l_67;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_11.f0;
  csmith_sink_ = g_11.f1;
  csmith_sink_ = g_11.f2;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_12[i];
  }
  csmith_sink_ = g_25;
  csmith_sink_ = g_43.f0;
  csmith_sink_ = g_43.f1;
  csmith_sink_ = g_45;
  csmith_sink_ = g_65.f0;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
    }
  }
  csmith_sink_ = g_94.f0;
  csmith_sink_ = g_94.f1;
  csmith_sink_ = g_94.f2;
  platform_main_end(0, 0);
  return 0;
}
