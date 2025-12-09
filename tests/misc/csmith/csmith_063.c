// Options:   --seed 100063 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_063.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t *volatile g_6 = (void *)0;
static uint8_t g_10 = 255UL;

static int8_t func_1(void);

static int8_t func_1(void) {
  uint8_t l_4 = 0x90L;
  const uint64_t l_5 = 0xA4F402E31D832937LL;
  int32_t *l_7 = (void *)0;
  int32_t *l_8 = (void *)0;
  int32_t l_9 = 0x5F0ED1ADL;
  l_9 ^= (0L && (safe_add_func_uint8_t_u_u(l_4, l_5)));
  return g_10;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_10;
  platform_main_end(0, 0);
  return 0;
}
