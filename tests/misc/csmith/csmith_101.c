// Options:   --seed 200101 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_101.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_2 = 0xC64A6847L;
static volatile int32_t g_3[4][1] = {{(-8L)}, {1L}, {(-8L)}, {1L}};
static volatile int32_t g_4 = 0xF0B96CA2L;
static volatile int32_t g_5 = 7L;
static volatile int32_t g_6 = (-9L);
static int32_t g_7 = 0x43250E6DL;
static int32_t g_10[4][2] = {
    {(-1L), (-1L)}, {(-1L), (-1L)}, {(-1L), (-1L)}, {(-1L), (-1L)}};

static uint32_t func_1(void);

static uint32_t func_1(void) {
  int8_t l_13 = 0x95L;
lbl_14:
  for (g_7 = 0; (g_7 == (-29)); --g_7) {
    for (g_10[0][1] = 11; (g_10[0][1] <= 24); g_10[0][1]++) {
      return l_13;
    }
    if (g_7)
      goto lbl_14;
    for (l_13 = 0; (l_13 <= 1); l_13 += 1) {
      int i, j;
      return g_10[l_13][l_13];
    }
  }
  return g_10[3][1];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_3[i][j];
    }
  }
  csmith_sink_ = g_4;
  csmith_sink_ = g_5;
  csmith_sink_ = g_6;
  csmith_sink_ = g_7;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_10[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
