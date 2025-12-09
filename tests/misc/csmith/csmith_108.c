// Options:   --seed 200108 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_108.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_2 = 0x9AC70C30L;
static volatile int32_t g_3 = (-8L);
static volatile int32_t g_4 = (-1L);
static volatile int32_t g_5 = 0x580849F8L;
static volatile int32_t g_6 = (-9L);
static volatile int32_t g_7 = 0x7B4BC662L;
static int32_t g_8 = 1L;
static volatile int32_t g_11[1][1] = {{(-1L)}};
static volatile int32_t g_12 = 0L;
static int32_t g_13[2] = {1L, 1L};

static uint32_t func_1(void);

static uint32_t func_1(void) {
  uint32_t l_19 = 0xD0890515L;
  for (g_8 = 13; (g_8 >= 24); g_8++) {
    int32_t *l_16 = &g_13[1];
    int32_t *l_17 = &g_13[1];
    int32_t *l_18[3][2];
    int i, j;
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 2; j++)
        l_18[i][j] = &g_13[1];
    }
    for (g_13[1] = 0; (g_13[1] < (-24));
         g_13[1] = safe_sub_func_uint16_t_u_u(g_13[1], 8)) {
      return g_13[1];
    }
    ++l_19;
  }
  return l_19;
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
  csmith_sink_ = g_6;
  csmith_sink_ = g_7;
  csmith_sink_ = g_8;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_11[i][j];
    }
  }
  csmith_sink_ = g_12;
  for (i = 0; i < 2; i++) {
    csmith_sink_ = g_13[i];
  }
  platform_main_end(0, 0);
  return 0;
}
