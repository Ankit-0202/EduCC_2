// Options:   --seed 300230 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_230.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int8_t g_4 = 0xFAL;
static int32_t g_12 = 0x7104272BL;

static uint32_t func_1(void);

static uint32_t func_1(void) {
  uint16_t l_10 = 0xE4B9L;
  int32_t *l_11 = &g_12;
  (*l_11) |= (safe_div_func_uint16_t_u_u(
      g_4, ((!((safe_mul_func_uint8_t_u_u(
                   (safe_add_func_uint64_t_u_u(0xD0289A6957688195LL,
                                               (l_10 < 0x33E34B64B5C6F8B8LL))),
                   1UL)) < 1UL)) ||
            l_10)));
  return (*l_11);
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_4;
  csmith_sink_ = g_12;
  platform_main_end(0, 0);
  return 0;
}
