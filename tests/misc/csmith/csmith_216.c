// Options:   --seed 300216 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_216.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U1 {
  volatile uint32_t f0;
};

static int32_t g_4 = (-1L);
static union U1 g_5 = {0xFA5C62E0L};

static union U1 func_1(void);

static union U1 func_1(void) {
  int8_t l_2[1];
  int32_t *l_3 = &g_4;
  int i;
  for (i = 0; i < 1; i++)
    l_2[i] = 8L;
  (*l_3) &= l_2[0];
  return g_5;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_4;
  csmith_sink_ = g_5.f0;
  platform_main_end(0, 0);
  return 0;
}
