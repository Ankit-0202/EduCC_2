// Options:   --seed 200150 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_150.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  uint16_t f0;
};

union U1 {
  volatile float f0;
  float f1;
};

union U2 {
  const uint32_t f0;
};

union U3 {
  volatile uint32_t f0;
  float f1;
};

union U5 {
  int64_t f0;
};

static int32_t g_2[4][4] = {
    {0xEA41449CL, 0xEA41449CL, 0xEA41449CL, 0xEA41449CL},
    {0xEA41449CL, 0xEA41449CL, 0xEA41449CL, 0xEA41449CL},
    {0xEA41449CL, 0xEA41449CL, 0xEA41449CL, 0xEA41449CL},
    {0xEA41449CL, 0xEA41449CL, 0xEA41449CL, 0xEA41449CL}};
static int32_t *g_7 = &g_2[3][1];
static int32_t **volatile g_6 = &g_7;
static union U2 g_15 = {0x9A22DB78L};
static union U2 *g_14 = &g_15;
static struct S0 g_17[1] = {{0xA4D3L}};
static int32_t g_19 = 0x56A0B349L;
static int32_t g_37 = 0xF41ADF89L;
static volatile int64_t g_38 = 5L;
static uint32_t g_46 = 1UL;
static union U3 g_55 = {0x94D23A2CL};
static union U3 *g_54 = &g_55;
static union U1 g_59 = {0xA.6A8E49p-82};
static struct S0 *volatile g_60 = &g_17[0];
static int8_t g_69 = 0L;
static const int32_t g_74 = 0x866C5D89L;
static const int32_t *g_77[4][2] = {
    {&g_19, &g_19}, {&g_19, &g_19}, {&g_19, &g_19}, {&g_19, &g_19}};

static float func_1(void);
static union U2 *func_8(union U2 *p_9, union U5 p_10, uint8_t p_11,
                        struct S0 p_12, int32_t *const p_13);

static float func_1(void) {
  union U5 l_16 = {0xC38EC326874BE76DLL};
  int32_t **l_67 = &g_7;
  for (g_2[1][2] = (-1); (g_2[1][2] >= 15); g_2[1][2]++) {
    int32_t **l_5 = (void *)0;
    union U2 **l_58[1][2];
    int i, j;
    for (i = 0; i < 1; i++) {
      for (j = 0; j < 2; j++)
        l_58[i][j] = &g_14;
    }
    (*g_6) = &g_2[1][2];
    g_14 = func_8(g_14, l_16, g_2[2][0], g_17[0], (*g_6));
  }
  for (g_19 = 0; (g_19 <= 3); g_19 += 1) {
    int8_t *l_68 = &g_69;
    int32_t l_70 = 0x8F681728L;
    struct S0 l_78[2] = {{0xF119L}, {0xF119L}};
    int i;
    (*g_60) = (g_59, g_17[0]);
    if ((safe_sub_func_int16_t_s_s(
            (safe_div_func_int16_t_s_s(
                ((((((0x0EL ^ (safe_lshift_func_int8_t_s_s(
                                  g_15.f0, ((*l_68) ^= (l_67 != &g_7))))) >=
                     l_70) < 0x5FA727FAL) &&
                   (*g_7)) >= (*g_7)) <= l_70),
                g_38)),
            l_70))) {
      const int32_t **l_71 = (void *)0;
      const int32_t *l_73 = &g_74;
      const int32_t **l_72 = &l_73;
      const int32_t *l_76 = &l_70;
      const int32_t **l_75[4][4];
      int i, j;
      for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++)
          l_75[i][j] = &l_76;
      }
      g_77[0][1] = ((*l_72) = (*g_6));
    } else {
      struct S0 *l_79 = &g_17[0];
      (*l_79) = l_78[1];
    }
    for (l_16.f0 = 0; (l_16.f0 >= 0); l_16.f0 -= 1) {
      float *l_86 = &g_55.f1;
      int i, j;
      (*l_86) = (safe_mul_func_float_f_f(
          (safe_mul_func_float_f_f(
              (safe_sub_func_float_f_f(g_2[g_19][(l_16.f0 + 1)], (**l_67))),
              0xE.831782p+11)),
          g_19));
    }
  }
  return (**l_67);
}

static union U2 *func_8(union U2 *p_9, union U5 p_10, uint8_t p_11,
                        struct S0 p_12, int32_t *const p_13) {
  int32_t *l_18 = &g_19;
  int32_t *l_20 = &g_19;
  int32_t *l_21 = &g_19;
  int32_t *l_22 = &g_19;
  int32_t *l_23 = &g_19;
  int32_t *l_24 = (void *)0;
  int32_t *l_25 = &g_19;
  int32_t *l_26 = (void *)0;
  int32_t *l_27 = (void *)0;
  int32_t *l_28 = &g_19;
  int32_t l_29 = 0x6FBFCC01L;
  int32_t *l_30 = &l_29;
  int32_t *l_31 = (void *)0;
  int32_t *l_32 = &l_29;
  int32_t *l_33 = &g_19;
  int32_t *l_34 = &l_29;
  int32_t l_35 = (-1L);
  int32_t *l_36[4][1] = {{&l_29}, {&l_35}, {&l_29}, {&l_35}};
  uint8_t l_39 = 247UL;
  union U2 *l_57[1];
  int i, j;
  for (i = 0; i < 1; i++)
    l_57[i] = &g_15;
  l_39++;
  if ((safe_sub_func_int64_t_s_s(
          (4294967289UL ^
           (((0xFE2D584125DBF607LL ||
              ((safe_sub_func_int8_t_s_s(
                   (((--g_46) != ((safe_rshift_func_int8_t_s_u(g_38, p_11)) >
                                  g_19)) != p_11),
                   g_2[1][2])) ||
               (*l_34))),
             p_11) >= 0x7CAFL)),
          18446744073709551607UL))) {
    union U2 *l_53 = &g_15;
    for (p_10.f0 = 14; (p_10.f0 <= (-10)); p_10.f0--) {
      return l_53;
    }
  } else {
    union U3 *l_56 = &g_55;
    l_56 = g_54;
  }
  return l_57[0];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_2[i][j];
    }
  }
  csmith_sink_ = g_15.f0;
  for (i = 0; i < 1; i++) {
  }
  csmith_sink_ = g_19;
  csmith_sink_ = g_37;
  csmith_sink_ = g_38;
  csmith_sink_ = g_46;
  csmith_sink_ = g_55.f0;
  csmith_sink_ = g_55.f1;
  csmith_sink_ = g_59.f0;
  csmith_sink_ = g_59.f1;
  csmith_sink_ = g_69;
  csmith_sink_ = g_74;
  platform_main_end(0, 0);
  return 0;
}
