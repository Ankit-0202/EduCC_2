// Options:   --seed 200124 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_124.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U1 {
  int8_t f0;
};

static union U1 g_7[1][4] = {{{-1L}, {-1L}, {-1L}, {-1L}}};
static int32_t g_11 = 1L;
static uint8_t g_12 = 9UL;

static float func_1(void);

static float func_1(void) {
  union U1 **l_2 = (void *)0;
  union U1 **l_3 = (void *)0;
  union U1 **l_4 = (void *)0;
  union U1 **l_5 = (void *)0;
  union U1 *l_6[3][3] = {{&g_7[0][2], &g_7[0][2], &g_7[0][2]},
                         {&g_7[0][2], &g_7[0][2], &g_7[0][2]},
                         {&g_7[0][2], &g_7[0][2], &g_7[0][2]}};
  int32_t *l_8 = (void *)0;
  int32_t *l_9 = (void *)0;
  int32_t *l_10[3];
  int i, j;
  for (i = 0; i < 3; i++)
    l_10[i] = &g_11;
  l_6[2][0] = (void *)0;
  ++g_12;
  return g_12;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 4; j++) {
    }
  }
  csmith_sink_ = g_11;
  csmith_sink_ = g_12;
  platform_main_end(0, 0);
  return 0;
}
