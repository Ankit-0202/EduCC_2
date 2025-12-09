// Options:   --seed 100018 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_018.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  uint16_t f0;
};

static int32_t g_5 = 0x72759951L;

static uint16_t func_1(void);

static uint16_t func_1(void) {
  uint16_t l_2 = 2UL;
  struct S0 l_6 = {0UL};
  if (l_2) {
    int16_t l_3 = (-6L);
    int32_t *l_4 = &g_5;
    (*l_4) |= (l_3 <= 0xFF82FF40L);
  } else {
    struct S0 *l_7 = &l_6;
    (*l_7) = l_6;
  }
  return g_5;
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
