// Options:   --seed 200138 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_138.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  const int32_t f0;
  const uint64_t f1;
};

struct S2 {
  uint64_t f0;
  int16_t f1;
};

union U3 {
  uint16_t f0;
};

static volatile struct S2 g_8 = {0x31551DA622A149CELL, 0x79E6L};
static const int32_t g_13 = 8L;
static uint8_t g_14 = 1UL;
static int32_t g_16 = 0xFBCE008FL;
static struct S0 g_23 = {0x58A60016L, 1UL};

static uint16_t func_1(void);
static int32_t func_2(float p_3, const uint16_t p_4, int64_t p_5);

static uint16_t func_1(void) {
  union U3 l_12 = {65535UL};
  int32_t *l_15[1][4];
  int32_t *l_17 = &g_16;
  struct S0 *l_22[4] = {&g_23, &g_23, &g_23, &g_23};
  struct S0 *l_27 = &g_23;
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 4; j++)
      l_15[i][j] = &g_16;
  }
  g_16 &= func_2(
      (g_14 = (((safe_mul_func_uint8_t_u_u(
                    (g_8, (safe_lshift_func_uint16_t_u_u((~(l_12, 1L)), 13))),
                    l_12.f0)) >= g_13),
               l_12.f0)),
      l_12.f0, g_13);
  if ((&g_16 != l_17)) {
    for (g_16 = 0; (g_16 >= 8); g_16 = safe_add_func_uint64_t_u_u(g_16, 4)) {
      if (g_8.f0)
        break;
    }
  } else {
    struct S0 *l_26 = &g_23;
    for (g_16 = 23; (g_16 > 8); g_16--) {
      struct S0 **l_24 = &l_22[0];
      (*l_24) = l_22[1];
    }
    (*l_17) |= ((!(l_26 != l_27)) | (0x0AL ^ g_8.f1));
  }
  return (*l_17);
}

static int32_t func_2(float p_3, const uint16_t p_4, int64_t p_5) {
  return p_5;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_8.f0;
  csmith_sink_ = g_8.f1;
  csmith_sink_ = g_13;
  csmith_sink_ = g_14;
  csmith_sink_ = g_16;
  csmith_sink_ = g_23.f0;
  csmith_sink_ = g_23.f1;
  platform_main_end(0, 0);
  return 0;
}
