// Options:   --seed 100008 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_008.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U0 {
  int8_t f0;
};

static int32_t g_4[1] = {(-1L)};
static int32_t *volatile g_3[2] = {&g_4[0], &g_4[0]};
static union U0 g_5 = {0x1DL};

static union U0 func_1(void);

static union U0 func_1(void) {
  int32_t l_2 = 1L;
  l_2 = l_2;
  return g_5;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_4[i];
  }
  csmith_sink_ = g_5.f0;
  platform_main_end(0, 0);
  return 0;
}
