// Options:   --seed 200120 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_120.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  uint16_t f0;
};

struct S1 {
  volatile int16_t f0;
  const uint32_t f1;
  volatile int8_t f2;
};

static uint16_t g_9[3][1] = {{65527UL}, {65527UL}, {65527UL}};
static int32_t g_13 = 0xB4C8F0D0L;
static int32_t g_21 = 0L;
static volatile int32_t g_22 = (-5L);
static volatile int32_t g_23 = 9L;
static uint64_t g_24 = 0x6B5CFDA6C2E3A4C6LL;
static struct S1 g_28 = {0xA14AL, 0xC79EBEF9L, 0x3BL};
static int32_t g_31[4] = {(-1L), (-1L), (-1L), (-1L)};
static float g_33 = 0x7.E4DDBBp+32;
static float *volatile g_32 = &g_33;
static struct S0 g_34[2] = {{0x255BL}, {0x255BL}};

static struct S0 func_1(void);
static int64_t func_4(int16_t p_5, int16_t p_6, struct S0 p_7, uint16_t p_8);

static struct S0 func_1(void) {
  int32_t l_10 = 1L;
  struct S0 l_11 = {0UL};
  float *l_30 = (void *)0;
  (*g_32) =
      (((safe_div_func_float_f_f(
            0x6.2E0897p-76,
            (g_31[3] = (func_4(g_9[2][0], l_10, l_11, g_9[2][0]), l_11.f0)))) <
        0x0.Cp-1) < g_9[2][0]);
  return g_34[0];
}

static int64_t func_4(int16_t p_5, int16_t p_6, struct S0 p_7, uint16_t p_8) {
  int32_t *l_12 = &g_13;
  int32_t *l_14 = &g_13;
  int32_t l_15 = (-1L);
  int32_t *l_16 = &g_13;
  int32_t l_17 = (-1L);
  int32_t *l_18 = &g_13;
  int32_t l_19 = 0x3AAF5BFBL;
  int32_t *l_20[1];
  struct S1 *l_27[4];
  struct S1 **l_29 = &l_27[2];
  int i;
  for (i = 0; i < 1; i++)
    l_20[i] = &l_19;
  for (i = 0; i < 4; i++)
    l_27[i] = &g_28;
  g_24--;
  (*l_29) = l_27[2];
  return g_23;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_9[i][j];
    }
  }
  csmith_sink_ = g_13;
  csmith_sink_ = g_21;
  csmith_sink_ = g_22;
  csmith_sink_ = g_23;
  csmith_sink_ = g_24;
  csmith_sink_ = g_28.f0;
  csmith_sink_ = g_28.f1;
  csmith_sink_ = g_28.f2;
  for (i = 0; i < 4; i++) {
    csmith_sink_ = g_31[i];
  }
  csmith_sink_ = g_33;
  for (i = 0; i < 2; i++) {
  }
  platform_main_end(0, 0);
  return 0;
}
