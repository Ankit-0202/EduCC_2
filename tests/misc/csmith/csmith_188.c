// Options:   --seed 200188 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_188.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_2 = 0x8114768CL;
static volatile int32_t g_3 = 0x39ED080CL;
static volatile int32_t g_4 = (-1L);
static int32_t g_5 = 0x978F3C34L;
static int32_t g_8[2][4] = {{(-2L), (-2L), (-2L), (-2L)},
                            {(-2L), (-2L), (-2L), (-2L)}};

static int16_t func_1(void);

static int16_t func_1(void) {
  float l_12 = (-0x1.2p+1);
  int32_t l_13[2][3] = {{2L, 2L, 2L}, {0L, 0L, 0L}};
  int i, j;
  for (g_5 = 0; (g_5 > 28); g_5 = safe_add_func_uint16_t_u_u(g_5, 8)) {
    uint32_t l_11 = 0UL;
    for (g_8[1][1] = 0; (g_8[1][1] > 22);
         g_8[1][1] = safe_add_func_int16_t_s_s(g_8[1][1], 5)) {
      if (l_11)
        break;
    }
  }
  return l_13[1][1];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_3;
  csmith_sink_ = g_4;
  csmith_sink_ = g_5;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 4; j++) {
      csmith_sink_ = g_8[i][j];
    }
  }
  platform_main_end(0, 0);
  return 0;
}
