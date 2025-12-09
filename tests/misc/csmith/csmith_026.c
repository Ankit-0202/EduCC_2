// Options:   --seed 100026 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_026.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_3 = 0L;
static volatile int32_t g_4 = 0xB6748F69L;

static uint32_t func_1(void);

static uint32_t func_1(void) {
  uint32_t l_2[4][1] = {{4UL}, {4294967294UL}, {4UL}, {4294967294UL}};
  int i, j;
  for (g_3 = 0; g_3 < 4; g_3 += 1) {
    for (g_4 = 0; g_4 < 1; g_4 += 1) {
      l_2[g_3][g_4] = 4294967295UL;
    }
  }
  return g_3;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  csmith_sink_ = g_4;
  platform_main_end(0, 0);
  return 0;
}
