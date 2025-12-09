// Options:   --seed 200152 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_152.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int8_t g_10 = 0x1CL;
static int64_t g_12[3][3] = {
    {(-1L), (-1L), (-1L)}, {(-1L), (-1L), (-1L)}, {(-1L), (-1L), (-1L)}};
static uint16_t g_21[4][2] = {{0xA530L, 0xA530L},
                              {0xA530L, 0xA530L},
                              {0xA530L, 0xA530L},
                              {0xA530L, 0xA530L}};
static int16_t g_28[3] = {0xF7B1L, 0xF7B1L, 0xF7B1L};
static int32_t *volatile g_29 = (void *)0;

static const int64_t func_1(void);
static int64_t func_6(int32_t p_7, uint64_t p_8, int64_t p_9);

static const int64_t func_1(void) {
  float l_11 = (-0x4.9p-1);
  int32_t l_16 = (-1L);
  float *l_17 = &l_11;
  (*l_17) = ((safe_mul_func_uint8_t_u_u(
                 (safe_mod_func_int8_t_s_s(
                     (0xC62E08974B666A75LL > func_6(g_10, g_10, g_10)), 0xF5L)),
                 l_16)),
             0x3.9p-1);
  for (g_10 = 0; (g_10 != (-9)); g_10 = safe_sub_func_int16_t_s_s(g_10, 3)) {
    int32_t l_30 = 0xFC75DAA0L;
    if (g_12[1][1]) {
      uint16_t *l_20 = &g_21[0][0];
      int16_t *l_26 = (void *)0;
      int16_t *l_27 = &g_28[1];
      l_16 &=
          ((--(*l_20)) >= ((*l_27) = (safe_add_func_uint16_t_u_u(g_10, g_10))));
    } else {
      if (l_30)
        break;
    }
    if (g_28[2])
      continue;
  }
  return l_16;
}

static int64_t func_6(int32_t p_7, uint64_t p_8, int64_t p_9) {
  uint64_t l_15 = 1UL;
  for (p_8 = 0; (p_8 <= 2); p_8 += 1) {
    int32_t *l_14[4];
    int32_t **l_13 = &l_14[1];
    int i;
    for (i = 0; i < 4; i++)
      l_14[i] = (void *)0;
    (*l_13) = (void *)0;
    if (p_8)
      continue;
    for (p_9 = 2; (p_9 >= 0); p_9 -= 1) {
      int i, j;
      return g_12[p_9][p_8];
    }
  }
  return l_15;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_10;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_12[i][j];
    }
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_21[i][j];
    }
  }
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_28[i];
  }
  platform_main_end(0, 0);
  return 0;
}
