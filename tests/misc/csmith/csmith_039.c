// Options:   --seed 100039 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_039.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_2[2] = {0L, 0L};
static int32_t g_3 = 9L;
static int32_t g_6[1] = {0x37D8E6E8L};
static int8_t g_9 = 0xE1L;

static int32_t func_1(void);

static int32_t func_1(void) {
  for (g_3 = (-30); (g_3 == (-17)); g_3 = safe_add_func_uint8_t_u_u(g_3, 8)) {
    for (g_6[0] = 0; (g_6[0] >= (-4)); --g_6[0]) {
      return g_6[0];
    }
    if (g_3)
      break;
  }
  return g_9;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_2[i];
  }
  csmith_sink_ = g_3;
  for (i = 0; i < 1; i++) {
    csmith_sink_ = g_6[i];
  }
  csmith_sink_ = g_9;
  platform_main_end(0, 0);
  return 0;
}
