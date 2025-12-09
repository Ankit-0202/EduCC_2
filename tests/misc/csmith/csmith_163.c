// Options:   --seed 200163 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_163.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_2[2][4] = {{(-6L), (-6L), (-6L), (-6L)},
                                     {(-6L), (-6L), (-6L), (-6L)}};
static volatile int32_t g_3[2][1] = {{(-6L)}, {(-6L)}};
static int32_t g_4 = 8L;
static volatile float g_8 = (-0x10.2p-1);
static volatile float *volatile g_7 = &g_8;

static const int32_t func_1(void);

static const int32_t func_1(void) {
  for (g_4 = 0; (g_4 >= 21); g_4 = safe_add_func_int64_t_s_s(g_4, 1)) {
    (*g_7) = g_3[0][0];
  }
  return g_3[1][0];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_2[i][j];
    }
  }
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_3[i][j];
    }
  }
  csmith_sink_ = g_4;
  csmith_sink_ = g_8;
  platform_main_end(0, 0);
  return 0;
}
