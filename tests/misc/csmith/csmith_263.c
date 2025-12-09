// Options:   --seed 300263 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_263.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_3[2][1] = {{5L}, {5L}};
static uint32_t g_14 = 0x71639956L;

static uint64_t func_1(void);

static uint64_t func_1(void) {
  int32_t *l_2 = &g_3[0][0];
  int32_t *l_4 = (void *)0;
  int32_t *l_5 = &g_3[1][0];
  int32_t *l_6 = &g_3[1][0];
  int32_t *l_7 = &g_3[0][0];
  int32_t *l_8 = (void *)0;
  int32_t *l_9 = &g_3[0][0];
  int32_t l_10 = 0x434678DCL;
  int32_t *l_11 = &g_3[0][0];
  int32_t l_12 = 2L;
  int32_t *l_13[1][1];
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++)
      l_13[i][j] = &l_12;
  }
  g_14++;
  return g_3[1][0];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_3[i][j];
    }
  }
  csmith_sink_ = g_14;
  platform_main_end(0, 0);
  return 0;
}
