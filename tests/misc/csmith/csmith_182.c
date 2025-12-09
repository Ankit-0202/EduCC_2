// Options:   --seed 200182 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_182.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_3 = 0x901F2C29L;
static volatile int32_t *g_2 = &g_3;
static int32_t g_6 = (-6L);
static int32_t g_7 = 0xFB37B048L;
static volatile int64_t g_8 = 0x091DF82D83D78398LL;
static uint32_t g_9[4][2] = {{0UL, 0UL}, {0UL, 0UL}, {0UL, 0UL}, {0UL, 0UL}};

static int32_t func_1(void);

static int32_t func_1(void) {
  volatile int32_t **l_4 = &g_2;
  int32_t *l_5[2];
  int i;
  for (i = 0; i < 2; i++)
    l_5[i] = &g_6;
  (*l_4) = g_2;
  --g_9[2][1];
  return g_7;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  csmith_sink_ = g_6;
  csmith_sink_ = g_7;
  csmith_sink_ = g_8;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_9[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
