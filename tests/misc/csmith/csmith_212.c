// Options:   --seed 300212 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_212.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_4 = 0xE97EEDE0L;
static int32_t g_6 = 0x8C66F5A9L;
static int32_t *volatile g_5 = &g_6;

static int8_t func_1(void);

static int8_t func_1(void) {
  uint64_t l_2[1];
  int32_t *l_3 = &g_4;
  int i;
  for (i = 0; i < 1; i++)
    l_2[i] = 18446744073709551615UL;
  (*g_5) = ((*l_3) |= l_2[0]);
  return (*l_3);
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_4;
  csmith_sink_ = g_6;
  platform_main_end(0, 0);
  return 0;
}
