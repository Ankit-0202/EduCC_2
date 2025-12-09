// Options:   --seed 100001 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_001.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S0 {
  volatile int64_t f0;
  int8_t f1;
};

static volatile int32_t g_3 = 0x03629AA8L;
static int32_t g_4 = 0x21DFE4B2L;
static volatile int8_t g_8[1][1] = {{6L}};
static const volatile int8_t *volatile g_7 = &g_8[0][0];
static int32_t g_14[3] = {(-1L), (-1L), (-1L)};
static int32_t *volatile g_13 = &g_14[0];
static struct S0 g_17 = {0L, 0x19L};
static struct S0 g_18[2][3] = {{{0L, 0xCBL}, {0L, 0xCBL}, {-1L, 0x6FL}},
                               {{0L, 0xCBL}, {0L, 0xCBL}, {-1L, 0x6FL}}};

static uint8_t func_1(void);
static struct S0 func_5(int64_t p_6);

static uint8_t func_1(void) {
  uint64_t l_2[1][4];
  int i, j;
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 4; j++)
      l_2[i][j] = 0x88A137B1891F782ALL;
  }
  for (g_3 = 0; g_3 < 1; g_3 += 1) {
    for (g_4 = 0; g_4 < 4; g_4 += 1) {
      l_2[g_3][g_4] = 18446744073709551615UL;
    }
  }
  g_18[1][1] = func_5(((void *)0 != g_7));
  return l_2[0][3];
}

static struct S0 func_5(int64_t p_6) {
  int32_t *l_15 = (void *)0;
  int32_t *l_16[2];
  int i;
  for (i = 0; i < 2; i++)
    l_16[i] = &g_4;
  for (g_4 = 0; (g_4 <= (-11)); g_4 = safe_sub_func_int16_t_s_s(g_4, 4)) {
    (*g_13) = (safe_lshift_func_int16_t_s_u((-1L), g_4));
  }
  g_4 ^= (*g_13);
  return g_17;
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
  for (i = 0; i < 1; i++) {
    for (j = 0; j < 1; j++) {
      csmith_sink_ = g_8[i][j];
    }
  }
  for (i = 0; i < 3; i++) {
    csmith_sink_ = g_14[i];
  }
  csmith_sink_ = g_17.f0;
  csmith_sink_ = g_17.f1;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 3; j++) {
    }
  }
  platform_main_end(0, 0);
  return 0;
}
