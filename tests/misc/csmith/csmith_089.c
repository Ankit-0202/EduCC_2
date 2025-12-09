// Options:   --seed 100089 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_089.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S1 {
  volatile int64_t f0;
};

static volatile struct S1 g_2 = {0x925B0E446DF37D45LL};
static volatile struct S1 *volatile g_3[2][3] = {{&g_2, &g_2, &g_2},
                                                 {&g_2, &g_2, &g_2}};

static uint32_t func_1(void);

static uint32_t func_1(void) {
  volatile struct S1 *l_4 = &g_2;
  int32_t l_5 = (-5L);
  (*l_4) = g_2;
  return l_5;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2.f0;
  platform_main_end(0, 0);
  return 0;
}
