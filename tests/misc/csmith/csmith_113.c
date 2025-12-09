// Options:   --seed 200113 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_113.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static uint32_t g_10 = 0x97F0A290L;
static uint16_t g_14 = 65532UL;
static int32_t g_22[2] = {0x7D72B90FL, 0x7D72B90FL};
static int32_t *volatile g_21[4][3] = {{&g_22[0], &g_22[0], &g_22[0]},
                                       {&g_22[0], &g_22[0], &g_22[0]},
                                       {&g_22[0], &g_22[0], &g_22[0]},
                                       {&g_22[0], &g_22[0], &g_22[0]}};
static int32_t *volatile g_23[3] = {&g_22[0], &g_22[0], &g_22[0]};

static int32_t func_1(void);
static const uint16_t func_4(int32_t p_5, int64_t p_6, uint8_t p_7, int8_t p_8,
                             int32_t p_9);

static int32_t func_1(void) {
  uint16_t *l_13 = &g_14;
  int32_t l_15[1][4] = {{0x3E95AAD8L, 0x3E95AAD8L, 0x3E95AAD8L, 0x3E95AAD8L}};
  uint32_t l_16 = 0xF3617394L;
  uint64_t l_17 = 0UL;
  int32_t *l_24 = (void *)0;
  int32_t l_25[4][4];
  int i, j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      l_25[i][j] = 0xC9105FA2L;
  }
  l_25[3][0] &= (safe_mod_func_uint16_t_u_u(
      func_4(g_10, (safe_rshift_func_uint16_t_u_u(1UL, ((*l_13) = 65530UL))),
             l_15[0][3], l_16, l_17),
      l_15[0][3]));
  for (l_17 = 0; (l_17 <= 49); l_17 = safe_add_func_int16_t_s_s(l_17, 5)) {
    int32_t **l_28 = &l_24;
    (*l_28) = &g_22[0];
  }
  return l_15[0][3];
}

static const uint16_t func_4(int32_t p_5, int64_t p_6, uint8_t p_7, int8_t p_8,
                             int32_t p_9) {
  uint16_t **l_18 = (void *)0;
  uint16_t ***l_19 = &l_18;
  const int32_t l_20[3] = {0xA5202749L, 0xA5202749L, 0xA5202749L};
  int i;
  (*l_19) = l_18;
  return l_20[2];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_10;
  csmith_sink_ = g_14;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_22[i];
  }
  platform_main_end(0, 0);
  return 0;
}
