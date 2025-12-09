// Options:   --seed 300294 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_294.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int16_t g_2[3] = {(-10L), (-10L), (-10L)};
static int32_t g_3 = 1L;
static int32_t g_6 = 4L;
static int32_t g_9 = 0L;

static uint64_t func_1(void);

static uint64_t func_1(void) {
  uint32_t l_7 = 0xBF38C088L;
  for (g_3 = 2; (g_3 >= 0); g_3 -= 1) {
    int32_t *l_4 = (void *)0;
    int32_t *l_5 = &g_6;
    int32_t *l_8 = &g_9;
    int i;
    if (g_2[g_3])
      break;
    (*l_8) ^= (l_7 |= ((*l_5) = g_2[g_3]));
  }
  return l_7;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_2[i];
  }
  csmith_sink_ = g_3;
  csmith_sink_ = g_6;
  csmith_sink_ = g_9;
  platform_main_end(0, 0);
  return 0;
}
