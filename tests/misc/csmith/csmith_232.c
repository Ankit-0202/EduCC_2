// Options:   --seed 300232 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 3 --max-pointer-depth 3 --max-block-size 2 --max-block-depth 2
// --max-expr-complexity 4 --max-struct-fields 3 --max-union-fields 2
// --max-array-dim 2 --max-array-len-per-dim 3 --concise --output
// tests/misc/csmith/csmith_232.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

static volatile int32_t g_3 = (-6L);
static volatile int32_t g_4 = 0x8F8256A9L;
static volatile int32_t g_5 = 0x2D4EA680L;
static volatile int32_t g_6 = 0x3EEE2FDEL;
static volatile int32_t g_7 = 0L;
static volatile int32_t g_8 = (-1L);
static volatile int32_t g_9 = 6L;
static volatile int32_t g_10 = 0x999D94B4L;
static int32_t g_11[2][3] = {{0x281D21F1L, 0x281D21F1L, 0x281D21F1L},
                             {0x281D21F1L, 0x281D21F1L, 0x281D21F1L}};
static volatile int32_t g_12 = (-6L);
static int32_t g_13 = 1L;
static int8_t g_17 = 1L;
static int32_t g_19 = 0L;
static int32_t *volatile g_18 = &g_19;

static const int16_t func_1(void);

static const int16_t func_1(void) {
  uint16_t l_2[3][3] = {
      {1UL, 0x0EA7L, 1UL}, {1UL, 0x0EA7L, 1UL}, {1UL, 0x0EA7L, 1UL}};
  int i, j;
  for (g_11[0][1] = 0; (g_11[0][1] <= 2); g_11[0][1] += 1) {
    for (g_13 = 2; (g_13 >= 0); g_13 -= 1) {
      int8_t *l_16 = &g_17;
      int i, j;
      (*g_18) = (l_2[g_11[0][1]][g_11[0][1]] <=
                 (safe_lshift_func_int8_t_s_s(((*l_16) = 0x7DL), 7)));
    }
    for (g_19 = 0; (g_19 <= 2); g_19 += 1) {
      int i, j;
      return l_2[g_19][g_11[0][1]];
    }
  }
  return l_2[0][1];
}

int main(int argc, char *argv[]) {
  int i, j;
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_3;
  csmith_sink_ = g_4;
  csmith_sink_ = g_5;
  csmith_sink_ = g_6;
  csmith_sink_ = g_7;
  csmith_sink_ = g_8;
  csmith_sink_ = g_9;
  csmith_sink_ = g_10;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 3; j++) {
      csmith_sink_ = g_11[i][j];
    }
  }
  csmith_sink_ = g_12;
  csmith_sink_ = g_13;
  csmith_sink_ = g_17;
  csmith_sink_ = g_19;
  platform_main_end(0, 0);
  return 0;
}
