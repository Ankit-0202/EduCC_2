// Options:   --seed 300264 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_264.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  const volatile int8_t f0;
  int32_t f1;
  uint32_t f2;
};

static uint16_t g_3 = 65526UL;
static struct S0 g_4 = {0x2FL, 1L, 0xBEF7D651L};

static struct S0 func_1(void);

static struct S0 func_1(void) {
  uint8_t l_2 = 1UL;
  g_3 = l_2;
  return g_4;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  csmith_sink_ = g_4.f0;
  csmith_sink_ = g_4.f1;
  csmith_sink_ = g_4.f2;
  platform_main_end(0, 0);
  return 0;
}
