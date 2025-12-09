// Options:   --seed 200176 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_176.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S1 {
  int64_t f0;
  volatile uint32_t f1;
};

static volatile int32_t g_3 = (-8L);
static volatile int32_t g_4 = 0x182EAC45L;
static volatile int32_t g_5[3][4] = {{(-7L), (-4L), (-7L), (-7L)},
                                     {(-4L), (-4L), 0x565E08CCL, (-4L)},
                                     {(-4L), (-7L), (-7L), (-4L)}};
static volatile int32_t g_6 = 0x8F576C51L;
static int32_t g_7 = (-8L);
static volatile int32_t g_8[4][4] = {
    {0x3D069F49L, 0x06C902DAL, 0x3D069F49L, 0x3D069F49L},
    {0x06C902DAL, 0x06C902DAL, 0x09884CB8L, 0x06C902DAL},
    {0x06C902DAL, 0x3D069F49L, 0x3D069F49L, 0x06C902DAL},
    {0x3D069F49L, 0x06C902DAL, 0x3D069F49L, 0x3D069F49L}};
static volatile int32_t g_9[3] = {0x934B0B4EL, 0x934B0B4EL, 0x934B0B4EL};
static int32_t g_10[1] = {0x722BA7B7L};
static int32_t g_13 = 0xB168F928L;
static int32_t g_25 = 0x4CC511ECL;
static uint64_t g_34 = 0x9D65FE96F77D900DLL;
static int8_t g_41 = 0x39L;
static const volatile struct S1 g_42 = {3L, 1UL};
static volatile struct S1 g_44[3][2] = {
    {{0xC37461BCF2EC2878LL, 18446744073709551612UL},
     {0xC37461BCF2EC2878LL, 18446744073709551612UL}},
    {{0xC37461BCF2EC2878LL, 18446744073709551612UL},
     {0xC37461BCF2EC2878LL, 18446744073709551612UL}},
    {{0xC37461BCF2EC2878LL, 18446744073709551612UL},
     {0xC37461BCF2EC2878LL, 18446744073709551612UL}}};
static float g_47 = 0x9.Fp-1;
static uint16_t g_48 = 0x42BFL;
static int64_t g_58 = 0xE4B4BC07302220C9LL;
static volatile int32_t *g_73 = (void *)0;
static volatile int32_t **volatile g_72 = &g_73;
static int64_t *g_81[3] = {(void *)0, (void *)0, (void *)0};

static uint16_t func_1(void);
static int32_t func_18(int32_t *p_19, int16_t p_20, uint16_t p_21, float p_22,
                       uint64_t p_23);

static uint16_t func_1(void) {
  float l_2[1];
  int32_t l_24 = 0x1966C477L;
  int32_t *l_29 = &g_10[0];
  int32_t **l_28 = &l_29;
  int32_t l_64 = 0x4B39C2D9L;
  int32_t l_65 = 0x5B9AADFEL;
  int32_t l_66 = 6L;
  int32_t l_67 = 0L;
  uint32_t l_68 = 8UL;
  int i;
  for (i = 0; i < 1; i++)
    l_2[i] = 0x3.8ECF54p-78;
  for (g_7 = 0; (g_7 <= 0); g_7 += 1) {
    for (g_10[0] = 0; (g_10[0] <= 0); g_10[0] += 1) {
      uint32_t l_11 = 4294967295UL;
      int32_t *l_12 = &g_13;
      (*l_12) ^= l_11;
      return g_8[2][0];
    }
  }
  if ((safe_sub_func_uint32_t_u_u(
          (((safe_div_func_int32_t_s_s(
                func_18(
                    &g_10[0], (g_25 ^= l_24),
                    ((safe_mul_func_int8_t_s_s(
                         ((((*l_28) = &l_24) != &g_8[2][1]) <= 1L), g_13)) ||
                     (**l_28)),
                    g_8[3][3], g_10[0]),
                g_48)) &
            g_48) < g_48),
          g_48))) {
    uint32_t l_56 = 4294967293UL;
    int64_t *l_57 = &g_58;
    int32_t l_63 = 1L;
    if (((g_44[2][1],
          (safe_rshift_func_int16_t_s_s(
              g_34,
              ((!((*l_57) |= (((safe_div_func_float_f_f(
                                   (safe_sub_func_float_f_f((-0x1.7p+1), l_56)),
                                   l_56)) >= 0x0.1p+1),
                              (-3L)))),
               (-3L))))) <= 4294967295UL)) {
      int32_t *l_59 = &g_10[0];
      l_59 = (void *)0;
    } else {
      int32_t *l_60 = &g_13;
      int32_t *l_61 = &g_13;
      int32_t *l_62[4][2] = {{&l_24, (void *)0},
                             {&l_24, &l_24},
                             {(void *)0, (void *)0},
                             {(void *)0, &g_13}};
      volatile int32_t **l_71 = (void *)0;
      int i, j;
      ++l_68;
      (*g_72) = &g_8[0][0];
    }
  } else {
    const int64_t *l_80 = &g_58;
    int32_t l_82 = 7L;
    if ((safe_mul_func_int16_t_s_s(
            (((safe_rshift_func_int16_t_s_u(
                  (safe_rshift_func_int8_t_s_s((l_80 != (g_81[1] = &g_58)), 7)),
                  ((g_42.f0 <= g_34) != g_25))),
              0L) == l_82),
            g_13))) {
      (*l_29) = 0x896CD2A5L;
      (**l_28) = (-4L);
    } else {
      return l_82;
    }
  }
  return g_10[0];
}

static int32_t func_18(int32_t *p_19, int16_t p_20, uint16_t p_21, float p_22,
                       uint64_t p_23) {
  int32_t *l_32 = &g_13;
  for (p_20 = 0; (p_20 <= 2); p_20 += 1) {
    for (g_13 = 0; (g_13 <= 2); g_13 += 1) {
      int i, j;
      return g_5[g_13][(g_13 + 1)];
    }
    for (g_7 = 2; (g_7 >= 0); g_7 -= 1) {
      uint64_t *l_33 = &g_34;
      int32_t *l_35 = &g_13;
      int i, j;
      g_5[p_20][p_20] |=
          (0xEC1EL <
           (((*l_33) = (safe_sub_func_uint32_t_u_u(
                 0x11771B70L, (((l_32 = (void *)0) == &g_3), (-7L))))),
            g_10[0]));
      (*l_35) = ((*p_19) = 0xE1DC630DL);
    }
  }
  for (g_34 = 0; (g_34 == 21); g_34 = safe_add_func_uint8_t_u_u(g_34, 1)) {
    int8_t *l_40 = &g_41;
    volatile struct S1 *l_43 = &g_44[2][1];
    int32_t *l_45 = (void *)0;
    float *l_46[2][2];
    int i, j;
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 2; j++)
        l_46[i][j] = &g_47;
    }
    (*l_43) =
        ((((safe_lshift_func_uint8_t_u_s(
               g_10[0], ((*l_40) = (0x9AL || ((((p_23 != 0x2CL) & 0xAB83DCDCL),
                                               g_25) >= 65535UL))))) >
           (*p_19)) == 0L),
         g_42);
    g_47 = (l_32 != l_45);
  }
  return (*p_19);
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  csmith_sink_ = g_4;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_5[i][j];
    }
  }
  csmith_sink_ = g_6;
  csmith_sink_ = g_7;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_8[i][j];
    }
  }
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_9[i];
  }
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_10[i];
  }
  csmith_sink_ = g_13;
  csmith_sink_ = g_25;
  csmith_sink_ = g_34;
  csmith_sink_ = g_41;
  csmith_sink_ = g_42.f0;
  csmith_sink_ = g_42.f1;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++) {
    }
  }
  csmith_sink_ = g_47;
  csmith_sink_ = g_48;
  csmith_sink_ = g_58;
  platform_main_end(0, 0);
  return 0;
}
