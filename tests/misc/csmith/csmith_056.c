// Options:   --seed 100056 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_056.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static const int32_t g_3 = 0x20398070L;
static const int32_t g_5 = 1L;
static const int32_t *g_4 = &g_5;

static uint32_t func_1(void);

static uint32_t func_1(void) {
  const int32_t *l_2 = &g_3;
  g_4 = l_2;
  return g_3;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  csmith_sink_ = g_5;
  platform_main_end(0, 0);
  return 0;
}
