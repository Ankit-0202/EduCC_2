// Options:   --seed 200127 --no-checksum --no-bitfields --no-packed-struct
// --float --max-funcs 2 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 4 --concise --output
// tests/misc/csmith/csmith_127.c
#include "csmith.h"
#include <float.h>
#include <math.h>

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

union U1 {
  int32_t f0;
};

static volatile int32_t g_2 = 0L;
static int32_t g_3 = 0x35F394A2L;
static volatile int32_t g_6 = 1L;
static volatile int32_t g_7[4] = {(-3L), (-3L), (-3L), (-3L)};
static volatile int32_t g_8 = 0xD72D7671L;
static volatile int32_t g_9 = 0L;
static int32_t g_10 = 5L;
static int32_t g_15 = 0L;

static union U1 func_1(void);

static union U1 func_1(void) {
  float l_13 = 0xE.7308F4p-47;
  int32_t l_21[4][4] = {
      {2L, 2L, 2L, 2L}, {2L, 2L, 2L, 2L}, {2L, 2L, 2L, 2L}, {2L, 2L, 2L, 2L}};
  int16_t l_32 = (-3L);
  union U1 l_36 = {-3L};
  int i, j;
  for (g_3 = (-22); (g_3 > 21); ++g_3) {
    int32_t l_20 = 0xCF1D65F4L;
    int32_t l_22 = 0L;
    int32_t l_23 = 1L;
    int32_t l_24 = (-2L);
    int32_t l_25 = 0x1D691704L;
    int32_t l_26 = 0x72625AA9L;
    int32_t l_27 = 1L;
    uint64_t l_28 = 1UL;
    int32_t *l_31[1];
    uint16_t l_33[3];
    int i;
    for (i = 0; i < 1; i++)
      l_31[i] = &l_21[0][0];
    for (i = 0; i < 3; i++)
      l_33[i] = 7UL;
    for (g_10 = 0; (g_10 <= (-10)); --g_10) {
      int32_t *l_14 = &g_15;
      int32_t *l_16 = &g_15;
      int32_t *l_17 = &g_15;
      int32_t *l_18 = (void *)0;
      int32_t *l_19[1];
      int i;
      for (i = 0; i < 1; i++)
        l_19[i] = &g_15;
      ++l_28;
    }
    ++l_33[0];
  }
  return l_36;
}

int main(int argc, char *argv[]) {
  int i;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_2;
  csmith_sink_ = g_3;
  csmith_sink_ = g_6;
  for (i = 0; i < 4; i++) {
    csmith_sink_ = g_7[i];
  }
  csmith_sink_ = g_8;
  csmith_sink_ = g_9;
  csmith_sink_ = g_10;
  csmith_sink_ = g_15;
  platform_main_end(0, 0);
  return 0;
}
