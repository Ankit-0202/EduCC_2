// Options:   --seed 100017 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_017.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_3[3][2] = {
    {(-5L), 0x95E17CA0L}, {0x95E17CA0L, (-5L)}, {0x95E17CA0L, 0x95E17CA0L}};
static volatile int32_t g_4[3] = {0x90BE4438L, 0x90BE4438L, 0x90BE4438L};

static uint64_t func_1(void);

static uint64_t func_1(void) {
  int8_t l_2[3][2] = {{(-1L), (-1L)}, {(-1L), (-1L)}, {(-1L), (-1L)}};
  int i, j;
  for (g_3[0][1] = 0; g_3[0][1] < 3; g_3[0][1] += 1) {
    for (g_4[1] = 0; g_4[1] < 2; g_4[1] += 1) {
      l_2[g_3[0][1]][g_4[1]] = 0x09L;
    }
  }
  return l_2[2][1];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 2; j++) {
      csmith_sink_ = g_3[i][j];
    }
  }
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_4[i];
  }
  platform_main_end(0, 0);
  return 0;
}
