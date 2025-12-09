// Options:   --seed 100021 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_021.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_2[3][3] = {{8L, 8L, 8L}, {8L, 8L, 8L}, {8L, 8L, 8L}};
static int32_t g_8 = 7L;

static uint16_t func_1(void);

static uint16_t func_1(void) {
  int32_t *l_10[1];
  int i;
  for (i = 0; i < 1; i++)
    l_10[i] = &g_8;
  for (g_2[2][1] = 0; (g_2[2][1] < 17); ++g_2[2][1]) {
    int32_t *l_5 = (void *)0;
    int32_t *l_6 = (void *)0;
    int32_t *l_7 = &g_8;
    if (g_2[2][1])
      break;
    (*l_7) |= (-8L);
  }
  g_2[1][1] = (!g_2[0][1]);
  return g_2[0][0];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_2[i][j];
    }
  }
  csmith_sink_ = g_8;
  platform_main_end(0, 0);
  return 0;
}
