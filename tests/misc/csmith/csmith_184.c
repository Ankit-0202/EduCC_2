// Options:   --seed 200184 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_184.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_5 = 0x2E08974BL;
static uint32_t g_15 = 0x4AD38DC5L;

static const int64_t func_1(void);

static const int64_t func_1(void) {
  int32_t *l_2 = (void *)0;
  int32_t *l_3 = (void *)0;
  int32_t *l_4 = &g_5;
  int32_t *l_6 = &g_5;
  int32_t *l_7 = &g_5;
  int32_t *l_8 = &g_5;
  int32_t *l_9 = &g_5;
  int32_t *l_10 = &g_5;
  int32_t *l_11 = &g_5;
  int32_t *l_12 = (void *)0;
  int32_t *l_13[2];
  int8_t l_14 = 0xD4L;
  int i;
  for (i = 0; i < 2; i++)
    l_13[i] = &g_5;
  g_15++;
  return (*l_7);
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_5;
  csmith_sink_ = g_15;
  platform_main_end(0, 0);
  return 0;
}
