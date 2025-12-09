// Options:   --seed 300280 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_280.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static uint32_t g_3 = 7UL;
static int32_t g_5 = (-7L);
static uint8_t g_6 = 255UL;
static int32_t *g_9 = (void *)0;
static int32_t **volatile g_8 = &g_9;

static int8_t func_1(void);

static int8_t func_1(void) {
  int32_t *l_4[1];
  int i;
  for (i = 0; i < 1; i++)
    l_4[i] = &g_5;
  if ((g_6 = (g_5 ^= (~g_3)))) {
    int32_t *l_7 = &g_5;
    (*g_8) = l_7;
  } else {
    for (g_3 = 0; (g_3 != 6); g_3++) {
      int16_t l_12 = (-8L);
      return l_12;
    }
  }
  g_5 = g_6;
  return g_6;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  csmith_sink_ = g_5;
  csmith_sink_ = g_6;
  platform_main_end(0, 0);
  return 0;
}
