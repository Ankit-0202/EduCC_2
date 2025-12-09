// Options:   --seed 300253 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_253.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_4 = (-1L);
static int64_t g_11[1] = {5L};
static int32_t g_12[3][3] = {{0x7F7B6FE6L, 0x7F7B6FE6L, 0x7F7B6FE6L},
                             {0x7F7B6FE6L, 0x7F7B6FE6L, 0x7F7B6FE6L},
                             {0x7F7B6FE6L, 0x7F7B6FE6L, 0x7F7B6FE6L}};
static uint32_t g_13[2] = {9UL, 9UL};

static int8_t func_1(void);

static int8_t func_1(void) {
  int32_t *l_3 = &g_4;
  int32_t **l_2 = &l_3;
  int32_t l_5[3][3] = {{0x6E871D97L, 0x6E871D97L, 0x6E871D97L},
                       {0L, 0L, 0L},
                       {0x6E871D97L, 0x6E871D97L, 0x6E871D97L}};
  int32_t *l_6 = (void *)0;
  int32_t *l_7 = &l_5[0][0];
  int32_t *l_8 = &l_5[0][1];
  int32_t *l_9 = &l_5[0][1];
  int32_t *l_10[3];
  uint8_t l_16 = 7UL;
  int i, j;
  for (i = 0; i < 3; i++)
    l_10[i] = &l_5[0][1];
  (*l_2) = (void *)0;
  g_13[1]--;
  return l_16;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_4;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_11[i];
  }
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_12[i][j];
    }
  }
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_13[i];
  }
  platform_main_end(0, 0);
  return 0;
}
