// Options:   --seed 300226 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_226.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  int32_t f0;
  uint8_t f1;
  uint8_t f2;
};

union U2 {
  struct S0 f0;
  const volatile int8_t *volatile f1;
};

static union U2 g_2 = {{0x2EE6D058L, 0x83L, 0xA2L}};

static union U2 func_1(void);

static union U2 func_1(void) { return g_2; }

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2.f0.f0;
  csmith_sink_ = g_2.f0.f1;
  csmith_sink_ = g_2.f0.f2;
  platform_main_end(0, 0);
  return 0;
}
