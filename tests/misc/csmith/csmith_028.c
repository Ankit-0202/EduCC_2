// Options:   --seed 100028 --no-checksum --no-bitfields --no-packed-struct
// --max-funcs 2 --max-block-size 2 --max-block-depth 3 --max-expr-complexity 4
// --max-struct-fields 3 --max-union-fields 2 --max-array-dim 2
// --max-array-len-per-dim 4 --concise --output tests/misc/csmith/csmith_028.c
#include "csmith.h"

volatile uint64_t csmith_sink_ = 0;

static long __undefined;

struct S1 {
  volatile int64_t f0;
  uint32_t f1;
};

struct S2 {
  int64_t f0;
  struct S1 f1;
  uint32_t f2;
};

static volatile int32_t g_4 = 5L;
static int16_t g_5 = (-1L);
static int32_t g_7 = 0x64FDA7EFL;
static int32_t *volatile g_6 = &g_7;
static uint32_t g_17 = 0UL;
static int16_t g_21 = 1L;
static int32_t g_22 = 2L;
static volatile uint32_t g_23 = 0x450C1979L;
static struct S2 g_26 = {
    0x1DB95674643A64E7LL, {0x5C2F4FE10EF7D594LL, 0x84F75DF1L}, 0x63CFEBDAL};

static struct S2 func_1(void);

static struct S2 func_1(void) {
  int16_t l_3 = 0xC25BL;
  int32_t l_13 = 0xD9DCEE34L;
  (*g_6) = (g_5 &= (((!l_3), g_4) | 0x2760L));
  for (g_5 = 0; (g_5 < 29); g_5++) {
    int32_t *l_10 = (void *)0;
    int32_t *l_11 = &g_7;
    int32_t *l_12 = (void *)0;
    int32_t *l_14 = &l_13;
    int32_t *l_15 = &l_13;
    int32_t *l_16[2][4] = {{&g_7, &g_7, &g_7, &g_7}, {&g_7, &g_7, &g_7, &g_7}};
    int32_t l_20 = 1L;
    int i, j;
    g_17--;
    ++g_23;
  }
  return g_26;
}

int main(int argc, char *argv[]) {
  int print_hash_value = 0;
  if (argc == 2 && strcmp(argv[1], "1") == 0)
    print_hash_value = 1;
  platform_main_begin();
  func_1();
  csmith_sink_ = g_4;
  csmith_sink_ = g_5;
  csmith_sink_ = g_7;
  csmith_sink_ = g_17;
  csmith_sink_ = g_21;
  csmith_sink_ = g_22;
  csmith_sink_ = g_23;
  csmith_sink_ = g_26.f0;
  csmith_sink_ = g_26.f1.f0;
  csmith_sink_ = g_26.f1.f1;
  csmith_sink_ = g_26.f2;
  platform_main_end(0, 0);
  return 0;
}
