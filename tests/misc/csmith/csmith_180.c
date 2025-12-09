// Options:   --seed 200180 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_180.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U3 {
  uint8_t f0;
  const uint16_t f1;
};

static int8_t g_4 = (-1L);
static union U3 g_5 = {0x21L};

static union U3 func_1(void);

static union U3 func_1(void) {
  int8_t *const l_3[3][3] = {
      {&g_4, &g_4, &g_4}, {&g_4, &g_4, &g_4}, {&g_4, &g_4, &g_4}};
  int8_t *const *l_2 = &l_3[0][2];
  int i, j;
  l_2 = (void *)0;
  return g_5;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_4;
  csmith_sink_ = g_5.f0;
  platform_main_end(0, 0);
  return 0;
}
