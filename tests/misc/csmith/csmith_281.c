// Options:   --seed 300281 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_281.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  int16_t f0;
  volatile uint64_t f1;
  uint64_t f2;
};

union U3 {
  uint8_t f0;
};

static uint16_t g_17 = 65535UL;
static int32_t g_26 = (-9L);
static int32_t g_28 = 0xE623B470L;
static uint16_t g_30 = 0xA7F4L;
static uint16_t g_31 = 0x30C4L;
static int16_t g_43 = (-6L);
static uint64_t g_52[2][3] = {
    {0x3EB999C826FFEA1ELL, 0x3EB999C826FFEA1ELL, 0x3EB999C826FFEA1ELL},
    {0x26AAF09D89C1C50DLL, 0x26AAF09D89C1C50DLL, 0x26AAF09D89C1C50DLL}};
static int32_t *volatile g_54 = &g_26;
static struct S0 g_56 = {-1L, 18446744073709551613UL, 0x6A9523668F781BE2LL};
static struct S0 *g_55[1][1] = {{&g_56}};
static struct S0 **volatile g_57 = &g_55[0][0];
static union U3 g_59 = {0xDBL};
static union U3 *volatile g_58 = &g_59;
static const union U3 *g_71 = (void *)0;
static const union U3 **g_70 = &g_71;
static const union U3 **g_74 = &g_71;

static const union U3 func_1(void);
static uint16_t func_10(uint16_t p_11, union U3 p_12, int32_t p_13,
                        uint8_t p_14);
static uint16_t func_15(int8_t p_16);

static const union U3 func_1(void) {
  union U3 l_29 = {3UL};
  int32_t l_50 = 0L;
  int32_t l_53 = 0x05F67326L;
  const int32_t *l_61 = &g_28;
  const union U3 **l_73 = &g_71;
  const union U3 ***l_72[2][1];
  const union U3 l_75 = {1UL};
  int i, j;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 1; j++)
      l_72[i][j] = &l_73;
  }
  if ((0x7CF2E566L > (safe_add_func_int64_t_s_s(
                         (safe_add_func_uint32_t_u_u(
                             9UL, (safe_lshift_func_int16_t_s_s(
                                      (safe_lshift_func_int16_t_s_u(
                                          (((func_10(func_15(g_17), l_29, g_30,
                                                     g_31) <= 7L) < l_29.f0) ^
                                           g_31),
                                          g_31)),
                                      g_30)))),
                         g_31)))) {
    uint32_t l_41[2][2];
    int16_t *l_42 = &g_43;
    uint64_t l_44[2][1];
    int i, j;
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 2; j++)
        l_41[i][j] = 0x4F69A750L;
    }
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 1; j++)
        l_44[i][j] = 0xA1D127A4EF21DDBCLL;
    }
    if ((((((*l_42) = (safe_div_func_uint16_t_u_u(
                (((safe_rshift_func_int8_t_s_u(
                      ((((((void *)0 == &g_28) ^
                          (safe_rshift_func_int16_t_s_u(
                              (safe_sub_func_uint8_t_u_u(g_17, 0x04L)),
                              g_17))) >= l_29.f0),
                        l_41[0][0]) > 0x33631AF6L),
                      5)) &&
                  l_41[1][1]) ^
                 0xDBC4L),
                g_28))) ||
           g_26) == g_28) ||
         l_44[0][0])) {
      uint8_t *l_49[1];
      int16_t *l_51[3];
      int i;
      for (i = 0; i < 1; i++)
        l_49[i] = &l_29.f0;
      for (i = 0; i < 3; i++)
        l_51[i] = (void *)0;
      (*g_54) ^=
          ((l_53 = (safe_div_func_int32_t_s_s(
                ((safe_add_func_uint8_t_u_u(
                     (l_50 = 0x4FL), (g_52[1][2] &= (l_51[2] == (void *)0)))) ^
                 0x231A2955L),
                0x164C1161L))),
           g_31);
      (*g_57) = g_55[0][0];
    } else {
      union U3 *volatile *l_60 = &g_58;
      const int32_t **l_62 = &l_61;
      (*l_60) = g_58;
      (*l_62) = l_61;
    }
  } else {
    uint32_t l_66[3][1];
    int i, j;
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 1; j++)
        l_66[i][j] = 1UL;
    }
    for (g_43 = 0; (g_43 >= 0); g_43 -= 1) {
      int32_t *l_63 = (void *)0;
      int32_t *l_64 = (void *)0;
      int32_t *l_65[3][2] = {{&l_53, &l_53}, {&l_53, &l_53}, {&l_53, &l_53}};
      int32_t **l_69 = &l_64;
      int i, j;
      --l_66[2][0];
      (*l_69) = &g_26;
    }
  }
  g_74 = (g_70 = g_70);
  return l_75;
}

static uint16_t func_10(uint16_t p_11, union U3 p_12, int32_t p_13,
                        uint8_t p_14) {
  uint32_t l_32 = 8UL;
  return l_32;
}

static uint16_t func_15(int8_t p_16) {
  for (g_17 = 0; (g_17 <= 58); g_17++) {
    int16_t l_20 = 0L;
    int32_t *l_25 = &g_26;
    int32_t *l_27 = &g_28;
    if (l_20)
      break;
    (*l_27) = ((*l_25) ^= (safe_lshift_func_uint16_t_u_s(
                   (safe_rshift_func_int8_t_s_s(p_16, 1)), 0)));
  }
  return g_26;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_17;
  csmith_sink_ = g_26;
  csmith_sink_ = g_28;
  csmith_sink_ = g_30;
  csmith_sink_ = g_31;
  csmith_sink_ = g_43;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_52[i][j];
    }
  }
  csmith_sink_ = g_56.f0;
  csmith_sink_ = g_56.f1;
  csmith_sink_ = g_56.f2;
  csmith_sink_ = g_59.f0;
  platform_main_end(0, 0);
  return 0;
}
