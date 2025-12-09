// Options:   --seed 200197 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_197.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_2[4] = {0xA2CB51DBL, 0xA2CB51DBL, 0xA2CB51DBL, 0xA2CB51DBL};
static int32_t g_3 = 0xE6DA5043L;
static float g_5[2] = {(-0x1.5p-1), (-0x1.5p-1)};
static float *volatile g_4 = &g_5[1];

static int16_t func_1(void);

static int16_t func_1(void) {
  for (g_3 = 3; (g_3 >= 0); g_3 -= 1) {
    int i;
    (*g_4) = g_2[g_3];
  }
  for (g_3 = 0; (g_3 <= 3); g_3 += 1) {
    return g_3;
  }
  return g_2[3];
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 4; i++) {
    csmith_sink_ = g_2[i];
  }
  csmith_sink_ = g_3;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_5[i];
  }
  platform_main_end(0, 0);
  return 0;
}
