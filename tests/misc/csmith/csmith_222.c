// Options:   --seed 300222 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_222.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_4 = 0x13A473EBL;

static uint32_t func_1(void);

static uint32_t func_1(void) {
  int32_t *l_3[3][3] = {{&g_4, &g_4, &g_4},
                        {(void *)0, (void *)0, (void *)0},
                        {&g_4, &g_4, &g_4}};
  int32_t **l_2 = &l_3[1][1];
  int i, j;
  (*l_2) = (void *)0;
  return g_4;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_4;
  platform_main_end(0, 0);
  return 0;
}
