// Options:   --seed 200156 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_156.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_2 = 0xE91A049FL;
static int32_t g_3[2] = {0x7FB0B029L, 0x7FB0B029L};
static uint16_t g_7[4] = {0x0997L, 0x0997L, 0x0997L, 0x0997L};
static uint16_t g_9[4][4] = {{0x91B6L, 0x5CC2L, 0x7642L, 0x5CC2L},
                             {0x5CC2L, 0x6038L, 0x7642L, 0x7642L},
                             {0x91B6L, 0x91B6L, 0x5CC2L, 0x7642L},
                             {0x8EB9L, 0x6038L, 0x8EB9L, 0x5CC2L}};
static int32_t *g_11 = &g_3[1];
static int32_t **volatile g_10 = &g_11;

static uint32_t func_1(void);

static uint32_t func_1(void) {
  uint16_t *l_8 = &g_9[0][1];
  int32_t l_12[2][1];
  int i, j;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 1; j++)
      l_12[i][j] = 0x7F1A969AL;
  }
  for (g_3[1] = 6; (g_3[1] >= (-12)); g_3[1]--) {
    uint16_t *l_6 = &g_7[2];
    if (((((*l_6) = 0x80C1L), (-4L)) != ((void *)0 == l_8))) {
      g_2 ^= g_9[2][0];
    } else {
      (*g_10) = &g_3[1];
    }
    if (l_12[1][0])
      continue;
  }
  return l_12[1][0];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_3[i];
  }
  for (i = 0; i < 4; i++) {
    csmith_sink_ = g_7[i];
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_9[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
