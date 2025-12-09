// Options:   --seed 200119 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_119.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_2 = 0L;
static volatile int32_t g_3 = (-1L);
static int32_t g_4 = 0xF506E60BL;

static int64_t func_1(void);

static int64_t func_1(void) {
  uint32_t l_7 = 18446744073709551615UL;
  for (g_4 = 0; (g_4 < 14); g_4 = safe_add_func_uint64_t_u_u(g_4, 3)) {
    return l_7;
  }
  return g_4;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_3;
  csmith_sink_ = g_4;
  platform_main_end(0, 0);
  return 0;
}
