// Options:   --seed 300202 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_202.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static int32_t g_4 = 0L;
static int32_t *const volatile g_3 = &g_4;
static volatile int32_t g_6 = 0L;
static uint32_t g_7[1][1] = {{4294967288UL}};

static const int64_t func_1(void);

static const int64_t func_1(void) {
  int64_t l_2 = (-4L);
  int32_t *l_5[1];
  int i;
  for (i = 0; i < 1; i++)
    l_5[i] = &g_4;
  (*g_3) = l_2;
  --g_7[0][0];
  return g_6;
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_4;
  csmith_sink_ = g_6;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_7[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
