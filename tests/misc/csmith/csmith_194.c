// Options:   --seed 200194 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_194.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S1 {
  volatile uint8_t f0;
};

struct S0 {
  volatile uint16_t f0;
  const int16_t f1;
  volatile uint32_t f2;
};

struct S2 {
  volatile struct S0 f0;
  const int32_t f1;
  float f2;
};

static int32_t g_6 = 0x70A77C87L;
static uint8_t g_11[1] = {0x5DL};
static int16_t g_12[1] = {(-6L)};
static int32_t g_14[2][3] = {{1L, 1L, 1L}, {1L, 1L, 1L}};
static volatile uint16_t g_29 = 1UL;
static struct S1 g_35 = {6UL};
static uint64_t g_45 = 0xE84CBF7762406C49LL;
static struct S2 g_46[3][4] = {{{{4UL, -1L, 0xF9E8BFA0L}, 0L, -0x5.1p+1},
                                {{4UL, -1L, 0xF9E8BFA0L}, 0L, -0x5.1p+1},
                                {{4UL, -1L, 0xF9E8BFA0L}, 0L, -0x5.1p+1},
                                {{4UL, -1L, 0xF9E8BFA0L}, 0L, -0x5.1p+1}},
                               {{{4UL, -1L, 0xF9E8BFA0L}, 0L, -0x5.1p+1},
                                {{4UL, -1L, 0xF9E8BFA0L}, 0L, -0x5.1p+1},
                                {{4UL, -1L, 0xF9E8BFA0L}, 0L, -0x5.1p+1},
                                {{4UL, -1L, 0xF9E8BFA0L}, 0L, -0x5.1p+1}},
                               {{{4UL, -1L, 0xF9E8BFA0L}, 0L, -0x5.1p+1},
                                {{4UL, -1L, 0xF9E8BFA0L}, 0L, -0x5.1p+1},
                                {{4UL, -1L, 0xF9E8BFA0L}, 0L, -0x5.1p+1},
                                {{4UL, -1L, 0xF9E8BFA0L}, 0L, -0x5.1p+1}}};
static float *volatile g_47 = &g_46[2][1].f2;
static struct S1 g_50 = {255UL};
static float *const volatile g_56 = &g_46[2][1].f2;
static uint64_t g_61 = 0x1468F30040642FC3LL;
static volatile struct S1 g_64 = {250UL};
static volatile struct S1 *volatile g_65 = &g_64;
static float g_78 = 0x0.56B0C4p+45;
static float *const volatile g_77 = &g_78;
static int32_t *g_81 = &g_6;
static int32_t **volatile g_80 = &g_81;

static uint64_t func_1(void);
static int32_t *func_2(int32_t *p_3, int32_t p_4);

static uint64_t func_1(void) {
  int32_t *l_5 = &g_6;
  int32_t *l_13[2];
  int i;
  for (i = 0; i < 2; i++)
    l_13[i] = &g_14[1][2];
  (*g_80) = func_2(
      l_5,
      (g_14[1][1] &=
       (g_12[0] =
            ((*l_5) ^ (safe_mod_func_uint16_t_u_u(
                          (safe_lshift_func_uint8_t_u_u(
                              (((0x7E78L != 0xCDE9L) > g_11[0]) & 0xDFADL), 6)),
                          (*l_5)))))));
  return g_35.f0;
}

static int32_t *func_2(int32_t *p_3, int32_t p_4) {
  float l_19 = 0x2.DA3C3Dp-84;
  int32_t l_24[1];
  volatile struct S1 *l_79 = &g_64;
  int i;
  for (i = 0; i < 1; i++)
    l_24[i] = 0L;
  if (((safe_lshift_func_int16_t_s_s(
           (8UL &&
            (((safe_div_func_float_f_f((l_19 = g_11[0]), p_4)), g_14[0][2]) |
             p_4)),
           3)) ||
       p_4)) {
    int8_t l_23 = (-1L);
    int16_t *l_25 = (void *)0;
    int16_t *l_26 = &g_12[0];
    int32_t l_59 = 1L;
    if (((!((*l_26) = ((safe_rshift_func_int16_t_s_u(l_23, 12)) <=
                       (p_4 == (l_24[0] || p_4))))) == l_24[0])) {
      int32_t *l_27 = &l_24[0];
      int32_t *l_28 = &l_24[0];
      --g_29;
    } else {
      int16_t l_43 = 6L;
      float *l_44 = (void *)0;
      (*g_47) = (safe_add_func_float_f_f(
          ((!(g_35, (safe_add_func_float_f_f(
                        (+(safe_mul_func_float_f_f(
                            (safe_div_func_float_f_f((g_45 = l_43),
                                                     (g_46[2][1], l_24[0]))),
                            l_43))),
                        p_4)))) < 0x5.4CEAA9p+51),
          p_4));
    }
    for (g_45 = 0; (g_45 > 9); g_45 = safe_add_func_int16_t_s_s(g_45, 6)) {
      uint16_t l_55 = 1UL;
      int32_t *l_57 = &l_24[0];
      int32_t *l_58 = &g_6;
      int32_t l_60 = (-10L);
      (*g_56) = (((g_50, (safe_div_func_float_f_f(
                             (safe_sub_func_float_f_f(
                                 0x9.A2DD31p-52, ((l_24[0] != p_4) == p_4))),
                             (*g_47)))) > p_4) < l_55);
      g_61++;
    }
  } else {
    uint16_t l_66[3][1];
    int i, j;
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 1; j++)
        l_66[i][j] = 0x5426L;
    }
    if ((1L & (((&g_6 == (void *)0) | 0x4EB7L) <= g_12[0]))) {
      (*g_65) = g_64;
    } else {
      float *l_75 = &g_46[2][1].f2;
      float *l_76 = &l_19;
      l_66[1][0]++;
      (*g_77) = (safe_mul_func_float_f_f(
          ((*l_76) = (safe_mul_func_float_f_f(
               ((*l_75) = (safe_add_func_float_f_f(
                    ((void *)0 == g_47), (0x6.E024B1p-64 <= 0x7.0p-1)))),
               (-0x5.2p-1)))),
          l_24[0]));
    }
  }
  (*l_79) = (*g_65);
  return p_3;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_6;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_11[i];
  }
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_12[i];
  }
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_14[i][j];
    }
  }
  csmith_sink_ = g_29;
  csmith_sink_ = g_35.f0;
  csmith_sink_ = g_45;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 4; j++) {
    }
  }
  csmith_sink_ = g_50.f0;
  csmith_sink_ = g_61;
  csmith_sink_ = g_64.f0;
  csmith_sink_ = g_78;
  platform_main_end(0, 0);
  return 0;
}
