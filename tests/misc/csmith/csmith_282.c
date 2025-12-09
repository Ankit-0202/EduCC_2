// Options:   --seed 300282 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_282.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_2 = 1L;
static volatile int32_t g_3 = 0xEAA32B1CL;
static volatile int32_t g_4 = 0x457102D1L;
static int32_t g_5 = 1L;
static int32_t *volatile g_27 = &g_5;
static int32_t g_29 = 0xFF609D70L;
static int32_t g_31 = 1L;

static uint16_t func_1(void);
static uint64_t func_11(int32_t p_12, int32_t p_13);
static uint64_t func_19(const uint64_t p_20, int32_t p_21, uint8_t p_22);

static uint16_t func_1(void) {
  uint16_t l_14 = 0x5792L;
  int32_t *l_30 = &g_31;
  for (g_5 = (-16); (g_5 == 21); g_5++) {
    uint32_t l_8 = 0x3843046BL;
    --l_8;
  }
  (*l_30) &= (((func_11(g_5, l_14) <= g_29) <= l_14), (*g_27));
  return g_29;
}

static uint64_t func_11(int32_t p_12, int32_t p_13) {
  const int16_t l_23 = 0x69B2L;
  int32_t *l_28[2];
  int i;
  for (i = 0; i < 2; i++)
    l_28[i] = &g_5;
  (*g_27) = (safe_add_func_uint16_t_u_u(
      (safe_add_func_int64_t_s_s(g_3, func_19(l_23, l_23, g_5))), 0x90FCL));
  l_28[0] = l_28[0];
  return p_13;
}

static uint64_t func_19(const uint64_t p_20, int32_t p_21, uint8_t p_22) {
  int32_t *l_25 = &g_5;
  int32_t **l_24 = &l_25;
  int32_t *l_26[1][3];
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 3; j++)
      l_26[i][j] = (void *)0;
  }
  (*l_24) = &g_5;
  (*l_24) = l_26[0][2];
  return g_5;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_3;
  csmith_sink_ = g_4;
  csmith_sink_ = g_5;
  csmith_sink_ = g_29;
  csmith_sink_ = g_31;
  platform_main_end(0, 0);
  return 0;
}
