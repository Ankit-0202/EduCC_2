// Options:   --seed 100098 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_098.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int8_t g_5 = (-5L);

static int8_t func_1(void);

static int8_t func_1(void) {
  int8_t *l_4[3];
  int8_t **l_3 = &l_4[1];
  int8_t ***l_2 = &l_3;
  int32_t l_6 = 0x58A835A2L;
  int i;
  for (i = 0; i < 3; i++)
    l_4[i] = &g_5;
  (*l_2) = (void *)0;
  return l_6;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_5;
  platform_main_end(0, 0);
  return 0;
}
