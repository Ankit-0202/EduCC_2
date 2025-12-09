// Options:   --seed 100067 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_067.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_3[3][1] = {{0xF1FEBAEEL}, {0xF1FEBAEEL}, {0xF1FEBAEEL}};

static int8_t func_1(void);

static int8_t func_1(void) {
  int32_t *l_2 = &g_3[2][0];
  int32_t *l_4 = &g_3[2][0];
  int32_t *l_5 = (void *)0;
  int32_t *l_6 = &g_3[2][0];
  int32_t *l_7 = &g_3[1][0];
  int32_t *l_8 = &g_3[2][0];
  int32_t *l_9 = &g_3[2][0];
  int32_t *l_10 = &g_3[0][0];
  int32_t *l_11 = &g_3[2][0];
  int32_t *l_12 = &g_3[2][0];
  int32_t *l_13 = &g_3[2][0];
  int32_t *l_14 = &g_3[2][0];
  int32_t *l_15 = &g_3[2][0];
  int32_t *l_16 = &g_3[2][0];
  int32_t *l_17 = &g_3[2][0];
  int32_t *l_18 = &g_3[2][0];
  int32_t *l_19 = (void *)0;
  int32_t *l_20 = &g_3[2][0];
  int32_t *l_21 = &g_3[2][0];
  int32_t *l_22[3];
  int64_t l_23[1];
  int32_t l_24 = 0x72DBE421L;
  int32_t l_25[2][3];
  int32_t l_26 = 7L;
  int32_t l_27 = 0x2AC5EDFBL;
  uint32_t l_28 = 1UL;
  int i, j;
  for (i = 0; i < 3; i++)
    l_22[i] = &g_3[2][0];
  for (i = 0; i < 1; i++)
    l_23[i] = 1L;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 3; j++)
      l_25[i][j] = 0L;
  }
  l_28++;
  for (l_24 = 9; (l_24 <= 24); l_24 = safe_add_func_int64_t_s_s(l_24, 9)) {
    for (l_28 = 0; (l_28 <= 1); l_28 += 1) {
      return g_3[2][0];
    }
  }
  return g_3[2][0];
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
      csmith_sink_ = g_3[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
