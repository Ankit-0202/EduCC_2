// Options:   --seed 100066 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_066.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_3 = 0x0AD6F2EEL;
static uint32_t g_5 = 6UL;

static const int32_t func_1(void);

static const int32_t func_1(void) {
  int32_t *l_2 = &g_3;
  int32_t *l_4 = &g_3;
  g_5--;
  (*l_2) = 0xC3AD3B31L;
  return (*l_2);
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
