// Options:   --seed 200117 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_117.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_3 = 0L;
static float g_7 = (-0x8.8p-1);
static volatile int64_t g_11 = 3L;
static volatile int8_t g_12 = 0xD3L;
static int16_t g_13[4][3] = {{0x8722L, (-3L), 0x8722L},
                             {8L, 0xB16AL, 8L},
                             {0x8722L, (-3L), 0x8722L},
                             {8L, 0xB16AL, 8L}};
static volatile int8_t g_14 = (-7L);
static volatile uint16_t g_15 = 0UL;

static uint16_t func_1(void);

static uint16_t func_1(void) {
  int32_t *l_2 = &g_3;
  int32_t l_4 = 9L;
  int32_t l_5[3];
  int32_t *l_6 = (void *)0;
  int32_t *l_8 = (void *)0;
  int32_t *l_9[4][1];
  int64_t l_10 = 0x8B9DBEA5223FA3A9LL;
  int i, j;
  for (i = 0; i < 3; i++)
    l_5[i] = 0x1ACCBAD8L;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 1; j++)
      l_9[i][j] = &g_3;
  }
  --g_15;
  return (*l_2);
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  csmith_sink_ = g_7;
  csmith_sink_ = g_11;
  csmith_sink_ = g_12;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_13[i][j];
    }
  }
  csmith_sink_ = g_14;
  csmith_sink_ = g_15;
  platform_main_end(0, 0);
  return 0;
}
