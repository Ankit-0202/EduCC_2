// Options:   --seed 200146 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_146.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U2 {
  int16_t f0;
  float f1;
};

static volatile int32_t g_3[4][2] = {
    {(-3L), (-3L)}, {(-3L), (-3L)}, {(-3L), (-3L)}, {(-3L), (-3L)}};
static int32_t g_4 = 7L;
static int32_t g_6 = (-9L);
static union U2 g_8 = {0xD035L};
static union U2 **volatile g_9 = (void *)0;
static int32_t g_13 = 0x2A83A0F0L;
static int32_t g_15[2] = {0xB2C593C8L, 0xB2C593C8L};
static int32_t *volatile g_14 = &g_15[0];

static uint16_t func_1(void);

static uint16_t func_1(void) {
  int8_t l_2[1][1];
  union U2 *l_11 = (void *)0;
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++)
      l_2[i][j] = 1L;
  }
  for (g_4 = 0; (g_4 <= 0); g_4 += 1) {
    int32_t *l_5 = &g_6;
    union U2 *l_7 = &g_8;
    (*l_5) = 0x568BE135L;
    for (g_6 = 0; (g_6 <= 0); g_6 += 1) {
      union U2 **l_10 = (void *)0;
      int i, j;
      l_11 = l_7;
      if (l_2[g_6][g_6])
        continue;
    }
    for (g_6 = 0; (g_6 >= 0); g_6 -= 1) {
      int32_t *l_12 = (void *)0;
      int i, j;
      (*g_14) &= (1UL <= (g_13 |= l_2[g_4][g_4]));
    }
  }
  return g_15[0];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_3[i][j];
    }
  }
  csmith_sink_ = g_4;
  csmith_sink_ = g_6;
  csmith_sink_ = g_8.f0;
  csmith_sink_ = g_13;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_15[i];
  }
  platform_main_end(0, 0);
  return 0;
}
