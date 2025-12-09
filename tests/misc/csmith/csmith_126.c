// Options:   --seed 200126 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_126.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_7 = 0L;
static int32_t g_8[4][4] = {
    {0x9EA98311L, 0x9EA98311L, 0x9EA98311L, 0x9EA98311L},
    {0x9EA98311L, 0x9EA98311L, 0x9EA98311L, 0x9EA98311L},
    {0x9EA98311L, 0x9EA98311L, 0x9EA98311L, 0x9EA98311L},
    {0x9EA98311L, 0x9EA98311L, 0x9EA98311L, 0x9EA98311L}};
static int32_t g_12 = 5L;

static uint32_t func_1(void);

static uint32_t func_1(void) {
  uint64_t l_2 = 1UL;
  l_2--;
  for (l_2 = 18; (l_2 <= 18); l_2 = safe_add_func_uint32_t_u_u(l_2, 4)) {
    uint32_t l_17 = 5UL;
    for (g_8[2][3] = 0; (g_8[2][3] <= (-21)); g_8[2][3]--) {
      int32_t *l_11 = &g_12;
      int32_t *l_13 = &g_12;
      int32_t *l_14 = &g_12;
      int32_t *l_15 = &g_12;
      int32_t *l_16[4][3] = {{&g_12, &g_12, &g_8[2][3]},
                             {&g_12, &g_12, &g_8[2][3]},
                             {&g_12, &g_12, &g_8[2][3]},
                             {&g_12, &g_12, &g_8[2][3]}};
      int i, j;
      ++l_17;
    }
  }
  return l_2;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_7;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_8[i][j];
    }
  }
  csmith_sink_ = g_12;
  platform_main_end(0, 0);
  return 0;
}
