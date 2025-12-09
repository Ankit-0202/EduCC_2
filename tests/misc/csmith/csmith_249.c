// Options:   --seed 300249 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_249.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  int8_t f0;
  volatile int32_t f1;
};

static int32_t g_3 = 0xDB34E6D4L;
static volatile int32_t g_4 = (-8L);
static volatile int32_t g_5 = (-1L);
static volatile int32_t g_6 = (-10L);
static volatile int32_t g_7 = 0x5FAAFE30L;
static volatile int32_t g_8 = (-4L);
static int32_t g_9 = (-1L);
static union U0 g_13[3] = {{0L}, {0L}, {0L}};

static union U0 func_1(void);

static union U0 func_1(void) {
  int8_t l_2[2];
  int i;
  for (i = 0; i < 2; i++)
    l_2[i] = 1L;
  for (g_3 = 1; (g_3 >= 0); g_3 -= 1) {
    uint16_t l_12[2][1];
    int i, j;
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 1; j++)
        l_12[i][j] = 65535UL;
    }
    for (g_9 = 1; (g_9 >= 0); g_9 -= 1) {
      int32_t *l_10 = &g_9;
      int32_t **l_11 = &l_10;
      (*l_11) = l_10;
      if (l_12[1][0])
        continue;
    }
  }
  for (g_5 = 0; g_5 < 2; g_5 += 1) {
    l_2[g_5] = 0x46L;
  }
  return g_13[2];
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  csmith_sink_ = g_4;
  csmith_sink_ = g_5;
  csmith_sink_ = g_6;
  csmith_sink_ = g_7;
  csmith_sink_ = g_8;
  csmith_sink_ = g_9;
  for (i = 0; i < 3; i++) {
  }
  platform_main_end(0, 0);
  return 0;
}
