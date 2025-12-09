// Options:   --seed 200178 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_178.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_2 = 0L;
static int32_t g_3 = 0L;
static int32_t g_6 = 0x772304B2L;
static int32_t g_10[2][3] = {{1L, 0x2A727599L, 1L}, {1L, 0x2A727599L, 1L}};
static int32_t g_30 = 0x758B39D2L;
static uint16_t g_32 = 0UL;
static int16_t g_39 = (-8L);
static uint64_t g_41[4][2] = {{0xAACC702B5BDDDD5DLL, 0xAACC702B5BDDDD5DLL},
                              {0xAACC702B5BDDDD5DLL, 0xAACC702B5BDDDD5DLL},
                              {0xAACC702B5BDDDD5DLL, 0xAACC702B5BDDDD5DLL},
                              {0xAACC702B5BDDDD5DLL, 0xAACC702B5BDDDD5DLL}};
static int32_t g_42[2][3] = {{0xE31B5465L, 0xE31B5465L, 0xE31B5465L},
                             {0xE31B5465L, 0xE31B5465L, 0xE31B5465L}};
static uint8_t g_49 = 0xF4L;
static uint8_t *g_48 = &g_49;

static uint32_t func_1(void);
static const int32_t *func_14(int32_t *p_15, int32_t *p_16);

static uint32_t func_1(void) {
  int32_t *l_17[1][1];
  uint8_t *l_51 = &g_49;
  uint32_t l_57 = 0xEC63F78CL;
  int16_t l_58 = 0L;
  int8_t l_59 = (-1L);
  uint8_t l_60 = 0x56L;
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++)
      l_17[i][j] = (void *)0;
  }
  for (g_3 = 0; (g_3 == (-14)); g_3 = safe_sub_func_uint16_t_u_u(g_3, 5)) {
    uint8_t l_11 = 255UL;
    const float l_37 = 0x3.E8EA47p-21;
    int16_t *l_38 = &g_39;
    uint8_t *l_40[3][1];
    int32_t l_43 = 0L;
    int i, j;
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 1; j++)
        l_40[i][j] = &l_11;
    }
    for (g_6 = 0; (g_6 != 1); g_6++) {
      int32_t *l_9[4] = {&g_10[0][2], &g_10[0][2], &g_10[0][2], &g_10[0][2]};
      const int32_t *l_36 = &g_3;
      const int32_t **l_35 = &l_36;
      int i;
      l_11--;
      (*l_35) = func_14(&g_3, l_17[0][0]);
    }
    if ((((g_10[0][2] &
           (g_3 <
            (l_43 = (g_6 = (((g_42[1][2] =
                                  (g_41[2][1] = (((*l_38) = (g_32, l_11)),
                                                 0UL))) <= g_3) != 0xDB47L))))),
          &g_10[1][1]) == &g_10[0][1])) {
      return l_43;
    } else {
      uint8_t **l_50[3];
      int32_t l_56 = 0x88C8ECA7L;
      int i;
      for (i = 0; i < 3; i++)
        l_50[i] = &l_40[0][0];
      g_2 ^=
          (((safe_rshift_func_int16_t_s_u(
                (safe_lshift_func_uint16_t_u_s(
                    ((l_51 = g_48) ==
                     ((safe_add_func_int8_t_s_s(
                          l_43, (((safe_sub_func_uint16_t_u_u(
                                      (g_32 &= ((((((l_56 <= g_6), 0xDE216D72L),
                                                   (void *)0) == l_38),
                                                 &g_32) == &g_32)),
                                      l_57)) <= (*g_48)) >= l_58))),
                      &l_11)),
                    l_11)),
                l_11)),
            g_10[1][0]) ^
           l_11);
      l_59 = (l_56 = 1L);
    }
  }
  --l_60;
  return g_42[1][2];
}

static const int32_t *func_14(int32_t *p_15, int32_t *p_16) {
  const float l_26 = 0x0.6p-1;
  int32_t l_27[3][2];
  uint16_t *l_31 = &g_32;
  int i, j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++)
      l_27[i][j] = 0x3C86992FL;
  }
  g_10[1][0] =
      (((*l_31) = (safe_mul_func_int16_t_s_s(
            g_10[1][0], ((safe_add_func_uint8_t_u_u(
                             ((safe_mul_func_int16_t_s_s(
                                  (safe_div_func_int64_t_s_s(
                                      l_27[2][0], (safe_mod_func_int32_t_s_s(
                                                      (g_30 & g_6), g_3)))),
                                  l_27[2][0])) < l_27[1][0]),
                             0xD1L)),
                         l_27[2][0])))) ^
       9UL);
  g_2 &= (g_10[0][2] != (safe_rshift_func_int8_t_s_u(0x24L, 0)));
  return p_16;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_3;
  csmith_sink_ = g_6;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_10[i][j];
    }
  }
  csmith_sink_ = g_30;
  csmith_sink_ = g_32;
  csmith_sink_ = g_39;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_41[i][j];
    }
  }
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_42[i][j];
    }
  }
  csmith_sink_ = g_49;
  platform_main_end(0, 0);
  return 0;
}
